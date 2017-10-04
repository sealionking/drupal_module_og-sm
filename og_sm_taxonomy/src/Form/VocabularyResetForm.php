<?php

namespace Drupal\og_sm_taxonomy\Form;

use Drupal\Core\Database\Connection;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Url;
use Drupal\node\NodeInterface;
use Drupal\og_sm\SiteManagerInterface;
use Drupal\taxonomy\Form\VocabularyResetForm as VocabularyResetFormBase;
use Drupal\taxonomy\TermStorageInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Provides confirmation form for resetting a vocabulary to alphabetical order.
 */
class VocabularyResetForm extends VocabularyResetFormBase {

  /**
   * The site manager.
   *
   * @var \Drupal\og_sm\SiteManagerInterface
   */
  protected $siteManager;

  /**
   * The database connection.
   *
   * @var \Drupal\Core\Database\Connection
   */
  protected $database;

  /**
   * Constructs a new VocabularyResetForm object.
   *
   * @param \Drupal\taxonomy\TermStorageInterface $term_storage
   *   The term storage.
   */
  public function __construct(TermStorageInterface $term_storage, SiteManagerInterface $site_manager, Connection $database) {
    parent::__construct($term_storage);
    $this->siteManager = $site_manager;
    $this->database = $database;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container) {
    return new static(
      $container->get('entity.manager')->getStorage('taxonomy_term'),
      $container->get('og_sm.site_manager'),
      $container->get('database')
    );
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $form = parent::buildForm($form, $form_state);

    $site = $this->siteManager->currentSite();
    $form_state->set('site', $site);

    return $form;
  }

  /**
   * {@inheritdoc}
   *
   * @param \Drupal\node\NodeInterface $site
   *   The site node.
   */
  public function getCancelUrl(NodeInterface $site = NULL) {
    if (!$site) {
      $site = $this->siteManager->currentSite();
    }

    if (!$site) {
      return parent::getCancelUrl();
    }
    return new Url('og_sm_taxonomy.vocabulary.term_overview', [
      'node' => $site->id(),
      'taxonomy_vocabulary' => $this->getEntity()->id(),
    ]);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    /* @var \Drupal\node\NodeInterface $site */
    $site = $form_state->get('site');
    if (!$site) {
      parent::submitForm($form, $form_state);
      return;
    }

    $form_state->cleanValues();
    $this->entity = $this->buildEntity($form, $form_state);

    // Custom query to order only the terms of the current Site.
    // \Drupal\Core\Database\Query\Update does not support joins :(.
    $query = <<<EOT
    UPDATE
      {taxonomy_term_field_data} td
      JOIN {taxonomy_term__og_audience} audience ON (td.tid = audience.entity_id)
    SET
      td.`weight` = 0
    WHERE
      td.vid = :vid
      AND audience.og_audience_target_id = :gid
EOT;

    $this->database->query($query, [
      ':vid' => $this->getEntity()->id(),
      ':gid' => $site->id(),
    ]);

    drupal_set_message($this->t('Reset vocabulary %name to alphabetical order.', ['%name' => $this->entity->label()]));
    $this->logger('taxonomy')->notice('Reset vocabulary %name to alphabetical order.', ['%name' => $this->entity->label()]);
    $form_state->setRedirectUrl($this->getCancelUrl($site));
  }

}

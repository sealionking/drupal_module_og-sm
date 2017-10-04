<?php

namespace Drupal\og_sm_taxonomy\FormAlter;

use Drupal\Core\DependencyInjection\ContainerInjectionInterface;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Render\Element;
use Drupal\Core\StringTranslation\StringTranslationTrait;
use Drupal\Core\Url;
use Drupal\og_sm\SiteManagerInterface;
use Drupal\og_sm_context\Plugin\OgGroupResolver\QueryParamGroupResolver;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Helper for taxonomy_overview_terms form alter hook.
 *
 * @see og_sm_taxonomy_form_taxonomy_overview_terms_alter()
 */
class TermOverviewFormAlter implements ContainerInjectionInterface {

  use StringTranslationTrait;

  /**
   * The site manager.
   *
   * @var \Drupal\og_sm\SiteManagerInterface
   */
  protected $siteManager;

  /**
   * Construct a TermOverviewFormAlter object.
   *
   * @param \Drupal\og_sm\SiteManagerInterface $site_manager
   *   The site manager.
   */
  public function __construct(SiteManagerInterface $site_manager) {
    $this->siteManager = $site_manager;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container) {
    return new static(
      $container->get('og_sm.site_manager')
    );
  }

  /**
   * This is a helper for og_sm_taxonomy_form_taxonomy_overview_terms_alter().
   *
   * @param array $form
   *   The form variable.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   The form state object.
   */
  public function formAlter(array &$form, FormStateInterface $form_state) {
    $this->addSiteTitles($form);
    $this->alterEmptyText($form, $form_state);
    $this->alterAlphabeticalSubmitHandler($form, $form_state);
  }

  /**
   * Alters the terms administration form by adding the Site titles to the terms.
   *
   * @param array $form
   *   The form structure.
   */
  public function addSiteTitles(array &$form) {
    // Only when not within a Site context.
    if ($this->siteManager->currentSite()) {
      return;
    }

    foreach (Element::children($form['terms']) as $key) {
      if (!preg_match('/^tid\:[0-9]+/', $key)) {
        continue;
      }

      $element = &$form['terms'][$key];

      /* @var \Drupal\taxonomy\TermInterface $term */
      $term = $element['#term'];
      $site = $this->siteManager->getSiteFromEntity($term);
      if (!$site) {
        continue;
      }

      $element['term']['#suffix'] = ' <small>(' . $site->label() . ')</small>';
    }
  }

  /**
   * Alters the empty text link to add the first Site term for the vocabulary.
   *
   * @param array $form
   *   The form structure.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   The form state.
   */
  public function alterEmptyText(array &$form, FormStateInterface $form_state) {
    // Only when there is an empty text element.
    if (empty($form['terms']['#empty'])) {
      return;
    }

    // Only within a Site context.
    $site = $this->siteManager->currentSite();
    if (!$site) {
      return;
    }
    /* @var \Drupal\taxonomy\VocabularyInterface $vocabulary */
    $vocabulary = $form_state->get(['taxonomy', 'vocabulary']);
    $form['terms']['#empty'] = $this->t(
      'No terms available. <a href=":link">Add term</a>.', [
        ':link' => Url::fromRoute('og_sm_taxonomy.vocabulary.term_add', [
          'node' => $site->id(),
          'taxonomy_vocabulary' => $vocabulary->id(),
        ])->toString(),
      ]
    );
  }

  /**
   * Adds a custom submit handler to the alphabetical reset button.
   *
   * @param array $form
   *   The form structure.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   The form state.
   *
   * @see og_sm_taxonomy_form_taxonomy_overview_terms_alter()
   */
  public function alterAlphabeticalSubmitHandler(&$form, FormStateInterface $form_state) {
    // Only when not within a Site context.
    $site = $this->siteManager->currentSite();
    if (!$site) {
      return;
    }
    $form_state->set('site', $site);

    // Custom submit handler.
    $form['actions']['reset_alphabetical']['#submit'][] = [$this, 'submitReset'];
  }

  /**
   * Custom submit handler for the alphabetical reset button.
   *
   * Adds the current site to the reset alphabetical redirect url in order to keep
   * site context on the confirm page.
   *
   * @param array $form
   *   The form structure.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   The form state.
   */
  public function submitReset($form, FormStateInterface $form_state) {
    /* @var \Drupal\Core\Url $redirect_url */
    $redirect_url = $form_state->getRedirect();
    $redirect_url->setRouteParameter(QueryParamGroupResolver::SITE_ID_ARGUMENT, $form_state->get('site')->id());
  }

}

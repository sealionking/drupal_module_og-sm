<?php

namespace Drupal\og_sm_taxonomy;

use Drupal\Core\Database\Query\ConditionInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\og\GroupTypeManager;

/**
 * A manager to keep track of which taxonomy terms are og_sm Site enabled.
 */
class SiteTaxonomyManager implements SiteTaxonomyManagerInterface {

  /**
   * The group type manager.
   *
   * @var \Drupal\og\GroupTypeManager
   */
  protected $groupTypeManager;

  /**
   * The entity type manager.
   *
   * @var \Drupal\Core\Entity\EntityTypeManagerInterface
   */
  protected $entityTypeManager;

  /**
   * Constructs a SiteTaxonomyManager object.
   *
   * @param \Drupal\og\GroupTypeManager $group_type_manager
   *   The group type manager.
   * @param \Drupal\Core\Entity\EntityTypeManagerInterface $entity_type_manager
   *   The entity type manager.
   */
  public function __construct(GroupTypeManager $group_type_manager, EntityTypeManagerInterface $entity_type_manager) {
    $this->groupTypeManager = $group_type_manager;
    $this->entityTypeManager = $entity_type_manager;
  }

  /**
   * {@inheritdoc}
   */
  public function getSiteVocabularyNames() {
    try {
      return $this->groupTypeManager->getAllGroupContentBundlesByEntityType('taxonomy_term');
    }
    catch (\InvalidArgumentException $exception) {
      return [];
    }
  }

  /**
   * {@inheritdoc}
   */
  public function getSiteVocabularies() {
    $vids = $this->getSiteVocabularyNames();
    if (!$vids) {
      return [];
    }

    return $this->entityTypeManager->getStorage('taxonomy_vocabulary')->loadMultiple($vids);
  }

  /**
   * {@inheritdoc}
   */
  public function getSiteVocabulariesFromConditions(array $table_aliases, array $conditions, array $vocabularies = []) {
    foreach ($conditions as $condition) {
      if (empty($condition['field'])) {
        continue;
      }

      // If the condition field implements the QueryConditionInterface it means
      // this condition contains several child conditions. In that case we need
      // loop through those to find the referenced vocabularies.
      if ($condition['field'] instanceof ConditionInterface) {
        $vocabularies = $this->getSiteVocabulariesFromConditions($table_aliases, $condition['field']->conditions(), $vocabularies);
        continue;
      }

      if (!is_string($condition['field']) || empty($condition['value'])) {
        continue;
      }
      // Check if the condition field is either a vid or a machine name. If so
      // load the vocabularies and add them to the vocabularies array.
      $field_parts = explode('.', $condition['field']);
      if (!count($field_parts) === 2) {
        continue;
      }

      if (!in_array($field_parts[0], $table_aliases)) {
        continue;
      }

      switch ($field_parts[1]) {
        case 'vid':
          $vids = (array) $condition['value'];
          $vocabularies += $this->entityTypeManager->getStorage('taxonomy_vocabulary')->loadMultiple($vids);
          break;

        case 'machine_name':
          $machine_names = (array) $condition['value'];
          $vocabularies += $this->entityTypeManager->getStorage('taxonomy_vocabulary')->loadByProperties(['machine_name' => $machine_names]);
          break;
      }
    }

    return $vocabularies;
  }

  /**
   * {@inheritdoc}
   */
  public function isSiteVocabulary($name) {
    $names = $this->getSiteVocabularyNames();
    return array_key_exists($name, $names);
  }

}

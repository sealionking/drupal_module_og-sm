<?php
/**
 * @file
 * Pathauto integration for profiles.
 *
 * @ingroup pathauto
 */

/**
 * Implements hook_path_alias_types().
 */
function og_sm_profile_path_alias_types() {
  $objects['profile/'] = t('Site User Profiles');
  return $objects;
}

/**
 * Implements hook_pathauto().
 */
function og_sm_profile_pathauto($op) {
  switch ($op) {
    case 'settings':
      $settings = array();
      $settings['module'] = 'og_sm_profile';
      $settings['token_type'] = 'og_sm_profile';
      $settings['groupheader'] = t('Site User Profile paths');
      $settings['patterndescr'] = t('Default path pattern');
      $settings['patterndefault'] = 'profile/[og_sm_profile:id]';
      $settings['batch_update_callback'] = 'og_sm_profile_pathauto_bulk_update_batch_process';
      $settings['batch_file'] = drupal_get_path('module', 'og_sm_profile') . '/og_sm_profile.pathauto.inc';
      return (object) $settings;

    default:
      break;
  }
}

/**
 * Batch processing callback; Generate aliases for profiles.
 */
function og_sm_profile_pathauto_bulk_update_batch_process(&$context) {
  if (!isset($context['sandbox']['current'])) {
    $context['sandbox']['count'] = 0;
    $context['sandbox']['current'] = 0;
  }

  $query = db_select('og_sm_profile', 'p');
  $query->leftJoin('url_alias', 'ua', "CONCAT('profile/', p.id) = ua.source");
  $query->addField('p', 'id');
  $query->isNull('ua.source');
  $query->condition('p.id', $context['sandbox']['current'], '>');
  $query->orderBy('p.id');
  $query->addTag('pathauto_bulk_update');

  // Get the total amount of items to process.
  if (!isset($context['sandbox']['total'])) {
    $context['sandbox']['total'] = $query->countQuery()->execute()->fetchField();

    // If there are no profiles to update, the stop immediately.
    if (!$context['sandbox']['total']) {
      $context['finished'] = 1;
      return;
    }
  }

  $query->range(0, 25);
  $profile_ids = $query->execute()->fetchCol();

  og_sm_profile_pathauto_update_alias_multiple($profile_ids, 'bulkupdate');
  $context['sandbox']['count'] += count($profile_ids);
  $context['sandbox']['current'] = max($profile_ids);
  $context['message'] = t('Updated alias for profile @profile_id.', array('@profile_id' => end($profile_ids)));

  if ($context['sandbox']['count'] != $context['sandbox']['total']) {
    $context['finished'] = $context['sandbox']['count'] / $context['sandbox']['total'];
  }
}

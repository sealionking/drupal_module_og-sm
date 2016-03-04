<?php
/**
 * @file
 * Pathauto related hook implementations.
 */

/**
 * Implements hook_path_alias_types().
 */
function og_sm_pathauto_path_alias_types() {
  $objects = array();

  $objects['group/node/%/admin'] = t('Site administration');
  $objects['node/%/group'] = t('Site administration');

  return $objects;
}

/**
 * Implements hook_pathauto().
 */
function og_sm_pathauto_pathauto($op) {
  switch ($op) {
    case 'settings':
      $settings = array();
      $settings['module'] = 'og_sm';
      $settings['token_type'] = 'node';
      $settings['groupheader'] = t('Site admin paths');
      $settings['patterndescr'] = t('Path pattern that will replace the <em>group/node/%nid</em> part of the Site administration paths.');
      $settings['patterndefault'] = '[node:site-name]';
      $settings['batch_update_callback'] = 'og_sm_pathauto_bulk_update_batch_process';
      $settings['batch_file'] = drupal_get_path('module', 'og_sm_pathauto') . '/og_sm_pathauto.batch.inc';
      return (object) $settings;

    default:
      break;
  }
}

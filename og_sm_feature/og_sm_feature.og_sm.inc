<?php
/**
 * @file
 * Implementation of the og_sm hooks.
 */


/**
 * Implements hook_og_sm_admin_menu().
 */
function og_sm_feature_og_sm_admin_menu() {
  $items = array();

  $items['structure/features'] = array(
    'title' => 'Features',
    'description' => 'Manage Site features.',
    'href' => 'admin/features',
    'weight' => 0,
  );

  // Make items translatable.
  if (FALSE) {
    t('Features');
    t('Manage Site features.');
  }

  return $items;
}

<?php
/**
 * @file
 * Site Manager (og_sm) related hooks.
 */

/**
 * Implements hook_og_sm_admin_menu().
 */
function og_sm_taxonomy_og_sm_admin_menu() {
  $items = array();

  $items['structure/taxonomy'] = array(
    'title' => 'Taxonomy',
    'description' => 'Manage taxonomy terms.',
    'href' => 'admin/taxonomy',
    'weight' => 0,
  );

  // Make items translatable.
  if (FALSE) {
    t('Taxonomy');
    t('Manage taxonomy terms.');
  }

  return $items;
}

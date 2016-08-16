<?php

/**
 * @file
 * Implemented og_sm hooks.
 */

/**
 * Implements hook_og_sm_admin_menu().
 */
function og_sm_og_sm_admin_menu() {
  $items = array();

  $items['site'] = array(
    'title' => 'Edit Site',
    'href' => 'admin/edit',
    'column' => 'right',
    'weight' => 100,
  );
  $items['site/edit'] = array(
    'title' => 'Edit Site',
    'description' => 'Edit the Site node.',
    'href' => 'admin/edit',
    'weight' => -100,
    'exclude_menu' => TRUE,
  );

  t('Edit Site');
  t('Edit the Site node.');

  return $items;
}

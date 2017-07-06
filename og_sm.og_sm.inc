<?php

/**
 * @file
 * Implemented og_sm hooks.
 */

/**
 * Implements hook_og_sm_admin_menu().
 *
 * @todo: Needs to be converted to yml file once og_sm_admin_menu is ported.
 */
function og_sm_og_sm_admin_menu() {
  $items = array();

  $items['structure/site-edit'] = array(
    'title' => 'Edit Site',
    'description' => 'Edit the Site node.',
    'href' => 'admin/site-edit',
    'weight' => 0,
  );

  t('Edit Site');
  t('Edit the Site node.');

  return $items;
}

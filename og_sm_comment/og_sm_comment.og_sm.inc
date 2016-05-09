<?php
/**
 * @file
 * Site Manager (og_sm) related hooks.
 */

/**
 * Implements hook_og_sm_admin_menu().
 */
function og_sm_comment_og_sm_admin_menu() {
  $items = array();

  $items['content/comments'] = array(
    'title' => 'Administer comments',
    'description' => 'Manage the comments of this Site.',
    'href' => 'admin/comments',
    'weight' => -5,
  );

  // Make items translatable.
  t('Administer comments');
  t('Manage the comments of this Site.');

  return $items;
}

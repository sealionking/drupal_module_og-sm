<?php
/**
 * @file
 * Site Manager (og_sm) related hooks.
 */

/**
 * Implements hook_og_sm_admin_menu().
 */
function og_sm_content_og_sm_admin_menu() {
  $items = array();

  // Administer content.
  $items['content'] = array(
    'title' => 'Content',
    'href' => 'admin/content',
    'column' => 'left',
    'weight' => -10,
  );
  $items['content/add'] = array(
    'title' => 'Add content',
    'description' => 'Add new content for this Site.',
    'href' => 'content/add',
    'exclude_menu' => TRUE,
    'weight' => -10,
  );
  $items['content/overview'] = array(
    'title' => 'Manage content',
    'description' => 'Manage contents of this Site.',
    'href' => 'admin/content',
    'exclude_menu' => TRUE,
    'weight' => -9,
  );

  $items['structure/site-settings'] = array(
    'title' => 'Site settings',
    'description' => 'Administer settings for this Site.',
    'href' => 'admin/site-settings',
    'weight' => 6,
  );

  // Make items translatable.
  if (FALSE) {
    t('Add content');
    t('Overview of all content types that can be created.');
    t('Manage content');
    t('Manage contents of this Site.');
    t('Site settings');
    t('Administer Site specific settings.');
  }

  return $items;
}

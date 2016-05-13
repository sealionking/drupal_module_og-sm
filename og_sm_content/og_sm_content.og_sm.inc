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

  // Administer content types.
  $items['structure/content_types'] = array(
    'title' => 'Content types',
    'description' => 'Administer the content types for this Site.',
    'href' => 'admin/structure/types',
    'column' => 'left',
    'weight' => 10,
  );

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

  // Make items translatable.
  if (FALSE) {
    t('Content types');
    t('Administer the content types for this Site.');
    t('Add content');
    t('Overview of all content types that can be created.');
    t('Manage content');
    t('Manage contents of this Site.');
  }

  return $items;
}

/**
 * Implements hook_og_sm_content_type_info_alter().
 */
function og_sm_content_og_sm_content_type_info_alter(&$type_info, $site) {
  $key_base = 'og_sm_content_' . $type_info->type . '_';

  $type_info->site_type = check_plain(
    og_sm_variable_get($site->nid, $key_base . 'machine_name', $type_info->type)
  );
  $type_info->name = check_plain(
    og_sm_variable_get($site->nid, $key_base . 'name', $type_info->name)
  );
  $type_info->name_plural = check_plain(
    og_sm_variable_get($site->nid, $key_base . 'name_plural', $type_info->name)
  );

  // TODO: move comments to og_sm_comments.
  if (module_exists('comment')) {
    $type_info->comment = variable_get('comment_' . $type_info->type, COMMENT_NODE_OPEN);

    // The comment setting can only be overridden when the node type's comments
    // are open.
    if ((int) $type_info->comment === COMMENT_NODE_OPEN) {
      $type_info->comment = og_sm_variable_get($site->nid, $key_base . 'comment', $type_info->comment);
    }
  }
}

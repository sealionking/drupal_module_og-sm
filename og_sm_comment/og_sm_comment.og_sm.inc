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

/**
 * Implements hook_og_sm_content_type_info_alter().
 */
function og_sm_comment_og_sm_content_type_info_alter(&$type_info, $site) {
  // Global value as fallback.
  $type_info->comment = variable_get('comment_' . $type_info->type, COMMENT_NODE_OPEN);

  // The comment setting can only be overridden when the node type's comments
  // are open.
  if ((int) $type_info->comment === COMMENT_NODE_OPEN) {
    $type_info->comment = og_sm_variable_get(
      $site->nid,
      'og_sm_content_' . $type_info->type . '_comment',
      $type_info->comment
    );
  }
}

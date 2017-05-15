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
  $comment_global = variable_get('comment_' . $type_info->type, COMMENT_NODE_OPEN);
  $type_info->comment = $comment_global;
  $type_info->comment_override = 0;
  $type_info->comment_override_default = 0;
  $type_info->comment_override_default_value = $comment_global;

  // The comment setting can only be overridden when the node type's comments
  // are open.
  if ((int) $comment_global === COMMENT_NODE_OPEN) {
    $type_info->comment = og_sm_variable_get(
      $site->nid,
      sprintf('og_sm_content_%s_comment', $type_info->type),
      $type_info->comment
    );
    $type_info->comment_override = og_sm_variable_get(
      $site->nid,
      sprintf('og_sm_content_%s_comment_override', $type_info->type),
      $type_info->comment_override
    );
    $type_info->comment_override_default = og_sm_variable_get(
      $site->nid,
      sprintf('og_sm_content_%s_comment_override_default', $type_info->type),
      $type_info->comment_override_default
    );
    $type_info->comment_override_default_value = og_sm_variable_get(
      $site->nid,
      sprintf('og_sm_content_%s_comment_override_default_value', $type_info->type),
      $type_info->comment_override_default_value
    );
  }
}

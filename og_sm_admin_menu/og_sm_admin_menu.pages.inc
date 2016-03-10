<?php
/**
 * @file
 * Page callbacks.
 */

/**
 * Placeholder for dynamic menu items.
 */
function og_sm_admin_menu_placeholder($token) {
  return $token;
}

/**
 * Build an overview page of all Administration tasks.
 *
 * @param object $site
 *   The Site node.
 * @param string $part
 *   (optional) The part of the items that should be listed.
 *   All will be listed if no part is given.
 *
 * @return string
 *   The rendered output.
 */
function og_sm_admin_menu_overview($site, $part = NULL) {
  module_load_include('inc', 'og_sm_admin_menu', 'og_sm_admin_menu.menu');
  $items = og_sm_admin_menu_items();

  $groups = array('left' => array(), 'right' => array());
  foreach ($items as $item) {
    $column = (!empty($item['column'])) ? $item['column'] : 'right';
    $group_items = _og_sm_admin_menu_overview_group_items($site, $item);
    if (!$group_items) {
      continue;
    }

    $groups[$column][] = theme(
      'og_sm_admin_menu_overview_group',
      array(
        // @codingStandardsIgnoreStart
        'title' => t($item['title']),
        // @codingStandardsIgnoreEnd
        'items' => $group_items,
        'class' => $item['path'],
      )
    );
  }

  return theme('og_sm_admin_menu_overview', $groups);
}

/**
 * Create an overview of grouped items.
 *
 * @param object $site
 *   The Site node for who we are creating this overview.
 * @param array $item
 *   The group item.
 *
 * @return array
 *   Array of rendered items.
 */
function _og_sm_admin_menu_overview_group_items($site, $item) {
  $group_items = array();
  if (empty($item['children'])) {
    return $group_items;
  }

  // Translate the items.
  foreach ($item['children'] as $child) {
    if (!empty($child['exclude_overview'])) {
      continue;
    }

    $path_raw = og_sm_admin_menu_router_path_from_admin_path($site, $child['admin_path']);

    // Load menu item and check access.
    $menu_item = menu_get_item($path_raw);
    if (empty($menu_item['access'])) {
      continue;
    }

    // Create the group item data.
    $group_items[$child['path']] = theme(
      'og_sm_admin_menu_overview_group_item',
      array(
        'url' => url($path_raw),
        // @codingStandardsIgnoreStart
        'title' => t($child['title']),
        'description' => (!empty($child['description']))
          ? t($child['description'])
          : NULL,
        // @codingStandardsIgnoreEnd
        'class' => preg_replace('#/#', '-', $child['path']),
      )
    );
  }

  return $group_items;
}

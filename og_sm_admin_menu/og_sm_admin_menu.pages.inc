<?php
/**
 * @file
 * Page callbacks.
 */

/**
 * Placeholder for dynamic menu items.
 */
function og_sm_admin_menu_placeholder($token) {
  return t('Token : @token', array('@token' => $token));
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
  $items = og_sm_admin_menu_items();

  if (empty($part)) {
    return _og_sm_admin_menu_overview_all($site, $items);
  }

  if (isset($items[$part])) {
    return _og_sm_admin_menu_overview_sub($site, $items[$part]);
  }

  drupal_not_found();
}

/**
 * Create the full overview.
 *
 * @param object $site
 *   The site to create the overview for.
 * @param array $items
 *   The items to create the overview from.
 *
 * @return string
 *   The rendered overview.
 */
function _og_sm_admin_menu_overview_all($site, array $items) {
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

  if (!empty($groups['left']) || !empty($groups['right'])) {
    return theme('og_sm_admin_menu_overview_all', $groups);
  }

  return t('You do not have any administrative items.');
}

/**
 * Create the overview for a sub page.
 *
 * @param object $site
 *   The site to generate the overview for.
 * @param array $item
 *   The item to generate the overview for.
 *
 * @return string
 *   The rendered output.
 */
function _og_sm_admin_menu_overview_sub($site, array $item) {
  $items = _og_sm_admin_menu_overview_group_items($site, $item);

  if ($items) {
    return theme('og_sm_admin_menu_overview_sub', array('items' => $items));
  }

  return t('You do not have any administrative items.');
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

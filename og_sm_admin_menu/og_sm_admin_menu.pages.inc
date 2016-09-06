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
  module_load_include('inc', 'og_sm_admin_menu', 'og_sm_admin_menu.menu');
  $items = _og_sm_admin_menu_load_site_menu('overview');

  if (empty($part)) {
    return _og_sm_admin_menu_overview_all($site, $items);
  }

  $item = _og_sm_admin_menu_overview_get_item($part, $items);
  if (!empty($item)) {
    return _og_sm_admin_menu_overview_sub($site, $item);
  }

  return MENU_NOT_FOUND;
}

/**
 * Create the full overview.
 *
 * @param object $site
 *   The site to create the overview for.
 * @param array $items
 *   The menu tree to create the overview from.
 *
 * @return string
 *   The rendered overview.
 */
function _og_sm_admin_menu_overview_all($site, array $items) {
  $groups = array('left' => array(), 'right' => array());

  foreach ($items as $item) {
    if (empty($item['link']['options'])) {
      continue;
    }
    $options = $item['link']['options'];

    $group_items = _og_sm_admin_menu_overview_group_items($site, $item);
    if (!$group_items) {
      continue;
    }

    $column = (!empty($options['og_sm_admin_menu_item_column']))
      ? $options['og_sm_admin_menu_item_column']
      : 'right';
    $groups[$column][] = theme(
      'og_sm_admin_menu_overview_group',
      array(
        'title' => $item['link']['title'],
        'items' => $group_items,
        'class' => $options['og_sm_admin_menu_item_path'],
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
 *   The menu tree item to generate the overview for.
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
 *   The group item menu tree.
 *
 * @return array
 *   Array of rendered items.
 */
function _og_sm_admin_menu_overview_group_items($site, $item) {
  $group_items = array();
  if (empty($item['below'])) {
    return $group_items;
  }

  // Translate the items.
  foreach ($item['below'] as $child) {
    $group_item = _og_sm_admin_menu_overview_group_item($site, $child);
    if (empty($group_item)) {
      continue;
    }

    $path = $child['link']['localized_options']['og_sm_admin_menu_item_path'];
    $group_items[$path] = $group_item;
  }

  foreach ($group_items as $path => $group_item) {
    $group_items[$path] = render($group_item);
  }

  return $group_items;
}

/**
 * Create a single element (link).
 *
 * @param object $site
 *   The Site node for who we are creating the link.
 * @param array $child
 *   The child menu tree item to add to a group.
 *
 * @return array|null
 *   The item to add to the overview, or NULL if the item should not be
 *   displayed.
 */
function _og_sm_admin_menu_overview_group_item($site, $child) {
  if (empty($child['link']['localized_options'])) {
    return;
  }
  $options = $child['link']['localized_options'];

  if (empty($child['link']['access'])) {
    return;
  }

  // Create the group item data.
  return array(
    '#theme' => 'og_sm_admin_menu_overview_group_item',
    '#url' => $child['link']['href'],
    '#title' => $child['link']['title'],
    '#description' => $child['link']['description'],
    '#class' => drupal_html_class($options['og_sm_admin_menu_item_path']),
  );
}

/**
 * Get the sub elements (children) of a main menu element by its item name.
 *
 * @param string $part
 *   The item part name as defined in the hook_og_sm_admin_menu().
 * @param array $items
 *   The menu tree items.
 *
 * @return array|null
 *   The found menu items.
 */
function _og_sm_admin_menu_overview_get_item($part, $items) {
  foreach ($items as $item) {
    if (empty($item['link']['localized_options']['og_sm_admin_menu_item_path'])) {
      continue;
    }

    if ($part !== $item['link']['localized_options']['og_sm_admin_menu_item_path']) {
      continue;
    }

    // We found the main item.
    return $item;
  }
}

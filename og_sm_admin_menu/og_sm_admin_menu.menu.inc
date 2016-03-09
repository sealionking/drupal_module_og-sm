<?php
/**
 * @file
 * Include file containing the functionality to create Site admin menu.
 */

/**
 * Load the Platform Administration menu to show in the admin_menu bar.
 *
 * @return array
 *   The og_sm_admin menu structure.
 */
function og_sm_admin_menu_load_platform() {
  $menu_data = menu_tree_all_data('management');

  $menu = admin_menu_links_menu($menu_data);
  $menu['#theme'] = 'admin_menu_links';
  $menu['#wrapper_attributes']['id'] = 'admin-menu-menu';
  $menu['#weight'] = 0;

  return $menu;
}

/**
 * Load the Site Administration menu to show in the admin_menu bar.
 *
 * @return array
 *   The og_sm_admin menu structure.
 */
function og_sm_admin_menu_load_site() {
  global $language;

  $menu_name = _og_sm_admin_menu_build_menu_name($language->language);
  $menu_data = menu_tree_all_data($menu_name);
  $menu = admin_menu_links_menu($menu_data);

  $menu['#theme'] = 'admin_menu_links';
  $menu['#wrapper_attributes']['id'] = 'admin-menu-menu';
  $menu['#weight'] = 0;

  return $menu;
}

/**
 * Create/Get the Administration menu records.
 */
function og_sm_admin_menu_build_menus() {
  $menus = array();

  // Create menu for each language.
  $languages = array_keys(language_list());
  foreach ($languages as $language) {
    $menu_name = _og_sm_admin_menu_build_menu_name($language);
    $menu = menu_load($menu_name);
    if (!$menu) {
      $t_options = array('language' => $language);
      $t_args = array('@language' => $language);
      $menu = array(
        'menu_name' => $menu_name,
        'title' => t('Site Administration menu (@language)', $t_args, $t_options),
        'description' => t('Menu to manage Site configuration.', $t_args, $t_options),
      );
      menu_save($menu);
    }

    $menus[$language] = $menu;
  }

  return $menus;
}

/**
 * Create the menu items.
 *
 * @param object $menu
 *   The menus to create the item for.
 * @param string $language
 *   The menu language.
 * @param array $items
 *   Array of menu items to create.
 */
function og_sm_admin_menu_build_items($menu, $language, array $items) {
  // Add the items.
  foreach ($items as $item) {
    og_sm_admin_menu_build_item($menu, $language, $item);
  }
}

/**
 * Create a menu item.
 *
 * @param object $menu
 *   The menu to create the item for.
 * @param string $language
 *   The menu language.
 * @param array $item
 *   The menu item.
 * @param int $plid
 *   (optional) Parent menu link id.
 */
function og_sm_admin_menu_build_item($menu, $language, array $item, $plid = NULL) {
  // Exclude from menu?
  if (!empty($item['exclude_menu'])) {
    return;
  }

  $router = $item['router'];

  $router_path = ($router)
    ? $router->path
    : 'group/%/%/' . $item['href'];
  $link_path = _og_sm_admin_menu_build_item_link_placeholder();
  $admin_path = preg_replace('#group/%/%/#', 'group/node/[site:nid]/', $router->path);
  $t_options = array('language' => $language);

  // Item structure.
  $menu_item = array(
    'link_path' => $link_path,
    // @codingStandardsIgnoreStart
    'link_title' => t($item['title'], array(), $t_options),
    // @codingStandardsIgnoreEnd
    'menu_name' => $menu['menu_name'],
    'weight' => $item['weight'],
    'options' => array(
      'og_sm_admin_menu_router' => $router_path,
      'og_sm_admin_menu_path' => $admin_path,
      'og_sm_admin_menu_uuid' => $link_path,
      'alter' => TRUE,
    ),
    'plid' => $plid,
    'expanded' => (int) !empty($item['children']),
  );

  // Save item.
  $mlid = menu_link_save($menu_item);

  // Add the children (if any).
  if (!empty($item['children'])) {
    foreach ($item['children'] as $child) {
      og_sm_admin_menu_build_item($menu, $language, $child, $mlid);
    }
  }
}

/**
 * Helper to create a menu name based on the language.
 *
 * @param string $language
 *   The language to create the menu for.
 *
 * @return string
 *   The menu name.
 */
function _og_sm_admin_menu_build_menu_name($language) {
  return OG_SM_ADMIN_MENU_NAME_PREFIX . '-' . $language;
}

/**
 * Helper to create the link path placeholder.
 *
 * @return string
 *   The placeholder.
 */
function _og_sm_admin_menu_build_item_link_placeholder() {
  return OG_SM_ADMIN_MENU_PLACEHOLDER . '/' . uniqid(NULL, TRUE);
}


/**
 * Get the menu structure as defined in the hooks.
 *
 * @return array
 *   The menu including the information from the menu_router table.
 */
function og_sm_admin_menu_items() {
  $items = array();

  // Convert hook information to menu structure.
  $menu_items = _og_sm_admin_menu_from_hooks();
  foreach ($menu_items as $path => $menu_item) {
    _og_sm_admin_menu_items_add($items, $path, $menu_item);
  }

  // Order items and their children.
  uasort($items, 'drupal_sort_weight');
  foreach ($items as $path => $item) {
    uasort($item['children'], 'drupal_sort_weight');
    $items[$path] = $item;
  }

  return $items;
}

/**
 * Add an item to the administration menu.
 *
 * @param array $items
 *   The menu items.
 * @param string $path
 *   Item path in the menu.
 * @param array $item
 *   The item to add.
 */
function _og_sm_admin_menu_items_add(array &$items, $path, array $item) {
  // Determine if we have a root or sub item.
  $path_parts = preg_split('#/#', $path, 2);

  // Root element.
  if (empty($path_parts[1])) {
    _og_sm_admin_menu_items_add_root($items, $path, $item);
    return;
  }

  // Child element.
  _og_sm_admin_menu_items_add_root($items, $path_parts[0], array('placeholder' => TRUE));
  _og_sm_admin_menu_item_add_child($items, $path_parts[0], $path_parts[1], $item);
}

/**
 * Add a root element to the menu.
 *
 * @param array $items
 *   The menu items.
 * @param string $path
 *   Item path in the menu.
 * @param array $item
 *   The item to add.
 */
function _og_sm_admin_menu_items_add_root(&$items, $path, $item) {
  if (empty($items[$path])) {
    $items[$path] = $item;
    $items[$path]['children'] = array();
    $items[$path]['path'] = $path;
  }

  // Stop here when it is a placeholder.
  if (!empty($item['placeholder'])) {
    return;
  }

  // Actual data comes after placeholder has been inserted.
  $items[$path] = array_merge(_og_sm_admin_menu_item_info($item), $items[$path]);
  $items[$path]['placeholder'] = FALSE;
}

/**
 * Add a child element to the menu.
 *
 * @param array $items
 *   The menu items.
 * @param string $path_parent
 *   The item parent path.
 * @param string $path
 *   Item path in the menu.
 * @param array $item
 *   The item to add.
 */
function _og_sm_admin_menu_item_add_child(array &$items, $path_parent, $path, array &$item) {
  $item['path'] = $path_parent . '/' . $path;
  $items[$path_parent]['children'][$path] = _og_sm_admin_menu_item_info($item);
}

/**
 * Add more info to the item.
 *
 * @param array $item
 *   The item to complete.
 *
 * @return array
 *   The item with more info.
 */
function _og_sm_admin_menu_item_info($item) {
  if (!empty($item['href'])) {
    $item['router'] = _og_sm_admin_menu_items_load_router_item($item['href']);
  }
  return $item;
}

/**
 * Load a router item by its path after group/%/%/.
 *
 * @param string $href
 *   The href path from the og_sm administration menu items.
 *
 * @return array
 *   The menu_router item.
 */
function _og_sm_admin_menu_items_load_router_item($href) {
  $query = db_select('menu_router', 'mr');
  $query->fields('mr');
  $query->condition('mr.path', 'group/%/%/' . $href);

  return $query->execute()->fetchObject();
}

/**
 * Get all menu items as defined in the hook_og_sm_admin_menu().
 *
 * @return array
 *   The admin navigation menu.
 */
function _og_sm_admin_menu_from_hooks() {
  $items = array();

  $modules = module_implements('og_sm_admin_menu');
  foreach ($modules as $module) {
    $module_items = call_user_func($module . '_og_sm_admin_menu');
    if ($module_items) {
      $items = array_merge($items, $module_items);
    }
  }

  drupal_alter('og_sm_admin_menu', $items);
  return $items;
}

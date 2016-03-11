<?php
/**
 * @file
 * Include file containing the functionality to create Site admin menu.
 */

/**
 * Create the admin menu(s) based on the implemented hooks.
 */
function _og_sm_admin_menu_rebuild() {
  // Get/Create the menus.
  $menu = _og_sm_admin_menu_build_menu();

  // Delete first all existing links.
  menu_delete_links($menu['menu_name']);

  // Build the menu items.
  $items = og_sm_admin_menu_items();
  _og_sm_admin_menu_build_items($menu, $items);
}

/**
 * Create/Get the Administration menu records.
 */
function _og_sm_admin_menu_build_menu() {
  $menu_name = OG_SM_ADMIN_MENU_NAME;
  $menu = menu_load($menu_name);

  if (!$menu) {
    $menu = array(
      'menu_name' => $menu_name,
      'title' => 'Site Administration menu',
      'description' => 'Menu to manage Site configuration.',
    );
    menu_save($menu);
  }

  return $menu;
}

/**
 * Create the menu items.
 *
 * @param object $menu
 *   The menus to create the item for.
 * @param array $items
 *   Array of menu items to create.
 */
function _og_sm_admin_menu_build_items($menu, array $items) {
  // Add the items.
  foreach ($items as $item) {
    _og_sm_admin_menu_build_item($menu, $item);
  }
}

/**
 * Create a menu item.
 *
 * @param object $menu
 *   The menu to create the item for.
 * @param array $item
 *   The menu item.
 * @param int $plid
 *   (optional) Parent menu link id.
 */
function _og_sm_admin_menu_build_item($menu, array $item, $plid = NULL) {
  // Exclude from menu?
  if (!empty($item['exclude_menu'])) {
    return;
  }

  $router = $item['router'];

  $router_path = ($router)
    ? $router->path
    : 'group/%/%/' . $item['href'];
  $link_path = _og_sm_admin_menu_build_item_link_placeholder();
  $admin_path = $item['admin_path'];

  // Item structure.
  $menu_item = array(
    'link_path' => $link_path,
    'link_title' => $item['title'],
    'menu_name' => $menu['menu_name'],
    'weight' => $item['weight'],
    'options' => array(
      'og_sm_admin_menu_router' => $router_path,
      'og_sm_admin_menu_path' => $admin_path,
      'og_sm_admin_menu_uuid' => $link_path,
      'og_sm_admin_menu_item_column' => !empty($item['column']) ? $item['column'] : FALSE,
      'og_sm_admin_menu_item_description' => !empty($item['description']) ? $item['description'] : FALSE,
      'og_sm_admin_menu_item_exclude_menu' => !empty($item['exclude_menu']),
      'og_sm_admin_menu_item_exclude_overview' => !empty($item['exclude_overview']),
      'og_sm_admin_menu_item_path' => $item['path'],
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
      _og_sm_admin_menu_build_item($menu, $child, $mlid);
    }
  }
}

/**
 * Helper to create the link path placeholder.
 *
 * @return string
 *   The placeholder.
 */
function _og_sm_admin_menu_build_item_link_placeholder() {
  return OG_SM_ADMIN_MENU_NAME . '/' . uniqid(NULL, TRUE);
}


/**
 * Get the menu structure as defined in the hooks.
 *
 * @return array
 *   The menu including the information from the menu_router table.
 */
function _og_sm_admin_menu_items() {
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
    $router = _og_sm_admin_menu_items_load_router_item($item['href']);
    $item['router'] = $router;
    $item['admin_path'] = $router
      ? preg_replace('#group/%/%/#', 'group/node/[site:nid]/', $router->path)
      : NULL;
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

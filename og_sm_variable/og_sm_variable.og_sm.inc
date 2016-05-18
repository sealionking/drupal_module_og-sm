<?php
/**
 * @file
 * Implementations of hooks provided by og_sm module suite.
 */

/**
 * Implements hook_og_sm_site_insert().
 *
 * Search for modules who provide default values and set them for the newly
 * created Site.
 */
function og_sm_variable_og_sm_site_insert($site) {
  $defaults = og_sm_variable_get_defaults($site);
  if (!$defaults) {
    return;
  }

  foreach ($defaults as $name => $value) {
    og_sm_variable_set($site->nid, $name, $value);
  }
}

/**
 * Get all the default values as defined by the hooks.
 *
 * @param object $site
 *   The site to create the default values for.
 *
 * @return array
 *   Default variable values for the provided Site.
 */
function og_sm_variable_get_defaults($site) {
  $items = array();

  $modules = module_implements('og_sm_variable_defaults');
  foreach ($modules as $module) {
    $module_items = call_user_func($module . '_og_sm_variable_defaults', $site);
    if ($module_items) {
      $items = array_merge($items, $module_items);
    }
  }

  drupal_alter('og_sm_variable_defaults', $items, $site);
  return $items;
}

<?php
/**
 * @file
 * All og_sm related hook implementations.
 */

/**
 * Implements hook_og_sm_site_type_add().
 */
function og_sm_path_og_sm_site_type_add($type) {
  // Set the pathauto pattern for the add node type to [node:site-path].
  variable_set(
    'pathauto_node_' . $type . '_pattern',
    '[node:site-path]'
  );
}

/**
 * Implements hook_og_sm_site_type_remove().
 */
function og_sm_path_og_sm_site_type_remove($type) {
  // Restore the pathauto pattern back to the default pattern.
  variable_set(
    'pathauto_node_' . $type . '_pattern',
    'content/[node:type]/[node:title]'
  );
}

/**
 * Implements hook_og_sm_site_insert().
 */
function og_sm_path_og_sm_site_insert($site) {
  // Save the Site path, no need to trigger the hook here.
  if (isset($site->site_path)) {
    og_sm_path_set($site, $site->site_path, FALSE);
  }
}

/**
 * Implements hook_og_sm_site_update().
 */
function og_sm_path_og_sm_site_update($site) {
  // Save the Site path IF the value changed.
  if (isset($site->site_path)) {
    og_sm_path_set($site, $site->site_path);
  }
}

/**
 * Implements hook_og_sm_site_path_change().
 */
function og_sm_path_og_sm_site_path_change($site) {
  // Update all aliases for the Site when its alias changes.
  module_load_include('inc', 'og_sm_path', 'og_sm_path.batch');
  og_sm_path_site_alias_update_batch($site);
}

/**
 * Implements hook_og_sm_site_delete().
 */
function og_sm_path_og_sm_site_delete($site) {
  // Delete all aliases for a site when it is deleted.
  og_sm_path_site_delete_aliases($site);
}

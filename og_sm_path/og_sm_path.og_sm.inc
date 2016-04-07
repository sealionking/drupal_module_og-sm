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



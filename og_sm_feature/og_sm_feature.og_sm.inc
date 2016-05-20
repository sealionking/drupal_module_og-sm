<?php
/**
 * @file
 * Implementation of the og_sm hooks.
 */

/**
 * Implements hook_og_sm_admin_menu().
 */
function og_sm_feature_og_sm_admin_menu() {
  $items = array();

  $items['structure/features'] = array(
    'title' => 'Features',
    'description' => 'Manage Site features.',
    'href' => 'admin/features',
    'weight' => 0,
  );

  // Make items translatable.
  if (FALSE) {
    t('Features');
    t('Manage Site features.');
  }

  return $items;
}

/**
 * Implements hook_og_sm_variable_defaults().
 */
function og_sm_feature_og_sm_variable_defaults($site) {
  $items = array();

  // Add the default features variables.
  $feature_names = array_keys(og_sm_feature_info());
  foreach ($feature_names as $name) {
    $var_key = og_sm_feature_variable_key($name);

    // Skip not enabled features.
    $default = variable_get($var_key, FALSE);
    if (empty($default)) {
      continue;
    }

    $items[$var_key] = $default;
  }

  return $items;
}

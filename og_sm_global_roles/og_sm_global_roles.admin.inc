<?php
/**
 * @file
 * Global roles administration pages.
 */

/**
 * Global roles configuration page.
 *
 * @param array $form
 *   The form array.
 */
function og_sm_global_roles_settings($form) {
  $roles_global = _og_sm_global_roles_settings_global_roles();
  $roles_groups = _og_sm_global_roles_settings_group_roles();

  $checkbox_options = $roles_global;

  foreach ($roles_groups as $role_group) {
    $key = sprintf('og_sm_global_roles_%s', $role_group);
    $args = array('%role' => $role_group);

    $form[$role_group] = array(
      '#type' => 'fieldset',
      '#title' => t('Site role : %role', $args),
      '#description' => t('Select what global roles a user should get within a Site when he gets the Site %role role.', $args),
    );
    $form[$role_group][$key] = array(
      '#type' => 'checkboxes',
      '#options' => $checkbox_options,
      '#default_value' => variable_get($key, array()),
    );
  }

  return system_settings_form($form);
}

/**
 * Helper to get the global user roles.
 *
 * @return array
 *   Global roles keyed by their id.
 */
function _og_sm_global_roles_settings_global_roles() {
  // Get all roles except anonymous.
  $roles_global = user_roles(TRUE);

  // Remove authenticated role.
  if (isset($roles_global[2])) {
    unset($roles_global[2]);
  }

  return $roles_global;
}

/**
 * Helper to get the site user roles.
 *
 * @return array
 *   Group roles keyed by their id.
 */
function _og_sm_global_roles_settings_group_roles() {
  $rows = db_select('og_role', 'ogr')
    ->distinct()
    ->fields('ogr', array('name'))
    ->condition('ogr.group_type', 'node')
    ->condition('ogr.group_bundle', og_sm_get_site_types())
    ->execute();

  $roles = array();
  foreach ($rows as $row) {
    $roles[$row->name] = $row->name;
  }

  ksort($roles);
  return $roles;
}

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
 *
 * @return array
 *   The form structure.
 */
function og_sm_global_roles_settings($form) {
  $roles_global = _og_sm_global_roles_settings_global_roles();
  $roles_groups = _og_sm_global_roles_get_all_site_roles();

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

  $form['#submit'][] = 'og_sm_global_roles_settings_submit_after';

  return system_settings_form($form);
}

/**
 * Clear the mappings cache when the config has changed.
 *
 * @param array $form
 *   The form structure.
 * @param array $form_state
 *   The form state.
 *
 * @see og_sm_global_roles_settings()
 */
function og_sm_global_roles_settings_submit_after(array $form, array $form_state) {
  cache_clear_all('og_sm_global_roles_mappings', 'cache');
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

  // Use role names as array keys (unique id) for feature exports.
  $role_names = array_values($roles_global);
  $roles_global = array_combine($role_names, $role_names);

  return $roles_global;
}

<?php
/**
 * @file
 * Form alters and related callbacks for the Site node forms.
 */

/**
 * Adds the site-path related field and functionality to the Site node forms.
 *
 * @param array $form
 *   The form structure.
 * @param array $form_state
 *   The form state.
 *
 * @see og_sm_pathauto_form_node_form_alter()
 */
function _og_sm_path_form_node_site_form_alter(array &$form, array &$form_state) {
  $site = $form['#node'];

  $default = (!empty($site->nid))
    ? og_sm_variable_get($site->nid, 'path', '')
    : '';

  // Add the Site Path field.
  $form['site_path'] = array(
    '#type' => 'textfield',
    '#maxlength' => 30,
    '#title' => t('Site Path'),
    '#description' => t('Choose a Site path. May contain only lowercase letters, numbers and dashes. e.g. "my-site".'),
    '#default_value' => $default,
    '#required' => TRUE,
    '#element_validate' => array('_og_sm_path_field_site_path_validate'),
    '#field_prefix' => url('<front>', array('absolute' => TRUE)),
  );
}

/**
 * Site Path field validator.
 *
 * Will check if the site path has a valid structure and is not already in use.
 *
 * @param array $element
 *   The element info.
 * @param array $form_state
 *   The current form state.
 * @param array $form
 *   The form structure.
 *
 * @see _og_sm_pathauto_form_node_site_form_alter()
 */
function _og_sm_path_field_site_path_validate($element, &$form_state, $form) {
  // Check if there is already a Site with the same path.
  $path = $element['#value'];

  // Check format.
  if (!preg_match('/^[a-z0-9-]+$/', $path)) {
    form_error($element, t('The Site path may contain only lowercase letters, numbers and dashes.'));
    return;
  }

  // Check if the path is not already used by another Site.
  $site = $form['#node'];
  $paths = og_sm_variable_get_all_sites('path');
  $existing = array_search($path, $paths);
  if ($existing && (empty($site->nid) || (int) $site->nid !== $existing)) {
    $args = array('%site_path' => $path);
    form_error($element, t('The Site path %site_path is already in use.', $args));
    return;
  }
}

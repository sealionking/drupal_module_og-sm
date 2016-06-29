<?php
/**
 * @file
 * Administrative pages for the OG SM Breadcrumb module.
 */

/**
 * Global settings form.
 *
 * @param array $form
 *   The form structure.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   The form structure.
 */
function og_sm_breadcrumb_admin(array $form, array &$form_state) {
  $form['info'] = array(
    '#markup' => t('Default settings for the Breadcrumb feature.'),
    '#prefix' => '<p>',
    '#suffix' => '</p>',
  );

  $defaults = array(
    'show_on_frontpage' => variable_get('og_sm_breadcrumb_show_on_frontpage', 0),
    'force_home' => variable_get('og_sm_breadcrumb_force_home', 1),
    'append_title' => variable_get('og_sm_breadcrumb_append_title', 1),
  );

  return system_settings_form(_og_sm_breadcrumb_admin_form($form, $defaults));
}

/**
 * Site specific settings form.
 *
 * @param array $form
 *   The form structure.
 * @param array $form_state
 *   The form state.
 * @param object $site
 *   The Site object.
 *
 * @return array
 *   The form structure.
 */
function og_sm_breadcrumb_og_admin(array $form, array &$form_state, $site) {
  $sid = $site->nid;

  $form['info'] = array(
    '#markup' => t('Site settings for the Breadcrumb feature.'),
    '#prefix' => '<p>',
    '#suffix' => '</p>',
  );

  $defaults = array(
    'show_on_frontpage' => og_sm_variable_get($sid, 'og_sm_breadcrumb_show_on_frontpage', 0),
    'force_home' => og_sm_variable_get($sid, 'og_sm_breadcrumb_force_home', 1),
    'append_title' => og_sm_variable_get($sid, 'og_sm_breadcrumb_append_title', 1),
  );

  $form = _og_sm_breadcrumb_admin_form($form, $defaults);

  // Append the breadcrumb settings part.
  $form['#submit'][] = 'og_sm_breadcrumb_og_admin_submit';

  return og_sm_variable_settings_form(
    $form,
    $form_state,
    $site
  );
}

/**
 * Shared form elements for the Global & OG settings.
 *
 * @param array $form
 *   The form structure.
 * @param array $defaults
 *   The default values for the form.
 *
 * @return array
 *   The form structure.
 */
function _og_sm_breadcrumb_admin_form(array $form, array $defaults) {
  // Options.
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Options'),
  );
  $form['options']['og_sm_breadcrumb_show_on_frontpage'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show on Site frontpage'),
    '#description' => t('Show breadcrumb on the Site homepage.'),
    '#default_value' => $defaults['show_on_frontpage'],
  );
  $form['options']['og_sm_breadcrumb_force_home'] = array(
    '#type' => 'checkbox',
    '#title' => t('Home link to Site frontpage'),
    '#description' => t('Force the home part of the breadcrumb to link to the Site frontpage.'),
    '#default_value' => $defaults['force_home'],
  );
  $form['options']['og_sm_breadcrumb_append_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Append the page title to the breadcrumb trail'),
    '#description' => t('The page title will be appended to the breadcrumb trail.'),
    '#default_value' => $defaults['append_title'],
  );

  return $form;
}

/**
 * Extra submit handler for og_sm_breadcrumb_og_admin() form.
 *
 * @param array $form
 *   The form structure.
 * @param array $form_state
 *   The current form state.
 *
 * @see og_sm_breadcrumb_og_admin()
 */
function og_sm_breadcrumb_og_admin_submit(array $form, array &$form_state) {
  // Make sure that the Site cache is cleared when the feature settings changes.
  og_sm_site_cache_clear_all($form_state['site']);
}

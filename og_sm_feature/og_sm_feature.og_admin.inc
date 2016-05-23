<?php
/**
 * @file
 * OG Administrative pages for og_sm_feature.
 */

/**
 * Form to get an overview to enable/disable features.
 *
 * @param array $form
 *   The form structure.
 * @param array $form_state
 *   The current form state.
 * @param object $site
 *   The Site node object.
 *
 * @return array
 *   The form structure.
 */
function og_sm_feature_og_admin_overview(array $form, array &$form_state, $site) {
  // Add the site to the form.
  $form_state['site'] = $site;

  // Information above the form.
  $form['info'] = array(
    '#markup' => t('Select the features to use on the Site.'),
    '#prefix' => '<p>',
    '#suffix' => '</p>',
  );

  // Get a list of all available features.
  $features = og_sm_feature_info();
  if (!$features) {
    drupal_set_message(t('No features available on this platform.'), 'warning');
    $form['no_features'] = array(
      '#markup' => t('There are no features available'),
      '#prefix' => '<div class="warning">',
      '#suffix' => '</div>',
    );
    return $form;
  }

  // Features list.
  $options = array();
  $defaults = array();
  foreach ($features as $name => $info) {
    $options[$name] = _og_sm_feature_og_admin_overview_row($site, $info);
    $defaults[$name] = (int) og_sm_feature_site_is_enabled($site, $name);
  }

  // Add the table data to the form.
  $form['features'] = array(
    '#type' => 'tableselect',
    '#header' => array(
      'name' => t('Feature'),
      'config' => NULL,
    ),
    '#options' => $options,
    '#default_value' => $defaults,
    '#multiple' => TRUE,
    '#js_select' => FALSE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Create a feature row for the features overview form.
 *
 * @param object $site
 *   The Site object to create the row for.
 * @param array $info
 *   The feature information.
 *
 * @return array
 *   The row structure.
 */
function _og_sm_feature_og_admin_overview_row($site, array $info) {
  // Create the row data array.
  $row_data = array(
    'feature' => array(
      '#markup' => $info['name'],
      '#prefix' => '<div class="feature"><strong>',
      '#suffix' => '</strong></div>',
    ),
  );
  if (!empty($info['description'])) {
    $row_data['description'] = array(
      '#markup' => $info['description'],
      '#prefix' => '<div class="description">',
      '#suffix' => '</div>',
    );
  }

  // Create the config link (if any).
  $config = NULL;
  if (!empty($info['site configuration'])) {
    $config = l(
      t('Configuration'),
      'group/node/' . $site->nid . '/' . $info['site configuration'],
      array('query' => drupal_get_destination())
    );
  }

  // Return the structure.
  return array(
    'name' => array('data' => $row_data),
    'config' => $config,
  );
}

/**
 * Submit handler for the features overview form.
 *
 * @param array $form
 *   The form structure.
 * @param array $form_state
 *   The form state.
 */
function og_sm_feature_og_admin_overview_submit(array $form, array $form_state) {
  $site = $form_state['site'];
  $features = $form_state['values']['features'];

  foreach ($features as $name => $state) {
    if (empty($state)) {
      og_sm_feature_site_disable($site, $name);
      continue;
    }

    og_sm_feature_site_enable($site, $name);
  }

  drupal_set_message(t('Saved Feature statuses.'));

  // Enable/disabeling the feature requires menu rebuild.
  menu_rebuild();
}

<?php
/**
 * @file
 * Form alters implemented by the og_sm_taxonomy module.
 */

/**
 * Alters the terms administration form by adding the Site titles to the terms.
 *
 * @param array $form
 *   The form structure.
 */
function _og_sm_taxonomy_form_taxonomy_overview_terms_alter_site_names(array &$form) {
  foreach (element_children($form) as $key) {
    if (!preg_match('/^tid\:[0-9]+/', $key)) {
      continue;
    }

    $element = &$form[$key];

    $term = taxonomy_term_load($element['#term']['tid']);
    $site = og_sm_taxonomy_term_get_site($term);
    if (!$site) {
      continue;
    }

    $element['view']['#suffix'] = ' <small>(' . $site->title . ')</small>';
  }
}

/**
 * Alters the confirmation form to order the terms alphabetically.
 *
 * @param array $form
 *   The form structure.
 *
 * @see og_sm_taxonomy_form_taxonomy_overview_terms_alter()
 */
function _og_sm_taxonomy_form_taxonomy_overview_terms_alter_order(&$form) {
  // Update the cancel link target.
  $form['actions']['cancel']['#href'] = current_path();

  $form['site'] = array(
    '#type' => 'value',
    '#value' => og_sm_current_site(),
  );

  // Custom submit handler.
  $form['#submit'] = array(
    'og_sm_taxonomy_form_taxonomy_overview_terms_alter_submit',
  );
}

/**
 * Submit handler so we can overwrite the redirect after term sort confirmation.
 *
 * @param array $form
 *   The form structure.
 * @param array $form_state
 *   The form state.
 *
 * @see _og_sm_taxonomy_form_taxonomy_overview_terms_alter()
 */
function og_sm_taxonomy_form_taxonomy_overview_terms_alter_submit($form, &$form_state) {
  $values = $form_state['values'];
  $site = $values['site'];

  // Custom query to order only the terms of the current Site.
  // Drupal db_update() does not support joins :(.
  $query = <<<EOT
    UPDATE
      {taxonomy_term_data} td
      JOIN {og_membership} ogm ON (td.tid = ogm.etid)
    SET
      td.`weight` = 0
    WHERE
      td.vid = :vid
      AND ogm.gid = :gid
      AND ogm.entity_type = :entity_type 
      AND ogm.group_type = :group_type
EOT;

  db_query($query, array(
    ':vid' => $values['vid'],
    ':gid' => $site->nid,
    ':entity_type' => 'taxonomy_term',
    ':group_type' => 'node',
  ));

  drupal_set_message(t(
    'Reset vocabulary %name to alphabetical order.',
    array('%name' => $form_state['values']['name'])
  ));
  watchdog(
    'taxonomy',
    'Reset vocabulary %name to alphabetical order for Site %site_name.',
    array(
      '%name' => $form_state['values']['name'],
      '%site_name' => $site->title,
    ),
    WATCHDOG_NOTICE
  );

  // Set the proper redirect.
  $form_state['redirect'] = current_path();
}

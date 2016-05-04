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

    $title = drupal_render($element['view']);
    $element['view'] = array(
      '#markup' => $title . ' <small>(' . $site->title . ')</small>',
    );
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

  // Add extra submit handler so we can overwrite the redirect.
  $form['#submit'][] = 'og_sm_taxonomy_form_taxonomy_overview_terms_alter_submit';
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
  $form_state['redirect'] = current_path();
}

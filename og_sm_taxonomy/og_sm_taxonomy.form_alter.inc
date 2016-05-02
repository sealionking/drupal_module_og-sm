<?php
/**
 * @file
 * Form alters implemented by the og_sm_taxonomy module.
 */

/**
 * Alters the confirmation form to order the terms alphabetically.
 *
 * @param array $form
 *   The form structure.
 *
 * @see og_sm_taxonomy_form_taxonomy_overview_terms_alter()
 */
function _og_sm_taxonomy_form_taxonomy_overview_terms_alter(&$form) {
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

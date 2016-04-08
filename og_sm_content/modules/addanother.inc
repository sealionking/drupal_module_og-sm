<?php
/**
 * @file
 * Integration of the og_sm_content module with addanother contrib module.
 */

/**
 * Custom callback to add support for the custom Site content creation paths.
 *
 * Is used as override for the addanother_goto() callback.
 *
 * @param object $node
 *   The node to base the redirect on.
 *
 * @see addanother_goto()
 * @see og_sm_content_menu_alter()
 */
function og_sm_content_addanother_goto($node) {
  $site = og_sm_content_get_site($node);
  if (!$site) {
    drupal_goto('node/add/' . _addanother_node_type_url($node->type));
  }

  drupal_goto(og_sm_content_add_uri($site, $node->type));
}

/**
 * Alter a form with addanother button so it support Site create content URL.
 *
 * @param array $form
 *   The form to alter.
 * @param array $form_state
 *   The form state to alter.
 */
function og_sm_content_form_alter_addanother(&$form, &$form_state) {
  $form['actions']['addanother']['#submit'] = array(
    'node_form_submit',
    'og_sm_content_addanother_node_form_submit',
  );
}

/**
 * Custom submit handler for addanother button.
 *
 * Submit handler for the 'Save and add another' button.
 * This allows a redirect to be set if this was the button pressed.
 *
 * @param array $form
 *   The form that is submitted.
 * @param array $form_state
 *   The current form state.
 *
 * @see addanother_node_form_submit()
 * @see og_sm_content_form_alter()
 */
function og_sm_content_addanother_node_form_submit($form, &$form_state) {
  if ($node = _addanother_get_node_from_form_state($form_state)) {
    _addanother_quelch_message($node);
    theme('addanother_button_message', array('nid' => $node->nid));

    $site = og_sm_content_get_site($node);
    $form_state['redirect'] = ($site)
      ? og_sm_content_add_uri($site, $node->type)
      : _addanother_node_add_path($node);
  }
}

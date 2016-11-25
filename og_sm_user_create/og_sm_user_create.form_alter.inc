<?php

/**
 * @file
 * Form alters implemented for the OG SM User Create module.
 */

/**
 * Adds og roles instead of global roles to the user register form.
 *
 * @param array $form
 *   The form structure.
 * @param array $form_state
 *   The form state.
 *
 * @see og_sm_user_create_form_user_register_form_alter()
 */
function _og_sm_user_create_form_user_register_form_alter(array &$form, array &$form_state) {
  if (!isset($form_state['build_info']['args'][0])) {
    return;
  }
  $site = $form_state['build_info']['args'][0];
  if (!og_sm_is_site($site)) {
    return;
  }

  // Don't allow the global roles to be added from within a Site.
  $form['account']['roles']['#access'] = FALSE;

  $og_roles = og_roles('node', $site->type, $site->nid, FALSE, FALSE);
  if ($og_roles) {
    $form['account']['og_roles'] = array(
      '#type' => 'checkboxes',
      '#options' => $og_roles,
      '#title' => t('Roles'),
    );
  }

  $form['#submit'][] = 'og_sm_user_create_user_create_submit';
}

/**
 * Submit handler for the user create form within a site context.
 *
 * This submit handler runs after a user account has been created.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The current form state.
 */
function og_sm_user_create_user_create_submit(array $form, array &$form_state) {
  $account = $form_state['user'];
  $site = $form_state['build_info']['args'][0];
  $group_type = 'node';
  $sid = $site->nid;

  $field_names = og_get_group_audience_fields('user', 'user', $group_type, $site->type);
  $membership = og_membership_create($group_type, $sid, 'user', $account->uid, key($field_names));
  $membership->save();

  if (!empty($form_state['values']['roles'])) {
    foreach ($form_state['values']['roles'] as $rid) {
      og_role_grant($group_type, $sid, $membership->etid, $rid);
    }
  }

  drupal_set_message(t('%user has been added to the group %group-title.', array('%user' => format_username($account), '%group-title' => $site->title)));
}

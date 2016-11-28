<?php

/**
 * @file
 * Form alters implemented for the OG SM User Create module.
 */

/**
 * Form definition of the user create form.
 *
 * @param array $form
 *   The form structure.
 * @param array $form_state
 *   The form state.
 * @param object $site
 *   The site node.
 *
 * @return array
 *   The form definition.
 */
function og_sm_user_create_register_form($form, &$form_state, $site) {
  global $user;

  // Since user_register_form does several checks on the 'administer users'
  // permission we are overriding the static user_access cache here and setting
  // 'administer users' to TRUE, this allows users with elevated site roles but
  // without elevated global roles to access the user_register_form properly.
  $static = &drupal_static('user_access');
  $static[$user->uid]['administer users'] = TRUE;

  $form = user_register_form($form, $form_state);

  $form['administer_users'] = array(
    '#type' => 'value',
    '#value' => TRUE,
  );

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

  $form['#submit'][] = 'og_sm_user_create_user_add_membership';

  return $form;
}

/**
 * Submit handler for the user create form within a site context.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The current form state.
 */
function og_sm_user_create_user_add_membership(array $form, array &$form_state) {
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

<?php
/**
 * @file
 * Pages for the og_sm_profile module.
 */

/**
 * The site user profile page.
 *
 * @param object $site
 *   The site node.
 *
 * @return array
 *   Renderable array of profile data.
 */
function og_sm_profile_page($site) {
  global $user;

  $path = array(
    l(og_sm_profile_page_title($site), 'node/' . $site->nid . '/profile'),
  );
  og_set_breadcrumb('node', $site->nid, $path);

  $profile = og_sm_profile_load_from_context(NULL, FALSE);

  // Allow other modules to add extra elements.
  $sections = module_invoke_all('og_sm_profile_view', $profile);
  // Allow other modules to alter the elements.
  drupal_alter('og_sm_profile_view', $sections, $profile);

  return array(
    '#theme' => 'og_sm_profile_page',
    '#name' => $user->name,
    '#email' => $user->mail,
    '#sections' => $sections,
  );
}

/**
 * Base profile form.
 *
 * @param array $form
 *   The form structure.
 * @param array $form_state
 *   The current form state.
 * @param object $site
 *   The site node.
 *
 * @return array
 *   The form structure.
 */
function og_sm_profile_edit_form($form, &$form_state, $site) {
  // Breadcrumbs.
  $context = og_context();
  og_set_breadcrumb('node', $context['gid'], array(
    l(og_sm_profile_page_title($context['gid']), 'node/' . $context['gid'] . '/profile'),
    l(t('Edit'), 'node/' . $context['gid'] . '/profile/modify'),
  ));

  $form['#prefix'] = '<div class="l-primary">';
  $form['#suffix'] = '</div>';

  $profile = og_sm_profile_load_from_context();
  $form_state['profile'] = $profile;

  // Every module with profile data should alter this form and add their own
  // elements with own validate and submit handlers.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 100,
  );
  return $form;
}

/**
 * Submit handler for the profile form.
 *
 * @param array $form
 *   The form structure.
 * @param array $form_state
 *   The current form state.
 */
function og_sm_profile_edit_form_submit($form, &$form_state) {
  $profile = $form_state['profile'];
  cache_clear_all($profile->uid . ':' . $profile->group_name, OG_SM_PROFILE_CACHE_BIN);

  drupal_set_message(t('Your profile has been saved'));
}

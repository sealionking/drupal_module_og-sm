<?php
/**
 * @file
 * Pages for the og_sm_profile module.
 */

/**
 * Returns sections info to build the user profile page.
 *
 * @return array
 *   An array of section info arrays, each section info array can contain the
 *   following attributes:
 *   - "render callback": The function to call to display the section on the
 *     profile page.
 *   - "weight": (optional) The weight of the section.
 */
function og_sm_profile_get_sections_info() {
  // Check if we already cached the information.
  $cache = cache_get(__FUNCTION__);
  if ($cache) {
    return $cache->data;
  }

  $sections_info = module_invoke_all('og_sm_profile_view');
  drupal_alter('og_sm_profile_view', $sections_info);
  uasort($sections_info, 'drupal_sort_weight');

  // Store in cache.
  cache_set(__FUNCTION__, $sections_info);

  // Return data.
  return $sections_info;
}

/**
 * The site user profile page.
 *
 * @param object $site
 *   The site node.
 * @param object $account
 *   (optional) The user object.
 *
 * @return array
 *   Renderable array of profile data.
 */
function og_sm_profile_page($site, $account = NULL) {
  if (!isset($account)) {
    global $user;
    $account = $user;
  }

  $path = array(
    l(og_sm_profile_page_title($site), 'node/' . $site->nid . '/profile'),
  );
  og_set_breadcrumb('node', $site->nid, $path);

  $profile = og_sm_profile_load_from_context($account->uid, FALSE);
  $sections_info = og_sm_profile_get_sections_info();

  $sections = array();
  foreach ($sections_info as $section_info) {
    if (!isset($section_info['render callback'])) {
      continue;
    }
    $render_callback = $section_info['render callback'];
    if (!function_exists($render_callback)) {
      continue;
    }
    $sections[] = call_user_func($render_callback, $profile);
  }

  return array(
    '#theme' => 'og_sm_profile_page',
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

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
 * @param object $profile
 *   (optional) The site profile object.
 *
 * @return array
 *   Renderable array of profile data.
 */
function og_sm_profile_page($profile = NULL) {
  if (!isset($profile)) {
    $profile = og_sm_profile_load_from_context(NULL, FALSE);
  }
  $site = node_load($profile->site_nid);

  $path = array(
    l(og_sm_profile_page_title($profile), 'node/' . $site->nid . '/profile'),
  );
  og_set_breadcrumb('node', $site->nid, $path);

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
    '#profile' => $profile,
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
 * @param object $profile
 *   The site profile pbject.
 *
 * @return array
 *   The form structure.
 */
function og_sm_profile_edit_form($form, &$form_state, $profile = NULL) {
  if (!isset($profile)) {
    $profile = og_sm_profile_load_from_context();
  }
  $site = og_sm_site_load($profile->site_nid);
  if (!$site) {
    return array();
  }

  // Breadcrumbs.
  og_set_breadcrumb('node', $site->nid, array(
    l(og_sm_profile_page_title($profile), 'node/' . $site->nid . '/profile'),
    l(t('Edit'), 'node/' . $site->nid . '/profile/modify'),
  ));

  $form['#prefix'] = '<div class="l-primary">';
  $form['#suffix'] = '</div>';

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
  cache_clear_all($profile->uid . ':' . $profile->site_nid, OG_SM_PROFILE_CACHE_BIN);

  drupal_set_message(t('Your profile has been saved'));
}

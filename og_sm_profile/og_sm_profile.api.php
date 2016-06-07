<?php
/**
 * @file
 * API documentation about the og_sm_profile module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Defines user profile sections to be displayed on the profile page.
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param object $profile
 *   The site user profile.
 *
 * @return array
 *   Array of sections, with the section machine name as key. Possible
 *   attributes:
 *   - "label": (optional) The label of the section.
 *   - "elements": An array of renderable arrays to be displayed under the
 *   section.
 *   - "weight":
 *
 * @see og_sm_profile_page()
 */
function hook_og_sm_profile_view($profile) {
  // @todo: Add example.
  return array();
}

/**
 * Alters user profile sections defined by hook_og_sm_profile_view().
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param array $output
 *   An associative array containing sections to be displayed on the profile
 *   page.
 * @param object $profile
 *   The site user profile.
 *
 * @see og_sm_profile_page()
 */
function hook_og_sm_profile_view_alter(&$output, $profile) {
  // @todo: Add example.
}

/**
 * @} End of "addtogroup hooks".
 */

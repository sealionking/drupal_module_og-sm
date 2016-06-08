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
 * @return array
 *   Array of section ifo, with the section machine name as key. Possible
 *   attributes:
 *   - "render callback": The function to call to display the section on the
 *     profile page.
 *   - "weight": (optional) The weight of the section.
 *
 * @see og_sm_profile_page()
 */
function hook_og_sm_profile_view() {
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
 * @param array $sections
 *   An associative array containing sections to be displayed on the profile
 *   page.
 *
 * @see og_sm_profile_page()
 */
function hook_og_sm_profile_view_alter(&$sections) {
  // @todo: Add example.
}

/**
 * @} End of "addtogroup hooks".
 */

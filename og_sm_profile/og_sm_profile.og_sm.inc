<?php
/**
 * @file
 * Site Manager (og_sm) related hooks.
 */

/**
 * Implements hook_og_sm_profile_view().
 */
function og_sm_profile_og_sm_profile_view() {
  return array(
    'basic_info' => array(
      'render callback' => 'og_sm_profile_section_basic_info',
    ),
  );
}

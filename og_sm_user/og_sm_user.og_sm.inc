<?php
/**
 * @file
 * Site Manager (og_sm) related hooks.
 */

/**
 * Implements hook_og_sm_user_view().
 */
function og_sm_user_og_sm_user_view() {
  return array(
    'basic_info' => array(
      'render callback' => 'og_sm_user_section_basic_info',
      'weight' => -10,
    ),
  );
}

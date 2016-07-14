<?php
/**
 * @file
 * Hooks implemented to test the Site Clone functionality.
 */

/**
 * Implements hook_og_sm_site_clone_prepare_alter().
 */
function og_sm_site_clone_test_og_sm_site_clone_prepare_alter(&$site_new, array $context) {
  // Set the new title based on original site prefixed with "Clone of".
  $site_original = $context['site_original'];
  $site_new->extra_field_to_test = sprintf('Test Hook %d', $site_original->nid);
}

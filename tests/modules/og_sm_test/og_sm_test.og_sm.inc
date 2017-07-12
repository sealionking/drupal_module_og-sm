<?php

/**
 * @file
 * Hooks implemented to test the OG SM functionality.
 */

/**
 * Implements hook_og_sm_site_homepage_alter().
 */
function og_sm_test_og_sm_site_homepage_alter(&$path, $site) {
  $path = 'group/node/' . $site->nid . '/dashboard';
}

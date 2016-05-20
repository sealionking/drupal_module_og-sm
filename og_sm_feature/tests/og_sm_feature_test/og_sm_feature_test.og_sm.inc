<?php
/**
 * @file
 * Hooks implemented to test the Variable defaults functionality.
 */

/**
 * Implements hook_og_sm_feature_info().
 */
function og_sm_feature_test_og_sm_feature_info() {
  $items = array();

  $items['news'] = array(
    'name' => 'News',
    'description' => 'News content and overviews.',
    'global configuration' => 'admin/config/group/features/news',
    'site configuration' => 'admin/features/news',
    'default status' => FALSE,
  );
  $items['articles'] = array(
    'name' => 'Articles',
  );

  return $items;
}

/**
 * Implements hook_og_sm_feature_info_alter().
 */
function og_sm_feature_test_og_sm_feature_info_alter(&$info) {
  $info['news']['global configuration'] = 'admin/config/group/features/news-test';
  $info['news']['site configuration'] = 'admin/features/news-test';
  $info['news']['default status'] = TRUE;
}

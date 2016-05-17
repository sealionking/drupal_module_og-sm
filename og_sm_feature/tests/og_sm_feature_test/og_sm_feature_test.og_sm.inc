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
    'title' => 'News',
    'description' => 'News content and overviews.',
    'configuration' => 'admin/feature/news',
    'default status' => TRUE,
  );

  return $items;
}

/**
 * Implements hook_og_sm_feature_info_alter().
 */
function og_sm_feature_test_og_sm_feature_info_alter(&$info) {
  $info['news']['configuration'] = 'admin/feature/news-test';
  $info['news']['default status'] = FALSE;
}

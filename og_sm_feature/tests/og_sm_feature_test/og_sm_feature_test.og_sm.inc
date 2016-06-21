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
    'name' => t('News'),
    'description' => t('News content and overviews.'),
    'content types' => array('news'),
    'global configuration' => 'admin/config/group/features/news',
    'site configuration' => 'admin/features/news',
  );
  $items['articles'] = array(
    'name' => t('Articles'),
  );
  $items['news and blogs'] = array(
    'name' => t('News and Blogs'),
    'content types' => array('news', 'blog_post'),
  );

  return $items;
}

/**
 * Implements hook_og_sm_feature_info_alter().
 */
function og_sm_feature_test_og_sm_feature_info_alter(&$info) {
  $info['news']['global configuration'] = 'admin/config/group/features/news-test';
  $info['news']['site configuration'] = 'admin/features/news-test';
}

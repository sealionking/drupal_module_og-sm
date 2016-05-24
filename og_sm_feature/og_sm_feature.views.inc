<?php
/**
 * @file
 * Implemented views plugins.
 */

/**
 * Implements hook_views_plugins().
 */
function og_sm_feature_views_plugins() {
  $plugins = array(
    'access' => array(
      'og_sm_feature' => array(
        'title' => t('OG SM Feature'),
        'help' => t('Checks access based on the status of a feature.'),
        'handler' => 'OgSmFeatureViewsAccess',
        'uses options' => TRUE,
      ),
    ),
  );
  return $plugins;
}

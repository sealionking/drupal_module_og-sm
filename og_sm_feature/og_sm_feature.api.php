<?php
/**
 * @file
 * API documentation about the og_sm_feature module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Inform the platform about the available feature(s).
 *
 * @return array
 *   Array containing the information about the feature(s).
 *   The Array has following content:
 *   - title : The feature title.
 *   - description : The feature description.
 *   - global configuration : An optional path to the a configuration page to
 *     set the global defaults for a feature.
 *   - site configuration : An optional path to change the configuration of the
 *     feature specific for the Site. The path should be specified without the
 *     group/node/NID/ path prefix as it will be appended automatically.
 */
function hook_og_sm_feature_info() {
  $items = array();

  $items['news'] = array(
    'name' => t('News'),
    'description' => t('News content and overviews.'),
    'global configuration' => 'admin/config/group/features/news',
    'site configuration' => 'admin/features/news',
  );
  $items['articles'] = array(
    'name' => 'Articles',
  );

  return $items;
}

/**
 * Alter the features information as collected by hook_og_sm_feature_info().
 *
 * @param array $info
 *   The information collected by the hook_og_sm_feature_info() hook.
 */
function hook_og_sm_feature_info_alter(&$info) {
  $info['news']['site configuration'] = 'admin/feature/news-test';
  $info['news']['default status'] = FALSE;
}

/**
 * @} End of "addtogroup hooks".
 */

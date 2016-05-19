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
 *   - title : The feature title. Do not translate the title, this will be done
 *     by the og_sm_feature module.
 *   - description : The feature description. Do not translate the description,
 *     this will be done by the og_sm_feature module.
 *   - configuration : An optional path to change the configuration of the
 *     feature specific for the Site. The path should be specified without the
 *     group/node/NID/ path prefix as it is appended automatically.
 *   - default status : The default enabled status (TRUE/FALSE) of a feature
 *     when a new Site is created.
 */
function hook_og_sm_feature_info() {
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
 * Alter the features information as collected by hook_og_sm_feature_info().
 *
 * @param array $info
 *   The information collected by the hook_og_sm_feature_info() hook.
 */
function hook_og_sm_feature_info_alter(&$info) {
  $info['news']['configuration'] = 'admin/feature/news-test';
  $info['news']['default status'] = FALSE;
}

/**
 * @} End of "addtogroup hooks".
 */

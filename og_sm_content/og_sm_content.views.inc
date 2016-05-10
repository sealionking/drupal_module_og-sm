<?php
/**
 * @file
 * Views plugins & hooks.
 */

/**
 * Implements hook_views_data_alter().
 */
function og_sm_content_views_data_alter(&$data) {
  $data['node']['og_sm_content_type'] = array(
    'title' => t('Site content types'),
    'help' => t('Content types that can be used to create content within a Site.'),
    'filter' => array(
      'handler' => 'ogSmContentViewsHandlerFilterContentType',
      'field' => 'type',
    ),
  );
  $data['node']['type']['field']['handler'] = 'ogSmContentViewsHandlerFieldContentType';
}

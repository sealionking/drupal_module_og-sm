<?php

/**
 * @file
 * Views plugins & hooks.
 */

/**
 * Implements hook_views_data_alter().
 */
function og_sm_views_data_alter(&$data) {
  $data['og_membership']['og_sm_sites'] = array(
    'title' => t('Site'),
    'help' => t('Filter on the site linked to the entity.'),
    'filter' => array(
      'handler' => 'og_sm_views_handler_filter_sites',
      'field' => 'gid',
    ),
  );
  $data['og_membership']['og_sm_manageable_sites_by_current_user'] = array(
    'title' => t('Manageable sites by current user'),
    'help' => t('Filter on all sites the current user can manage.'),
    'filter' => array(
      'handler' => 'og_sm_views_handler_filter_manageable_sites_by_current_user',
      'field' => 'gid',
      'type' => 'yes-no',
    ),
  );
}

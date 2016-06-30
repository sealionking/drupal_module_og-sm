<?php
/**
 * @file
 * Implemented og_sm hooks.
 */

/**
 * Implements hook_og_sm_feature_info().
 */
function og_sm_breadcrumb_og_sm_feature_info() {
  $items = array();

  $items[OG_SM_BREADCUMB_FEATURE] = array(
    'name' => t('Breadcrumb'),
    'description' => t('Show customizable breadcrumb.'),
    'global configuration' => 'admin/config/group/features/breadcrumb',
    'site configuration' => 'admin/features/breadcrumb',
  );

  return $items;
}

/**
 * Implements hook_og_sm_variable_defaults().
 */
function og_sm_breadcrumb_og_sm_variable_defaults($site) {
  $items = array();

  // Enabled Site breadcrumb trail.
  $items['og_sm_breadcrumb_hide_on_frontpage'] = variable_get('og_sm_breadcrumb_hide_on_frontpage', 1);
  $items['og_sm_breadcrumb_force_home'] = variable_get('og_sm_breadcrumb_force_home', 1);
  $items['og_sm_breadcrumb_append_title'] = variable_get('og_sm_breadcrumb_append_title', 1);

  return $items;
}

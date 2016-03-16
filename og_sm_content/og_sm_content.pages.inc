<?php
/**
 * @file
 * Administration pages for the og_sm_content module.
 */

/**
 * Site content overview.
 *
 * @param object $site
 *   The Site node.
 *
 * @return string
 *   The page content.
 */
function og_sm_content_admin_overview($site) {
  //og_set_breadcrumb('node', $site->nid, array(l(t('Group'), "node/$site->nid/group")));

  $view = views_get_view('og_sm_content_admin_overview');
  $view->set_display('embed_overview');
  $view->set_arguments(array($site->nid));
  $view->override_path = 'group/node/' . $site->nid . '/admin/content';

  return $view->preview();
}

/**
 * Site content overview owned by the current user.
 *
 * @param object $site
 *   The Site node.
 *
 * @return string
 *   The page content.
 */
function og_sm_content_admin_overview_my($site) {
  //og_set_breadcrumb('node', $site->nid, array(l(t('Group'), "node/$site->nid/group")));

  $view = views_get_view('og_sm_content_admin_overview');
  $view->set_display('embed_overview_my');
  $view->set_arguments(array($site->nid));
  $view->override_path = 'group/node/' . $site->nid . '/admin/content';

  return $view->preview();
}

/**
 * Admin add content menu callback.
 *
 * Will redirect to group/node/nid/content/add.
 *
 * @param object $site
 *   The Site node.
 */
function og_sm_content_admin_add_content($site) {
  drupal_goto('group/node/' . $site->nid . '/content/add');
}

/**
 * Add Site content overview menu callback.
 *
 * @param object $site
 *   The Site node.
 *
 * @return string
 *   The page content.
 */
function og_sm_content_add_overview($site) {
  og_set_breadcrumb('node', $site->nid, array(l(t('Group'), "node/$site->nid/group")));

  $options = array();
  $base_path = 'group/node/' . $site->nid . '/content/add/';

  $types = og_sm_content_get_types_by_site($site);
  foreach ($types as $type) {
    $options[$type->name] = l($type->name, $base_path . $type->type);
  }
  ksort($options);

  return theme('item_list', array('items' => $options));
}

/**
 * Add Site content item menu callback.
 *
 * @param object $site
 *   The Site node.
 * @param string $node_type
 *   The node type to add.
 *
 * @return string
 *   The page content.
 */
function og_sm_content_add_content($site, $node_type) {
  og_set_breadcrumb('node', $site->nid, array(l(t('Group'), "node/$site->nid/group")));

  return $site->title . ' : ' . $node_type;
}

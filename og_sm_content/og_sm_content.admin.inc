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
  $parent = 'group/node/' . $site->nid . '/admin';
  og_sm_set_breadcrumb($site, array(l(t('Administer Site'), $parent)));

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
  $parent = 'group/node/' . $site->nid . '/admin';
  og_sm_set_breadcrumb($site, array(l(t('Administer Site'), $parent)));

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

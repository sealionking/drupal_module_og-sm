<?php
/**
 * @file
 * Administration pages for the og_sm_comment module.
 */

/**
 * Admin content page callback.
 *
 * @param object $site
 *   The site node.
 *
 * @return string
 *   Then rendered comment overview view.
 */
function og_sm_comment_admin_overview($site) {
  og_sm_set_breadcrumb($site);

  $view = views_get_view('pp_admin_comments');
  $view->set_display('default');
  $view->set_arguments(array($site->nid));
  $view->override_path = 'group/node/' . $site->nid . '/admin/comments';

  return $view->preview();
}

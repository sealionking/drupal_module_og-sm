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
  $types = og_sm_content_get_types_by_site($site);

  // Redirect to the content type if the user has access to only 1 type.
  if (count($types) === 1) {
    $type = array_shift($types);
    drupal_goto(og_sm_content_add_uri($site, $type->type));
  }

  og_sm_set_breadcrumb($site);

  // Show list of node types the user can create.
  $options = array();
  foreach ($types as $type) {
    $options[$type->name] = array(
      'title' => $type->name,
      'description' => $type->description,
      'href' => og_sm_content_add_uri($site, $type->type),
      'localized_options' => array(),
    );
  }
  ksort($options);

  return theme('node_add_list', array('content' => $options));
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
 *   The content creation form.
 */
function og_sm_content_add_content($site, $node_type) {
  $parent = 'group/node/' . $site->nid . '/content/add';
  og_sm_set_breadcrumb($site, array(l(t('Create content'), $parent)));

  // Set the Site reference.
  $_GET['og_group_ref'] = $site->nid;

  module_load_include('inc', 'node', 'node.pages');
  return node_add($node_type);
}

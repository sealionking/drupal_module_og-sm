<?php
/**
 * @file
 * Pages for the og_sm_content module.
 */

// We need to include the node.pages.inc file to support ajax callbacks.
module_load_include('inc', 'node', 'node.pages');


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
    // Check if user has access to create new content.
    $path = og_sm_content_add_uri($site, $type->type);
    if (!drupal_valid_path($path)) {
      continue;
    }

    $options[$type->type] = array(
      'title' => filter_xss($type->name),
      'description' => $type->description,
      'href' => $path,
      'localized_options' => array(),
    );
  }

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
  og_sm_set_breadcrumb($site, array(l(t('Add content'), $parent)));

  // Set the Site reference.
  $_GET['og_group_ref'] = $site->nid;
  return node_add($node_type);
}

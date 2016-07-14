<?php
/**
 * @file
 * Page callbacks and their helpers.
 */

/**
 * Page callback to redirect the clone tab to the node/clone/* URL.
 *
 * @param object $site_original
 *   The node to clone.
 */
function og_sm_site_clone_node_redirect($site_original) {
  drupal_goto('node/clone/' . $site_original->nid);
}

/**
 * Page callback to render the clone form.
 *
 * @param object $site_original
 *   The site to clone from.
 *
 * @return array
 *   The node form.
 */
function og_sm_site_clone_node_form($site_original) {
  drupal_set_title(t('Clone @site', array('@site' => $site_original->title)));

  // Create the new Site object based on the existing.
  $site_new = og_sm_site_clone_prepare($site_original);

  // Create the default form state and add the original site to it.
  $form_state = array();
  $form_state['build_info']['args'] = array($site_new);
  $form_state['site_original'] = $site_original;

  // Make sure the file defining the node form is loaded.
  form_load_include($form_state, 'inc', 'node', 'node.pages');

  // Build the node form based on the new Site.
  return drupal_build_form($site_new->type . '_node_form', $form_state);
}

/**
 * Prepares a node to be cloned.
 *
 * Code based on node_clone module (https://www.drupal.org/project/node_clone).
 *
 * @param object $site_original
 *   The Site node to create the clone for.
 * @param object $account
 *   The owner of the new Site.
 *
 * @return object
 *   The new node object (not saved).
 */
function og_sm_site_clone_prepare($site_original, $account = NULL) {
  $site_new = clone $site_original;

  // Fallback to current user.
  if (!isset($account->uid)) {
    $account = $GLOBALS['user'];
  }

  // Anonymous users don't have a name.
  // @see: drupal_anonymous_user().
  $site_new->name = isset($account->name) ? $account->name : NULL;
  $site_new->uid = (int) $account->uid;

  // Clear values that are filled in automatically for new nodes.
  $site_new->title = NULL;
  $site_new->nid = NULL;
  $site_new->tnid = NULL;
  $site_new->log = NULL;
  $site_new->created = NULL;
  $site_new->changed = NULL;
  $site_new->path = NULL;
  $site_new->files = array();
  $site_new->menu = NULL;

  // By default not published.
  $site_new->status = 0;

  // Revisions.
  $site_new->vid = NULL;
  $site_new->revision_timestamp = NULL;
  $site_new->revision_uid = (int) $site_new->uid;

  // Also handle modules that attach a UUID to the node.
  $site_new->uuid = NULL;
  $site_new->vuuid = NULL;

  // Support comments.
  $site_new->last_comment_timestamp = NULL;
  $site_new->last_comment_name = NULL;
  $site_new->last_comment_uid = NULL;
  $site_new->comment_count = 0;

  // Support Sites that are part of book structure.
  if (isset($site_new->book['mlid'])) {
    $site_new->book['mlid'] = NULL;
    $site_new->book['has_children'] = 0;
  }

  // Inform other modules that this is a clone.
  $site_new->site_is_clone = TRUE;

  // Add the original Site Node ID as property.
  $site_new->site_is_clone_of_nid = (int) $site_original->nid;

  // Allow other modules to alter the prepared node.
  $context = array('site_original' => $site_original);
  drupal_alter('og_sm_site_clone_prepare', $site_new, $context);

  return $site_new;
}

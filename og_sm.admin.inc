<?php

/**
 * @file
 * Admin pages & functionality.
 */

/**
 * Page callback for group/node/%og_sm_site/admin/site-edit.
 *
 * Redirects to the node/%nid/edit URL.
 *
 * @param object $site
 *   The Site node to edit.
 */
function og_sm_admin_site_edit($site) {
  drupal_goto('node/' . $site->nid . '/edit');
}

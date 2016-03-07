<?php
/**
 * @file
 * Page callbacks.
 */

/**
 * Page callback to show the overview of all possible admin tasks.
 *
 * @param int $site_nid
 *   The Site Node ID to build the overview for.
 */
function og_sm_admin_overview_all($site_nid) {
  $site = og_sm_site_load($site_nid);

  return 'Site : ' . $site->title;
}

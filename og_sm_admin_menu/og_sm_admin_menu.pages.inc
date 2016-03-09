<?php
/**
 * @file
 * Page callbacks.
 */

/**
 * Placeholder for dynamic menu items.
 */
function og_sm_admin_menu_placeholder($token) {
  return $token;
}

/**
 * Build an overview page of all Administration tasks.
 *
 * @param object $site
 *   The Site node.
 * @param string $part
 *   (optional) The part of the items that should be listed.
 *   All will be listed if no part is given.
 *
 * @return string
 *   The rendered output.
 */
function og_sm_admin_menu_overview($site, $part = NULL) {
  return $site->title . ' : ' . $part;
}

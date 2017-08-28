<?php

/**
 * @file
 * Hooks provided by the og_sm_admin_menu module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Alters all the site menu links discovered by the menu link plugin manager.
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param array $links
 *   The link definitions to be altered.
 */
function hook_og_sm_site_menu_links_discovered_alter(array &$links) {

}

/**
 * @} End of "addtogroup hooks".
 */

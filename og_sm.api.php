<?php
/**
 * @file
 * API documentation about the og_sm module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Act when a node type is added to the list of Site node type.
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param string $type
 *   The node type machine name.
 *
 * @see og_sm_site_type_add()
 */
function hook_og_sm_site_type_add($type) {

}

/**
 * Act when a node type is removed from the list of Site node types.
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param string $type
 *   The node type machine name.
 *
 * @see og_sm_site_type_remove()
 */
function hook_og_sm_site_type_remove($type) {

}

/**
 * Act when the og_sm_site_cache_clear() function is called.
 *
 * That function does not clear the cache itself, it calls all the implemented
 * hook_og_sm_site_cache_clear_all() hooks so modules can clear their specific
 * cached Site parts.
 *
 * @param object $site
 *   The Site node to clear the cache for.
 *
 * @see og_sm_site_cache_clear_all()
 */
function hook_og_sm_site_cache_clear_all($site) {

}

/**
 * Act on a Site node being viewed.
 *
 * Will only be triggered when the node_view hook is triggered for a node type
 * that is a Site type.
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param object $site
 *   The Site node object.
 * @param string $view_mode
 *   The view mode for the Site node.
 * @param string $langcode
 *   The language code.
 *
 * @see hook_node_view()
 */
function hook_og_sm_site_view($site, $view_mode, $langcode) {

}

/**
 * Act on a Site node being inserted or updated.
 *
 * Will only be triggered when the node_presave hook is triggered for a node
 * type that is a Site type.
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param object $site
 *   The Site node object.
 *
 * @see hook_node_presave()
 */
function hook_og_sm_site_presave($site) {

}

/**
 * Act on a Site node about to be shown on the add/edit form.
 *
 * Will only be triggered when the node_prepare hook is triggered for a node
 * type that is a Site type.
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param object $site
 *   The Site node object.
 *
 * @see hook_node_prepare()
 */
function hook_og_sm_site_prepare($site) {

}

/**
 * Act on a Site node being inserted.
 *
 * Will only be triggered when the node_insert hook is triggered for a node type
 * that is a Site type.
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param object $site
 *   The Site node object.
 *
 * @see hook_node_insert()
 */
function hook_og_sm_site_insert($site) {

}

/**
 * Act on a Site node being updated.
 *
 * Will only be triggered when the node_update hook is triggered for a node type
 * that is a Site type.
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param object $site
 *   The Site node object.
 *
 * @see hook_node_update()
 */
function hook_og_sm_site_update($site) {

}

/**
 * Act on a Site node being saved.
 *
 * Will be triggered after a node is inserted or updated. It will always be
 * called after all the hook_site_insert/update hooks are processed.
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param object $site
 *   The Site node object.
 *
 * @see hook_node_insert()
 * @see hook_node_update()
 */
function hook_og_sm_site_save($site) {

}

/**
 * Act on a Site node being deleted.
 *
 * Will only be triggered when the node_delete hook is triggered for a node type
 * that is a Site type.
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param object $site
 *   The Site node object.
 *
 * @see hook_node_delete()
 */
function hook_og_sm_site_delete($site) {

}

/**
 * Act on a Site node after it is being inserted in the database.
 *
 * This allows modules to interact with Sites after the insert queries are
 * stored in the database (after database transaction commit).
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param object $site
 *   The Site node object.
 *
 * @see hook_node_insert()
 */
function hook_og_sm_site_post_insert($site) {

}

/**
 * Act on a Site node after it is being updated in the database.
 *
 * This allows modules to interact with Sites after the update queries are
 * stored in the database (after database transaction commit).
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param object $site
 *   The Site node object.
 *
 * @see hook_node_update()
 */
function hook_og_sm_site_post_update($site) {

}

/**
 * Act on a Site node after it is being inserted of updated in the database.
 *
 * This allows modules to interact with Sites after the insert/update queries
 * are stored in the database (after database transaction commit).
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param object $site
 *   The Site node object.
 *
 * @see hook_node_post_insert()
 * @see hook_node_post_update()
 * @see hook_node_save()
 */
function hook_og_sm_site_post_save($site) {

}

/**
 * Act on a Site node after it is being deleted from the database.
 *
 * This allows modules to interact with Sites after the delete queries are
 * performend on the database (after database transaction commit).
 *
 * The hook can be put in the yourmodule.module OR in the yourmodule.og_sm.inc
 * file. The recommended place is in the yourmodule.og_sm.inc file as it keeps
 * your .module file cleaner and makes the platform load less code by default.
 *
 * @param object $site
 *   The Site node object.
 *
 * @see hook_node_delete()
 */
function hook_og_sm_site_post_delete($site) {

}

/**
 * Alter the Site homepage path.
 *
 * The og_sm_site_homepage() function creates and returns the path (as string)
 * to the frontpage (homepage) of a Site. That homepage is by default the Site
 * node detail page (node/[site-nid]).
 *
 * Implementations can require that the homepage links to a different page (eg.
 * group/node/NID/dashboard).
 *
 * This alter function allows modules to alter that path.
 *
 * @param string $path
 *   The current path to the Site homepage.
 * @param object $site
 *   The Site object to alter the homepage path for.
 */
function hook_og_sm_site_homepage_alter(&$path, $site) {
  $path = 'group/node/' . $site->nid . '/dashboard';
}

/**
 * Alter the platform administration page path.
 *
 * The og_sm_platform_administration_page() function creates and returns the
 * path (as string) to the platform adminstration page.
 *
 * Implementations can require that the page links to a different page (eg.
 * admin/dashboard).
 *
 * This alter function allows modules to alter that path.
 *
 * @param string $path
 *   The current path to the Site homepage.
 */
function hook_og_sm_platform_administration_page_alter(&$path) {
  $path = 'admin/dashboard';
}

/**
 * @} End of "addtogroup hooks".
 */

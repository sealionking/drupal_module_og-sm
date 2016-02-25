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
 * Act on a Site node being viewed.
 *
 * Will only be triggered when the node_view hook is triggered for a node type
 * that is a Site type.
 *
 * @param object $site
 *   The Site node object.
 * @param string $view_mode
 *   The view mode for the Site node.
 * @param string $langcode
 *   The language code.
 */
function hook_og_sm_site_view($site, $view_mode, $langcode) {

}

/**
 * Act on a Site node being inserted or updated.
 *
 * Will only be triggered when the node_presave hook is triggered for a node
 * type that is a Site type.
 *
 * @param object $site
 *   The Site node object.
 */
function hook_og_sm_site_presave($site) {

}

/**
 * Act on a Site node about to be shown on the add/edit form.
 *
 * Will only be triggered when the node_prepare hook is triggered for a node
 * type that is a Site type.
 *
 * @param object $site
 *   The Site node object.
 */
function hook_og_sm_site_prepare($site) {

}

/**
 * Act on a Site node being inserted.
 *
 * Will only be triggered when the node_insert hook is triggered for a node type
 * that is a Site type.
 *
 * @param object $site
 *   The Site node object.
 */
function hook_og_sm_site_insert($site) {

}

/**
 * Act on a Site node being updated.
 *
 * Will only be triggered when the node_update hook is triggered for a node type
 * that is a Site type.
 *
 * @param object $site
 *   The Site node object.
 */
function hook_og_sm_site_update($site) {

}

/**
 * Act on a Site node being deleted.
 *
 * Will only be triggered when the node_delete hook is triggered for a node type
 * that is a Site type.
 *
 * @param object $site
 *   The Site node object.
 */
function hook_og_sm_site_delete($site) {

}

/**
 * @} End of "addtogroup hooks".
 */

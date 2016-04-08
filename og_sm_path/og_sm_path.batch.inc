<?php
/**
 * @file
 * Batch functionality.
 */

/**
 * Create a batch for a single Site to update ALL aliases (admin & content).
 *
 * @param object $site
 *   The Site to create the batch for.
 */
function og_sm_path_site_alias_update_batch($site) {
  $params = array($site->nid);
  $file = drupal_get_path('module', 'og_sm_path') . '/og_sm_path.batch.inc';

  $batch = array(
    'title' => t('Update Site content aliases'),
    'operations' => array(
      array('og_sm_path_site_alias_update_content_process', $params),
      array('og_sm_path_site_alias_update_menu_process', $params),
    ),
    'file' => $file,
  );

  batch_set($batch);
}

/**
 * Batch processing callback; Process to update the Site content pages.
 *
 * This will create/update aliases for all content pages of a single Site.
 *
 * @param int $site_nid
 *   The Site Node ID to run the process for.
 * @param array $context
 *   The process context.
 *
 * @see og_sm_path_site_alias_update_batch
 */
function og_sm_path_site_alias_update_content_process($site_nid, &$context) {
  $site = og_sm_site_load($site_nid);
  _og_sm_path_site_alias_update_content_init($site->nid, $context);

  // Get the group memberships.
  $site_memberships = _og_sm_path_site_alias_update_content_get_memberships($site->nid, $context);
  if (!$site_memberships) {
    $context['finished'] = 1;
    return;
  }

  // Rebuild the permissions for the node.
  foreach ($site_memberships as $site_membership) {
    $node = node_load($site_membership->etid);
    pathauto_node_update_alias($node, 'bulkupdate');

    $context['sandbox']['progress']++;
    $context['sandbox']['last_id'] = $node->nid;
  }

  // Show some feedback.
  $context['message'] = t(
    'Updated %count of %total content aliases for %site.',
    array(
      '%count' => $context['sandbox']['progress'],
      '%total' => $context['sandbox']['total'],
      '%site' => $site->title,
    )
  );

  // Progress.
  $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['total'];
}

/**
 * Batch processing callback; Process to update the menu's.
 *
 * This will trigger a menu cache clear.
 *
 * @param int $site_nid
 *   The Site Node ID to run the process for.
 * @param array $context
 *   The process context.
 *
 * @see og_sm_path_site_alias_update_batch
 */
function og_sm_path_site_alias_update_menu_process($site_nid, &$context) {
  menu_rebuild();
  menu_cache_clear_all();

  if (module_exists('admin_menu')) {
    admin_menu_flush_caches();
  }

  $context['message'] = t('Menu cache cleared.');
  $context['finished'] = 1;
}

/**
 * Initiate the batch.
 *
 * @param int $site_nid
 *   The Site node id.
 * @param array $context
 *   Batch API context.
 *
 * @see og_sm_path_site_alias_update_content_process
 */
function _og_sm_path_site_alias_update_content_init($site_nid, &$context) {
  // Initiate the batch.
  if (empty($context['sandbox'])) {
    // Count relevant nodes.
    $query = new EntityFieldQuery();
    $total = $query
      ->entityCondition('entity_type', 'og_membership')
      ->propertyCondition('group_type', 'node')
      ->propertyCondition('entity_type', 'node')
      ->propertyCondition('gid', $site_nid, '=')
      ->count()->execute();

    $context['sandbox']['progress'] = 0;
    $context['sandbox']['last_id'] = 0;
    $context['sandbox']['total'] = $total;
  }
}

/**
 * Get the next set of site_memberships (og_membership) to process.
 *
 * @param int $site_nid
 *   The Site node id.
 * @param array $context
 *   Batch API context.
 *
 * @return array[OgMembership]
 *   Array of OgMembership objects.
 *
 * @see og_sm_path_site_alias_update_content_process
 */
function _og_sm_path_site_alias_update_content_get_memberships($site_nid, &$context) {
  $limit = 50;

  // Retrieve the next batch.
  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'og_membership')
    ->propertyCondition('group_type', 'node')
    ->propertyCondition('entity_type', 'node')
    ->propertyCondition('gid', $site_nid)
    ->propertyCondition('etid', $context['sandbox']['last_id'], '>')
    ->propertyOrderBy('etid', 'ASC')
    ->range(0, $limit)
    ->execute();

  // Check if we found any memberships.
  if (!isset($result['og_membership'])) {
    return array();
  }

  return entity_load('og_membership', array_keys($result['og_membership']));
}

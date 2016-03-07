<?php
/**
 * @file
 * Batch functionality.
 */

/**
 * Batch processing callback; Generate aliases for Site administration pages.
 *
 * This will process all administration pages for all Sites.
 *
 * @param array $context
 *   The process context.
 */
function og_sm_pathauto_bulk_update_batch_process(&$context) {
  if (!isset($context['sandbox']['sites'])) {
    $site_nids = og_sm_site_all_nids();
    $context['sandbox']['sites'] = $site_nids;
    $context['sandbox']['count'] = 0;
    $context['sandbox']['total'] = count($site_nids);
  }

  $site = og_sm_site_load(array_shift($context['sandbox']['sites']));
  if (!$site) {
    $context['finished'] = 1;
    return;
  }

  // Process one site.
  og_sm_pathauto_site_path_update_admin_aliases($site, 'bulkupdate');
  $context['sandbox']['count']++;
  $context['message'] = t('Updated aliases for site @name.', array('@name' => $site->title));

  if ($context['sandbox']['count'] < $context['sandbox']['total']) {
    $context['finished'] = $context['sandbox']['count'] / $context['sandbox']['total'];
  }
  else {
    $context['finished'] = 1;
  }
}

/**
 * Create a batch for a single Site to update ALL aliases (admin & content).
 *
 * @param object $site
 *   The Site to create the batch for.
 */
function og_sm_pathauto_site_alias_update_batch($site) {
  $params = array($site->nid);
  $file = drupal_get_path('module', 'og_sm_pathauto') . '/og_sm_pathauto.batch.inc';

  $batch = array(
    'title' => t('Update Site pages & content aliases'),
    'operations' => array(
      array('og_sm_pathauto_site_alias_update_admin_process', $params),
      array('og_sm_pathauto_site_alias_update_content_process', $params),
    ),
    'file' => $file,
  );

  batch_set($batch);
}

/**
 * Batch processing callback; Process to update a Site administration pages.
 *
 * This will create/update aliases for all administration pages of a single
 * Site.
 *
 * @param array $context
 *   The process context.
 */
function og_sm_pathauto_site_alias_update_admin_process($site_nid, &$context) {
  $site = og_sm_site_load($site_nid);

  og_sm_pathauto_site_path_update_admin_aliases($site, 'bulkupdate');

  $context['finished'] = 1;
  $context['message'] = t(
    'Updated administration page aliases for %site.',
    array('%site' => $site->title)
  );
}

/**
 * Batch processing callback; Process to update the Site content pages.
 *
 * This will create/update aliases for all content pages of a single Site.
 *
 * @param array $context
 *   The process context.
 */
function og_sm_pathauto_site_alias_update_content_process($site_nid, &$context) {
  $site = og_sm_site_load($site_nid);
  _og_sm_pathauto_site_alias_update_content_init($site->nid, $context);

  // Get the group memberships.
  $site_memberships = _og_sm_pathauto_site_alias_update_content_get_memberships($site->nid, $context);
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
 * Initiate the batch.
 *
 * @param int $site_nid
 *   The Site node id.
 * @param array $context
 *   Batch API context.
 */
function _og_sm_pathauto_site_alias_update_content_init($site_nid, &$context) {
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
 */
function _og_sm_pathauto_site_alias_update_content_get_memberships($site_nid, &$context) {
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

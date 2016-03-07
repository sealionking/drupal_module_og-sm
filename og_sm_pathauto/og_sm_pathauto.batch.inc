<?php
/**
 * @file
 * Batch functionality.
 */

/**
 * Batch processing callback; Generate aliases for Site administration pages.
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
  og_sm_pathauto_site_paths_update_aliases($site, 'bulkupdate');
  $context['sandbox']['count']++;
  $context['message'] = t('Updated aliases for site @name.', array('@name' => $site->title));

  if ($context['sandbox']['count'] < $context['sandbox']['total']) {
    $context['finished'] = $context['sandbox']['count'] / $context['sandbox']['total'];
  }
  else {
    $context['finished'] = 1;
  }
}

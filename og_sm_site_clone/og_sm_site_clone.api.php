<?php
/**
 * @file
 * API documentation of avalailable og_sm_site_clone hooks.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Hook to alter the new Site before being shown in the node form.
 *
 * @param object $site_new
 *   The new Site object being prepared.
 * @param array $context
 *   The context for the alter. The context contains:
 *   - original_site: Site node object that is used as source for the clone.
 */
function hook_og_sm_site_clone_prepare_alter(&$site_new, array $context) {
  // Set the new title based on original site prefixed with "Clone of".
  $site_original = $context['site_original'];
  $site_new->title = t(
    'Clone of !title',
    array('!title' => $site_original->title)
  );
}

/**
 * @} End of "addtogroup hooks".
 */

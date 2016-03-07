<?php
/**
 * @file
 * Pathauto related hook implementations.
 */

/**
 * Implements hook_path_alias_types().
 */
function og_sm_pathauto_path_alias_types() {
  $objects = array(
    'group/node/' => t('Site administration paths'),
  );
  return $objects;
}

/**
 * Implements hook_pathauto().
 */
function og_sm_pathauto_pathauto($op) {
  switch ($op) {
    case 'settings':
      $settings = array();
      $settings['module'] = 'og_sm';
      $settings['token_type'] = 'node';
      $settings['groupheader'] = t('Site administration paths');
      $settings['patterndescr'] = t('Path pattern that will replace the <em>group/node/%nid</em> part of the Site administration paths.');
      $settings['patterndefault'] = '[node:site-path]';
      $settings['batch_update_callback'] = 'og_sm_pathauto_bulk_update_batch_process';
      $settings['batch_file'] = drupal_get_path('module', 'og_sm_pathauto') . '/og_sm_pathauto.batch.inc';
      return (object) $settings;

    default:
      break;
  }
}

/**
 * Implements hook_pathauto_pattern_alter().
 *
 * Replaces the [node:site-path] with the actual path:
 * - pattern: [node:site-path].
 * - path: group/node/25/admin/people.
 * => Pattern will be: [node:site-path]/admin/people.
 */
function og_sm_pathauto_pathauto_pattern_alter(&$pattern, array $context) {
  if ($context['module'] !== 'og_sm') {
    return;
  }

  if (!isset($context['data']['og_sm_site_path'])) {
    return;
  }
  $path = $context['data']['og_sm_site_path'];

  if (!isset($context['data']['node'])) {
    return;
  }
  $site = $context['data']['node'];

  if (!og_sm_is_site($site)) {
    return;
  }

  $pattern = preg_replace('#^group/%/%#', $pattern, $path);
}

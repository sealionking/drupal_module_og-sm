<?php
/**
 * @file
 * Contains token hook implementations.
 */

/**
 * Implements hook_tokens_alter().
 */
function og_sm_content_tokens_alter(array &$replacements, array $context) {
  if ($context['type'] !== 'node') {
    return;
  }
  $node = $context['data']['node'];
  if ($content_type = og_sm_content_get_type_info_by_node($node)) {
    $replacements['[node:content-type]'] = $content_type->name;
  }
}

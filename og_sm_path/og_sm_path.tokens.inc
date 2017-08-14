<?php

/**
 * @file
 * Custom tokens.
 */

use Drupal\Component\Utility\Html;
use Drupal\Core\Render\BubbleableMetadata;
use Drupal\node\NodeInterface;
use Drupal\og_sm\OgSm;
use Drupal\og_sm_path\OgSmPath;

/**
 * Implements hook_token_info().
 */
function og_sm_path_token_info() {
  $node_tokens = [];
  $node_tokens['site-path'] = [
    'name' => t('Site Path'),
    'description' => t('The path of the Site the node belongs to.'),
  ];

  return [
    'tokens' => ['node' => $node_tokens],
  ];
}

/**
 * Implements hook_tokens().
 */
function og_sm_path_tokens($type, $tokens, array $data = [], array $options = [], BubbleableMetadata $bubbleable_metadata) {
  $replacements = [];

  switch ($type) {
    case 'node':
      $replacements = _og_sm_path_tokens_node($tokens, $data, $options, $bubbleable_metadata);
      break;
  }

  return $replacements;
}

/**
 * Tokens for nodes.
 *
 * @param array $tokens
 *   An array of tokens to be replaced. The keys are the machine-readable token
 *   names, and the values are the raw [type:token] strings that appeared in the
 *   original text.
 * @param array $data
 *   An associative array of data objects to be used when generating replacement
 *   values, as supplied in the $data parameter to
 *   \Drupal\Core\Utility\Token::replace().
 * @param array $options
 *   An associative array of options for token replacement; see
 *   \Drupal\Core\Utility\Token::replace() for possible values.
 * @param \Drupal\Core\Render\BubbleableMetadata $bubbleable_metadata
 *   The bubbleable metadata.
 *
 * @return array
 *   Replacements keyed by their token.
 */
function _og_sm_path_tokens_node(array $tokens, array $data, array $options, BubbleableMetadata $bubbleable_metadata) {
  $node = $data['node'];
  $sanitize = !empty($options['sanitize']);

  // Create the replacements.
  $replacements = [];
  foreach ($tokens as $name => $original) {
    switch ($name) {
      case 'site-path':
        $replacements[$original] = _og_sm_path_tokens_site_path($node, $sanitize);
        $bubbleable_metadata->addCacheableDependency($node);
        break;
    }
  }

  // Filter out empty values.
  return array_filter($replacements);
}

/**
 * Get the path of the Site the node belongs to.
 *
 * @param \Drupal\node\NodeInterface $node
 *   The node to create the token for.
 * @param bool $sanitize
 *   Should the output be sanitized.
 *
 * @return string|NULL
 *   Token string if any.
 */
function _og_sm_path_tokens_site_path(NodeInterface $node, $sanitize) {
  $site_manager = OgSm::siteManager();
  $site = ($site_manager->isSite($node))
    ? $node
    : $site_manager->getSiteFromContent($node);

  if (!$site) {
    return NULL;
  }

  $path = OgSmPath::sitePathManager()->getPathFromSite($site);
  return $sanitize ? Html::escape($path) : $path;
}

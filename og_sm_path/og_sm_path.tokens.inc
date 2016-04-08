<?php
/**
 * @file
 * Custom tokens.
 */

/**
 * Implements hook_token_info().
 */
function og_sm_path_token_info() {
  $node_tokens = array();
  $node_tokens['site-path'] = array(
    'name' => t('Site Path'),
    'description' => t('The path of the Site the node belongs to.'),
  );

  return array(
    'tokens' => array('node' => $node_tokens),
  );
}

/**
 * Implements hook_tokens().
 */
function og_sm_path_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();

  switch ($type) {
    case 'node':
      $replacements = _og_sm_path_tokens_node($tokens, $data, $options);
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
 *   values, as supplied in the $data parameter to token_replace().
 * @param array $options
 *   An associative array of options for token replacement; see token_replace()
 *   for possible values.
 *
 * @return array
 *   Replacements keyed by their token.
 */
function _og_sm_path_tokens_node(array $tokens, array $data, array $options) {
  $node = $data['node'];
  $sanitize = !empty($options['sanitize']);

  // Create the replacements.
  $replacements = array();
  foreach ($tokens as $name => $original) {
    switch ($name) {
      case 'site-path':
        $replacements[$original] = _og_sm_path_tokens_site_path($node, $sanitize);
        break;
    }
  }

  // Filter out empty values.
  return array_filter($replacements);
}

/**
 * Get the path of the Site the node belongs to.
 *
 * @param object $node
 *   The node to create the token for.
 * @param bool $sanitize
 *   Should the output be sanitized.
 *
 * @return string|NULL
 *   Token string if any.
 */
function _og_sm_path_tokens_site_path($node, $sanitize) {
  $site = (og_sm_is_site($node))
    ? $node
    : og_sm_content_get_site($node);

  if (!$site) {
    return NULL;
  }

  $path = og_sm_path($site);
  return $sanitize ? check_plain($path) : $path;
}

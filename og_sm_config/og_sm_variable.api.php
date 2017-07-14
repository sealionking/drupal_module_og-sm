<?php
/**
 * @file
 * API documentation about the og_sm_variable module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Default Site variable values when a new Site is created.
 *
 * @param object $site
 *   The site node object.
 *
 * @return array
 *   Array of default variable values for the new Site keyed by the variable
 *   name.
 */
function hook_og_sm_variable_defaults($site) {
  $items = array(
    'theme' => 'bartik',
    'og_sm_content_article_comment' => COMMENT_NODE_OPEN,
    'og_sm_content_article_machine_name' => 'news',
    'og_sm_content_article_name' => 'news',
    'og_sm_content_article_name_plural' => 'news',
  );

  return $items;
}

/**
 * Alter the default Site variables.
 *
 * @param array $items
 *   The default variable items.
 * @param object $site
 *   The site node object.
 *
 * @see hook_og_sm_variable_defaults
 */
function hook_og_sm_variable_defaults_alter(&$items, $site) {
  $items['theme'] = 'my-theme';
}

/**
 * @} End of "addtogroup hooks".
 */

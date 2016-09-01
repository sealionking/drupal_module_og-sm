<?php

/**
 * @file
 * Module API.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Create Drupal menu items (hook_menu) based on the given Site node.
 *
 * Modules can require to have unique menu items for specific sites (path
 * prefix, only when a Site feature is active...).
 *
 * This hook is called by the og_sm_menu module to collect such items. The
 * collected data is then bundled and passed to the Drupal menu.
 *
 * @param object $site
 *   The Site node object to collect the menu items for.
 *
 * @return array|null
 *   Menu item arrays to add to the Drupal menu system.
 *   See https://api.drupal.org/api/drupal/modules%21system%21system.api.php/function/hook_menu/7.x
 */
function hook_og_sm_menu($site) {
  return array(
    'group/node/' . $site->nid . '/article' => array(
      'title' => 'Articles',
      'page callback' => 'og_sm_menu_test_article_page',
      'access callback' => TRUE,
    ),
    'group/node/' . $site->nid . '/news' => array(
      'title' => 'News',
      'page callback' => 'og_sm_menu_test_news_page',
      'access callback' => TRUE,
    ),
  );
}

/**
 * Alter the menu items collected for a singe Site.
 *
 * @param array $items
 *   The items as collected.
 * @param object $site
 *   The Site for who the menu items are collected.
 */
function hook_og_sm_menu_alter(array &$items, $site) {
  $items['group/node/' . $site->nid . '/article']['page callback'] = 'og_sm_menu_test_article_page_altered';
}

/**
 * @} End of "addtogroup hooks".
 */

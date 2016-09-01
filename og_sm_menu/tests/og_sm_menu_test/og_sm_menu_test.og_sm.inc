<?php

/**
 * @file
 * Hooks implemented to test the Menu functionality.
 */

/**
 * Implements hook_og_sm_menu().
 */
function og_sm_menu_test_og_sm_menu($site) {
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
 * Implements hook_og_sm_menu_alter().
 */
function og_sm_menu_test_og_sm_menu_alter(array &$items, $site) {
  $items['group/node/' . $site->nid . '/article']['page callback'] = 'og_sm_menu_test_article_page_altered';
}

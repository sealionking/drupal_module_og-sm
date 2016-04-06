<?php
/**
 * @file
 * API documentation about the og_sm_theme module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Alter the list of allowed site themes for a Site.
 *
 * @param array $themes
 *   The allowed site themes for this Site.
 * @param array $context
 *   The context - contains the Site for which to alter the themes list.
 */
function hook_og_sm_theme_site_themes_alter(&$themes, $context) {

}

/**
 * Alters theme operation links for a Site.
 *
 * @param array $theme_groups
 *   An associative array containing groups of themes.
 *
 * @see og_sm_theme_themes_page()
 */
function hook_og_sm_theme_themes_page_alter(&$theme_groups) {

}

/**
 * @} End of "addtogroup hooks".
 */

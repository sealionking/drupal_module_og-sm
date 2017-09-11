<?php

namespace Drupal\og_sm_menu;

use Drupal\node\NodeInterface;

/**
 * Interface for site menu manager classes.
 */
interface SiteMenuManagerInterface {

  const SITE_MENU_NAME = 'site_menu';

  /**
   * Gets the current site menu.
   *
   * @return \Drupal\og_menu\OgMenuInstanceInterface|null
   *   The og-menu instance, NULL if no menu was found in the current context.
   */
  public function getCurrentMenu();

  /**
   * Creates a site menu for the passed site.
   *
   * @param \Drupal\node\NodeInterface $site
   *   The site node.
   */
  public function createMenu(NodeInterface $site);

  /**
   * Gets all site menu instances.
   *
   * @return \Drupal\og_menu\OgMenuInstanceInterface[]
   *   An array of og-menu instances.
   */
  public function getAllMenus();

}

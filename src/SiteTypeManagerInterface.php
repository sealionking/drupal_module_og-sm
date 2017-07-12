<?php

namespace Drupal\og_sm;

use Drupal\node\NodeTypeInterface;

/**
 * Interface for site type manager classes.
 */
interface SiteTypeManagerInterface {

  /**
   * The third party setting key which stores whether a node is a site.
   */
  const SITE_TYPE_SETTING_KEY = 'og_sm_site_type';

  /**
   * Check if a given node type is a Site type.
   *
   * @param \Drupal\node\NodeTypeInterface $type
   *   The type to check.
   *
   * @return bool
   *   Is Site type.
   */
  public function isSiteType(NodeTypeInterface $type);

  /**
   * Get a list of Site node types.
   *
   * @return \Drupal\node\NodeTypeInterface[]
   *   List of node types that are Sites.
   */
  public function getSiteTypes();

  /**
   * Add a node type as a site type.
   *
   * @param \Drupal\node\NodeTypeInterface $type
   *   The content type to add.
   */
  public function addSiteType(NodeTypeInterface $type);

  /**
   * Remove a node type a a site type.
   *
   * @param \Drupal\node\NodeTypeInterface $type
   *   The content type to remove.
   */
  public function removeSiteType(NodeTypeInterface $type);

  /**
   * Get a list of content types that can be used to create Site content.
   *
   * @return \Drupal\node\NodeTypeInterface[]
   *   Content types that are OG types, sorted by their name.
   */
  public function getContentTypes();

  /**
   * Check if a given content type is a Site content type.
   *
   * @param NodeTypeInterface $type
   *   The content type to check.
   *
   * @return bool
   *   Is Site content type.
   */
  public function isSiteContentType(NodeTypeInterface $type);

}

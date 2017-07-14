<?php

namespace Drupal\og_sm_config\Config;

use Drupal\Core\Cache\CacheableMetadata;
use Drupal\Core\Config\ConfigCollectionInfo;
use Drupal\Core\Config\ConfigCrudEvent;
use Drupal\Core\Config\ConfigFactoryOverrideBase;
use Drupal\Core\Config\ConfigFactoryOverrideInterface;
use Drupal\Core\Config\ConfigRenameEvent;
use Drupal\Core\Config\StorageInterface;
use Drupal\Core\Config\TypedConfigManagerInterface;
use Drupal\node\Entity\Node;
use Drupal\node\NodeInterface;
use Drupal\og_sm\SiteManagerInterface;

/**
 * Provides site overrides for the configuration factory.
 */
interface SiteConfigFactoryOverrideInterface extends ConfigFactoryOverrideInterface {

  /**
   * Get language override for given site and configuration name.
   *
   * @param \Drupal\node\NodeInterface $site
   *   The site node.
   * @param string $name
   *   Configuration name.
   *
   * @return \Drupal\og_sm_config\Config\SiteConfigOverride
   *   Configuration override object.
   */
  public function getOverride(NodeInterface $site, $name);

  /**
   * Returns the storage instance for a particular site.
   *
   * @param NodeInterface $site
   *   The site node.
   *
   * @return \Drupal\Core\Config\StorageInterface
   *   The storage instance for a particular site.
   */
  public function getStorage($site);

  /**
   * Gets the site node used to override configuration data.
   *
   * @return \Drupal\node\NodeInterface $site
   *   The site node.
   */
  public function getSite();

  /**
   * Sets the site to be used in configuration overrides.
   *
   * @param \Drupal\node\NodeInterface $site
   *   The site node.
   *
   * @return $this
   */
  public function setSite(NodeInterface $site = NULL);

}

<?php

namespace Drupal\og_sm\Access;

use Drupal\Core\Access\AccessResult;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Routing\Access\AccessInterface;
use Drupal\Core\Session\AccountInterface;
use Drupal\node\NodeInterface;
use Drupal\og\OgAccessInterface;
use Drupal\og_sm\SiteManagerInterface;
use Symfony\Component\Routing\Route;

/**
 * Determines access to for node add pages.
 *
 * @ingroup node_access
 */
class SitePermissionAccessCheck implements AccessInterface {

  /**
   * The entity manager.
   *
   * @var \Drupal\Core\Entity\EntityTypeManagerInterface
   */
  protected $entityTypeManager;

  /**
   * The OG access service.
   *
   * @var \Drupal\og\OgAccessInterface
   */
  protected $ogAccess;

  /**
   * The site manager service.
   *
   * @var \Drupal\og_sm\SiteManagerInterface
   */
  protected $siteManager;

  /**
   * Constructs a EntityCreateAccessCheck object.
   *
   * @param \Drupal\Core\Entity\EntityTypeManagerInterface $entity_type_manager
   *   The entity type manager.
   * @param \Drupal\og\OgAccessInterface $og_access
   *   The OG access service.
   * @param \Drupal\og_sm\SiteManagerInterface $site_manager
   *   The site manager service.
   */
  public function __construct(EntityTypeManagerInterface $entity_type_manager, OgAccessInterface $og_access, SiteManagerInterface $site_manager) {
    $this->entityTypeManager = $entity_type_manager;
    $this->ogAccess = $og_access;
    $this->siteManager = $site_manager;
  }

  /**
   * Checks access to the node add page for the node type.
   *
   * @param \Symfony\Component\Routing\Route $route
   *   The route to check against.
   * @param \Drupal\Core\Session\AccountInterface $account
   *   The currently logged in account.
   * @param \Drupal\node\NodeInterface $node
   *   THe site node.
   *
   * @return string
   *   A \Drupal\Core\Access\AccessInterface constant value.
   */
  public function access(Route $route, AccountInterface $account, NodeInterface $node) {
    if ($this->siteManager->isSite($node)) {
      $operation = $route->getRequirement('_site_permission');
      return $this->ogAccess->userAccess($node, $operation, $account);
    }
    return AccessResult::neutral();
  }

}

<?php

namespace Drupal\og_sm_context\Plugin\OgGroupResolver;

use Drupal\node\NodeInterface;
use Drupal\og\OgResolvedGroupCollectionInterface;

/**
 * Tries to get the context based on the fact that we are on a site admin page.
 *
 * Will check if:
 * - The path starts with group/node/{node}
 * - If the group is a Site node type.
 *
 * @OgGroupResolver(
 *   id = "og_sm_context_admin",
 *   label = "Site Administration",
 *   description = @Translation("Determine Site context based on the fact that we are on a Site administration page.")
 * )
 */
class AdminGroupResolver extends OgSmGroupResolverBase {

  /**
   * {@inheritdoc}
   */
  public function resolve(OgResolvedGroupCollectionInterface $collection) {
    $route_object = $this->routeMatch->getRouteObject();
    if (!$route_object) {
      return;
    }
    if (!preg_match('#^/group/node/({node}|[0-9]+)#', $route_object->getPath())) {
      return;
    }
    $group = $this->routeMatch->getParameter('node');

    if ($group instanceof NodeInterface && $this->siteManager->isSite($group)) {
      $collection->addGroup($group, ['url']);
      $this->stopPropagation();
    }
  }

}

<?php

namespace Drupal\og_sm_context\Plugin\OgGroupResolver;

use Drupal\og\OgResolvedGroupCollectionInterface;

/**
 * Tries to get the context based on the fact that we are on a site admin page.
 *
 * Will check if:
 * - The path starts with group/node/[nid]
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
    if (strpos($route_object->getPath(), '/group/node/{group}/') !== 0) {
      return;
    }
    $group = $this->routeMatch->getParameter('group');

    if ($this->siteManager->isSite($group)) {
      $collection->addGroup($group, ['url']);
      $this->stopPropagation();
    }
  }

}

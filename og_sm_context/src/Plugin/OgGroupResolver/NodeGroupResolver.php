<?php

namespace Drupal\og_sm_context\Plugin\OgGroupResolver;

use Drupal\og\OgResolvedGroupCollectionInterface;

/**
 * Tries to get the context based on the fact that we are on a node page.
 *
 * @OgGroupResolver(
 *   id = "og_sm_context_node",
 *   label = "Site Content",
 *   description = @Translation("Determine Site context based on the fact that we are on a Site page or a Site content page.")
 * )
 */
class NodeGroupResolver extends OgSmGroupResolverBase {

  /**
   * {@inheritdoc}
   */
  public function resolve(OgResolvedGroupCollectionInterface $collection) {
    $route_object = $this->routeMatch->getRouteObject();
    if (!$route_object) {
      return;
    }
    if (strpos($route_object->getPath(), '/node/{node}') !== 0) {
      return;
    }
    $node = $this->routeMatch->getParameter('node');

    if ($this->siteManager->isSite($node)) {
      $collection->addGroup($node, ['url']);
      $this->stopPropagation();
    }
    elseif ($site = $this->siteManager->getSiteFromContent($node)) {
      $collection->addGroup($site, ['url']);
      $this->stopPropagation();
    }

  }

}

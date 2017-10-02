<?php

namespace Drupal\og_sm_menu\Routing;

use Drupal\Core\Routing\RouteSubscriberBase;
use Symfony\Component\Routing\RouteCollection;

/**
 * Listens to the dynamic route events.
 */
class RouteSubscriber extends RouteSubscriberBase {

  /**
   * {@inheritdoc}
   */
  protected function alterRoutes(RouteCollection $collection) {
    $routes = $collection->all();
    foreach ($routes as $route_name => $route) {
      if ($route_name === 'og_sm.site_menu.edit_link') {
        $route->setRequirements(['_custom_access' => '\Drupal\menu_admin_per_menu\Access\MenuAdminPerMenuAccess::menuLinkAccess']);
      }
    }
  }

}

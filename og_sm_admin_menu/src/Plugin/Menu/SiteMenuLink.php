<?php

namespace Drupal\og_sm_admin_menu\Plugin\Menu;

use Drupal\Core\Menu\MenuLinkDefault;
use Drupal\Core\Menu\StaticMenuLinkOverridesInterface;
use Drupal\Core\Routing\RouteProviderInterface;
use Drupal\og_sm\SiteManagerInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Defines site menu links.
 *
 * @see \Drupal\og_sm_admin_menu\Plugin\Derivative\SiteMenuLink
 */
class SiteMenuLink extends MenuLinkDefault {

  /**
   * The site manager.
   *
   * @var \Drupal\og_sm\SiteManagerInterface
   */
  protected $siteManager;

  /**
   * The route provider.
   *
   * @var \Drupal\Core\Routing\RouteProviderInterface
   */
  protected $routeProvider;

  /**
   * Constructs a new ViewsMenuLink.
   *
   * @param array $configuration
   *   A configuration array containing information about the plugin instance.
   * @param string $plugin_id
   *   The plugin_id for the plugin instance.
   * @param mixed $plugin_definition
   *   The plugin implementation definition.
   * @param \Drupal\Core\Menu\StaticMenuLinkOverridesInterface $static_override
   *   The static override storage.
   * @param \Drupal\og_sm\SiteManagerInterface $site_manager
   *   The site manager.
   * @param \Drupal\Core\Routing\RouteProviderInterface $route_provider
   *   The route provider.
   */
  public function __construct(array $configuration, $plugin_id, $plugin_definition, StaticMenuLinkOverridesInterface $static_override, SiteManagerInterface $site_manager, RouteProviderInterface $route_provider) {
    parent::__construct($configuration, $plugin_id, $plugin_definition, $static_override);
    $this->siteManager = $site_manager;
    $this->routeProvider = $route_provider;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition) {
    return new static(
      $configuration,
      $plugin_id,
      $plugin_definition,
      $container->get('menu_link.static.overrides'),
      $container->get('og_sm.site_manager'),
      $container->get('router.route_provider')
    );
  }

  /**
   * {@inheritdoc}
   */
  public function getRouteParameters() {
    $route_parameters = parent::getRouteParameters();
    $site = $this->siteManager->currentSite();
    $route_parameters['entity_type_id'] = 'node';
    $route_parameters['node'] = $site ? $site->id() : 0;
    $route = $this->routeProvider->getRouteByName($this->getRouteName());
    return array_intersect_key($route_parameters, array_flip($route->compile()->getPathVariables()));
  }

}

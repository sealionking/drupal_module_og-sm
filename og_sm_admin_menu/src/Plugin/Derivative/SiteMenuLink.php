<?php

namespace Drupal\og_sm_admin_menu\Plugin\Derivative;

use Drupal\Component\Plugin\Derivative\DeriverBase;
use Drupal\Core\Plugin\Discovery\YamlDiscovery;
use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\Core\Plugin\Discovery\ContainerDeriverInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Provides site admin menu links.
 *
 * @see \Drupal\og_sm_admin_menu\Plugin\Menu\SiteMenuLink
 */
class SiteMenuLink extends DeriverBase implements ContainerDeriverInterface {

  /**
   * The module handler.
   *
   * @var \Drupal\Core\Extension\ModuleHandlerInterface
   */
  protected $moduleHandler;

  /**
   * Creates an SiteMenuLink object.
   *
   * @param \Drupal\Core\Extension\ModuleHandlerInterface $module_handler
   *   The module handler.
   */
  public function __construct(ModuleHandlerInterface $module_handler) {
    $this->moduleHandler = $module_handler;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container, $base_plugin_id) {
    return new static(
      $container->get('module_handler')
    );
  }

  /**
   * {@inheritdoc}
   */
  public function getDerivativeDefinitions($base_plugin_definition) {
    $yaml_discovery = new YamlDiscovery('site_links.menu', $this->moduleHandler->getModuleDirectories());
    $yaml_discovery->addTranslatableProperty('title', 'title_context');
    $yaml_discovery->addTranslatableProperty('description', 'description_context');

    $definitions = $yaml_discovery->getDefinitions();
    $this->moduleHandler->alter('og_sm_site_menu_links_discovered', $definitions);

    $links = [];
    foreach ($definitions as $plugin_id => $plugin_definition) {
      if (!empty($plugin_definition['parent'])) {
        $plugin_definition['parent'] = 'og_sm_admin_menu:' . $plugin_definition['parent'];
      }

      $links[$plugin_id] = $plugin_definition + $base_plugin_definition;
    }
    return $links;
  }

}

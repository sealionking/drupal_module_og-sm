<?php

namespace Drupal\og_sm_context\Plugin\OgGroupResolver;

use Drupal\Component\Plugin\Exception\InvalidPluginDefinitionException;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\Core\Routing\RouteMatchInterface;
use Drupal\og\GroupTypeManager;
use Drupal\og\OgGroupResolverBase;
use Drupal\og\OgResolvedGroupCollectionInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Symfony\Component\HttpFoundation\RequestStack;

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
class AdminGroupResolver extends OgGroupResolverBase implements ContainerFactoryPluginInterface {

  /**
   * The route match object.
   *
   * @var \Drupal\Core\Routing\RouteMatchInterface
   */
  protected $routeMatch;

  /**
   * Constructs a AdminGroupResolver.
   *
   * @param array $configuration
   *   A configuration array containing information about the plugin instance.
   * @param string $plugin_id
   *   The plugin_id for the plugin instance.
   * @param mixed $plugin_definition
   *   The plugin implementation definition.
   * @param \Drupal\Core\Routing\RouteMatchInterface $route_match
   *   The route match object.
   */
  public function __construct(array $configuration, $plugin_id, $plugin_definition, RouteMatchInterface $route_match) {
    parent::__construct($configuration, $plugin_id, $plugin_definition);
    $this->routeMatch = $route_match;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition) {
    return new static(
      $configuration,
      $plugin_id,
      $plugin_definition,
      $container->get('current_route_match')
    );
  }

  /**
   * {@inheritdoc}
   */
  public function resolve(OgResolvedGroupCollectionInterface $collection) {
    $route_object = $this->routeMatch->getRouteObject();
    if (!$route_object) {
      return FALSE;
    }
    if (strpos($route_object->getPath(), '/group/node/{group}/') !== 0) {
      return FALSE;
    }
    $group = $this->routeMatch->getParameter('group');
    $collection->addGroup($group, ['url']);
    $this->stopPropagation();
  }

}

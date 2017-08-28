<?php

namespace Drupal\og_sm\EventSubscriber;

use Drupal\og\Event\PermissionEventInterface;
use Drupal\og\GroupPermission;
use Drupal\og\OgRoleInterface;
use Symfony\Component\EventDispatcher\EventSubscriberInterface;

/**
 * Group permission event subscriber for og_sm.
 */
class GroupPermissionEventSubscriber implements EventSubscriberInterface {

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents() {
    return [
      PermissionEventInterface::EVENT_NAME => [['provideDefaultOgPermissions']],
    ];
  }

  /**
   * Provides default OG permissions.
   *
   * @param \Drupal\og\Event\PermissionEventInterface $event
   *   The OG permission event.
   */
  public function provideDefaultOgPermissions(PermissionEventInterface $event) {
    $event->setPermission(
      new GroupPermission([
        'name' => 'administer site',
        'title' => t('Administer Site'),
        'description' => t('View the Site administration pages.'),
        'default roles' => [OgRoleInterface::ADMINISTRATOR],
      ])
    );
  }

}

<?php

namespace Drupal\og_sm\Event;

/**
 * Defines events for site types.
 */
final class SiteTypeEvents {

  /**
   * Name of the event fired when setting a node type as a site.
   *
   * This event allows modules to perform an action whenever a node type is set
   * as a site. The event listener method receives a
   * \Drupal\og_sm\Event\SiteTypeEvent instance.
   *
   * @Event
   *
   * @see \Drupal\og_sm\SiteTypeManagerInterface::addSiteType()
   */
  const ADD = 'og_sm.site_type.add';

  /**
   * Name of the event fired when setting a node type as a site.
   *
   * This event allows modules to perform an action whenever a node type is
   * removed as a site. The event listener method receives a
   * \Drupal\og_sm\Event\SiteTypeEvent instance.
   *
   * @Event
   *
   * @see \Drupal\og_sm\SiteTypeManagerInterface::removeSiteType()
   */
  const REMOVE = 'og_sm.site_type.remove';

}

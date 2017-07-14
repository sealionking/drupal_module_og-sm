<?php

namespace Drupal\Tests\og_sm\Functional;

use Drupal\simpletest\WebTestBase;
use Drupal\og_sm\Tests\SiteCreationTrait;

/**
 * Base class to do functional tests for OG Site Manager functionality.
 */
class OgSmWebTestBase extends WebTestBase {

  use SiteCreationTrait;

  /**
   * {@inheritdoc}
   */
  public static $modules = [
    'field',
    'node',
    'og',
    'og_ui',
    'og_sm',
    'system',
    'user',
  ];

  /**
   * Node types to use in the test.
   */
  const TYPE_DEFAULT = 'og_sm_node_type_not_group';
  const TYPE_IS_GROUP = 'og_sm_node_type_is_group';
  const TYPE_IS_GROUP_CONTENT = 'og_sm_node_type_is_group_content';

}

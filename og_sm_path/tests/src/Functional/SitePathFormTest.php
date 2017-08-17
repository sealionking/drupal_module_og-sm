<?php

namespace Drupal\Tests\og_sm_path\Functional;

use Drupal\og_sm\OgSm;
use Drupal\og_sm_path\OgSmPath;
use Drupal\Tests\og_sm\Functional\OgSmWebTestBase;

/**
 * Tests Site Path node form settings.
 *
 * @group og_sm
 */
class SitePathFormTest extends OgSmWebTestBase {

  /**
   * {@inheritdoc}
   */
  public static $modules = [
    'og_sm_path',
  ];

  /**
   * The admin user to test with.
   *
   * @var \Drupal\Core\Session\AccountInterface
   */
  protected $userAdministrator;

  /**
   * Global user without Change All permission.
   *
   * @var \Drupal\Core\Session\AccountInterface
   */
  protected $userWithoutChangeAllPermission;

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    parent::setUp();

    $this->userAdministrator = $this->drupalCreateUser([], NULL, TRUE);
    $this->userWithoutChangeAllPermission = $this->drupalCreateUser(
      ['bypass node access', 'administer nodes']
    );

    // Create Sites.
    $this->createGroupNodeType('not_site_type');
    $site_type  = $this->createGroupNodeType('is_site_type');
    OgSm::siteTypeManager()->setIsSiteType($site_type, TRUE);
    $site_type->save();
  }

  /**
   * Test the node form.
   */
  public function testSiteNodeForm() {
    // As Administrator.
    $this->drupalLogin($this->userAdministrator);

    // Test non-site node forms.
    $this->drupalGet('node/add/not_site_type');
    $this->assertResponse(200);
    $this->assertNoFieldById('edit-site-path', NULL, 'No Site Path field for non Site content types.');
    $this->assertFieldById('edit-path-0-alias', NULL, 'Path alias field should be available.');

    // Test site node form.
    $this->drupalGet('node/add/is_site_type');
    $this->assertResponse(200);
    $this->assertFieldById('edit-site-path', NULL, 'Site Path field available for Site content types.');
    $this->assertNoFieldById('edit-path-0-alias', NULL, 'Path alias field not available.');

    // Create a new Site, check if the path is saved.
    $edit = [
      'title[0][value]' => 'Site node test 1',
      'site_path' => '/site-node-test-me',
    ];
    $this->drupalPostForm('node/add/is_site_type', $edit, 'Save and publish');
    $site_node = $this->getNodeByTitle('Site node test 1');
    $this->assertEqual($edit['site_path'], OgSmPath::sitePathManager()->getPathFromSite($site_node), 'Site path is saved as Site variable');

    // Creating a new Site with an existing path should result in a form error.
    $edit = [
      'title[0][value]' => 'Site node test 2',
      'site_path' => '/site-node-test-me',
    ];
    $this->drupalPostForm('node/add/is_site_type', $edit, 'Save and publish');
    $this->assertText(
      'The Site path /site-node-test-me is already in use.',
      'Error message when a Site with the same path exists.'
    );

    // Creating a new Site with an invalid path should result in a form error.
    $edit = [
      'title[0][value]' => 'Site node test 2',
      'site_path' => '/site path not valid',
    ];
    $this->drupalPostForm('node/add/is_site_type', $edit, 'Save and publish');
    $this->assertText(
      'The Site path may contain only lowercase letters, numbers and dashes.',
      'Error message about the format of the Site path.'
    );
    $edit = [
      'title[0][value]' => 'Site node test 2',
      'site_path' => 'site-path-not-valid',
    ];
    $this->drupalPostForm('node/add/is_site_type', $edit, 'Save and publish');
    $this->assertText(
      'The alias needs to start with a slash.',
      'Error message when the site path does not start with a slash'
    );

    // The site path should be in the edit form for users with the proper
    // permissions.
    $this->drupalGet('node/' . $site_node->id() . '/edit');
    $this->assertFieldById('edit-site-path', NULL, 'Site path should be in the node edit form.');

    // Test with user who has no change path permissions.
    $this->drupalLogin($this->userWithoutChangeAllPermission);

    // Should have access to the field when creating new Sites.
    $this->drupalGet('node/add/is_site_type');
    $this->assertResponse(200);
    $this->assertFieldById('edit-site-path', NULL, 'Site Path field available for Site content types.');
    $this->assertNoFieldById('edit-path-0-alias', NULL, 'Path alias field not available.');

    // Site path should not be shown when editing existing Sites.
    $this->drupalGet('node/' . $site_node->id() . '/edit');
    $this->assertResponse(200);
    $this->assertNoFieldById('edit-site-path', NULL, 'Site path should NOT be in the node edit form.');
  }

}

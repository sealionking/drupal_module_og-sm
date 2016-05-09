<?php
/**
 * @file
 * Implemented og_sm_admin hooks.
 */

/**
 * Implements hook_og_sm_admin_menu().
 *
 * This will add menu items for contrib modules.
 */
function og_sm_admin_menu_og_sm_admin_menu() {
  $items = array();

  // Add og_ui items.
  if (module_exists('og_ui')) {
    $items['people'] = array(
      'title' => 'People',
      'href' => 'admin/people',
      'column' => 'right',
      'weight' => 40,
    );
    $items['people/overview'] = array(
      'title' => 'People',
      'description' => 'Manage Site members',
      'href' => 'admin/people',
      'exclude_menu' => TRUE,
      'weight' => -9,
    );
    $items['people/add'] = array(
      'title' => 'Add people',
      'description' => 'Add Site members.',
      'href' => 'admin/people/add-user',
      'weight' => -6,
    );
    $items['people/roles'] = array(
      'title' => 'Roles',
      'description' => 'View Site roles.',
      'href' => 'admin/roles',
      'weight' => -3,
    );
    $items['people/permissions'] = array(
      'title' => 'Permissions',
      'description' => 'View Site permissions.',
      'href' => 'admin/permissions',
      'weight' => 0,
    );
  }

  $structure = array(
    'title' => 'Structure',
    'href' => 'admin/structure',
    'column' => 'left',
    'weight' => 30,
  );

  // Add og_menu items.
  if (module_exists('og_menu')) {
    $items['structure'] = $structure;
    $items['structure/menu'] = array(
      'title' => 'Menus',
      'description' => 'Manage Site menus and their content.',
      'href' => 'admin/menus',
      'weight' => 0,
    );
  }

  // Add og_variables items.
  if (module_exists('og_variables')) {
    $items['structure'] = $structure;
    $items['structure/variables'] = array(
      'title' => 'Variables',
      'description' => 'Override global variables with Site specific values.',
      'href' => 'admin/variables',
      'weight' => 10,
    );
  }

  // Translate strings.
  t('People');
  t('Manage Site members');
  t('Add people');
  t('Add Site members.');
  t('Roles');
  t('View Site roles.');
  t('Permissions');
  t('View Site permissions.');
  t('Structure');
  t('Menus');
  t('Manage Site menus and their content.');
  t('Variables');
  t('Override global variables with Site specific values.');

  return $items;
}

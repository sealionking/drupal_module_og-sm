# Organic Groups : Site Administration Menu
This module replaces the administration menu with a Site specific version when
the User is within a Site context.

It also provides the Administration pages overview on <site-path>/admin.



## Functionality
* Site Administration menu when a Site context is active.
* Hooks to register admin pages in the menu and in the overview pages.



## Dependencies
Following modules are required to use the Sites functionality:

* [Administration Menu][link-admin-menu] module (admin_menu)
* og_sm
* [Patch][link-admin-menu-patch] for the administration menu module cache.



## Installation
1. Enable the module.
2. Open the admin_menu settings (admin/config/administration/admin_menu) and
   check the "Site Administration menu" option.

> **TIP** : The user needs the global "access administration menu" permission.
> This can only be assigned to global roles.
>
> Use the og_sm_global_roles module to give users within a Site the roles who
> have access to the administration menu.



## API
This module uses 2 hooks to collect what info to show in the menu and the
overview page.

> The hooks can be put in the `yourmodule.module` OR in the
> `yourmodule.og_sm.inc` file.
> The recommended place is in the yourmodule.og_sm.inc file as it keeps your
> .module file cleaner and makes the platform load less code by default.


### hook_og_sm_admin_menu()
Provide information about the items that should go into the admin menu.

Do not user t() when defining the items. The translation will be performend
by the Site Manager administration menu functionality.

The permission system of the menu_router table will be used to determine if a
user has access to a given path.

The return array should contain a list of menu items keyed by the path in the
menu:

* features : This is the first level and will be used to group the items by.
* features/contact : This is a subitem. If the Parent does not exist, it will
  be automatically added.

Each item contains an array with following parameters:

* **title** : The title for the item.
* **description** : The description of the administration page.
* **href** : The link to the page. Do not include "group/%/%/" as this will be
  filled in group specific. If href = people/add-user, the final URL will be
  "group/node/$site_nid/admin/people/add-user".
* **exclude_menu** : Set this to TRUE to exclude the item in the menu.
* **exclude_overview** : Set this to TRUE to exclude the item in the overview
  page(s).
* **weight** : The weight to order the items by.
* **column** : In what column (left, right) should the item be shown on the
  overview page. Only applicable for the first level items.

Example:

```php
function hook_og_sm_admin_menu() {
  $items = array();

  // Root item, will be used to group the sub items by.
  $items['features'] = array(
    'title' => 'Features',
    'href' => 'admin/features',
    'column' => 'left',
    'weight' => 2,
  );

  // Sub items for the "features" root item.
  $items['features/overview'] = array(
    'title' => 'Features',
    'description' => 'Enable/disable features for the site & configure those features.',
    'href' => 'admin/features',
    'weight' => -10,
    'hide_menu' => TRUE,
  );
  $items['features/contact'] = array(
    'title' => 'Contact',
    'description' => 'Contact page configuration.',
    'href' => 'admin/features/contact',
  );

  return $items;
}
```

### hook_og_sm_admin_menu_alter(&$items)
Alter the menu items as gathered using hook_og_sm_admin_menu().



[link-admin-menu]: https://www.drupal.org/project/admin_menu
[link-admin-menu-patch]: https://www.drupal.org/files/issues/admin_menu_cache_id_alter-2684839-2.patch

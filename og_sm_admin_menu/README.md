# Organic Groups : Site Administration Menu
This module replaces the administration menu with a Site specific version when
the User is within a Site context.

It also provides the Administration pages overview on <site-path>/admin.



## Functionality
* Site Administration menu when a Site context is active.
* Yml file discovery for administration links which should only be shown in site
  context.



## Requirements
Following modules are required to use the Sites functionality:

* og_sm



## Installation
1. Enable the module.

> **TIP** : The user needs the global "access toolbar" permission.
> This can only be assigned to global roles.



## API
This module uses yml file discovery to collect what info to show in the menu and
the overview page.



### module_name.site_links.menu.yml
The naming of the .yml file should be `module_name.site_links.menu.yml`

The allowed parameters per menu item are the same as core's `module_name.links.menu.yml`
file. Dynamic route parameters like the group's entity type (`{entity_type_id}`)
and the site node (`{node}`) are automatically injected when needed.

Example:

```yml
og_sm.site.admin:
  title: 'Administer site'
  route_name: entity.node.og_admin_routes
  menu_name: og_sm_admin_menu
og_sm.site.structure:
  title: 'Structure'
  route_name: og_sm.site.structure
  parent: og_sm.site.admin
  menu_name: og_sm_admin_menu
  weight: 30
  options:
    attributes:
      class:
        - 'toolbar-icon-system-admin-structure'
```

### hook_og_sm_site_menu_links_discovered_alter(&$items)
Alter the menu items as gathered using `module_name.site_links.menu.yml`.

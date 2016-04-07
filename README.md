# Organic Groups : Site Manager
This module provides support to setup a platform supporting multiple (sub)sites
based on [Organic Groups][link-og] (OG) functionality.

The usage of OG allows to share users between sites.



## Functionality
This module and its submodules adds functionality to support:

### Included in og_sm module
* Support for Group types to become sites enabled (Site).
* Support for Group Content types (Site Content).
* Support for Group Users (Site Users).

### Included in og_sm_access module
* Access to Site content based on the publication status of the Site they
  belong to.

### Included in og_sm_admin_menu module
* Site administration menu that replaces the default admin toolbar when the user
  is in a

### Included in og_sm_content module
* Site content administration

### Included in og_sm_context module
* OG context detection based on:
  - Path alias of the current page.
  - Paths starting with group/node/NID

### Included in og_sm_global_roles module
* Dynamically grant user global roles when they have specific Site roles.

### Included in og_sm_path module
* Define a Site path prefix per Site.
* Automatic path aliasing with the Site path as staring point.
* Auto update of Site content aliases and Site related page aliases when the
  Site path changes.
* Altering the `group/node/nid/admin/...` paths to `[site-path]/admin/...`.

### Included in og_sm_variable module
* Store Site specific settings in og_sm_variable table.
* Get/Set/Delete Site specific variables.


### Todo
* Support for User profile & settings per Site (Site User).
* Theme settings per Site (different theme or same theme with different
  settings).
* Taxonomy terms per Site.
* Site features: enable functionality per site (eg. Site A has blogs, Site B
  not).
* Site Content settings per Site (eg. Site A enables commenting on Blog posts,
  Site B not).
* Rename Site Content types per site.



## Installation
Enable the Organic Groups Site Manager module.

Edit the node type settings of the types that should be Site types.
Enable:
* The Organic Groups > Group checkbox
* And the Site Manager > Site Type checkbox.


### Dependencies
The Sites functionality is build upon [Organic Groups][link-og].

Following modules are required to use the Sites functionality:

* [Organic Groups][link-og]



## API

### Load a Site node
Get a Site node by its Node ID (nid). Will only return the node object if the
node exists and it is a Site node type.
```php
$site = og_sm_site_load($site_nid);
```

### Currently active Site
A lot of code depends if we are currently in an active Site context.

A helper function is available to get the currently active Site node.
This is a wrapper around the og_context() function + loading the node.

Get the currently active Site node:
```php
$site = og_sm_current_site();
```

### Site types
Get a list of node types that are Site node types:
```php
$site_types = og_sm_get_site_types();
```

### Check if content is a Site
The module provides helper functions to detect is a node or node type is a Site
node type:

Check if the given node is a Site type:
```php
$is_site = og_sm_is_site($node);
```

Check if the given node type is a Site type:
```php
$is_site_type = og_sm_is_site_type($node_type);
```

### Set the breacrumb for a site
This is a wrapper around the og_set_breadcrumb.

```php
og_sm_set_breadcrumb($site, 'path/to/set/the/breadcrumb');
```

### Site content types
Helper function to get a list of site type objects that can be used to create
content within a site.

```php
$site_content_types = og_sm_content_get_types();
```

### Check if content belongs to a Site
Helper functions to get the Site (if any) of a given content item (node) belongs
to.

Get all the Site nodes a node belongs to.
```php
$sites = og_sm_content_get_sites($node);
```

Get the Site node object from a given node object.
If a node belongs to multiple Sites only the first Site will be returned.

```php
$site = og_sm_content_get_site($node);
```

Check if the given node belongs to a Site:
```php
$is_site_content = og_sm_content_is_site_content($node);
```

Check if the given node is a member of the given Site:
```php
$is_member = og_sm_content_is_site_member($node, $site);
```

### Check if user is member of a Site
Helper functions about the Sites a user is member of.

Get the Site nodes a given user belongs to:
```php
$sites = og_sm_user_get_sites($account);
```

Check if a user is member of the given site:
```php
$is_member = og_sm_user_is_member_of_site($account, $site);
```

### Check access to Site permission
The OG module provides functionality to grant Site specific permissions.

The Site Manager module has wrappers around this functionality to check
permission acces for a site.

These functions can be used in Menu items ($account is optional):

* `og_sm_site_permission_access($site, $permission, $account)` : Check by Site
  node and permission name.
* `og_sm_site_nid_permission_access($site_nid, $permission, $account)` : Check
  by Site node id and permission name.


### Site node type action hooks
The module triggers hooks when a node type is being added or removed as being a
Site node type.

* `hook_og_sm_site_type_add($type)` : Site node type is being added as a Site
  type.
* `hook_og_sm_site_type_remove($type)` : Site node type is no longer a Site
  type.

> The hook can be put in the `yourmodule.module` OR in the
> `yourmodule.og_sm.inc` file.
> The recommended place is in the yourmodule.og_sm.inc file as it keeps your
> .module file cleaner and makes the platform load less code by default.


### Site action hooks
The module watches actions taken place on Site nodes and triggers its own hooks
when an action happens:

* `hook_og_sm_site_prepare($site)` : Site node being prepared to being shown on a
  node add/edit form.
* `hook_og_sm_site_presave($site)` : Site node being prepared to be inserted or
  updated in the database.
* `hook_og_sm_site_view($site, $view_mode, $langcode)` : Site node being
  prepared to being shown on the screen.
* `hook_og_sm_site_insert($site)` : Site node being inserted.
* `hook_og_sm_site_update($site)` : Site node being updated.
* `hook_og_sm_site_delete($site)` : Site node being deleted.

> The hooks can be put in the `yourmodule.module` OR in the
> `yourmodule.og_sm.inc` file.
> The recommended place is in the yourmodule.og_sm.inc file as it keeps your
> .module file cleaner and makes the platform load less code by default.




[link-og]: https://www.drupal.org/project/og

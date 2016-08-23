# Organic Groups : Site Manager
This module provides support to setup a platform supporting multiple (sub)sites
based on [Organic Groups][link-og] (OG) functionality.

* Define what node types should be used as Site's.
* Simplified OG API by providing OG function wrappers.

> *NOTE* : Site entities are limited to node entities.



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
  is in a Site context.

### Included in the og_sm_breadcrumb module
* Global breadcrumb behaviour configuration:
* When the og_sm_feature module is enabled: Configurable breadcrumb per Site.

### Included in og_sm_comment module
* Site comment administration

### Included in og_sm_content module
* Site content administration

### Included in og_sm_context module
* OG context detection based on:
  - Path alias of the current page.
  - Paths starting with group/node/NID

### Included in og_sm_feature module
* Enable/Disable & configure Site features.
  - Define globally default state & configuration.
  - Enable/Disable per Site.
  - Configuration per Site.

### Included in og_sm_global_roles module
* Dynamically grant user global roles when they have specific Site roles.

### Included in og_sm_path module
* Define a Site path prefix per Site.
* Automatic path aliasing with the Site path as staring point.
* Auto update of Site content aliases and Site related page aliases when the
  Site path changes.
* Altering the `group/node/nid/admin/...` paths to `[site-path]/admin/...`.

### Included in og_sm_site_clone module
* A "Clone" tab on Site node detail/edit pages.
* A form to clone an existing Site (`node/[existing-site-nid]/clone`).
* Hooks so modules can alter prepared cloned Site and perform actions after a 
  cloned Site is saved.

### Included in og_sm_taxonomy module
* Support global vocabularies with Site specific terms.
* Manage terms per Site.
* Select only from terms within the Site when creating content.

### Included in og_sm_theme module
* Set the theme per Site.
* Configure the breadcrumb for a theme within a Site.

### Included in og_sm_user module
* Site feature that creates site specific user profiles.
* Allow Sites to disable the editing of profiles, eg. when no alterable
  sections are available.

### Included in og_sm_variable module
* Store Site specific settings in og_sm_variable table.
* Get/Set/Delete Site specific variables.



## Requirements
The Sites functionality is build upon [Organic Groups][link-og].

Following modules are required to use the Sites functionality:

* [Organic Groups][link-og]



## Installation
Enable the Organic Groups Site Manager module.

Edit the node type settings of the types that should be Site types.
Enable:
* The Organic Groups > Group checkbox
* And the Site Manager > Site Type checkbox.



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

### Clear all cache for Site
Clear all cache for one site.

This function does not clear the cache itself, it calls all the implemented
hook_og_sm_site_cache_clear_all() hooks so modules can clear their specific
cached Site parts.

```php
og_sm_site_cache_clear_all($site);
```

### Site types
Get a list of node types that are Site node types:
```php
$site_types = og_sm_get_site_types();
```

### Check if node is a Site
The module provides helper functions to detect is a node or node type is a Site
node type:

Check if the given node is a Site type:
```php
$is_site = og_sm_is_site($node);
```

### Check if a node type is a Site type
Check if the given node type is a Site type:
```php
$is_site_type = og_sm_is_site_type($node_type);
```

### Set the breacrumb for a site
This is a wrapper around the og_set_breadcrumb.

```php
og_sm_set_breadcrumb($site, 'path/to/set/the/breadcrumb');
```

### Get the path to the Site homepage
Get the path to the homepage of a Site. This will return by default the path to
the detail page of the Site. Modules can implement
hook_og_dm_site_homepage_alter() to alter the path.

The function will return the path based on the given Site or, if no Site is
provided, the current Site (from OG context) will be used.

```php
$homepage_path = og_sm_site_homepage($site);
if ($homepage_path) {
  $homepage_url = url($homepage_path);
}
```

### Site content types
Helper function to get a list of site type objects that can be used to create
content within a site.

```php
$site_content_types = og_sm_content_get_types();
```

### Check if a content type can be used within a Site
Helper function to check if a given content type (by its name) can be used to
create content within a Site.

```php
$is_site_content_type = og_sm_content_is_site_content_type($type_name);
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


## Hooks
The og_sm module provides multiple hooks to make it easier to alter
functionality when a Site is involved.

> The hooks can be put in the `yourmodule.module` OR in the
> `yourmodule.og_sm.inc` file.
> The recommended place is in the yourmodule.og_sm.inc file as it keeps your
> .module file cleaner and makes the platform load less code by default.


### Clear all Site cache
When `og_sm_site_cache_clear_all()` is called, it will not clear any cache
itself. It will call all implemented `hook_og_sm_site_cache_clear_all()` hooks
so modules can clear the Site parts they have cached.

* `hook_og_sm_site_cache_clear_all($site)` : Cache clear call is called for the
  given Site.


### Site node type action hooks
The module triggers hooks when a node type is being added or removed as being a
Site node type.

* `hook_og_sm_site_type_add($type)` : Site node type is being added as a Site
  type.
* `hook_og_sm_site_type_remove($type)` : Site node type is no longer a Site
  type.


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
* `hook_og_sm_site_save($site)` : Act on a Site node being saved. Will be 
  triggered after a node is inserted or updated. It will always be called after 
  all the hook_site_insert/update hooks are processed.
* `hook_og_sm_site_delete($site)` : Site node being deleted.

There are also special post-action hooks available: the default action hooks 
(insert, update, save) are called during a DB transation. This means that it is
not possible to perform actions based data in the database as all SQL operations
are not committed yet.

To allow modules to interact with a Site node actions after the Site node & all 
queries by implemented hooks are stored in the database, following extra action 
hooks are provided:
 
* `hook_og_sm_site_post_insert($site)` : Site node is inserted in the DB and all 
  *_insert hooks are processed.
* `hook_og_sm_site_post_update($site)` : Site node is updated in the DB and all 
  *_update hooks are processed.
* `hook_og_sm_site_post_save($site)` : Site is inserted or updated in the DB and all 
  *_insert, *_update, and *_save hooks are processed.
* `hook_og_sm_site_post_delete($site)` : Site is deleted from DB and all 
  *_delete hooks are processed.


### Alter the Site homepage path.
The og_sm_site_homepage() function creates and returns the path (as string) to
the frontpage (homepage) of a Site. That homepage is by default the Site node
detail page (node/[site-nid]).

Implementations can require that the homepage links to a different page (eg.
group/node/NID/dashboard).

This alter function allows modules to alter that path.

```php
/**
 * Implements hook_og_sm_site_homepage_alter().
 *
 * @param string $path
 *   The current path to the Site homepage.
 * @param object $site
 *    The Site object to alter the homepage path for.
 */
function mymodule_og_sm_site_homepage_alter(&$path, $site) {
  $path = 'group/node/' . $site->nid . '/dashboard';
}
```




[link-og]: https://www.drupal.org/project/og

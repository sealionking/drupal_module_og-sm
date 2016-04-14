# Organic Groups : Site Content
This module provides content management functionality within a Site context.


## Functionality

### Create content within the Site context
Add new content within a Site context:
* `[site-path]/content/add` : Overview of all content types a user can create
  within a Site.
* `[site-path]/content/add/\[node-type]` : Add new content of a specific content
  type.


### TIP: Aliases for node/NID/edit & node/NID/delete
This module does not provide path alaises for `node/NID/edit` and
`node/NID/delete` paths.

Install the [Extended Path Aliases][link-path_alias_xt] module to provide this
functionality.


### Manage content within a Site
Two new Site admin pages are provided by this module:
* `[site-path]/admin/content` : Overview of all content within the Site.
* `[site-path]/admin/content/my` : Pvreview of all content created by the logged
  in user.


### Extend the Site admin menu
This module extends the Site administration menu (see og_sm_admin_menu).

It adds an item "Add content" to the menu. This is a link to the
`[site-path]/content/add` page. The menu items contains a submenu with links to
all the content creation forms for all content types the user has access to
within the Site.


### Extend the Site admin overview page
This module adds two items to the "Content" block on the `[site-path]/admin`
overview page:
* Add content
* Administer content



## Requirements
* Organic Groups Site Manager

Optional:
* Organic Groups Administration menu : this module adds extra menu items to
  quickly add new content.
* Organic Groups Path : all content related paths
  (`group/node/[nid]/content/add/...`) are rewritten to
  `[site-path]/content/add/...`.
* [Extended Path Aliases][link-path_alias_xt] : Will add an
  `[content-path]/edit` and `[content-path]/delete` alias for all Site content.



## Installation
1. Enable the module.



## API

### Check if user has access to create content type
Check if a user has access to create new content of the given type within a
Site.

Check for currently logged in user:
```php
$has_access = og_sm_content_add_content_access($site, 'article');
```

Check for provided user:
```php
$has_access = og_sm_content_add_content_access($site, 'article', $account);
```


### Get a list of node types a user can create
Get a list of content types the user can create within a Site:.

Get for the currently logged in user:
```php
$list = og_sm_content_get_types_by_site($site);
```

Get for the provided user:
```php
$list = og_sm_content_get_types_by_site($site, $account);
```


### Get the URI to create content within a Site
Create the URI to the node creation form for the specified Site and node type:

```php
$uri = og_sm_content_add_uri($site, 'article');
```


## Contributed module support
This module alters contributed modules so they support the new node/add paths:

* [addanother][link-addanother] : Make sure that the path to add another node
  within a Site stays within the current Site context.



[link-path_alias_xt]: https://www.drupal.org/project/path_alias_xt
[link-addanother]: https://www.drupal.org/project/addanother

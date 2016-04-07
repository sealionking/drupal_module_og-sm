# Organic Groups : Site Path
This module adds a field to the Site node form to set a Path prefix for the
Site.

That path is used as path alias for the Node and will be used to rewrite Site
related paths and URL's.



## Functionality
### Define a path per Site
Adds a Site Path field to the Site node form. That path will be used to create
content path aliases and to rewrite Site administration paths.


### URL alter
This module will automatically alter all outgoing URL's from
`group/node/[nid]/admin/…` to `[site-alias]/admin/…`.

It will transform incoming altered URL's back to its original path.


### URL query *destination* alter
It will check if an URL has a destination query parameter and will replace its
value by the proper path alias or URL outbound altered value.


### Update all aliases when a Site path changes
This module will update all aliases (content) when the
alias of the Site changes.


### Delete all aliases when a Site is deleted
This module will delete all existing aliases for content and pages related to
the Site.

This is done by deleting all aliases where the alias path starts with the Site
alias.


### Aliases for node/NID/edit and node/NID/delete
This module does not provide path alaises for `node/NID/edit` and
`node/NID/delete` paths.

Install the [Extended Path Aliases][link-path_alias_xt] module to provide this
functionality.



## Installation
1. Enable the module.
2. Configure the alias for content on admin/config/search/path/patterns:
   - Site node type : `[node:site-path]`.
   - Site content types : `[node:site-path]/...`

### Dependencies
* Organic Groups Site Manager



## API
### Get the path of a Site
Get the path of the given Site:
```php
$path = og_sm_path($site);
```


### Get a Site by its path
Get the Site object by its path:
```php
$site = og_sm_path_load_site($path);
```


### Set the path for a site
Pragmatically set the path for a given site.

This will:
- Set the path variable for the site.
- Set the path alias path for the given site.
- Trigger a hook to inform the platform about the path change.
```php
og_sm_path_set($site, 'my-site-path');
```

Triggering the `og_sm_site_path_changed` can be disabled:
```php
og_sm_path_set($site, 'my-site-path', FALSE);
```


### Site action hooks
The module watches actions taken place on Site nodes and triggers its own hooks
when an action happens:

* `hook_og_sm_site_path_change($site)` : Site node path has changed.

> NOTE : The hooks can be implemented in a `modulename.og_sm.inc` file
> instead of the modulename.module file.



[link-path_alias_xt]: https://www.drupal.org/project/path_alias_xt

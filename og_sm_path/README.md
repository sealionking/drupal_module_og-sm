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


### OG Context provider by Site path
Context provider to detect the Group context based on the Site path of the
current page.

It will check if:
- The path alias (if any) starts with a known Site path.
- The path (if no alias) starts with a known Site path.

Content created within the Site needs to get a path prefixed with the Site path.
See installation instructions.


## Installation
1. Enable the module.
2. Configure the alias for content on admin/config/search/path/patterns:
   - Overall or per Site content types : `[node:site-path]/...`
3. Setup the OG context providers on admin/config/group/context:
   - Enable the "**Site Path**" detection method.
   - Put the "**Site Path**" detection method on the **first** place.
   If the og_sm_context module is used, make sure that the "**Site Path**"
   method is always set first.
4. Delete and regenerate all content aliases.


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
- Check if the new path is different from the current if so it will:
  - Set the path variable for the site.
  - Trigger a hook `og_sm_site_path_change` to inform the platform about the
    path change.
```php
og_sm_path_set($site, 'my-site-path');
```

Triggering the `og_sm_site_path_change` can be disabled:
```php
og_sm_path_set($site, 'my-site-path', FALSE);
```


### Site action hooks
The module watches actions taken place on Site nodes and triggers its own hooks
when an action happens:

* `hook_og_sm_site_path_change($site)` : Site node path has changed.

> The hooks can be put in the `yourmodule.module` OR in the
> `yourmodule.og_sm.inc` file.
> The recommended place is in the yourmodule.og_sm.inc file as it keeps your
> .module file cleaner and makes the platform load less code by default.



[link-path_alias_xt]: https://www.drupal.org/project/path_alias_xt

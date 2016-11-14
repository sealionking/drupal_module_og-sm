# Organic Groups : Site Path
This module adds a field to the Site node form to set a Path prefix for the
Site.

That path is used as path alias for the Node and will be used to rewrite Site
related paths and URL's.



## Functionality
### Define a path per Site
Adds a Site Path field to the Site node form. That path will be used to create
content path aliases and to rewrite Site administration paths.

Changing existing Site paths can be limited by global and Site roles.


### URL alter
This module will automatically alter all outgoing URL's from:
* `group/node/[nid]/admin/…` to `[site-path]/admin/…`.
* `system/ajax` to `[site-path]/system/ajax` (only if the URL is created within
  an active Site context).
* `views/ajax` to `[site-path]/views/ajax` (only if the URL is created within
  an active Site context).

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


### OG Context provider by GET parameter
Context provider to detect if a Group context was set using a GET parameter with
the name "og_sm_context_site_id". This GET parameter is used to pass any context
detaction during the URL inbound alter of system paths starting with a site-path
prefix (eg. [site-path]/system/ajax, [site-path]/views/ajax).



## Requirements
* Organic Groups Site Manager
* Organic Groups Site Variable
* [Pathauto](https://www.drupal.org/project/pathauto)
* [Token](https://www.drupal.org/project/token)



## Installation
1. Enable the module.
2. Configure the alias for content on admin/config/search/path/patterns:
   - Overall or per Site content types : `[node:site-path]/...`
3. Setup the OG context providers on admin/config/group/context:
   - Enable the "**Site Path**" detection method.
   - Put the "**Site Path**" detection method on the **first** place.
   If the og_sm_context module is used, make sure that the "**Site Path**"
   method is always set first.
4. Grant user roles access to edit existing Site paths.
5. Grant organic group roles access to edit existing Site paths.
6. Update all existing Sites: edit them and set their Site Path value.
7. Delete and regenerate all content aliases.



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


## Hooks
### Site action hooks
The module watches actions taken place on Site nodes and triggers its own hooks
when an action happens:

* `hook_og_sm_site_path_change($site, $path_old, $path_new)` : Site node path 
  has changed.

> The hooks can be put in the `yourmodule.module` OR in the
> `yourmodule.og_sm.inc` file.
> The recommended place is in the yourmodule.og_sm.inc file as it keeps your
> .module file cleaner and makes the platform load less code by default.


### Alter a list of ajax paths.
Hook to alter a list of ajax paths that will be rewritten to have site context.

```php
function hook_og_sm_ajax_paths_alter(&$paths) {
  $paths[] = 'media/browser';
}
```


[link-path_alias_xt]: https://www.drupal.org/project/path_alias_xt

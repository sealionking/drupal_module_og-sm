# Organic Groups : Site theme
This module allows to choose a theme per Site.


## Functionality
* Define what themes a Site can choose from.
* Define the default theme (fallback).
* Set a theme per Site.
* Set visibility of theme components, currently only breadcrumb 
  supported
* Breadcrumb configuration per theme within a Site.
    * Append the page title to the breadcrumb trail
    * Override the root of the breadcrumb trail



## Requirements
* Organic Groups Site Manager
* Organic Groups Site Variable



## Installation
1. Enable the module.
2. Open the admin settings (admin/config/administration/theme) and
   choose one of the enabled themes for your Site.
3. Open the Site theme settings (`[site-path]/admin/theme`) and select the theme
   for the Site.



## API
### Set the Site theme programmatically
The Site theme settings are stored in an og_sm_variable.

Setting the theme can be done by changing the `theme` variable for a Site:
```php
og_sm_variable_set($site, 'theme', 'bartik');
```



## Hooks
Two hooks are available to alter the theme settings behaviour:

* `hook_og_sm_theme_themes_site_alter(&$themes, $context)` : Alter the list of
  allowed site themes for a Site.
* `hook_og_sm_theme_themes_page_alter(&$theme_groups)` : Alters theme operation
  links for a Site.

> The hooks can be put in the `yourmodule.module` OR in the
> `yourmodule.og_sm.inc` file.
> The recommended place is in the yourmodule.og_sm.inc file as it keeps your
> .module file cleaner and makes the platform load less code by default.

# Organic Groups : Site Variable
Module to support site specific settings by storing them in a separate table and
link them to the Site they belong to.

The difference between this module and og_variables is that the og_variables
module overwrites global variables, while the og_sm_variable module adds new
variables.


## Functionality
This module provides:
* API to set and get a single variable per Site.
* Get all variables at once for a Site.
* Get for all sites the values of a specific variable name.
* Delete all variables at once for a Site.
* Caching to speed up variable access.
* Mechanism to define default variables to set when a new Site is created.



## Requirements
* Organic Groups



## Installation
1. Enable the module. Variables are set by modules that store their settings in
   the variables table.


## API

### Get a variable value
Get a variable by its name:

```php
$value = og_sm_variable_get($site_nid, 'variable_name');
```

It is not required to pass a default value, if the variable is not set NULL will
be returned. You can pass in a default value if the value does not exists yet:
```php
$value = og_sm_variable_get($site_nid, 'variable_name', 'default value');
```

### Set a variable value
Set a variable by its name:

```php
og_sm_variable_set($site_nid, 'variable_name', 'variable value');
```

### Delete a variable
A variable can be removed from the variables table:

```php
og_sm_variable_delete($site_nid, 'variable_name');
```

### Get all variables for a site
Get all variables at once for a site. The values will be sorted by the variable
name. The array will be keyed by the variable names.

```php
$variables = og_sm_variable_get_all($site_nid);
```

### Delete all variables for a site
Delete all variables belonging to a Site at once.

```php
og_sm_variable_delete_all($site_nid);
```

### Get variable values for all sites
This will get an array of all values set for a specific variable name keyed by
the Site node id.

```php
$values = og_sm_variable_get_all_sites($name);
```

### Hooks to set the default variables for a new Site
This module provides hooks to define the default variable values to set when a
new Site is created.

> The hooks can be put in the `yourmodule.module` OR in the
> `yourmodule.og_sm.inc` file.
> The recommended place is in the yourmodule.og_sm.inc file as it keeps your
> .module file cleaner and makes the platform load less code by default.

#### hook_og_sm_variable_defaults($site)
This hook is used to define default variables for the Site that is created and
saved in the database.

The hook should return an array of values keyed by their variable name.

```php
function my_module_og_sm_variable_defaults($site) {
  $items = array(
    'theme' => 'bartik',
    'og_sm_content_article_comment' => COMMENT_NODE_OPEN,
    'og_sm_content_article_machine_name' => 'news',
    'og_sm_content_article_name' => 'news',
    'og_sm_content_article_name_plural' => 'news',
  );

  return $items;
}
```

#### hook_og_sm_variable_defaults_alter(&$items, $site)
Use this hook to alter variables as defined by other modules.

```php
function my_module_og_sm_variable_defaults_alter(&$items, $site) {
  $items['theme'] = 'my-theme';
}
```

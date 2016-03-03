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


## Installation
Enable the module. Variables are set by modules that store their settings in the
variables table.

### Dependencies
* Organic Groups


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

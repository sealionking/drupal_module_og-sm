# Organic Groups : Features
Adds an API and interface to disable/enable features per Site.



## Functionality
### Detect features
Provides a hook system to allow modules to provide this module information about
features.


### Enable/Disable features
Interface per Site to enable/disable available features.


### API
API to retrieve the status of a feature.



## Requirements
* Organic Groups Site Manager
* Organic Groups Site Variable



## Installation
1. Enable this module.
2. Define the features for a module.



## API
### Get information of all features
Get information about all features.

```php
$info = og_sm_feature_info();
```


### Check if a feature exists
Check if a feature exists by its name.

```php
$exists = og_sm_feature_exists('feature name');
```


### Enable a feature for a Site
Enable a feature for the given Site.

```php
og_sm_feature_site_enable($site, 'feature name');
```


### Disable a feature for a Site
Enable a feature for the given Site.

```php
og_sm_feature_site_disable($site, 'feature name');
```


### Check if feature is enabled
Check if a feature is enabled for a given Site.

```php
$is_enabled = og_sm_feature_site_is_enabled($site, 'feature name');
```



## Hooks
> The hooks can be put in the `yourmodule.module` OR in the
> `yourmodule.og_sm.inc` file.
> The recommended place is in the yourmodule.og_sm.inc file as it keeps your
> .module file cleaner and makes the platform load less code by default.


### Inform the platform about feature(s)
The module provides a hook to allow modules to inform about their feature(s).

```php
/**
 * Inform the platform about the available feature(s).
 *
 * @return array
 *   Array containing the information about the feature(s).
 *   The Array has following content:
 *   - title : The feature title. Do not translate the title, this will be done
 *     by the og_sm_feature module.
 *   - description : The feature description. Do not translate the description,
 *     this will be done by the og_sm_feature module.
 *   - configuration : An optional path to change the configuration of the
 *     feature specific for the Site. The path should be specified without the
 *     group/node/NID/ path prefix as it is appended automatically.
 *   - default status : The default enabled status (TRUE/FALSE) of a feature
 *     when a new Site is created.
 */
function hook_og_sm_feature_info() {
  $items = array();

  $items['news'] = array(
    'title' => 'News',
    'description' => 'News content and overviews.',
    'configuration' => 'admin/feature/news',
    'default status' => TRUE,
  );

  return $items;
}
```


### Alter the feature(s) info
Hook to alter the information collected using the hook_og_sm_feature_info()
hook.

```php
/**
 * Alter the features information.
 *
 * @param array $info
 *   The information collected by the hook_og_sm_feature_info() hook.
 */
function hook_og_sm_feature_info_alter(&$info) {
  $info['news']['configuration'] = 'admin/feature/news-test';
  $info['news']['default status'] = FALSE;
}
```

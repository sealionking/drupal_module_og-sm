# Organic Groups : Site Menu
This module adds support to have Site specific menu (router) items in the 
Drupal menu system.




## Functionality
Modules can require to have Site-specific menu items with Site specific 
custom paths. This module provides the necessary hooks to provide those items.
It passes the collected items to Drupal using a hook_menu() implementation.



## Requirements
* og_sm




## Installation
1. Enable the module.
2. Implement `hook_og_sm_menu()` and `hook_og_sm_menu_alter()` in the modules 
   who provide custom menu items.




## API
### Collect all menu items for a single Site
This will call all implemented hook_og_sm_menu() hooks and collect all the 
menu items for the given Site node object.
Once the collection has finished, the hook_og_sm_menu_alter() hook is called
to allow modules to alter menu items for the passed Site.

```php
$site_menu_items = og_sm_menu_menu_site($site);
```



## Hooks
This module provides hooks to define the default variable values to set when a
new Site is created.

> The hooks can be put in the `yourmodule.module` OR in the
> `yourmodule.og_sm.inc` file.
> The recommended place is in the yourmodule.og_sm.inc file as it keeps your
> .module file cleaner and makes the platform load less code by default.


### hook_og_sm_menu($site)
Provide Drupal menu items (see [hook_menu()][link-hook-menu] based on the 
given Site node.

Modules can require to have unique menu items for specific sites (path prefix,
only when a Site feature is active...).

This hook is called by the og_sm_menu module to collect such items. The
collected data is then bundled and passed to the Drupal menu.

The hooks should return menu items in the same structure as 
[hook_menu()][link-hook-menu].

```php
function hook_og_sm_menu($site) {
  return array(
    'group/node/' . $site->nid . '/article' => array(
      'title' => 'Articles',
      'page callback' => 'og_sm_menu_test_article_page',
      'access callback' => TRUE,
    ),
    'group/node/' . $site->nid . '/news' => array(
      'title' => 'News',
      'page callback' => 'og_sm_menu_test_news_page',
      'access callback' => TRUE,
    ),
  );
}
```


### hook_og_sm_menu_alter(array &$items, $site)
Alter the menu items collected for a singe Site.

Once all menu items for a specific site are collected by calling the 
`hook_og_sm_menu()` modules are given the opportunity to alter the collection
of menu items for a single Site.

```php
function hook_og_sm_menu_alter(array &$items, $site) {
  $items['group/node/' . $site->nid . '/article']['page callback'] = 'og_sm_menu_test_article_page_altered';
}
```




[link-hook-menu]: https://api.drupal.org/api/drupal/modules%21system%21system.api.php/function/hook_menu/7.x

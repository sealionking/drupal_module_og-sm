# Organic Groups : Site Global Roles
This module adds the functionality for users within a Site to get global role(s)
only when they have a Site role that gives access to the Global one.



## Functionality
* Link Site roles to Global roles.
* Users get the Global roles (and their permissions) when they have the linked
  Site role within an active Site context.



## Requirements
* og_sm



## Installation
1. Enable the module.
2. Create global roles and assign them the proper global permissions.
3. Create Site roles and assign them proper Site permissions.
4. Go to the Admin > Configuration > Organic Groups > OG Global Roles overview
   and assign what Global roles a Group role should get when within a Site
   context.



## API

### Check user permission within a site context.
Check if the passed user has a global permission within a site context.
This function is based of `user_access()`.
```php
$has_access = og_sm_global_roles_user_access($site, 'access content', $account);
```

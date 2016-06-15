# Organic Groups : Site User Profile
This module provides user profiles within a Site context.


## Functionality

### Permissions for viewing site user profiles
* Access site user profiles : Allows a user to view other users group profiles.

### Context detection: Site User Profile
This module provides context detection for site user profiles.

The site user profile provider checks if a path starts with `profile/ID`. If so it
will load the profile object and will return the related Site nid as context.

### Pathauto integration for profiles
This module provides integration to create path aliases for site profile pages.

To make use of this feature the pathauto module needs to be enabled.

### TIP: Aliases for profile/ID/modify
This module does not provide path aliases for `profile/ID/modify` paths.

Install the [Extended Path Aliases][link-path_alias_xt] module to provide this
functionality.

## Requirements
* Organic Groups Site Manager

## Installation
1. Enable the module.
2. Configure the alias for site user profiles on admin/config/search/path/patterns:
   - Site User Profile paths : `[og_sm_profile:node:site-path]/...`
3. Regenerate all profile aliases.
4. Setup the OG context providers on admin/config/group/context:
  - Enable the "**Site User Profile**" detection method.
5. Grant user roles access to access group user profiles.



## API

### Create a site user profile.

```php
$profile = og_sm_profile_create($site_nid, $uid);
```

### Delete a site user profile.

```php
$profile = og_sm_profile_delete($site_nid, $uid);
```

### Loads a site user profile.

```php
$profile = og_sm_profile_load($profile_id);
```

### Loads multiple site user profiles.

```php
$profile = og_sm_profile_load_multiple($profile_ids);
```

### Loads a site user profile based on a user id and site id.

```php
$profile = og_sm_profile_load_by_uid($site_id, $user_id);
```

### Loads the site user profile based on the current context.

```php
$profile = og_sm_profile_load_from_context();
```

[link-path_alias_xt]: https://www.drupal.org/project/path_alias_xt

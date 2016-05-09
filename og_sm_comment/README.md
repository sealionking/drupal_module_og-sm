# Organic Groups : Site Comment
This module provides comment management functionality within a Site context.


## Functionality

### Extra permissions for comment actions
The Site Comment module adds extra permission to manage comments. The following
permissions are added :
* Delete own comments : Allows the user to delete his/her own comments.
* Delete all comments : Allows the user to delete all comments.
* Edit all comments : Allows the user to edit all comments.

These permissions can be used on global level and site level.


### Context detection: Site Comment
This module provides context detection for site comments.

The site comment provider checks if a path starts with `comment/CID`. If so it
will load the comment's node and checks if it is a Site or a Site Content. If so
it will return the related Site nid as context.

### Pathauto integration for comments
This module provides integration to create path aliases for comment pages.

To make use of this feature the pathauto module needs to be enabled.

### TIP: Aliases for comment/CID/edit and comment/CID/delete
This module does not provide path aliases for `comment/CID/edit` and
`comment/CID/delete` paths.

Install the [Extended Path Aliases][link-path_alias_xt] module to provide this
functionality.


### Manage comments within a Site
A new Site admin page is provided by this module:
* `[site-path]/admin/comments` : Overview of all comments within the Site.

## Requirements
* Organic Groups Site Manager

## Installation
1. Enable the module.



## API

### Find the site on which this comment was made.
Find the site node that is linked to the node on which the comment was made.

```php
$has_access = og_sm_comment_get_site($comment);
```


[link-path_alias_xt]: https://www.drupal.org/project/path_alias_xt

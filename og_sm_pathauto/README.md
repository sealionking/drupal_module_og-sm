# Organic Groups : Site Pathauto
This module uses the pathauto Site node alias to create aliases for all Site
content or to rewrite the Site administration pages URL's so they always contain
the Site alias.



## Functionality
### URL alter
This module will automatically alter all outgoing URL's from
`group/node/[nid]/admin/…` to `[site-alias]/admin/…`.

It will transform incoming altered URL's back to its original path.


### URL query *destination* alter
It will check if an URL has a destination query parameter and will replace its
value by the proper path alias or URL outbound altered value.


### Update all aliases when a Site alias changes
This module will update all aliases (content and administration pages) when the
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



## Installation
1. Enable the module.
2. Configure the alias for "Site administration paths" on
   admin/config/search/path/patterns.

### Dependencies
* Organic Groups Site Manager



[link-path_alias_xt]: https://www.drupal.org/project/path_alias_xt

# Organic Groups : Site Pathauto
This module provides extra pathauto functionality to create aliases for all Site
related pages that are not content (e.g. administration pages).

The aliased path is then used to get the Site context.



## Functionality
### Aliases for group administration pages.
This module will automatically replace all paths that start with:

* **group/node/%nid**(/rest of path)

and create an alias like:

* **\[node:site-path\]**(/rest of path).

### Update all aliases when a Site alias changes
This module will update all aliases (content & administration pages) when the
alias of the Site changes.



## Installation
1. Enable the module.
2. Configure the alias for "Site administration paths" on
   admin/config/search/path/patterns.

### Dependencies
* Organic Groups

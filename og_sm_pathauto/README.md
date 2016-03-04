# Organic Groups : Site Pathauto
This module provides extra pathauto functionality to create aliases for all Site
related pages that are not content (e.g. administration pages).

The aliased path is then used to get the Site context.

## Functionality
This module will automatically replace all paths that start with:

* **group/node/%nid**(/rest of path)

and create an alias like:

* **\[node:site-path\]**(/rest of path).

# Organic Groups : Site Context
The Site Context module provides context detection based on the Site node path
alias.

Each site gets it's own alias based on its name.

Example:
* Site name: My Site
* Site path: my-site

Content created within the Site needs to get a path prefixed with the Site path.

Example:
* Content type: news
* Content title: My News
* Content path: my-site/news/my-news


## Functionality
This module supports this by providing following functionality:

* og_context provider to detect the Group context based on the alias of the
  current page.
* The context provider will also detect Site context if a custom menu path
  starts with the Site path.


## Installation
1. Enable the module.
2. Configure the path alias for Site node types.

   Example:

   ```
   [node:title]
   ```

3. Configure the path alias for Site Content node types. Use `[node:site-path]` in
   front of the content path.

   Example:

   ```
   [node:site-path]/[node:type]/[node:title]
   ```

4. Delete and regenerate all content aliases.

5. Configure the og_context providers, enable the "Site Manager" detection
   method and put it on the first place.


## Dependencies
* Organic Groups Site Manager

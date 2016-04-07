# Organic Groups : Site Context
The Site Context module provides context detection based on:
* Site node path alias.
* Site Content (site or site content).
* Site Administration pages.


## Functionality
This module supports this by providing following context detection:

### Site node path alias
Context provider to detect the Group context based on the alias of the current
page. The context provider will also detect Site context if a custom menu path
starts with the Site path.

Each site gets it's own alias based on its name.

Example:
* Site name: My Site
* Site path: my-site

Content created within the Site needs to get a path prefixed with the Site path.

Example:
* Content type: news
* Content title: My News
* Content path: my-site/news/my-news


### Site Content
This provider checks if a path starts with `node/NID`. If so it will load the
node and checks if it is a Site or a Site Content. If so it will return the
related Site nid as context.


### Site Administration pages
All Site Administration pages have a router path like `group/node/NID/…`. This
context provider will detect these paths and use the `NID` to check if this is a
Site node.



## Installation
1. Enable the module.
2. Configure the path alias for Site node types.

   Example:

   ```
   [node:site-path]
   ```

3. Configure the path alias for Site Content node types. Use `[node:site-path]` in
   front of the content path.

   Example:

   ```
   [node:site-path]/[node:type]/[node:title]
   ```

4. Configure the og_context providers:
   * Enable the "**Site Content**" detection method and put it on the **first**
     place.
   * Enable the "**Site Administration**" detection method and put it on the
     **second** place.
   * Enable or disable other context providers. Put them lower then the Site
     context providers.

5. Delete and regenerate all content aliases.


> **NOTE :**
> The **Site Content** provider replaces the "Node" context provider as provided
> by the og_context module. This provider can be disabled.

> **TIP :**
> If the og_sm_content module is used, the "URL (content create)" is no longer
> required to detect the context as provided by the `og_group_ref` get
> parameter.



## Dependencies
* Organic Groups Site Manager
* Organic Groups Context (part of Organic Groups module suite).

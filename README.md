# Organic Groups : Sites
This module provides support to setup a platform supporting multiple (sub)sites
based on [Organic Groups][link-og] (OG) functionality.

The usage of OG allows to share users between sites.


## Functionality
This module and its submodules adds functionality to support:

* Support for Group types to become sites enabled (Site).
* Support for Group Content types (Site Content).
* Support for User profile & settings per Site (Site User).
* Theme settings per Site (different theme or same theme with different
  settings).
* Taxonomy terms per Site.
* Automatic path aliasing with the Site alias as staring point.
* Access to Site content based on the publication status of the Site they
  belong to.
* Site settings.
* Site administration.
* Site features: enable functionality per site (eg. Site A has blogs, Site B
  not).
* Site Content settings per Site (eg. Site A enables commenting on Blog posts,
  Site B not).
* Rename Site Content types per site.
* ...


## Installation
Enable the Organic Groups Site Manager module.

Edit the node type settings of the types that should be Site types.
Enable:
* The Organic Groups > Group checkbox
* And the Site Manager > Site Type checkbox.

### Dependencies
The Sites functionality is build upon [Organic Groups][link-og].

Following modules are required to use the Sites functionality:

* [Organic Groups][link-og]



## API

### Check if content is a Site
The module provides helper functions to detect is a node or node type is a Site
node type:

* og_sm_is_site($node) : Check if the given node is a Site type.
* og_sm_is_site_type($node_type) : Check if the given node type is a Site type.


### Site action hooks
The module watches actions taken place on Site nodes and triggers its own hooks
when an action happens:

* hook_og_sm_site_prepare($site) : Site node being prepared to being shown on a
  node add/edit form.
* hook_og_sm_site_presave($site) : Site node being prepared to be inserted or
  updated in the database.
* hook_og_sm_site_view($site, $view_mode, $langcode) : Site node being prepared
  to being shown on the screen.
* hook_og_sm_site_insert($site) : Site node being inserted.
* hook_og_sm_site_update($site) : Site node being updated.
* hook_og_sm_site_delete($site) : Site node being deleted.




## Usage




[link-og]: https://www.drupal.org/project/og

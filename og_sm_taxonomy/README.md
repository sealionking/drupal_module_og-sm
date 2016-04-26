# Organic Groups : Site Taxonomy
Module to support sharing a common vocabulary in multiple Sites. Each Site has
its own taxonomy terms.


## Functionality
This module provides:
* Support one global vocabulary with Site specific terms.
* Manage terms per Site.
* Select only from terms within the Site when creating content.



## Requirements
* Organic Groups Site Manager
* Taxonomy



## Installation
1. Enable the module.
2. Create a global vocabulary.
3. Add the Organic Groups audience field to the vocabulary.
4. Grant Organic Groups roles the proper taxonomy permissions.



## API
### Get all the vocabulary names
Get a list of all vocabulary names of the vocabularies who have an Organic
Groups Audience field.

Will return the vocabulary labels keyed by their machine name.

```php
$names = og_sm_taxonomy_get_vocabulary_names();
```


### Get all vocabularies
Get all the vocabulary objects that have the Group Audience field.

Will return the vocabulary objects keyed by their machine name.

```php
$vocabularies = og_sm_taxonomy_get_vocabularies();
```


### Check if a vocabulary has the OG Audience field
Check if the given vocabluary machine name is a vocabulary with the Organic
Groups Audience field.

```php
$has_og_audience = og_sm_taxonomy_is_vocabulary('machine_name');
```


### Get all the Sites a Term belongs to
Get all the Site nodes a Taxonomy Term belongs to.

```php
$sites = og_sm_taxonomy_term_get_sites($term);
```


### Get the Site a Term belongs to
Get the Site node a Taxonomy Term belongs to.

If a term belongs to multiple Sites, only the first will be returned.

```php
$site = og_sm_taxonomy_term_get_site($term);
```


### Check if a term is used within Site(s)
Check if the Term is used within one or more Sites.

```php
$is_site_term = og_sm_taxonomy_term_is_site_term($term);
```


### Check if a term belongs to a Site
Check if the term belongs to the given Site object.

```php
$is_member = og_sm_taxonomy_term_is_site_member($term, $site);
```

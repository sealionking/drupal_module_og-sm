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
### Get all vocabularies
Get all the vocabulary objects that have the Group Audience field.

```php
$vocabularies = og_sm_taxonomy_get_vocabularies();
```

### Check if vocbulary has the OG Audience field
Check if the given vocabluary machine name is a vocabulary with the Organic
Groups Audience field.

```php
$has_og_audience = og_sm_taxonomy_is_vocabulary('machine_name');
```
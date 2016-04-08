# Organic Groups : Theme
This module allows to choose a theme per Site.


## Functionality
* Define what themes a Site can choose from.
* Define the default theme (fallback).
* Set a theme per Site.


## Installation
1. Enable the module.
2. Open the admin settings (admin/config/administration/theme) and
   choose one of the enabled themes for your Site.
3. Open the Site theme settings (`[site-path]/admin/theme`) and select the theme
   for the Site.

### Dependencies
* Organic Groups Site Manager


## API
### Set the Site theme programmatically
The Site theme settings are stored in an og_sm_variable.

Setting the theme can be done by changing the `theme` variable for a Site:
```php
og_sm_variable_set($site, 'theme', 'bartik');
```
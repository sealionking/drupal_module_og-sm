# Organic Groups : Site Configuration
Module to support site specific settings by storing them in a separate table and
link them to the Site they belong to.


## Functionality
This module provides no helper functions, site configuration should be fetched
just like normal configuration, config overrides will be loaded based on the
current site context.

In case you want to load site configuration outside of a site context you could
use the "og_sm.config_factory_override" service.

Site configuration is mostly based on the config override system, the most
important difference is that it uses a custom config storage table, this prevents
the configuration from being exported/imported.



## Requirements
* Organic Groups



## Installation
1. Enable the module.



## API
All the logic for fetching configuration is done in the background so should be
no concern of the developer.

To store configuration within a site context the configuration form should be
extended from the `SiteConfigFormBase` class.
Using the form with a route that allows determining site context will result in
configuration saved under that site context. See `og_sm_config_test` module for a
simple implementation.

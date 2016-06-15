# Changelog
All Notable changes to **Organic Groups Site Manager** module suite.




## [7.x-1.3]
### Added
- DMOGSM-57 : Added extra permissions so Site Users can get granted to delete
  Site terms.


### Fixed
- WEBSECOND-248 : Added Views exposed filters support for og_sm_taxonomy.
- DMOGSM-60 : Added fix for entityreference_prepopulate and Site taxonomy terms
  that are created with hidden group fields.




## [7.x-1.2]
### Added
- DMOGSM-12 : Functionality to enable/disable & configure features per Site.




## [7.x-1.1]
### Added
- DMOGSM-37 : Added permissions to limit access to change the path of existing
  Sites.
- DMOGSM-41 : Added the og_sm_comment module.
- DMOGSM-13 : Added the og_sm_taxonomy module.
- DMOGSM-12 : Added functionality to define default Site variable values when a
  new Site is created.


### Changed
- DMOGSM-36 : Changed storing the mapping between Global roles and Site roles by
  role name instead of Role ID. Makes it easier to export the mapping using
  features (strongarm).


### Fixed
- DMOGSM-16 : Added support for og_variables to the admin menu.
- DMOGSM-16 : Removed the default OG UI admin overview page as this is replaced
  by the functionality provided by og_sm_admin_menu.




## [7.x-1.0]
First stable release of the og_sm module.


### Added
- DMOGSM-2 : Site administration overview.
- DMOGSM-7 : Identify node (types) as being a Site node/type.
- DMOGSM-8 : Site management menu that replaces the Administration menu.
- DMOGSM-9 : Site Access based on Site published status.
- DMOGSM-11 : Added the og_sm_content module to create & manage Site content
  within the Site context.
- DMOGSM-14 : Site variable module to store Site specific configuration.
- DMOGSM-17 : Site content path aliases based on the Site path alias.
- DMOGSM-19 : Added the og_sm_theme module to configure a theme per Site.
- DMOGSM-26 : Added the og_sm_global_roles module to grant users global roles
  when they have a specific Site role (when a Site context is active).
- DMOGSM-27 : Added extra permission and node_access implementation to grant
  Site roles admin access to all Site content.
- DMOGSM-31 : Added extra og_context handler to detect the Site context based on
  the node/\[nid](/\[action]) paths.
- DMOGSM-35 : Added new module og_sm_path that contains all logic about hosting
  a subsite on its own path (eg. `http://domain/[site-path]`).
- DMOGSM-35 : Added OG Context Site Path handler to detect context based on the
  current path (or its alias) starting with a known Site Path value.
- DMOGSM-35 : Added the Site Path field to the extra fields so the placement in
  the Site node forms can be altered.
- DMOGSM-39 : Added access to the authoring data of a node for users with
  "administer site" permission within a Site.
- PPL-310 : Rewrite the paths of ajax callbacks to they get the proper Site
  context.




[Unreleased]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/develop%0Dmaster
[7.x-1.3]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.3%0D7.x-1.2#diff
[7.x-1.2]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.2%0D7.x-1.1#diff
[7.x-1.1]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.1%0D7.x-1.0#diff
[7.x-1.0]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/commits/tag/7.x-1.0

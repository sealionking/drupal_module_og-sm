# Changelog
All Notable changes to `digipolisgent/drupal_module_og-sm`.


## [Unreleased]
### Added
- DMOGSM-11 : Added the og_sm_content module to create & manage Site content
  within the Site context.
- DMOGSM-26 : Added the og_sm_global_roles module to grant users global roles
  when they have a specific Site role (when a Site context is active).
- DMOGSM-31 : Added extra og_context handler to detect the Site context based on
  the node/\[nid](/\[action]) paths.



## [7.x-1.0-alpha3]
### Fixed
- DMOGSM-7 : Broken tests due to changed context detection callback name.
- DMOGSM-7 : Broken tests due to notices when testing with non-existing node
  ID's'.
- DMOGSM-8 : Content types with "-" in machine name where always filtered in the
  Site menu.



## [7.x-1.0-alpha2]
### Fixed
- DMOGSM-7 : Fixed context detection when on Site administration pages by adding
  an extra context detector based on paths like `group/node/[nid]`.



## [7.x-1.0-alpha1]
### Added
- DMOGSM-2 : Site administration overview.
- DMOGSM-7 : Identify node (types) as being a Site node/type.
- DMOGSM-8 : Site management menu that replaces the Administration menu.
- DMOGSM-9 : Site Access based on Site published status.
- DMOGSM-14 : Site variable module to store Site specific configuration.
- DMOGSM-17 : Site content path aliases based on the Site path alias.



[Unreleased]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/develop%0Dmaster
[7.x-1.0-alpha3]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.0-alpha3%0D7.x-1.0-alpha2#diff
[7.x-1.0-alpha2]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.0-alpha2%0D7.x-1.0-alpha1#diff
[7.x-1.0-alpha1]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/commits/tag/7.x-1.0-alpha1

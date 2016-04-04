# Changelog
All Notable changes to `digipolisgent/drupal_module_og-sm`.


## [Unreleased]
### Fixed
- DMOGSM-11 : Added support for the addanother module so it uses the proper
  content creation paths within a Site context.
- PPL-309 : Fixed logout link in the admin bar + fixed home link in the
  responsive version of the admin bar.
- DMOGSM-33 : Fixed responsive version of the node/add menu.


## [7.x-1.0-alpha5]
### Fixed
- DMOGSM-17 : Fixed broken global roles due to using url_outbound/inbound_alter.



## [7.x-1.0-alpha4]
### Added
- DMOGSM-11 : Added the og_sm_content module to create & manage Site content
  within the Site context.
- DMOGSM-26 : Added the og_sm_global_roles module to grant users global roles
  when they have a specific Site role (when a Site context is active).
- DMOGSM-27 : Added extra permission and node_access implementation to grant
  Site roles admin access to all Site content.
- DMOGSM-31 : Added extra og_context handler to detect the Site context based on
  the node/\[nid](/\[action]) paths.
- DMOGSM-17 : Removed the usage of pathauto for the `group/node/[NID]/admin/…`
  and `group/node/[nid]/content/add…` paths. Using url_outbound/inbound_alter to
  cover also dynamic paths. This replaces also the destination query parameter
  by its alias or altered URL.



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
[7.x-1.0-alpha5]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.0-alpha5%0D7.x-1.0-alpha4#diff
[7.x-1.0-alpha4]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.0-alpha4%0D7.x-1.0-alpha3#diff
[7.x-1.0-alpha3]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.0-alpha3%0D7.x-1.0-alpha2#diff
[7.x-1.0-alpha2]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.0-alpha2%0D7.x-1.0-alpha1#diff
[7.x-1.0-alpha1]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/commits/tag/7.x-1.0-alpha1

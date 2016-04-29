# Changelog
All Notable changes to **Organic Groups Site Manager** module suite.



## [7.x-1.0]
### Deleted
- DMOGSM-42: Removed the no longer required og_sm_pathauto module.



## [7.x-1.0-alpha8]
### Fixed
- DMOGSM-40 : Fixed determining when to use the admin theme.



## [7.x-1.0-alpha7]
### Added
- DMOGSM-35 : Added the Site Path field to the extra fields so the placement in
  the Site node fomrs can be altered.
- PPL-310 : Rewrite the paths of ajax callbacks to they get the proper Site
  context.
- DMOGSM-39 : Added access to the authoring data of a node for users with
  "administer site" permission within a Site.

### Updated
- DMOGSM-38 : Updated documentation.

### Fixed
- PPL-365 : Added missing space between the action links in the administer
  content page.
- PPL-375 : Fixed the og_sm_content_type views handler.



## [7.x-1.0-alpha6]
### Added
- DMOGSM-19 : Added the og_sm_theme module to configure a theme per Site.
- DMOGSM-35 : Added new module og_sm_path that contains all logic about hosting
  a subsite on its own path (eg. `http://domain/[site-path]`).
- DMOGSM-35 : Added OG Context Site Path handler to detect context based on the
  current path (or its alias) starting with a known Site Path value.

### Changed
- DMOGSM-35 : Replaced the `og_sm_site_path()` function by `og_sm_path()`.
- DMOGSM-35 : Replaced the `og_sm_site_load_by_path()` function by
  `og_sm_path_load_site()`.

### Removed
- DMOGSM-35 : Removed the og_sm_pathauto module, all logic about using Site
  paths is now in the og_sm_path module.
- DMOGSM-35 : Removed the `og_sm_site_path_permission_access()` function.
- DMOGSM-35 : Removed the OG Context Site Alias handler as it is replaced by
  the Site Path handler.

### Fixed
- DMOGSM-11 : Added support for the addanother module so it uses the proper
  content creation paths within a Site context.
- PPL-309 : Fixed logout link in the admin bar + fixed home link in the
  responsive version of the admin bar.
- DMOGSM-33 : Fixed responsive version of the node/add menu.
- DMOGSM-35 : Fixed auto path alias generating by setting the Site path as a
  separate field instead of relying on pathauto to generate one.



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
[7.x-1.0-alpha8]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.0%0D7.x-1.0-alpha8#diff
[7.x-1.0-alpha8]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.0-alpha8%0D7.x-1.0-alpha7#diff
[7.x-1.0-alpha7]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.0-alpha7%0D7.x-1.0-alpha6#diff
[7.x-1.0-alpha6]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.0-alpha6%0D7.x-1.0-alpha5#diff
[7.x-1.0-alpha5]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.0-alpha5%0D7.x-1.0-alpha4#diff
[7.x-1.0-alpha4]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.0-alpha4%0D7.x-1.0-alpha3#diff
[7.x-1.0-alpha3]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.0-alpha3%0D7.x-1.0-alpha2#diff
[7.x-1.0-alpha2]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/branches/compare/7.x-1.0-alpha2%0D7.x-1.0-alpha1#diff
[7.x-1.0-alpha1]: https://bitbucket.org/digipolisgent/drupal_module_og-sm/commits/tag/7.x-1.0-alpha1

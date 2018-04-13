#!/bin/bash

# Add an optional statement to see that this is running in Travis CI.
echo "running drupal_ti/before/before_script.sh"

set -e $DRUPAL_TI_DEBUG

# Ensure the right Drupal version is installed.
# The first time this is run, it will install Drupal.
# Note: This function is re-entrant.
drupal_ti_ensure_drupal

# Change to the Drupal directory
cd "$DRUPAL_TI_DRUPAL_DIR"

# Enable submodules
drush --yes en og_sm_access og_sm_admin_menu og_sm_breadcrumb og_sm_comment og_sm_config og_sm_content og_sm_context og_sm_dashboard og_sm_feature og_sm_menu og_sm_path og_sm_routing og_sm_site_clone og_sm_taxonomy og_sm_theme og_sm_user og_sm_user_create
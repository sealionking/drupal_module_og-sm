<?php

/**
 * @file
 * Definition of og_sm_views_handler_filter_manageable_sites_by_current_user.
 */

/**
 * Filter entities based on the current user's manageable sites.
 */
class og_sm_views_handler_filter_manageable_sites_by_current_user extends views_handler_filter_boolean_operator {

  /**
   * {@inheritdoc}
   */
  function construct() {
    parent::construct();
    $this->value_value = t('Are the sites manageable by the current user');
  }

  /**
   * {@inheritdoc}
   */
  function query() {
    if (!empty($this->value)) {
      $this->ensure_my_table();
      $field = $this->table_alias . '.' . $this->real_field;
      $sites = og_sm_user_get_manageable_sites();
      $this->query->add_where(0, $field, array_keys($sites), 'IN');
    }
  }
}

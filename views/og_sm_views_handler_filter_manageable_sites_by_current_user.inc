<?php

/**
 * @file
 * Definition of og_sm_views_handler_filter_manageable_sites_by_current_user.
 */

/**
 * Filter entities based on the current user's manageable sites.
 */
// @codingStandardsIgnoreStart
class og_sm_views_handler_filter_manageable_sites_by_current_user extends views_handler_filter_boolean_operator {
  // @codingStandardsIgnoreEnd

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
    $this->ensure_my_table();
    $field = $this->table_alias . '.' . $this->real_field;

    $sites = og_sm_user_get_manageable_sites();
    $site_ids = array_keys($sites);
    if (empty($this->value)) {
      $this->query->add_where(0, $field, $site_ids, 'NOT IN');
    }
    else {
      $this->query->add_where(0, $field, $site_ids, 'IN');
    }
  }

}

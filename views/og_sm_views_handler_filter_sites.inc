<?php

/**
 * @file
 * Definition of og_sm_views_handler_filter_sites.
 */

/**
 * Filter handler to filter entities based on a their site.
 */
// @codingStandardsIgnoreStart
class og_sm_views_handler_filter_sites extends views_handler_filter_in_operator {
  // @codingStandardsIgnoreEnd

  /**
   * {@inheritdoc}
   */
  // @codingStandardsIgnoreStart
  function option_definition() {
    // @codingStandardsIgnoreEnd
    $options = parent::option_definition();
    $options['manageable_sites']['default'] = FALSE;
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  // @codingStandardsIgnoreStart
  function options_form(&$form, &$form_state) {
    // @codingStandardsIgnoreEnd
    parent::options_form($form, $form_state);
    $form['manageable_sites'] = array(
      '#type' => 'checkbox',
      '#title' => t('Limit options to the current user\'s manageable sites'),
      '#default_value' => $this->options['manageable_sites'],
    );
  }

  /**
   * {@inheritdoc}
   */
  // @codingStandardsIgnoreStart
  function get_value_options() {
    // @codingStandardsIgnoreEnd
    if (isset($this->value_options)) {
      return;
    }

    if ($this->options['manageable_sites']) {
      $sites = og_sm_user_get_manageable_sites();
    }
    else {
      $sites = og_sm_get_sites();
    }

    $options = array();
    foreach ($sites as $site_nid => $site) {
      $options[$site_nid] = $site->title;
    }
    asort($options);
    $this->value_options = $options;
  }

  /**
   * {@inheritdoc}
   */
  function query() {
    $this->ensure_my_table();
    if (!empty($this->value)) {
      $field = $this->table_alias . '.' . $this->real_field;
      $this->query->add_where(0, $field, $this->value);
    }
  }

}

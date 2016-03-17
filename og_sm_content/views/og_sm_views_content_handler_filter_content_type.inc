<?php
/**
 * @file
 * Views filter handler.
 */

/**
 * Views handler to filter content by being a Site content type.
 */
class ogSmContentViewsHandlerFilterContentType extends views_handler_filter_in_operator {
  /**
   * {@inheritdoc}
   */
  // @codingStandardsIgnoreStart
  function get_value_options() {

    if (!isset($this->value_options)) {
      $this->value_title = t('Content types');

      $types = og_sm_content_get_types();
      $options = array();
      foreach ($types as $type => $info) {
        $options[$type] = t($info->name);
      }

      $this->value_options = $options;
    }
  }
  // @codingStandardsIgnoreEnd

}

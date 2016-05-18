<?php
/**
 * @file
 * Views filter handler.
 */

/**
 * Views handler to filter content by being a Site content type.
 */
// @codingStandardsIgnoreStart
class ogSmContentViewsHandlerFilterContentType extends views_handler_filter_in_operator {
// @codingStandardsIgnoreEnd

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
        if ($site = og_sm_current_site()) {
          $info = og_sm_content_get_type_info_by_site($site, $info);
        }
        $options[$type] = ($info)
          ? t($info->name)
          : t($type);
      }

      $this->value_options = $options;
    }
  }
  // @codingStandardsIgnoreEnd

}

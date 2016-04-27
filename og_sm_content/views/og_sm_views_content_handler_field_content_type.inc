<?php
/**
 * @file
 * Views content type field handler.
 */

/**
 * Views handler to filter content by being a Site content type.
 */
class ogSmContentViewsHandlerFieldContentType extends views_handler_field_node_type {

  /**
   * {@inheritdoc}
   */
  // @codingStandardsIgnoreStart
  function render_name($data, $values) {
    $site = og_sm_current_site();
    if (!$site) {
      return parent::render_name($data, $values);
    }
    $content_type = og_sm_content_get_type_info_by_site($site, $data);
    if ($this->options['machine_name'] != 1 && $data !== NULL && $data !== '') {
      return $content_type->name;
    }
    return $content_type->site_type;
  }
  // @codingStandardsIgnoreEnd
}

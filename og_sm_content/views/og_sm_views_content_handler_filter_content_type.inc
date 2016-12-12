<?php
/**
 * @file
 * Views filter handler.
 */

/**
 * Views handler to filter content by being a Site content type.
 */
// @codingStandardsIgnoreStart
class OgSmContentViewsHandlerFilterContentType extends views_handler_filter_in_operator {
// @codingStandardsIgnoreEnd

  /**
   * The site node.
   *
   * @var object $site
   */
  protected $site;

  /**
   * {@inheritdoc}
   */
  // @codingStandardsIgnoreStart
  public function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Content types');
      $this->site = og_sm_current_site();

      if ($this->site) {
        $types = og_sm_content_get_types_by_site($this->site);
      }
      else {
        $types = og_sm_content_get_types();
      }

      $options = array();
      foreach ($types as $type => $info) {
        $options[$type] = ($info)
          ? t($info->name)
          : t($type);
      }

      $this->value_options = $options;
    }
  }
  // @codingStandardsIgnoreEnd

}

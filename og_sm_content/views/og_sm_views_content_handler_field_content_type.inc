<?php
/**
 * @file
 * Views content type field handler.
 */

/**
 * Views handler to filter content by being a Site content type.
 */
// @codingStandardsIgnoreStart
class ogSmContentViewsHandlerFieldContentType extends views_handler_field_node_type {
// @codingStandardsIgnoreEnd

  /**
   * {@inheritdoc}
   */
  // @codingStandardsIgnoreStart
  function option_definition() {
    //@codingStandardsIgnoreEnd
    $options = parent::option_definition();
    $options['display_site_node_type'] = array('default' => TRUE, 'bool' => TRUE);

    return $options;
  }

  /**
   * {@inheritdoc}
   */
  // @codingStandardsIgnoreStart
  function options_form(&$form, &$form_state) {
    // @codingStandardsIgnoreEnd
    parent::options_form($form, $form_state);

    $form['display_site_node_type'] = array(
      '#title' => t('Display site node type.'),
      '#description' => t('Append the site content type machine name.'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['display_site_node_type']),
    );
  }

  /**
   * {@inheritdoc}
   */
  // @codingStandardsIgnoreStart
  function render_name($data, $values) {
  // @codingStandardsIgnoreEnd
    $site = og_sm_current_site();
    if (!$site) {
      return parent::render_name($data, $values);
    }
    $content_type = og_sm_content_get_type_info_by_site($site, $data);
    if ($this->options['machine_name'] != 1 && $data !== NULL && $data !== '') {
      $output = $content_type->name;
      if ($this->options['display_site_node_type']) {
        $output .= ' <em>' . t('(original: @site_type)', array('@site_type' => $content_type->site_type)) . '</em>';
      }
      return $output;
    }
    return $content_type->site_type;
  }

}

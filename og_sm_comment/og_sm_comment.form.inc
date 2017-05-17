<?php

/**
 * @file
 * Forms and form alters.
 */

/**
 * Adds the comment settings to the Site content settings.
 *
 * Adds the comment settings to the content type form ONLY if the comments are
 * set to OPEN on global level.
 *
 * @param array $form
 *   The form structure.
 * @param array $form_state
 *   The form state.
 *
 * @see og_sm_comment_form_og_sm_content_admin_overview_type_edit_form_alter()
 */
function _og_sm_comment_form_og_sm_content_admin_overview_type_edit_form_alter(array &$form, array &$form_state) {
  // Existing info.
  $info = $form['#content_type_info'];
  $content_type = $info->site_type;
  $config = $info->comment_config;
  /* @var $config OgSmCommentOverrideConfig */

  // Add the comment settings only if comments are enabled on platform level.
  if (!$config->isGlobalEnabled()) {
    return;
  }

  // Group the fields.
  $form['content_comments'] = array(
    '#type' => 'fieldset',
    '#title' => t('Comments'),
  );

  // Comment state.
  $key_comment = sprintf('og_sm_content_%s_comment', $content_type);
  $form['content_comments'][$key_comment] = _og_sm_comment_settings_element(
    $form['#content_type'],
    $config->hasSiteComment() ? $config->getSiteComment() : $config->getGlobalComment(),
    OG_SM_COMMENT_NODE_OPEN_FOR_ANONYMOUS
  );

  // Override comment state per node.
  $form['content_comments']['override'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'og-sm-content-comments-override',
      ),
    ),
    '#states' => array(
      'visible' => array(
        // Comments = 2 or 3.
        array(
          sprintf(':input[name="%s"]', $key_comment) => array(
            'value' => (string) COMMENT_NODE_OPEN,
          ),
        ),
        array(
          sprintf(':input[name="%s"]', $key_comment) => array(
            'value' => (string) OG_SM_COMMENT_NODE_OPEN_FOR_ANONYMOUS,
          ),
        ),
      ),
    ),
  );

  // Default comment state when overridden.
  $key_comment_override = sprintf('og_sm_content_%s_comment_override', $content_type);
  $form['content_comments']['override'][$key_comment_override] = array(
    '#type' => 'checkbox',
    '#title' => t('Comment settings can be set per content item'),
    '#description' => t('If and who can post comments is by default set on the site level. Enabeling this option will allow users to override this per content item.'),
    '#default_value' => (int) $config->isOverridable(),
  );

  $key_comment_override_default = sprintf('og_sm_content_%s_comment_override_default', $content_type);
  $form['content_comments']['override'][$key_comment_override_default] = array_merge(
      _og_sm_comment_settings_element(
      $form['#content_type'],
      $config->getDefaultComment(),
      OG_SM_COMMENT_NODE_OPEN_FOR_ANONYMOUS
    ),
    array(
      '#title' => t('Default when no specific value is set for a content item'),
      '#description' => t('The default comment setting for each newly created content item when no explicit override is set. If no default is set, the Site comment setting will be used.'),
      '#required' => FALSE,
      '#empty_value' => TRUE,
      '#empty_option' => t(' - Same as site -'),
      '#states' => array(
        'invisible' => array(
          sprintf(':input[name="%s"]', $key_comment_override) => array(
            'checked' => FALSE,
          ),
        ),
      ),
    )
  );

  $form['#comment_keys'] = array(
    'comment' => $key_comment,
    'comment_override' => $key_comment_override,
    'comment_override_default' => $key_comment_override_default,
  );

  // Custom validator for this complex form alter.
  $form['#validate'][] = 'og_sm_comment_form_og_sm_content_admin_overview_type_edit_form_alter_validate';
}

/**
 * Node type (within Site) form settings validation.
 *
 * @param array $form
 *   The form structure.
 * @param array $form_state
 *   The form state.
 */
function og_sm_comment_form_og_sm_content_admin_overview_type_edit_form_alter_validate($form, &$form_state) {
  $keys = $form['#comment_keys'];
  $values = $form_state['values'];

  $config_old = $form['#content_type_info']->comment_config;
  /* @var $config_old \OgSmCommentOverrideConfig */
  $config_new = new OgSmCommentOverrideConfig(
    $config_old->getGlobalComment(),
    (int) $values[$keys['comment']],
    (int) $values[$keys['comment_override']],
    (int) $values[$keys['comment_override_default']]
  );

  // Change values if comments are not allowed or are not overidable.
  if (!$config_new->isSiteEnabled() || !$config_new->isOverridable()) {
    $form_state['values'][$keys['comment_override_default']] = NULL;
  }
  // Validate that the max level is higher then the maximum allowed one.
  elseif ($config_new->getSiteComment() < (int) $values[$keys['comment_override_default']]) {
    form_set_error(
      $keys['comment_override_default'],
      t('The default overridden value can not be more open then the comment setting.')
    );
  }
}

/**
 * Adds the custom comment settings to the node form.
 *
 * @param array $form
 *   The form structure.
 * @param array $form_state
 *   The form state.
 */
function _og_sm_comment_form_node_form_alter(array &$form, array &$form_state) {
  $node = $form['#node'];

  // Add the comment settings only if we are in a site context.
  $site = og_sm_current_site();
  if (!$site) {
    return;
  }

  // Global comment administrators can always override!
  if (user_access('administer comments')) {
    _og_sm_comment_form_node_form_alter_elements($form, OG_SM_COMMENT_NODE_OPEN_FOR_ANONYMOUS);
    return;
  }

  $config = og_sm_comment_get_config($node->type, $site);

  // Show only if comments are enabled and overridable.
  if (!$config->isSiteEnabled() || !$config->isOverridable()) {
    return;
  }

  // Access check.
  if (!user_access(OG_SM_COMMENT_OG_PERM_OVERRIDE_NODE_COMMENT_SETTINGS)
    && !og_sm_site_permission_access($site, OG_SM_COMMENT_OG_PERM_OVERRIDE_NODE_COMMENT_SETTINGS)
  ) {
    return;
  }

  // If we got here, the user has access to the form elements.
  _og_sm_comment_form_node_form_alter_elements($form);
}

/**
 * Actual form for the _og_sm_comment_form_node_form_alter() function.
 *
 * @param array $form
 *   The form structure.
 * @param int|null $max_level
 *   The max level a user has access to. If non given, the max level of the node
 *   type settings will be used.
 *
 * @return array
 */
function _og_sm_comment_form_node_form_alter_elements(array &$form, $max_level = NULL) {
  $node = $form['#node'];
  $site = og_sm_current_site();
  $config = og_sm_content_get_type_info_by_site($site, $node->type);
  $site_config_label = og_sm_comment_config_label($config->comment);
  $max_level = $max_level === NULL
    ? $config->comment
    : $max_level;

  $overridden = (int) !empty($node->og_sm_comment_override);
  $override_default_value = !isset($node->og_sm_comment_override->comment)
    ? $config->comment_override_default_value
    : $node->og_sm_comment_override->comment;

  // Make sure that the currently set value can be seen while updating the node.
  if ($override_default_value > $max_level) {
    $max_level = $override_default_value;
  }

  // Remove the existing comments section.
  unset($form['comment_settings']);

  // Replace by custom form.
  $form['comment_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Comment settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'additional_settings',
    '#attributes' => array(
      'class' => array(
        0 => 'og-sm-comment-node-settings-form',
      ),
    ),
    '#attached' => array(
      'js' => array(
        0 => drupal_get_path('module', 'og_sm_comment') . '/js/og-sm-comment-node-form.js',
      ),
    ),
    '#weight' => 30,
  );
  $form['comment_settings']['comment_default'] = array(
    '#type' => 'hidden',
    '#value' => $site_config_label,
  );
  $form['comment_settings']['comment_override'] = array(
    '#type' => 'checkbox',
    '#title' => t(
      'Override comment settings for this node (default: %default)',
      array('%default' => $site_config_label)
    ),
    '#default_value' => $overridden,
  );
  $form['comment_settings']['comment_override_value'] = array_merge(
    _og_sm_comment_settings_element(
      $node->type,
      $override_default_value,
      $max_level
    ),
    array(
      '#states' => array(
        'invisible' => array(
          ':input[name="comment_override"]' => array(
            'checked' => FALSE,
          ),
        ),
      ),
    )
  );
}

/**
 * Helper to create the field to show the comment settings.
 *
 * @param string $node_type
 *   The node type to create the form element for.
 * @param int $default
 *   The default value.
 * @param int $max_level
 *   The maximum level for the option field.
 *
 * @return array
 *   Form element structure.
 */
function _og_sm_comment_settings_element($node_type, $default, $max_level = COMMENT_NODE_OPEN) {
  $site = og_sm_current_site();
  $info = og_sm_content_get_type_info_by_site($site, $node_type);

  $description = t(
    'Select whether the comment form can be shown for @content_type_plural.',
    array('@content_type_plural' => drupal_strtolower($info->name_plural))
  );
  $help = og_sm_comment_config_descriptions();
  foreach (array_keys($help) as $key) {
    if ($key > $max_level) {
      unset($help[$key]);
    }
  }
  $description .= '<ul><li>' . implode('</li><li>', $help) . '</li></ul>';

  $options = og_sm_comment_config_labels();
  foreach (array_keys($options) as $key) {
    if ($key > $max_level) {
      unset($options[$key]);
    }
  }
  return array(
    '#type' => 'select',
    '#title' => t('Comments'),
    '#description' => $description,
    '#default_value' => $default,
    '#options' => $options,
  );
}

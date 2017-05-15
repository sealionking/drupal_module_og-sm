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

  // Add the comment settings only if comments are enabled for this content
  // type.
  if ((int) variable_get('comment_' . $content_type, 0) !== COMMENT_NODE_OPEN) {
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
    $info->comment,
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
    '#default_value' => $info->comment_override,
  );

  $key_comment_override_default = sprintf('og_sm_content_%s_comment_override_default', $content_type);
  $form['content_comments']['override'][$key_comment_override_default] = array(
    '#type' => 'checkbox',
    '#title' => t('Default value when no override is set for a content item is different then the site setting.'),
    '#default_value' => $info->comment_override_default,
    '#states' => array(
      'invisible' => array(
        sprintf(':input[name="%s"]', $key_comment_override) => array(
          'checked' => FALSE,
        ),
      ),
    ),
  );

  $key_comment_override_default_value = sprintf('og_sm_content_%s_comment_override_default_value', $content_type);
  $form['content_comments']['override'][$key_comment_override_default_value] = array_merge(
      _og_sm_comment_settings_element(
      $form['#content_type'],
      $info->comment_override_default_value,
      OG_SM_COMMENT_NODE_OPEN_FOR_ANONYMOUS
    ),
    array(
      '#title' => t('Default per content item'),
      '#description' => t('The default comment setting for each newly created content item when no explicit override is set.'),
      '#states' => array(
        'visible' => array(
          sprintf(':input[name="%s"]', $key_comment_override) => array(
            'checked' => TRUE,
          ),
          sprintf(':input[name="%s"]', $key_comment_override_default) => array(
            'checked' => TRUE,
          ),
        ),
      ),
    )
  );

  $form['#comment_keys'] = array(
    'comment' => $key_comment,
    'comment_override' => $key_comment_override,
    'comment_override_default' => $key_comment_override_default,
    'comment_override_default_value' => $key_comment_override_default_value,
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

  // Extract values.
  $comment = (int) $values[$keys['comment']];
  $comment_override = (int) $values[$keys['comment_override']];
  $comment_override_default = (int) $values[$keys['comment_override_default']];
  $comment_override_default_value = (int) $values[$keys['comment_override_default_value']];

  // Change values if not overridden.
  if ($comment < COMMENT_NODE_OPEN || !$comment_override) {
    $form_state['values'][$keys['comment_override']] = 0;
    $form_state['values'][$keys['comment_override_default']] = 0;
    $form_state['values'][$keys['comment_override_default_value']] = $comment;
  }
  // Reset override value if no default is set.
  elseif (!$comment_override_default) {
    $form_state['values'][$keys['comment_override_default_value']] = $comment;
  }
  // Validate that the max level is higher then the maximum allowed one.
  elseif ($comment < $comment_override_default_value) {
    form_set_error(
      $keys['comment_override_default_value'],
      t('The default overridden value can not be more open then the comment setting.')
    );
  }
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
  $help = array(
    COMMENT_NODE_HIDDEN => t('Hidden: No comments are allowed, and past comments are hidden.'),
    COMMENT_NODE_CLOSED => t('Closed: No comments are allowed, but any past comments remain visible.'),
    COMMENT_NODE_OPEN => t('Open: Any content of this type is open to new comments by logged in users.'),
    OG_SM_COMMENT_NODE_OPEN_FOR_ANONYMOUS => t('Open for anonymous users: Any content of this type is open to new comments by anonymous and logged in users.'),
  );
  foreach (array_keys($help) as $key) {
    if ($key > $max_level) {
      unset($help[$key]);
    }
  }
  $description .= '<ul><li>' . implode('</li><li>', $help) . '</li></ul>';

  $options = array(
    COMMENT_NODE_HIDDEN => t('Hidden'),
    COMMENT_NODE_CLOSED => t('Closed'),
    COMMENT_NODE_OPEN => t('Open'),
    OG_SM_COMMENT_NODE_OPEN_FOR_ANONYMOUS => t('Open for anonymous users'),
  );
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

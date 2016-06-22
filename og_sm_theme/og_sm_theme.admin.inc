<?php
/**
 * @file
 * Admin callbacks for the theme settings.
 */

/**
 * Menu callback; displays a listing of all themes for a Site.
 *
 * Similar to Core, but only displays the enabled theme groups. We assume
 * all themes will be enabled globally before we allow them to be used in a
 * Site. Enabling and disabling is not supported from the Site theme settings.
 * Same goes for the incompatibility checks, we assume they passed when the
 * theme was enabled globally.
 *
 * @param object $site
 *   The Site.
 *
 * @return string
 *   Rendered themes overview
 *
 * @see system_themes_page()
 */
function og_sm_theme_themes_page($site) {
  $parent = 'group/node/' . $site->nid . '/admin/theme';
  og_sm_set_breadcrumb($site, array(l(t('Administer theme'), $parent)));

  // Get a list of available themes.
  $themes = og_sm_theme_site_themes($site);

  $global_theme = variable_get('theme_default', 'bartik');
  $theme_default = og_sm_variable_get($site->nid, 'theme', $global_theme);
  $theme_groups  = array();

  foreach ($themes as &$theme) {
    if (!empty($theme->info['hidden'])) {
      continue;
    }

    $theme->is_default = ($theme->name == $theme_default);

    // Identify theme screenshot.
    $theme->screenshot = NULL;
    // Create a list which includes the current theme and all its base themes.
    if (isset($themes[$theme->name]->base_themes)) {
      $theme_keys = array_keys($themes[$theme->name]->base_themes);
      $theme_keys[] = $theme->name;
    }
    else {
      $theme_keys = array($theme->name);
    }
    // Look for a screenshot in the current theme or in its closest ancestor.
    foreach (array_reverse($theme_keys) as $theme_key) {
      if (!isset($themes[$theme_key])) {
        continue;
      }
      if (!file_exists($themes[$theme_key]->info['screenshot'])) {
        continue;
      }
      $theme_name = $theme->info['name'];
      $theme->screenshot = array(
        'path' => $themes[$theme_key]->info['screenshot'],
        'alt' => t('Screenshot for !theme theme', array('!theme' => $theme_name)),
        'title' => t('Screenshot for !theme theme', array('!theme' => $theme_name)),
        'attributes' => array('class' => array('screenshot')),
      );
      break;
    }

    $query['token'] = drupal_get_token('og-sm-theme-operation-link');
    $theme->operations = array();
    if (!empty($theme->status)) {
      // Create the operations links.
      $query['theme'] = $theme->name;
      if (drupal_theme_access($theme)) {
        $theme->operations[] = array(
          'title' => t('Settings'),
          'href' => $parent . '/settings/' . $theme->name,
          'attributes' => array('title' => t('Settings for !theme theme', array('!theme' => $theme->info['name']))),
        );
      }
      if (!empty($theme->status)) {
        if (!$theme->is_default) {
          $theme->operations[] = array(
            'title' => t('Set as site theme'),
            'href' => $parent . '/default',
            'query' => $query,
            'attributes' => array(
              'title' => t('Set !theme as site theme', array('!theme' => $theme->info['name'])),
            ),
          );
        }
      }
    }

    // Add notes to default and administration theme.
    $theme->notes = array();
    $theme->classes = array();
    if ($theme->is_default) {
      $theme->classes[] = 'theme-default';
      $theme->notes[] = t('default theme');
    }

    // Sort enabled and disabled themes into their own groups.
    $theme_groups[$theme->status ? 'enabled' : 'disabled'][] = $theme;
  }

  // There is just one possible theme group for Site themes, but since we reuse
  // Drupal's theme function we keep the array structure.
  $theme_group_titles = array(
    'enabled' => format_plural(count($theme_groups['enabled']), 'Site theme', 'Site themes'),
  );

  module_load_include('inc', 'system', 'system.admin');
  uasort($theme_groups['enabled'], 'system_sort_themes');

  drupal_alter('og_sm_theme_themes_page', $theme_groups);

  return theme('system_themes_page', array(
    'theme_groups' => $theme_groups,
    'theme_group_titles' => $theme_group_titles,
  ));
}

/**
 * Menu callback; Set the default theme.
 *
 * Similar to Drupal's callback but sets a Site variable instead of the global
 * default theme.
 *
 * @param object $site
 *   The Site.
 *
 * @return int|void
 *   Menu callback response or void on redirect
 *
 * @see system_theme_default()
 */
function og_sm_theme_set_default($site) {
  if (!isset($_REQUEST['theme']) || !isset($_REQUEST['token'])) {
    return MENU_ACCESS_DENIED;
  }

  if (!drupal_valid_token($_REQUEST['token'], 'og-sm-theme-operation-link')) {
    return MENU_ACCESS_DENIED;
  }

  $theme = $_REQUEST['theme'];

  // Get all themes that we can choose from.
  $themes = og_sm_theme_site_themes($site);

  // Check if the specified theme is one recognized by the system.
  if (!empty($themes[$theme])) {
    // Set the default theme.
    og_sm_variable_set($site->nid, 'theme', $theme);

    drupal_set_message(t('%theme is now the default theme.', array(
      '%theme' => $themes[$theme]->info['name'],
    )));

  }
  else {
    drupal_set_message(t('The %theme theme was not found.', array(
      '%theme' => $theme,
    )), 'error');
  }
  drupal_goto('group/node/' . $site->nid . '/admin/theme');
}

/**
 * Global theme configuration form.
 *
 * @return array $form
 *   The form
 */
function og_sm_theme_global_settings_form() {

  $form['available_themes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Allowed themes'),
    '#description' => t('Select which themes should be available for Sites.'),
  );

  // Get a sorted list of enabled themes.
  $themes = array_filter(list_themes(), function ($theme) {
    return $theme->status;
  });

  // Sort the list.
  module_load_include('inc', 'system', 'system.admin');
  uasort($themes, 'system_sort_modules_by_info_name');

  // Map the keys with the human readable name.
  $themes = array_map(
    function ($theme) {
      return $theme->info['name'];
    }, $themes
  );

  $form['available_themes']['themes'] = array(
    '#type' => 'checkboxes',
    '#options' => $themes,
    '#default_value' => variable_get('og_sm_theme_site_themes', array()),
  );

  $global_theme = variable_get('theme_default', 'bartik');
  $form['default_theme'] = array(
    '#type' => 'select',
    '#options' => $themes,
    '#title' => t('Default theme'),
    '#description' => t('Choose the default Site theme to use when no theme has been selected.'),
    '#default_value' => variable_get('og_sm_theme_default_theme', $global_theme),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Form submit handler for the theme settings form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function og_sm_theme_global_settings_form_submit($form, $form_state) {

  variable_set('og_sm_theme_default_theme', $form_state['values']['default_theme']);

  $current_themes = variable_get('og_sm_theme_site_themes', array());
  $new_themes = $form_state['values']['themes'];

  variable_set('og_sm_theme_site_themes', $new_themes);

  // See if some sites are still using a theme that's not allowed anymore.
  $diff = array_diff(
    array_filter($current_themes),
    array_filter($new_themes)
  );
  if ($diff) {
    _og_sm_theme_verify_disabled_site_themes($diff);
  }

  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Form for configuring theme settings within a Site.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 * @param object $site
 *   The Site object.
 * @param string $theme_key
 *   The theme key.
 *
 * @return array $form
 *   The settings form.
 *
 * @see system_theme_settings()
 */
function og_sm_theme_site_settings_form(array $form, array &$form_state, $site, $theme_key) {
  // Save them for later.
  $form_state['site'] = $site;
  $form_state['theme_key'] = $theme_key;

  $settings = og_sm_theme_get_theme_settings($site, $theme_key);

  // Toggle settings.
  $toggles = array(
    'breadcrumb' => t('breadcrumb'),
    /* 'main_menu' => t('Main menu'), */
  );

  $form['theme_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Toggle display'),
    '#description' => t('Enable or disable the display of certain page elements.'),
  );
  foreach ($toggles as $name => $title) {
    $form['theme_settings']['toggle_' . $name] = array(
      '#type' => 'checkbox',
      '#title' => $title,
      '#default_value' => $settings['toggle_' . $name],
    );
  }

  $form = system_settings_form($form);
  // We don't want to call system_settings_form_submit(), so change #submit.
  $form['#submit'] = array('og_sm_theme_site_settings_form_submit');

  return $form;
}

/**
 * Form submit handler for the Site theme settings form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function og_sm_theme_site_settings_form_submit(array $form, array $form_state) {
  $site = $form_state['site'];
  $theme_key = $form_state['theme_key'];

  $settings = og_sm_theme_get_theme_settings($site, $theme_key);

  form_state_values_clean($form_state);
  $values = $form_state['values'];

  og_sm_theme_set_theme_settings($values, $site, $theme_key);

  og_sm_site_cache_clear_all($site);
  drupal_set_message(t('The theme settings have been saved.'));
}

/**
 * Breadcrumb component settings form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 * @param object $site
 *   The Site object.
 * @param string $theme_key
 *   The theme key.
 *
 * @return array
 *   The form structure.
 */
function og_sm_theme_component_breadcrumb_form(array $form, array &$form_state, $site, $theme_key) {
  // Save them for later.
  $form_state['site'] = $site;
  $form_state['theme_key'] = $theme_key;

  $settings = og_sm_theme_get_breadcrumb_settings($site, $theme_key);

  $form['append_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Append the page title to the breadcrumb trail'),
    '#description' => t('The page title will be appended to the breadcrumb trail.'),
    '#default_value' => $settings['append_title'],
  );

  $form['override_root'] = array(
    '#type' => 'checkbox',
    '#title' => t('Manually set the breadcrumb root'),
    '#description' => t('If checked, you can specify the root of the breadcrumb for this theme.'),
    '#default_value' => $settings['override_root'],
  );

  // Initialize our form state.
  if (!isset($form_state['input']['root_parts'])) {
    $form_state['input']['root_parts'] = $settings['root_parts'];
    $form_state['row_count'] = count($settings['root_parts']);

    if ($form_state['row_count'] == 0) {
      ++$form_state['row_count'];
    }
  }

  $form['#tree'] = TRUE;
  $wrapper_id = 'breadcrumb-parts-wrapper';
  $form['root_parts'] = array(
    '#type' => 'container',
  );

  $parts_table = array(
    '#theme' => 'og_sm_theme_component_breadcrumb_parts',
    '#prefix' => '<div id="' . $wrapper_id . '">',
    '#suffix' => '</div>',
  );

  for ($i = 0; $i < $form_state['row_count']; $i++) {
    $default_values = isset($form_state['input']['root_parts'][$i])
      ? $form_state['input']['root_parts'][$i]
      : array('text' => '', 'path' => '', 'weight' => 0);

    $parts_table[$i]['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text'),
      '#title_display' => 'invisible',
      '#default_value' => $default_values['text'],
    );

    $parts_table[$i]['path'] = array(
      '#type' => 'textfield',
      '#title' => t('Path'),
      '#title_display' => 'invisible',
      '#default_value' => $default_values['path'],
    );

    $parts_table[$i]['operations'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#name' => 'delete_breadcrumb_part_' . $i,
      '#validate' => array(),
      '#limit_validation_errors' => array(),
      '#submit' => array('og_sm_theme_component_breadcrumb_delete_item'),
      '#ajax' => array(
        'callback' => 'og_sm_theme_component_breadcrumb_js_callback',
        'wrapper' => $wrapper_id,
      ),
    );

    $parts_table[$i]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#title_display' => 'invisible',
      '#default_value' => $default_values['weight'],
      '#delta' => 100,
      '#attributes' => array('class' => array('item-weight')),
    );
  }

  $form['root_parts']['parts'] = $parts_table;

  $form['root_parts']['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add part'),
    '#validate' => array(),
    '#limit_validation_errors' => array(),
    '#submit' => array('og_sm_theme_component_breadcrumb_add_item'),
    '#ajax' => array(
      'callback' => 'og_sm_theme_component_breadcrumb_js_callback',
      'wrapper' => $wrapper_id,
    ),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Validate handler for the breadcrumb form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function og_sm_theme_component_breadcrumb_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  if ($values['override_root']) {
    foreach ($values['root_parts']['parts'] as $i => $part) {
      if (empty($part['text'])) {
        form_set_error('root_parts][parts][' . $i . '][text', t('The field %field is required.', array(
          '%field' => t('Text'),
        )));
      }

      if (empty($part['path'])) {
        form_set_error('root_parts][parts][' . $i . '][path', t('The field %field is required.', array(
          '%field' => t('Path'),
        )));
      }
      elseif (!drupal_valid_path($part['path'])) {
        form_set_error('root_parts][parts][' . $i . '][path', t('The value provided for %field is not a valid URL.', array(
          '%field' => t('Path'),
        )));
      }
    }
  }
}

/**
 * Submit handler for the breadcrumb form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function og_sm_theme_component_breadcrumb_form_submit($form, &$form_state) {
  form_state_values_clean($form_state);
  $values = $form_state['values'];
  unset($values['actions']);

  $site = $form_state['site'];
  $theme_key = $form_state['theme_key'];

  $settings['append_title'] = (int) $values['append_title'];
  $settings['override_root'] = (int) $values['override_root'];

  if ($settings['override_root']) {
    $parts = $values['root_parts']['parts'];
    foreach ($parts as &$part) {
      unset($part['operation']);
    }
    usort($parts, 'drupal_sort_weight');
    $settings['root_parts'] = $parts;
  }
  else {
    $settings['root_parts'] = array();
  }

  og_sm_theme_set_breadcrumb_settings($settings, $site, $theme_key);
  og_sm_site_cache_clear_all($site);

  drupal_set_message(t('The breadcrumb settings have been saved.'));
}

/**
 * Submit function for the add item button.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function og_sm_theme_component_breadcrumb_add_item($form, &$form_state) {
  $form_state['row_count']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit function for the delete item button.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function og_sm_theme_component_breadcrumb_delete_item($form, &$form_state) {
  if (preg_match('#^delete_breadcrumb_part_(\d+)$#', $form_state['triggering_element']['#name'], $matches)) {
    if (isset($form_state['input']['root_parts']['parts'][$matches[1]])) {
      unset($form_state['input']['root_parts']['parts'][$matches[1]]);
      $form_state['input']['root_parts']['parts'] = array_values($form_state['input']['root_parts']['parts']);
      $form_state['row_count']--;
    }
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * AJAX callback that returns the updated component.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   The element to update.
 */
function og_sm_theme_component_breadcrumb_js_callback($form, $form_state) {
  return $form['root_parts']['parts'];
}

/**
 * Theme function for the breadcrumb parts table.
 *
 * @param array $variables
 *   The variables array.
 *
 * @return string
 *   The rendered content.
 */
function theme_og_sm_theme_component_breadcrumb_parts($variables) {
  $element = $variables['element'];
  drupal_add_tabledrag('breadcrumb-parts-table', 'order', 'sibling', 'item-weight');
  drupal_add_js(drupal_get_path('module', 'og_sm_theme') . '/js/breadcrumb_parts.js');

  $header = array(
    'text' => t('Text'),
    'path' => t('Path'),
    'operations' => t('Operations'),
    'weight' => t('Weight'),
  );

  $rows = array();
  foreach (element_children($element) as $key) {
    $row = array();
    $row['data'] = array();
    foreach ($header as $field_name => $title) {
      $row['data'][] = drupal_render($element[$key][$field_name]);
      $row['class'] = array('draggable');
    }
    $rows[] = $row;
  }

  return theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'breadcrumb-parts-table'),
    'empty' => t('There are no parts added yet.'),
  ));
}

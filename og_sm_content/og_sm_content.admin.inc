<?php
/**
 * @file
 * Administration pages for the og_sm_content module.
 */

/**
 * Site content types overview.
 *
 * @param object $site
 *   The Site node.
 *
 * @return string
 *   The page content.
 */
function og_sm_content_admin_overview_types($site) {
  $parent = 'group/node/' . $site->nid . '/admin';
  og_sm_set_breadcrumb($site, array(l(t('Administer Site'), $parent)));

  $rows = array();
  foreach (og_sm_content_get_types_by_site($site) as $machine_name => $content_type) {
    $rows[] = array(
      $content_type->site_type,
      $content_type->name,
      $content_type->name_plural,
      l(t('Edit'), 'group/node/' . $site->nid . '/admin/structure/types/' . $machine_name, array(
        'query' => drupal_get_destination(),
      )),
    );
  }

  return array(
    '#theme' => 'table',
    '#rows' => $rows,
    '#header' => array(
      t('Machine name'),
      t('Name singular'),
      t('Name plural'),
      t('Operations'),
    ),
  );
}

/**
 * Form definition for editing a content type within a site.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The current form state.
 * @param object $site
 *   The Site node.
 * @param string $content_type
 *   The content type machine name.
 *
 * @return array
 *   The form definition.
 */
function og_sm_content_admin_overview_type_edit_form($form, &$form_state, $site, $content_type) {
  $content_type = og_sm_content_get_type_info_by_site($site, $content_type);
  $variable_base = 'og_sm_content_' . $content_type->type . '_';
  $form[$variable_base . 'machine_name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Machine name'),
    '#machine_name' => array(
      'exists' => 'og_sm_content_type_site_machine_name_exists',
    ),
    '#default_value' => $content_type->site_type,
  );
  $form[$variable_base . 'name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name singular'),
    '#default_value' => $content_type->name,
  );
  $form[$variable_base . 'name_plural'] = array(
    '#type' => 'textfield',
    '#title' => t('Name plural'),
    '#default_value' => $content_type->name_plural,
  );

  // Only relevant if comments are enabled by default for this content type.
  if (module_exists('comment') && variable_get('comment_' . $content_type->type) == COMMENT_NODE_OPEN) {
    $form[$variable_base . 'comment'] = array(
      '#type' => 'select',
      '#title' => t('Comments'),
      '#description' => t('Select whether the comment form can be shown for @content_type_plural.', array(
        '@content_type_plural' => drupal_strtolower($content_type->name_plural),
      )),
      '#default_value' => $content_type->comment,
      '#options' => array(
        COMMENT_NODE_OPEN => t('Open'),
        COMMENT_NODE_HIDDEN => t('Hidden'),
      ),
    );
  }

  $form = og_sm_variable_settings_form($form, $form_state, $site);

  // Rebuild menu after variables have been saved.
  $form['#submit'][] = 'menu_rebuild';

  return $form;
}

/**
 * Checks whether a site machine name already exists within site context.
 *
 * @param string $machine_name
 *   The new site specific machine name.
 * @param array $element
 *   The machine name form element.
 * @param array $form_state
 *   The current form state.
 *
 * @return bool
 *   Content type exists within site context.
 */
function og_sm_content_type_site_machine_name_exists($machine_name, $element, $form_state) {
  $site = $form_state['build_info']['args'][0];
  return og_sm_content_get_original_type_by_site_alias_type($site, $machine_name);
}

/**
 * Site content overview.
 *
 * @param object $site
 *   The Site node.
 *
 * @return string
 *   The page content.
 */
function og_sm_content_admin_overview($site) {
  $parent = 'group/node/' . $site->nid . '/admin';
  og_sm_set_breadcrumb($site, array(l(t('Administer Site'), $parent)));

  $view = views_get_view('og_sm_content_admin_overview');
  $view->set_display('embed_overview');
  $view->set_arguments(array($site->nid));
  $view->override_path = 'group/node/' . $site->nid . '/admin/content';

  return $view->preview();
}

/**
 * Site content overview owned by the current user.
 *
 * @param object $site
 *   The Site node.
 *
 * @return string
 *   The page content.
 */
function og_sm_content_admin_overview_my($site) {
  $parent = 'group/node/' . $site->nid . '/admin';
  og_sm_set_breadcrumb($site, array(l(t('Administer Site'), $parent)));

  $view = views_get_view('og_sm_content_admin_overview');
  $view->set_display('embed_overview_my');
  $view->set_arguments(array($site->nid));
  $view->override_path = 'group/node/' . $site->nid . '/admin/content';

  return $view->preview();
}

/**
 * Admin add content menu callback.
 *
 * Will redirect to group/node/nid/content/add.
 *
 * @param object $site
 *   The Site node.
 */
function og_sm_content_admin_add_content($site) {
  drupal_goto('group/node/' . $site->nid . '/content/add');
}

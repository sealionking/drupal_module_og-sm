<?php
/**
 * @file
 * Administration pages for the og_sm_taxonomy module.
 */

/**
 * Overview of the vocabularies a user can administer.
 *
 * @param object $site
 *   The Site to render the overview page for.
 *
 * @return array
 *   The page content as a renderable array.
 */
function og_sm_taxonomy_admin_overview($site) {
  $url = 'group/node/' . $site->nid . '/admin/taxonomy/';

  $header = array(
    t('Vocabulary name'),
    array(
      'data' => t('Operations'),
      'colspan' => 2,
    ),
  );

  $rows = array();
  $vocabularies = og_sm_taxonomy_get_vocabularies();
  foreach ($vocabularies as $vocabulary) {
    $label = check_plain($vocabulary->name);
    $name = $vocabulary->machine_name;

    if (!og_sm_taxonomy_admin_access_vocabulary($site, $vocabulary)) {
      continue;
    }

    $rows[] = array(
      $label,
      l(t('list terms'), $url . $name),
      l(t('add terms'), $url . $name . '/add'),
    );
  }

  // Return the table.
  return array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );
}

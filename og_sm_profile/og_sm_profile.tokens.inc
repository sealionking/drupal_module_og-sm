<?php

/**
 * @file
 * Builds placeholder replacement tokens for profile-related data.
 */

/**
 * Implements hook_token_info().
 */
function og_sm_profile_token_info() {
  $type = array(
    'name' => t('Site User Profiles'),
    'description' => t('Tokens for user profiles linked to the site.'),
    'needs-data' => 'og_sm_profile',
  );

  $tokens['id'] = array(
    'name' => t('Profile ID'),
    'description' => t('The unique ID of the site user profile.'),
  );
  $tokens['site'] = array(
    'name' => t("Site"),
    'description' => t("The site to which the profile is linked."),
    'type' => 'node',
  );
  $tokens['user'] = array(
    'name' => t("User"),
    'description' => t("The user to which the profile is linked."),
    'type' => 'user',
  );
  $tokens['created'] = array(
    'name' => t("Date created"),
    'description' => t("The date the profile was created."),
  );

  return array(
    'types' => array('og_sm_profile' => $type),
    'tokens' => array('og_sm_profile' => $tokens),
  );
}

/**
 * Implements hook_tokens().
 */
function og_sm_profile_tokens($type, $tokens, array $data = array(), array $options = array()) {

  $replacements = array();

  if ($type == 'og_sm_profile' && !empty($data['og_sm_profile'])) {
    $profile = $data['og_sm_profile'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'id':
          $replacements[$original] = $profile->id;
          break;

        case 'created':
          $replacements[$original] = format_date($profile->created, 'medium');
          break;
      }
    }

    // Chained token relationships.
    if ($site_tokens = token_find_with_prefix($tokens, 'site')) {
      $site = og_sm_site_load($profile->site_nid);
      $replacements += token_generate('node', $site_tokens, array('node' => $site), $options);
    }

    if ($user_tokens = token_find_with_prefix($tokens, 'user')) {
      $user = user_load($profile->uid);
      $replacements += token_generate('user', $user_tokens, array('user' => $user), $options);
    }
  }

  return $replacements;
}

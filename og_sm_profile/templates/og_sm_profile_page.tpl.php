<?php
/**
 * @file
 * Markup for the site profile page.
 *
 * Variables:
 *
 * @var string $name
 *   The name of the user.
 * @var string $email
 *   The mail-address of the user.
 * @var array $sections
 *   An array of renderable arrays containing section info.
 */
?>
<div class="l-primary og-sm-profile">
  <div class="og-sm-profile__userinfo">
    <h2><?php print t('Profile') ?></h2>
    <h3><?php print $name ?></h3>
    <?php if ($email): ?>
    <address><?php print $email ?></address>
    <?php endif; ?>
  </div>

  <div class="og-sm-profile__sections">
    <?php print drupal_render($sections) ?>
  </div>
</div>

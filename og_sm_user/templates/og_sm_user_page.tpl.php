<?php
/**
 * @file
 * Markup for the site profile page.
 *
 * Variables:
 *
 * @var array $sections
 *   An array of renderable arrays containing section info.
 */
?>
<div class="l-primary og-sm-profile">
  <div class="og-sm-profile__sections">
    <?php print drupal_render($sections) ?>
  </div>
</div>

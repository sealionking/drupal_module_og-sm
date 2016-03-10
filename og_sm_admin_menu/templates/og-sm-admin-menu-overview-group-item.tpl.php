<?php
/**
 * @file
 * Template to render the Administrative overview group item.
 *
 * Variables:
 *
 * @var string $url
 *   The url of the item.
 * @var string $title
 *   The item title.
 * @var string $description
 *   The description for the item.
 * @var string $class
 *   The css class name for the item.
 */
?>

<div class="admin-block-item admin-config-<?php print $class; ?>">
  <dt>
    <a href="<?php print $url; ?>"><?php print $title; ?></a>
  </dt>
  <dd class="description">
    <?php print $description; ?>
  </dd>
</div>

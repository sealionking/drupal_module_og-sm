<?php

/**
 * @file
 * Template to render an Administrative overview group.
 *
 * Variables:
 *
 * @var string $title
 *   The title of the group.
 * @var array $items
 *   Array of items for the group.
 * @var string $class
 *   The class name to use for the group.
 */
?>

<div class="admin-panel admin <?php print $class; ?>">
  <h3 class="title"><?php print $title; ?></h3>

  <div class="body">
    <dl class="admin-list">
      <?php foreach($items as $item): ?>
        <?php print $item; ?>
      <?php endforeach; ?>
    </dl>
  </div>

</div>

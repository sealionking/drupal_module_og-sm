<?php
/**
 * @file
 * Template to render the Administrative overview page for a single group.
 *
 * Variables:
 *
 * @var array $items
 *   The items to show on the page.
 */
?>

<dl class="admin-list">
  <?php foreach ($items as $item): ?>
    <?php print $item; ?>
  <?php endforeach; ?>
</dl>

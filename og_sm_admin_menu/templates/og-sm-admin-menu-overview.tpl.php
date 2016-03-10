<?php
/**
 * @file
 * Template to render the Administrative overview page.
 *
 * Variables:
 *
 * @var array $left
 *   Array of groups to render in the left column.
 * @var array $right
 *   Array of groups to render in the right column.
 */
?>

<div class="admin clearfix">
  <?php if (!empty($left)): ?>
    <div class="left clearfix">
      <?php foreach ($left as $group): ?>
        <?php print $group; ?>
      <?php endforeach; ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($right)): ?>
    <div class="right clearfix">
      <?php foreach ($right as $group): ?>
        <?php print $group; ?>
      <?php endforeach; ?>
    </div>
  <?php endif; ?>
</div>

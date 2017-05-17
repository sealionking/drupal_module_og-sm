<?php

/**
 * @file
 * Object containing the Comment Override Config.
 */

/**
 * Object describing the Comment Override Config.
 */
class OgSmCommentOverrideConfig
{
  /**
   * Override is active.
   *
   * @var bool
   */
  private $overridable = FALSE;

  /**
   * A default value for the override.
   *
   * @var int|null
   */
  private $default;

  /**
   * Construct a new object from overridable & default value.
   *
   * @param bool $overridable
   *   Are the comment settings overridable per content item?
   * @param int|null $default
   *   The default comment level when the comment settings are overridable. Set
   *   to NULL not set a default value.
   */
  public function __construct($overridable, $default = NULL) {
    $this->overridable = (bool) $overridable;
    if ($this->overridable && $default !== NULL) {
      $this->default = (int) $default;
    }
  }

  /**
   * Are the comment settings overridable?
   *
   * @return bool
   *   Overridable.
   */
  public function isOverridable() {
    return $this->overridable;
  }

  /**
   * Has a default value.
   *
   * @return bool
   *   Has default value.
   */
  public function hasDefault() {
    return NULL !== $this->default;
  }

  /**
   * Get the default value.
   *
   * @return int|null
   *   The default value.
   */
  public function getDefault() {
    return $this->default;
  }

}

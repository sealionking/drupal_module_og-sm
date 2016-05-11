<?php
/**
 * @file
 * Hooks implemented to test the Variable defaults functionality.
 */

/**
 * Implements hook_og_sm_variable_defaults().
 */
function og_sm_variable_test_og_sm_variable_defaults($site) {
  return array(
    'og_sm_variable_test_1' => 'test value 1',
    'og_sm_variable_test_2' => 'test value 2',
  );
}

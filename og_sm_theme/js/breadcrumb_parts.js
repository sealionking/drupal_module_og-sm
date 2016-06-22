/**
 * @file
 * Javascript for the breadcrumb parts table.
 */

(function ($) {
  Drupal.behaviors.ogSmBreadcrumbPartsTable = {
    attach: function () {
      // States API doesn't work for our themed table. Toggle it here.
      $('input[name="override_root"]').once('breadcrumb-parts').change(function () {
        $('#edit-root-parts').slideToggle($(this).prop('checked'));
      });
    }
  };
})(jQuery);

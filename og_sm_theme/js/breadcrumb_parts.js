/**
 * @file
 * Javascript for the breadcrumb parts table.
 */

(function ($) {
  Drupal.behaviors.ogSmBreadcrumbPartsTable = {
    attach: function () {
      // States API doesn't work for our themed table. Toggle it here.
      $('input[name="override_root"]').once('breadcrumb-parts').change(function () {
        var $element = $('#edit-root-parts');
        if ($(this).prop('checked')) {
          $element.slideDown();
        }
        else {
          $element.slideUp();
        }
      }).change();
    }
  };
})(jQuery);

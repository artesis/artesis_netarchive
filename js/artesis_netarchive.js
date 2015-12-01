(function($) {

  Drupal.insertNetArchive = function (netCovers) {
    $.each(netCovers, function(id, netarchive) {
      var link = '<a href="' + netarchive + '" target="_blank">' + Drupal.t('Access via DBC Web Archive') + '</a>';
      $('.artesis-netarchive-id-' + id).html(link);
    });
  };

  Drupal.extractNetArchive = function (e) {
    var classname = $(e).attr('class');
    var id = classname.match(/artesis-netarchive-id-(\S+)/);
    if (!id) {
      return false;
    }

    return id[1];
  };

  Drupal.behaviors.netarchive = {
    attach: function(context) {
     var netArchiveData = [];

      $('.artesis-netarchive', context).each(function(i, e) {
        var netarchvie_id = Drupal.extractNetArchive(e);
        if (netarchvie_id) {
          netArchiveData.push(netarchvie_id);
        }
      });

      request = $.ajax({
        url: '/ting/netarchive',
        type: 'POST',
        data:{
          netArchiveData: netArchiveData
        },
        dataType: 'json',
        success: Drupal.insertNetArchive
      });
    },
    detach: function(context) {
      //If we have a request associated with the context then abort it.
      //It is obsolete.
      var request = $(context).data('request');
      if (request) {
        request.abort();
      }
    }
  };
} (jQuery));

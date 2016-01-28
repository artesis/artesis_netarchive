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
        var netarchive_id = Drupal.extractNetArchive(e);
        if (netarchive_id) {
          netArchiveData.push(netarchive_id);
        }
      });
      if (netArchiveData.length > 0) {
        $.getJSON(Drupal.settings.basePath + 'ting/netarchive/' + netArchiveData.join(','), {netarchive_data: netArchiveData}, Drupal.insertNetArchive);
      }
    }
  };
} (jQuery));

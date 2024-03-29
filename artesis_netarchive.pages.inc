<?php

/**
 * @file
 * Perform request for the netarchive links to the service.
 */

/**
 * Pass array of pdf links to js processing.
 */
function artesis_netarchive_objects($netarchive_data) {
  $ids = explode(',', $netarchive_data);

  $pdfs = _artesis_netarchive_objects($ids);
  drupal_json_output($pdfs);
  drupal_exit();
}

/**
 * Request data from Netarchive Service.
 *
 * @param array $ids
 *   Array of ting object ids.
 *
 * @return array
 *   Array of links to web service.
 */
function _artesis_netarchive_objects($ids) {
  $pdfs = [];

  try {
    $netarchive_url = variable_get('addi_wsdl_url', '');
    $netarchive_username = variable_get('addi_username', '');
    $netarchive_group = variable_get('addi_group', '');
    $netarchive_password = variable_get('addi_password', '');

    $service = new NetArchiveService($netarchive_url, $netarchive_username, $netarchive_group, $netarchive_password);
    $pdfs = $service->getByFaustNumber($ids);
  }
  catch (Exception $e) {
    watchdog_exception('artesis_netarchive', $e, 'Unable to retrieve pdf from MoreInfo: %message', ['%message' => $e->getMessage()]);
  }

  return $pdfs;
}

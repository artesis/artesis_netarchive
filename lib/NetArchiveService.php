<?php

/**
 * Recieve netarchive data from service.
 */

class NetArchiveService {

  private $wsdlUrl;
  private $username;
  private $group;
  private $password;

  public function __construct($wsdlUrl, $username, $group, $password) {
    $this->wsdlUrl = $wsdlUrl;
    $this->username = $username;
    $this->group = $group;
    $this->password = $password;
  }

  public function getByFaustNumber($faustNumber) {
    $identifiers = $this->collectIdentifiers('faust', $faustNumber);

    $response = $this->sendRequest($identifiers);
    $data = $this->extractNetArchiveLink($response);
    return $data;
  }

  protected function collectIdentifiers($idName, $ids) {
    if (!is_array($ids)) {
      $ids = array($ids);
    }

    $identifiers = array();
    foreach ($ids as $i) {
      $identifiers[] = array($idName => $i);
    }

    return $identifiers;
  }

  protected function sendRequest($identifiers) {
    $ids = array();
    foreach ($identifiers as $i) {
      $ids = array_merge($ids, array_values($i));
    }

    $authInfo = array(
      'authenticationUser' => $this->username,
      'authenticationGroup' => $this->group,
      'authenticationPassword' => $this->password,
    );
    $client = new SoapClient($this->wsdlUrl);

    try {
      $response = $client->moreInfo(
        array(
        'authentication' => $authInfo,
        'identifier' => $identifiers,
        )
      );
    }
    catch (Exception $e) {
      throw new Exception($e->getMessage());
    }

    return $response;
  }

  public function extractNetArchiveLink($response) {
    $additionalInformations = array();

    foreach ($response->identifierInformation as $info) {
      if (isset($info->netArchive)) {
        $additionalInformations[$info->identifier->faust] = $info->netArchive->_;
      }
    }

    return $additionalInformations;
  }
}

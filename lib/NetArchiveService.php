<?php

/**
 * @file
 * Receive netarchive data from service.
 */

class NetArchiveService {
  private $wsdlUrl;
  private $username;
  private $group;
  private $password;

  /**
   * Class constructor.
   *
   * @param $wsdlUrl
   *   Service wsdl url.
   * @param $username
   *   Service access username.
   * @param $group
   *   Service access group.
   * @param $password
   *   Service access password.
   */
  public function __construct($wsdlUrl, $username, $group, $password) {
    $this->wsdlUrl = $wsdlUrl;
    $this->username = $username;
    $this->group = $group;
    $this->password = $password;
  }

  /**
   * Get service link by faust number of the object.
   *
   * @param $faustNumber
   *   Faust number of the object.
   *
   * @return array
   *   Array of service links of the object.
   */
  public function getByFaustNumber($faustNumber) {
    $identifiers = $this->collectIdentifiers('faust', $faustNumber);

    $response = $this->sendRequest($identifiers);
    $data = $this->extractNetArchiveLink($response);
    return $data;
  }

  /**
   * Get object by one of its params.
   *
   * @param $idName
   *   Name of the parameter.
   * @param array $ids
   *   Array of parameters.
   * @return array
   *  Array of identifiers based on parameter and their names.
   */
  protected function collectIdentifiers($idName, array $ids) {
    $identifiers = array();
    foreach ($ids as $i) {
      $identifiers[] = array($idName => $i);
    }

    return $identifiers;
  }

  /**
   * Send the request to service.
   *
   * @param $identifiers
   *   Pass requested identifiers.
   * @return mixed
   *   Response object or error message.
   */
  protected function sendRequest($identifiers) {
    $authInfo = array(
      'authenticationUser' => $this->username,
      'authenticationGroup' => $this->group,
      'authenticationPassword' => $this->password,
    );
    $client = new SoapClient($this->wsdlUrl . '/?wsdl');

    try {
      $response = $client->moreInfo(
        array(
        'authentication' => $authInfo,
        'identifier' => $identifiers,
        )
      );
    }
    catch (Exception $e) {
      watchdog_exception('artesis_netarchive', $e);
    }

    return $response;
  }

  /**
   * Get array of netarchive links based on the object response from the service.
   *
   * @param \stdClass $response
   *   Service object response.
   * @return array
   *   Array of netarchive links.
   */
  public function extractNetArchiveLink(stdClass $response) {
    $additionalInformations = array();
    if (isset($response->identifierInformation)) {
      $identifiers = $response->identifierInformation;

      // If response has only one element, convert it to array.
      if (!is_array($response->identifierInformation)) {
        $identifiers = array($response->identifierInformation);
      }
      foreach ($identifiers as $info) {
        $identifier = $info->identifier;
        $netarchive = $info->netArchive;
        if (isset($netarchive)) {
          if (is_array($netarchive)) {
            $link = $netarchive[0]->_;
          }
          else {
            $link = $netarchive->_;
          }
          $additionalInformations[$identifier->faust] = $link;
        }
      }
    }

    return $additionalInformations;
  }
}

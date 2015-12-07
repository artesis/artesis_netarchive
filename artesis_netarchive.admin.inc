<?php
/**
 * @file
 * Configuration form for netarchive service.
 */

/**
 * Form builder; Configure ADDI settings for this site.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function artesis_netarchive_admin_settings_form($form, &$form_state) {
  $form['addi'] = array(
    '#type' => 'fieldset',
    '#title' => t('Additional Information settings'),
    '#description' => t('The Additional Information service is used to retrieve cover images. <a href="http://www.danbib.dk/index.php?doc=moreinfo">More information about the service (in Danish)</a>'),
  );

  $form['addi']['netarchive_wsdl_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Service URL'),
    '#description' => t('URL to the Additional Information webservice, e.g. http://moreinfo.addi.dk/2.1/'),
    '#required' => TRUE,
    '#default_value' => variable_get('netarchive_wsdl_url', ''),
  );

  $form['addi']['netarchive_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t('Service database username'),
    '#required' => TRUE,
    '#default_value' => variable_get('netarchive_username', ''),
  );

  $form['addi']['netarchive_group'] = array(
    '#type' => 'textfield',
    '#title' => t('Group'),
    '#description' => t('User group (normally library ID)'),
    '#required' => TRUE,
    '#default_value' => variable_get('netarchive_group', ''),
  );

  $form['addi']['netarchive_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#description' => t('Service database password'),
    '#required' => TRUE,
    '#default_value' => variable_get('netarchive_password', ''),
  );

  return system_settings_form($form);
}

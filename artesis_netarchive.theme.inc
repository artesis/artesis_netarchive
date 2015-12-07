<?php
/**
 * @file
 * Theme functions for DBC Web service link.
 */

/**
 * Style Netarchive link.
 *
 * @param $variables
 *   Ting object entity.
 *
 * @return string
 *   Themed netarchive link.
 */
function theme_artesis_netarchive_link_theme(&$variables) {
  return '<div class="' . implode(' ', $variables['classes']) . '"></div>';
}

/**
 * Add classes to netarchive link to trigger them from js.
 *
 * @param $variables
 *   Ting object entity.
 */
function template_preprocess_artesis_netarchive_link_theme(&$variables) {
  $object = $variables['object'] = $variables['elements']['#object'];

  $local_id = $object->getLocalId();

  // Set initial values required by the template.
  $variables['classes'] = array(
    'artesis-netarchive',
    'artesis-netarchive-id-' . $local_id,
  );
}

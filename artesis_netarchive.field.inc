<?php
/**
 * @file
 * Define netarchive link field.
 */

/**
 * Implements hook_field_info().
 */
function artesis_netarchive_field_info() {
  return array(
    'netarchive_link' => array(
      'label' => t('NetArchive Link'),
      'description' => t('NetArchive link to the PDF file from the moreinfo service, if any.'),
      'default_widget' => 'hidden',
      'default_formatter' => 'link_default',
      'virtual_field' => array(
        'entity_types' => array('ting_object'),
        'add_widget' => TRUE,
      ),
    ),
  );
}

/**
 * Implements hook_field_load().
 */
function artesis_netarchive_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    $items[$id][0] = array(
      'local_id' => $entity->getLocalId(),
    );
  }
}

/**
 * Implements hook_field_formatter_info_alter().
 */
function artesis_netarchive_field_formatter_info_alter(&$info) {
  if (isset($info['link_default'])) {
    $info['link_default']['field types'][] = 'netarchive_link';
    // Point formatter for the artesis netarchive module.
    $info['link_default']['module'] = 'artesis_netarchive';
  }
}

/**
 * Implements hook_field_formatter_view().
 */
function artesis_netarchive_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $path = drupal_get_path('module', 'artesis_netarchive');
  switch ($field['field_name']) {
    case 'netarchive_link':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'artesis_netarchive_link_theme',
          '#object' => $entity,
          '#attached' => array(
            'js' => array($path . '/js/artesis_netarchive.js'),
          ),
        );
      }
    break;
  }

  return $element;
}

/**
 * Implements hook_field_is_empty().
 */
function artesis_netarchive_field_is_empty($item, $field) {
  return empty($item['value']);
}

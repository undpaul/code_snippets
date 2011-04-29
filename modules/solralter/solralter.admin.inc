<?php
// $Id$

/**
 * @file
 *   Settings form for Solr  Alter.
 */

/**
 * Settings form for solralter.
 */
function solralter_settings_form() {
  $form = array();

  $nodetypes = node_get_types('names');

  $restricted_to = variable_get('solralter_nodetypes', FALSE);
  if (!$restricted_to || !is_array($restricted_to)) {
    $restricted_to = array_keys($nodetypes);
  }

  $form['solralter_nodetypes'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Node types'),
    '#description' => t('Enable all node types that shall be selectable on the apache solr search form'),
    '#options' => $nodetypes,
    '#default_value' => $restricted_to,
  );


  $form['solralter_nodetypemerge'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node type merge'),
    '#tree' => TRUE,
    '#description' => t('Select the nodetype that shall be merged to another in the faceted type block.'),
  );

  $merge = _solralter_nodetypemerge();
  foreach ($nodetypes as $nodetype => $name) {
    $form['solralter_nodetypemerge'][$nodetype] = array(
      '#title' => $name,
      '#type' => 'select',
      '#options' => $nodetypes,
      '#default_value' => isset($merge[$nodetype]) ? $merge[$nodetype] : $nodetype,
    );
  }

  return system_settings_form($form);
}

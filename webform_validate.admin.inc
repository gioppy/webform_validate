<?php
//$Id$

function webform_validate_setting(){
  $form = array();

  $form['wv_settings'] = array(
	'#type' => 'fieldset',
	'#title' => t('Webform Validate settings'),
	'#description' => t('General Settings for Webform Validate.'),
  );

  $node_types = node_type_get_names();
  $form['wv_settings']['node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Contet type to use ValidateWebform'),
    '#options' => $node_types,
	'#default_value' => variable_get('wv_settings_node_types', array()),
  );

  $form['wv_settings']['other_page'] = array(
    '#type' => 'textarea',
    '#title' => t('Extra page to use ValidateWebform'),
    '#description' => t('Add extra page path to use ValidateWebform.'),
    '#default_value' => variable_get('wv_settings_other_page', ""),
  );

  $form['wv_libraries'] = array(
    '#type' => 'fieldset',
    '#title' => t('ValidateWebform plugin')
  );

  $form['wv_libraries']['vw_js'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use minified version of ValidateWebform.js'),
    '#default_value' => variable_get('wv_libraries_vw_min', 0),
  );

  $form['#submit'][] = 'webform_validate_setting_submit';

  return system_settings_form($form);
}

function webform_validate_setting_submit($form, &$form_state){
  variable_set('wv_libraries_vw_min', $form_state['values']['vw_js']);
  $content_type = array();
  foreach($form_state['values']['node_types'] as $type){
    if($type){
      $content_type[] = $type;
    }
  }
  variable_set('wv_settings_node_types', $content_type);
  variable_set('wv_settings_other_page', $form_state['values']['other_page']);
}

?>
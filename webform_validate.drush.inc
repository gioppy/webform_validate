<?php

/**
 * @file
 *   drush integration for colorbox.
 */
 
define('VW_DOWNLOAD_URI', 'https://github.com/gioppy/ValidateWebform/archive/master.zip');
define('VW_DOWNLOAD_PREFIX', 'ValidateWebform-');

/**
 * Implementation of hook_drush_command().
 */ 
function webform_validate_drush_command(){
  $items = array();
  
  $items['vw-download'] = array(
    'description' => 'Download ValidateWebform jQuery plugin',
    'arguments' => array(),
    'examples' => array(
      'drush vw-download' => 'Download ValidateWebform jQuery plugin'
    ),
    'aliases' => array('vw-dl'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH
  );
  
  return $items;
}

/**
 * Implementation of hook_drush_help().
 */ 
function webform_validate_drush_help($section) {
  switch ($section) {
    case 'drush:vw-download':
      return dt('Download and install the ValidateWebform plugin from github.com/gioppy, default location is sites/all/libraries.');
  }
}
 
/**
 * Command to download the ValidateWebform plugin.
 */ 
function drush_webform_validate_vw_download(){
  $path = 'sites/all/libraries';
  
  // Create the path if it does not exist.
  if (!is_dir($path)) {
    drush_op('mkdir', $path);
    drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
  }
  
  // Set the directory to the download location.
  $olddir = getcwd();
  chdir($path);
  
  // Download the zip archive
  if ($filepath = drush_download_file(VW_DOWNLOAD_URI)) {
    $filename = basename($filepath);
    $dirname = VW_DOWNLOAD_PREFIX . basename($filepath, '.zip');

    // Remove any existing Colorbox plugin directory
    if (is_dir($dirname) || is_dir('ValidateWebform')) {
      drush_delete_dir($dirname, TRUE);
      drush_delete_dir('ValidateWebform', TRUE);
      drush_log(dt('A existing ValidateWebform plugin was deleted from @path', array('@path' => $path)), 'notice');
    }

    // Decompress the zip archive
    drush_tarball_extract($filename);

    // Change the directory name to "colorbox" if needed.
    if ($dirname != 'ValidateWebform') {
      drush_move_dir($dirname, 'ValidateWebform', TRUE);
      $dirname = 'ValidateWebform';
    }
  }
  
  if (is_dir($dirname)) {
    drush_log(dt('ValidateWebform plugin has been installed in @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to install the ValidateWebform plugin to @path', array('@path' => $path)), 'error');
  }

  // Set working directory back to the previous working directory.
  chdir($olddir);
}

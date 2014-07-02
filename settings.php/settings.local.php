<?php

/**
 * @file
 * Environment specific configuration file.
 *
 * @see shared.settings.php
 * @see default.settings.php
 */

/**
 * Include shared.settings.php for settings that are common in all environments.
 */
include(DRUPAL_ROOT . '/sites/default/shared.settings.php');

/**
 * Overrides for this environment.
 */

// Do not send any mails.
$conf['maillog_send'] = 0;
$conf['maillog_log'] = 1;
$conf['maillog_devel'] = 1;

$conf['mail_system'] = array(
  'default-system' => 'MaillogMailSystem',
  'maillog' => 'MaillogMailSystem',
);

// Search API solr settings.
$conf['search_api_override_mode'] = 'load';
$conf['search_api_override_servers'] = array(
  'tb_solr' => array(
    'name' => 'My Solr Server (overriden)',
    'options' => array(
      'host' => 'localhost',
      'port' => '8983',
      'path' => '/solr/mycore',
      'http_user' => '',
      'http_pass' => '',
      'excerpt' => 0,
      'retrieve_data' => 0,
      'highlight_data' => 0,
      'http_method' => 'POST',
    ),
  ),
);

/**
 * Include local.settings.php
 *
 * The file is in .gitignore so we can safely use it for local overrides, that
 * shall not be stored in the repository.
 */
if (file_exists('sites/default/local.settings.php')) {
  include('local.settings.php');
}


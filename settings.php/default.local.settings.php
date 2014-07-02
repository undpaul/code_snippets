<?php

/**
 * @file
 * Template for the local.settings.php, the file that shall not be pushed to git.
 */

// Database setting for the local
$databases['default']['default'] = array(
  'driver' => 'mysql',
  'database' => 'mydatabse',
  'username' => 'dbuser',
  'password' => 'dbpassword',
  'host' => 'localhost',
  'prefix' => '',
);


$conf['stage_file_proxy_origin'] = 'http://www.example.com';

// Search API solr settings.
$conf['search_api_override_mode'] = 'load';
$conf['search_api_override_servers'] = array(
  'tb_solr' => array(
    'name' => 'My Solr Server (overriden)',
    'options' => array(
      'host' => 'localhost',
      'port' => '8983',
      'path' => '/solr/myproject',
      'http_user' => '',
      'http_pass' => '',
      'excerpt' => 0,
      'retrieve_data' => 0,
      'highlight_data' => 0,
      'http_method' => 'POST',
    ),
  ),
);

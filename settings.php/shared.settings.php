<?php

/**
 * @file
 * Here we set all values that are valid for ALL stages.
 *
 * If any value listed in this file shall be overwritten by any stage specific
 * setting, it has to be removed from this file and added in any stage specific
 * settings.php.
 *
 * The rest will be set by the stage specific files like
 * - settings.local.php
 * - settings.develop.php
 * - settings.stage.php
 * - settings.live.php
 *
 */

// We include the default settings, so we do not need to copy the settings.php
// again on a core update.
include 'default.settings.php';

// Here we set values that are valid for ALL stages.
$conf['install_profile'] = 'minimal';

$conf['mail_system'] = array(
  'default-system' => 'DefaultMailSystem',
);

// As we use the update.sh to deploy our changes, we do a manuall features
// revert call, and therefore do not need a rebuild on flush caches.
$conf['features_rebuild_on_flush'] = FALSE;

// Disable default configurations of several modules for several hooks to remove
// them from the installation or make them exportable via features.
// @see https://drupal.org/sandbox/derhasi/2004516
$conf['disable_defaults'] = array(
  // Entityform shall not take full control over aliases and menu links.
  'entity_presave' => array(
    'entityform',
  ),
  'flag_default_flags' => array(
    'flag_abuse',
  ),
  // We want to have all our image styles defined in our features.
  'image_default_styles' => array(
    'image',
    'linkit',
    'media',
  ),
  // Avoid that file_entity and media override features exported file display
  // settings.
  'file_default_displays_alter' => array(
    'image',
    'media',
  ),
  // Make default file type settings exportable via features.
  'file_default_types' => array(
    'file_entity',
  ),
  'node_info' => array(
    'forum',
  ),
  // Remove the default views from contrib modules, that are not used or will be
  // overwritten in features.
  'views_default' => array(
    'admin_views',
    'comment',
    'content_menu',
    'media',
    'node',
    'redirect',
    'search',
    'statistics',
    'taxonomy',
    'views_bulk_operations',
    'votingapi',
  ),
);

// Master module settings.
// @see https://www.drupal.org/project/master
$conf['master_version'] = 2;
$conf['master_modules'] = array(
  'base' => array(
    // Features
    'myproject_base',
    'myproject_news',
  ),
);
$conf['master_modules']['local'] = array(
  // Dev modules.
  'stage_file_proxy',
  'maillog',
  'devel',
  'views_ui',
  'module_filter',
  'field_ui',
  'devel_generate',
  'rules_admin',
);
// Stage default..
$conf['master_modules']['stage'] = array(
  'stage_file_proxy',
  'maillog',
);
// Live sites.
$conf['master_modules']['live'] = array(
);

// Stage file proxy origin.
$conf['stage_file_proxy_origin'] = 'http://www.example.com';

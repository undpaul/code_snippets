<?php

/**
 * Implementation of hook_views_plugins().
 */
function views_goto_views_plugins(){
  return array(
    'display' => array(
      'goto' => array(
       'title' => t('Goto'),
        'help' => t('Display the view as a page, with a URL and menu links.'),
        'handler' => 'views_goto_plugin_display_goto',
        'theme' => 'views_view',
        'uses hook menu' => TRUE,
        'use ajax' => FALSE,
        'use pager' => FALSE,
        'accept attachments' => FALSE,
        'admin' => t('Goto'),
        'help topic' => 'display-goto',
        'parent' => 'page',
      ),
    ),
  );
}

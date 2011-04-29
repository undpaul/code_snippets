<?php
// $Id$;

/**
 * @file
 * Additional handling and data for i18ntaxonomy translated terms.
 */

/**
 * Implemenation of hook_views_data_alter().
 */
function i18ntaxonomyplus_views_data_alter(&$data) {
  // tid field
  $data['term_data']['tid_i18n'] = array(
    'group' => t('Taxonomy translation'),
    'title' => t('Term ID - translated'),
    'help' => t('The taxonomy term ID and all its translated IDs.'),
    'real field' => 'tid',
    'argument' => array(
      'handler' => 'i18ntaxonomyplus_argumemt_handler_tid',
      'skip base' => array('node', 'node_revision'),
      'zero is null' => TRUE,
    ),
  );

  // tid field
  $data['term_node']['tid_i18n'] = array(
    'group' => t('Taxonomy translation'),
    'title' => t('Term ID (node) - translated'),
    'help' => t('The taxonomy term ID - translated'),
    //'field' => array(
    //  'title' => t('All terms'),
    //  'help' => t('Display all taxonomy terms associated with a node from specified vocabularies.'),
    //  'handler' => 'views_handler_field_term_node_tid',
    //  'skip base' => 'term_data',
    //),
    'argument' => array(
      'handler' => 'i18ntaxonomyplus_argumemt_handler_term_node_tid',
      'handler' => 'views_handler_argument_term_node_tid',
      'name table' => 'term_data',
      'name field' => 'name',
      'empty field name' => t('Uncategorized'),
      'numeric' => TRUE,
      'skip base' => 'term_data',
    ),
    'filter' => array(
      'title' => t('Term with translation'),
      'handler' => 'views_handler_filter_term_node_tid',
      'hierarchy table' => 'term_hierarchy',
      'numeric' => TRUE,
      'skip base' => 'term_data',
      'allow empty' => TRUE,
    ),
  );

  $data['node']['term_node_tid_depth_i18n'] = array(
    'group' => t('Taxonomy translation'),
    'title' => t('Term ID (with depth) - translated'),
    'help' => t('The depth filter is more complex, so provides fewer options. It '),
    'real field' => 'vid',
    'argument' => array(
      'handler' => 'i18ntaxonomyplus_argument_handler_term_node_tid_depth',
      'accept depth modifier' => TRUE,
    ),
    'filter' => array(
      'handler' => 'i18ntaxonomyplus_filter_handler_term_node_tid_depth',
    ),
  );

   // Joins
  //$data['term_data']['table']['join']['term_data'] = array(
  //  'left_field' => 'trid',
  //  'field' => 'trid',
  //);

  // Language field
  $data['term_data']['language'] = array(
    'group' => t('Taxonomy translation'),
    'title' => t('Term Language'),
    'help' => t('The language the taxonomy term is of.'),
    'field' => array(
      'handler' => 'i18ntaxonomyplus_handler_field_term_language',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'i18ntaxonomyplus_handler_filter_term_language',
    ),
    'argument' => array(
      'handler' => 'i18ntaxonomyplus_handler_argument_term_language',
    ),
  );

  // The translations.
  $data['term_data']['translation'] = array(
    'group' => t('Taxonomy translation'),
    'title' => t('Term Translations'),
    'help' => t('Term in different languages.'),
    'relationship' => array(
      'title' => t('Term Translations'),
      'help' => t('Term in different languages.'),
      'base' => 'term_data',
      'base field' => 'trid',
      'relationship table' => 'term_data',
      'relationship field' => 'trid',
      'handler' => 'i18ntaxonomyplus_handler_relationship_term_translation',
      'label' => t('Term Translations'),
    ),
  );

}

/**
 * Implementation of hook_views_handlers().
 */
function i18ntaxonomyplus_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'i18ntaxonomyplus') . '/includes/views',
    ),
    'handlers' => array(
      'i18ntaxonomyplus_argumemt_handler_tid' => array(
        'parent' => 'views_handler_argument_numeric',
      ),
      'i18ntaxonomyplus_argumemt_handler_term_node_tid' => array(
        'handler' => 'views_handler_argument_term_node_tid',
      ),
      'i18ntaxonomyplus_filter_handler_term_node_tid' => array(
        'handler' => 'views_handler_filter_term_node_tid',
      ),
      'i18ntaxonomyplus_filter_handler_term_node_tid_depth' => array(
        'parent' => 'views_handler_filter_term_node_tid_depth',
      ),
      'i18ntaxonomyplus_argument_handler_term_node_tid_depth' => array(
        'parent' => 'views_handler_argument_term_node_tid_depth',
      ),
      'i18ntaxonomyplus_handler_filter_term_language' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
      'i18ntaxonomyplus_handler_field_term_language' => array(
        'parent' => 'views_handler_field_taxonomy',
      ),
      'i18ntaxonomyplus_handler_relationship_term_translation' => array(
        'parent' => 'views_handler_relationship',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_plugins().
 *
 * @see http://drupal.org/node/556172
 */
function i18ntaxonomyplus_views_plugins() {
  // Register plugins
  $plugins = array();
  $plugins['module'] = 'i18ntaxonomyplus';
  // Cache plugin: time-based with locale
  $plugins['cache']['i18ntaxonomyplus_plugin_cache_time_locale'] = array(
    'handler' => 'i18ntaxonomyplus_plugin_cache_time_locale', // Remember that the plugin filename has to be identical
    'help' => t('Simple time-based caching of data respecting the website language.'),
    'parent' => 'time',
    'path' => drupal_get_path('module', 'i18ntaxonomyplus') .'/includes/views',
    'title' => t('Time-based respecting website language'),
    'uses options' => TRUE,
  );
  return $plugins;
}

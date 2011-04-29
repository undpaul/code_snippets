; $Id$

@author: derhasi

Dependencies
============
Apache Solr (Apache Solr Search): http://drupal.org/project/apachesolr

Solr Alter
==========
Adds functionality to alter a solr query and so use multiple values for node type
filter.
Provides settings and a block for merging nodetypes to one facet.


Solr Alter Search Form
========================================
The module adds a checkbox selection of node types to the apache solr search
form to select multiple node types. If 'retain filters' is selected existing
type:[node_type] filters will be removed and replaced by the selected node types.

This module adds to run a 'OR'-search on node types by using the
'?filters=type:story type:page' syntax.

The idea to this module is provided in http://drupal.org/node/452874#comment-2934588.

You now can use the custom_search module (http://drupal.org/project/custom_search)
for providing blocks with multiple node type selection.

Settings
--------
You can select the nodetypes that can be selected on the search form.
The Settings page is located at admin/settings/apachesolr/solralter.
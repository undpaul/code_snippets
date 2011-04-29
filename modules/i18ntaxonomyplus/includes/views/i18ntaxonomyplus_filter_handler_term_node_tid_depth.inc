<?php


class i18ntaxonomyplus_filter_handler_term_node_tid_depth extends views_handler_filter_term_node_tid_depth {
  function query() {

    // Get all translated tids for the given tids
    foreach ($this->value as $tid) {
      $terms = i18ntaxonomy_term_get_translations(array('tid' => $tid));
      foreach ($terms as $term) {
        $this->value[] = $term->tid;
      }
    }

    $this->value = array_unique($this->value);
    parent::query();
  }
}
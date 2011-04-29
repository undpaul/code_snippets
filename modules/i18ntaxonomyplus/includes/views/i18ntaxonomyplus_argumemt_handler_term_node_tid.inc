<?php

/**
 * Provides a views argument, that applies not only a single term but all its translations as argument.
 */
class i18ntaxonomyplus_argumemt_handler_term_node_tid extends views_handler_argument_term_node_tid {

  function query() {
    $empty = FALSE;
    if (isset($this->definition['zero is null']) && $this->definition['zero is null']) {
      if (empty($this->argument)) {
        $empty = TRUE;
      }
    }
    else {
      if (!isset($this->argument)) {
        $empty = TRUE;
      }
    }
    if ($empty) {
      parent::ensure_my_table();
      $this->query->add_where(0, "$this->table_alias.$this->real_field IS NULL");
      return;
    }

    if (!empty($this->options['break_phrase'])) {
      views_break_phrase($this->argument, $this);
    }
    else {
      $this->value = array($this->argument);
      $this->operator = 'or';
    }

    // Get all translated tids for the given tids
    foreach ($this->value as $tid) {
      $terms = i18ntaxonomy_term_get_translations(array('tid' => $tid));
      foreach ($terms as $term) {
        $this->value[] = $term->tid;
      }
    }
    $this->value = array_unique($this->value);

    $this->helper->add_filter();
  }

}
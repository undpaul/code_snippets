<?php
// $Id$
/**
 * @file
 * Handler for using tid and its translations as argument.
 */

/**
 * Basic argument handler for arguments that are numeric. Incorporates
 * break_phrase.
 *
 * @ingroup views_argument_handlers
 */
class i18ntaxonomyplus_argumemt_handler_tid extends views_handler_argument_numeric {

  /**
   * Modified views_handler_argument_numeric::query() to implement translated tids.
   */
  function query() {
    $this->ensure_my_table();

    if (!empty($this->options['break_phrase'])) {
      views_break_phrase($this->argument, $this);
    }
    else {
      $this->value = array($this->argument);
    }

    // Get all translated tids for the given tids
    foreach ($this->value as $tid) {
      $terms = i18ntaxonomy_term_get_translations(array('tid' => $tid));
      foreach ($terms as $term) {
        $this->value[] = $term->tid;
      }
    }

    $this->value = array_unique($this->value);

    if (count($this->value) > 1) {
      $operator = empty($this->options['not']) ? 'IN' : 'NOT IN';
      $placeholders = implode(', ', array_fill(0, sizeof($this->value), '%d'));
      $this->query->add_where(0, "$this->table_alias.$this->real_field $operator ($placeholders)", $this->value);
    }
    else {
      $operator = empty($this->options['not']) ? '=' : '!=';
      $this->query->add_where(0, "$this->table_alias.$this->real_field $operator %d", $this->argument);
    }
  }

}
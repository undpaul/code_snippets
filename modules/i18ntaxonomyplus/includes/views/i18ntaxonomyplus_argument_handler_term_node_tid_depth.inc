<?php

class i18ntaxonomyplus_argument_handler_term_node_tid_depth extends views_handler_argument_term_node_tid_depth {

  function query() {
    $this->ensure_my_table();

    if (!empty($this->options['break_phrase'])) {
      $tids = new stdClass();
      $tids->value = $this->argument;
      $tids = views_break_phrase($this->argument, $tids);
      if ($tids->value == -1) {
        return FALSE;
      }

      $tids = $tids->value;
    }
    else {
      $tids = array($this->argument);
    }

    // Get all translated tids for the given tids
    foreach ($tids as $tid) {
      $terms = i18ntaxonomy_term_get_translations(array('tid' => $tid));
      foreach ($terms as $term) {
        $tids[] = $term->tid;
      }
    }
    $tids = array_unique($tids);

    if (count($tids) > 1) {
      $placeholder = " IN (" . implode(', ', array_fill(0, sizeof($tids), '%d')) . ")";
    }
    else {
      $placeholder = " = %d";
    }

    $subquery = "\n  SELECT tn.vid FROM {term_node} tn\n";
    $where = "  WHERE tn.tid $placeholder\n";
    $args = $tids;
    $last = "tn";

    if ($this->options['depth'] > 0) {
      $subquery .= "    LEFT JOIN {term_hierarchy} th ON th.tid = tn.tid\n";
      $last = "th";
      foreach (range(1, abs($this->options['depth'])) as $count) {
        $subquery .= "    LEFT JOIN {term_hierarchy} th$count ON $last.parent = th$count.tid\n";
        $where .= "    OR th$count.tid $placeholder\n";
        $args = array_merge($args, $tids);
        $last = "th$count";
      }
    }
    else if ($this->options['depth'] < 0) {
      foreach (range(1, abs($this->options['depth'])) as $count) {
        $subquery .= "    LEFT JOIN {term_hierarchy} th$count ON $last.tid = th$count.parent\n";
        $where .= "    OR th$count.tid $placeholder\n";
        $args = array_merge($args, $tids);
        $last = "th$count";
      }
    }

    $this->query->add_where(0, "$this->table_alias.$this->real_field IN ($subquery$where  )", $args);
  }

}
<?php

/**
 * The plugin that handles a goto.
 *
 * @ingroup views_display_plugins
 */
class views_goto_plugin_display_goto extends views_plugin_display_page {
  function uses_breadcrumb() { return FALSE; }
  //function get_style_type() { return 'feed'; }

  /**
   * Feeds do not go through the normal page theming mechanism. Instead, they
   * go through their own little theme function and then return NULL so that
   * Drupal believes that the page has already rendered itself...which it has.
   */
  function execute() {
    $output = $this->view->render();
    if (empty($output)) {
      return drupal_not_found();
    }
    print $output;
  }

  function preview() {
    if (count($this->view->result)){
      $first = current($this->view->result);
      if ($first->nid) {
        return "<pre>" . node_view(node_load($first->nid)) . "</pre>";
      }
    }
    //return '<pre>' . check_plain($this->view->render()) . '</pre>';
  }

  /**
   * Instead of going through the standard views_view.tpl.php, delegate this
   * to the style handler.
   */
  function render() {
    if (count($this->view->result)){
      $first = current($this->view->result);
      if ($first->nid) {
        drupal_goto("node/$first->nid");
      }
    }
    return $this->view->style_plugin->render($this->view->result);
  }

}

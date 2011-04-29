<?php
// $Id$

/**
 * @file
 *   Formatters for multilingual content taxonomy fields.
 */

/**
 * Theme function for 'text_translated' text field formatter.
 */
function theme_i18ntaxonomyplus_formatter_text_translated($element) {
  if (!empty($element['#item']['value'])) {
    $tid = $element['#item']['value'];
    $term = _i18ntaxonomy_get_current_language_term($tid);
    return check_plain($term->name);
  }
}


/**
 * Theme function for 'link_translated' text field formatter.
 */
function theme_i18ntaxonomyplus_formatter_link_translated($element) {
  if (!empty($element['#item']['value'])) {
    $tid = $element['#item']['value'];
    $term = _i18ntaxonomy_get_current_language_term($tid);
    // The tid is set to the original one, to create a link to the orignal.
    $term->tid = $tid;

    return l($term->name, taxonomy_term_path($term), array('attributes' => array('rel' => 'tag', 'title' => $term->description)));
  }
}

/**
 * Theme function for 'link_totranslated' text field formatter.
 */
function theme_i18ntaxonomyplus_formatter_link_totranslated($element) {
  if (!empty($element['#item']['value'])) {
    $tid = $element['#item']['value'];
    $term = _i18ntaxonomy_get_current_language_term($tid);
    return l($term->name, taxonomy_term_path($term), array('attributes' => array('rel' => 'tag', 'title' => $term->description)));
  }
}

/**
 * Helper to get current language term.
 */
function _i18ntaxonomy_get_current_language_term($tid) {
  $lang = i18n_get_lang();
  $terms = i18ntaxonomy_term_get_translations(array('tid' => $tid));

  // There is a related language version of the tid.
  if (is_array($terms) && isset($terms[$lang])) {
    $current_language_term = $terms[$lang];
  }
  // If there is no translated term in the given language, try to fetch the original
  elseif(is_array($terms)) {
    foreach ($terms as $term) {
      if ($term->tid == $tid) {
        $current_language_term = $term;
        break;
      }
    }
    // No term found for tid.
    if (!isset($current_language_term)) {
      return NULL;
    }
    _content_taxonomy_localize_term($current_language_term);
  }
  else {
    return NULL;
  }

  return $current_language_term;
}
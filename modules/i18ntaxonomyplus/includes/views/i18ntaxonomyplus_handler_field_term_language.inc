<?php

/**
 * Field handler to translate a language into its readable form.
 */
class i18ntaxonomyplus_handler_field_term_language extends views_handler_field_taxonomy {
  function render($values) {
    $languages = locale_language_list();
    $value = isset($languages[$values->{$this->field_alias}]) ? $languages[$values->{$this->field_alias}] : '';
    return $this->render_link($value, $values);
  }
}

<?php
// $Id$

/**
 * @file
 * Cache plugin: time-based respecting website language
 *
 * @author hctom <info@hctom.net>
 */

////////////////////////////////////////////////////////////////////////////////
//
//  Plugin
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Cache plugin respecting th ewebsite language.
 */
class i18ntaxonomyplus_plugin_cache_time_locale extends views_plugin_cache_time {

  //////////////////////////////////////////////////////////////////////////////
  //
  //  Method implementations
  //
  //////////////////////////////////////////////////////////////////////////////

  /**
   * Implementation of option_defaults().
   */
  function option_defaults(&$options) {
    parent::option_defaults($options);
    $options['respect_website_language'] = 1;
  }

  /**
   * Implementation of options_form().
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    // Checkbox: use locale for cache key?
    $form['respect_website_language'] = array(
    '#default_value' => array_key_exists('respect_website_language', $this->options) ? $this->options['respect_website_language'] : 1,
    '#description' => t('Whether the website language should be respected when caching.'),
    '#required' => FALSE,
    '#return_value' => 1,
    '#title' => t('Respect website language'),
    '#type' => 'checkbox'
    );
  }

  /**
   * Implementation of get_output_key().
   */
  function get_output_key() {
    global $language;
    // Do not use locale
    if (!$this->options['respect_website_language']) {
      return parent::get_output_key();
    }
    // Use locale
    if (!isset($this->_output_key)) {
      $this->_output_key = parent::get_output_key() .':'. $language->language;
    }
    return $this->_output_key;
  }

  /**
   * Implementation of get_results_key().
   */
  function get_results_key() {
    global $language;
    // Do not use locale
    if (!$this->options['respect_website_language']) {
      return parent::get_results_key();
    }
    // Use locale
    if (!isset($this->_results_key)) {
      $this->_results_key = parent::get_results_key() .':'. $language->language;
    }
    return $this->_results_key;
  }

}
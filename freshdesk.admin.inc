<?php

/**
 * @file
 * Provides admin settings form(s) for Freshdesk module
 */

/**
 * The form to provide admin settings for the SS Newsletter Module
 */
function freshdesk_admin_account($form, &$form_state) {

  $form = array();
  $form['freshdesk_url'] = array(
    '#type' => 'textfield',
    '#size' => '100',
    '#title' => t('URL of your Freshdesk Account'),
    '#description' => t('Highly advisable to use the HTTPS version. ex. https://example.freshdesk.com'),
    '#default_value' => variable_get('freshdesk_url', ''),
  );
  $form['freshdesk_api_key'] = array(
    '#type' => 'textfield',
    '#size' => '40',
    '#title' => t('API Key for Freshdesk Agent Account'),
    '#description' => t('Freshdesk API keys are agent specific, there is no key for the account in general.  Go <a href="@url">here</a> to read how to obtain a key', array('@url' => 'http://freshdesk.com/api#authentication')),
    '#default_value' => variable_get('freshdesk_api_key', ''),
  );

  $form['freshdesk_sso'] = array(
    '#type' => 'fieldset',
    '#title' => t('Single Sign-On Configuration'),
    '#collapsible' => FALSE,
  );  
  $form['freshdesk_sso']['freshdesk_sso_intro'] = array(
    '#markup' => t('This creates a Simple SSO launch page at the path <tt>freshdesk/support/portal</tt>. <br />If you want to alter this path you can use a module such as Pathauto to do so.'),
    );
  $form['freshdesk_sso']['freshdesk_sso_key'] = array(
    '#type' => 'textfield',
    '#size' => '100',
    '#title' => t('SSO Secret Key'),
    '#default_value' => variable_get('freshdesk_sso_key', ''),
    '#description' => t('Instructions on obtaining this key are available on Freshdesk support <a href="@url">page</a>', array('@url' => 'https://support.freshdesk.com/support/solutions/articles/31166-single-sign-on-remote-authentication-in-freshdesk'))
  );

  return system_settings_form($form);
}

/**
 * The form to provide Feedback Popup widget
 */
function freshdesk_admin_widget_popup($form, &$form_state) {

  $form = array();

  return system_settings_form($form);
}

/**
 * The form to provide Feedback Embed widget
 */
function freshdesk_admin_widget_embed($form, &$form_state) {

  $form = array();

  return system_settings_form($form);
}

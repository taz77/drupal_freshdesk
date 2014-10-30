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
  $form['intro'] = array(
    '#prefix' => '<span style="font-size: 1.2em;">',
    '#markup' => t('This will allow you to enable and customize the Freshdesk JS popup widget. Currently this turns on the popup site wide.'),
    '#suffix' => '</span>',
  );
  $form['intro1'] = array(
    '#prefix' => '<span style="font-size: 1.8em;">',
    '#markup' => t('This is unfinished at the moment.'),
    '#suffix' => '</span>',
  );
  $form['freshdesk_widget_popup_control'] = array(
    '#type' => 'fieldset',
    '#title' => t('Popup control settings'),
    '#collapsible' => FALSE,
  );
  $form['freshdesk_widget_popup_control']['freshdesk_widget_popup_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Check this box to enable the popup.')
  );
  $form['freshdesk_widget_popup_button_type'] = array(
    '#type' => 'fieldset',
    '#title' => t('Button Settings'),
    '#collapsible' => FALSE,
  );
  $form['freshdesk_widget_popup_button_type']['freshdesk_widget_popup_type'] = array(
    '#type' => 'select',
    '#title' => t('Type of display, button or text'),
    '#description' => t('Do you want to display an image to click or text to click for the popup?'),
    '#options' => array(
      'button' => t('Button'),
      'text' => t('Text'),
    ),
    '#default_value' => variable_get('freshdesk_widget_popup_type', 'button'),
  );
  $form['freshdesk_widget_popup_button_type']['freshdesk_widget_popup_position'] = array(
    '#type' => 'select',
    '#title' => t('Button position'),
    '#description' => t('Position of the overlayed popup button or image button on the page.'),
    '#options' => array(
      4 => t('Left'),
      2 => t('Right'),
      1 => t('Top'),
      3 => t('Bottom'),
    ),
    '#default_value' => variable_get('freshdesk_widget_popup_position', 4),
  );

  return system_settings_form($form);
}

/**
 * The form to provide Feedback Embed widget
 */
function freshdesk_admin_widget_embed($form, &$form_state) {

  $form = array();

  return system_settings_form($form);
}

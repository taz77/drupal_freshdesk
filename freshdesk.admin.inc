<?php

/**
 * @file
 * Provides admin settings form(s) for Freshdesk module.
 */

/**
 * The form to provide admin settings for the Freshdesk module.
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

  return system_settings_form($form);
}

/**
 * The form to provide Feedback Popup widget.
 */
function freshdesk_admin_widget_popup($form, &$form_state) {
  $form = array();
  $form['intro'] = array(
    '#prefix' => '<span style="font-size: 1.2em;">',
    '#markup' => t('This will allow you to enable and customize the Freshdesk JS popup widget. Currently this turns on the popup site wide. Changes to this form will require a clearing of the template cache.'),
    '#suffix' => '</span>',
  );
  $form['freshdesk_widget_popup_control'] = array(
    '#type' => 'fieldset',
    '#title' => t('Popup control settings'),
    '#collapsible' => FALSE,
  );
  $form['freshdesk_widget_popup_control']['freshdesk_widget_popup_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Check this box to enable the popup.'),
    '#default_value' => variable_get('freshdesk_widget_popup_enable', 0),
  );
  $form['freshdesk_widget_popup_control']['freshdesk_widget_popup_form_responsive'] = array(
    '#type' => 'checkbox',
    '#title' => t('Uncheck this to not use responsive layout.'),
    '#default_value' => variable_get('freshdesk_widget_popup_form_responsive', 1),
    '#prefix' => '<em>' . t('Responsive layout control') . '</em>',
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
      0 => t('Please Select'),
      'button' => t('Button'),
      'text' => t('Text'),
    ),
    '#default_value' => variable_get('freshdesk_widget_popup_type'),
    '#ajax' => array(
      'callback' => 'freshdesk_ajax_type_attribute',
      'wrapper' => 'replace_freshdesk_type_attribute',
    ),
  );
  if (variable_get('freshdesk_widget_popup_type')) {
    $popup_type = variable_get('freshdesk_widget_popup_type');
    switch ($popup_type) {
      case 'text':
        $att_title = t('Button Text');
        $att_description = t('What do you want the button to say?');
        break;

      case 'button':
        $att_title = t('URL to button image');
        $att_description = t('What image do you want to use? Freshdesk provides a button here: https://s3.amazonaws.com/assets.freshdesk.com/widget/help-button.png');
        break;

      default:
        $att_title = t('Select Type First');
        $att_description = '';
        break;
    }
  }
  else {
    $att_title = t('Select Type First');
    $att_description = '';
  }
  $form['freshdesk_widget_popup_button_type']['freshdesk_widget_popup_type_attribute'] = array(
    '#type' => 'textfield',
    '#title' => $att_title,
    '#description' => $att_description,
    '#default_value' => variable_get('freshdesk_widget_popup_type_attribute'),
    '#size' => 100,
    '#prefix' => '<div id="replace_freshdesk_type_attribute">',
    '#suffix' => '</div>',
  );
  if (!empty($form_state['values']['freshdesk_widget_popup_type'])) {

    if ($form_state['values']['freshdesk_widget_popup_type'] == 'text') {
      $form['freshdesk_widget_popup_button_type']['freshdesk_widget_popup_type_attribute']['#title'] = t('Button Text');
      $form['freshdesk_widget_popup_button_type']['freshdesk_widget_popup_type_attribute']['#description'] = t('What do you want the button to say?');
    }
    if ($form_state['values']['freshdesk_widget_popup_type'] == 'button') {
      $form['freshdesk_widget_popup_button_type']['freshdesk_widget_popup_type_attribute']['#title'] = t('URL to button image');
      $form['freshdesk_widget_popup_button_type']['freshdesk_widget_popup_type_attribute']['#description'] = t('What image do you want to use? Freshdesk provides a button here: https://s3.amazonaws.com/assets.freshdesk.com/widget/help-button.png');
    }
  }
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
  $form['freshdesk_widget_popup_button_type']['freshdesk_widget_popup_offset'] = array(
    '#type' => 'textfield',
    '#title' => t('Offset'),
    '#description' => t('Offset distance from the left or top of the screen in pixels.'),
    '#field_suffix' => t('px'),
    '#default_value' => variable_get('freshdesk_widget_popup_offset', 235),
    '#size' => 5,
  );
  $form['freshdesk_widget_popup_customize_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Customize Form'),
    '#collapsible' => FALSE,
  );
  $requester_value = array(
    0 => t('Pre-populated with the current user\'s e-mail address'),
    1 => t('Blank or pre-populated with a custom e-mail address'),
  );
  $form['freshdesk_widget_popup_customize_form']['freshdesk_widget_popup_form_requester'] = array(
    '#type' => 'radios',
    '#title' => t('Requester e-mail address'),
    '#default_value' => variable_get('freshdesk_widget_popup_form_requester'),
    '#options' => $requester_value,
  );
  $form['freshdesk_widget_popup_customize_form']['freshdesk_widget_popup_form_requester_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom value'),
    '#default_value' => variable_get('freshdesk_widget_popup_form_requester_value'),
    '#states' => array(
      'visible' => array(
        ':input[name="freshdesk_widget_popup_form_requester"]' => array('value' => 1),
      ),
    ),
    '#description' => t('Leave blank to prompt the end-user for an e-mail address, or pre-populate with a custom e-mail address.'),
  );
  $form['freshdesk_widget_popup_customize_form']['freshdesk_widget_popup_form_requester_disable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable Requester Field'),
    '#default_value' => variable_get('freshdesk_widget_popup_form_requester_disable', 0),
    '#description' => t('If you enable this, the user will not be able to change the requester email addresss on the ticket.'),
  );
  $form['freshdesk_widget_popup_customize_form']['freshdesk_widget_popup_form_heading'] = array(
    '#type' => 'textfield',
    '#title' => t('Form Heading'),
    '#default_value' => variable_get('freshdesk_widget_popup_form_heading', 'Help and Support'),
    '#size' => 120,
  );
  $form['freshdesk_widget_popup_customize_form']['freshdesk_widget_popup_form_submit_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Submit Message'),
    '#default_value' => variable_get('freshdesk_widget_popup_form_submit_message', 'Thank you for your feedback'),
    '#rows' => 2,
    '#cols' => 100,
  );
  $form['freshdesk_widget_popup_customize_form']['freshdesk_widget_popup_form_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Form Height'),
    '#description' => t('Height of the form in pixels.'),
    '#field_suffix' => t('px'),
    '#default_value' => variable_get('freshdesk_widget_popup_form_height', 500),
    '#size' => 5,
  );
  $form['freshdesk_widget_popup_customize_form']['freshdesk_widget_popup_form_screenshot'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow users to take screenshots?'),
    '#default_value' => variable_get('freshdesk_widget_popup_form_screenshot', 1),
  );
  $form['freshdesk_widget_popup_customize_form']['freshdesk_widget_popup_form_attach'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow users to attach files?'),
    '#default_value' => variable_get('freshdesk_widget_popup_form_attach', 1),
  );
  $form['freshdesk_widget_popup_customize_form']['freshdesk_widget_popup_form_search'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow users to search articles?'),
    '#default_value' => variable_get('freshdesk_widget_popup_form_search', 1),
  );
  $form['freshdesk_widget_popup_paths'] = array(
    '#type' => 'textarea',
    '#title' => t('Paths'),
    '#default_value' => variable_get('freshdesk_widget_popup_paths', ''),
    '#rows' => 8,
    '#cols' => 128,
    '#required' => FALSE,
    '#description' => t('A list of paths to exclude from the displaying the popup widget. Each separated by a new line.'),
  );
  // Render the role overview.
  $result = db_query('SELECT * FROM {role} ORDER BY rid');

  $form['freshdesk_widget_popup_roles_set']['freshdesk_widget_popup_roles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display of Widget for Roles'),
    '#collapsible' => TRUE,
    '#description' => t('Define what user roles should be given the popup widget.'),
  );

  foreach ($result as $role) {
    // Can't use empty spaces in varname.
    $role_name = $role->name;
    $role_varname = str_replace(' ', '_', $role_name);
    $form['freshdesk_widget_popup_roles_set']['freshdesk_widget_popup_roles']['freshdesk_widget_popup_roles_' . $role_varname] = array(
      '#type' => 'checkbox',
      '#title' => t(ucfirst($role_name)),
      '#default_value' => variable_get('freshdesk_widget_popup_roles_' . $role_varname, FALSE),
    );
  }
  $form['information'] = array(
    '#markup' => t('We only implement the SSL version of the form for this module. So there is no switch for SSL.'),
  );
  return system_settings_form($form);
}

/**
 * The form to provide Feedback Embed widget.
 */
function freshdesk_admin_widget_embed($form, &$form_state) {
  $form = array();
  $form['intro'] = array(
    '#prefix' => '<div style="font-size: 1.2em;">',
    '#markup' => t('This will allow you to enable and customize the Freshdesk embed widget and apply it to the bottom of pages. Changes to this form will require a clearing of the template cache.'),
    '#suffix' => '</div>',
  );
  $form['freshdesk_widget_embed_customize_form']['freshdesk_widget_embed_form_heading'] = array(
    '#type' => 'textfield',
    '#title' => t('Form Heading'),
    '#default_value' => variable_get('freshdesk_widget_embed_form_heading', 'Help and Support'),
    '#size' => 120,
  );
  $form['freshdesk_widget_embed_customize_form']['freshdesk_widget_embed_form_submit_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Submit Message'),
    '#default_value' => variable_get('freshdesk_widget_embed_form_submit_message', 'Thank you for your feedback'),
    '#rows' => 2,
    '#cols' => 100,
  );
  $requester_value = array(
    0 => t('Pre-populated with the current user\'s e-mail address'),
    1 => t('Blank or pre-populated with a custom e-mail address'),
  );
  $form['freshdesk_widget_embed_customize_form']['freshdesk_widget_embed_form_requester'] = array(
    '#type' => 'radios',
    '#title' => t('Requester e-mail address'),
    '#default_value' => variable_get('freshdesk_widget_embed_form_requester'),
    '#options' => $requester_value,
  );
  $form['freshdesk_widget_embed_customize_form']['freshdesk_widget_embed_form_requester_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom value'),
    '#default_value' => variable_get('freshdesk_widget_embed_form_requester_value'),
    '#states' => array(
      'visible' => array(
        ':input[name="freshdesk_widget_embed_form_requester"]' => array('value' => 1),
      ),
    ),
    '#description' => t('Leave blank to prompt the end-user for an e-mail address, or pre-populate with a custom e-mail address.'),
  );
  $form['freshdesk_widget_embed_customize_form']['freshdesk_widget_embed_form_requester_disable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable Requester Field'),
    '#default_value' => variable_get('freshdesk_widget_embed_form_requester_disable', 0),
    '#description' => t('If you enable this, the user will not be able to change the requester email addresss on the ticket.'),
  );
  $form['freshdesk_widget_embed_customize_form']['freshdesk_widget_embed_form_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Form Height'),
    '#description' => t('Height of the form in pixels. Test these settings based on the options you choose to display as you may need to make this larger or smaller.'),
    '#field_suffix' => t('px'),
    '#default_value' => variable_get('freshdesk_widget_embed_form_height', 500),
    '#size' => 5,
  );
  $form['freshdesk_widget_embed_customize_form']['freshdesk_widget_embed_form_search'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow users to search articles?'),
    '#default_value' => variable_get('freshdesk_widget_embed_form_search', 1),
  );
  $form['freshdesk_widget_embed_customize_form']['freshdesk_widget_embed_form_attach'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow users to attach files?'),
    '#default_value' => variable_get('freshdesk_widget_embed_form_attach', 1),
  );
  $form['information'] = array(
    '#prefix' => '<div style="font-size: 1.2em; margin-bottom: 20px; margin-top:20px;">',
    '#markup' => t('We only implement the SSL version of the form for this module. So there is no switch for SSL.'),
    '#suffix' => '</div>',
  );
  $form['tokennotice'] = array(
    '#prefix' => '<div style="font-size: 1.2em;">',
    '#markup' => t('This module creates a token [freshdesk:freshdeskembed] that can be used through the token system. One method is to use the module') . ' ' . l('Token Filter', 'https://www.drupal.org/project/token_filter') . ' ' . t('to include this form into content at places you designate in the content of a node.'),
    '#suffix' => '</div>',
  );
  return system_settings_form($form);
}

/**
 * AJAX callback to replace button attribute.
 */
function freshdesk_ajax_type_attribute($form, $form_state) {
  return $form['freshdesk_widget_popup_button_type']['freshdesk_widget_popup_type_attribute'];
}

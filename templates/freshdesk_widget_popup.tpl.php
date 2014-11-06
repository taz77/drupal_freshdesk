<?php
/**
 * @file
 * Freshbook template for popup feedback widget.
 */

// Setting button text based on popup type and the attribute variable.
if ($freshdesk_widget_popup_type == 'text') {
  $btext = $freshdesk_widget_popup_type_attribute;
}
else {
  $btext = 'Support';
}
// We must built the query string based on options to insert into the JS.
$qsting = '&widgetType=popup';
if (empty($freshdesk_widget_popup_form_responsive)) {
  $qsting .= '&responsive=no';
}
if (!empty($freshdesk_widget_popup_form_heading)) {
  $qsting .= '&formTitle=' . $freshdesk_widget_popup_form_heading;
}
if (!empty($freshdesk_widget_popup_form_submit_message)) {
  $qsting .= '&submitThanks=' . $freshdesk_widget_popup_form_submit_message;
}
if (empty($freshdesk_widget_popup_form_screenshot)) {
  $qsting .= '&screenshot=no';
}
if (empty($freshdesk_widget_popup_form_attach)) {
  $qsting .= '&attachFile=no';
}
if (empty($freshdesk_widget_popup_form_search)) {
  $qsting .= '&searchArea=no';
}
?>

<script type="text/javascript" src="https://s3.amazonaws.com/assets.freshdesk.com/widget/freshwidget.js"></script>
<script type="text/javascript">
  FreshWidget.init("", {"queryString": "<?php print $qsting ?>",
    "widgetType": "popup",
    "buttonType": "<?php print $freshdesk_widget_popup_type; ?>",
    "buttonText": "<?php print $btext; ?>",
    "buttonColor": "white",
    "buttonBg": "#006063",
    "alignment": "<?php print $freshdesk_widget_popup_position; ?>",
    "offset": "<?php print $freshdesk_widget_popup_offset; ?>px",
    "formHeight": "<?php print $freshdesk_widget_popup_form_height; ?>",
    "url": "<?php print $fresdesk_url; ?>"});
</script>

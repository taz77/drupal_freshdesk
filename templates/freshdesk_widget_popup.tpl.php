<?php
/**
 * @file
 * Freshbook template for popup feedback widget.
 */
?>

<script type="text/javascript" src="https://s3.amazonaws.com/assets.freshdesk.com/widget/freshwidget.js"></script>
<script type="text/javascript">
  FreshWidget.init("", {"queryString": "&widgetType=popup",
    "widgetType": "popup",
    "buttonType": "text",
    "buttonText": "Support",
    "buttonColor": "white",
    "buttonBg": "#006063",
    "alignment": "4",
    "offset": "235px",
    "formHeight": "500px",
    "url": "<?php print $fresdesk_url; ?>"});
</script>

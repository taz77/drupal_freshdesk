

        FRESDESK MODULE - README
______________________________________________________________________________

NAME:       Freshdesk
AUTHORS:    Brady Owens <info@fastglass.net>
______________________________________________________________________________


DESCRIPTION

This module allows some level of integration between your Drupal website and
the Freshdesk support service.


INSTALLATION

Step 1) Download latest release from https://www.drupal.org/project/freshdesk

Step 2)
  Extract the package into your 'modules' directory.

Step 3)
  Enable the forward module.

  Go to "/admin/modules" and put a checkmark in the 'Enabled' column next to
  'Forward'.

Step 4)
  Go to "/admin/config/services/freshdesk" to configure the module.

Step 5)
  Enable permissions appropriate to your site.

  Go to "/admin/people/permissions" to configure permissions.

Requirements
-----------
As of 20 August 2018, Freshdesk has changed the time-to-live on hashes generated
for single sign on request to +/- 30 seconds. Any request made outside of that
time restriction will not be allowed to login to Freshdesk. Due to this short
amount of time, it is highly recommended that the server that hosts the Drupal
site this module is installed on be synchronized via the network time protocol (NTP).

EMBEDDED FORM

The embedded form (iframe) works via a token so it can be put anywhere. You are
free to choose whatever method that you would like to display the token.

If you want a quick and easy way to put it into content. You can download the
module Token Filter https://www.drupal.org/project/token_filter

____________________________________________________________________________
http://www.fastglass.net

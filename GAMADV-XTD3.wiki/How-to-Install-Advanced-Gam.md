# Installing GAMADV-XTD3
Use these steps if you have never used any version of GAM in your domain. They will create your GAM project
and all necessary authentications.

- [Downloads](Downloads)
- [GAM Configuration](gam.cfg)
- [Linux and MacOS and Google Cloud Shell](#linux-and-mac-os-and-google-cloud-shell)
- [Windows](#windows)

## Linux and MacOS and Google Cloud Shell

In these examples, the user home folder is shown as /Users/admin; adjust according to your
specific situation; e.g., /home/administrator.

This example assumes that GAMADV-XTD3 has been installed in /Users/admin/bin/gamadv-xtd3.
If you've installed GAMADV-XTD3 in another directory, substitute that value in the directions.

### Set a configuration directory

The default GAM configuration directory is /Users/admin/.gam; for more flexibility you
probably want to select a non-hidden location. This example assumes that the GAM
configuration directory will be /Users/admin/GAMConfig; If you've chosen another directory,
substitute that value in the directions.

Add the following line:
```
export GAMCFGDIR="/Users/admin/GAMConfig"
```
to one of these files based on your shell:
```
~/.bash_profile
~/.bashrc
~/.zshrc
~/.profile
```

Issue the following command replacing `<Filename>` with the name of the file you edited:
```
source <Filename>
```

* Make the /Users/admin/GAMConfig directory before proceeding.

### Set a working directory

You should establish a GAM working directory; you will store your GAM related
data in this folder and execute GAM commands from this folder. You should not use
/Users/admin/bin/gamadv-xtd3 or /Users/admin/GAMConfig for this purpose.
This example assumes that the GAM working directory will be /Users/admin/GAMWork; If you've chosen
another directory, substitute that value in the directions.
* Make the /Users/admin/GAMWork directory before proceeding.

### Set an alias
You should set an alias to point to /Users/admin/bin/gamadv-xtd3/gam so you can operate from the /Users/admin/GAMWork directory.

Add the following line:
```
alias gam="/Users/admin/bin/gamadv-xtd3/gam"
```
to one of these files based on your shell:
```
~/.bash_aliases
~/.bash_profile
~/.bashrc
~/.zshrc
~/.profile
```

Issue the following command replacing `<Filename>` with the name of the file you edited:
```
source <Filename>
```

### Initialize GAMADV-XTD3; this should be the first GAMADV-XTD3 command executed.
```
admin@server:~$ cd /Users/admin/bin/gamadv-xtd3
admin@server:/Users/admin/bin/gamadv-xtd3$ ./gam config drive_dir /Users/admin/GAMWork verify
Created: /Users/admin/GAMConfig
Created: /Users/admin/GAMConfig/gamcache
Config File: /Users/admin/GAMConfig/gam.cfg, Initialized
Section: DEFAULT
  activity_max_results = 100
  admin_email = ''
  api_calls_rate_check = false
  api_calls_rate_limit = 100
  auto_batch_min = 0
  batch_size = 50
  cacerts_pem = ''
  cache_dir = /Users/admin/GAMConfig/gamcache
  cache_discovery_only = true
  charset = utf-8
  cmdlog = ''
  cmdlog_max_backups = 5
  cmdlog_max_kilo_bytes = 1000
  classroom_max_results = 0
  client_secrets_json = client_secrets.json ; /Users/admin/GAMConfig/client_secrets.json
  config_dir = /Users/admin/GAMConfig
  contact_max_results = 100
  csv_input_column_delimiter = ,
  csv_input_quote_char = '"'
  csv_output_column_delimiter = ,
  csv_output_convert_cr_nl = false
  csv_output_field_delimiter = ' '
  csv_output_header_drop_filter = ''
  csv_output_header_filter = ''
  csv_output_line_terminator = lf
  csv_output_quote_char = '"'
  csv_output_row_drop_filter = ''
  csv_output_row_filter = ''
  csv_output_subfield_delimiter = '.'
  csv_output_timestamp_column = ''
  csv_output_users_audit = false
  customer_id = my_customer
  debug_level = 0
  device_max_results = 200
  domain = ''
  drive_dir = /Users/admin/GAMWork
  drive_max_results = 1000
  drive_v3_native_names = true
  email_batch_size = 50
  event_max_results = 250
  extra_args = ''
  inter_batch_wait = 0
  member_max_results = 200
  message_batch_size = 50
  message_max_results = 500
  never_time = Never
  no_browser = false
  no_cache = false
  no_update_check = true
  no_verify_ssl = false
  num_tbatch_threads = 2
  num_threads = 5
  oauth2_txt = oauth2.txt ; /Users/admin/GAMConfig/oauth2.txt
  oauth2service_json = oauth2service.json ; /Users/admin/GAMConfig/oauth2service.json
  people_max_results = 100
  quick_info_user = False
  section = ''
  show_api_calls_retry_data = false
  show_commands = false
  show_convert_cr_nl = false
  show_counts_min = 1
  show_gettings = true
  show_gettings_got_nl = false
  show_multiprocess_info = false
  smtp_fqdn = ''
  smtp_host = ''
  smtp_password = ''
  smtp_username = ''
  timezone = utc
  tls_max_version = ''
  tls_min_version = 'TLSv1_2'
  todrive_clearfilter = false
  todrive_clientaccess = false
  todrive_conversion = true
  todrive_localcopy = false
  todrive_locale = ''
  todrive_nobrowser = false
  todrive_noemail = true
  todrive_parent = root
  todrive_sheet_timeformat = ''
  todrive_sheet_timestamp = false
  todrive_timeformat = ''
  todrive_timestamp = false
  todrive_timezone = ''
  todrive_upload_nodata = true
  todrive_user = ''
  update_cros_ou_with_id = false
  user_max_results = 500
  user_service_account_access_only = false

admin@server:/Users/admin/bin/gamadv-xtd3$
```
### Verify initialization, this was a successful installation.
```
admin@server:/Users/admin/bin/gamadv-xtd3$ ls -l $GAMCFGDIR
total 48
-rw-r-----+ 1 admin  staff  1069 Mar  3 09:23 gam.cfg
drwxr-x---+ 2 admin  staff    68 Mar  3 09:23 gamcache
-rw-rw-rw-+ 1 admin  staff     0 Mar  3 09:23 oauth2.txt.lock
admin@server:/Users/admin/bin/gamadv-xtd3$ 
```
### Create your project with local browser
```
admin@server:/Users/admin/bin/gamadv-xtd3$ gam create project
WARNING: Config File: /Users/admin/GAMConfig/gam.cfg, Item: client_secrets_json, Value: /Users/admin/GAMConfig/client_secrets.json, Not Found
WARNING: Config File: /Users/admin/GAMConfig/gam.cfg, Item: oauth2service_json, Value: /Users/admin/GAMConfig/oauth2service.json, Not Found

Enter your Google Workspace admin or GCP project manager email address authorized to manage project(s) admin@domain.com

Your browser has been opened to visit:

    https://accounts.google.com/o/oauth2/v2/auth?client_id=CLIENTID&redirect_uri=http%3A%2F%2Flocalhost%3A8080%2F&scope=https%3A%2F%2Fwww.googleapis.com%2Fauth%2Fcloud-platform&login_hint=admin%40domain.com&code_challenge=Yhr1lmXAtwClE9qs7hzXMRcnPMMOv85INAsWjWwEIAI&code_challenge_method=S256&access_type=online&response_type=code

If your browser is on a different machine then press CTRL+C,
set no_browser = true in gam.cfg and re-run this command.

Authentication successful.
Creating project "GAM Project"...
Checking project status...
Project: gam-project-abc-def-ghi, Enable 23 APIs
  API: admin.googleapis.com, Enabled (1/23)
  API: alertcenter.googleapis.com, Enabled (2/23)
  API: appsactivity.googleapis.com, Enabled (3/23)
  API: audit.googleapis.com, Enabled (4/23)
  API: calendar-json.googleapis.com, Enabled (5/23)
  API: chat.googleapis.com, Enabled (6/23)
  API: classroom.googleapis.com, Enabled (7/23)
  API: contacts.googleapis.com, Enabled (8/23)
  API: drive.googleapis.com, Enabled (9/23)
  API: driveactivity.googleapis.com, Enabled (10/23)
  API: gmail.googleapis.com, Enabled (11/23)
  API: groupsmigration.googleapis.com, Enabled (12/23)
  API: groupssettings.googleapis.com, Enabled (13/23)
  API: iam.googleapis.com, Enabled (14/23)
  API: iap.googleapis.com, Enabled (15/23)
  API: licensing.googleapis.com, Enabled (16/23)
  API: people.googleapis.com, Enabled (17/23)
  API: pubsub.googleapis.com, Enabled (18/23)
  API: reseller.googleapis.com, Enabled (19/23)
  API: sheets.googleapis.com, Enabled (20/23)
  API: siteverification.googleapis.com, Enabled (21/23)
  API: storage-api.googleapis.com, Enabled (22/23)
  API: vault.googleapis.com, Enabled (23/23)
Setting GAM project consent screen...
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Enabled
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Generating new private key
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Extracting public certificate
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Done generating private key and public certificate
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Service Account Key: SVCACCTKEY, Uploaded
Service Account OAuth2 File: /Users/admin/GAMConfig/oauth2service.json, Service Account Key: SVCACCTKEY, Updated
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Has rights to rotate own private key
Please go to:

https://console.cloud.google.com/apis/credentials/oauthclient?project=gam-project-abc-def-ghi

1. Choose "Desktop App" or "Other" for "Application type".
2. Enter "GAM" or another desired value for "Name".
3. Click the blue "Create" button.
4. Copy your "client ID" value that shows on the next page.

Enter your Client ID: CLIENTID

5. Go back to your browser and copy your "client secret" value.
Enter your Client Secret: CLIENTSECRET
6. Go back to your browser and click OK to close the "OAuth client" popup if it's still open.
That's it! Your GAM Project is created and ready to use.

admin@server:/Users/admin/bin/gamadv-xtd3$ 
```
### Create your project without local browser (Google Cloud Shell for instance)
```
admin@server:/Users/admin/bin/gamadv-xtd3$ gam config no_browser true save
admin@server:/Users/admin/bin/gamadv-xtd3$ gam create project
WARNING: Config File: /Users/admin/GAMConfig/gam.cfg, Item: client_secrets_json, Value: /Users/admin/GAMConfig/client_secrets.json, Not Found
WARNING: Config File: /Users/admin/GAMConfig/gam.cfg, Item: oauth2service_json, Value: /Users/admin/GAMConfig/oauth2service.json, Not Found

Enter your Google Workspace admin or GCP project manager email address authorized to manage project(s) admin@domain.com

Go to the following link in a browser on other computer:

    https://accounts.google.com/o/oauth2/v2/auth?response_type=code&client_id=297408095146-fug707qsjv4ikron0hugpevbrjhkmsk7.apps.googleusercontent.com&redirect_uri=urn%3Aietf%3Awg%3Aoauth%3A2.0%3Aoob&scope=https%3A%2F%2Fwww.googleapis.com%2Fauth%2Fcloud-platform&state=TPEFpVgakTP5O7eBQuS4Y3PG33Gojz&code_challenge=agNDL2O1uD0lfvhU134bRFeOr7SgNGfnsh8wtX8utlA&code_challenge_method=S256&access_type=online&login_hint=admin%40domain.com&prompt=consent

Enter verification code: abc...xyz

Authentication successful.
Creating project "GAM Project"...
Checking project status...
Project: gam-project-abc-def-ghi, Enable 23 APIs
  API: admin.googleapis.com, Enabled (1/23)
  API: alertcenter.googleapis.com, Enabled (2/23)
  API: appsactivity.googleapis.com, Enabled (3/23)
  API: audit.googleapis.com, Enabled (4/23)
  API: calendar-json.googleapis.com, Enabled (5/23)
  API: chat.googleapis.com, Enabled (6/23)
  API: classroom.googleapis.com, Enabled (7/23)
  API: contacts.googleapis.com, Enabled (8/23)
  API: drive.googleapis.com, Enabled (9/23)
  API: driveactivity.googleapis.com, Enabled (10/23)
  API: gmail.googleapis.com, Enabled (11/23)
  API: groupsmigration.googleapis.com, Enabled (12/23)
  API: groupssettings.googleapis.com, Enabled (13/23)
  API: iam.googleapis.com, Enabled (14/23)
  API: iap.googleapis.com, Enabled (15/23)
  API: licensing.googleapis.com, Enabled (16/23)
  API: people.googleapis.com, Enabled (17/23)
  API: pubsub.googleapis.com, Enabled (18/23)
  API: reseller.googleapis.com, Enabled (19/23)
  API: sheets.googleapis.com, Enabled (20/23)
  API: siteverification.googleapis.com, Enabled (21/23)
  API: storage-api.googleapis.com, Enabled (22/23)
  API: vault.googleapis.com, Enabled (23/23)
Setting GAM project consent screen...
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Enabled
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Generating new private key
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Extracting public certificate
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Done generating private key and public certificate
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Service Account Key: SVCACCTKEY, Uploaded
Service Account OAuth2 File: /Users/admin/GAMConfig/oauth2service.json, Service Account Key: SVCACCTKEY, Updated
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Has rights to rotate own private key
Please go to:

https://console.cloud.google.com/apis/credentials/oauthclient?project=gam-project-abc-def-ghi

1. Choose "Desktop App" or "Other" for "Application type".
2. Enter "GAM" or another desired value for "Name".
3. Click the blue "Create" button.
4. Copy your "client ID" value that shows on the next page.

Enter your Client ID: CLIENTID

5. Go back to your browser and copy your "client secret" value.
Enter your Client Secret: CLIENTSECRET
6. Go back to your browser and click OK to close the "OAuth client" popup if it's still open.
That's it! Your GAM Project is created and ready to use.

admin@server:/Users/admin/bin/gamadv-xtd3$ 
```
### Enable GAMADV-XTD3 client access

You select a list of scopes, GAM uses a browser to get final authorization from Google for these scopes and
writes the credentials into the file oauth2.txt.

```
admin@server:/Users/admin/bin/gamadv-xtd3$ ./gam oauth create

Select the authorized scopes by entering a number.
Append an 'r' to grant read-only access or an 'a' to grant action-only access.

[*]  0)  Calendar API (supports readonly)
[*]  1)  Chrome Browser Cloud Management API (supports readonly)
[*]  2)  Chrome Management API - Telemetry read only
[*]  3)  Chrome Management API - read only
[*]  4)  Chrome Policy API (supports readonly)
[*]  5)  Chrome Printer Management API (supports readonly)
[*]  6)  Chrome Version History API
[*]  7)  Classroom API - Course Announcements (supports readonly)
[*]  8)  Classroom API - Course Topics (supports readonly)
[*]  9)  Classroom API - Course Work/Materials (supports readonly)
[*] 10)  Classroom API - Course Work/Submissions (supports readonly)
[*] 11)  Classroom API - Courses (supports readonly)
[*] 12)  Classroom API - Profile Emails
[*] 13)  Classroom API - Profile Photos
[*] 14)  Classroom API - Rosters (supports readonly)
[*] 15)  Classroom API - Student Guardians (supports readonly)
[*] 16)  Cloud Identity Groups API (supports readonly)
[*] 17)  Cloud Storage (Vault Export - read only)
[*] 18)  Contact Delegation API (supports readonly)
[*] 19)  Contacts API - Domain Shared and Users and GAL
[*] 20)  Data Transfer API (supports readonly)
[*] 21)  Directory API - Chrome OS Devices (supports readonly)
[*] 22)  Directory API - Customers (supports readonly)
[*] 23)  Directory API - Domains (supports readonly)
[*] 24)  Directory API - Groups (supports readonly)
[*] 25)  Directory API - Mobile Devices Directory (supports readonly and action)
[*] 26)  Directory API - Organizational Units (supports readonly)
[*] 27)  Directory API - Resource Calendars (supports readonly)
[*] 28)  Directory API - Roles (supports readonly)
[*] 29)  Directory API - User Schemas (supports readonly)
[*] 30)  Directory API - User Security
[*] 31)  Directory API - Users (supports readonly)
[*] 32)  Email Audit API
[*] 33)  Groups Migration API
[*] 34)  Groups Settings API
[*] 35)  License Manager API
[*] 36)  People API (supports readonly)
[*] 37)  People Directory API - read only
[ ] 38)  Pub / Sub API
[*] 39)  Reports API - Audit Reports
[*] 40)  Reports API - Usage Reports
[ ] 41)  Reseller API
[*] 42)  Site Verification API
[*] 43)  Sites API
[*] 44)  Vault API (supports readonly)

     s)  Select all scopes
     u)  Unselect all scopes
     e)  Exit without changes
     c)  Continue to authorization
Please enter 0-42[a|r] or s|u|e|c: 

Enter your Google Workspace admin email address? admin@domain.com

Go to the following link in a browser on this computer or on another computer:

    https://accounts.google.com/o/oauth2/v2/auth?response_type=code&client_id=423565144751-10lsdt2lgnsch9jmdhl35uq4617u1ifp&redirect_uri=http%3A%2F%2F127.0.0.1%3A8080%2F&scope=...

If you use a browser on another computer, you will get a browser error that the site can't be reached AFTER you
click the Allow button, paste "Unable to connect" URL from other computer (only URL data up to &scope required):

Enter verification code or paste "Unable to connect" URL from other computer (only URL data up to &scope required):

The authentication flow has completed.
Client OAuth2 File: /Users/admin/GAMConfig/oauth2.txt, Created

admin@server:/Users/admin/bin/gamadv-xtd3$ 
```
### Enable GAMADV-XTD3 service account access.
```
admin@server:/Users/admin/bin/gamadv-xtd3$ ./gam user user@domain.com check serviceaccount
System time status:
  Your system time differs from www.googleapis.com by less than 1 second    PASS
Service Account Private Key Authentication:
  Authentication                                                            PASS
Domain-Wide Delegation authentication:, User: user@domain.com, Scopes: 20
  https://mail.google.com/                                                  FAIL (1/20)
  https://sites.google.com/feeds                                            FAIL (2/20)
  https://www.google.com/m8/feeds                                           FAIL (3/20)
  https://www.googleapis.com/auth/apps.alerts                               FAIL (4/20)
  https://www.googleapis.com/auth/calendar                                  FAIL (5/20)
  https://www.googleapis.com/auth/classroom.announcements                   FAIL (6/20)
  https://www.googleapis.com/auth/classroom.coursework.students             FAIL (7/20)
  https://www.googleapis.com/auth/classroom.profile.emails                  FAIL (8/20)
  https://www.googleapis.com/auth/classroom.rosters                         FAIL (9/20)
  https://www.googleapis.com/auth/classroom.topics                          FAIL (10/20)
  https://www.googleapis.com/auth/cloud-identity                            FAIL (11/20)
  https://www.googleapis.com/auth/cloud-platform                            FAIL (12/20)
  https://www.googleapis.com/auth/contacts                                  FAIL (13/20)
  https://www.googleapis.com/auth/documents                                 FAIL (14/20)
  https://www.googleapis.com/auth/drive                                     FAIL (15/20)
  https://www.googleapis.com/auth/drive.activity                            FAIL (16/20)
  https://www.googleapis.com/auth/gmail.modify                              FAIL (17/20)
  https://www.googleapis.com/auth/gmail.settings.basic                      FAIL (18/20)
  https://www.googleapis.com/auth/gmail.settings.sharing                    FAIL (19/20)
  https://www.googleapis.com/auth/spreadsheets                              FAIL (20/20)
Some scopes FAILED!
To authorize them, please go to:

    https://admin.google.com/ac/owl/domainwidedelegation?clientScopeToAdd=https://mail.google.com/,https://sites.google.com/feeds,https://www.google.com/m8/feeds,https://www.googleapis.com/auth/apps.alerts,https://www.googleapis.com/auth/calendar,https://www.googleapis.com/auth/classroom.announcements,https://www.googleapis.com/auth/classroom.coursework.students,https://www.googleapis.com/auth/classroom.profile.emails,https://www.googleapis.com/auth/classroom.rosters,https://www.googleapis.com/auth/classroom.topics,https://www.googleapis.com/auth/cloud-identity,https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/contacts,https://www.googleapis.com/auth/drive,https://www.googleapis.com/auth/drive.activity,https://www.googleapis.com/auth/gmail.modify,https://www.googleapis.com/auth/gmail.settings.basic,https://www.googleapis.com/auth/gmail.settings.sharing,https://www.googleapis.com/auth/spreadsheets,https://www.googleapis.com/auth/userinfo.email&clientIdToAdd=SVCACCTID&overwriteClientId=true

You will be directed to the Google Workspace admin console Security/API Controls/Domain-wide Delegation page
The "Add a new Client ID" box will open
Make sure that "Overwrite existing client ID" is checked
Click AUTHORIZE
When the box closes you're done
After authorizing it may take some time for this test to pass so wait a few moments and then try this command again.

admin@server:/Users/admin/bin/gamadv-xtd3$
```
The link shown in the error message should take you directly to the authorization screen.
If not, make sure that you are logged in as a domain admin, then re-enter the link.

### Verify GAMADV-XTD3 service account access.

Wait a moment and then perform the following command; it it still fails, wait a bit longer, it can sometimes take several minutes
for the authorization to complete.
```
admin@server:/Users/admin/bin/gamadv-xtd3$ gam user user@domain.com check serviceaccount
System time status:
  Your system time differs from www.googleapis.com by less than 1 second    PASS
Service Account Private Key Authentication:
  Authentication                                                            PASS
Domain-Wide Delegation authentication:, User: user@domain.com, Scopes: 20
  https://mail.google.com/                                                  PASS (1/20)
  https://sites.google.com/feeds                                            PASS (2/20)
  https://www.google.com/m8/feeds                                           PASS (3/20)
  https://www.googleapis.com/auth/apps.alerts                               PASS (4/20)
  https://www.googleapis.com/auth/calendar                                  PASS (5/20)
  https://www.googleapis.com/auth/classroom.announcements                   PASS (6/20)
  https://www.googleapis.com/auth/classroom.coursework.students             PASS (7/20)
  https://www.googleapis.com/auth/classroom.profile.emails                  PASS (8/20)
  https://www.googleapis.com/auth/classroom.rosters                         PASS (9/20)
  https://www.googleapis.com/auth/classroom.topics                          PASS (10/20)
  https://www.googleapis.com/auth/cloud-identity                            PASS (11/20)
  https://www.googleapis.com/auth/cloud-platform                            PASS (12/20)
  https://www.googleapis.com/auth/contacts                                  PASS (13/20)
  https://www.googleapis.com/auth/documents                                 PASS (14/20)
  https://www.googleapis.com/auth/drive                                     PASS (15/20)
  https://www.googleapis.com/auth/drive.activity                            PASS (16/20)
  https://www.googleapis.com/auth/gmail.modify                              PASS (17/20)
  https://www.googleapis.com/auth/gmail.settings.basic                      PASS (18/20)
  https://www.googleapis.com/auth/gmail.settings.sharing                    PASS (19/20)
  https://www.googleapis.com/auth/spreadsheets                              PASS (20/20)
All scopes PASSED!

Service Account Client name: SVCACCTID is fully authorized.

admin@server:/Users/admin/bin/gamadv-xtd3$ 
```
### Update gam.cfg with some basic values
* `customer_id` - Having this data keeps Gam from having to make extra API calls
* `domain` - This allows you to omit the domain portion of email addresses
* `timezone local` - Gam will convert all UTC times to your local timezone
```
admin@server:/Users/admin/bin/gamadv-xtd3$ ./gam info domain
Customer ID: C01234567
Primary Domain: domain.com
Customer Creation Time: 2007-06-06T15:47:55.444Z
Primary Domain Verified: True
Default Language: en
...

admin@server:/Users/admin/bin/gamadv-xtd3$ ./gam config customer_id C01234567 domain domain.com timezone local save verify
Config File: /Users/admin/GAMConfig/gam.cfg, Saved
Section: DEFAULT
  activity_max_results = 100
  admin_email = ''
  api_calls_rate_check = false
  api_calls_rate_limit = 100
  auto_batch_min = 0
  batch_size = 50
  cacerts_pem = ''
  cache_dir = /Users/admin/GAMConfig/gamcache
  cache_discovery_only = true
  charset = utf-8
  cmdlog = ''
  cmdlog_max_backups = 5
  cmdlog_max_kilo_bytes = 1000
  classroom_max_results = 0
  client_secrets_json = client_secrets.json ; /Users/admin/GAMConfig/client_secrets.json
  config_dir = /Users/admin/GAMConfig
  contact_max_results = 100
  csv_input_column_delimiter = ,
  csv_input_quote_char = '"'
  csv_output_column_delimiter = ,
  csv_output_convert_cr_nl = false
  csv_output_field_delimiter = ' '
  csv_output_header_drop_filter = ''
  csv_output_header_filter = ''
  csv_output_line_terminator = lf
  csv_output_quote_char = '"'
  csv_output_row_drop_filter = ''
  csv_output_row_filter = ''
  csv_output_subfield_delimiter = '.'
  csv_output_timestamp_column = ''
  csv_output_users_audit = false
  customer_id = C01234567
  debug_level = 0
  device_max_results = 200
  domain = domain.com
  drive_dir = /Users/admin/GAMWork
  drive_max_results = 1000
  drive_v3_native_names = true
  email_batch_size = 50
  event_max_results = 250
  extra_args = ''
  inter_batch_wait = 0
  member_max_results = 200
  message_batch_size = 50
  message_max_results = 500
  never_time = Never
  no_browser = false
  no_cache = false
  no_update_check = true
  no_verify_ssl = false
  num_tbatch_threads = 2
  num_threads = 5
  oauth2_txt = oauth2.txt ; /Users/admin/GAMConfig/oauth2.txt
  oauth2service_json = oauth2service.json ; /Users/admin/GAMConfig/oauth2service.json
  people_max_results = 100
  quick_info_user = False
  section = ''
  show_api_calls_retry_data = false
  show_commands = false
  show_convert_cr_nl = false
  show_counts_min = 1
  show_gettings = true
  show_gettings_got_nl = false
  show_multiprocess_info = false
  smtp_fqdn = ''
  smtp_host = ''
  smtp_password = ''
  smtp_username = ''
  timezone = local
  tls_max_version = ''
  tls_min_version = 'TLSv1_2'
  todrive_clearfilter = false
  todrive_clientaccess = false
  todrive_conversion = true
  todrive_localcopy = false
  todrive_locale = ''
  todrive_nobrowser = false
  todrive_noemail = true
  todrive_parent = root
  todrive_sheet_timeformat = ''
  todrive_sheet_timestamp = false
  todrive_timeformat = ''
  todrive_timestamp = false
  todrive_timezone = ''
  todrive_upload_nodata = true
  todrive_user = ''
  update_cros_ou_with_id = false
  user_max_results = 500
  user_service_account_access_only = false

admin@server:/Users/admin/bin/gamadv-xtd3$
```

## Windows

This example assumes that GAMADV-XTD3 has been installed in C:\GAMADV-XTD3; if you've installed
GAMADV-XTD3 in another directory, substitute that value in the directions.

These steps assume Command Prompt, adjust if you're using PowerShell.

### Set a configuration directory

The default GAM configuration directory is C:\Users\<UserName>\.gam; for more flexibility you
probably want to select a non user-specific location. This example assumes that the GAM
configuration directory will be C:\GAMConfig; If you've chosen another directory,
substitute that value in the directions.
* Make the C:\GAMConfig directory before proceeding.

### Set a working directory

You should extablish a GAM working directory; you will store your GAM related
data in this folder and execute GAM commands from this folder. You should not use
C:\GAMADV-XTD3 or C:\GAMConfig for this purpose.
This example assumes that the GAM working directory will be C:\GAMWork; If you've chosen
another directory, substitute that value in the directions.
* Make the C:\GAMWork directory before proceeding.

### Set system path and GAM configuration directory
You should set the system path to point to C:\GAMADV-XTD3 so you can operate from the C:\GAMWork directory.
```
Start Control Panel
Click System
Click Advanced system settings
Click Environment Variables...
Click Path under System variables
Click Edit...
If C:\GAMADV-XTD3 is already on the Path, skip the next three steps
  Click New
  Enter C:\GAMADV-XTD3
  Click OK
Click New
Set Variable name: GAMCFGDIR
Set Variable value: C:\GAMConfig
Click OK
Click OK
Click OK
Exit Control Panel
```

At this point, you should restart Command Prompt so that it has the updated path and environment variables.

### Initialize GAMADV-XTD3; this should be the first GAMADV-XTD3 command executed.
```
C:>cd C:\GAMADV-XTD3
C:\GAMADV-XTD3>gam config drive_dir C:\GAMWork verify
Created: C:\GAMConfig
Created: C:\GAMConfig\gamcache
Config File: C:\GAMConfig\gam.cfg, Initialized
Section: DEFAULT
  activity_max_results = 100
  admin_email = ''
  api_calls_rate_check = false
  api_calls_rate_limit = 100
  auto_batch_min = 0
  batch_size = 50
  cacerts_pem = ''
  cache_dir = C:\GAMConfig\gamcache
  cache_discovery_only = true
  charset = utf-8
  cmdlog = ''
  cmdlog_max_backups = 5
  cmdlog_max_kilo_bytes = 1000
  classroom_max_results = 0
  client_secrets_json = client_secrets.json ; C:\GAMConfig\client_secrets.json
  config_dir = C:\GAMConfig
  contact_max_results = 100
  csv_input_column_delimiter = ,
  csv_input_quote_char = '"'
  csv_output_column_delimiter = ,
  csv_output_convert_cr_nl = false
  csv_output_field_delimiter = ' '
  csv_output_header_drop_filter = ''
  csv_output_header_filter = ''
  csv_output_line_terminator = lf
  csv_output_quote_char = '"'
  csv_output_row_drop_filter = ''
  csv_output_row_filter = ''
  csv_output_subfield_delimiter = '.'
  csv_output_timestamp_column = ''
  csv_output_users_audit = false
  customer_id = my_customer
  debug_level = 0
  device_max_results = 200
  domain = ''
  drive_dir = C:\GAMWork
  drive_max_results = 1000
  drive_v3_native_names = true
  email_batch_size = 50
  event_max_results = 250
  extra_args = ''
  inter_batch_wait = 0
  member_max_results = 200
  message_batch_size = 50
  message_max_results = 500
  never_time = Never
  no_browser = false
  no_cache = false
  no_update_check = true
  no_verify_ssl = false
  num_tbatch_threads = 2
  num_threads = 5
  oauth2_txt = oauth2.txt ; C:\GAMConfig\oauth2.txt
  oauth2service_json = oauth2service.json ; C:\GAMConfig\oauth2service.json
  people_max_results = 100
  quick_info_user = False
  section = ''
  show_api_calls_retry_data = false
  show_commands = false
  show_convert_cr_nl = false
  show_counts_min = 1
  show_gettings = true
  show_gettings_got_nl = false
  show_multiprocess_info = false
  smtp_fqdn = ''
  smtp_host = ''
  smtp_password = ''
  smtp_username = ''
  timezone = utc
  tls_max_version = ''
  tls_min_version = 'TLSv1_2'
  todrive_clearfilter = false
  todrive_clientaccess = false
  todrive_conversion = true
  todrive_localcopy = false
  todrive_locale = ''
  todrive_nobrowser = false
  todrive_noemail = true
  todrive_parent = root
  todrive_sheet_timeformat = ''
  todrive_sheet_timestamp = false
  todrive_timeformat = ''
  todrive_timestamp = false
  todrive_timezone = ''
  todrive_upload_nodata = true
  todrive_user = ''
  update_cros_ou_with_id = false
  user_max_results = 500
  user_service_account_access_only = false

C:\GAMADV-XTD3>
```
### Verify initialization, this was a successful installation.
```
C:\GAMADV-XTD3>dir %GAMCFGDIR%
 Volume in drive C has no label.
 Volume Serial Number is 663F-DA8B

 Directory of C:\GAMConfig

03/03/2017  10:16 AM    <DIR>          .
03/03/2017  10:16 AM    <DIR>          ..
03/03/2017  10:15 AM             1,125 gam.cfg
03/03/2017  10:15 AM    <DIR>          gamcache
03/03/2017  10:15 AM                 0 oauth2.txt.lock
               2 File(s)         15,769 bytes
               3 Dir(s)  110,532,562,944 bytes free
C:\GAMADV-XTD3>
```

### Create your project with local browser
```
C:\GAMADV-XTD3>gam create project
WARNING: Config File: C:\GAMConfig\gam.cfg, Item: client_secrets_json, Value: C:\GAMConfig\client_secrets.json, Not Found
WARNING: Config File: C:\GAMConfig\gam.cfg, Item: oauth2service_json, Value: C:\GAMConfig\oauth2service.json, Not Found

Enter your Google Workspace admin or GCP project manager email address authorized to manage project(s) admin@domain.com

Your browser has been opened to visit:

    https://accounts.google.com/o/oauth2/v2/auth?client_id=CLIENTID&redirect_uri=http%3A%2F%2Flocalhost%3A8080%2F&scope=https%3A%2F%2Fwww.googleapis.com%2Fauth%2Fcloud-platform&login_hint=admin%40domain.com&code_challenge=Yhr1lmXAtwClE9qs7hzXMRcnPMMOv85INAsWjWwEIAI&code_challenge_method=S256&access_type=online&response_type=code

If your browser is on a different machine then press CTRL+C,
set no_browser = true in gam.cfg and re-run this command.

Authentication successful.
Creating project "GAM Project"...
Checking project status...
Project: gam-project-abc-def-ghi, Enable 23 APIs
  API: admin.googleapis.com, Enabled (1/23)
  API: alertcenter.googleapis.com, Enabled (2/23)
  API: appsactivity.googleapis.com, Enabled (3/23)
  API: audit.googleapis.com, Enabled (4/23)
  API: calendar-json.googleapis.com, Enabled (5/23)
  API: chat.googleapis.com, Enabled (6/23)
  API: classroom.googleapis.com, Enabled (7/23)
  API: contacts.googleapis.com, Enabled (8/23)
  API: drive.googleapis.com, Enabled (9/23)
  API: driveactivity.googleapis.com, Enabled (10/23)
  API: gmail.googleapis.com, Enabled (11/23)
  API: groupsmigration.googleapis.com, Enabled (12/23)
  API: groupssettings.googleapis.com, Enabled (13/23)
  API: iam.googleapis.com, Enabled (14/23)
  API: iap.googleapis.com, Enabled (15/23)
  API: licensing.googleapis.com, Enabled (16/23)
  API: people.googleapis.com, Enabled (17/23)
  API: pubsub.googleapis.com, Enabled (18/23)
  API: reseller.googleapis.com, Enabled (19/23)
  API: sheets.googleapis.com, Enabled (20/23)
  API: siteverification.googleapis.com, Enabled (21/23)
  API: storage-api.googleapis.com, Enabled (22/23)
  API: vault.googleapis.com, Enabled (23/23)
Setting GAM project consent screen...
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Enabled
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Generating new private key
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Extracting public certificate
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Done generating private key and public certificate
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Service Account Key: SVCACCTKEY, Uploaded
Service Account OAuth2 File: C:\GAMConfig\oauth2service.json, Service Account Key: SVCACCTKEY, Updated
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Has rights to rotate own private key
Please go to:

https://console.cloud.google.com/apis/credentials/oauthclient?project=gam-project-abc-def-ghi

1. Choose "Desktop App" or "Other" for "Application type".
2. Enter "GAM" or another desired value for "Name".
3. Click the blue "Create" button.
4. Copy your "client ID" value that shows on the next page.

Enter your Client ID: CLIENTID

5. Go back to your browser and copy your "client secret" value.
Enter your Client Secret: CLIENTSECRET
6. Go back to your browser and click OK to close the "OAuth client" popup if it's still open.
That's it! Your GAM Project is created and ready to use.

C:\GAMADV-XTD3>
```
### Create your project without local browser (headless server for instance)
```
C:\GAMADV-XTD3>gam config no_browser true save
C:\GAMADV-XTD3>gam create project
WARNING: Config File: C:\GAMConfig\gam.cfg, Item: client_secrets_json, Value: C:\GAMConfig\client_secrets.json, Not Found
WARNING: Config File: C:\GAMConfig\gam.cfg, Item: oauth2service_json, Value: C:\GAMConfig\oauth2service.json, Not Found

Enter your Google Workspace admin or GCP project manager email address authorized to manage project(s) admin@domain.com

Go to the following link in a browser on other computer:

    https://accounts.google.com/o/oauth2/v2/auth?redirect_uri=http%3A%2F%2Flocalhost%3A8080%2F&response_type=code&client_id=...

Enter verification code: abc...xyz

Authentication successful.
Creating project "GAM Project"...
Checking project status...
Project: gam-project-abc-def-ghi, Enable 23 APIs
  API: admin.googleapis.com, Enabled (1/23)
  API: alertcenter.googleapis.com, Enabled (2/23)
  API: appsactivity.googleapis.com, Enabled (3/23)
  API: audit.googleapis.com, Enabled (4/23)
  API: calendar-json.googleapis.com, Enabled (5/23)
  API: chat.googleapis.com, Enabled (6/23)
  API: classroom.googleapis.com, Enabled (7/23)
  API: contacts.googleapis.com, Enabled (8/23)
  API: drive.googleapis.com, Enabled (9/23)
  API: driveactivity.googleapis.com, Enabled (10/23)
  API: gmail.googleapis.com, Enabled (11/23)
  API: groupsmigration.googleapis.com, Enabled (12/23)
  API: groupssettings.googleapis.com, Enabled (13/23)
  API: iam.googleapis.com, Enabled (14/23)
  API: iap.googleapis.com, Enabled (15/23)
  API: licensing.googleapis.com, Enabled (16/23)
  API: people.googleapis.com, Enabled (17/23)
  API: pubsub.googleapis.com, Enabled (18/23)
  API: reseller.googleapis.com, Enabled (19/23)
  API: sheets.googleapis.com, Enabled (20/23)
  API: siteverification.googleapis.com, Enabled (21/23)
  API: storage-api.googleapis.com, Enabled (22/23)
  API: vault.googleapis.com, Enabled (23/23)
Setting GAM project consent screen...
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Enabled
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Generating new private key
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Extracting public certificate
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Done generating private key and public certificate
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Service Account Key: SVCACCTKEY, Uploaded
Service Account OAuth2 File: C:\GAMConfig\oauth2service.json, Service Account Key: SVCACCTKEY, Updated
Project: gam-project-abc-def-ghi, Service Account: gam-project-abc-def-ghi@gam-project-abc-def-ghi.iam.gserviceaccount.com, Has rights to rotate own private key
Please go to:

https://console.cloud.google.com/apis/credentials/oauthclient?project=gam-project-abc-def-ghi

1. Choose "Desktop App" or "Other" for "Application type".
2. Enter "GAM" or another desired value for "Name".
3. Click the blue "Create" button.
4. Copy your "client ID" value that shows on the next page.

Enter your Client ID: CLIENTID

5. Go back to your browser and copy your "client secret" value.
Enter your Client Secret: CLIENTSECRET
6. Go back to your browser and click OK to close the "OAuth client" popup if it's still open.
That's it! Your GAM Project is created and ready to use.

C:\GAMADV-XTD3>
```
### Enable GAMADV-XTD3 client access

You select a list of scopes, GAM uses a browser to get final authorization from Google for these scopes and
writes the credentials into the file oauth2.txt.

```
C:\GAMADV-XTD3>gam oauth create

Select the authorized scopes by entering a number.
Append an 'r' to grant read-only access or an 'a' to grant action-only access.

[*]  0)  Calendar API (supports readonly)
[*]  1)  Chrome Browser Cloud Management API (supports readonly)
[*]  2)  Chrome Management API - Telemetry read only
[*]  3)  Chrome Management API - read only
[*]  4)  Chrome Policy API (supports readonly)
[*]  5)  Chrome Printer Management API (supports readonly)
[*]  6)  Chrome Version History API
[*]  7)  Classroom API - Course Announcements (supports readonly)
[*]  8)  Classroom API - Course Topics (supports readonly)
[*]  9)  Classroom API - Course Work/Materials (supports readonly)
[*] 10)  Classroom API - Course Work/Submissions (supports readonly)
[*] 11)  Classroom API - Courses (supports readonly)
[*] 12)  Classroom API - Profile Emails
[*] 13)  Classroom API - Profile Photos
[*] 14)  Classroom API - Rosters (supports readonly)
[*] 15)  Classroom API - Student Guardians (supports readonly)
[*] 16)  Cloud Identity Groups API (supports readonly)
[*] 17)  Cloud Storage (Vault Export - read only)
[*] 18)  Contact Delegation API (supports readonly)
[*] 19)  Contacts API - Domain Shared and Users and GAL
[*] 20)  Data Transfer API (supports readonly)
[*] 21)  Directory API - Chrome OS Devices (supports readonly)
[*] 22)  Directory API - Customers (supports readonly)
[*] 23)  Directory API - Domains (supports readonly)
[*] 24)  Directory API - Groups (supports readonly)
[*] 25)  Directory API - Mobile Devices Directory (supports readonly and action)
[*] 26)  Directory API - Organizational Units (supports readonly)
[*] 27)  Directory API - Resource Calendars (supports readonly)
[*] 28)  Directory API - Roles (supports readonly)
[*] 29)  Directory API - User Schemas (supports readonly)
[*] 30)  Directory API - User Security
[*] 31)  Directory API - Users (supports readonly)
[*] 32)  Email Audit API
[*] 33)  Groups Migration API
[*] 34)  Groups Settings API
[*] 35)  License Manager API
[*] 36)  People API (supports readonly)
[*] 37)  People Directory API - read only
[ ] 38)  Pub / Sub API
[*] 39)  Reports API - Audit Reports
[*] 40)  Reports API - Usage Reports
[ ] 41)  Reseller API
[*] 42)  Site Verification API
[*] 43)  Sites API
[*] 44)  Vault API (supports readonly)

     s)  Select all scopes
     u)  Unselect all scopes
     e)  Exit without changes
     c)  Continue to authorization
Please enter 0-42[a|r] or s|u|e|c: 

Enter your Google Workspace admin email address? admin@domain.com

Go to the following link in a browser on this computer or on another computer:

    https://accounts.google.com/o/oauth2/v2/auth?response_type=code&client_id=423565144751-10lsdt2lgnsch9jmdhl35uq4617u1ifp&redirect_uri=http%3A%2F%2F127.0.0.1%3A8080%2F&scope=...

If you use a browser on another computer, you will get a browser error that the site can't be reached AFTER you
click the Allow button, paste "Unable to connect" URL from other computer (only URL data up to &scope required):

Enter verification code or paste "Unable to connect" URL from other computer (only URL data up to &scope required):

The authentication flow has completed.
Client OAuth2 File: C:\GAMConfig\oauth2.txt, Created

C:\GAMADV-XTD3>
```
### Enable GAMADV-XTD3 service account access.
```
C:\GAMADV-XTD3>gam user user@domain.com check serviceaccount
System time status:
  Your system time differs from www.googleapis.com by less than 1 second    PASS
Service Account Private Key Authentication:
  Authentication                                                            PASS
Domain-Wide Delegation authentication:, User: user@domain.com, Scopes: 20
  https://mail.google.com/                                                  FAIL (1/20)
  https://sites.google.com/feeds                                            FAIL (2/20)
  https://www.google.com/m8/feeds                                           FAIL (3/20)
  https://www.googleapis.com/auth/apps.alerts                               FAIL (4/20)
  https://www.googleapis.com/auth/calendar                                  FAIL (5/20)
  https://www.googleapis.com/auth/classroom.announcements                   FAIL (6/20)
  https://www.googleapis.com/auth/classroom.coursework.students             FAIL (7/20)
  https://www.googleapis.com/auth/classroom.profile.emails                  FAIL (8/20)
  https://www.googleapis.com/auth/classroom.rosters                         FAIL (9/20)
  https://www.googleapis.com/auth/classroom.topics                          FAIL (10/20)
  https://www.googleapis.com/auth/cloud-identity                            FAIL (11/20)
  https://www.googleapis.com/auth/cloud-platform                            FAIL (12/20)
  https://www.googleapis.com/auth/contacts                                  FAIL (13/20)
  https://www.googleapis.com/auth/documents                                 FAIL (14/20)
  https://www.googleapis.com/auth/drive                                     FAIL (15/20)
  https://www.googleapis.com/auth/drive.activity                            FAIL (16/20)
  https://www.googleapis.com/auth/gmail.modify                              FAIL (17/20)
  https://www.googleapis.com/auth/gmail.settings.basic                      FAIL (18/20)
  https://www.googleapis.com/auth/gmail.settings.sharing                    FAIL (19/20)
  https://www.googleapis.com/auth/spreadsheets                              FAIL (20/20)
Some scopes FAILED!
To authorize them, please go to:

    https://admin.google.com/ac/owl/domainwidedelegation?clientScopeToAdd=https://mail.google.com/,https://sites.google.com/feeds,https://www.google.com/m8/feeds,https://www.googleapis.com/auth/apps.alerts,https://www.googleapis.com/auth/calendar,https://www.googleapis.com/auth/classroom.announcements,https://www.googleapis.com/auth/classroom.coursework.students,https://www.googleapis.com/auth/classroom.profile.emails,https://www.googleapis.com/auth/classroom.rosters,https://www.googleapis.com/auth/classroom.topics,https://www.googleapis.com/auth/cloud-identity,https://www.googleapis.com/auth/cloud-platform,https://www.googleapis.com/auth/contacts,https://www.googleapis.com/auth/drive,https://www.googleapis.com/auth/drive.activity,https://www.googleapis.com/auth/gmail.modify,https://www.googleapis.com/auth/gmail.settings.basic,https://www.googleapis.com/auth/gmail.settings.sharing,https://www.googleapis.com/auth/spreadsheets,https://www.googleapis.com/auth/userinfo.email&clientIdToAdd=SVCACCTID&overwriteClientId=true

You will be directed to the Google Workspace admin console Security/API Controls/Domain-wide Delegation page
The "Add a new Client ID" box will open
Make sure that "Overwrite existing client ID" is checked
Click AUTHORIZE
When the box closes you're done
After authorizing it may take some time for this test to pass so wait a few moments and then try this command again.

C:\GAMADV-XTD3>
```
The link shown in the error message should take you directly to the authorization screen.
If not, make sure that you are logged in as a domain admin, then re-enter the link.

### Verify GAMADV-XTD3 service account access.

Wait a moment and then perform the following command; it it still fails, wait a bit longer, it can sometimes take serveral minutes
for the authorization to complete.
```
C:\GAMADV-XTD3>gam user user@domain.com check serviceaccount
System time status:
  Your system time differs from www.googleapis.com by less than 1 second    PASS
Service Account Private Key Authentication:
  Authentication                                                            PASS
Domain-Wide Delegation authentication:, User: user@domain.com, Scopes: 20
  https://mail.google.com/                                                  PASS (1/20)
  https://sites.google.com/feeds                                            PASS (2/20)
  https://www.google.com/m8/feeds                                           PASS (3/20)
  https://www.googleapis.com/auth/apps.alerts                               PASS (4/20)
  https://www.googleapis.com/auth/calendar                                  PASS (5/20)
  https://www.googleapis.com/auth/classroom.announcements                   PASS (6/20)
  https://www.googleapis.com/auth/classroom.coursework.students             PASS (7/20)
  https://www.googleapis.com/auth/classroom.profile.emails                  PASS (8/20)
  https://www.googleapis.com/auth/classroom.rosters                         PASS (9/20)
  https://www.googleapis.com/auth/classroom.topics                          PASS (10/20)
  https://www.googleapis.com/auth/cloud-identity                            PASS (11/20)
  https://www.googleapis.com/auth/cloud-platform                            PASS (12/20)
  https://www.googleapis.com/auth/contacts                                  PASS (13/20)
  https://www.googleapis.com/auth/documents                                 PASS (14/20)
  https://www.googleapis.com/auth/drive                                     PASS (15/20)
  https://www.googleapis.com/auth/drive.activity                            PASS (16/20)
  https://www.googleapis.com/auth/gmail.modify                              PASS (17/20)
  https://www.googleapis.com/auth/gmail.settings.basic                      PASS (18/20)
  https://www.googleapis.com/auth/gmail.settings.sharing                    PASS (19/20)
  https://www.googleapis.com/auth/spreadsheets                              PASS (20/20)
All scopes PASSED!

Service Account Client name: SVCACCTID is fully authorized.

C:\GAMADV-XTD3>
```
### Update gam.cfg with some basic values
* `customer_id` - Having this data keeps Gam from having to make extra API calls
* `domain` - This allows you to omit the domain portion of email addresses
* `timezone local` - Gam will convert all UTC times to your local timezone
```
C:\GAMADV-XTD3>gam info domain
Customer ID: C01234567
Primary Domain: domain.com
Customer Creation Time: 2007-06-06T15:47:55.444Z
Primary Domain Verified: True
Default Language: en
...

C:\GAMADV-XTD3>gam config customer_id C01234567 domain domain.com timezone local save verify
Config File: C:\GAMConfig\gam.cfg, Saved
Section: DEFAULT
  activity_max_results = 100
  admin_email = ''
  api_calls_rate_check = false
  api_calls_rate_limit = 100
  auto_batch_min = 0
  batch_size = 50
  cacerts_pem = ''
  cache_dir = C:\GAMConfig\gamcache
  cache_discovery_only = true
  charset = utf-8
  cmdlog = ''
  cmdlog_max_backups = 5
  cmdlog_max_kilo_bytes = 1000
  classroom_max_results = 0
  client_secrets_json = client_secrets.json ; C:\GAMConfig\client_secrets.json
  config_dir = C:\GAMConfig
  contact_max_results = 100
  csv_input_column_delimiter = ,
  csv_input_quote_char = '"'
  csv_output_column_delimiter = ,
  csv_output_convert_cr_nl = false
  csv_output_field_delimiter = ' '
  csv_output_header_drop_filter = ''
  csv_output_header_filter = ''
  csv_output_line_terminator = lf
  csv_output_quote_char = '"'
  csv_output_row_drop_filter = ''
  csv_output_row_filter = ''
  csv_output_subfield_delimiter = '.'
  csv_output_timestamp_column = ''
  csv_output_users_audit = false
  customer_id = C01234567
  debug_level = 0
  device_max_results = 200
  domain = domain.com
  drive_dir = C:\GAMWork
  drive_max_results = 1000
  drive_v3_native_names = true
  email_batch_size = 50
  event_max_results = 250
  extra_args = ''
  inter_batch_wait = 0
  member_max_results = 200
  message_batch_size = 50
  message_max_results = 500
  never_time = Never
  no_browser = false
  no_cache = false
  no_update_check = true
  no_verify_ssl = false
  num_tbatch_threads = 2
  num_threads = 5
  oauth2_txt = oauth2.txt ; C:\GAMConfig\oauth2.txt
  oauth2service_json = oauth2service.json ; C:\GAMConfig\oauth2service.json
  people_max_results = 100
  quick_info_user = False
  section = ''
  show_api_calls_retry_data = false
  show_commands = false
  show_convert_cr_nl = false
  show_counts_min = 1
  show_gettings = true
  show_gettings_got_nl = false
  show_multiprocess_info = false
  smtp_fqdn = ''
  smtp_host = ''
  smtp_password = ''
  smtp_username = ''
  timezone = local
  tls_max_version = ''
  tls_min_version = 'TLSv1_2'
  todrive_clearfilter = false
  todrive_clientaccess = false
  todrive_conversion = true
  todrive_localcopy = false
  todrive_locale = ''
  todrive_nobrowser = false
  todrive_noemail = true
  todrive_parent = root
  todrive_sheet_timeformat = ''
  todrive_sheet_timestamp = false
  todrive_timeformat = ''
  todrive_timestamp = false
  todrive_timezone = ''
  todrive_upload_nodata = true
  todrive_user = ''
  update_cros_ou_with_id = false
  user_max_results = 500
  user_service_account_access_only = false

C:\GAMADV-XTD3>
```

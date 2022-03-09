### Update GAMADV-XTD3 to latest version
Automatic update to the latest version on Linux/Mac OS/Google Cloud Shell/Raspberry Pi/ChromeOS:
- Do not create project or authorizations, default path `$HOME/bin`
  - `bash <(curl -s -S -L https://git.io/fhZWP) -l`
- Do not create project or authorizations, specify a path
  - `bash <(curl -s -S -L https://git.io/fhZWP) -l -d <Path>`

See [Downloads](https://github.com/taers232c/GAMADV-XTD3/wiki/Downloads) for Windows or other options, including manual installation.

### 6.16.09

Added option `role|roles <DriveFileACLRoleList>` to `gam <UserTypeEntity> print|show drivefileacls`
to simplify limiting displayed ACLs by role.

### 6.16.08

Added command to upload image files for use in Chrome policies.
```
<ChromePolicyImageSchemaName> ::=
        chrome.devices.managedguest.avatar |
        chrome.devices.managedguest.wallpaper |
        chrome.devices.signinwallpaperimage |
        chrome.users.avatar |
        chrome.users.wallpaper

gam create chromepolicyimage <ChromePolicyImageSchemaName> <FileName>
```

### 6.16.07

Extended option `stripcrsfromname` option in the following commands to strip nulls and linefeeds
from displayed file names in addition to carriage returns.
```
gam <UserTypeEntity> info drivefile <DriveFileEntity>
gam <UserTypeEntity> print|show filerevisions <DriveFileEntity>
gam <UserTypeEntity> show fileinfo <DriveFileEntity>
gam <UserTypeEntity> print|show filetree
gam <UserTypeEntity> print filelist
```

### 6.16.06

Updated code to remove Python 3.9 dependency introduced in 6.16.05.

### 6.16.05

Added option `domain <DomainName>` to `gam print aliases` to simplify printing aliases from a secondary domain.

### 6.16.04

Fixed bug in `gam <UserTypeEntity> get drivefile` that caused a trap when the target file couldn't be written.

### 6.16.03

Fixed bug that broke `vault` commands.

Updated `gam oauth create` to use client access authentication flow as in Standard GAM, `config no_browser true` is no longer necessary.

### 6.16.02

Following Jay's lead, added option `removeresetlock` to `gam wipe device <DeviceEntity>` that will remove the account lock
on the Android or iOS device. This lock is enabled by default and requires the existing device user to log in after the wipe in order to unlock the device.
* See: https://support.google.com/android/answer/9459346

Following Jay's lead, added option `usenewexport <Boolean>` to `gam create vaultexport ... corpus mail`.
* See: https://support.google.com/vault/answer/4388708#new_gmail_export&zippy=%2Cfebruary-new-gmail-export-system-available

### 6.16.01

Updated `gam oauth create` to allow retries when `no_browser` is true and the user
enters an invalid authentication code.

### 6.16.00

With many thanks to Jay, updated `gam oauth create` to use a new client access authentication flow
as required by Google for headless computers/cloud shells; this is required as of February 28, 2022.
* See: https://developers.googleblog.com/2022/02/making-oauth-flows-safer.html
  * OAuth out-of-band (oob) flow will be deprecated

### 6.15.24

Cleaned up `gam report` commands again to improve verification that valid data has been received.

Fixed bug in `gam <UserTypeEntity> dedup contacts` where `<PeopleResourceNameEntity>|<PeopleUserContactSelection>`
was not optional as documented.

### 6.15.23

Added option `replacefilename <RegularExpression> <String>` to `gam <UserTypeEntity> copy|update drivefile`
that allows using regular expressions to modify the copied/updated file name.
```
gam user user@domain.com update drivefile query "name contains '2020-2021'" replacefilename "2020-2021" "2021-2022"
gam user user@domain.com copy drivefile name Template parentid root recursive replacefilename Template NewCustomer
```
* See: https://github.com/taers232c/GAMADV-XTD3/wiki/Users-Drive-Files-Manage#update-files
* See: https://github.com/taers232c/GAMADV-XTD3/wiki/Users-Drive-Copy-Move#copy-files-and-folders

### 6.15.22

Cleaned up `gam report` commands to improve verification that valid data has been received.

### 6.15.21

Added email audit monitor commands that were deleted in 5.34.00.
```
gam audit monitor create <EmailAddress> <DestEmailAddress> [begin <DateTime>] [end <DateTime>]
        [incoming_headers] [outgoing_headers] [nochats] [nodrafts] [chat_headers] [draft_headers]
gam audit monitor delete <EmailAddress> <DestEmailAddress>
gam audit monitor list <EmailAddress>
```
To use these commands, you should do:
```
gam update project
gam oauth create
```

### 6.15.20

Fixed bug in `gam <UserTypeEntity> print datastudiopermissions` where `todrive` was not recognized.

### 6.15.19

Further cleanup of `gam create|update alias`.
* See: https://github.com/taers232c/GAMADV-XTD3/wiki/Aliases

### 6.15.18

After discussions with Jay, the default for creating/updating aliases is to verify that
the target `<UniqueID>|<EmailAddress>` exists by making extra API calls;
if you know that the target exists, you can suppress the verification with `notargetverify`.

### 6.15.17

Added option `verifytarget` to `gam create|update alias <EmailAddressEntity> user|group|target <UniqueID>|<EmailAddress>`
that causes Gam to verify that the target `<UniqueID>|<EmailAddress>` exists.

### 6.15.16

Updated `gam <UserTypeEntity> deprovision` and `gam <UserTypeEntity> delete|update backupcodes`
to give a more informative error message when a user is suspended and backup codes can't be deleted|updated.

### 6.15.15

Fixed bug in `gam print crosactivity recentusers oneuserperrow` that caused a trap.

### 6.15.14

Added option `setchangepasswordoncreate [<Boolean>]` to `gam <UserTypeEntity> update user` that can be used
to force created (as opposed to updated) users to change their password at their next login.

### 6.15.13

Updated error messages in `gam <UserTypeEntity> update user createifnotfound`.

### 6.15.12

Added option `notifyonupdate [<Boolean>]` to `gam <UserTypeEntity> update user` that can be used
to suppress the email notificaton when options `notify <EmailAddressList> notifypassword <String>`
are specified for use in the case when the user must be created but not used when the user does exist
and is simply updated.

### 6.15.11

Updated `gam create cigroup` to handle the following error:
```
ERROR: 403: permissionDenied - Error(3006): This feature (Dynamic Groups) requires a premium SKU.
```

### 6.15.10

Fixed bug in `gam update ou / add|move ...` that caused the following error:
```
ERROR: 400: invalid - Invalid field selection orgUnitPath
```

### 6.15.09

Updated option `corpus` in `gam print vaultcounts` to only allow `mail` and `groups` as
required by the API.

### 6.15.08

Following Jay's lead, added option `condition securitygroup|nonsecuritygroup` to `gam create admin`
and option `condition` to `gam print|show admins`.
* See: https://github.com/taers232c/GAMADV-XTD3/wiki/Administrators

### 6.15.07

Updated code in `gam print cros` to handle a missing data field that caused a trap.

### 6.15.06

Added option `dateheaderconverttimezone [<Boolean>]>` to `gam <UserTypeEntity> print|show messages|threads` that allows
converting `<SMTPDateHeader>` values to the `gam.cfg timezone`.

Updated option `dateheaderformat iso|rfc2822|<String>` to `gam <UserTypeEntity> print|show messages|threads` that allows
reformatting of the message `Date` header value from RFC2822 format to the the following:
* `iso` - Format is `%Y-%m-%dT%H:%M:%S%z`
* `rfc2822` - Format is `%a, %d %b %Y %H:%M:%S %z`
* `<String>` - Format according to: https://docs.python.org/3/library/datetime.html#strftime-strptime-behavior

### 6.15.05

Added option `dateheaderformat <String>` to `gam <UserTypeEntity> print|show messages|threads` that allows
reformatting of the message `Date` header from RFC2822 format to the format specified by `<String>`.
If `<String>` is `iso`, then ISO 8601 format is used, otherwise see: https://docs.python.org/3/library/datetime.html#strftime-strptime-behavior
If the `Date` header can't be parsed as RFC2822, it is left unchanged.

### 6.15.04

Fixed bug in `gam <UserTypeEntity> copy drivefile <DriveFileEntity> ... excludepermissionsfromdomains <DomainNameList>` that caused a trap.

### 6.15.03

Updated `<CourseAttribute>` and `<CourseFieldName>` to use `descriptionheading` and `heading` synonymously.

### 6.15.02

Added the following options to `gam <UserTypeEntity> copy drivefile <DriveFileEntity>`
that provide more flexibility in managing permissions when copying/moving folders.
* Thanks to Kevin Sanghvi for suggesting these enhancements.
```
copysheetprotectedrangesinheritedpermissions [<Boolean>]
copysheetprotectedrangesnoninheritedpermissions [<Boolean>]
```
* See: https://github.com/taers232c/GAMADV-XTD3/wiki/Users-Drive-Copy-Move#copy-permissions

### 6.15.01

Fixed bug in `gam <UserTypeEntity> print|show messages ... showattachments|saveattachments` where
some attachments were not recognized.
* Thanks to Craig Millsap for spending the time with me to find the solution.

### 6.15.00

Updated processing of `teamdrive <SharedDriveName>` in the following commands.
Previously, if there were multiple Shared Drives with the same `<SharedDriveName>`, GAM silently processed
the first one which may not have been the desired action. Now, a message is issued listing the multiple `<DriveFileIDs>` and
no processing is performed. Determine which Shared Drive ID is desired and reissue the command with `teamdriveid <DriveFileID>`.
```
gam <UserTypeEntity> print filelist select teamdrive <SharedDriveName>
gam <UserTypeEntity> print|show filecounts select teamdrive <SharedDriveName>
gam <UserTypeEntity> print|show filetree select teamdrive <SharedDriveName>
gam <UserTypeEntity> update teamdrive teamdrive <SharedDriveName>
gam <UserTypeEntity> delete teamdrive teamdrive <SharedDriveName>
gam <UserTypeEntity> hide teamdrive teamdrive <SharedDriveName>
gam <UserTypeEntity> unhide teamdrive teamdrive <SharedDriveName>
gam <UserTypeEntity> info teamdrive teamdrive <SharedDriveName>
gam <UserTypeEntity> print emptydrivefolders teamdrive <SharedDriveName>
gam <UserTypeEntity> delete emptydrivefolders teamdrive <SharedDriveName>
gam <UserTypeEntity> empty drivetrash teamdrive <SharedDriveName>
```

Added the following commands to transfer top level ACLs from one Shared Drive to another.
```
gam [<UserTypeEntity>] copy teamdriveacls <SharedDriveEntity> to <SharedDriveEntity>
        [adminaccess|asadmin]
        [showpermissionsmessages [<Boolean>]]
        [excludepermissionsfromdomains <DomainNameList>]
        (mappermissionsdomain <DomainName> <DomainName>)*
gam [<UserTypeEntity>] sync teamdriveacls <SharedDriveEntity> with <SharedDriveEntity>
        [adminaccess|asadmin]
        [showpermissionsmessages [<Boolean>]]
        [excludepermissionsfromdomains <DomainNameList>]
        (mappermissionsdomain <DomainName> <DomainName>)*
```

Added option `shownopermissionsdrives false|true|only` to `gam <UserTypeEntity> print|show teamdriveacls` that
controls whether Shared Drives with no permissions are displayed.
* `false` - Do not display Shared Drives with no permissions; this is the default
* `true` - Display Shared Drives with no permissions in addition to Shared Drives with permissions
* `only` - Display only Shared Drives with no permissions

Added the option `mappermissionsdomain <DomainName1> <DomainName2>` to `gam <UserTypeEntity> copy|move drivefile <DriveFileEntity>`
that maps `<DomainName1>` to `<DomainName2>` in any non-inherited permissions that are copied. The option can be specified multiple times
to provide different mappings.
* Thanks to Kevin Sanghvi for suggesting this enhancement.

Updated `gam <UserTypeEntity> delete othercontacts` to retry the delete step when
`notFound` errors are returned after the update step.

Fixed bug in `gam courses <CourseEntity> add|remove students|teachers` that caused API
call retries to fail with the following error:
```
Temporary error: notFound - @CourseNotFound The course was not found.
```

Improved performance when converting Shared Drive names to IDs.

Updated code to handle Shared Drive names that contain single quotes.

### 6.14.07

Corrected `gam.cfg` variable `cmdlog_max__backups` to be `cmdlog_max_backups`.

### 6.14.06

Fixed bug in `gam sync devices` where option `serialnumber_column` was not recognized.

Fixed bug in `gam sync devices` where a trap occurred when option `assigned_missing_action` was not specified.

### 6.14.05

Upgraded the `countsonly` suboption `showsource` in `gam <UserTypeEntity> print filelist` to display
the name of the source drive/folder (Name column) in addition to its ID (Source Column).

### 6.14.04

Added a command to move Other Contacts to My Contacts.
* See: https://github.com/taers232c/GAMADV-XTD3/wiki/Users-People-Contacts-Profiles#move-user-other-contacts
```
gam <UserTypeEntity> move othercontacts <OtherContactResourceNameEntity>|<OtherContactSelection>
```

Improved action performed messages in `gam <UserTypeEntity> update othercontacts`.

### 6.14.03

Added a command to delete Other Contacts.
* Thanks to Kim Nilsson for finding a Stack Overflow page that showed the way to do this.
* See: https://github.com/taers232c/GAMADV-XTD3/wiki/Users-People-Contacts-Profiles#delete-user-other-contacts
```
gam <UserTypeEntity> delete othercontacts <PeopleResourceNameEntity>|<PeopleUserOtherContactSelection>
```

Added a command to update Other Contacts and move them to My Contacts.
* Thanks to Kim Nilsson for finding a Stack Overflow page that showed the way to do this.
* See: https://github.com/taers232c/GAMADV-XTD3/wiki/Users-People-Contacts-Profiles#update-user-other-contacts
```
gam <UserTypeEntity> update othercontacts <PeopleResourceNameEntity>|<PeopleUserOtherContactSelection>
        <PeopleContactAttribute>+
        (contactgroup <ContactGroupItem>)*
```

### 6.14.02

Updated `gam print|show teamdriveacls` to display the creation time of the Team/Shared drives.

### 6.14.01

Added the option `excludepermissionsfromdomains <DomainNameList>` to `gam <UserTypeEntity> copy|move drivefile <DriveFileEntity>`
that excludes permissions that reference any domain in `<DomainNameList>` from being copied.
* Thanks to Kevin Sanghvi for suggesting this enhancement.

Fixed bug `gam <UserTypeEntity> copy|move drivefile <DriveFileEntity>` where option `copymergewithparentfolderpermissions`
was not recognized.

### 6.14.00

Added the following options to `gam <UserTypeEntity> copy|move drivefile <DriveFileEntity>`
that provide more flexibility in managing permissions when copying/moving folders.
Thanks to Kevin Sanghvi for suggesting these enhancements.
```
copyfileinheritedpermissions [<Boolean>]
copyfilenoninheritedpermissions [<Boolean>]
copymergewithparentfolderpermissions [<Boolean>]
copymergedtopfolderpermissions [<Boolean>]
copytopfolderiheritedpermissions [<Boolean>]
copytopfoldernoniheritedpermissions never|always|syncallfolders|syncupdatedfolders
copymergedsubfolderpermissions [<Boolean>]
copysubfolderinheritedpermissions [<Boolean>]
copysubfoldernoniheritedpermissions never|always|syncallfolders|syncupdatedfolders
```
* See: https://github.com/taers232c/GAMADV-XTD3/wiki/Users-Drive-Copy-Move#copy-permissions
* See: https://github.com/taers232c/GAMADV-XTD3/wiki/Users-Drive-Copy-Move#move-permissions

Following Jay's lead, added command `gam <UserTypeEntity> show vaultholds` to display all vault holds
affecting a user. This allows you to investigate the error `Delete Failed: Precondition is not met.`
when trying to delete a user.

Added option `buildpath [<Boolean>]` to `gam <UserTypeEntity> create filter label <LabelName>` that controls whether
`<LabelNames>` of the form `Top/Middle/Bottom` will be created as single-level or multi-level.

Added option `hidden <Boolean>' to `gam <UserTypeEntity> update teamdrive`.

Fixed bug in `gam print|show matters matterstate <MatterStateList>` that caused a trap.

Fixed bug in `gam update mobile <MobileEntity> action block` that caused the following error:
```
ERROR: 400: invalidInput - Invalid value for: action_block is not a valid value
```

* Upgraded to Python 3.10.2
* Updated google-api-python-client to version 2.35.0

### 6.13.09

Fixed bug in `gam <UserTypeEntity> update chromepolicy` that caused a trap.

Fixed bug in `gam print|show datatransfers oldowner|newowner <UserItem>` that did not
properly handle `<UserItem>` of form `uid:<String>`.

### 6.13.08

* Updated to OpenSSL 1.1.1m

Added command `gam info currentprojectid` that displays the current Project ID.

### 6.13.07

Added options `showpermissionmessages` and `sendemailifrequired` to `gam <UserTypeEntity> copy|move drivefile <DriveFileEntity>`.
Previously, when attempting to copy ACLs, GAM would report any errors; some errors were generated when an attempt
was made to inappropriately copy an ACL. Now, GAM will not attempt to copy ACLs unless they are appropriate.
When `showpermissionmessages` is specified GAM will display messages about ACLs not copied, ACLs that were copied
and any remaining copy errors.

When copying an ACL that references a non Google account, an error is generated unless an email is sent to the account;
by default, no email notifications are sent. The `sendemailifrequired` options instructs GAM to send an email notification in this case.

### 6.13.06

Added option `formatjson` to `gam <UserTypeEntity> info filters` and `gam <UserTypeEntity> show filters`.

### 6.13.05

Handle the following error in `gam <UserTypeEntity> signout`:
```
ERROR: 400: invalidInput - Invalid Input
```
This can be caused by applying the command to a suspended user.

### 6.13.04

Added option `showsize` to `gam <UserTypeEntity> print|show filecounts` that displays the
size (in bytes) of the files counted.

Following Jay's lead, added commands to display ChromeOS device telemetry data.
* See: https://github.com/taers232c/GAMADV-XTD3/wiki/ChromeOS-Devices#display-chromeos-telemetry-data

To use these commands  you must authorize an additional scope:
* `Chrome Management API - Telemetry read only`
```
gam oauth create
```

Added option `reverselists <ListFieldNameList>` to commands that display ChromeOS device information.
For each list in `<ListFieldNameList>`, the list order is changed from ascending (oldest to newest) to descending (newest to oldest);
this makes it easy to get the `N` most recent values with `listlimit N reverselists <ListFieldNameList>`.

### 6.13.03

Added options `parentselector <OrgUnitSelector>` and `childselector <OrgUnitSelector>` to
`gam print orgs|ous` that add an additional column `orgUnitSelector` to the output. This column
value can be used in subsequent `gam csv` commands to appropriately select members without duplication.
```
<OrgUnitSelector> ::=
        cros_ou | cros_ou_and_children|
        ou| ou_ns | ou_susp|
        ou_and_children | ou_and_children_ns | ou_and_children_susp

Get file count summariess by OU; top level selector is ou, sub level selectors are ou_and_children

gam redirect csv ./TopLevelOUs.csv print ous showparent toplevelonly parentselector ou childselector ou_and_children fields orgunitpath
gam redirect csv ./FileCounts.csv multiprocess csv ./TopLevelOUs.csv gam "~orgUnitSelector" "~orgUnitPath" print filecounts excludetrashed summary only summaryuser "~orgUnitPath"
```

### 6.13.02

Updated error handling in `gam <UserTypeEntity> copy drivefile` when copying files to a shared drive folder.

### 6.13.01

Added option `summaryuser <String>` to `gam <UserTypeEntity> print filecounts` and
`gam <UserTypeEntity> print filelist countsonly` that replaces the default summary user `Summary`
with `<String>`.
```
gam redirect csv ./FileCounts.csv multiprocess csv ./OUs.csv gam ou_ns "~orgUnitPath" print filecounts excludetrashed summary only summaryuser "~orgUnitPath"
```

Uodated `gam <UserTypeEntity> update drivefile <DriveFileEntity> teamdriveparentid <DriveFolderID>
to handle the following error:
```
ERROR: 400: shareOutNotPermitted - Bad Request. User message: "shareOutNotPermitted"
```

### 6.13.00

Fixed bug in `gam <UserTypeEntity> copy drivefile` where `contentManager|fileOrganizer` ACLs
were not copied from a source shared drive folder to a target shared drive folder.

### 6.12.06

Fixed bug where `redirect csv - multiprocess todrive redirect stdout - multiprocess` would disable
`multiprocess` for `redirect csv` which resulted in multiple files being uploaded.

Added option `showshareddrivepermissions` to `gam <UserTypeEntity> show fileinfo <DriveFileEntity>` that is applicable
when no fields are selected and `<DriveFileEntity>` is a shared drive file/folder. In this case,
the Drive API returns the permission IDs but not the permissions themselves so GAM makes an additional API call
to get the permissions.

Added option `showshareddrivepermissions` to `gam <UserTypeEntity> print filelist` that is applicable
when no fields are selected and shared drives are queried/selected. In this case,
the Drive API returns the permission IDs but not the permissions themselves so GAM makes an additional API call
per file to get the permissions.

Added commands that can process lists of Gmail labels.
* See: https://github.com/taers232c/GAMADV-XTD3/wiki/Users-Gmail-Labels

### 6.12.05

Updated `gam info|print cros showdvrsfp formatjson` to include `diskVolumeReports.volumeInfo.storageFreePercentage`.

Improved error messages for `gam create resource` when options `capacity <Number>` and `floor <String>`
are required but not provided.

### 6.12.04

Added option `showdvrsfp` to `gam info|print cros` that causes GAM to display a field
`diskVolumeReports.volumeInfo.storageFreePercentage` which is calculated as:
* `(diskVolumeReports.volumeInfo.storageFree/diskVolumeReports.volumeInfo.storageTotal)*100`

You can use an output row filter to only show ChromeOS devices with a limited amount of free space:
* `config csv_output_row_filter "diskVolumeReports.volumeInfo.0.storageFreePercentage:countrange=1/15"`
Use `countrange=1/15` instead of `count<15` as the latter will display ChromeOS devices with no
diskVolumeReports; a blank entry is treated as a zero.

ChromeOS devices can have multiple diskVolumeReports; some experimentation may be required to
get the desired results.

### 6.12.03

The 6.12.02 bug fix in `gam <UserTypeEntity> print|show filetree select <DriveFileEntity>`
was too aggressive; when showing a file tree, folders owned by others must be processed
so that files owned by the user within those folders are displayed.

### 6.12.02

When running `gam oauth create` and `gam.cfg no_browser = true`, the authorization link is
no longer copied to the file `gamoauthurl.txt` as this functionality required modifying
a Google supplied library.

Removed the option `writeurltofile` from `gam check| svcacct` that caused GAM to write
the authorization link to the file `gamsvcaccturl.txt`.

Fixed bug in `gam <UserTypeEntity> print|show filetree select <DriveFileEntity>` where
file ownership was not being checked which resulted in files not owned by the user being displayed.

### 6.12.01

Updated code to perform retries when a `serviceNotAvailable` error occurs when listing file permissions.

### 6.12.00

Fixed bug in `gam <UserTypeEntity> copy drivefile <DriveFileEntity> <DriveFileParentAttribute> recursive`
that mis-copied files when the target parent folder `<DriveFileParentAttribute>` was within the folder structure of `<DriveFileEntity>`.

Fixed bug in `gam <UserTypeEntity> check drivefileshortcut <DriveFileEntity> csv` that caused a trap.

### 6.11.07

Added command `gam <UserTypeEntity> delete labelid <LabelID>` that is used to 
delete Gmail labels by ID rather than by name.

### 6.11.06

Fixed bug in 6.11.05 for updating Chromebook OU by ID.

### 6.11.05

Added `update_cros_ou_with_id` variable to `gam.cfg` that causes GAM to update
the OU of a Chromebook with the OU ID rather than the OU path.
Set this value to true if you are getting the following error:
```
400: invalidInput - Invalid Input: Inconsistent Orgunit id and path in request
```

### 6.11.04

When specifying `<UserAttribute> languages`, it is an error to specify a custom language with a preference suffix `+-`.

Added option `includederivedmembership` to `gam print|show cigroup-members`.
This option causes the API to list indirect members of groups.
See: https://github.com/taers232c/GAMADV-XTD3/wiki/Cloud-Identity-Groups-Membership

Updated `gam oauth export|refresh` to privent the following error.
```
ERROR: Authentication Token Error - Not all requested scopes were granted by the authorization server, missing scopes , https://sitesgooglecom/feeds, https://wwwgooglecom/m8/feeds
```

### 6.11.03

Added option `noinvitablecheck` to `gam whatis <EmailItem>` that suppresses the user invitation check
to avoid exceeding quota limits when checking a large number of addresses.

Following Jay's lead, updated processing of `<UserAttribute> languages`.
You could always set a user's languages via the API; Google has added the ability to
indicate whether a language is `preferred` or `not_preferred`. This is implemeted in
GAM by optionally appending a `+` to a language code to set `preferred` and a '-' to set `not_preferred`.
In the user's profile, only `preferred` languages are displayed.
```
gam update user user@domain.com languages en+,fr+.
```

Updated all Cloud Identity API group calls to use version `v1` of the API rather than version `v1beta1`.

### 6.11.02

Added option `nobatchupdate` to `gam <CrOSTypeEntity> update ou <OrgUnitPath>` and
`gam update cros <CrOSEntity> ou <OrgUnitPath>` that prevents GAM from using batch mode
to update the devices; this allows handling the `rateLimitExceeded` error described below.

### 6.11.01

Updated code to to handle the following error as retryable:
```
403: rateLimitExceeded - Quota exceeded for quota metric 'Queries' and limit 'Queries per minute per user' of service 'admin.googleapis.com' for consumer 'project_number: (project)'
```

### 6.11.00

Updated `gam print groups` and `gam print|show group-members` to allow identification of groups
with the `All users in the organization` member with: `member id:<CustomerID>`.

Upgraded to Python 3.10.1

### 6.10.05

Added option to the `copyfrom` option used with `gam create/update course` that modifies how
course work and materials are copied.
* `markdraftaspublished` - Mark all draft course work and materials as published

Updated `todrive` options to simplify updating an existing sheet within an existing file.
Previously, if you specified `tdfileid <DriveFileID> tdsheet (id:<Number>)|<String> tdupdatesheet`,
the sheet had to exist. The updated behavior is:
* `tdfileid <DriveFileID> tdsheet id:<Number> tdupdatesheet` - The specified sheet must exist
* `tdfileid <DriveFileID> tdsheet <String> tdupdatesheet` - The specified sheet will be created if necessary

### 6.10.04

Fixed bug introduced in 6.10.03 that broke `gam <UserTypeEntity> update drivefileacl <DriveFileEntity>`.

Updated `gam whatis <EmailItem>` to give a better message if `<EmailItem>` is not a group/user email address
or alias and Service Account scope `Cloud Identity User Invitations API` is not enabled.

Renamed client access scope `Directory API Printers` to `Chrome Printer Management API`; there is
no change in functionality.

### 6.10.03

Updated `gam <UserTypeEntity> copy|move drivefile <DriveFileEntity> <DriveFileParentAttribute>`
to enforce the requirement that the specified user be a Shared Drive organizer
if either `<DriveFileEntity>` or `<DriveFileParentAttribute>` specifies a Shared Drive.

Added options `csv [todrive <ToDriveAttribute>*] [formatjson [quotechar <Character>]]` to
`gam <UserTypeEntity> create|update drivefileacl <DriveFileEntity>` that causes GAM to
output the new ACL details in CSV form rather than indented keywords and values.

### 6.10.02

Following Jay's lead, fixed obscure problem when creating a project in timezones ahead of GMT.

### 6.10.01

Updated `gam create domainalias|aliasdomain <DomainAlias> <DomainName>` to handle error when
an invalid `<DomainAlias>` is specified.

### 6.10.00

Added `csv_output_subfield_delimiter` and `people_max_results` variables to `gam.cfg`.
```
csv_output_subfield_delimiter
    Character used to delimit fields and subfields in headers when writing CSV files;
    this must be a single character
    Default: '.'

people_max_results
    When retrieving lists of People from API,
    how many should be retrieved in each API call
    Default: 100
    Range: 0 - 1000
```

### 6.08.31

Updated `<UserBasicAttribute>` so that an OU ID can be specified in addition to an OU path.
```
<UserBasicAttribute> ::=
        org|ou|orgunitpath <OrgUnitPath>|<OrgUnitID>
```
This is applicable to `gam create|update user`; n.b., the API requires a path so an additional API call
must be made to convert the ID to a path.

### 6.08.30

Added option `showsize` to `gam <UserTypeEntity> print filelist countsonly` that adds an additional
column `Size` that indicates the total size (in bytes) of the files represented on the row.

### 6.08.29

Added options `onerowpertarget` and `suppressnoaliasrows` to `gam print aliases`.

By default, the CSV output has three columns: `Alias,Target,TargetType`; if a target
has multiple aliases, there will be multiple rows, one per alias. Specifying `onerowpertarget` changes
the three columns to: `Target,TargetType,Aliases`; all aliases for the target are space-separated in the
`Aliases` column.

Specifying both `onerowpertarget` and `suppressnoaliasrows` causes GAM to not display any targets that have no aliases.

Added command `gam remove aliases|nicknames <EmailAddress> user|group <EmailAddressEntity>` to more efficiently
delete the aliases in `<EmailAddressEntity>` from the `user|group` `<EmailAddress>`.

You can combine these two changes as follows:
```
gam redirect csv ./OldDomainAliases.csv print aliases aliasmatchpattern ".*@olddomain.com" onerowpertarget suppressnoaliasrows
gam csv ./OldDomainAliases.csv gam remove aliases "~Target" "~TargetType" "~Aliases"
```

Fixed bug in `gam user user@domain.com sendemail ... ghtml ...` that caused an inappropriate error.
```
ERROR: User: user@domain.com, Drive File: Email Doc, Data Not Retrieved: Invalid mimeType application/vnd.google-apps.document, must be text/html
```

### 6.08.28

Updated Google API libraries.

### 6.08.27

Reverted update 6.08.26 as it couldn't accurately distinguish between the following cases in all instances:
* A Service Account scope is not authorized
* A user with a service disabled
* A user from outside your domain

### 6.08.26

Improved the error message dislayed when a Service Account scope is not authorized so it
can be distinguished from a user with the service disabled.

### 6.08.25

Updated `gam create|use project` to handle the following spurious Google error:
```
ERROR: 500: Failed to convert server response to JSON - 500
```

### 6.08.24

Fixed bug in `gam <UserTypeEntity> print|show contacts fields ...` that caused an error
when retrieving other contacts.

Revert Google Auth library to version 2.0.2 to avoid the following error:
```
ERROR: Token used too early, 1634572527 < 1634572532. Check that your computer's clock is set correctly.
```

### 6.08.23

Updated code to format Google timestamps with fractional seconds, e.g., `2021-10-13T13:35:42.590124Z`
and `timezone = utc` in gam.cfg.

### 6.08.22

Fixed bug in `gam create|clear|dedup|delete|info|print|show|update contacts` where
the command would fail if the domain was not defined in gam.cfg

### 6.08.21

Fixed bug `gam <UserTypeEntity> print contactdelegates` that caused a trap.

### 6.08.20

Updated `gam print|show ownership` to display the event name of the most recent
primary event. If the event name is `delete`, then you'll know who the owner was
but won't be able to do much with the file.

### 6.08.19

Fixed bug in `gam update group` where field `memberKey` was mistakenly converted to `preferredMemberKey`;
this caused a trap.

### 6.08.18

Updated code to work around issue in Cloud Identity Groups API where a group member of
type `CUSTOMER` is not properly marked as that type; this caused a trap.

### 6.08.17

Fixed bug in `gam show cigroup-members` where the deprecated field `memberKey` was still being used;
it was replaced with `preferredMemberKey`.

### 6.08.16

Fixed bug in metacommand `multiprocessexit` where GAM would not terminate when the condition was met
by one process while multiple other processes terminated simultaneously with the condition not met.

### 6.08.15

In 6.07.24, `delivery_settings` was added to the default list of fields in `gam print group-members`.
Unfortunately, it is still the case that an additional API call per member is required to get this setting;
this makes getting group members very slow for large groups.

`delivery_settings` has been removed from the default list of fields and the option `showdeliverysettings`
adds this field to the default list of fields. You can always specify a specific list of fields that includes
`delivery_settings`.

### 6.08.14

Fixed bug in `gam redirect csv ... multiprocess ...` that caused a trap when running on Windows.

### 6.08.13

Fixed bugs in `gam <UserTypeEntity> copy othercontacts` that rendered it unusable; sigh.

Following Jay's lead, added support for newly announced group member restrictions.
You can update groups to restrict membership to only include users, groups or service accounts as well as internal users and groups.
* See: https://workspaceupdates.googleblog.com/2021/10/membership-restrictions-google-groups-.html
In the API, these member restrictions fall with a category called `SecuritySettings`.

Added option `nosecuritysettings` to `gam info cigroups <GroupEntity>`. By default, GAM
makes an additional API call to get the `SecuritySettings`; this option suppresses that call.

Added option `memberrestrictions <QueryMemberRestrictions>` to `gam update cigroups <GroupEntity>`
to define member restrictions.
* See: https://cloud.google.com/identity/docs/reference/rest/v1beta1/SecuritySettings#MemberRestriction

Added option `memberrestrictions` to `gam print cigroups` that causes GAM to make an
additional API call to get the member restrictions from the `SecuritySettings`.

### 6.08.12

Added `(json [charset <Charset>] <JSONData>)|(json file <FileName> [charset <Charset>])` to `<PrinterAttribute>`
that allows specification of printer attributes from JSON data in `gam create|update printer`.
```
<PrinterAttribute> ::=
        (description <String>)|
        (displayname <String>)|
        (json [charset <Charset>] <JSONData>)|(json file <FileName> [charset <Charset>])|
        (makeandmodel <String>)|
        (ou|org|orgunit <OrgUnitItem>)|
        (uri <String>)|
        (driverless [<Boolean>])
```

### 6.08.11

Added option `copysheetprotectedranges [<Boolean>]` to `gam <UserTypeEntity> copy drivefile` that causes
GAM to copy the Google Sheet permissions and protected ranges from the source file to the target file.

Updated `gam update cigroups <GroupEntity> update [<GroupRole>] expires <Time> <UserTypeEntity>`
to handle the following error:
```
ERROR: 403: permissionDenied - Error(3005): Non-premium customers do not have access to certain premium features.
```

### 6.08.10

Fixed bug in `gam <UserTypeEntity> clear contacts` that caused a trap.

### 6.08.09

Changed license SKU `Google-Apps` name `Google Workspace Free/Standard` to `G Suite Legacy` to be
consistent with Google.

### 6.08.08

Updated all commands that reference Cloud Identity Group members to use the field `preferredMemberKey`
rather than the deprecated field `memberKey` which would cause traps.

### 6.08.07

Fixed bug in `gam <UserTypeEntity> create|update contact json <JSONData>` that failed to delete
the read-only field `updateTime` which caused the command to fail.

Added the following keyword to `gam.cfg` that causes GAM to add a timestamp column
to the CSV output file; the value in each row is time at which the command started.
```
csv_output_timestamp_column
        Name of column in the CSV output file to contain a timestamp
        Default: ''
```

Added option `timestampcolumn` to `<Redirect>` that causes GAM to add a timestamp column labeled `<String>`
to the output CSV file; the value in each row is time at which the command started.
This overrides the `csv_output_timestamp_column` value in `gam.cfg`.

```
<Redirect> ::=
        redirect csv <FileName> [multiprocess] [append] [noheader] [charset <Charset>]
                     [columndelimiter <Character>] [quotechar <Character>]
                     [timestampcolumn <String>]
                     [todrive <ToDriveAttribute>*] |
```

### 6.08.06

Added `formatjson` to `gam info|show resoldsubscriptions` and `formatjson [quotechar <Character>]`
to `gam print resoldsubscriptions`.

Handle the following error as retryable when managing user's contacts:
```
ERROR: API access Denied
```

### 6.08.05

Added option `addcsvdata <FieldName> <String>` to `gam create drivefile ... csv`. This adds
additional columns of data to the CSV file output. For example, you are building student folders
on a Shared Drive as an admin and want to add ACLs to the folders allowing the student write access
and you want a shortcut on the student's My Drive pointing to the folder. By adding the student's
primary email address to the CSV output, it can be used in subsequent commands.
Substitute for admin@domain.com and `<TeamDriveID>`.
```
Students.csv
primaryEmail,Name
bob@domain.com,Bob Jones
mary@domain.com, Mary Smith
...

# Create the student folders on the Shared Drive
gam redirect csv ./StudentFolders.csv multiprocess csv Students.csv gam user admin@domain.com create drivefile mimetype gfolder drivefilename "~~Name~~ Digital Portfolio" parentid <TeamDriveID> csv addcsvdata primaryEmail "~primaryEmail"
# Add ACLs granting the students write access to their folders; ~User refers to admin@domain.com
gam csv StudentFolders.csv gam user "~User" add drivefileacl "~id" user "~primaryEmail" role fileorganizer
# Add a shortcut to the folder on the student's My Drive
gam csv StudentFolders.csv gam user "~primaryEmail" create drivefileshortcut "~id" parentid root
```

### 6.08.04

Handle the following error in `gam move drivefile`:
```
ERROR: 400: crossDomainMoveRestriction - Bad Request. User message: "crossDomainMoveRestriction"
```

Improved error messages when an unknown contact ID is used in a command.

### 6.08.03

Use Python library pathvalidate to clean up filenames in `gam get drivefile|document`.
If you are using the source verson of GAMADV-XTD3, do the following command to update your Python libraries.
```
pip install --upgrade -r src/requirements.txt
```

### 6.08.02

Updated `gam sync devices` to include the `assetTag` field, if specified, as part of the device
comparison key in addition to `serialNmmber` and `deviceType`.

### 6.08.01

Fixed bug in `gam create device` that caused a trap.

Updated `gam print|show chromeapps|chromedevices|chromeversions` to handle the following error.
```
ERROR: 503: serviceNotAvailable - The service is currently unavailable.
```

### 6.08.00

GAM now uses the People API to manage user contacts rather than the Contacts API.

Most commands will work unchanged but Google has completely changed how the data is presented. If you
have scripts that process the output from `print contacts` for example, they will have to be changed.

You might want to keep an older version of GAM available so you can compare the output from the two
versions and make adjustments as necessary.

This is work in progress, report issues/problems.
* https://github.com/taers232c/GAMADV-XTD3/wiki/Users-People-Contacts-Profiles

### 6.07.31

Fixed bugs in `gam sync devices` that rendered it useless.

Deleted most local copies of Google and non-standard Python libraries.
If you are using the source verson of GAMADV-XTD3, do the following command to update your Python libraries.
```
pip install --upgrade -r src/requirements.txt
```
You should delete the following files from `src/gam`:
```
distro.py,filelock.py
```
You should delete the following directories from `src/gam`:
```
dateutil,google,google_auth_httplib2,googleapiclient,
httplib2,oauthlib,passlib,requests,requests_oauthlib
```

### 6.07.30

Update Google API libraries.

### 6.07.29

Removed `agreed2terms|agreedtoterms <Boolean>` from `<UserBasicAttribute>`; this is a read-only attribute
and can't be modified.

### 6.07.28

Fixed bug in `gam user user@domain.com remove calendars courses_with_teacher user@domain.com` that caused a trap.

### 6.07.27

Updated from `Cloud Identity Groups API` version v1beta1 to version v1.

### 6.07.26

Added metacommand `multiprocessexit (rc<Operator><Number>)|(rcrange=<Number>/<Number>)|(rcrange!=<Number>/<Number>)`
that will terminate processing of a CSV or batch file when one of the subprocesses returns a matching return code.
See: https://github.com/taers232c/GAMADV-XTD3/wiki/Meta-Commands-and-File-Redirection#specify-multiprocessing-termination-return-code

This change was inspired by the brute force approach to finding the owner of a file by stepping through
all users. Once the owner is found, there is no need to process the remaining users; this change allows
processing to be terminated when the owner is found.
```
gam config auto_batch_min 1 multiprocessexit rc=0 redirect csv - multiprocess redirect stderr null multiprocess all users print filelist select id <DriveFileID> fields id,name,owners.emailaddress norecursion showownedby any
```

### 6.07.25

Cleaned up License Product/SKU names; replaced `G Suite` with `Google Workspace` where appropriate.

### 6.07.24

Added option `defaultsender self|group` to `<GroupSettingsAttribute>`.

Added `delivery_settings` to the default list of fields in `gam print group-members`.

### 6.07.23

Update Google API libraries, remove unused libraries.

### 6.07.22

Updated `gam info domain` to generate an error when the `customer_id` and `oauth2_txt` values are not consistent.
This typically happens when the wrong customer ID is assigned to a `gam.cfg` section.

### 6.07.21

Fixed bug in `gam create datatransfer <OldOwnerID> <DataTransferServiceList> <NewOwnerID>`
where the privacy level was not being set in all applications if more than one was
specified in `<DataTransferServiceList>`.

### 6.07.20

* Upgraded to Python 3.9.7
* Upgraded to OpenSSL 1.1.1l

### 6.07.19

Fixed bug in `gam print chromepolicies` that caused the following error:
```
Chrome Policy: chrome.devices.*, Print Failed: Invalid page token, request parameters do not match page token.
```

### 6.07.18

Updated `gam create|update course copyfrom <CourseID> ... markpublishedasdraft` to mark
published course materials as draft as well as course work; this matches the console
copy course behavior.

Updated more course related commands to handle the following error.
```
ERROR: 503: serviceNotAvailable - The service is currently unavailable.
```

### 6.07.17

Following Jay's suggestion, added option `maxresults <Number>` to `gam print|show resoldsubscriptions`;
the default value is 100 and the range is 1-100.

### 6.07.16

Updated `gam <UserTypeEntity> claim|transfer ownership <DriveFileEntity>` to handle the following error:
```
ERROR: 403: insufficientFilePermissions - The user does not have sufficient permissions for this file.
```

### 6.07.15

Updated `gam <UserTypeEntity> copy drivefile <DriveFileEntity>` to allow more attributes
to be specified on the copy. These only apply when a single file/folder is being copied.
```
<DriveFileCopyAttribute> ::=
        (contentrestrictions readonly false)|
        (contentrestrictions readonly true [reason <String>])|
        (copyrequireswriterpermission [<Boolean>])|
        (description <String>)|
        ignoredefaultvisibility|
        (keeprevisionforever|pinned)|
        (lastviewedbyme <Time>)|
        (modifieddate|modifiedtime <Time>)|
        (mimetype <MimeType>)|
        (ocrlanguage <Language>)|
        (privateproperty <PropertyKey> <PropertyValue>)|
        (publicproperty <PropertyKey> <PropertyValue>)|
        (property <PropertyKey> <PropertyValue> [private|public])|
        (viewerscancopycontent [<Boolean>])|
        (writerscanshare|writerscantshare [<Boolean>])
```

### 6.07.14

Following Jay's suggestions, updated `gam download vaultexport <ExportItem> matter <MatterItem> targetname <FileName>`
to avaid data loss when `<FileName>` does not contain `#filename#` and there are multiple top level files with the same extension.
The files will be named `FileName-N.ext` where `N` is `1,2,3,...`.

### 6.07.13

Fixed `gam <UserTypeEntity> print filelist ... formatjson nodataheaders <String>` to
output only `<String>` when there is no data.

### 6.07.12

Updated various course related commands to handle the following error.
```
ERROR: 503: serviceNotAvailable - The service is currently unavailable.
```

### 6.07.11

Fixed bug in `gam <UserTypeEntity> modify messages|threads removelabel <LabelName>` where `<LabelName>`
was being created inappropriately.

### 6.07.10

Due to missing API documentation, `gam <UserTypeEntity> print|show datastudioassets orderby title ascending|descending`'
displayed in the opposite of the specified order.

Fixed bug that caused a trap in `gam print|show chromeschemas std`.

### 6.07.09

Following Jay's suggestion, added `all` to `assettype` in all `datastudioassets`
and `datastudiopermissions` commands so you can get information on both `reports`
and `datasources` in a single command.

### 6.07.08

Fixed bug that caused a trap in `gam <UserTypeEntity> transfer calendars <UserItem> <UserCalendarEntity> append description|location|summary`.

### 6.07.07

Added option `alias|aliases <EmailAddressList>` to `gam create user` that causes GAM
to create the user aliases in `<EmailAddressList>` after creation of the user. The
same option was added to `gam update user createifnotfound` and applies when a user is
not found and must be created.

### 6.07.06

Handle the following error in `gam create|update drivefileacl`:
```
ERROR: 400: publishOutNotPermitted - Bad Request. User message: "publishOutNotPermitted"
```

### 6.07.05

Updated `gam print|show datatransfers status completed|failed|inprogress`;
previously, `pending` was allowed but it generates an error.

### 6.07.04

Updated `gam copy drivefile` to avoid the following error when copying a shortcut to a folder.
```
ERROR: 403: fieldNotWritable - The resource body includes fields which are not directly writable.
```

### 6.07.03

Fixed bug in `gam show ownership` that always showed file name as blank.

### 6.07.02

Updated various Google libraries and httplib2.

### 6.07.01

Updated `gam print|show admins` to allow specification of both `user <UserItem>`
and `role <RoleItem>` and then avoid the undocumented API rule that disallows both.

### 6.07.00

Added the following keywords to `gam.cfg` to provide logging of GAM commands.
```
cmdlog
        Path to GAM Log file
        Default: ''
cmdlog_max_backups
        Maximum number of backup log files
        Default: 5
        Range: 1 - 10
cmdlog_max_kilo_bytes
        Maximum kilobytes per log file
        Default: 1000
        Range: 100 - 10000
```
See: https://github.com/taers232c/GAMADV-XTD3/wiki/Command-Logging-Progress#command-logging

Added the following keyword to `gam.cfg` to display commands to stderr when executing `gam batch|tbatch|csv|loop`.
```
show_commands
	Display commands to stderr when executing `gam batch|tbatch|csv|loop`.
	Default: False
```
See: https://github.com/taers232c/GAMADV-XTD3/wiki/Command-Logging-Progress#command-progress


### 6.06.15

Updated option`showcmds` output in `gam batch|csv|tbatch` to show the total number of commands
to be executed in addition to the current command number.

Added option `showcmds [<Boolean>]` option to `gam loop`; this causes GAM to display each command to stderr
as it is initiated so you can monitor GAM's progress. If `<Boolean>` is omitted, True is assumed.
When `showcmds` is not specified or False, the input file is processed line-by-line. When `showcmds` is True,
the input file is pre-processed so the total number of commands is known.

### 6.06.14

The following options have been deprecated in `gam <UserTypeEntity> copy drivefile <DriveFileEntity>`
as Google no longer supports multiple parents on files; using them will cause an error so as to alert
you to review the command.

No existing parents are copied for source top/sub files/folders.
```
These options control the action GAM takes when a source top file/folder has multiple parents.
* `copytopfileparents all` - Copy all of the existing parents.
* `copytopfolderparents all` - Copy all of the existing parents.

These options control the action GAM takes when a source sub file/folder has multiple parents.
* `copysubfileparents nonpath` - Copy all of the existing parents except the parent on the path from the top folder; this is the default action.
* `copysubfileparents all` - Copy all of the existing parents.
* `copysubfolderparents nonpath` - Copy all of the existing parents except the parent on the path from the top folder; this is the default action.
* `copysubfolderparents all` - Copy all of the existing parents.
```

### 6.06.13

Fixed bug in `gam info user <UserItem> quick` that generated the following error:
```
Cloud Identity Group: groups/-, Lookup Failed: Error(4016): Insufficient permissions to retrieve membership graph.
```

Added option `domainlist|notdomainlist <DomainNameList>` to `<PermissionMatch>`
to make it easier to specify a list of domains.

Added option `notrole <DriveFileACLRole>` to `<PermissionMatch>`
to make it possible to match any role other that the specified role.

### 6.06.12

Fixed bug in `gam report <ActivityApplicationName>` where only the last subevent
of an event was shown rather than all subevents.

### 6.06.11

Following Jay's lead, improved error messages when invalid client_secrets.json, oauth2service.json
and oauth2.txt files are encountered.

### 6.06.10

Code cleanup for internal routines cleanJSON, flattenJSON, showJSON.

### 6.06.09

Fixed more issues caused by update to Cloud Resource Manager API v3.

### 6.06.08

Fixed bug in `gam update project` that caused a trap.

### 6.06.07

Defined `<ProjectIDEntity>` to allow selection of project IDs from a flat or CSV file in addition
to the current options.
```
<ProjectIDList> ::= "<ProjectID>(,<ProjectID>)*"
<ProjectIDEntity> ::=
        current | gam | <ProjectID> | (filter <String>) |
        (select <ProjectIDList> | <FileSelector> | <CSVFileSelector>)
gam update project [[admin] <EmailAddress>] [<ProjectIDEntity>]
gam delete project [[admin] <EmailAddress>] [<ProjectIDEntity>]
gam show projects [[admin] <EmailAddress>] [all|<ProjectIDEntity>]
        [states all|active|deleterequested] [showiampolicies 0|1|3]
gam print projects [[admin] <EmailAddress>] [all|<ProjectIDEntity>] [todrive <ToDriveAttribute>*]
        [states all|active|deleterequested] [showiampolicies 0|1|3 [onememberperrow]]
        [delimiter <Character>]] [[formatjson [quotechar <Character>]]

gam create|add svcacct [[admin] <EmailAddress>] [<ProjectIDEntity>]
        [saname <ServiceAccountName>] [sadisplayname <ServiceAccountDisplayName>]
        [sadescription <ServiceAccountDescription>]
gam delete svcacct [[admin] <EmailAddress>] [<ProjectIDEntity>]
        (saemail <ServiceAccountEmail>)|(saname <ServiceAccountName>)|(sauniqueid <ServiceAccountUniqueID>)
gam show svcaccts [[admin] <EmailAddress>] [all|<ProjectIDEntity>]
        [showsakeys all|system|user]
gam print svcaccts [[admin] <EmailAddress>] [all|<ProjectIDEntity>]
        [showsakeys all|system|user]
        [todrive <ToDriveAttribute>*]
        [formatjson [quotechar <Character>]]
```

### 6.06.06

Fixed issues caused by update to Cloud Resource Manager API v3.

Following Jay's lead, added command to create a Google Cloud Platform folder.
This folder can be used in a subsequent `gam create project` command.
```
gam create gcpfolder <String>
gam create gcpfolder [admin <EmailAddress] folder <String>
```

### 6.06.05

Updated `gam print|show|update chromepolicy` to handle the following special case policies:
```
chrome.users.AutoUpdateCheckPeriodNew autoupdatecheckperiodminutesnew
chrome.users.BrowserSwitcherDelayDuration browserswitcherdelayduration
chrome.users.FetchKeepaliveDurationSecondsOnShutdown fetchkeepalivedurationsecondsonshutdown
chrome.users.MaxInvalidationFetchDelay maxinvalidationfetchdelay
chrome.users.PrintingMaxSheetsAllowed printingmaxsheetsallowednullable
chrome.users.PrintJobHistoryExpirationPeriodNew printjobhistoryexpirationperioddaysnew
chrome.users.SecurityTokenSessionSettings securitytokensessionnotificationseconds
chrome.users.SessionLength sessiondurationlimit
chrome.users.UpdatesSuppressed updatessuppresseddurationmin
chrome.users.UpdatesSuppressed updatessuppressedstarttime
```

### 6.06.04

Fixed bug in `gam print|show chromepolicies` that caused a trap.

### 6.06.03

Fixed `gam print|show chromepolicies` to display `targetKey.additionalTargetKey` fields.

Updated `gam info|show|print note` to display `owner` and `ownedByMe` fields.

Following Jay's lead, updated to Cloud Resource Manager API v3.

### 6.06.02

Improved Google Keep notes commands.

### 6.06.01

Code cleanup for Google Keep notes commands.

### 6.06.00

Added commands to manage and display Google Keep notes.
* https://github.com/taers232c/GAMADV-XTD3/wiki/Users-Keep

### 6.04.25

Updated random password processing in `gam create|update user`.

As in prior versions of Advanced GAM, if you create a user and don't specify a password
or specify `password random`, a password of length 25 comprised of letters, numbers and special characters is created.
This does not match Standard GAM; it generates an unusable login password.
You can specify the length of the random password with `password random <Integer>`,
`<Integer>` must be between 8 and 100; this is not available in Standard GAM.

If you specify `password blocklogin`, a password of length 4096 comprised of random Unicode
characters is created; it's purpose is to create a password that blocks logins. This
matches the `password random` option of Standard GAM.

### 6.04.24

Handle the following error in `gam <UserTypeEntity> copy drivefile <DriveFileEntity>`:
```
ERROR: 400: invalidLinkVisibility - Bad Request. User message: ""
```

### 6.04.23

Following Jay's lead, improved `gam <UserTypeEntity> waitformailbox [retries <Number>]`.

### 6.04.22

Added additional code to handle the following error in `gam print group-members`.
```
ERROR: 503: serviceNotAvailable - The service is currently unavailable.
```

### 6.04.21

Fixed bugs in `gam <UserTypeEntity> print|show messages|threads sendermatchpattern <RegularExpression> countsonly`.

### 6.04.20

Added option `sendermatchpattern <RegularExpression>` to `gam <UserTypeEntity> print|show messages|threads`
that causes GAM to display messages and threads only if the sender matches the `<RegularExpression>`.
This is used to display messages sent by a particular delegate for a delegator; the message is
from the delegator but sent by the delegate.

See: https://github.com/taers232c/GAMADV-XTD3/wiki/Users-Gmail-Messages-Threads#display-messages-sent-by-delegates-for-delegator

### 6.04.19

Updated processing of `query <QueryGmail>` that contains `(after|before|newer|older):YYYY/MM/DD`
so that GAM results match Gmail results. `YYYY/MM/DD` is interpreted as midnight on the given
date but GAM has to adjust the time to be consistent with `gam.cfg timezone`.

### 6.04.18

Handle the following error in `gam <UserTypeEntity> print filelist select teamdriveid <SharedDriveID>`
when `<SharedDriveID>` is not valid.
```
ERROR: 404: fileNotFound - Does not exist
```

### 6.04.17

* Upgraded to Python 3.9.6
* Upgraded to Google API Python Client 2.10.0
* Upgraded to Google Auth 1.32.0

Added option `groupidfilter <String>` to `gam report <ActivityApplictionName>`.

From the API documentation: https://developers.google.com/admin-sdk/reports/reference/rest/v1/activities/list
```
Comma separated group ids (obfuscated) on which user activities are filtered,
i.e, the response will contain activities for only those users that are a
part of at least one of the group ids mentioned here. Format: "id:abc123,id:xyz456"
```
Is `obfuscated` explained? No. Does the option work in my testing? No.
Updates when I figure out what's going on.


### 6.04.16

Added fields `resourcekey`  and `linksharemetadata` to `<DriveFieldName>`.

Added option `securityupdate <Boolean>` to `<DriveFileAttribute>` that
sets `linkShareMetadata.securityUpdateEnabled` to `<Boolean>`.

### 6.04.15

Fixed bug in `gam <UserTypeEntity> sendemail newuser <EmailAddress> ...` that caused a trap.

### 6.04.14

Fixed bug in `gam <UserTypeEntity> print filelist filetree|filepath ..." where all
files were not displayed.
* `showownedby` not specified - Files owned by the user in `Shared with me` were not displayed
* `showownedby me` - Files owned by the user in `Shared with me` were not displayed
* `showownedby others` - Files not owned by the user that are orphans were not displayed

### 6.04.13

Added option `clearfilter` to `gam <UserTypeEntity> update drivefile <DriveFileEntity> csvsheet <SheetEntity>`
that causes GAM to clear the spreadsheet basic filter when uploading data to the existing sheet so hidden data will be overwritten.

### 6.04.12

Added option `addsheet <String>` to `gam <UserTypeEntity> update drivefile <DriveFileEntity>`
that allows creating a new sheet within a Google spreadsheet with data from `localfile <FileName>`.
Remember, when updating a file with `addsheet|csvsheet` and `localfile <FileName>`, you may want to
use the `retainname` option so that the spreadsheet file is not renamed to `<FileName>`.

### 6.04.11

Updated Contacts API calls to handle the following error generated by Google as a reminder
to switch to the People API.
```
Contacts API is being deprecated. Migrate to People API to retain programmatic access to Google Contacts. See https://developers.google.com/people/contacts-api-migration.
```

### 6.04.10

Fixed bug in `gam print resources formatjson` that caused a trap.

Added ability to display output in JSON format to `gam info|print|show buildings`.

Added command to display empty drive folders on My Drive or a selected Shared Drive.
```
gam <UserTypeEntity> print emptydrivefolders [todrive <ToDriveAttribute>*]
        [select <SharedDriveEntity>]
```

### 6.04.09

Handle the following error generated by `gam report ... fields xxx`.
```
ERROR: 400: invalidInput - Invalid value 'xxx'. Values must match the following regular expression: '(((accounts)|(classroom)|(cros)|(gmail)|(calendar)|(docs)|(gplus)|(sites)|(device_management)|(drive)):[^,]+,)*(((accounts)|(classroom)|(cros)|(gmail)|(calendar)|(docs)|(gplus)|(sites)|(device_management)|(drive)):[^,]+)'
```

### 6.04.08

Updated processing of `<DriveFileURL>` as Google introduced this new form
of a folder URL that GAM didn't recognize and thus couldn't isolate `<DriveFileID>`.
```
https://drive.google.com/drive/folders/<DriveFileID>?resourcekey=<String>
```

### 6.04.07

Changed `config csv_input_row_filter|csv_output_row_filter` processing of blank fields
for `count<Operator><Number>` and `boolean:<Boolean>`. Previously, a blank field was
always treated a mismatch; now a blank field will be interpreted as `False` for `<Boolean>`
and `0` for `<Number>` and the match test will be performed.

Added options `primary` and `default` to the following commands
so that only the primary or default sendas is displayed
for each user in `<UserTypeEntity>` rather than all sendas.
```
gam <UserTypeEntity> show sendas [compact|format|html]
        [primary] [default] [verifyonly]
gam <UserTypeEntity> print sendas [compact]
        [primary] [default] [verifyonly] [todrive <ToDriveAttribute>*]
```

Added options `primary` and `default` to the following commands
so that the primary or default signature is displayed
for each user in `<UserTypeEntity>` rather than the current signature.
```
gam <UserTypeEntity> show signature [compact|format|html]
        [primary] [default] [verifyonly]
gam <UserTypeEntity> print signature [compact]
        [primary] [default] [verifyonly] [todrive <ToDriveAttribute>*]
```

Added option `verifyonly` to the commands show above; it causes a Boolean
to be displayed in the `signature` field rather that the signature text;
this simplifies checking for users with undefined signatures.

For example, this command will display a list of users without a primary email address signature (wrapped for readability):
```
gam config csv_output_row_filter "signature:boolean:false" csv_output_header_filter "User,displayName,signature"
    auto_batch_min 1 num_threads 10 redirect csv ./NoPrimarySignature.csv multiprocess
    all users print signature primary verifyonly

Explanation:
config csv_output_row_filter "signature:boolean:false" - Output rows that indicate no signature
csv_output_header_filter "User,displayName,signature" - Output basic headers
auto_batch_min 1 num_threads 10 - Turn on parallel processing
redirect csv ./NoPrimarySignature.csv multiprocess - Intelligently combine output from all processes
all users - Process all non-suspended users
print signature primary verifyonly - Display state of primary email address signature
```

### 6.04.06

Eliminated `ios` from `<DeviceType> ::= android|chrome_os|google_sync|linux|mac_os|windows`
as company owned IOS devices can not be created with `gam create device`.

### 6.04.05

Fixed bug in `gam <UserTypeEntity> get drivefile` where extensions were inappropriately applied
to files that Google reported as having no extension.

### 6.04.04

Fixed bug in `gam <UserTypeEntity> move drivefile ... duplicatefiles uniquename` that caused
a trap when the source file name contained a '(' with no following ')' or contained a '['.

Updated `gam <UserTypeEntity> move drivefile ... duplicatefiles uniquename` to not treat the
rightmost '.' followed by more than five characters as an extension.
* `foo.abcde` will be renamed to `foo(1).abcde` when moved into a folder containing `foo.abcde`
* `foo.abcdef` will be renamed to `foo.abcdef(1)` when moved into a folder containing `foo.abcdef`

### 6.04.03

Fixed bug in `gam report` where event names were not put in upper case for:
`chrome`, `contextawareaccess`, `datastudio` and `jamboard`.

### 6.04.02

Added `chrome`, `contextawareaccess` and `datastudio` to `<ActivityApplicationName>` so you can do `gam report xxx`.

### 6.04.01

Added `keep` to `<ActivityApplicationName>` so you can do `gam report keep`.

Handle the following error when trying to share a folder on a Team Drive to a domain.
```
ERROR: 400: invalidLinkVisibility - Bad Request. User message: ""
```

### 6.04.00

Following Jay's lead, added chat bot commands.
* https://github.com/taers232c/GAMADV-XTD3/wiki/Chat-Bot

### 6.03.34

Updated `gam copy drivefile` to handle the following error:
```
ERROR: internalError - Internal Error
```

### 6.03.33

Added option `stripnameprefix <String>` to `gam create|copy|update drivefile` to aid in the following situation.
You have a CSV file listing some files owned by an external user; your ultimate goal is to move them to a Shared Drive.
This is not possible so you decide to make locally owned copies, backup the externally owned originals and then rename
the copies to have the original name and then move those copies to thw Shared Drive.
```
# Make copies of the externally owned files
gam csv ./ExtFiles.csv gam user user@domain.com copy drivefile "~id"
# You now have `FileName` and 'Copy of Filename`; move the originals to a backup folder
gam csv ./ExtFiles.csv gam user user@domain.com update drivefile "~id" parentid <BackupParentFolderID>
# Generate a list of the "Copy of " copied files
gam redirect csv ./CopyOfFiles.csv user user@domain.com print filelist fields id,name query "name contains 'Copy of '"
# Rename the files stripping off the "Copy of " prefix
gam csv ./CopyOfFiles.csv gam user user@domain.com update drivefile "~id" newfilename "~name" stripnameprefix "Copy of "
```

### 6.03.32

Added option `notdomain <RegularExpression>` to `<PermissionMatch>` to make it easier to
select files owned by someone outside of your domain.
```
gam user user@domain.com print filelist showownedby others fields id,name,owners.emailaddress pm type user role owner notdomain domain.com em
```

### 6.03.31

Fixed a bug in `gam create|update user` where the required `area` field in `location`
could be omitted and no error message was given.

### 6.03.30

Added option `addtitle <String>` to `gam print|show drivefileacls` to provide more useful output
when reading file IDs from a CSV file. By default, just the file ID is displayed with the permissions;
the `showtitles` option adds the file name to the output at the expense of an additional API call.
If you have the file name in the CSV file, you can use the `addtitle` option to supply the file name.
For example, to get the ACLs for your Team Drives with the Team Drive name included in the output:
```
gam redirect csv ./TeamDrives.csv print teamdrives
gam redirect csv ./TeamDriveACLs.csv multiprocess csv ./TeamDrives.csv gam print drivefileacls teamdriveid "~id" addtitle "~name" fields id,domain,emailaddress,role,type,deleted
```

### 6.03.29

Added option `stripcrsfromname` to the following commands that causes carriage returns `\r`
to be stripped from drive file names. This option is special purpose and will not generally be used.
```
gam <UserTypeEntity> show fileinfo
gam <UserTypeEntity> print filelist
gam <UserTypeEntity> print|show filetree
gam <UserTypeEntity> print|Show filerevisions
```
How did a carriage return get added to a drive file name? Good question; the files seen so far are named `Icon\r`.

### 6.03.28

Fixed bug in `gam <UserTypeEntity> print filelist` where blank lines were being displayed after
the `Got n Drive File/Folder ...` messages.

### 6.03.27

Updated `gam print courses` to handle the following error.
```
ERROR: 503: serviceNotAvailable - The service is currently unavailable.
```

Updated `gam <UserTypeEntity> move events <UserCalendarEntity> <EventEntity> to|destination <CalendarItem>`
to correct an incorrect error message from Google.
* Incorrect message: Move Failed: You need to have reader access to this calendar.
* Correct message: Move Failed: You need to have writer access to both calendars.

### 6.03.26

Updated the following commands to allow selection of archived users from a source group.
```
gam update group add|delete|update|sync
gam update cigroups add|delete|update|sync
```
See: https://github.com/taers232c/GAMADV-XTD3/wiki/Groups-Membership
See: https://github.com/taers232c/GAMADV-XTD3/wiki/Cloud-Identity-Groups-Membership

Updated the following command to allow selection of archived users to be cleared.
```
gam update group clear
```
See: https://github.com/taers232c/GAMADV-XTD3/wiki/Groups-Membership

Updated the following commands to allow selection of archived users for display.
```
gam info group
gam print groups
gam print group-members
```
See: https://github.com/taers232c/GAMADV-XTD3/wiki/Groups

Added new option to `<UserTypeEntity>` that allows selection of group members based on their archived status.
```
group_users_select <GroupList>
       [members] [managers] [owners]
       [notsuspended|suspended] [notarchived|archived]
       [primarydomain] [domains <DomainNameList>] [recursive|includederivedmembership] end
```
See: https://github.com/taers232c/GAMADV-XTD3/wiki/Collections-of-Users#selected-users-from-groups

### 6.03.25

Updated `gam create project` to handle Google change that causes the following error:
```
ERROR: 403: Permission iam.serviceAccountKeys.create is required to perform this operation on service account
```

### 6.03.24

Added option `showdetails` to `gam <UserTypeEntity> create drivefile` that adds the
parent folder ID and MIME type to the output.

### 6.03.23

Updated `<BrowserFieldName>`:
* Added `deviceidentifiershistory`
* Removed `installedbrowserversion`

Updated `gam print browsers` to avoid token expiration and minimize memory usage.

### 6.03.22

Fixed bug in `gam <UserTypeEntity> update drivefile` where the options `retainname | (newfilename <DriveFileName>)`
were ignored if they appeared after option `localfile <FileName>`; the options can now appear in any order.

### 6.03.21

Updated the processing of `<UserTypeEntity>` to minimize memory usage when getting users directly in an OU.
```
ou|ou_ns|ou_susp <OrgUnitItem>
ous|ous_ns|ous_susp <OrgUnitList>
```

Updated `gam [<UserTypeEntity>] create|update teamdrive <Name> ... customtheme <DriveFileID> <Float> <Float> <Float>`
to better handle errors.

Updated `gam [<UserTypeEntity>] create teamdrive <Name>` to output the name of the newly created
Team Drive in addition to its ID.
```
$ gam user user@domain.com create teamdrive Test
User: user@domain.com, Shared Drive Name: Test, Shared Drive ID: 0ALHCDtCDTx_4Uk9PVA, Created
```
### 6.03.20

Updated `gam <UserTypeEntity> print filelist select <DriveFileEntity>` to display progress
messages as it recurses through the folder tree.

Updated `gam <UserTypeEntity> print filelist select <DriveFileEntity> norecursion` to
retrieve the selected folder without retrieving its direct children which aren't going to be displayed.

### 6.03.19

Added option `showattachments [attachmentnamepattern <RegularExpression>]` to
`gam <UserTypeEntity> print messages|threads`. This adds the column `Attachments`
that shows the number of attachments and columns `Attachments.n.name` and `Attachments.n.mimeType`
that show the attachment names and MIME types.

### 6.03.18

Added commands to delete specific domain contacts and user's contacts using the People API.
```
gam delete domaincontacts <PeopleResourceNameEntity>
gam <UserTypeEntity> delete peoplecontacts <PeopleResourceNameEntity>
```
* https://github.com/taers232c/GAMADV-XTD3/wiki/People
* https://github.com/taers232c/GAMADV-XTD3/wiki/Users-People

Updated various google libraries.

### 6.03.17

Corrected 6.03.16 code fix to avoid trap on Windows when doing the following:
```
gam config debug_level 1 redirect stdout foo.txt multiprocess ..
```
It fixed the trap but disabled the redirect.

### 6.03.16

Fixed code to avoid trap on Windows when doing the following:
```
gam config debug_level 1 redirect stdout foo.txt multiprocess ..
```

Updated code to handle the following error in `gam copy drivefile`:
```
ERROR: 400: badRequest - Bad Request
```

Updated code in `gam info resoldcustomer <CustomerID>` to avoid a trap when `<CustomerID>`
is not a resold customer ID.

Fixed bug in `gam <UserTypeEntity> print filelist ... formatjson` that caused a trap when no files were listed.

### 6.03.15

Fixed bug in `gam update cigroup` where `dynamic <QueryDynamicGroup>` was makrked as invalid.

### 6.03.14

Added code to handle the following errors when adding an ACL on a Team Drive file.
```
ERROR: 403: cannotShareTeamDriveWithNonGoogleAccounts - Cannot share a shared drive with non Google accounts.
ERROR: 400: shareOutNotPermitted - Bad Request. User message: "This email address is linked to a personal Google Account. <Your domain> doesn't allow sharing with personal accounts."
```

### 6.03.13

Added option `show all|direct|inherited` to `gam print|show chromepolicies` which allows selection of
policies by whether the policy is set directly on the OU or is inherited from a parent OU; the default is `all`.
A Boolean field/column, `direct`, has been added to the output. This makes copying only direct policies from one OU to another easy.
```
# Display direct policies
gam redirect csv ChromePolicies.csv print chromepolicies ou "/Path/To/OU1" show direct
gam csv ChromePolicies.csv gam update chromepolicy "~name" "~fields.0.name" "~fields.0.value" "~fields.1.name" "~fields.1.value" ou "/Path/To/OU2"

# Display all policies, select direct on update
gam redirect csv ChromePolicies.csv print chromepolicies ou "/Path/To/OU1"
gam config csv_input_row_filter "direct:boolean:true" csv ChromePolicies.csv gam update chromepolicy "~name" "~fields.0.name" "~fields.0.value" "~fields.1.name" "~fields.1.value" ou "/Path/To/OU2"
```

### 6.03.12

Updated `gam update chromepolicy (<SchemaName> (<Field> <Value>)+)+` to allow empty
`<Field> <Value>` pairs. This makes copying a set of policies from one OU to another easy
without having to deal with policies with differing numbers of fields.
```
gam csv ChromePolicies.csv gam update chromepolicy "~name" "~fields.0.name" "~fields.0.value" "~fields.1.name" "~fields.1.value" ou "/Path/To/OU"
```

Following Jay's lead, added option 'grouptree` to `gam info user` and `membertree` to `gam info cigroup`.
* https://github.com/taers232c/GAMADV-XTD3/wiki/Users#display-information-about-a-single-user
* https://github.com/taers232c/GAMADV-XTD3/wiki/Cloud-Identity-Groups#display-information-about-individual-groups

### 6.03.11

Upgraded to Python 3.9.5.

Following Jay's lead, Google time is now checked against admin.googleapis.com rather than www.googleapis.com.

Updated code to convert the Shared Drive file field `trashedTime` from UTC according to `gam.cfg timezone`.

### 6.03.10

Fixed bug in `gam create course ... copyfrom <CourseID> ... copytopics ... copymaterialsfiles true materialstates "all"`
that generated the following error:
```
ERROR: 400: invalidArgument - Request contains an invalid argument.
```

### 6.03.09

Added command to print Chrome policies.
```
gam print chromepolicies [todrive <ToDriveAttribute>*]
        [filter <String>]
        ou|org|orgunit <OrgUnitItem> [(printerid <PrinterID>)|(appid <AppID>)]
        [[formatjson [quotechar <Character>]]
```

### 6.03.08

Added commands to display specific domain profiles and user's contacts using the People API.
```
gam info domainprofiles <PeopleResourceNameEntity>
        [allfields|(fields <PeopleFieldNameList>)]
        [formatjson]
gam <UserTypeEntity> info peoplecontacts <PeopleResourceNameEntity>
        [allfields|(fields <PeopleFieldNameList>)]
        [formatjson]
```
* https://github.com/taers232c/GAMADV-XTD3/wiki/People
* https://github.com/taers232c/GAMADV-XTD3/wiki/Users-People

### 6.03.07

Updated code to properly set the values for the following Chrome Policy schema values:
* chrome.users.SessionLength - sessionDurationLimit
* chrome.users.BrowserSwitcherDelayDuration - browserSwitcherDelayDuration
* chrome.users.MaxInvalidationFetchDelay - maxInvalidationFetchDelay
* chrome.users.SecurityTokenSessionSettings - securityTokenSessionNotificationSeconds
* chrome.users.PrintingMaxSheetsAllowed - printingMaxSheetsAllowedNullable

### 6.03.06

Added enhanced commands for displaying Chrome Policy schemas.
```
gam info chromeschema <SchemaName>
        <ChromePolicySchemaFieldName>* [fields <ChromePolicySchemaFieldNameList>]
        [formatjson]
gam show chromeschemas
        [filter <String>]
        <ChromePolicySchemaFieldName>* [fields <ChromePolicySchemaFieldNameList>]
        [formatjson]
gam print chromschemas [todrive <ToDriveAttribute>*]
        [filter <String>]
        <ChromePolicySchemaFieldName>* [fields <ChromePolicySchemaFieldNameList>]
        [[formatjson [quotechar <Character>]]
```

### 6.03.05

Added commands to print Gmail imap/pop/language settings to CSV files.
```
gam <UserTypeEntity> print imap|imap4 [todrive <ToDriveAttribute>*]
gam <UserTypeEntity> print pop|pop3 [todrive <ToDriveAttribute>*]
gam <UserTypeEntity> print language [todrive <ToDriveAttribute>*]
```

### 6.03.04

Added commands to display user's other contacts using the People API.
* https://github.com/taers232c/GAMADV-XTD3/wiki/Users-People

To use this feature you must add the `People API` to your project and authorize the appropriate scopes:
* `People API - Other Contacts - read only`: https://www.googleapis.com/auth/contacts.other.readonly
```
gam update project
gam user user@domain.com check serviceaccount
```

Added commands to display user's contact groups using the People API.
* https://github.com/taers232c/GAMADV-XTD3/wiki/Users-People

### 6.03.03

Added commands to display user's contacts using the People API.
* https://github.com/taers232c/GAMADV-XTD3/wiki/Users-People

Simplified commands for displaying domain contacts/profiles with the People API.
* https://github.com/taers232c/GAMADV-XTD3/wiki/People

### 6.03.02

Changed the time window for `api_calls_rate_check` from 100 seconds to 60 seconds as Google
seems to be changing quota limits to be measured over 60 seconds.

### 6.03.01

Added option `showsource` to `gam <UserTypeEntity> print filelist countsonly` that adds an additional
column `Source` that indicates the top level folder ID from which the counts are derived.

### 6.03.00

As the Contacts API is being deprecated in June, additional support for the People API has been added.
This is the first step of many required to make the transition.
* https://github.com/taers232c/GAMADV-XTD3/wiki/People

The existing commands `get profilephoto`, `print|show peopleprofile` have been changed to use
Service Account Access to avoid having to make additional Directory API calls to convert the user email address to the people ID.

To use these features you must add the `People API` to your project and authorize the appropriate scopes:
* `Client Access` - `People Directory API - read only`.
* `Service Account Access`
  * `People Directory API - read only`: https://www.googleapis.com/auth/directory.readonly
  * `OAuth2 API`: https://www.googleapis.com/auth/userinfo.profile
```
gam update project
gam oauth create
gam user user@domain.com check serviceaccount
```

Following Jay's lead, added new license SKU `Cloud Search`.

### 6.02.04

Updated code to handle the following error:
```
ERROR: Authentication Token Error - Not all requested scopes were granted by the authorization server, missing scopes , https://sites.google.com/feeds, email, https://www.google.com/m8/feeds, profile.
```

### 6.02.03

Added optional argument `convertalias` to all commands that manipulate Gmail delegates.
If not specified, the extra API call introduced in 6.02.00 to convert potential delegate email aliases
to primary email addresses is not performed; if you specify an alias as a delegate, the command will fail.
If you know that all of the delegate email addresses are primary, you can omit `convertalias` and avoid the extra API calls.

### 6.02.02

Thanks to Jay's assistance in getting a Data Studio API discovery document,
updated the Data Studio permissions commands.
* https://github.com/taers232c/GAMADV-XTD3/wiki/Users-DataStudio

### 6.02.01

Fixed bug in `gam <UserTypeEntity> add datastudiopermissions` that caused a trap.

### 6.02.00

Following Jay's lead, aliases are converted to primary email addresses when adding delegates.

Added commands to display Data Studio assets and display/manage Data Studio permissions.
* https://github.com/taers232c/GAMADV-XTD3/wiki/Users-DataStudio

To use these commands you must add the `Data Studio API` to your project and update your service account authorization.
```
gam update project
gam user user@domain.com check serviceaccount
```
This is a first release from me, experiment and use with caution.

### 6.01.09

Added support for `localfile -` in `gam <UserTypeEntity> create|update drivefile` which allows
commands/programs to output data to stdout which can then be uploaded to a Google Drive file.
```
generatedata | gam user user@domain.com create drivefile drivefilename test.csv localfile - mimetype gsheet
```

### 6.01.08

Following Jay's lead, cleaned up field names in `gam print chromehistory`.

Following Jay's lead, added new license SKU `Google Workspace Frontline`.

### 6.01.07

Following Jay's lead, added additional columns to `gam print chromehistory`.

### 6.01.06

Updated `gam whatis <EmailItem>` to check if `<EmailItem>` is an unmanaged account
if it is not a group/user email address or alias.

Following Jay's lead, switched all commands referencing unmanaged accounts to use
Service Account access rather than Client access. This avoids the `Invalid Scope`
issue when doing `gam oauth create`. The `Cloud Identity User Invitations API` has
been dropped from `gam oauth create` for now.

### 6.01.05

Added the capability to display Chrome version history.
* https://github.com/taers232c/GAMADV-XTD3/wiki/Chrome-Version-History

Added the option `verifynotinvitable` to `gam create|update alias|group|user` that causes GAM to verify
that the email address being created/updated is not that of an unmanaged account; if it is, the
command is not performed.

To use this option you must add the `Cloud Identity API` to your project and authorize
the appropriate scope: `Cloud Identity User Invitations API`.

* Unmanaged Accounts - https://github.com/taers232c/GAMADV-XTD3/wiki/Unmanaged-Accounts

You'll have to do `gam update project` and `gam oauth create` to enable this option.

Updated google-api-python-client to version 2.1.0.

### 6.01.04

Fixed bug in `gam report usage customer` that caused a trap.

Upgraded to Python 3.9.4.

### 6.01.03

Upgraded to Python 3.9.3.

Upgraded to OpenSSL 1.1.1k.

### 6.01.02

Updated google_auth, google_auth_httplib2, google_auth_oauthlib, googleapiclient, httplib2 libraries.

### 6.01.01

Updated `gam print|show chromeversions` to avoid a trap where a version was returned without a `version` field.

### 6.01.00

Added the capability to access two new areas.

* Chrome Installed Apps Counts - https://github.com/taers232c/GAMADV-XTD3/wiki/Chrome-Installed-Apps-Counts
* Chrome Versions Counts - https://github.com/taers232c/GAMADV-XTD3/wiki/Chrome-Versions-Counts

You'll have to do `gam update project` and `gam oauth create` to enable these commands.

As with any initial release, report any problems.

Improved error reporting when trying to add/remove licenses with an administrator that is not authorized to do so.

### 6.00.08

Fixed bug in `gam print course-materials fields <CourseAnnouncementFieldNameList>` that caused the following error:
```
Course: <CourseID>, Print Failed: Request contains an invalid argument.
```

Code cleanup for `gam print course-work` and `gam print course-materials`.

### 6.00.07

Added option `splitupdate` to `gam <UserTypeEntity> update calattendees` to handle replacing
an email alias with its primary email in the event attendee list.
By default, when you try to replace an email alias with its primary email, the Google Calendar API
detects that the underlying user ID is the same and doesn't change the address. The `splitupdate`
option causes GAM to make two updates to the attendee list; the first removes the alias and
the second adds the primary email.

### 6.00.06

Added command `gam print addresses [todrive <ToDriveAttribute>*]` that produces a
two column CSV file (headers Type, Email) that displays all group and user primary
email addresses and aliases. The types are: Group, GroupAlias, GroupNEAlias,
SuspendedUser, User, UserAlias, UserNEAlias. 'NE' is and abbreviation for NonEditable.

### 6.00.05

Fixed bug in `gam print vaultcounts ... everyone` which caused the following error:
```
ERROR: getUsersToModify coding error
```

### 6.00.04

Updated `<CalendarAttribute>` to allow specifying a list of email notification event types.

Previously, you had to specify each email notification event type individually (this still works).
```
<CalendarEmailNotificatonEventType> ::=
        eventcreation|eventchange|eventcancellation|eventresponse|agenda
<CalendarEmailNotificatonEventTypeList> ::=
        <CalendarEmailNotificatonEventType>(,<CalendarEmailNotificatonEventType>)*

<CalendarAttribute> ::=
...
        (notification clear|(email <CalendarEmailNotificatonEventTypeList>))|

gam user user@domain.con update calendar primary notification email eventchange,eventcancellation
```

### 6.00.03

Fixed bug in `gam calendar update event` introduced in 5.34.02 where updating an event's start or end time appeared to work
but no change was actually made.

### 6.00.02

Added support for stand-alone course materials; these were not previously supported by the Google Classroom API.
* See: https://github.com/taers232c/GAMADV-XTD3/wiki/Classroom-Courses#display-course-materials
* See: https://github.com/taers232c/GAMADV-XTD3/wiki/Classroom-Courses#create-and-update-courses

To use the course materials features you must authorize the appropriate scope: `Classroom API - Course Work/Materials`.
```
gam oauth create
gam user user@domain.com check|update serviceaccount
```

### 6.00.01

Improve error handling in `gam delete|update chromepolicy` and `gam show chromepolicies`.

When showing Chrome Policies, display OU and optional printerid/appid at top of output.

### 6.00.00

Following Jay's lead, added the capability to manage three new areas.

* Chrome Policies - https://github.com/taers232c/GAMADV-XTD3/wiki/Chrome-Policies
* Chrome Printers - https://github.com/taers232c/GAMADV-XTD3/wiki/Chrome-Printers
* Unmanaged Accounts - https://github.com/taers232c/GAMADV-XTD3/wiki/Unmanaged-Accounts

You'll have to do `gam update project` and `gam oauth create` to enable these commands.

As with any initial release, proceed with care and report any problems.

Updated `gam report customer|user` to continue processing subsequent dates when Google indicates that no data is available
for a particular date.

Improved `gam report` `Got` messages so it is easier to monitor progress.

Removed extraneous `email` header in `gam report user ... aggregatebydate`.


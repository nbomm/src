# Users - Drive Files Copy/Move
- [API documentation](#api-documentation)
- [Query documentation](#query-documentation)
- [Python Regular Expressions](Python-Regular-Expressions) Sub function
- [Collections of Users](Collections-of-Users)
- [Definitions](#definitions)
- [Copy files and folders](#copy-files-and-folders)
  - [Copy Permissions](#copy-permissions)
  - [Copy content of shared drive to other shared drive](#example-copy-the-content-of-one-shared-drive-into-another-shared-drive)
- [Move files and folders](#move-files-and-folders)
  - [Simple moves by changing parents](#simple-moves-by-changing-parents)
  - [Move Permissions](#move-permissions)
  - [Complex moves](#complex-moves)

## API documentation
* https://developers.google.com/drive/api/v3/reference/files

## Query documentation
* https://developers.google.com/drive/api/v3/search-files

## Definitions
See [Drive File Selection](Drive-File-Selection) for symbols not listed here, such as `<DriveFileEntity>`
```
<CorporaAttribute> ::= allteamdrives|domain|onlyteamdrives|user
<DomainName> ::= <String>(.<String>)+
<DomainNameList> ::= "<DomainName>(,<DomainName>)*"
<EmailAddress> ::= <String>@<DomainName>
<UniqueID> ::= uid:<String>
<UserItem> ::= <EmailAddress>|<UniqueID>|<String>

<DriveFileParentAttribute> ::=
        (parentid <DriveFolderID>)|
        (parentname <DriveFolderName>)|
        (anyownerparentname <DriveFolderName>)|
        (teamdriveparentid <DriveFolderID>)|
        (teamdriveparent <SharedDriveName>)|
        (teamdriveparentid <SharedDriveID> teamdriveparentname <DriveFolderName>)|
        (teamdriveparent <SharedDriveName> teamdriveparentname <DriveFolderName>)

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
## Copy files and folders
```
gam <UserTypeEntity> copy drivefile <DriveFileEntity>
        [newfilename <DriveFileName>] (replacefilename <RegularExpression> <String>)*
        [stripnameprefix <String>]
        [newfilename <DriveFileName>] [stripnameprefix <String>]
        [excludetrashed] [returnidonly|returnlinkonly]
        [summary [<Boolean>]] [showpermissionmessages [<Boolean>]]
        [<DriveFileParentAttribute>]
        [mergewithparent [<Boolean>]] [recursive [depth <Number>]]
        <DriveFileCopyAttribute>*
        [duplicatefiles overwriteolder|overwriteall|duplicatename|uniquename|skip]
        [duplicatefolders merge|duplicatename|uniquename|skip]
        [copytopfileparents none] [copytopfolderparents none]
        [copysubfileparents none] [copysubfolderparents none]
        [copyfilepermissions [<Boolean>]]
        [copyfileinheritedpermissions [<Boolean>]
        [copyfilenoninheritedpermissions [<Boolean>]
        [copymergewithparentfolderpermissions [<Boolean>]]
        [copymergedtopfolderpermissions [<Boolean>]]
        [copytopfolderpermissions [<Boolean>]]
        [copytopfolderiheritedpermissions [<Boolean>]]
        [copytopfoldernoniheritedpermissions never|always|syncallfolders|syncupdatedfolders]
        [copymergedsubfolderpermissions [<Boolean>]]
        [copysubfolderpermissions [<Boolean>]]
        [copysubfolderinheritedpermissions [<Boolean>]]
        [copysubfoldernoniheritedpermissions never|always|syncallfolders|syncupdatedfolders]
        [copysheetprotectedranges [<Boolean>]]
        [copysheetprotectedrangesinheritedpermissions [<Boolean>]]
        [copysheetprotectedrangesnoninheritedpermissions [<Boolean>]]
        [excludepermissionsfromdomains <DomainNameList>]
        (mappermissionsdomain <DomainName> <DomainName>)*
        [sendemailifrequired [<Boolean>]]
```
The files/folders specified by `<DriveFileEntity>` are referred to as `source`, `target` refers to where those files are being copied.
The files/folders specified by `<DriveFileEntity>` are referred to as `top`; when a folder is being copied recursively, the files/folders that it contains are referred as `sub`.

At its simplest, you copy files/folders by giving the copy a new name and parent location.

By default, files/folders in the Trash are copied; use `excludetrashed` to prevent these files/folders from being copied.

When copying folders, you have three modes of operation:

### Copy the top folder but none of its sub files/folders
This is the default mode.

### Copy the top folder and its sub files/folders
Use the `recursive` option to enable this mode.
The `depth <Number>` argument controls which files or folders within the top folder are copied.
* `depth -1` - all files and folders in the topfolder and below are copied; this is the default.
* `depth 0` - the files or folders in the top folder are copied, no descendants of folders are copied.
* `depth N` - the files and folders within the topfolder and those files and folders N levels below the top folder are copied.

### Copy the sub files/folders within the top folder, but not the top folder itself
Use the `recursive` and `mergewithparent` options to enable this mode.
The `depth <Number>` argument controls which files or folders within the top folder are copied.
* `depth -1` - all files and folders in the topfolder and below are copied; this is the default.
* `depth 0` - the files or folders in the top folder are copied, no descendants of folders are copied.
* `depth N` - the files and folders within the top folder and those files and folders N levels below the top folder are copied.

### Specify a new name for the file/folder
* `newfilename <DriveFileName>` - The copied file/folder will be named `<DriveFileName>`
  * If `stripnameprefix <String>` is specified, `<String>` will be stripped from the front of `<DriveFileName>`
* If you don't specify a new name, the copy will be named "Copy of `<ExistingName>`" if you're copying the file/folder into the source folder, otherwise the file/folder will retain its current name.

### Update file/folder names when copying a folder structure
Wnen copying a folder structure, use `replacefilename <RegularExpression> <String>` to update file/folder names within the structure; this might
be used when copying a template folder structure and the file/folder names are updated to reflect some characteristic of the target.
You can use multiple `replacefilename <RegularExpression> <String>` options for complex name mapping.
* `copy drivefile name "Top Folder" parentid root recursive newfilename "NewCustomer Folder" replacefilename Template NewCustomer` - "Top Folder" is copied as "NewCustomer Folder"
and "Template" is replaced by "NewCustomer" in all copied sub files and folders
* `copy drivefile name "Template Folder" parentid root recursive replacefilename Template NewCustomer` - "Template" is replaced by "NewCustomer" in the copied top folder and in all copied sub files and folders

### Specify the target(parent) folder
* `parentid <DriveFolderID>` - The target folder is identified by `<DriveFolderID>` which must be writable by `<UserTypeEntity>`.
* `parentname <DriveFolderName>` - A search is performed for a folder named `<DriveFolderName>` owned by `<UserTypeEntity>`.
* `anyownerparentname <DriveFolderName>` - A search is performed for a folder named `<DriveFolderName>` owned by any user but must be writable by `<UserTypeEntity>`.
* `teamdriveparentid <DriveFolderID>` - Shared Drive folder ID; when used alone, this indicates a specific Shared Drive folder.
* `teamdriveparent <SharedDriveName>` - Shared Drive name; when used alone, this indicates the root level of the Shared Drive.
* `teamdriveparentid <SharedDriveID> teamdriveparentname <DriveFolderName>` - A Shared Drive ID and a folder name  on that Shared Drive.
* `teamdriveparent <SharedDriveName> teamdriveparentname <DriveFolderName>` - A Shared Drive name and a folder name on that Shared Drive.
* If none of the parent options are specified, the copied file/folder will be located in the source folder.

### Duplicate files
When copying files, these options control the action GAM takes when a target file has the same name and MIME type as the source file:
* `duplicatefiles overwriteolder` - If the target file has an older `modifiedDate` than the source file, it will be deleted and replaced by the source file; otherwise no copy will be made; this is the default action.
* `duplicatefiles overwriteall` - The target file will be deleted and replaced by the source file.
* `duplicatefiles duplicatename` - The source file will be copied to a duplicate named target file.
* `duplicatefiles uniquename` - The source file will be copied to the target file after adding `(N)` to the base of the file name.
* `duplicatefiles skip` - No copy will be made.

### Duplicate folders
When copying folders, these options control the action GAM takes when a target folder has the same name as the source folder:
* `duplicatefolders merge` - The contents of the source folder will be merged with the contents of the target folder; this is the default action.
* `duplicatefolders duplicatename` - The source folder will be copied to a duplicate named target folder.
* `duplicatefolders uniquename` - The source file will be copied to the target file after adding `(N)` to the base of the file name.
* `duplicatefolders skip` - No copy will be made.

### Multiple parents
Generally, files and folders have one parent folder; these options control the action GAM takes when a source file/folder has multiple parents.

No existing parents are copied for source top/sub files/folders.

The following options will generate an error.

These options control the action GAM takes when a source top file/folder has multiple parents.
* `copytopfileparents all` - Copy all of the existing parents.
* `copytopfolderparents all` - Copy all of the existing parents.

These options control the action GAM takes when a source sub file/folder has multiple parents.
* `copysubfileparents nonpath` - Copy all of the existing parents except the parent on the path from the top folder; this is the default action.
* `copysubfileparents all` - Copy all of the existing parents.
* `copysubfolderparents nonpath` - Copy all of the existing parents except the parent on the path from the top folder; this is the default action.
* `copysubfolderparents all` - Copy all of the existing parents.

### Copy Permissions
### Files
When a file is copied, its permissions are not copied; these options control copying permissions for files. For options
of the form `option [<Boolean>]`; if `<Boolean>` is omitted, `true` is assumed.

When copied, a target file inherits the permissions of its parent folder; this option controls whether GAM copies the existing source file permissions:
* `copyfilepermissions false` - The permissions of the source top/sub file are not copied to the target file; this is the default action.
* `copyfilepermissions true` - The permissions of the source top/sub file are copied to the target file

When `copyfilepermissions` is `true`, this option controls whether GAM copies inherited source file permissions; this only applies to source files
on a Shared Drive.
* `copyfileinheritedpermissions false` - The inherited permissions of the source file are not copied to the target file
* `copyfileinheritedpermissions true` - The inherited permissions of the source file are copied to the target file; this is the default action.

When `copyfilepermissions` is `true`, this option controls whether GAM copies non-inherited source file permissions; this only applies to source files
on a Shared Drive.
* `copyfilenoninheritedpermissions false` - The non-inherited permissions of the source file are not copied to the target file
* `copyfilenoninheritedpermissions true` - The non-inherited permissions of the source file are copied to the target file; this is the default action.

### Folders
When a folder is copied, its permissions are not copied; these options control copying permissions for folders. For options
of the form `option [<Boolean>]`; if `<Boolean>` is omitted, `true` is assumed.

When copied, a target folder inherits the permissions of its parent folder; these options control whether/how GAM copies the existing source folder permissions;
The default values of options introduced in version 6.14.00 are set to match the behavior of earlier versions.

When `mergewithparent` is `true`:
* `copymergewithparentfolderpermissions false` - The permissions of the source top folder are not not copied to the target folder; this is the default action.
* `copymergewithparentfolderpermissions true` - The permissions of the source top folder are copied to the target folder.

When `mergewithparent` is `false`, `duplicatefolders` is `merge` and the top folder is a duplicate:
* `copymergdtopfolderpermissions false` - The permissions of the source top folder are not not copied to the target folder.
* `copymergedtopfolderpermissions true` - The permissions of the source top folder are copied to the target folder; this is the default action.

When `duplicatefolders` is `merge` and a sub folder is a duplicate:
* `copymergedsubfolderpermissions false` - The permissions of the source sub folder are not not copied to the target folder.
* `copymergedsubfolderpermissions true` - The permissions of the source sub folder are copied to the target folder; this is the default action.

When `duplicatefolders` is `duplicatename` or `uniquename` and a top/sub folder is not a duplicate:
* `copytopfolderpermissions true` - The permissions of the source top folder are copied to the target folder; this is the default action.
* `copytopfolderpermissions false` - The permissions of the source top folder are not not copied to the target folder.
* `copysubfolderpermissions true` - The permissions of the source sub folders are copied to the target folder; this is the default action.
* `copysubfolderpermissions false` -  The permissions of the source sub folders are not not copied to the target folder.

When copying folder permissions, this option controls whether GAM copies inherited source folder permissions; this only applies to source folders
on a Shared Drive.
* `copytopfolderinheritedpermissions false` - The inherited permissions of the source top folder are not copied to the target folder.
* `copytopfolderinheritedpermissions true` - The inherited permissions of the source top folder are copied to the target folder; this is the default action.
* `copysubfolderinheritedpermissions false` - The inherited permissions of the source sub folder are not copied to the target folder.
* `copysubfolderinheritedpermissions true` - The inherited permissions of the source sub folder are copied to the target folder; this is the default action.

When copying folder permissions on a merged top/source folder, these options control whether GAM copies non-inherited source folder permissions.
* `copytopfoldernoninheritedpermissions never` - The non-inherited permissions of the source top folder are not copied to the target folder.
* `copytopfoldernoninheritedpermissions always` - The non-inherited permissions of the source top folder are copied to the target folder; this is the default action.
* `copytopfoldernoninheritedpermissions syncallfolders` - The non-inherited permissions of the source top folder are synced with the target folder. This requires additional API calls.
* `copytopfoldernoninheritedpermissions syncupdatedfolders` - The non-inherited permissions of the source top folder are synced with the target folder if the modifiedTime of the source folder is greater than the modifiedtime of the target folder. This requires additional API calls.
* `copysubfoldernoninheritedpermissions never` - The non-inherited permissions of the source sub folder are not copied to the target folder.
* `copysubfoldernoninheritedpermissions always` - The non-inherited permissions of the source sub folder are copied to the target folder; this is the default action.
* `copysubfoldernoninheritedpermissions syncallfolders` - The non-inherited permissions of the source sub folder are synced with the target folder. This requires additional API calls.
* `copysubfoldernoninheritedpermissions syncupdatedfolders` - The non-inherited permissions of the source sub folder are synced with the target folder if the modifiedTime of the source folder is greater than the modifiedtime of the target folder. This requires additional API calls.

When `syncallfolders` or `syncupdatedfoders` is specifid:
* A permission on the source folder has been removed since the last copy; it will be removed from the target folder.
* A permission role on the source folder has been changed since the last copy; it will be updated on the target folder.
* A permission expiration time on the source folder has been added/changed/removed since the last copy; it will be added/changed/removed on the target folder.

When `excludepermissionsfromdomains <DomainNameList>` is specified, any ACL that references a domain in `<DomainNameList>` will not be copied.

When `mappermissionsdomain <DomainName> <DomainName>` is specifed, any ACL that references the first `<DomainName>` will be modified
to reference the second `<DonainName>` when copied; the original ACL is not modified. The option can be repeated if multiple domain names are to me mapped.

When copying an ACL that references a non Google account, an error is generated unless an email is sent to the account;
by default, no email notifications are sent. The `sendemailifrequired` options instructs GAM to send an email notification in this case.

In versions before 6.03.17, when attempting to copy ACLs, GAM would report any errors; some errors were generated when an attempt
was made to inappropriately copy an ACL. Now, GAM will not attempt to copy ACLs unless they are appropriate.
When `showpermissionmessages` is specified GAM will display messages about ACLs not copied, ACLs that were copied
and any remaining copy errors.

### Google Sheet protected ranges
When the Drive API copies a Google Sheet, the protected ranges within the sheet are not copied. If any of the following
options are true, the protected ranges of the source file are copied to the target file. 
* `copysheetprotectedranges false` - The protected ranges of the source file are not copied to the target file; this is the default action.
* `copysheetprotectedranges true` - The protected ranges and all permissions of the source file are copied to the target file.
* `copysheetprotectedrangesinheritedpermissions false` - The inheried permissions of the source file are not copied to the target file.
* `copysheetprotectedrangesinheritedpermissions true` - The protected ranges and inheried permissions of the source file are copied to the target file.
* `copysheetprotectedrangesnoninheritedpermissions false` - The non-inheried permissions of the source file are not copied to the target file.
* `copysheetprotectedrangesnoninheritedpermissions true` - The protected ranges and non-inheried permissions of the source file are copied to the target file.

### Summary
Use the `summary` option to get a two-line summary of the actions performed.

By default, the user, file name, copied file name and id values are displayed on stdout.
* `returnidonly` - Display just the file ID of the copied file as output
* `returnlinkonly` - Display just the file webViewLink of the copied file as output

When copying folders, the option is only useful when copying a folder without recursion. 

To retrieve the file ID with `returnidonly`:
```
Linux/MacOS
fileId=gam user user@domain.com copy drivefile <DriveFileEntity> ... returnidonly
Windows PowerShell
$fileId = & gam user user@domain.com copy drivefile <DriveFileEntity> ... returnidonly
```
The file ID will only be valid when the return code of the command is 0; program accordingly.

### Example: Copy the content of one shared drive into another shared drive
Suppose you have a source Shared Drive called 0AC_1AB with multiple files and folders, and want to copy all of its content to the target Shared Drive 0AE_9ZX.

The following command will copy the content, files and folders inside the source drive recursively, and put them in the target drive.

The example is assuming that the target drive is empty.

* Inherited folder permssions are not copied as they will be automatically generated.
* Inherited file permssions are not copied as they will be automatically generated.
* Non-inherited top folder (the source drive) permissions are copied.
* Non-inherited sub folder permissions are copied.
* Non-inherited file permissions are copied.
```
gam user user@domain.com copy drivefile teamdriveid 0AC_1AB teamdriveparentid 0AE_9ZX mergewithparent recursive
        copymergewithparentfolderpermissions true
        copytopfolderinheritedpermissions false
        copytopfoldernoninheritedpermissions always
        copysubfolderinheritedpermissions false
        copysubfoldernoninheritedpermissions always
        copyfilepermissions true
        copyfileinheritedpermissions false
        copyfilenoninheritedpermissions true
```

Suppose that the source drive has been updated and you want to refresh the target drive.

* Inherited folder permssions are not copied as they will be automatically generated.
* Inherited file permssions are not copied as they will be automatically generated.
* Non-inherited top folder (the source drive) permissions are copied
* Non-inherited sub folder permissions are copied if the source folder has a later modifiedTime that the target folder
* Non-inherited file permissions are copied.
* Files and folders that have been deleted from the source drive will remain on the target drive
```
gam user user@domain.com copy drivefile teamdriveid 0AC_1AB teamdriveparentid 0AE_9ZX mergewithparent recursive
        copymergewithparentfolderpermissions true
        copytopfolderinheritedpermissions false
        copytopfoldernoninheritedpermissions syncallfolders
        copysubfolderinheritedpermissions false
        copysubfoldernoninheritedpermissions syncupdatedfolders
        copyfilepermissions true
        copyfileinheritedpermissions false
        copyfilenoninheritedpermissions true
```

## Move files and folders
## Simple moves by changing parents
Use this command in the following cases:
* Move a file or folder from one location to another on My Drive
* Move a file or folder from one location to another on a Shared Drive
* Move a file or folder from a Shared Drive to My Drive
* Move a file or folder from a location on a Shared Drive to a location on a different Shared Drive (see notes below)

```
gam <UserTypeEntity> update drivefile <DriveFileEntity> <DriveFileParentAttribute>
```

All file/folder IDs are preserved, there is no processing of permissions.

Now, moving content by just changing the parent is also possible to a completely other drive, even in another Workspace account, but there are some very specific requirements.

1. In [Drive Sharing settings](https://admin.google.com/ac/appsettings/55656082996/sharing?hl=en) of the source domain in the root OU you must allow [Anyone to move files/folders outside of a Shared Drive](https://support.google.com/a/answer/60781?hl=en#zippy=%2Ccontrol-files-stored-on-shared-drives) (#5). That's because the root OU holds the settings for all SDs.

2. The destination user must be a Manager of both the source (external) SD and the destination SD.

3. The destination user must be allowed to move folders to SDs in the destination domain. That's accomplished by assigning a delegated admin role with that right in the destination domain.

## Complex moves
You must use this command when moving between My Drive and Shared Drives. When moving folders, the folder structure on the source drive
is recreated on the target drive; this results in new folder IDs.
```
gam <UserTypeEntity> move drivefile <DriveFileEntity> [newfilename <DriveFileName>]
        [summary [<Boolean>]] [showpermissionmessages [<Boolean>]]
        [<DriveFileParentAttribute>]
        [mergewithparent|mergewithparentretain [<Boolean>]]
        [duplicatefiles overwriteolder|overwriteall|duplicatename|uniquename|skip]
        [duplicatefolders merge|duplicatename|uniquename|skip]
        [copysubfileparents nonpath|none|all] [copysubfolderparents nonpath|none|all]
        [copymergewithparentfolderpermissions [<Boolean>]]
        [copymergedtopfolderpermissions [<Boolean>]]
        [copytopfolderpermissions [<Boolean>]]
        [copytopfolderiheritedpermissions [<Boolean>]]
        [copytopfoldernoniheritedpermissions never|always|syncallfolders|syncupdatedfolders]
        [copymergedsubfolderpermissions [<Boolean>]]
        [copysubfolderpermissions [<Boolean>]]
        [copysubfolderinheritedpermissions [<Boolean>]]
        [copysubfoldernoniheritedpermissions never|always|syncallfolders|syncupdatedfolders]
        [excludepermissionsfromdomains <DomainNameList>]
        (mappermissionsdomain <DomainName> <DomainName>)*
        [retainsourcefolders [<Boolean>]]
        [sendemailifrequired [<Boolean>]]
```
The files/folders specified by `<DriveFileEntity>` are referred to as `source`, `target` refers to where those files are being moved.
The files/folders specified by `<DriveFileEntity>` are referred to as `top`; when a folder is being moved, the files/folders that it contains are referred as `sub`.

At its simplest, you move files/folders by giving them a new name and parent location.

When moving folders, you have two modes of operation:

### Move the top folder and its sub files/folders
This is the default mode.

### Move the sub files/folders within the top folder, but not the top folder itself
* `mergewithparent [<Boolean>]` - If `<Boolean>` is True or not specified, the top folder is deleted after its sub files/folders are moved
* `mergewithparentretain [<Boolean>]` - If `<Boolean>` is True or not specified, the top folder is retained after its sub files/folders are moved

### Specify a new name for the file/folder
* `newfilename <DriveFileName>` - The target file/folder will be named `<DriveFileName>`
* If you don't specify a new name, the target file/folder will be named "Copy of `<ExistingName>`" if you're moving the file/folder into the source folder, otherwise the file/folder will retain its current name.

### Specify the target(parent) folder
* `parentid <DriveFolderID>` - The target folder is identified by `<DriveFolderID>` which must be writable by `<UserTypeEntity>`.
* `parentname <DriveFolderName>` - A search is performed for a folder named `<DriveFolderName>` owned by `<UserTypeEntity>`.
* `anyownerparentname <DriveFolderName>` - A search is performed for a folder named `<DriveFolderName>` owned by any user but must be writable by `<UserTypeEntity>`.
* `teamdriveparentid <DriveFolderID>` - Shared Drive folder ID; when used alone, this indicates a specific Shared Drive folder.
* `teamdriveparent <SharedDriveName>` - Shared Drive name; when used alone, this indicates the root level of the Shared Drive.
* `teamdriveparentid <SharedDriveID> teamdriveparentname <DriveFolderName>` - A Shared Drive ID and a folder name  on that Shared Drive.
* `teamdriveparent <SharedDriveName> teamdriveparentname <DriveFolderName>` - A Shared Drive name and a folder name on that Shared Drive.
* If none of the parent options are specified, the moved file/folder will be located in the source folder.

### Duplicate files
When moving files, these options control the action GAM takes when a target file has the same name and MIME type as the source file:
* `duplicatefiles overwriteolder` - If the target file has an older `modifiedDate` than the source file, it will be deleted and replaced by the source file; otherwise no move will be made; this is the default action.
* `duplicatefiles overwriteall` - The target file will be deleted and replaced by the source file.
* `duplicatefiles duplicatename` - The source file will be moved to a duplicate named target file.
* `duplicatefiles uniquename` - The source file will be moved to the target folder after adding `(N)` to the base of the file name.
* `duplicatefiles skip` - No move will be made.

### Duplicate folders
When moving folders, these options control the action GAM takes when a target folder has the same name as the source folder:
* `duplicatefolders merge` - The contents of the source folder will be merged with the contents of the target folder; this is the default action.
* `duplicatefolders duplicatename` - The source folder will be moved to a duplicate named target folder.
* `duplicatefolders uniquename` - The source file will be moved to the target folder after adding `(N)` to the base of the file name.
* `duplicatefolders skip` - No move will be made.

### Multiple parents
Generally, files and folders have one parent folder; these options control the action GAM takes when a source file/folder has multiple parents.

These options control the action GAM takes when a source top file/folder has multiple parents.
* Copy none of the existing parents.

These options control the action GAM takes when a source sub file/folder has multiple parents.
* `copysubfileparents nonpath` - Copy all of the existing parents except the parent on the path from the top folder; this is the default action.
* `copysubfileparents none` - Copy none of the existing parents.
* `copysubfileparents all` - Copy all of the existing parents.
* `copysubfolderparents nonpath` - Copy all of the existing parents except the parent on the path from the top folder; this is the default action.
* `copysubfolderparents none` - Copy none of the existing parents.
* `copysubfolderparents all` - Copy all of the existing parents.

### Move Permissions
### Folders
When a folder is moved by recreating it, its permissions are not copied; these options control copying permissions for folders. For options
of the form `option [<Boolean>]`; if `<Boolean>` is omitted, `true` is assumed.

When recreated, a target folder inherits the permissions of its parent folder; these options control whether/how GAM copies the existing source folder permissions;
The default values of options introduced in version 6.14.00 are set to match the behavior of earlier versions.

When `mergewithparent` is `true`:
* `copymergewithparentfolderpermissions false` - The permissions of the source top folder are not not copied to the target folder; this is the default action.
* `copymergewithparentfolderpermissions true` - The permissions of the source top folder are copied to the target folder.

When `mergewithparent` is `false`, `duplicatefolders` is `merge` and the top folder is a duplicate:
* `copymergdtopfolderpermissions false` - The permissions of the source top folder are not not copied to the target folder.
* `copymergedtopfolderpermissions true` - The permissions of the source top folder are copied to the target folder; this is the default action.

When `duplicatefolders` is `merge` and a sub folder is a duplicate:
* `copymergedsubfolderpermissions false` - The permissions of the source sub folder are not not copied to the target folder.
* `copymergedsubfolderpermissions true` - The permissions of the source sub folder are copied to the target folder; this is the default action.

When `duplicatefolders` is `duplicatename` or `uniquename` and a top/sub folder is not a duplicate:
* `copytopfolderpermissions true` - The permissions of the source top folder are copied to the target folder; this is the default action.
* `copytopfolderpermissions false` - The permissions of the source top folder are not not copied to the target folder.
* `copysubfolderpermissions true` - The permissions of the source sub folders are copied to the target folder; this is the default action.
* `copysubfolderpermissions false` -  The permissions of the source sub folders are not not copied to the target folder.

When copying folder permissions, this option controls whether GAM copies inherited source folder permissions; this only applies to source folders
on a Shared Drive.
* `copytopfolderinheritedpermissions false` - The inherited permissions of the source top folder are not copied to the target folder.
* `copytopfolderinheritedpermissions true` - The inherited permissions of the source top folder are copied to the target folder; this is the default action.
* `copysubfolderinheritedpermissions false` - The inherited permissions of the source sub folder are not copied to the target folder.
* `copysubfolderinheritedpermissions true` - The inherited permissions of the source sub folder are copied to the target folder; this is the default action.

When copying folder permissions on a merged top/source folder, these options control whether GAM copies non-inherited source folder permissions.
* `copytopfoldernoninheritedpermissions never` - The non-inherited permissions of the source top folder are not copied to the target folder.
* `copytopfoldernoninheritedpermissions always` - The non-inherited permissions of the source top folder are copied to the target folder; this is the default action.
* `copytopfoldernoninheritedpermissions syncallfolders` - The non-inherited permissions of the source top folder are synced with the target folder. This requires additional API calls.
* `copytopfoldernoninheritedpermissions syncupdatedfolders` - The non-inherited permissions of the source top folder are synced with the target folder if the modifiedTime of the source folder is greater than the modifiedtime of the target folder. This requires additional API calls.
* `copysubfoldernoninheritedpermissions never` - The non-inherited permissions of the source sub folder are not copied to the target folder.
* `copysubfoldernoninheritedpermissions always` - The non-inherited permissions of the source sub folder are copied to the target folder; this is the default action.
* `copysubfoldernoninheritedpermissions syncallfolders` - The non-inherited permissions of the source sub folder are synced with the target folder. This requires additional API calls.
* `copysubfoldernoninheritedpermissions syncupdatedfolders` - The non-inherited permissions of the source sub folder are synced with the target folder if the modifiedTime of the source folder is greater than the modifiedtime of the target folder. This requires additional API calls.

When `syncallfolders` or `syncupdatedfoders` is specifid:
* A permission on the source folder has been removed since the last copy; it will be removed from the target folder.
* A permission role on the source folder has been changed since the last copy; it will be updated on the target folder.
* A permission expiration time on the source folder has been added/changed/removed since the last copy; it will be added/changed/removed on the target folder.

When `excludepermissionsfromdomains <DomainNameList>` is specified, any ACL that references a domain in `<DomainNameList>` will not be copied.

When `mappermissionsdomain <DomainName> <DomainName>` is specifed, any ACL that references the first `<DomainName>` will be modified
to reference the second `<DonainName>` when copied; the original ACL is not modified. The option can be repeated if multiple domain names are to me mapped.

When copying an ACL that references a non Google account, an error is generated unless an email is sent to the account;
by default, no email notifications are sent. The `sendemailifrequired` options instructs GAM to send an email notification in this case.

In versions before 6.03.17, when attempting to copy ACLs, GAM would report any errors; some errors were generated when an attempt
was made to inappropriately copy an ACL. Now, GAM will not attempt to copy ACLs unless they are appropriate.
When `showpermissionmessages` is specified GAM will display messages about ACLs not copied, ACLs that were copied
and any remaining copy errors.

### Permissions
In versions before 6.03.17, when attempting to copy ACLs, GAM would report any errors; some errors were generated when an attempt
was made to inappropriately copy an ACL. Now, GAM will not attempt to copy ACLs unless they are appropriate.
When `showpermissionmessages` is specified GAM will display messages about ACLs not copied, ACLs that were copied
and any remaining copy errors.

When copying an ACL that references a non Google account, an error is generated unless an email is sent to the account;
by default, no email notifications are sent. The `sendemailifrequired` options instructs GAM to send an email notification in this case.

When moving a folder you can use the `retainsourcefolders` option to cause GAM to retain the top folder and its sub folders while moving the sub files to the target folder; this is typically used with `duplicatefolders merge` 

Use the `summary` option to get a two-line summary of the actions performed.

Moving a Drive folder to a Shared Drive is not directly supported by the API; GAM has to make a copy of the folder on the Shared Drive and
recursively adjust the files/folders within it to point to the new parent folder. Once the original folder is emptied, it is deleted unless `retainsourcefolders` is specified.

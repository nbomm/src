# Users - Drive - Permissions
- [API documentation](#api-documentation)
- [Query documentation](#query-documentation)
- [Collections of Users](Collections-of-Users)
- [Permission Matches](Permission-Matches)
- [Definitions](#definitions)
- [Manage file permissions/sharing](#manage-file-permissionssharing)
- [Display file permissions/sharing](#display-file-permissionssharing)
- [Delete all ACLs except owner from a file](#delete-all-acls-except-owner-from-a-file)
## API documentation
* https://developers.google.com/drive/api/v3/reference/permissions
* https://developers.google.com/drive/api/v3/ref-single-parent

## Query documentation
* https://developers.google.com/drive/api/v3/search-files
* https://developers.google.com/drive/api/v3/ref-search-terms

## Definitions
See [Drive File Selection](Drive-File-Selection) for symbols not listed here, such as `<DriveFileEntity>`
```
<DomainName> ::= <String>(.<String>)+
<EmailAddress> ::= <String>@<DomainName>
<UniqueID> ::= uid:<String>
<UserItem> ::= <EmailAddress>|<UniqueID>|<String>

<DrivePermissionsFieldName> ::=
        additionalroles|
        allowfilediscovery|
        basicpermissions|
        deleted|
        displayname|
        domain|
        emailaddress|
        expirationdate|
        expirationtime|
        id|
        name|
        pendingowner|
        permissiondetails|
        photolink|
        role|
        type|
        view|
        withlink
<DrivePermissionsFieldNameList> ::= "<DrivePermissionsFieldName>(,<DrivePermissionsFieldName>)*"

```
`basicpermissions` is equivalent to:
```
permissions.allowFileDiscovery,
permissions.deleted,
permissions.domain,
permissions.emailAddress,
permissions.expirationTime,
permissions.id,
permissions.role,
permissions.type
```
In particular, this omits these fields:
```
permissions.displayName,
permissions.permissionDetails,
permissions.photoLink,
permissions.teamDrivePermissionDetails
```
This allows you to select the essential permission fields without enumerating them. Of course,
you can specify `permissions` to get all of the fields, enumerate the specific fields you want or
specify `basicpermissions` and additional permission fields, e.g., `permissions.displayName`.

```
<DriveOrderByFieldName> ::=
        createddate|createdtime|
        folder|
        modifiedbyme|modifiedbymedate|modifiedbymetime|modifiedbyuser|
        modifieddate|modifiedtime|
        name|
        name_natural|
        quotabytesused|quotaused|
        recency|
        sharedwithmedate|sharedwithmetime|
        starred|
        title|
        title_natural|
        viewedbymedate|viewedbymetime
<DriveFileACLRole> ::=
        commenter|
        contentmanager|fileorganizer|
        contributor|editor|writer|
        manager|organizer|owner|
        reader|viewer
<DriveFileACLRoleList> ::= "<DriveFileACLRole>(,<DriveFileACLRole>)*"
<DriveFileACLType> ::= anyone|domain|group|user
<DriveFilePermission> ::=
        anyone|anyonewithlink|
        user:<EmailAddress>|group:<EmailAddress>|
        domain:<DomainName>|domainwithlink:<DomainName>;<DriveFileACLRole>
<DriveFilePermissionID> ::=
        anyone|anyonewithlink|id:<String>
<DriveFilePermissionIDorEmail> ::=
        <DriveFilePermissionID>|<EmailAddress>
<DriveFilePermissionList> ::=
        "<DriveFilePermission>(,<DriveFilePermission)*"
<DriveFilePermissionIDList> ::=
        "<DriveFilePermissionID>(,<DriveFilePermissionID>)*"
<DriveFilePermissionEntity> ::=
         <DriveFilePermissionList> |
         (json [charset <Charset>] <JSONData>)|(json file <FileName> [charset <Charset>]) |
         <FileSelector> |
         <CSVFileSelector> |
         <CSVkmdSelector> |
         <CSVDataSelector>
<DriveFilePermissionIDEntity> ::=
         <DriveFilePermissionIDList> |
         (json [charset <Charset>] <JSONData>)|(json file <FileName> [charset <Charset>]) |
         <FileSelector> |
         <CSVFileSelector> |
         <CSVkmdSelector> |
         <CSVDataSelector>
```
## Manage file permissions/sharing
### Process single ACLs.
### Create
```
gam <UserTypeEntity> create|add drivefileacl <DriveFileEntity>
        anyone|(user <UserItem>)|(group <GroupItem>)|(domain <DomainName>)
        (role <DriveFileACLRole>) [withlink|(allowfilediscovery|discoverable [<Boolean>])]
        [enforcesingleparent <Boolean>] [movetonewownersroot <Boolean>]
        [expiration <Time>] [sendemail] [emailmessage <String>]
        [showtitles] [nodetails|(csv [todrive <ToDriveAttribute>*] [formatjson [quotechar <Character>]])]
```
From the Google Drive API documentation.
* `enforcesingleparent` - This parameter only takes effect if the item is not in a shared drive.
  * `false` - Do not opt in to API behavior that aims for all items to have exactly one parent. Default.
  * `true` - Opt in to API behavior that aims for all items to have exactly one parent.
* `movetonewownersroot` - This parameter only takes effect if the item is not in a shared drive and the request is attempting to transfer the ownership of the item.
  * `false` - Default
    * `enforceSingleParent=false` - Existing parents are not changed; however, the file will be added to the new owner's My Drive root folder, unless it is already in the new owner's My Drive.
    * `enforceSingleParent=true` -  Parents are not changed. The file is an orphan for the new owner.
  * `true` - Optional
    * `enforceSingleParent=false` - The item is moved to the new owner's My Drive root folder and all prior parents removed.
    * `enforceSingleParent=true` - The item is moved to the new owner's My Drive root folder and all prior parents removed.

By default, the file ID is displayed in the output; to see the file name, use the `showtitles`
option; this requires an additional API call per file.

By default, when an ACL is created, GAM outputs details of the ACL as indented keywords and values.
* `nodetails` - Suppress the details output.
* `csv [todrive <ToDriveAttribute>*] [formatjson [quotechar <Character>]]` - Output the details in CSV format.

### Update
```
gam <UserTypeEntity> update drivefileacl <DriveFileEntity> <DriveFilePermissionIDorEmail>
        (role <DriveFileACLRole>) [expiration <Time>] [removeexpiration [<Boolean>]]
        [showtitles] [nodetails|(csv [todrive <ToDriveAttribute>*] [formatjson [quotechar <Character>]])]
```
There is no change of parents when a new user is updated to be a file's owner.

By default, the file ID is displayed in the output; to see the file name, use the `showtitles`
option; this requires an additional API call per file.

By default, when an ACL is updated, GAM outputs details of the ACL as indented keywords and values.
* `nodetails` - Suppress the details output.
* `csv [todrive <ToDriveAttribute>*] [formatjson [quotechar <Character>]]` - Output the details in CSV format.

### Delete
```
gam <UserTypeEntity> delete|del drivefileacl <DriveFileEntity> <DriveFilePermissionIDorEmail>
        [showtitles]
```
By default, the file ID is displayed in the output; to see the file name, use the `showtitles`
option; this requires an additional API call per file.

### Process multiple ACLs.
### Create
```
gam <UserTypeEntity> create|add permissions <DriveFileEntity> <DriveFilePermissionEntity>
        [expiration <Time>] [sendemail] [emailmessage <String>]
        [enforcesingleparent <Boolean>] [movetonewownersroot <Boolean>]
        <PermissionMatch>* [<PermissionMatchAction>]
```
From the Google Drive API documentation.
* `enforcesingleparent` - This parameter only takes effect if the item is not in a shared drive.
  * `false` - Do not opt in to API behavior that aims for all items to have exactly one parent. Default.
  * `true` - Opt in to API behavior that aims for all items to have exactly one parent.
* `movetonewownersroot` - This parameter only takes effect if the item is not in a shared drive and the request is attempting to transfer the ownership of the item.
  * `false` - Default
    * `enforceSingleParent=true` -  Parents are not changed. The file is an orphan for the new owner.
    * `enforceSingleParent=false` - Existing parents are not changed; however, the file will be added to the new owner's My Drive root folder, unless it is already in the new owner's My Drive.
  * `true` - Optional
    * `enforceSingleParent=false` - The item is moved to the new owner's My Drive root folder and all prior parents removed.
    * `enforceSingleParent=true` - The item is moved to the new owner's My Drive root folder and all prior parents removed.

Permission matching only applies when the `(json [charset <Charset>] <JSONData>)|(json file <FileName> [charset <Charset>])`
variant of `<DriveFilePermissionEntity>` and `<DriveFilePermissionIDEntity>` is used.

When adding permissions from JSON data, there is a default match: `pm not role owner em` that disables ownership changes.
If you want to process all permissions, enter `pm em` to clear the default match.

When adding permissions from JSON data, permissions with `deleted` true are never processed.

### Delete
```
gam <UserTypeEntity> delete permissions <DriveFileEntity> <DriveFilePermissionIDEntity>
        <PermissionMatch>* [<PermissionMatchAction>]
```
When deleting permissions from JSON data, permissions with role `owner` true are never processed.

## Display file permissions/sharing
```
gam <UserTypeEntity> info drivefileacl <DriveFileEntity> <DriveFilePermissionIDorEmail>
        [showtitles] [formatjson]
gam <UserTypeEntity> show drivefileacls <DriveFileEntity>
        (role|roles <DriveFileACLRoleList>)*
        <PermissionMatch>* [<PermissionMatchAction>] [pmselect]
        [includepermissionsforview published]
        [oneitemperrow] [<DrivePermissionsFieldName>*|(fields <DrivePermissionsFieldNameList>)]
        [showtitles|(addtitle <String>)]]
        (orderby <DriveFileOrderByFieldName> [ascending|descending])*
        [formatjson]
gam <UserTypeEntity> print drivefileacls <DriveFileEntity> [todrive <ToDriveAttributes>*]
        (role|roles <DriveFileACLRoleList>)*
        <PermissionMatch>* [<PermissionMatchAction>] [pmselect]
        [includepermissionsforview published]
        [oneitemperrow] [<DrivePermissionsFieldName>*|(fields <DrivePermissionsFieldNameList>)]
        [showtitles|(addtitle <String>)]]
        (orderby <DriveFileOrderByFieldName> [ascending|descending])*
        [formatjson [quotechar <Character>]]
```
By default, the file ID is displayed in the output; to see the file name, use the `showtitles`
option; this requires an additional API call per file. If you are reading the file IDs from a
CSV file that also includes the file name, you can use the `addtitle` option to supply the file name.

By default, all files specified are displayed; use the following option to select a subset of those files.
* `<PermissionMatch>* [<PermissionMatchAction>] pmselect` - Use permission matching to select files

By default, all ACLS are displayed; use the following option to select a subset of the ACLS to display.
* `role|roles <DriveFileACLRoleList>` - Display ACLs for the specified roles only.
* `<PermissionMatch>* [<PermissionMatchAction>]` - Use permission matching to display a subset of the ACLs for each file; this only applies when `pmselect` is not specified


With `print drivefileacls` or `show drivefileacls formatjson`, the ACLs selected for display are all output on one row/line as a repeating item with the matching file id.
When `oneitemperrow` is specified, each ACL is output on a separate row/line with the matching file id. This simplifies processing the CSV file with subsequent Gam commands.

By default, when writing CSV files, Gam uses a quote character of double quote `"`. The quote character is used to enclose columns that contain
the quote character itself, the column delimiter (comma by default) and new-line characters. Any quote characters within the column are doubled.
When using the `formatjson` option, double quotes are used extensively in the data resulting in hard to read/process output.
The `quotechar <Character>` option allows you to choose an alternate quote character, single quote for instance, that makes for readable/processable output.
`quotechar` defaults to `gam.cfg/csv_output_quote_char`.

For example, to get the ACLs for your Team Drives with the Team Drive name included in the output:
```
gam redirect csv ./TeamDrives.csv print teamdrives
gam redirect csv ./TeamDriveACLs.csv multiprocess csv ./TeamDrives.csv gam print drivefileacls teamdriveid "~id" addtitle "~name" fields id,domain,emailaddress,role,type,deleted
```

## Delete all ACLs except owner from a file
Get the current ACLs.
```
gam redirect csv ./Permissions.csv user <UserItem> print drivefileacls <DriveFileID> oneitemperrow
```
Inspect Permissions.csv, verify that you want to proceed.
```
gam config csv_input_row_drop_filter "permission.role:regex:(owner)|(organizer)" csv ./Permissions.csv gam user "~Owner" delete drivefileacl "~id" "id:~~permission.id~~"
```

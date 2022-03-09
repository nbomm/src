# Users - Drive Files Display 
- [API documentation](#api-documentation)
- [Query documentation](#query-documentation)
- [Python Regular Expressions](Python-Regular-Expressions) Match function
- [Collections of Users](Collections-of-Users)
- [Permission Matches](Permission-Matches)
- [Definitions](#definitions)
- [Display file information](#display-file-information)
- [Display file paths](#display-file-paths)
- [Select files for Display file counts, list, tree](#select-files-for-Display-file-counts-list-tree)
  - [File selection definitions](#file-selection-definitions)
  - [File selection defaults](#file-selection-defaults)
  - [File selection by query](#file-selection-by-query)
  - [File selection by ownership](#file-selection-by-ownership)
  - [File selection by MIME type](#file-selection-by-mime-type)
  - [File selection by file size](#file-selection-by-file-size)
  - [File selection by file name pattern matching](#file-selection-by-file-name-pattern-matching)
  - [File selection by permission matching](#file-selection-by-permission-matching)
  - [File selection to exclude items in the trash](#file-selection-to-exclude-items-in-the-trash)
- [Display file counts](#display-file-counts)
  - [File selection of Shared Drive for Display file counts](#file-selection-of-shared-drive-for-display-file-counts)
- [Display file tree](#display-file-tree)
  - [File selection starting point for Display file tree](#file-selection-starting-point-for-display-file-tree)
- [Display file list](#display-file-list)
  - [File selection by name and entity shortcuts for Display file list](#file-selection-by-name-and-entity-shortcuts-for-display-file-list)
  - [File selection starting point for Display file list](#file-selection-starting-point-for-display-file-list)
  - [Handle empty file lists](#handle-empty-file-lists)

## API documentation
* https://developers.google.com/drive/api/v3/reference/files

## Query documentation
* https://developers.google.com/drive/api/v3/search-files
* https://developers.google.com/drive/api/v3/ref-search-terms

## Definitions
See [Drive File Selection](Drive-File-Selection) for symbols not listed here, such as `<DriveFileEntity>`
```
<CorporaAttribute> ::=
        alldrives |
        domain |
        onlyteamdrives |
        user
<DomainName> ::= <String>(.<String>)+
<EmailAddress> ::= <String>@<DomainName>
<UniqueID> ::= uid:<String>
<Time> ::=
        <Year>-<Month>-<Day>(<Space>|T)<Hour>:<Minute>:<Second>[.<MilliSeconds>](Z|(+|-(<Hour>:<Minute>))) |
        (+|-)<Number>(m|h|d|w|y) |
        never|
        now|today

<MimeTypeShortcut> ::=
        gdoc|gdocument|
        gdrawing|
        gfile|
        gfolder|gdirectory|
        gform|
        gfusion|
        gmap|
        gpresentation|
        gscript|
        gsheet|gspreadsheet|
        gshortcut|
        g3pshortcut|
        gsite|
        gsheet|gspreadsheet
<MimeTypeName> ::= application|audio|font|image|message|model|multipart|text|video
<MimeType> ::= <MimeTypeShortcut>|(<MimeTypeName>/<String>)
<MimeTypeList> ::= "<MimeType>(,<MimeType>)*"
```
```
<DriveCapabilitiesSubfieldName> ::=
        canaddchildren|
        canaddmydriveparent|
        canchangecopyrequireswriterpermission|
        canchangeviewerscancopycontent|
        cancomment|
        cancopy|
        candelete|
        candownload|
        canedit|
        canlistchildren|
        canmodifycontent|
        canmovechildrenoutofdrive|
        canmovechildrenoutofteamdrive|
        canmovechildrenwithindrive|
        canmovechildrenwithinteamdrive|
        canmoveitemintoteamdrive|
        canmoveitemoutofdrive|
        canmoveitemoutofteamdrive|
        canmoveitemwithindrive|
        canmoveitemwithinteamdrive|
        canmoveteamdriveitem|
        canreaddrive|
        canreadrevisions|
        canreadteamdrive|
        canremovechildren|
        canremovemydriveparent|
        canrename|
        canshare|
        cantrash|
        cantrashchildren|
        canuntrash

<DriveLabelsSubfieldName> ::=
        labels.modified|        # modifiedByMe
        labels.restricted|      # copyRequiresWriterPermission
        labels.starred|         # starred
        labels.trashed|         # trashed
        labels.viewed           # viewedByMe

<DriveOwnersSubfieldName> ::=
        owners.displayname|
        owners.emailaddress|
        owners.isauthenticateduser|
        owners.me|
        owners.permissionid|
        owners.photolink|
        owners.picture

<DriveParentsSubfieldName> ::=
        parents.id|
        parents.isroot

<DrivePermissionsSubfieldName> ::=
        permissions.additionalroles|
        permissions.allowfilediscovery|
        permissions.deleted|
        permissions.permissiondetails|
        permissions.displayname|
        permissions.domain|
        permissions.emailaddress|
        permissions.expirationdate|
        permissions.expirationtime|
        permissions.id|
        permissions.name|
        permissions.photolink|
        permissions.role|
        permissions.type|
        permissions.withlink

<DriveLastModifyingUserSubfieldName> ::=
        lastmodifyinguser.displayname|
        lastmodifyinguser.emailaddress|
        lastmodifyinguser.isauthenticateduser|
        lastmodifyinguser.me|
        lastmodifyinguser.name|
        lastmodifyinguser.permissionid|
        lastmodifyinguser.photolink|
        lastmodifyinguser.picture

<DriveSharingUserSubfieldName> ::=
        sharinguser.displayname|
        sharinguser.emailaddress|
        sharinguser.isauthenticateduser|
        sharinguser.me|
        sharinguser.name|
        sharinguser.permissionid|
        sharinguser.photolink|
        sharinguser.picture

<DriveTrashingUserSubfieldName> ::=
        trashinguser.displayname|
        trashinguser.emailaddress|
        trashinguser.isauthenticateduser|
        trashinguser.me|
        trashinguser.name|
        trashinguser.permissionid|
        trashinguser.photolink|
        trashinguser.picture

<DriveShortcutDetailsSubfieldName> ::=
        shortcutdetails.targetid|
        shortcutdetails.targetmimetype
        shortcutdetails.resourcekey
```
```
<DriveFieldName> ::=
        alternatelink|
        appdatacontents|
        appproperties|
        basicpermissions|
        cancomment|
        canreadrevisions|
        capabilities|
        <DriveCapabilitiesSubfieldName>|
        contenthints|
        copyable|
        copyrequireswriterpermission|
        createddate|createdtime|
        description|
        driveid|
        drivename|
        editable|
        explicitlytrashed|
        exportlinks|
        fileextension|
        filesize|
        foldercolorrgb|
        fullfileextension|
        hasaugmentedpermissions|
        hasthumbnail|
        headrevisionid|
        iconlink|
        id|
        imagemediametadata|
        isappauthorized|
        labels|
        <DriveLabelsSubfieldName>|
        lastmodifyinguser|
        <DriveLastModifyingUserSubfieldName>|
        lastmodifyingusername|
        lastviewedbyme|lastviewedbymedate|lastviewedbymetime|lastviewedbyuser|
        linksharemetadata|
        md5|md5checksum|md5sum|
        mime|mimetype|
        modifiedbyme|modifiedbymedate|modifiedbymetime|modifiedbyuser|
        modifieddate|modifiedtime|
        name|
        originalfilename|
        ownedbyme|
        ownernames|
        owners|
        <DriveOwnersSubfieldName>|
        parents|
        <DriveParentsSubfieldName>|
        permissions|
        <DrivePermissionsSubfieldName>|
        permissionids|
        properties|
        quotabytesused|quotaused|
        resourcekey|
        restricted|
        shareable|
        shared|
        sharedwithmedate|sharedwithmetime|
        sharinguser|
        <DriveSharingUserSubfieldName>|
        shortcutdetails|
        <DriveShortcutDetailsSubfieldName>|
        size|
        spaces|
        starred|
        teamdriveid|
        teamdrivename|
        thumbnaillink|
        thumbnailversion|
        title|
        trashed|
        trasheddate|trashedtime|
        trashinguser|
        <DriveTrashingUserSubfieldName>|
        userpermission|
        version|
        videomediametadata|
        viewed|
        viewedbymedate|viewedbymetime|
        viewerscancopycontent|
        webcontentlink|
        webviewlink|
        writerscanshare
<DriveFieldNameList> ::= "<DriveFieldName>(,<DriveFieldName>)*"
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
<<DriveOrderByFieldName> ::=
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
```
## Display file information
Display file details in indented keyword: value format.
```
gam <UserTypeEntity> show fileinfo <DriveFileEntity>
        [filepath] [allfields|<DriveFieldName>*|(fields <DriveFieldNameList>)]
        (orderby <DriveFileOrderByFieldName> [ascending|descending])*
        [showparentsidsaslist] [showshareddrivepermissions]
        [showdrivename|showshareddrivename|showteamdrivename]
        [stripcrsfromname]
        [formatjson]
```
When `allfields` is specified (or no fields are specified), use `showdrivename` to display Shared(Team) Drive names.
An additional API call is required to get each Shared(Team) Drive name; the names are cached so there is only one additional
API call per Shared(Team) Drive.

When `allfields` is specified (or no fields are specified), use `showshareddrivepermissions` to display permissions
for `<DriveFileEntity>` when it is a shared drive file/folder. In this case, the Drive API returns the permission IDs
but not the permissions themselves so GAM makes an additional API call to get the permissions.

By default, when file parents are displayed, they are displayed in this form:
```
  parents:
    id: <DriveFileID>
      isRoot: <Boolean>
    id: <DriveFileID>
      isRoot: <Boolean>
    ...
```
The `showparentsidsaslist` option changes the output to this form:
```
  parentsIds: <DriveFileID> <DriveFileID> ...
```
There is no `isRoot` information displayed.

The `stripcrsfromname` option strips nulls, carriage returns and linefeeds from drive file names.
This option is special purpose and will not generally be used.

By default, Gam displays the information as an indented list of keys and values.
* `formatjson` - Display the fields in JSON format.

## Display file paths
```
gam <UserTypeEntity> show filepath <DriveFileEntity>
        (orderby <DriveFileOrderByFieldName> [ascending|descending])*
gam <UserTypeEntity> print filepath <DriveFileEntity> [todrive <ToDriveAttribute>*]
        [oneitemperrow] (orderby <DriveFileOrderByFieldName> [ascending|descending])*
```
By default, when printing file paths, all paths for a file are displayed on the same row; use `oneitemperrow` to
have each file path displayed on a separate row.

## Select files for Display file counts, list, tree
Most GAM commands that deal with files require a `<DriveFileEntity>` to be specified; the command
then processes those files. The `filecounts`, `filelist` and `filetree` commands don't process files, they just list them.
They offer more powerful methods to select the files to be displayed.

## File selection definitions
See: [Drive File Selection](Drive-File-Selection) for details of `<DriveFileNameEntity>`, `<DriveFileQueryShortcut>` and `<DriveFileEntity>`.
```
<DriveFileNameEntity> ::=
        (anyname <DriveFileName>) | (anyname:<DriveFileName>) |
        (anydrivefilename <DriveFileName>) | (anydrivefilename:<DriveFileName>) |
        (name <DriveFileName>) | (name:<DriveFileName>) |
        (drivefilename <DriveFileName>) | (drivefilename:<DriveFileName>) |
        (othername <DriveFileName>) | (othername:<DriveFileName>) |
        (otherdrivefilename <DriveFileName>) | (otherdrivefilename:<DriveFileName>)

<DriveFileQueryShortcut> ::=
        all_files |
        all_folders |
        all_google_files |
        all_non_google_files |
        all_shortcuts |
        all_3p_shortcuts |
        all_items |
        my_files |
        my_folders |
        my_google_files |
        my_non_google_files |
        my_shortcuts |
        my_3p_shortcuts |
        my_items |
        others_files |
        others_folders |
        others_google_files |
        others_non_google_files |
        others_shortcuts |
        others_3p_shortcuts |
        others_items |
        writable_files

<DriveFileEntity> ::=
        <DriveFileIDEntity> |
        <DriveFileNameEntity> |
        <DriveFileQueryEntity> |
        <DriveFileQueryShortcut> |
        root|mydrive |
        <SharedDriveIDEntity> [<SharedDriveFileQueryShortcut>] |
        <SharedDriveNameEntity> [<SharedDriveFileQueryShortcut>] |
        <SharedDriveFileNameEntity> |
        <SharedDriveFileQueryEntity> |
        <FileSelector> | <CSVFileSelector> | <CSVkmdSelector> | <CSVSubkeySelector>) | <CSVDataSelector>)
```

## File selection defaults
By default, file selection starts with a query of "'me' in owners".
The sections below detail other methiods for selecting files.

## File selection by query
Select a subset of files by query.

This option is not available for `print|show filetree`.
```
((query <QueryDriveFile>) | (fullquery <QueryDriveFile>) | <DriveFileQueryShortcut>) (querytime<String> <Time>)*
```
* `query "xxx"` - ` and xxx` is appended to the current query; you can repeat the query argument to build up a longer query.
* `fullquery "xxx"` - The query is set to `xxx` eliminating the initial `'me' in owners`.
* `<DriveFileQueryShortcut>` - Predefined queries

Use the `querytime<String> <Time>` option to allow times, usually relative, to be substituted into the `query <QueryDriveFile>` option.
The `querytime<String> <Time>` value replaces the string `#querytime<String>#` in any queries.
The characters following `querytime` can be any combination of lowercase letters and numbers. This is most useful in scripts
where you can specify a relative date without having to change the script.

For example, query for files last modified me than 5 years ago:
```
querytime5years -5y query "modifiedTime<'#querytime5years#'"
```

## File selection by corpora
Select files by corpora.

This option is not available for `print|show filetree`.
```
corpora <CorporaAttribute>
```
* `corpora alldrives` - Selects files on Shared Drives and files owned by or shared to the user.
* `corpora domain` - Selects files shared to the user's domain.
* `corpora onlyteamdrives` - Selects files on Shared Drives.
* `corpora user` - Selects files owned by or shared to the user.

## File selection by ownership
By default, files owned by the user are selected. These options update the current query with the desired ownership.
```
anyowner|(showownedby any|me|others)

```
* `showownedby me` - Select files owned by the user; this is the default
* `showownedby any` or `anyowner` - Select files accessible by the user
* `showownedby others` - Select files not owned by the user

## File selection by MIME type
By default, all types of files and folders are selected. You can specify a list of MIME types to display or a list of MIME types to suppress.
This option updates the current query.
```
showmimetype [not] <MimeTypeList>
```
* `showmimetype <MimeTypeList>` - Select files and folders with the specified MIME types
* `showmimetype not <MimeTypeList>` - Select files and folders with MIME types other than those specified

## File selection by file size
This option allows you to limit the selection to files with binary content of size >= `<Integer>`.
This option would typically be used with `shomimetype` to select files with binary content. This
selection is performed by GAM, not the API.
```
minimumfilesize <Integer>
```

## File selection by file name pattern matching
This option allows you to limit the display to files whose name matches `<RegularExpression>`.
The Drive API supports basic file name selection via query; this selection by pattern matching
is performed by GAM. You could use a query to do broad file name matching and then fine tune it with
`filenamematchpattern`.
```
filenamematchpattern <RegularExpression>
```

## File selection by permission matching
See: [Permission Matches](Permission-Matches)

## File selection to exclude items in the trash
This option excludes items in the trash from being selected.
```
excludetrashed
```

## Display file counts
Print or show file counts by MIME type and/or file name.
```
gam <UserTypeEntity> print filecounts [todrive <ToDriveAttribute>*]
        [((query <QueryDriveFile>) | (fullquery <QueryDriveFile>) | <DriveFileQueryShortcut>)
            (querytime<String> <Time>)*]
        [corpora <CorporaAttribute>]
        [select <SharedDriveEntity>]
        [anyowner|(showownedby any|me|others)]
        [showmimetype [not] <MimeTypeList>] [minimumfilesize <Integer>]
        [filenamematchpattern <RegularExpression>]
        <PermissionMatch>* [<PermissionMatchMode>] [<PermissionMatchAction>]
        [excludetrashed]
        [summary none|only|plus] [summaryuser <String>] [showsize]
gam <UserTypeEntity> show filecounts
        [((query <QueryDriveFile>) | (fullquery <QueryDriveFile>) | <DriveFileQueryShortcut>)
            (querytime<String> <Time>)*]
        [corpora <CorporaAttribute>]
        [select <SharedDriveEntity>]
        [anyowner|(showownedby any|me|others)]
        [showmimetype [not] <MimeTypeList>] [minimumfilesize <Integer>]
        [filenamematchpattern <RegularExpression>]
        <PermissionMatch>* [<PermissionMatchMode>] [<PermissionMatchAction>]
        [excludetrashed]
        [summary none|only|plus] [summaryuser <String>] [showsize]
```

By default, print filecounts displays counts of all files owned by the specified `<UserTypeEntity>`.

The `showsize` option displays the total size (in bytes) of the files counted.

See [Select files for Display file counts, list, tree](#select-files-for-Display-file-counts-list-tree)

## File selection of Shared Drive for Display file counts
You can limit the selection for files on a specific Shared drive.
Any query will be applied to the Shared drive.
```
select <SharedDriveEntity>
```
Use the `excludetrashed` option to suppress counting files in the trash.

By default, file counts for individual users are displayed; the `summary` option offers alternatives
that can display a summarization of file counts across all users specified in the command.
* `none` - No summary is displayed; this is the default
* `only` - Only the summary is displayed, no individual user file counts are displayed
* `plus` - The summary is displayed in addition to the individual user file counts

The `summaryuser <String>` option  replaces the default summary user `Summary` with `<String>`.

### Example
Get file count summaries by OU; top level selector is ou, sub level selectors are ou_and_children
```
gam redirect csv ./TopLevelOUs.csv print ous showparent toplevelonly parentselector ou childselector ou_and_children fields orgunitpath
gam redirect csv ./FileCounts.csv multiprocess csv ./TopLevelOUs.csv gam "~orgUnitSelector" "~orgUnitPath" print filecounts excludetrashed summary only summaryuser "~orgUnitPath"
```

## Display file tree
Display a list of file/folder names indented to show structure.
```
<FileTreeFieldName> ::=
        explicitlytrashed|
        filesize|
        id|
        mimetype|
        owners|
        parents|
        size|
        trashed
<FileTreeFieldNameList> ::= "<FileTreeFieldName>(,<FileTreeFieldName>)*"

gam <UserTypeEntity> print filetree [todrive <ToDriveAttribute>*]
        [select <DriveFileEntity> [selectsubquery <QueryDriveFile>]
            [depth <Number>]]
        [anyowner|(showownedby any|me|others)]
        [showmimetype [not] <MimeTypeList>] [minimumfilesize <Integer>]
        [filenamematchpattern <RegularExpression>]
        <PermissionMatch>* [<PermissionMatchMode>] [<PermissionMatchAction>]
        [excludetrashed]
        [fields <FileTreeFieldNameList>]
        (orderby <DriveFileOrderByFieldName> [ascending|descending])* [delimiter <Character>]
        [noindent] [stripcrsfromname]
gam <UserTypeEntity> show filetree
        [select <DriveFileEntity> [selectsubquery <QueryDriveFile>]
            [depth <Number>]]
        [anyowner|(showownedby any|me|others)]
        [showmimetype [not] <MimeTypeList>] [minimumfilesize <Integer>]
        [filenamematchpattern <RegularExpression>]
        <PermissionMatch>* [<PermissionMatchMode>] [<PermissionMatchAction>]
        [excludetrashed]
        [fields <FileTreeFieldNameList>]
        (orderby <DriveFileOrderByFieldName> [ascending|descending])* [delimiter <Character>]
        [stripcrsfromname]
```
By default, the file tree starting at the root and all orphans are shown.

See [Select files for Display file counts, list, tree](#select-files-for-Display-file-counts-list-tree)

## File selection starting point for Display file tree
You can specify a specific folder from which to select files.
```
        [select <DriveFileEntity> [selectsubquery <QueryDriveFile>]
            [depth <Number>]]
```
* `select <DriveFileEntity>` - All files in the selected folder and below are shown.
* `selectsubquery <QueryDriveFile>` - Only the files in the selected folder that match the query are shown.

The `depth <Number>` argument controls which files or folders within a selected folder are listed.
* `depth -1` - all files and folders in the selected folder and below are listed; this is the default.
* `depth 0` - the files or folders within a selected folder are listed, no descendants are listed.
* `depth N` - the files and folders within the selected folder and those files and folders N levels below the selected folder are listed.

## Choose what fields to display
By default, only the file/folder name is displayed; use the following options to display additional fields.
* `fields <FileTreeFieldNameList>` - Display the selected fields.
* `delimiter <Character>` - If any field has multiple values, separate them with `<Character>`; the default value is `csv_output_field_delimiter` from `gam.cfg`.

For fields `explicitlytrashed` and `trashed`, only True values are shown with `show filetree`; True and False values are shown with `print filetree`.

For `print filetree`, use the `noindent` option to eliminate the indentation in front of the file name.

The `stripcrsfromname` option strips nulls, carriage returns and linefeeds from drive file names.
This option is special purpose and will not generally be used.

### Examples
Show full file tree including the file id and mimetype:
```
gam user testuser show filetree fields id,mimetype
```
Show file tree starting at the folder named "Middle Folder" and 2 levels deeper
```
gam user testuser show filetree select drivefilename "Middle Folder" depth 2
```
## Display file list
Display a list of file/folder details in CSV format.
```
gam <UserTypeEntity> print|show filelist [todrive <ToDriveAttribute>*]
        [((query <QueryDriveFile>) | (fullquery <QueryDriveFile>) | <DriveFileQueryShortcut>)
            (querytime<String> <Time>)*]
        [choose <DriveFileNameEntity>|<DriveFileEntityShortcut>]
        [corpora <CorporaAttribute>]
        [select <DriveFileEntity> [selectsubquery <QueryDriveFile>]
            [norecursion|(depth <Number>)] [showparent]]
        [anyowner|(showownedby any|me|others)]
        [showmimetype [not] <MimeTypeList>] [minimumfilesize <Integer>]
        [filenamematchpattern <RegularExpression>]
        <PermissionMatch>* [<PermissionMatchMode>] [<PermissionMatchAction>]
        [excludetrashed]
        [maxfiles <Integer>] [nodataheaders <String>]
        [countsonly [summary none|only|plus] [summaryuser <String>] [showsource] [showsize]] [countsrowfilter]
        [filepath|fullpath [addpathstojson] [showdepth]] [buildtree]
        [allfields|<DriveFieldName>*|(fields <DriveFieldNameList>)]
        [showdrivename] [showparentsidsaslist] [showpermissionslast] [showshareddrivepermissions]
        (orderby <DriveFileOrderByFieldName> [ascending|descending])* [delimiter <Character>]
        [stripcrsfromname]
        [formatjson [quotechar <Character>]]
```
By default, `print filelist` displays all files owned by the specified `<UserTypeEntity>`.

When `allfields` is specified (or no fields are specified), use `showshareddrivepermissions` to display permissions
when shared drives are queried/selected. In this case, the Drive API returns the permission IDs
but not the permissions themselves so GAM makes an additional API call per file to get the permissions.

See [Select files for Display file counts, list, tree](#select-files-for-Display-file-counts-list-tree)

## File selection by name and entity shortcuts for Display file list
Select a subset of files by pre-defined queries.

These options define a complete query, eliminating the initial "`me` in owners".
The `<DriveFileEntityShortcut>` option was added in version 5.04.00.
```
<DriveFileEntityShortcut> ::=
        alldrives |
        mydrive_any |
        mydrive_me |
        mydrive_others |
        onlyteamdrives|onlyshareddrives |
        orphans |
        ownedby_any |
        ownedby_me |
        ownedby_others |
        root|mydrive |
        rootwithorphans|mydrivewithorphans |
        sharedwithme |
        sharedwithme_mydrive |
        sharedwithme_notmydrive
```
Definition of `<DriveFileEntityShortcut>`:
* `alldrives` - All files accessible by the user; `My Drive` including orphans, `Shared with me`, `Shared drives`
* `mydrive` - All files in `My Drive` excluding orphans; ownership controlled by `showownedby`
* `mydrive_any` - All files in `My Drive` including orphans owned by anyone
* `mydrive_me` - All files in `My Drive` including orphans owned by the user; `'me' in owners`
* `mydrive_others` - All files in `My Drive` excluding orphans owned by others; `not 'me' in owners`
* `mydrive_with_orphans` - All files in `My Drive` including orphans; ownership controlled by `showownedby`
* `onlyshareddrives` - All files in `Shared drives` accessible by the user
* `onlyteamdrives` - All files in `Shared drives` accessible by the user
* `orphans` - All files in `My Drive` whose parentage doesn't lead to `My Drive`; `'me' in owners`
* `ownedby_any` - All files in `My Drive` including orphans and `Shared with me` owned by anyone
* `ownedby_me` - All files in `My Drive` including orphans owned by the user; `'me' in owners`
* `ownedby_others` - All files in `My Drive` excluding orphans and `Shared with me` owned by others; `not 'me' in owners`
* `root` - All files in `My Drive` excluding orphans; ownership controlled by `showownedby`
* `root_with_orphans` - All files in `My Drive` including orphans; ownership controlled by `showownedby`
* `sharedwithme` - All files in `My Drive` and `Shared with me` owned by others; `not 'me' in owners`
* `sharedwithme_mydrive` - All files in `My Drive` owned by others; `not 'me' in owners`
* `sharedwithme_notmydrive` - All files in `Shared with me` but not in `My Drive`; `not 'me' in owners`

```
choose <DriveFileNameEntity>|<DriveFileEntityShortcut>
```

## File selection starting point for Display file list
You can specify a specific folder from which to select files.
```
select <DriveFileEntity> [selectsubquery <QueryDriveFile>]
    [norecursion|(depth <Number>)] [showparent]
```
These options can be used instead of the query options to select a specific folder to display.
* `select <DriveFileEntity>` - All files in the selected folder and below are shown.
* `selectsubquery <QueryDriveFile>` - Only the files in the selected folder that match the query are shown.

The `norecursion` and `depth <Number>` arguments control which files or folders within a selected folder are listed.
* `norecursion` - no files and folders in the selected folder and below are listed
* `depth -1` - all files and folders in the selected folder and below are listed; this is the default.
* `depth 0` - the files or folders within the selected folder are listed, no descendants are listed.
* `depth N` - the files and folders within the selected folder and those files and folders N levels below the selected folder are listed.

By default, when a folder is selected, only its contents are displayed.
* `showparent` - The selected folder is also displayed.

## Choose what fields to display
If no query or select is performed, use these options to get file path information:
* `filepath|fullpath` - For files and folders, display the full path(s) to them starting at the root (My Drive)
* `addpathstojson` - When this option and `formatjson` are specified, the path information will be included in the
JSON data rather than as additional columns

When used with `filepath` or `fullpath`, `showdepth` will display a `depth` column.
Files/folders directly in `My Drive` are at depth 0, the depth increases by 1
for each containing folder. For files with multiple parents, the maximum depth is displayed.

If a query or select is performed, use these options to get file path information:
* `filepath` - For files, no path information is shown; for folders, the paths of all of its children are shown starting at the selected folder
* `fullpath` - For files and folders, display the full path(s) to them starting at the root (My Drive or Shared Drive)
* `addpathstojson` - When this option and `formatjson` are specified, the path information will be included in the
JSON data rather than as additional columns

By default, only the fields `id` and `webViewLink` are displayed.
* `allfields` - Display all file fields
* `<DriveFieldName>*` - Select individual fields for display
* `fields <DriveFieldNameList>` - Select a list of fields for display
* `orderby <DriveFileOrderByFieldName> [ascending|descending])*` - Select the order in which the files are displayed
* `delimiter <Character>` - Specifiy the `<Character>` to separate items in the fields: `parentsIds, permissionIds, spaces`; the default value is `csv_output_field_delimiter` from `gam.cfg`.

When `allfields` is specified, use `showdrivename` to display Shared(Team) Drive names.
An additional API call is required to get each Shared(Team) Drive name; the names are cached so there is only one additional
API call per Shared(Team) Drive.

By default, when file parents are displayed, the columns displayed are:
```
...,parents,parents.0.id`,parents.0.isRoot,parents.1.id,parents.1.isRoot,...
```
The `parents` column indicates the number of parents a file has and there are discrete entries for each parent.

The `showparentsidsaslist` option changes the output to be only two columns:
```
...,parents,parentsIds,...
```
The `parents` column indicates the number of parents a file has and the `parentsIds` column is a list of the parent IDs
separated by `delimiter <Character>`; the default value is `csv_output_field_delimiter` from `gam.cfg`.
There is no `isRoot` information displayed. This option allows you to reference all of a files parents with
`addparents <DriveFolderIDList>` or `removeparents <DriveFolderIDList>` wn updating a file.

By default, all `permissions` fields are displayed sorted with the other fields, the `showpermissionslast` option
causes GAM to display all `permissions` fields as the right-most columns in the CSV file. This option does not apply
when `formatjson` is specified.

The `countsonly` option doesn't display any indididual file data, it lists the total number of files that the use can access
and the mumber of files by MIME type.

The `countsonly` suboption `summary none|only|plus` specifies display of a summarization of file counts across all users specified in the command.
* `none` - No summary is displayed; this is the default
* `only` - Only the summary is displayed, no individual user file counts are displayed
* `plus` - The summary is displayed in addition to the individual user file counts

The `summaryuser <String>` option  replaces the default summary user `Summary` with `<String>`.

The `countsonly` suboption `showsource` adds additional columns `Source` and `Name` that identify the top level folder ID and Name from which the counts are derived.

The `countsonly` suboption `showsize` adds an additional column `Size` that indicates the total size (in bytes) of the files represented on the row.

By default, when `countsonly` is specified, GAM applies `config csv_output_row_filter` to the file details to select which files are counted.
Use the `countsrowfilter` option to have GAM to apply `config csv_output_row_filter` to the file counts rather than the file details.

The `stripcrsfromname` option strips nulls, carriage returns and linefeeds from drive file names.
This option is special purpose and will not generally be used.

By default, when writing CSV files, Gam uses a quote character of double quote `"`. The quote character is used to enclose columns that contain
the quote character itself, the column delimiter (comma by default) and new-line characters. Any quote characters within the column are doubled.
When using the `formatjson` option, double quotes are used extensively in the data resulting in hard to read/process output.
The `quotechar <Character>` option allows you to choose an alternate quote character, single quote for instance, that makes for readable/processable output.
`quotechar` defaults to `gam.cfg/csv_output_quote_char`.

### Examples
List all files/folders owned by the user:
```
gam user testuser print filelist
```
List all files/folders owned by the user that begin with the word 'Test':
```
gam user testuser print filelist query "title contains 'Test'"
```
List all files/folders owned by any user that are starred and have been modified in the last year:
```
gam user testuser print filelist fullquery "starred = true and modifiedTime >= '#querytimelastyear#'" querytimelastyear -1y
```
List the file with the most recent modification date:
```
gam user testuser print filelist orderby modifiedtime descending maxfile 1
```
List the file with the oldest modification date:
```
gam user testuser print filelist orderby modifiedtime ascending maxfile 1
```
List all files/folders without a parent, owned by anyone, do not show their descendants:
```
gam user testuser print filelist select orphans showownedby any depth 0
```
List all files/folders and their descendents, owned by the user, in the folder 'Top Folder':
```
gam user testuser print filelist select drivefilename 'Top Folder' showownedby me
```
List all files whose name ends in ".exe" that are in the folder named "Folder Name" and its sub-folders:
```
gam user testuser print filelist select drivefilename "Folder Name" filenamematchpattern ".*\.exe"
```
If you only want files whose name ends in ".exe" that are directly in the folder named "Folder Name":
```
gam user testuser print filelist select drivefilename "Folder Name" depth 0 filenamematchpattern ".*\.exe"
```
List all Meet recordings older than 30 days.
```
gam user testuser print filelist select drivefilename "Meet Recordings" querytime30d -30d selectsubquery "modifiedTime<'#querytime30d#'"
```
### Examples using csv_output_row_filter
Display file counts for users with files of size greater that 100MB, `csv_output_row_filter`
is applied to the file details.
```
gam config csv_output_row_filter "size:count>100000000" all users print filelist countsonly fields size
```
Display file counts for users with more than 100 `video/mp4` files, `csv_output_row_filter`
is applied to the file counts.
```
gam config csv_output_row_filter "video/mp4:count>100" csv_output_header_filter "Owner,video/mp4" all users print filelist countsonly countsrowfilter
```

### Examples showing file paths
All files, no file path
```
$ gam user testuser print filelist title
Getting all Drive Files/Folders that match query ('me' in owners) for testuser@domain.com
Got 11 Drive Files/Folders for testuser@domain.com...
Owner,title
testuser@domain.com,Bottom Sheet 12
testuser@domain.com,Bottom Sheet 11
testuser@domain.com,Bottom Doc 22
testuser@domain.com,Bottom Doc 21
testuser@domain.com,Bottom Folder 22
testuser@domain.com,Bottom Folder 21
testuser@domain.com,Bottom Folder 12
testuser@domain.com,Bottom Folder 11
testuser@domain.com,Middle Folder 2
testuser@domain.com,Middle Folder 1
testuser@domain.com,Top Folder
```
No `select` or `query`, `filepath` and `fullpath` give same result
```
$ gam user testuser print filelist title filepath
Getting all Drive Files/Folders that match query ('me' in owners) for testuser@domain.com
Got 11 Drive Files/Folders for testuser@domain.com...
Owner,title,paths,path.0
testuser@domain.com,Bottom Sheet 12,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 12/Bottom Sheet 12
testuser@domain.com,Bottom Sheet 11,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 11/Bottom Sheet 11
testuser@domain.com,Bottom Doc 22,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 22/Bottom Doc 22
testuser@domain.com,Bottom Doc 21,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 21/Bottom Doc 21
testuser@domain.com,Bottom Folder 22,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 22
testuser@domain.com,Bottom Folder 21,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 21
testuser@domain.com,Bottom Folder 12,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 12
testuser@domain.com,Bottom Folder 11,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 11
testuser@domain.com,Middle Folder 2,1,My Drive/Top Folder/Middle Folder 2
testuser@domain.com,Middle Folder 1,1,My Drive/Top Folder/Middle Folder 1
testuser@domain.com,Top Folder,1,My Drive/Top Folder

$ gam user testuser print filelist title fullpath
Getting all Drive Files/Folders that match query ('me' in owners) for testuser@domain.com
Got 11 Drive Files/Folders for testuser@domain.com...
Owner,title,paths,path.0
testuser@domain.com,Bottom Sheet 12,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 12/Bottom Sheet 12
testuser@domain.com,Bottom Sheet 11,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 11/Bottom Sheet 11
testuser@domain.com,Bottom Doc 22,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 22/Bottom Doc 22
testuser@domain.com,Bottom Doc 21,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 21/Bottom Doc 21
testuser@domain.com,Bottom Folder 22,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 22
testuser@domain.com,Bottom Folder 21,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 21
testuser@domain.com,Bottom Folder 12,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 12
testuser@domain.com,Bottom Folder 11,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 11
testuser@domain.com,Middle Folder 2,1,My Drive/Top Folder/Middle Folder 2
testuser@domain.com,Middle Folder 1,1,My Drive/Top Folder/Middle Folder 1
testuser@domain.com,Top Folder,1,My Drive/Top Folder
```
Select a folder, no file path
```
$ gam user testuser print filelist title select drivefilename "Top Folder"
Getting all Drive Files/Folders that match query ('me' in owners and title = 'Top Folder') for testuser@domain.com
Got 1 Drive File/Folder for testuser@domain.com...
Owner,title
testuser@domain.com,Middle Folder 2
testuser@domain.com,Bottom Folder 22
testuser@domain.com,Bottom Doc 22
testuser@domain.com,Bottom Folder 21
testuser@domain.com,Bottom Doc 21
testuser@domain.com,Middle Folder 1
testuser@domain.com,Bottom Folder 12
testuser@domain.com,Bottom Sheet 12
testuser@domain.com,Bottom Folder 11
testuser@domain.com,Bottom Sheet 11
```
Select a folder, no file path, show parent (selected) folder
```
$ gam user testuser print filelist title select drivefilename "Top Folder" showparent
Getting all Drive Files/Folders that match query ('me' in owners and title = 'Top Folder') for testuser@domain.com
Got 1 Drive File/Folder for testuser@domain.com...
Owner,title
testuser@domain.com,Top Folder
testuser@domain.com,Middle Folder 2
testuser@domain.com,Bottom Folder 22
testuser@domain.com,Bottom Doc 22
testuser@domain.com,Bottom Folder 21
testuser@domain.com,Bottom Doc 21
testuser@domain.com,Middle Folder 1
testuser@domain.com,Bottom Folder 12
testuser@domain.com,Bottom Sheet 12
testuser@domain.com,Bottom Folder 11
testuser@domain.com,Bottom Sheet 11
```
Select a folder, partial file path
```
$ gam user testuser print filelist title select drivefilename "Top Folder" filepath
Getting all Drive Files/Folders that match query ('me' in owners and title = 'Top Folder') for testuser@domain.com
Got 1 Drive File/Folder for testuser@domain.com...
Owner,title,paths,path.0
testuser@domain.com,Middle Folder 2,1,Top Folder/Middle Folder 2
testuser@domain.com,Bottom Folder 22,1,Top Folder/Middle Folder 2/Bottom Folder 22
testuser@domain.com,Bottom Doc 22,1,Top Folder/Middle Folder 2/Bottom Folder 22/Bottom Doc 22
testuser@domain.com,Bottom Folder 21,1,Top Folder/Middle Folder 2/Bottom Folder 21
testuser@domain.com,Bottom Doc 21,1,Top Folder/Middle Folder 2/Bottom Folder 21/Bottom Doc 21
testuser@domain.com,Middle Folder 1,1,Top Folder/Middle Folder 1
testuser@domain.com,Bottom Folder 12,1,Top Folder/Middle Folder 1/Bottom Folder 12
testuser@domain.com,Bottom Sheet 12,1,Top Folder/Middle Folder 1/Bottom Folder 12/Bottom Sheet 12
testuser@domain.com,Bottom Folder 11,1,Top Folder/Middle Folder 1/Bottom Folder 11
testuser@domain.com,Bottom Sheet 11,1,Top Folder/Middle Folder 1/Bottom Folder 11/Bottom Sheet 11
```
Select a folder, partial file path, show parent (selected) folder
```
$ gam user testuser print filelist title select drivefilename "Top Folder" filepath showparent
Getting all Drive Files/Folders that match query ('me' in owners and title = 'Top Folder') for testuser@domain.com
Got 1 Drive File/Folder for testuser@domain.com...
Owner,title,paths,path.0
testuser@domain.com,Top Folder,1,Top Folder
testuser@domain.com,Middle Folder 2,1,Top Folder/Middle Folder 2
testuser@domain.com,Bottom Folder 22,1,Top Folder/Middle Folder 2/Bottom Folder 22
testuser@domain.com,Bottom Doc 22,1,Top Folder/Middle Folder 2/Bottom Folder 22/Bottom Doc 22
testuser@domain.com,Bottom Folder 21,1,Top Folder/Middle Folder 2/Bottom Folder 21
testuser@domain.com,Bottom Doc 21,1,Top Folder/Middle Folder 2/Bottom Folder 21/Bottom Doc 21
testuser@domain.com,Middle Folder 1,1,Top Folder/Middle Folder 1
testuser@domain.com,Bottom Folder 12,1,Top Folder/Middle Folder 1/Bottom Folder 12
testuser@domain.com,Bottom Sheet 12,1,Top Folder/Middle Folder 1/Bottom Folder 12/Bottom Sheet 12
testuser@domain.com,Bottom Folder 11,1,Top Folder/Middle Folder 1/Bottom Folder 11
testuser@domain.com,Bottom Sheet 11,1,Top Folder/Middle Folder 1/Bottom Folder 11/Bottom Sheet 11
```
Select a folder, full file path
```
$ gam user testuser print filelist title select drivefilename "Top Folder" fullpath
Getting all Drive Files/Folders that match query ('me' in owners and title = 'Top Folder') for testuser@domain.com
Got 1 Drive File/Folder for testuser@domain.com...
Owner,title,paths,path.0
testuser@domain.com,Middle Folder 2,1,My Drive/Top Folder/Middle Folder 2
testuser@domain.com,Bottom Folder 22,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 22
testuser@domain.com,Bottom Doc 22,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 22/Bottom Doc 22
testuser@domain.com,Bottom Folder 21,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 21
testuser@domain.com,Bottom Doc 21,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 21/Bottom Doc 21
testuser@domain.com,Middle Folder 1,1,My Drive/Top Folder/Middle Folder 1
testuser@domain.com,Bottom Folder 12,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 12
testuser@domain.com,Bottom Sheet 12,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 12/Bottom Sheet 12
testuser@domain.com,Bottom Folder 11,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 11
testuser@domain.com,Bottom Sheet 11,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 11/Bottom Sheet 11
```
Select a folder, full file path, show parent (selected) folder
```
$ gam user testuser print filelist title select drivefilename "Top Folder" fullpath showparent
Getting all Drive Files/Folders that match query ('me' in owners and title = 'Top Folder') for testuser@domain.com
Got 1 Drive File/Folder for testuser@domain.com...
Owner,title,paths,path.0
testuser@domain.com,Top Folder,1,My Drive/Top Folder
testuser@domain.com,Middle Folder 2,1,My Drive/Top Folder/Middle Folder 2
testuser@domain.com,Bottom Folder 22,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 22
testuser@domain.com,Bottom Doc 22,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 22/Bottom Doc 22
testuser@domain.com,Bottom Folder 21,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 21
testuser@domain.com,Bottom Doc 21,1,My Drive/Top Folder/Middle Folder 2/Bottom Folder 21/Bottom Doc 21
testuser@domain.com,Middle Folder 1,1,My Drive/Top Folder/Middle Folder 1
testuser@domain.com,Bottom Folder 12,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 12
testuser@domain.com,Bottom Sheet 12,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 12/Bottom Sheet 12
testuser@domain.com,Bottom Folder 11,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 11
testuser@domain.com,Bottom Sheet 11,1,My Drive/Top Folder/Middle Folder 1/Bottom Folder 11/Bottom Sheet 11
```

## Handle empty file lists
When you execute a `gam print filelist` command with a query or permission match, there may be no files output;
in this case, there is only a header row: `Owner`. Subsequent gam commands to process the file will fail.
```
$ gam redirect csv ./Files.csv user user@domain.com print filelist query "name contains 'abcd'" fields id,name 
Getting all Drive Files/Folders that match query ('me' in owners and name contains 'abcd') for user@domain.com
Got 0 Drive Files/Folders that matched query ('me' in owners and name contains 'abcd') for user@domain.com...
$ more Files.csv
Owner
$ gam csv Files.csv gam user ~Owner show fileinfo ~id permissions
Command: /Users/admin/bin/gam csv Files.csv gam user ~Owner show fileinfo >>>~id<<< permissions

ERROR: Header "id" not found in CSV headers of "Owner".
Help: Syntax in file /Users/admin/bin/gam/GamCommands.txt
Help: Documentation is at https://github.com/taers232c/GAMADV-XTD3/wiki
```

Now, the fields you select will be output on the header row and the subsequent command will not fail.
```
$ gam redirect csv ./Files.csv user user@domain.com print filelist query "name contains 'abcd'" fields id,name
Getting all Drive Files/Folders that match query ('me' in owners and name contains 'abcd') for user@domain.com
Got 0 Drive Files/Folders that matched query ('me' in owners and name contains 'abcd') for user@domain.com...
$ more Files.csv
Owner,id,name
$ gam csv Files.csv gam user ~Owner show fileinfo ~id permissions
$
```

If you specify `allfields`, a predefined set of headers are output.
```
$ gam redirect csv ./Files.csv user user@domain.com print filelist query "name contains 'abcd'" allfields
Getting all Drive Files/Folders that match query ('me' in owners and name contains 'abcd') for user@domain.com
Got 0 Drive Files/Folders that matched query ('me' in owners and name contains 'abcd') for user@domain.com...
$ more Files.csv
Owner,id,name,owners.0.emailAddress,permissions,permissions.0.allowFileDiscovery,permissions.0.deleted,permissions.0.displayName,permissions.0.domain,permissions.0.emailAddress,permissions.0.expirationTime,permissions.0.id,permissions.0.permissionDetails,permissions.0.photoLink,permissions.0.role,permissions.0.teamDrivePermissionDetails,permissions.0.type
```

You can also specify the headers you want in the case that there are no files selected; your script could test for this value.
```
$ gam redirect csv ./Files.csv user user@domain.com print filelist query "name contains 'abcd'" allfields nodataheaders "BadNews-NoData"
Getting all Drive Files/Folders that match query ('me' in owners and name contains 'abcd') for user@domain.com
Got 0 Drive Files/Folders that matched query ('me' in owners and name contains 'abcd') for user@domain.com...
$ more Files.csv
BadNews-NoData
```

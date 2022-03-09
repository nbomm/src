# Users - Drive Files Manage 
- [API documentation](#api-documentation)
- [Query documentation](#query-documentation)
- [Python Regular Expressions](Python-Regular-Expressions) Sub function
- [Collections of Users](Collections-of-Users)
- [Permission Matches](Permission-Matches)
- [Definitions](#definitions)
- [Create files](#create-files)
  - [Create folders](#create-folders)
  - [Bulk Create Files and Folders](#bulk-create-files-and-folders)
  - [Bulk Create Student Folders on a Shared Drive](#bulk-create-student-folders-on-a-shared-drive)
- [Update files](#update-files)
- [Download files](#download-files)
- [Trash files](#trash-files)
- [Untrash files](#untrash-files)
- [Purge files](#purge-files)
- [Copy/Move Files](Users-Drive-Copy-Move)
- [Create shortcuts](#create-shortcuts)
- [Check shortcut validity](#check-shortcut-validity)
- [Delete broken shortcuts](#delete-broken-shortcuts)
- [Delete stale shortcuts](#delete-stale-shortcuts)
- [Download Google Documents as JSON](#download-google-documents-as-json)

## API documentation
* https://developers.google.com/drive/api/v3/reference/files
* https://developers.google.com/drive/api/v3/ref-single-parent
* https://developers.google.com/drive/api/v3/shared-drives-diffs
* https://developers.google.com/drive/api/v3/shortcuts
* https://support.google.com/a/answer/7374057
* https://developers.google.com/docs/api/reference/rest

## Query documentation
* https://developers.google.com/drive/api/v3/search-files
* https://developers.google.com/drive/api/v3/ref-search-terms

## Definitions
See [Drive File Selection](Drive-File-Selection) for symbols not listed here, such as `<DriveFileEntity>`
```
<ColorHex> ::= "#<Hex><Hex><Hex><Hex><Hex><Hex>"
<ColorNameGoogle> ::=
        asparagus|bluevelvet|bubblegum|cardinal|chocolateicecream|denim|desertsand|
        earthworm|macaroni|marsorange|mountaingray|mountaingrey|mouse|oldbrickred|
        pool|purpledino|purplerain|rainysky|seafoam|slimegreen|spearmint|
        toyeggplant|vernfern|wildstrawberries|yellowcab
<ColorNameWeb> ::=
        aliceblue|antiquewhite|aqua|aquamarine|azure|beige|bisque|black|blanchedalmond|
        blue|blueviolet|brown|burlywood|cadetblue|chartreuse|chocolate|coral|
        cornflowerblue|cornsilk|crimson|cyan|darkblue|darkcyan|darkgoldenrod|darkgray|
        darkgrey|darkgreen|darkkhaki|darkmagenta|darkolivegreen|darkorange|darkorchid|
        darkred|darksalmon|darkseagreen|darkslateblue|darkslategray|darkslategrey|
        darkturquoise|darkviolet|deeppink|deepskyblue|dimgray|dimgrey|dodgerblue|
        firebrick|floralwhite|forestgreen|fuchsia|gainsboro|ghostwhite|gold|goldenrod|
        gray|grey|green|greenyellow|honeydew|hotpink|indianred|indigo|ivory|khaki|
        lavender|lavenderblush|lawngreen|lemonchiffon|lightblue|lightcoral|lightcyan|
        lightgoldenrodyellow|lightgray|lightgrey|lightgreen|lightpink|lightsalmon|
        lightseagreen|lightskyblue|lightslategray|lightslategrey|lightsteelblue|
        lightyellow|lime|limegreen|linen|magenta|maroon|mediumaquamarine|mediumblue|
        mediumorchid|mediumpurple|mediumseagreen|mediumslateblue|mediumspringgreen|
        mediumturquoise|mediumvioletred|midnightblue|mintcream|mistyrose|moccasin|
        navajowhite|navy|oldlace|olive|olivedrab|orange|orangered|orchid|
        palegoldenrod|palegreen|paleturquoise|palevioletred|papayawhip|peachpuff|
        peru|pink|plum|powderblue|purple|red|rosybrown|royalblue|saddlebrown|salmon|
        sandybrown|seagreen|seashell|sienna|silver|skyblue|slateblue|slategray|
        slategrey|snow|springgreen|steelblue|tan|teal|thistle|tomato|turquoise|violet|
        wheat|white|whitesmoke|yellow|yellowgreen
<ColorName> ::= <ColorNameGoogle>|<ColorNameWeb>
<ColorValue> ::= <ColorName>|<ColorHex>
```
```
<DomainName> ::= <String>(.<String>)+
<EmailAddress> ::= <String>@<DomainName>
<DriveFileRevisionID> ::= <String>
<SheetEntity> ::= <String>|id:<Number>
<Time> ::=
        <Year>-<Month>-<Day>(<Space>|T)<Hour>:<Minute>:<Second>[.<MilliSeconds>](Z|(+|-(<Hour>:<Minute>))) |
        (+|-)<Number>(m|h|d|w|y) |
        never|
        now|today

<FileFormat> ::=
        csv|doc|dot|docx|dotx|epub|html|jpeg|jpg|mht|odp|ods|odt|
        pdf|png|ppt|pot|potx|pptx|rtf|svg|tsv|txt|xls|xlt|xlsx|xltx|zip|
        ms|microsoft|openoffice|
<FileFormatList> ::= "<FileFormat>(,<FileFormat)*"

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
        

<MimeTypeName> ::= application|audio|font|image|message|model|multipart|text|video

<MimeType> ::= <MimeTypeShortcut>|(<MimeTypeName>/<String>)
```
```
<DriveFileAttribute> ::=
        (contentrestrictions readonly false)|
        (contentrestrictions readonly true [reason <String>])|
        (copyrequireswriterpermission [<Boolean>])|
        (description <String>)|
        (folderColorRgb <ColorValue>)|
        (indexabletext <String>)|
        (keeprevisionforever|pinned)|
        (lastviewedbyme <Time>)|
        (mimetype <MimeType>)|
        (ocrlanguage <Language>)|
        (preservefiletimes [<Boolean>])|
        (privateproperty <PropertyKey> <PropertyValue>)|
        (publicproperty <PropertyKey> <PropertyValue>)|
        (property <PropertyKey> <PropertyValue> [private|public])|
        (restricted|restrict [<Boolean>])|
        (securityupdate [<Boolean>])|
        (starred|star [<Boolean>])|
        (trashed|trash [<Boolean>])|
        (viewed|view [<Boolean>])|
        (shortcut <DriveFileID>)|
        (viewerscancopycontent [<Boolean>])|
        (writerscanshare|writerscantshare [<Boolean>])

<DriveFileParentAttribute> ::=
        (parentid <DriveFolderID>)|
        (parentname <DriveFolderName>)|
        (anyownerparentname <DriveFolderName>)|
        (teamdriveparentid <DriveFolderID>)|
        (teamdriveparent <SharedDriveName>)|
        (teamdriveparentid <SharedDriveID> teamdriveparentname <DriveFolderName>)|
        (teamdriveparent <SharedDriveName> teamdriveparentname <DriveFolderName>)

<DriveFileCreateAttribute> ::=
        <DriveFileAttribute>|
        <DriveFileParentAttribute>|
        (createddate|createdtime <Time>)|
        (modifieddate|modifiedtime <Time>)|
        ignoredefaultvisibility|
        usecontentasindexabletext

<DriveFileUpdateAttribute> ::=
        <DriveFileAttribute>|
        <DriveFileParentAttribute>|
        (modifieddate|modifiedtime <Time>)|
        usecontentasindexabletext|
        ((addparents <DriveFolderIDList>)|
         (addparentname <DriveFolderName>)|
         (addanyownerparentname <DriveFolderName>))|
        ((removeparents <DriveFolderIDList>)|
         (removeparentname <DriveFolderName>)|
         (removeanyownerparentname <DriveFolderName>))
```
## Create files
```
gam <UserTypeEntity> create|add drivefile
        [localfile <FileName>|-] [drivefilename <DriveFileName>] [stripnameprefix <String>]
        <DriveFileCreateAttribute>* [enforcesingleparent <Boolean>]
        [csv [todrive <ToDriveAttribute>*]] [returnidonly|returnlinkonly|returneditlinkonly|showdetails]
        (addcsvdata <FieldName> <String>)*
```
By default, an empty file is created.

To upload content to the file use:
* `localfile <FileName>` - Upload content from `<FileName>`
* `localfile -` - Upload content from stdin

You can specify where the new file is to be located:
* `parentid <DriveFolderID>` - Folder ID.
* `parentname <DriveFolderName>` - Folder name; the folder must be owned by `<UserTypeEntity>`.
* `anyownerparentname <DriveFolderName>` - Folder name; the folder can be owned by any user, `<UserTypeEntity>` must be able to write to the folder.
* `teamdriveparentid <DriveFolderID>` - Shared Drive folder ID; when used alone, this indicates a specfic Shared Drive folder.
* `teamdriveparent <SharedDriveName>` - Shared Drive name; when used alone, this indicates the root level of the Shared Drive.
* `teamdriveparentid <SharedDriveID> teamdriveparentname <DriveFolderName>` - A Shared Drive ID and a folder name  on that Shared Drive.
* `teamdriveparent <SharedDriveName> teamdriveparentname <DriveFolderName>` - A Shared Drive name and a folder name on that Shared Drive.
* If none of the parent options are specified, the parent folder is the root folder.

From the Google Drive API documentation.
* `enforcesingleparent` - This parameter only takes effect if the item is not in a shared drive.
  * `false` - Do not opt in to API behavior that aims for all items to have exactly one parent. Default.
  * `true` - Opt in to API behavior that aims for all items to have exactly one parent.
    * Requests that specify more than one parent fail.

By default, Google assigns the current time to the attributes `createdTime` and `modifiedTime`; you can assign your own values
with `createdtime <Time>` and `modifiedtime <Time>`.

The option `preservefiletimes`, when used with `localfile <FileName>`, will set the `createdTime` and `modifiedTime` attributes from the local file.

On some Linux systems getting the createdtime is problematic.
* See: https://stackoverflow.com/questions/237079/how-to-get-file-creation-modification-date-times-in-python/39501288#39501288

These are the naming rules:
* `create drivefile localfile "LocalFile.csv"` - Google Drive file is named "LocalFile.csv"
* `create drivefile drivefilename "GoogleFile.csv" localfile "LocalFile.csv"` - Google Drive file is named "GoogleFile.csv"

If `stripnameprefix <String>` is specified, `<String>` will be stripped from the front of the Google Drive file name if present.

By default, the user, file name and id values are displayed on stdout.
* `csv [todrive <ToDriveAttribute>*]` - Write user, file name and id values to a CSV file.
  * `addcsvdata <FieldName> <String>` - Add additional columns of data from the command lineto the output
* `returnidonly` - Display just the file ID of the created file as output
* `returnlinkonly` - Display just the file webViewLink of the created file as output
* `returneditlinkonly` - Display just the file editLink of the created file as output
* `showdetails` - Add the parent folder ID and MIME type to the output

To retrieve the file ID with `returnidonly`:
```
Linux/MacOS
fileId=`gam user user@domain.com create drivefile ... returnidonly`
Windows PowerShell
$fileId = & gam user user@domain.com create drivefile ... returnidonly
```
The file ID will only be valid when the return code of the command is 0; program accordingly.

## Create folders

Google Drive folders to GAM are just like files, with the MimeType for a folder. To create a folder `FooFolder` in the root of the Drive for user `Fred`:

```
user Fred@yourdomain.com create drivefile drivefilename FooFolder mimetype gfolder
```

The same, but created in the existing folder `BarFolder`:

```
user Fred@yourdomain.com create drivefile drivefilename FooFolder mimetype gfolder parentname BarFolder
```

This only works if the folder name for the parent is unique. An alternative is to use the folder ID:

```
user Fred@yourdomain.com create drivefile drivefilename FooFolder mimetype gfolder parentid <FolderID>
```

## Bulk Create Files and Folders
Make a CSV file FileNames.csv with at least two columns, primaryEmail and Name.
```
Files
gam redirect csv ./FileNamesIDs.csv multiprocess [todrive <ToDriveAttribute>*] csv FileNames.csv gam user "~primaryEmail" create drivefile drivefilename "~Name" csv [other options as desired]

Folders
gam redirect csv ./FileNamesIDs.csv multiprocess [todrive <ToDriveAttribute>*] csv FileNames.csv gam user "~primaryEmail" create drivefile drivefilename "~Name" csv mimetype gfolder [other options as desired]

Add a column mimetype to create files and folders
gam redirect csv ./FileNamesIDs.csv multiprocess [todrive <ToDriveAttribute>*] csv FileNames.csv gam user "~primaryEmail" create drivefile drivefilename "~Name" csv mimetype "~mimetype" [other options as desired]
```
This will create a three column CSV file SharedDriveNamesIDs.csv with columns: User,name,id
* There will be a row for each file/folder.

## Bulk Create Student Folders on a Shared Drive
You are building student folders on a Shared Drive as an admin and want to add ACLs to the folders
allowing the student write access and you want a shortcut on the student's My Drive pointing to the folder.
By adding the student's primary email address to the CSV output, it can be used in subsequent commands.
Sustitute for admin@domain.com and `<TeamDriveID>`.
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

## Update files
```
gam <UserTypeEntity> update drivefile <DriveFileEntity> [copy] [returnidonly|returnlinkonly]
        [localfile <FileName>|-]
        [retainname | (newfilename <DriveFileName>) | (replacefilename <RegularExpression> <String>)*]
        [stripnameprefix <String>]
        <DriveFileUpdateAttribute>* [enforcesingleparent <Boolean>]
        [(gsheet|csvsheet <SheetEntity> [clearfilter])|(addsheet <String>)]
        [charset <CharSet>] [columndelimiter <Character>]
```
By default, an existing file's attributes are updated.

To upload content to the file use:
* `localfile <FileName>` - Upload content from `<FileName>`
* `localfile -` - Upload content from stdin

You can change where the new file is to be located; this removes all other parent folders:
* `parentid <DriveFolderID>` - Folder ID.
* `parentname <DriveFolderName>` - Folder name; the folder must be owned by `<UserTypeEntity>`.
* `anyownerparentname <DriveFolderName>` - Folder name; the folder can be owned by any user, `<UserTypeEntity>` must be able to write to the folder.
* `teamdriveparentid <DriveFolderID>` - Shared Drive folder ID; when used alone, this indicates a specfic Shared Drive folder.
* `teamdriveparent <SharedDriveName>` - Shared Drive name; when used alone, this indicates the root level of the Shared Drive.
* `teamdriveparentid <SharedDriveID> teamdriveparentname <DriveFolderName>` - A Shared Drive ID and a folder name  on that Shared Drive.
* `teamdriveparent <SharedDriveName> teamdriveparentname <DriveFolderName>` - A Shared Drive name and a folder name on that Shared Drive.

You can add/remove parent folders without affecting other parent folders.
* `addparents|removeparents <DriveFolderIDList>` - Specify the parent folders by ID.
* `addparentname|removeparentname <DriveFolderName>` - Perform the query: `"'me' in owners and name='<DriveFolderName>'"` to convert `<DriveFolderName>` to its `<DriveFolderID>`.
* `addanyownerparentname|removeanyownerparentname <DriveFolderName>` - Perform the query: `"name='<DriveFolderName>'"` to convert `<DriveFolderName>` to its `<DriveFolderID>`.

From the Google Drive API documentation.
* `enforcesingleparent` - This parameter only takes effect if the item is not in a shared drive.
  * `false` - Do not opt in to API behavior that aims for all items to have exactly one parent. Default.
  * `true` - Opt in to API behavior that aims for all items to have exactly one parent.
    * If the item's owner makes a request to add a single parent, the item is removed from all current folders and placed in the requested folder.
    * Other requests that increase the number of parents fail, except when the canAddMyDriveParent file capability is true and a single parent is being added. 

By default, Google assigns the current time to the attribute `modifiedTime`; you can assign your own value
with `modifiedtime <Time>`.

The option `preservefiletimes`, when used with `localfile <FileName>`, will set the `modifiedTime` attribute from the local file.

These are the naming rules when updating from a local file:
* `update drivefile drivefilename "GoogleFile.csv" localfile "NewLocalFile.csv"` - Google Drive file "GoogleFile.csv" is renamed "NewLocalFile.csv"
* `update drivefile drivefilename "GoogleFile.csv" newfilename "NewGoogleFile.csv" localfile "NewLocalFile.csv"` - Google Drive file "GoogleFile.csv" is renamed "NewGoogleFile.csv"
* `update drivefile drivefilename "GoogleFile.csv" retainname localfile "NewLocalFile.csv"` - Google Drive file "GoogleFile.csv" is not renamed

To simply rename a file, use `newfilename <String>`:
* `update drivefile drivefilename "GoogleFile.csv" newfilename "NewGoogleFile.csv"` - Google Drive file "GoogleFile.csv" is renamed "NewGoogleFile.csv"

For more complex renaming, use `replacefilename <RegularExpression> <String>`:
* `update drivefile drivefilename "GoogleFile.csv" replacefilename "Google" "Boggle"` - Google Drive file "GoogleFile.csv" is renamed "BoggleFile.csv"
* `update drivefile drivefilename "GoogleFile.csv" replacefilename "^(.+)$" "New\1"` - Google Drive file "GoogleFile.csv" is renamed "NewGoogleFile.csv"

If `retainname` is not specified and `stripnameprefix <String>` is specified, `<String>` will be stripped from the front of the Google Drive file name if present.

You can update a specific sheet within a Google spreadsheet or add a new sheet to the spreadsheet
* `gsheet|csvsheet <String>` - Specify a sheet by name in a Google Sheets file to be updated
* `gsheet|csvsheet id:<Number>` - Specify a sheet by ID in a Google Sheets file to be updated
  * `clearfilter` - When updating a sheet, this option causes GAM to clear the spreadsheet basic filter so hidden data will be overwritten
* `addsheet <String>` - Specify a sheet name to be added to the Google Sheets file
* `charset <CharSet>` - Specify the character set of the local file; if not specified, the value of `charset` from `gam.cfg` will be used
* `columndelimiter <Character>` - Columns are separated by `<Character>`; if not specified, the value of `csv_input_column_delimiter` from `gam.cfg` will be used
If you want the Google spreadsheet to retain its name, specify: `retainname localfile LocalFile.csv`.

By default, the user, file name, updated file name and id values are displayed on stdout.
* `returnidonly` - Display just the file ID of the updated file as output
* `returnlinkonly` - Display just the file webViewLink of the updated file as output

To retrieve the file ID with `returnidonly`:
```
Linux/MacOS
fileId=`gam user user@domain.com update drivefile <DriveFileEntity> copy ... returnidonly`
Windows PowerShell
$fileId = & gam user user@domain.com update drivefile <DriveFileEntity> copy ... returnidonly
```
The file ID will only be valid when the return code of the command is 0; program accordingly.

By default, a file or folder is updated. Use the `copy` option to copy a file or folder.

## Download files

```
gam <UserTypeEntity> get drivefile <DriveFileEntity> [revision <DriveFileRevisionID>]
        [(format <FileFormatList>)|(gsheet|csvsheet <SheetEntity>)] [exportsheetaspdf <String>]
        [targetfolder <FilePath>] [targetname <FileName>|-] [overwrite [<Boolean>]] [showprogress [<Boolean>]]
```
By default, Google Docs/Sheets/Slides are converted to Open Office format when downloaded. If you want a
different format for these files or are downloading a different type of file, you must specify the format.
* `format <FileFormatList>` - Specify a list of formats, the downloaded file will be converted to the first applicable format
* `gsheet|csvsheet <String>` - Specify a sheet by name in a Google Sheets file to be downloaded in CSV format
* `gsheet|csvsheet id:<Number>` - Specify a sheet by ID in a Google Sheets file to be downloaded in CSV format

You can download Google Sheets into PDF files; `exportsheetaspdf <String>` specifies formatting options.
* All sheets will be downloaded, use `gsheet|csvsheet <String>|id:<Number>` to download a specific sheet
* Page order: &pageorder=1|2
    * 1 = Down, then over
    * 2 = Over, then down
* Paper size: &size=A3|A4|A5|B4|B5|letter|tabloid|legal|statement|executive|folio
* Scale: &scale=1|2|3|4
    * 1 = Normal 100%
    * 2 = Fit to width
    * 3 = Fit to height
    * 4 = Fit to Page
* Orientation: &portrait=true|false
    * false = landscape
* Fit to width: &fitw=true|false
    * false = actual size
* Horizontal alignment: &horizontal_alignment=LEFT|RIGHT|CENTER
* Vertical alignment: &vertical_alignment=TOP|MIDDLE|BOTTOM
* Top margin: &top_margin=0.00
    * All four margins must be set
* Bottom margin: &bottom_margin=0.00
* Left margin: &left_margin=0.00
* Right margin: &right_margin=0.00
* Print sheet names: &sheetnames=true|false
* Print notes: &printnotes=true|false
* Print title: &printtitle=true|false
* Print page numbers: &pagenum=CENTER|UNDEFINED
    * CENTER = include page numbers, but they always seem to be in the bottom right
    * UNDEFINED = do not include page numbera
* Print gridlines: &gridlines=true|false
* Frozen columns: &fzc=true|false
* Frozen rows: &fzr=true|false
* Range: &r1=0&c1=0&r2=1&c2=1
    * Rows and columns are numbered from 0
    * r1 - top row
    * c1 - left column
    * r2 - bottom row + 1
    * c2 - right column +1
If you make a mistake in `exportsheetaspdf <String>`, the download will fail with HTTP error 400 or 500.

By default, when getting a drivefile, it is downloaded to the directory specified in `gam.cfg/drive_dir`.
* `targetfolder <FilePath>` - Specify an alternate location for the downloaded file.

By default, when getting a drivefile, the local name is the same as the Google Drive name.
* `targetname <FileName>` - Specify an alternate name for the downloaded file.
* `targetname -` - The drivefile will be written to stdout

The strings `#email#`, `#user#` and `#username#` will be replaced by the the user's full emailaddress or just the name portion
in `targetfolder <FilePath>` and `targetname <FileName>`.

By default, when getting a drivefile, an existing local file will not be overwritten; a numeric prefix is added to the filename.
* `overwrite` - Overwite an existing file
* `overwrite true` - Overwite an existing file
* `overwrite false` - Do not overwite an existing file; add a numeric prefix and create a new file

When getting a drivefile, you can show download progress information with the `showprogress` option.
* `showprogress` - Show download progress information
* `showprogress true` - Show download progress information
* `showprogress false` - Do not show download progress information

### Example: Download a CSV file and execute a Gam command on its contents
Suppose you have a Google Sheets file UserSheet with multiple sheets, one of which is named NewUsers; it has a column labelled primaryEmail.

The following command will download the sheet and show the name for each user in the column.
```
gam user user@domain.com get drivefile drivefilename UserSheet csvsheet NewUsers targetname - | gam redirect stdout - multiprocess csv - gam info user ~primaryEmail name nogroups nolicenses
```
* The `redirect stdout - multiprocess` option produces clean output from the multiple processes

## Trash files
Move a file or folder to the trash. If a folder is moved to the trash, all of its child files and folders are moved to the trash.
```
gam <UserTypeEntity> trash drivefile <DriveFileEntity>
gam <UserTypeEntity> delete|del drivefile <DriveFileEntity> trash
```

## Untrash files
Remove a file or folder from the trash. If a folder is removed from the trash, all of its child files and folders are removed from the trash.
```
gam <UserTypeEntity> untrash drivefile <DriveFileEntity>
gam <UserTypeEntity> delete|del drivefile <DriveFileEntity> untrash
```

## Purge files
Purging a file permanently deletes it; it can not be recovered. If a folder is purged, all of its child files and folders are purged.
```
gam <UserTypeEntity> purge drivefile <DriveFileEntity>
gam <UserTypeEntity> delete|del drivefile <DriveFileEntity> purge
```

## Create shortcuts
```
gam <UserTypeEntity> create|add drivefileshortcut <DriveFileEntity> [shortcutname <String>]
        [<DriveFileParentAttribute>|convertparents]
        [csv [todrive <ToDriveAttribute>*]] [returnidonly]
```
Shortcuts will be created for all files in `<DriveFileEntity>`; if `shortcutname <String>`
is not specified, the shortcuts will be named `<DriveFileName>` where `<DriveFileName>`
is the name of each file referenced in `<DriveFileEntity>`. `<String>` can contain the string `#filename#` which will be replaced with
`<DriveFileName>`; e.g., `shortcutname "Shortcut to #filename#"`.

There are two modes of operaton:
* `<DriveFileParentAttribute>` - Create shortcuts in specific locations
  * `parentid <DriveFolderID>` - Folder ID.
  * `parentname <DriveFolderName>` - Folder name; the folder must be owned by `<UserTypeEntity>`.
  * `anyownerparentname <DriveFolderName>` - Folder name; the folder can be owned by any user, `<UserTypeEntity>` must be able to write to the folder.
  * `teamdriveparentid <DriveFolderID>` - Shared Drive folder ID; when used alone, this indicates a specfic Shared Drive folder.
  * `teamdriveparent <SharedDriveName>` - Shared Drive name; when used alone, this indicates the root level of the Shared Drive.
  * `teamdriveparentid <SharedDriveID> teamdriveparentname <DriveFolderName>` - A Shared Drive ID and a folder name  on that Shared Drive.
  * `teamdriveparent <SharedDriveName> teamdriveparentname <DriveFolderName>` - A Shared Drive name and a folder name on that Shared Drive.
* `convertparents` - Convert all but the last parent reference in `<DriveFileEntity>` to shortcuts. My testing shows that as parents are added to a file, they are added to the front of the parents list; thus, the last parent is the original parent.

If neither `<DriveFileParentAttribute>` nor `convertparents` are specified, the shortcut is placed in the root folder (My Drive).

When creating shortcuts in specific locations, duplicate shortcuts will not be created.
A duplicate shortcut is one that is in the same folder as another shortcut of the same name pointing to the
same target file/folder.

By default, the user, shortcut name(ID) and file name(ID) are displayed on stdout.
* `csv [todrive <ToDriveAttribute>*]` - Write user, shortcut name, shortcut ID, file name and file ID values to a CSV file.
* `returnidonly` - Display just the shortcut ID of the created shortcut as output

To retrieve the shortcut ID with `returnidonly`:
```
Linux/MacOS
fileId=`gam user user@domain.com create drivefileshortcut ... returnidonly`
Windows PowerShell
$fileId = & gam user user@domain.com create drivefileshortcut ... returnidonly
```
The shortcut ID will only be valid when the return code of the command is 0; program accordingly.

### Examples
Create a shortcut where the shortcut name is the same as the target filename.
```
$ gam user testsimple create drivefileshortcut name "My Doc" parentname "Top Folder"
User: user@domain.com, Drive File: My Doc, Create 1 Drive File Shortcut
  User: user@domain.com, Drive File: My Doc, Drive File Shortcut: My Doc(xxxD5Txq7Ptt_V-eQJMkW-O1ZS3EORzzz), Created
```
Create a shortcut where the shortcut name is different from the target filename.
```
$ gam user testsimple create drivefileshortcut name "My Doc" parentname "Top Folder" shortcutname "Shortcut to #filename#"
User: user@domain.com, Drive File: My Doc, Create 1 Drive File Shortcut
  User: user@domain.com, Drive File: My Doc, Drive File Shortcut: Shortcut to My Doc(xxxVCDtuBaJ7bc64rbK5FTVyy6ZxQyzzz), Created

$ gam user testsimple create drivefileshortcut name "My Doc 1" parentname "Top Folder" returnidonly
xxxDmNzbA86RAacOgeGqK6n9jwV2ypzzz
```
## Check shortcut validity
The files/folders that shortcuts reference can be deleted or have their MIME type changed so that it doesn't
match the MIME type specified in the shortcut. You can check the validity of shortcuts.
```
gam <UserTypeEntity> check drivefileshortcut <DriveFileEntity>
        [csv [todrive <ToDriveAttribute>*]]
```
By default, the user, shortcut name(ID) and file name(ID) and validity  are displayed on stdout.
* `csv [todrive <ToDriveAttribute>*]` - Write user and shortcut/target file details to a CSV file.
  * `User` - User email address
  * `name` - Shortcut file name
  * `id` - Shortcut file ID
  * `owner` - Shortcut file owner
  * `parentId` - Shortcut file parent
  * `shortcutDetails.targetId` - Target file ID in shortcut
  * `shortcutDetails.targetMimeType` - Target file MIME type in shortcut
  * `targetName` - Target file name
  * `targetId` - Target file ID
  * `targetMimeType` - Target file MIME type
  * `code` - 
    * 0 - Valid shortcut: `shortcutDetails.targetId` exists and `shortcutDetails.targetMimeType` matches `targetMimeType`
    * 1 - File `id` not found
    * 2 - File `id` is not a shortcut
    * 3 - File `shortcutDetails.targetId` not found
    * 4 - `shortcutDetails.targetMimeType` does not match `targetMimeType`

## Delete broken shortcuts
You can delete shortcuts that point to files that have been deleted.
```
gam redirect csv ./Shortcuts.csv user user@domain.com check drivefileshortcut my_shortcuts csv
gam csv Shortcuts.csv matchfield code 3 gam user "~owner" delete drivefile "~id"
```

## Delete stale shortcuts
You can delete/create shortcuts that point to files whose MIME type has changed; short cuts can't be updated.
```
gam redirect csv ./Shortcuts.csv user user@domain.com check drivefileshortcut my_shortcuts csv
gam csv Shortcuts.csv matchfield code 4 gam user "~owner" delete drivefile "~id"
gam csv Shortcuts.csv matchfield code 4 gam user "~owner" create drivefileshortcut "~targetId" parentid "~parentId" shortcutname "~name"
```
## Download Google Documents as JSON
This command was added in version 5.31.04, you'll have to do `gam update project` and
`gam <UserTypeEntity> check|update serviceaccount` to enable it.
```
gam <UserTypeEntity> get document <DriveFileEntity>
        [viewmode default|suggestions_inline|preview_suggestions_accepted|preview_without_suggestions]
        [targetfolder <FilePath>] [targetname <FileName>] [overwrite [<Boolean>]]
```
By default, when getting a document, it is downloaded to the directory specified in `gam.cfg/drive_dir`.
* `targetfolder <FilePath>` - Specify an alternate location for the downloaded document.

By default, when getting a document, the local name is the same as the Google Document name.
* `targetname <FileName>` - Specify an alternate name for the downloaded file.

The strings `#email#`, `#user#` and `#username#` will be replaced by the the user's full emailaddress or just the name portion
in `targetfolder <FilePath>` and `targetname <FileName>`.

By default, when getting a document, an existing local file will not be overwritten; a numeric prefix is added to the filename.
* `overwrite` - Overwite an existing file
* `overwrite true` - Overwite an existing file
* `overwrite false` - Do not overwite an existing file; add a numeric prefix and create a new file

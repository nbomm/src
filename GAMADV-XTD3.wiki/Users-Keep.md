# Users - Keep
- [API documentation](#api-documentation)
- [Notes](#notes)
- [Collections of Users](Collections-of-Users)
- [Definitions](#definitions)
- [Add Note](#add-note)
- [Delete Note](#delete-note)
- [Display Notes](#display-notes)
- [Manage Notes permissions](#manage-notes-permissions)
  - [Add Permissions](#add-permissions)
  - [Delete Permissions](#delete-permissions)
- [Examples](#examples)

## API documentation
* https://developers.google.com/keep/api/reference/rest

## Notes
To use these commands you must add the 'Keep API' to your project and update your service account authorization.
```
gam update project
gam user user@domain.com check serviceaccount
```

The Keep API does not support note labels and colors.

## Definitions
* [Command data from Google Docs/Sheets](Command-Data-From-Google-Docs-Sheets)
```
<UserGoogleDoc> ::=
        <EmailAddress> <DriveFileIDEntity>|<DriveFileNameEntity>|(<SharedDriveEntity> <SharedDriveFileNameEntity>)

<NotesName> ::= notes/<String>
<NotesNameList> ::= "<NotesName>(,<NotesName)*"
<NotesNameEntity> ::=
        <NotesNameList> | <FileSelector> | <CSVFileSelector> | <CSVkmdSelector> | <CSVDataSelector>

<NotesField> ::=
        attachments|
        body|
        createtime|
        name|
        permissions|
        title|
        trashed|
        trashtime|
        updatetime
<NotesFieldList> ::= "<NotesField>(,<NotesField>)*"
```

Keep notes have an ID that is referred to by Google as its `name`; this is the value
you will use wherever `<NotesName>` is required.

## Add Note
```
gam <UserTypeEntity> create note [title <String>]
        ((text <String>)|
         (textfile <FileName> [charset <CharSet>])|
         (gdoc <UserGoogleDoc>)|
         (json [charset <Charset>] <JSONData>)|(json file <FileName> [charset <Charset>]))
	[copyacls [copyowneraswriter]]
        [compact|formatjson|nodetails]
```
Use the `text`, `textfile` and `gdoc` options to specify the note text.

Use the `json` option to specify the title and text.
The `title <String>` option takes precedence over the json title.
```
json {"title": "Note Title", "body": {"text": {"text": "Note Text"}}
```
If you specify options `json` and `copyacls`, the note is created and any ACLs
from the json data are added to the note. If you also specify `copyowneraswriter`,
the original note owner is added as a writer to the created note.

By default, Gam displays the created note as an indented list of keys and values; the note text is displayed as individual lines.
* `compact` - Display the note text with escaped carriage returns as \r and newlines as \n
* `formatjson` - Display the note in JSON format
* `nodetails` - Display the note name only

## Delete Note
```
gam <UserTypeEntity> delete note <NoteNameEntity>
```

## Display Notes
Display selected notes
```
gam <UserTypeEntity> info note <NotesNameEntity>
        [fields <NotesFieldList>]
        [compact|formatjson]
```
By default, Gam displays the information as an indented list of keys and values; the note text is displayed as individual lines.
* `compact` - Display the note text with escaped carriage returns as \r and newlines as \n
* `formatjson` - Display the note in JSON format

Display all notes
```
gam <UserTypeEntity> show notes
        [fields <NotesFieldList>] [filter <String>]
        [role owner|writwer]
        [compact|formatjson]
```
By default, GAM displays all non-trashed notes:
* `filter trashed` - Display notes in the trash
* `role owner|writer` - Display notes where the user has the specified role

By default, Gam displays the information as an indented list of keys and values; the note text is displayed as individual lines.
* `compact` - Display the note text with escaped carriage returns as \r and newlines as \n
* `formatjson` - Display the note in JSON format

```
gam <UserTypeEntity> print notes [todrive <ToDriveAttribute>*]
        [fields <NotesFieldList>] [filter <String>]
        [role owner|writwer]
        [formatjson [quotechar <Character>]]

```
By default, GAM displays all non-trashed notes:
* `filter trashed` - Display notes in the trash
* `role owner|writer` - Display notes where the user has the specified role

By default, when writing CSV files, Gam uses a quote character of double quote `"`. The quote character is used to enclose columns that contain
the quote character itself, the column delimiter (comma by default) and new-line characters. Any quote characters within the column are doubled.
When using the `formatjson` option, double quotes are used extensively in the data resulting in hard to read/process output.
The `quotechar <Character>` option allows you to choose an alternate quote character, single quote for instance, that makes for readable/processable output.
`quotechar` defaults to `gam.cfg/csv_output_quote_char`.

## Manage Notes permissions
* The owner of a note can not have it's role changed.
* The owner of a note can not be deleted.
* A new owner can not be added to a note.

### Add permissions
```
gam <UserTypeEntity> create noteacl <NotesNameEntity>
        (user|group <EmailAddress>)+
        (json [charset <Charset>] <JSONData>)|(json file <FileName> [charset <Charset>])
        [nodetails]
```

By default, Gam displays the user, note name, number of created permissions and the permission details
* `nodetails` - Do not display the permission details

### Delete permissions
```
gam <UserTypeEntity> delete noteacl <NotesNameEntity>
        (user|group <EmailAddress>)+
        (json [charset <Charset>] <JSONData>)|(json file <FileName> [charset <Charset>])
```
Use the `user and `group`` options to specify email addresses.

Use the `json` option to specify permissions.
```
{"permissions": [{"email": "user@domain.com", "name": "notes/abc123xyz/permissions/def456uvw", "role": "WRITER", "user": {"email": "user@domain.com"}}]}
```

## Examples
### Copy notes and permissions from one user to another.
```
gam redirect csv ./notes.csv user user1@domain.com print notes formatjson quotechar "'"
gam csv ./notes.csv quotechar "'" gam user user2@domain.com create note json "~JSON" copyacls
```

### Delete all permissions for a note
```
gam redirect stdout ./notes.json user user@domain.com info note notes/abc123xyz permissions formatjson
gam user user@domain.com delete notesacl notes/abc123xyz json file notes.json
```

### Delete all of a user's trashed notes.
```
gam redirect csv ./notes.csv user user@domain.com print notes fields name filter trashed
gam user user@domain.com delete notes csvfile notes.csv:name
```
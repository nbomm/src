'# Vault
- [API documentation](#api-documentation)
- [Query documentation](#query-documentation)
- [Definitions](#definitions)
- [Vault Matters](#vault-matters)
  - [Create Vault Matters](#create-vault-matters)
  - [Manage Vault Matters](#manage-vault-matters)
  - [Display Vault Matters](#display-vault-matters)
  - [Display Vault Counts](#display-vault-counts)
- [Vault Exports](#vault-exports)
  - [Create Vault Exports](#create-vault-exports)
  - [Delete Vault Exports](#delete-vault-exports)
  - [Download Vault Exports](#download-vault-exports)
  - [Display Vault Exports](#display-vault-exports)
- [Vault Holds](#vault-holds)
  - [Create Vault Holds](#create-vault-holds)
  - [Update Vault Holds](#update-vault-holds)
  - [Delete Vault Holds](#delete-vault-holds)
  - [Display Vault Holds](#display-vault-holds)

## API documentation
* https://developers.google.com/vault/reference/rest/
* https://developers.google.com/vault/reference/rest/v1/matters.holds#CorpusQuery
* https://support.google.com/vault/answer/6099459#metadata
* https://support.google.com/vault/answer/4388708#new_gmail_export&zippy=%2Cfebruary-new-gmail-export-system-available

## Query documentation
* https://support.google.com/vault/answer/2474474

## Definitions
```
<EmailItem> ::= <EmailAddress>|<UniqueID>|<String>
<EmailItemList> ::= "<EmailItem>(,<EmailItem>)*"
<EmailAddressList> ::= "<EmailAddess>(,<EmailAddress>)*"
<EmailAddressEntity> ::= <EmailAddressList> | <FileSelector> | <CSVFileSelector> | <CSVkmdSelector> | <CSVDataSelector>
<TimeZone> ::= <String>
        See: https://en.wikipedia.org/wiki/List_of_tz_database_time_zones
<UniqueID> ::= uid:<String>
<ExportItem> ::= <UniqueID>|<String>
<ExportStatus> ::= completed|failed|inprogrsss
<ExportStatusList> ::= "<ExportStatus>(,<ExportStatus>)*"
<HoldItem> ::= <UniqueID>|<String>
<MatterItem> ::= <UniqueID>|<String>
<MatterState> ::= open|closed|deleted
<MatterStateList> ::= "<MatterState>(,<MatterState>)*"

<QueryVaultCorpus> ::= <String>
        See: https://developers.google.com/vault/reference/rest/v1/matters.holds#CorpusQuery

<VaultMatterFieldName> ::=
        description|
        matterid|
        matterpermissions|
        name|
        state
<VaultMatterFieldNameList> ::= "<VaultMatterFieldName>(,<VaultMatterFieldName>)*"

<VaultExportFieldName> ::=
        cloudstoragesink|
        createtime|
        exportoptions|
        id|
        matterid|
        name|
        query|
        requester|
        requester.displayname|
        requester.email|
        stats|
        stats.exportedArtifactCount|
        stats.sizeinbytes|
        stats.totalartifactcount|
        status
<VaultExportFieldNameList> ::= "<VaultExportFieldName>(,<VaultExportFieldName>)*"

<VaultHoldFieldName> ::=
        accounts|
        accounts.acountid|
	accounts.email|
        accounts.firstname|
        accounts.holdtime|
        accounts.lastname|
        corpus|
        holdid|
        name|
        orgunit|
        orgunit.holdtime|
        orgunit.orgunitid|
        query|
        updatetime
<VaultHoldFieldNameList> ::= "<VaultHoldFieldName>(,<VaultHoldFieldName>)*"
```
You specify matters, exports and holds by ID (`<UniqueID>`) or name (`<String>`). The API requires an ID, so if you specify a name,
GAM has to make additional API calls to convert the name to an ID.

## Vault Matters
## Create Vault Matters
Create a Google Vault matter.
```
gam create vaultmatter|matter [name <String>] [description <string>]
        [collaborator|collaborators <EmailItemList>] [sendemails <Boolean>] [ccme <Boolean>]
        [showdetails]
```
Specify the name of the matter:
* `name <String>` - The matter will be named `<String>`
* `default` - The matter will be named `GAM Matter - <Time>`

The Vault API will give an error if you try to create a new matter with the same name as an existing matter. It will, however, let you update a matter and give it a new name that matches the name of an existing matter. Subsequent GAM commands that reference that matter name will give an error indicating that you'll have to reference the matters by ID.

Use the `showdetails` option to have the full details of the matter displayed.

## Manage Vault Matters
```
gam update vaultmatter|matter <MatterItem> [name <String>] [description <string>]
        [addcollaborator|addcollaborators <EmailItemList>] [removecollaborator|removecollaborators <EmailItemList>]
gam close vaultmatter|matter <MatterItem>
gam reopen vaultmatter|matter <MatterItem>
gam delete vaultmatter|matter <MatterItem>
gam undelete vaultmatter|matter <MatterItem>
```
Vault Matters can be in one of three states: `OPEN`, `CLOSED` and `DELETED`. The valid operations in each state are:
* `OPEN` - `update` and `close`
* `CLOSED` - `reopen` and `delete`
* `DELETED` - `undelete`

## Display Vault Matters
```
gam info vaultmatter|matter <MatterItem>
        [basic|full|(fields <VaultMatterFieldNameList>)]
gam print vaultmatters|matters [todrive <ToDriveAttributes>*] [matterstate <MatterStateList>]
        [basic|full|(fields <VaultMatterFieldNameList>)]
gam show vaultmatters|matters [matterstate <MatterStateList>]
        [basic|full|(fields <VaultMatterFieldNameList>)]
```
For `show` and `print`, all matters are displayed by default; use `matterstate <MatterStateList>` to display matters filtered by state.

Select fields to display:
* `basic` - Display `matterId`, `name`, `description` and `state` fields.
* `full` - Display `matterpermissions` in addition to `basic` fields; this is the default.
* `fields <VaultMatterFieldNameList>` - Display selected fields; `matterId` and `name` are always displayed

## Display Vault Counts
Display item counts retained in Vault for the given users or groups.
* The required argument `matter` specifies the matter name or ID (prefix with id:) where the count should be performed.
* The required argument `corpus` specifies whether Gmail mailbox data or Google Groups archives are queried.
* You need to specify one argument of accounts, orgunit or everyone to determine which users/groups to query.
* The `scope` argument specifies the data to be queried, `all_data` is  the default and is recommended.

The command may take some time to complete; GAM makes repeated API calls until the operation is complete. By default,
GAM waits 15 seconds between API calls; use the `wait <Integer>` option to specify a different wait period.

This command can be useful for discovering legacy former employee accounts which no longer have any mail data retained by Vault.
```
gam print vaultcounts [todrive <ToDriveAttributes>*]
        matter <MatterItem> corpus mail|groups
        (accounts <EmailAddressEntity>) | (orgunit|org|ou <OrgUnitPath>) | everyone
        (shareddrives|teamdrives <SharedDriveIDList>) | (rooms <RoomList>)
        [scope <all_data|held_data|unprocessed_data>]
        [terms <String>] [start|starttime <Date>|<Time>] [end|endtime <Date>|<Time>] [timezone <TimeZone>]
        [excludedrafts <Boolean>]
        [includerooms <Boolean>]
        [includeshareddrives|includeteamdrives <Boolean>] [driveversiondate <Date>|<Time>]
        [wait <Integer>]
```
Check the status of a previous count operation with the name from a previous command.
```
gam print vaultcounts [todrive <ToDriveAttributes>*]
        matter <MatterItem> operation <String> [wait <Integer>]
```

## Vault Exports
## Create Vault Exports
Create a Google Vault export request.
```
gam create vaultexport|export matter <MatterItem> [name <String>] corpus drive|mail|groups|hangouts_chat|voice
        (accounts <EmailAddressEntity>) | (orgunit|org|ou <OrgUnitPath>) | everyone
        (shareddrives|teamdrives <SharedDriveIDList>) | (rooms <RoomList>)
        [scope <all_data|held_data|unprocessed_data>]
        [terms <String>] [start|starttime <Date>|<Time>] [end|endtime <Date>|<Time>] [timezone <TimeZone>]
        [excludedrafts <Boolean>] [format mbox|pst]
        [showconfidentialmodecontent <Boolean>] [usenewexport <Boolean>]
        [includerooms <Boolean>]
        [covereddata calllogs|textmessages|voicemails]
        [includeshareddrives <Boolean>] [driveversiondate <Date>|<Time>] [includeaccessinfo <Boolean>]
        [region any|europe|us] [showdetails]
```
<MatterItem> specifies the matter name or ID the export should be associated with.

Specify the name of the export:
* `name <String>` - The export will be named `<String>`
* `default` - The export will be named `GAM <corpus> Export - <Time>`

Specify the corpus of data, this option is required::
* `drive`
* `mail`
* `groups`
* `hangouts_chat`
* `voice`

Specify the search method, this option is required:
* `accounts <EmailAddressEntity>` - Search all accounts specified in `<EmailAddressEntity>`
* `orgunit|org|ou <OrgUnitPath>` - Search all accounts in the OU `<OrgUnitPath>`
* `everyone` - Search for all accounts in the organization
* `shareddrives|teamdrives <SharedDriveIDList>` - Search for all accounts in the Shared Drives specified in `<SharedDriveIDList>`
* `rooms <RoomList>` - Search in the Room specified in the chat rooms specified in `<RoomList>`

Specify the scope of data to include in the export:
* `all_data` - All available data; this is the default
* `held_data` - Data on Hold
* `unprocessed_data` - Data not processed

Specify time limits on the scope of data:
* `start|starttime <Date>|<Time>` - The start time range for the search query. These timestamps are in GMT and rounded down to the start of the given date.
* `end|endtime <Date>|<Time>` - The end time range for the search query. These timestamps are in GMT and rounded down to the start of the given date.
* `timezone <TimeZone>` - The time zone name. It should be an IANA TZ name, such as "America/Los_Angeles"

For `corpus drive`, you can specify advanced search options:
* `driveversiondate <Date>|<Time>` - Search the versions of the Drive file as of the reference date. These timestamps are in GMT and rounded down to the given date.
* `includeshareddrives False` - Do not include Shared Drives in the search, this is the default.
* `includeshareddrives True` - Innclude Shared Drives in the search.

For `corpus drive`, you can specify whether to include access information for users with [indirect access](https://support.google.com/vault/answer/6099459#metadata) to the files:
* `includeaccessinfo False` - Do not include access information for users with indirect access, this is the default
* `includeaccessinfo True` - Include access information for users with indirect access

For `corpus hangouts_chat` you can specify advanced search options:
* `includerooms False` - Do not include rooms, this is the default
* `includerooms True` - Include rooms

For `corpus mail`, you can specify search terms to limit the scope of data:
* `terms <String>` - [Vault search](https://support.google.com/vault/answer/2474474)

For `corpus mail`, you can specify whether to exclude draft messages:
* `excludedrafts False` - Do not exclude drafts, this is the default
* `excludedrafts True` - Exclude drafts

For `corpus mail`, you can specify whether to export confidential mode content:
* `showconfidentialmodecontent false` - Do not export confidential mode content
* `showconfidentialmodecontent true` - Export confidential mode content

For `corpus mail`, you can specify whether to use the new export system:
* `usenewexport false` - Do not use the new export system
* `usenewexport true` - Use the new export system

See: https://support.google.com/vault/answer/4388708#new_gmail_export&zippy=%2Cfebruary-new-gmail-export-system-available

For `corpus mail`, `corpus groups` and `corpus hangouts_chat`, you can specfiy the format of the exported data:
* `format mbox` - Export in MBOX format, this is the default
* `format pst` - Export in PST format

For `corpus voice` you can specify thet data covered by the export:
* `covereddata calllogs` - Call logs
* `covereddata textmessages` - Voice text messages
* `covereddata voicemail` - Voicemail

Use the `region any|europe|us` option to specify the export location; it requires Google Workspace Enterprise or Google Workspace Business licenses.

Use the `showdetails` option to have the full details of the export displayed.

## Delete Vault Exports
```
gam delete vaultexport|export <ExportItem> matter <MatterItem>
gam delete vaultexport|export <MatterItem> <ExportItem>
```
## Download Vault Exports
```
gam download vaultexport|export <ExportItem> matter <MatterItem> [targetfolder <FilePath>] [targetname <FileName>] [noverify] [noextract] [ziptostdout]
gam download vaultexport|export <MatterItem> <ExportItem> [targetfolder <FilePath>] [targetname <FileName>] [noverify] [noextract] [ziptostdout]
```
By default, the export file will be downloaded to the directory specified by `drive_dir` in gam.cfg.
* `targetfolder <FilePath>` - The export file will be downloaded to `<FilePath>`

By default, the export files have long names made up of the matter name, export name and date.
* `targetname <FileName>` - Specify a name for the top level files: `.zip`, `.xml`, `.csv`.

The extensions of the top level files will be appended to `<FileName>`.

Alternatively, `<FileName>` can contain the strings `#objectname#`, `#filename#`
and `#extension#` which will be replaced by the values from the original object names to construct a complete top level name.
For example, `targetname "#filename#.#extension#"` strips the long matter name from the original name.

**In versions prior to 6.07.14, If `<FileName>` does not contain `#filename#` and there are multiple top level files with the same extension, only the 
last file with a given extension will be saved as the earlier files will be overwritten.**

This is fixed in 6.07.14: the files will be named `FileName-N.ext` where `N` is `1,2,3,...`.

Zip files extracted from the top level Zip file will still have their long names.

* `noverify` - Do not verify MD5 hash on downloaded file
* `noextract` - Do not extract files from downloaded Zip file

The Zip file can be written to stdout to allow the following command structure:
```
gam download vaultexport <MatterItem> <ExportItem> ziptostdout | some program that consumes the Zip file
```
This will only be successful if there is one main Zip file in the export.

## Display Vault Exports
```
gam info vaultexport|export <ExportItem> matter <MatterItem>
        [fields <VaultExportFieldNameList>] [shownames]
gam info vaultexport|export <MatterItem> <ExportItem>
        [fields <VaultExportFieldNameList>] [shownames]
gam print vaultexports|exports [todrive <ToDriveAttributes>*]
        [matters <MatterItemList>] [exportstatus <ExportStatusList>]
        [fields <VaultExportFieldNameList>] [shownames]
gam show vaultexports|exports
        [matters <MatterItemList>] [exportstatus <ExportStatusList>]
        [fields <VaultExportFieldNameList>] [shownames]
```
For `show` and `print`, exports for all matters are displayed by default; use `matter|matters <MatterItemList>` to display exports for a specific set of matters.

For `show` and `print`, all exports are displayed by default; use `exportstatus <ExportStatusList>` to display exports filtered by status.

Select fields to display:
* By default all fields are displayed
* `fields <VaultExportFieldNameList>` - Display selected fields; `id` and `name` are always displayed

The `shownames` argument controls whether account and org unit names are displayed; additional API calls are required to get the names.

## Vault Holds
## Create Vault Holds
```
gam create vaulthold|hold matter <MatterItem> [name <String>] corpus drive|mail|groups|hangouts_chat
        [(accounts|groups|users <EmailItemList>) | (orgunit|org|ou <OrgUnit>)]
        [query <QueryVaultCorpus>]
        [terms <String>] [start|starttime <Date>|<Time>] [end|endtime <Date>|<Time>]
        [includerooms <Boolean>]
        [covereddata calllogs|textmessages|voicemails]
        [includeshareddrives|includeteamdrives <Boolean>]
        [showdetails]
```
Specify the name of the hold:
* `name <String>` - The hold will be named `<String>`
* `default` - The hold will be named `GAM <corpus> Hold - <Time>`

Specify the corpus of data, this option is required::
* `drive`
* `mail`
* `groups`
* `hangouts_chat`

Specify the search method, this option is required:
* `accounts|groups|users <EmailAddressEntity>` - Search all accounts specified in `<EmailAddressEntity>`
* `orgunit|org|ou <OrgUnitPath>` - Search all accounts in the OU `<OrgUnitPath>`

The `query <QueryVaultCorpus>` option can still be used but it is much simpler to use the following options.

For `corpus drive`, you can specify advanced search options:
* `includeshareddrives False` - Do not include Shared Drives in the search, this is the default.
* `includeshareddrives True` - Include Shared Drives in the search.

For `corpus mail`, you can specify search terms to limit the search.
* `terms <String>` - [Vault search](https://support.google.com/vault/answer/2474474)

For `corpus mail`, you can specify time limits on the search:
* `start|starttime <Date>|<Time>` - The start time range for the search query. These timestamps are in GMT and rounded down to the start of the given date.
* `end|endtime <Date>|<Time>` - The end time range for the search query. These timestamps are in GMT and rounded down to the start of the given date.

For `corpus hangouts_chat` you can specify advanced search options:
* `includerooms False` - Do not include rooms, this is the default
* `includerooms True` - Include rooms

For `corpus voice` you can specify the data covered by the hold:
* `covereddata calllogs` - Call logs
* `covereddata textmessages` - Voice text messages
* `covereddata voicemail` - Voicemail

Use the `showdetails` option to have the full details of the hold displayed.

## Update Vault Holds
```
gam update vaulthold|hold <HoldItem> matter <MatterItem>
        [([addaccounts|addgroups|addusers <EmailItemList>] [removeaccounts|removegroups|removeusers <EmailItemList>]) | (orgunit|ou <OrgUnit>)]
        [query <QueryVaultCorpus>]
        [terms <String>] [start|starttime <Date>|<Time>] [end|endtime <Date>|<Time>]
        [includerooms <Boolean>]
        [covereddata calllogs|textmessages|voicemails]
        [includeshareddrives|includeteamdrives <Boolean>]
        [showdetails]
```
For a hold with `corpus drive`, you can specify advanced search options:
* `includeshareddrives False` - Do not include Shared Drives in the search, this is the default.
* `includeshareddrives True` - Include Shared Drives in the search.

For a hold with `corpus mail`, you can specify search terms to limit the search.
* `terms <String>` - [Vault search](https://support.google.com/vault/answer/2474474)

For a hold with `corpus mail`, you can specify time limits on the search:
* `start|starttime <Date>|<Time>` - The start time range for the search query. These timestamps are in GMT and rounded down to the start of the given date.
* `end|endtime <Date>|<Time>` - The end time range for the search query. These timestamps are in GMT and rounded down to the start of the given date.

For a hold with `corpus hangouts_chat` you can specify advanced search options:
* `includerooms False` - Do not include rooms, this is the default
* `includerooms True` - Include rooms

For a hold with `corpus voice` you can specify the data covered by the hold:
* `covereddata calllogs` - Call logs
* `covereddata textmessages` - Voice text messages
* `covereddata voicemail` - Voicemail

Use the `showdetails` option to have the full details of the hold displayed.

## Delete Vault Holds
```
gam delete vaulthold|hold <HoldItem> matter <MatterItem>
gam delete vaulthold|hold <MatterItem> <HoldItem>
```
Vault holds can only be managed in `OPEN` matters.

The types of email addresses in `<EmailItemList>` is determined by the value of `corpus`:
* `drive` or `mail` - user email addresses
* `group` - group email addresses

## Display Vault Holds
```
gam info vaulthold|hold <HoldItem> matter <MatterItem>
        [fields <VaultHoldFieldNameList>] [shownames]
gam info vaulthold|hold <MatterItem> <HoldItem>
        [fields <VaultHoldFieldNameList>] [shownames]
gam print vaultholds|holds [todrive <ToDriveAttributes>*] [matters <MatterItemList>]
        [fields <VaultHoldFieldNameList>] [shownames]
gam show vaultholds|holds [matters <MatterItemList>]
        [fields <VaultHoldFieldNameList>] [shownames]
```
Vault holds can only be displayed in `OPEN` matters.

For `show` and `print`, holds for all matters are displayed by default; use `matter|matters <MatterItemList>` to display holds for a specific set of matters.

Select fields to display:
* By default all fields are displayed
* `fields <VaultHoldFieldNameList>` - Display selected fields; `holdId` and `name` are always displayed

The `shownames` argument controls whether account and org unit names are displayed; additional API calls are required to get the names.

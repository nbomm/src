# Users
- [API documentation](#api-documentation)
- [Name guidelines](#name-guidelines)
- [Query documentation](#query-documentation)
- [Quoting rules](#quoting-rules)
- [Python Regular Expressions](Python-Regular-Expressions) Match function
- [Collections of Users](Collections-of-Users)
- [Definitions](#definitions)
- [Admin Console User Info](#admin-console-user-info)
- [Passwords](#passwords)
- [Password Notification](#password-notification)
- [Define schema fields](#define-schema-fields)
- [Clear schema fields](#clear-schema-fields)
- [Create a user](#create-a-user)
  - [Verify mailbox creation](#verify-mailbox-creation)
- [Update a user](#update-a-user)
  - [Special case processing for update user](#special-case-processing-for-update-user)
  - [User attribute `replace <Tag> <UserReplacement>` processing](Tag-Replace)
  - [Update a user's name](#update-a-users-name)
  - [Update a user's password](#update-a-users-password)
  - [Update a user's primary email address](#update-a-users-primary-email-address)
  - [Update a user's attributes with JSON data](#update-a-users-attributes-with-JSON-data)
  - [Update a user's OU based on group membership](#update-a-users-OU-based-on-group-membership)
- [Delete or suspend users](#delete-or-suspend-users)
- [Undelete or unsuspend users](#undelete-or-unsuspend-users)
- [Display information about users](#display-information-about-users)
  - [Display information about a single user](#display-information-about-a-single-user)
  - [Display information about multiple users](#display-information-about-multiple-users)
- [Print user primary email addresses](#print-user-primary-email-addresses)
    - [Print no header row and primaryEmail for specified users](#print-no-header-row-and-primaryemail-for-specified-users)
    - [Print a header row and primaryEmail for all users](#print-a-header-row-and-primaryemail-for-all-users)
- [Print user details](#print-user-details)
    - [Print a header row and fields for selected users](#print-a-header-row-and-fields-for-selected-users)
    - [Print a header row and fields for users specified by `<UserTypeEntity>`](#print-a-header-row-and-fields-for-users-specified-by-UserTypeEntity)
- [Print user domain counts](#print-user-domain-counts)
    - [Print domain counts for users in a specific domain and/or selected by a query](#print-domain-counts-for-users-in-a-specific-domain-and-or-selected-by-a-query)
    - [Print domain counts for users specified by `<UserTypeEntity>`](#print-domain-counts-for-users-specified-by-UserTypeEntity)

## API documentation
* https://developers.google.com/admin-sdk/directory/reference/rest/v1/users
* https://developers.google.com/admin-sdk/directory/reference/rest/v1/schemas

## Name guidelines
* https://support.google.com/a/answer/9193374?hl=en

## Query documentation
* https://developers.google.com/admin-sdk/directory/v1/guides/search-users

## Quoting rules
Items in a list can be separated by commas or spaces; if an item itself contains a comma, a space or a single quote, special quoting must be used.
Typically, you will enclose the entire list in double quotes and quote each item in the list as detailed below.

- Items, separated by commas, without spaces, commas or single quotes in the items themselves
   * ```"item,item,item"```
- Items, separated by spaces, without spaces, commas or single quotes in the items themselves
   * ```"item item item"```
- Items, separated by commas, with spaces, commas or single quotes in the items themselves
   * ```"'it em','it,em',\"it'em\""```
- Items, separated by spaces, with spaces, commas or single quotes in the items themselves
   * ```"'it em' 'it,em' \"it'em\""```

For example, a list of queries for Org Units where the Org Unit names contain spaces:
```
queries  "\"orgUnitPath='/Students/Middle School'\",\"orgUnitPath='/Students/Lower School'\""
```

## Definitions
* [Command data from Google Docs/Sheets](Command-Data-From-Google-Docs-Sheets)
```
<UserGoogleDoc> ::=
        <EmailAddress> <DriveFileIDEntity>|<DriveFileNameEntity>|(<SharedDriveEntity> <SharedDriveFileNameEntity>)

<DeliverySetting> ::=
        allmail|
        abridged|daily|
        digest|
        disabled|
        none|nomail

<DomainName> ::= <String>(.<String>)+
<EmailAddress> ::=
        <String>@<DomainName> |
        <String> <<String>@<DomainName>> # The outer <> around <String>@<DomainName> are literal, e.g., IT Group<group@domain.com> 
<EmailAddressList> ::= "<EmailAddress>(,<EmailAddress>)*"

<GroupItem> ::= <EmailAddress>|<UniqueID>|<String>
<GroupList> ::= "<GroupItem>(,<GroupItem>)*"
<GroupRole> ::= owner|manager|member

<OrgUnitID> ::= id:<String>
<OrgUnitPath> ::= /|(/<String>)+

<QueryUser> ::= <String>
        See: https://developers.google.com/admin-sdk/directory/v1/guides/search-users
```
```
<UserFieldName> ::=
        addresses|address|
        agreedtoterms|agreed2terms|
        aliases|
        archived|
        changepasswordatnextlogin|changepassword|
        creationtime|
        customerid|
        deletiontime|
        email|emails|otheremail|otheremails|
        externalids|externalid|
        familyname|firstname|fullname|givenname|lastname|name|
        gender|
        id|
        ims|im|
        includeinglobaladdresslist|gal|
        ipwhitelisted|
        isdelegatedadmin|admin|isadmin|
        ismailboxsetup|
        isenforcedin2sv|is2svenforced|
        isenrolledin2sv|is2svenrolled|
        keyword|keywords|
        language|languages|
        lastlogintime|
        locations|location|
        noneditablealiases|aliases|nicknames|
        notes|note|
        organizations|organization|
        orgunitpath|org|ou|
        phones|phone|
        posixaccounts|posix|
        primaryemail|username|
        recoveryemail|
        recoveryphone|
        relations|relation|
        sshpublickeys|ssh|sshkeys|
        suspended|
        thumbnailphotourl|photo|photourl|
        websites|website
<UserFieldNameList> ::= "<UserFieldName>(,<UserFieldName>)*"

<UserOrderByFieldName> ::=
        familyname|lastname|givenname|firstname|email
```
```
<LanguageCode> ::=
        ach|af|ag|ak|am|ar|az|be|bem|bg|bn|br|bs|ca|chr|ckb|co|crs|cs|cy|da|de|
        ee|el|en|en-gb|en-us|eo|es|es-419|et|eu|fa|fi|fil|fo|fr|fr-ca|fy|
        ga|gaa|gd|gl|gn|gu|ha|haw|he|hi|hr|ht|hu|hy|ia|id|ig|in|is|it|iw|ja|jw|
        ka|kg|kk|km|kn|ko|kri|ku|ky|la|lg|ln|lo|loz|lt|lua|lv|
        mfe|mg|mi|mk|ml|mn|mo|mr|ms|mt|my|ne|nl|nn|no|nso|ny|nyn|oc|om|or|
        pa|pcm|pl|ps|pt-br|pt-pt|qu|rm|rn|ro|ru|rw|
        sd|sh|si|sk|sl|sn|so|sq|sr|sr-me|st|su|sv|sw|
        ta|te|tg|th|ti|tk|tl|tn|to|tr|tt|tum|tw|
        ug|uk|ur|uz|vi|wo|xh|yi|yo|zh-cn|zh-hk|zh-tw|zu
<Language> ::=
        <Language>[+|-]|
        <String>
<LanguageList> ::= "<Language>(,<Language>)*"
```
```
<UserBasicAttribute> ::=
        (archived <Boolean>)|
        (changepassword|changepasswordatnextlogin <Boolean>)|
        (base64-md5|base64-sha1|crypt|sha|sha1|sha-1|md5|nohash)|
        (customerid <String>)|
        (email|primaryemail|username <EmailAddress>)|
        (firstname|givenname <String>)|
        (gal|includeinglobaladdresslist <Boolean>)|
        (gender clear|(female|male|unknown|(other <String>) [addressmeas <String>]))|
        (ipwhitelisted <Boolean>)|
        (language clear|<LanguageList>)|
        (lastname|familyname <String>)|
        (note clear|([text_html|text_plain] <String>|
                                            (file|htmlfile <FileName> [charset <Charset>])|
                                            (gdoc|ghtml <UserGoogleDoc>)))|
        (org|ou|orgunitpath <OrgUnitPath>|<OrgUnitID>)
        (password (random [<Integer>])|(uniquerandom [<Integer>])|blocklogin|<Password>)|
        (recoveryemail <EmailAddress>)|
        (recoveryphone <string>)|
        (suspended <Boolean>)|
        (<SchemaName>.<FieldName> [scalarnonempty|
                                   [multivalued|multivalue|value|multinonempty [type home|other|work|(custom <String>)]]]
                                  <String>)
```
```
<UserMultiAttribute> ::=
        (address type home|other|work|(custom <String>)
                [unstructured|formatted <String>]
                [pobox <String>] [extendedaddress <String>] [streetaddress <String>]
                [locality <String>] [region <String>] [postalcode <String>]
                [country <String>] [countrycode <String>]
                notprimary|primary)|
        (otheremail home|other|work|<String> <String>)|
        (externalid account|customer|login_id|network|organization|<String> <String>)|
        (im type home|other|work|(custom <String>)
                protocol aim|gtalk|icq|jabber|msn|net_meeting|qq|
                skype|yahoo|(custom_protocol <String>) <String>
                notprimary|primary)|
        (keyword mission|occupation|outlook|(custom <string>) <String>)|
        (location [type default|desk|<String>] area <String>
                [building|buildingid <String>] [floor|floorname <String>]
                [section|floorsection <String>] [desk|deskcode <String>] endlocation)|
        (organization [type domain_only|school|unknown|work] [customtype <String>]
                [name <String>] [title <String>] [department <String>]
                [symbol <String>] [costcenter <String>] [location <String>]
                [description <String>] [domain <String>]
                [fulltimeequivalent <Integer>]
                notprimary|primary)|
        (phone [type assistant|callback|car|company_main|grand_central|home|
                home_fax|isdn|main|mobile|other|other_fax|pager|radio|telex|tty_tdd|
                work|work_fax|work_mobile|work_pager|(custom <String>)]
                [value <String>]
                notprimary|primary)|
        (posix username <String> uid <Integer> gid <Integer> [system|systemid <String>]
                [home|homedirectory <String>] [shell <String>]
                [gecos <String>] [os|operatingSystemType linux|unspecified|windows]
                [primary <Boolean>] endposix)|
        (relation admin_assistant|assistant|brother|child|domestic_partner|
                dotted-line_manager|exec_assistant|father|friend|manager|mother|
                parent|partner|referred_by|relative|sister|spouse|<String> <String>)|
        (sshkeys key <String> [expires <Integer>] endssh)|
        (website app_install_page|blog|ftp|home|home_page|other|
                profile|reservations|resume|work|<String> <URL>
                notprimary|primary)

<UserClearAttribute> ::=
        (address clear)|
        (otheremail clear)|
        (externalid clear)|
        (im clear)|
        (keyword clear)|
        (location clear)|
        (organization clear)|
        (phone clear)|
        (posix clear)|
        (relation clear)|
        (sshkeys clear)|
        (website clear)
```
```
<UserAttribute> ::=
        (json [charset <Charset>] <JSONData>)|(json file <FileName> [charset <Charset>])|
        <UserBasicAttribute>|
        <UserMultiAttribute>|
        <UserClearAttribute>
```
## Admin Console User Info
When defining a user in the admin console, there is a section labelled `Employee information` with the following items:
* `Employee ID`
* `Job title`
* `Type of employee`
* `Manager's email`
* `Department`
* `Cost center`
* `Building id`
* `Floor name`
* `Floor section`

Here is how that data is represented in GAM:
```
Locations:
  type: desk
    area: desk
    buildingId: Building-ID
    buildingName: Building name
    floorName: Floor name
    floorSection: Floor section
Organizations:
  customType:
    description: Type of Employee
    costCenter: Cost center
    department: Department
    title: Job Title
    primary: True
Relations:
  type: manager
    value: manageremail@domain.com
External IDs:
  type: organization
    value: Employee ID
```
These options will set those values:
```
location type desk area desk buildingid Building-ID floorname "Floor name" floorsection "Floor section" endlocation
organization customtype "" description "Type of employee" costcenter "Cost center" department "Department" title "Job Title" primary
relation manager manageremail@domain.com
externalid organization "Employee ID"

```
## Passwords
To set a user's password, you specify a `<Password>` string and a hash method that specifies how to interpret the string
* `password random|uniquerandom` - A 25 character plain text string of ASCII uppercase/lowecase letters, digits and punctuation
  * Do not specify a hash method, the string will be hashed with Crypt before being passed to Google
* `password random <Integer>|uniquerandom <Integer>` - An `<Integer>` length plain text string of ASCII uppercase/lowecase letters, digits and punctuation
  * `<Integer>` must be between 8 and 100
  * Do not specify a hash method, the string will be hashed with Crypt before being passed to Google
* `password blocklogin` - A 4096 character string comprised of random Unicode characters; it's purpose is to create a password that blocks logins
* `password <Password>` - A string of characters; if no hash method is specified, `<Password>` is assumed to be plain text and is hashed with Crypt before being passed to Google
  * `base64-md5` - `<Password>` is a string hashed with MD5 and Base64 encoded
  * `base64-sha1` - `<Password>` is a string hashed with SHA1 and Base64 encoded
  * `crypt` - `<Password>` is a string hashed with Crypt
  * `md5` - `<Password>` is a string hashed with MD5
  * `sha|sha1|sha-1` - `<Password>` is a string hashed with SHA1
  * `nohash` - `<Password>` is plain text and will be passed to Google as such; not recommended

All of the following specifiy the password `helloworld`.
```
password "helloworld"
password "/F4DjTilcDIIVEHn/nAQsA==" base64-md5
password "at+xg6SiyUovktq1redipHiJpaE=" base64-sha1
password "quNTaKHn/QNxM" crypt
password "fc5e038d38a57032085441e7fe7010b0" md5
password "6adfb183a4a2c94a2f92dab5ade762a47889a5a1" sha1
password "helloworld" nohash
```

## Password Notification
When creating a user or updating a user's password, you can send a message with details to an email address; this might be the user's secondary email address.
```
notify <EmailAddressList>
[subject <String>]
[message|htmlmessage <String>|(file|htmlfile <FileName> [charset <CharSet>])|(gdoc|ghtml <UserGoogleDoc>)] [html [<Boolean>]]
(replace <Tag> <UserReplacement>)*
[notifypassword <String>]
[notifyonupdate [<Boolean>]]
```
* `notify <EmailAddressList>` - Specify recipients

If subject is not specified, the following value will be used:
* create - `Welcome to #domain#`
* update - `Account #user# password has been changed`

If message is not specified, the following value will be used:
* create - `Hello #givenname# #familyname#,\n\nYou have a new account at #domain#\nAccount details:\n\nUsername\n#user#\n\nPassword\n#password#\n\n
    Start using your new account by signing in at\nhttps://www.google.com/accounts/AccountChooser?Email=#user#&continue=https://workspace.google.com/dashboard\n`
* update - `The account password for #givenname# #familyname#, #user# has been changed to: #password#\n`

In the subject and message, these strings will be replaced with the specified values:
* `#givenname#` - first/given name
* `#familyname#` - last/family name
* `#email#` - user's email address
* `#user#` - user's email address
* `#username#` - portion of user's email address before @
* `#domain#` - portion of user's email after after @
* `#password#` - password

Use `\n` in `message <String>` to indicate a line break; no other special characters are recognized.

You can use `replace <Tag> <UserReplacement>` to provide additional information in the message and subject.
Note that the only user field values that are available are those specified in the command; in particular,
`name/fullname` is not available.

If you want a language/organization specific message, use a template file: `message file <FileName> [charset <CharSet>]`

When no hash method is specified or hash method `nohash` is specified, the `<Password>` string can be sent in the notification.

When you specify a hash method, the `<Password>` string is not interpretable by the user; you should use the following option:
* `notifiypassword <String>` - `<String>`, which should be the plain text version of `<Password>`, is sent in the notification

If `<Password>` is hashed and you don't set `notifiypassword <String>`, `Contact administrator for password` is sent in the notification.

By default, when options `notify <EmailAddressList> notifypassword <String>` are specified, an email notification
is sent when the user is updated or created. Use `notifyonupdate false` to suppress the notification on an update.

The email is sent from the admin user identified in oauth2.txt, `gam oauth info` will show the value.
Gam gets no indication as to the status of the message delivery; the admin user user will get a non-delivery receipt if the message could not be sent to the `notify <EmailAddressList>`.

By default, messages are sent as plain text, use `html` or `html true` to indicate that the message is HTML.

## Define schema fields
You can set custom schema field values for users; schema fields can be scalar, a single value, or can be multivalued.
* https://developers.google.com/admin-sdk/directory/reference/rest/v1/schemas

Schema fields can have one of seven types:
* `bool` - `true` and `yes` are interpreted as `True`, all other values, including an empty value, are interpreted as `False`
* `date` - Three valid formats; can not be empty
  * `YYYY` - Interpreted as `YYYY-01-01`
  * `YYYY-MM` - Interpreted as `YYYY-MM-01`
  * `YYYY-MM-DD` - Intrepreted as `YYYY-MM-DD`
* `double` - A floating point number; can not be empty
* `email` - An email address, must be in the format `<String>@<DomainName>`; can not be empty
* `int64` - A 64-bit integer value; can not be empty
* `phone` - A phone number; can be empty
* `string` - A string; can be empty

### Scalar fields
```
<SchemaName>.<FieldName> [scalarnonempty] <String>
```
If you don't specify `scalarnonempty`, an empty value will be set for `phone` amd `string`, `False` will be set for `bool`
and an error will be generated for `date`, `double`, `email` and `int64`.

If you specify `scalarnonempty`, empty values will be suppressed. This is most useful when read files values from a CSV file.

For example, to suppress errors when empty values would cause an error or are simply undesirable:
```
GeoData.Region scalarnonempty ~region GeoData.State scalarnonempty ~state GeoData.City scalarnonempty ~city
```
### Multivalued fields
```
<SchemaName>.<FieldName> [multivalued|multivalue|value|multinonempty [type home|other|work|(custom <String>)]]]
                         <String>
```
If you specify `multivalued|multivalue|value`, an empty value will be set for `phone` amd `string`, `False` will be set for `bool`
and an error will be generated for `date`, `double`, `email` and `int64`.

If you specify `multinonempty`, empty values will be suppressed.

Multivalued fields can specify a type; there are predefined types `home`, `work` and `other` or you can specify `custom <String>`.
If you don't specify a type, `work` is assumed.

For example:
```
ContactNumber.Work multivalued type work "800-123-4567" ContactNumber.Home multivalued type home "510-987-6543" ContactNumber.Cell type custom cell "501-345-6789"
```

## Clear schema fields
You can clear custom schema field values when updating a user.

Clear all fields in a schema:
```
clearschema <SchemaName>
```
Clear a specific field in a schema:
```
clearschema <SchemaName>.<FieldName>
```

## Create a user
```
gam create user <EmailAddress> [ignorenullpassword] <UserAttribute>*
        (groups [<GroupRole>] [[delivery] <DeliverySetting>] <GroupEntity>)*
        [alias|aliases <EmailAddressList>]
        [notify <EmailAddressList>] [subject <String>] [notifypassword <String>]
            [(message|htmlmessage <String>)|(file|htmlfile <FileName> [charset <CharSet>])|
             (gdoc|ghtml <UserGoogleDoc>)] [html [<Boolean>]]
        (replace <Tag> <UserReplacement>)*
        [lograndompassword <FileName>]
```
The user will be added to the groups specified by `groups [<GroupRole>] [[delivery] <DeliverySetting>] <GroupEntity>`.

The user aliases in `alias|aliases <EmailAddressList>` will be created.

In version 6.11.03 and later, you can specify preferred languages that will be reflected
in the user's profile. In `languages <LanguageList>`, append a `+` to `<Language>` to indicate
that is it `preferred` and a `-` to set `non_preferred`. No suffix indiates that there is no preference.
A `<Language>` in `<LanguageList>` that is not a `<LanguageCode>` is a custom language and can not have
a preference suffix. In the user's profile, only `preferred` languages are displayed.

When creating a user, you can send a message with the account details to an email address; this might be the user's secondary email address.

If you create a user with `random password`, the `lograndompassword <FileName>` option causes GAM
to append the user email address and random password to `<FileName>`. If `<FileName>` is `-`, the data is written to stdout.

Option `ignorenullpassword` causes GAM to ignore options like `password ""` or `password ~password` where the
CSV entry `password` is null; it must appear in the command before any null passwords.
If `ignorenullpassword` and a null password are entered, the user will be assigned a random password.

See [Password Notification](#password-notification)
```
gam create user user@domain.com firstname "First" lastname "Last" password "newpassword" notify user@home.com
```

### Create users in bulk with password notifications to user and help desk
This command should be on a single line, it is wrapped here for clarity.
```
gam redirect stdout CreateUsers.log multiprocess redirect stderr stdout csv CreateUsers.csv
     gam create user "~useremail" firstname "~firstname" lastname "~lastname" ou "~ou" password "~password"
     notify "~~notifyemail~~,helpdesk@domain.com"
```

## Verify mailbox creation
Creating a user is usually instantaneous but you can verify that a new user's mailbox has been setup.
```
gam <UserTypeEntity> waitformailbox [retries <Number>]
```
If `retries <Number>` is not specified, the command will keep retrying until the mailbox is setup or you hit Control-C.

If `retries <Number>` is specified, the command will keep retrying until the mailbox is setup or the retries are exhausted.
If the mailbox is setup, a zero return code is returned; if the retries are exhausted, a non-zero return code will be returned.


## Update a user
```
gam update user <UserItem> [ignorenullpassword] <UserAttribute>* [noactionifalias]
        [updateprimaryemail <RegularExpression> <EmailReplacement>]
        [updateoufromgroup <FileName> [charset <CharSet>]
            [columndelimiter <Character>] [quotechar <Character>]
            [fields <FieldNameList>] [keyfield <FieldName>] [datafield <FieldName>]]
        [clearschema <SchemaName>] [clearschema <SchemaName>.<FieldName>]
        [createifnotfound] [notfoundpassword random|<Password>]
        (groups [<GroupRole>] [[delivery] <DeliverySetting>] <GroupEntity>)*
        [alias|aliases <EmailAddressList>]
        [notify <EmailAddressList>] [subject <String>] [notifypassword <String>]
            [(message|htmlmessage <String>)|(file|htmlfile <FileName> [charset <CharSet>])|
             (gdoc|ghtml <UserGoogleDoc>)] [html [<Boolean>]]
        [notifyonupdate [<Boolean>]] [setchangepasswordoncreate [<Boolean>]]
        (replace <Tag> <UserReplacement>)*
        [lograndompassword <FileName>]
gam update users <UserTypeEntity> [ignorenullpassword] <UserAttribute>* [noactionifalias]
        [updateprimaryemail <RegularExpression> <EmailReplacement>]
        [updateoufromgroup <FileName> [charset <CharSet>]
            [columndelimiter <Character>] [quotechar <Character>]
            [fields <FieldNameList>] [keyfield <FieldName>] [datafield <FieldName>]]
        [clearschema <SchemaName>] [clearschema <SchemaName>.<FieldName>]
        [createifnotfound] [notfoundpassword random|<Password>]
        (groups [<GroupRole>] [[delivery] <DeliverySetting>] <GroupEntity>)*
        [alias|aliases <EmailAddressList>]
        [notify <EmailAddressList>] [subject <String>] [notifypassword <String>]
            [(message|htmlmessage <String>)|(file|htmlfile <FileName> [charset <CharSet>])|
             (gdoc|ghtml <UserGoogleDoc>)] [html [<Boolean>]]
        [notifyonupdate [<Boolean>]] [setchangepasswordoncreate [<Boolean>]]
        (replace <Tag> <UserReplacement>)*
        [lograndompassword <FileName>]
gam <UserTypeEntity> update users [ignorenullpassword] <UserAttribute>* [noactionifalias]
        [updateprimaryemail <RegularExpression> <EmailReplacement>]
        [updateoufromgroup <FileName> [charset <CharSet>]
            [columndelimiter <Character>] [quotechar <Character>]
            [fields <FieldNameList>] [keyfield <FieldName>] [datafield <FieldName>]]
        [clearschema <SchemaName>] [clearschema <SchemaName>.<FieldName>]
        [createifnotfound] [notfoundpassword random|<Password>]
        (groups [<GroupRole>] [[delivery] <DeliverySetting>] <GroupEntity>)*
        [alias|aliases <EmailAddressList>]
        [notify <EmailAddressList>] [subject <String>] [notifypassword <String>]
            [(message|htmlmessage <String>)|(file|htmlfile <FileName> [charset <CharSet>])|
             (gdoc|ghtml <UserGoogleDoc>)] [html [<Boolean>]]
        [notifyonupdate [<Boolean>]] [setchangepasswordoncreate [<Boolean>]]
        (replace <Tag> <UserReplacement>)*
        [lograndompassword <FileName>]
```

When `noactionifalias` is specified, no action is performed if `<UserItem>` or `<UserTypeEntity>` specifies an alias rather than a primary email address.

**Note that when `changepassword true` is specified, the user is immediately logged out.**

The `groups [<GroupRole>] [[delivery] <DeliverySetting>] <GroupEntity>` option only applies if `createifnotfound` is specified and the user has to be created; see below.

The  `alias|aliases <EmailAddressList>` only applies if `createifnotfound` is specified and the user has to be created; see below.

In version 6.11.03 and later, you can specify preferred languages that will be reflected
in the user's profile. In `languages <LanguageList>`, append a `+` to `<Language>` to indicate
that is it `preferred` and a `-` to set `non_preferred`. No suffix indiates that there is no preference.
A `<Language>` in `<LanguageList>` that is not a `<LanguageCode>` is a custom language and can not have
a preference suffix. In the user's profile, only `preferred` languages are displayed.

## Special case processing for update user

Some information systems output a CSV file of user data that can be used to create Google users but there is no indication as to which users are new. If you try to create all of
the users you'll get `duplicate` errors for the existing users; if you try to update all of the users you'll get `not found` errors for the new users.
The `createifnotfound` option causes Gam to create the new users if the `givenname`, `familyname` and `password` options are specified and `<UserItem>` or `<UserTypeEntity>` specify a single user.
The user will be added to the groups specified by `groups <GroupRole> <GroupList>`.
The user aliases in `alias|aliases <EmailAddressList>` will be created.

For example, you are given a CSV file Users.csv with these headers: email,firstname,lastname,password,ou,altemail
```
gam csv Users.csv gam update user ~email firstname ~firstname lastname ~lastname password ~password ou ~ou createifnotfound notify ~altemail
```
The existing users (including their passwords) will be updated and the new users will be created; if `notify` is specified, a notification email message is sent as in (#create-a-user).

If you don't want to update the passwords of the existing users but must supply a password for newly created users, use the `notfoundpassword` option.
```
gam csv Users.csv gam update user ~email firstname ~firstname lastname ~lastname notfoundpassword ~password ou ~ou createifnotfound notify ~altemail
```
The existing users (but not their passwords) will be updated and the new users will be created; if `notify` is specified, a notification email message is sent as in (#create-a-user).

If you don't want to force a password change of the existing users but do want newly created users to change their password, use the `setchangepasswordoncreate` option.
```
gam csv Users.csv gam update user ~email firstname ~firstname lastname ~lastname notfoundpassword ~password ou ~ou createifnotfound notify ~altemail setchangepasswordoncreate true
```

## Update a user's name
When updating a user's name, always update both the `firstname/givenname` and the `lastname/familyname` fields. If you only update one of the fields, the other will be cleared.

## Update a user's password
When updating a user's password, you can send a message with the new password to an email address; this might be the user's secondary email address.

In versions of GAMADV-XTD3 prior to 5.07.00, if you do `gam update users <UserTypeEntity>` or `gam <UserTypeEntity> update users` and
specify `password random`, all of the users in `<UserTypeEntity>` are assigned the same random password;
this is the same behavior as in Standard GAM. If you would like each of the users in `<UserTypeEntity>` to be
assigned a unique random password, specify `password uniquerandom`.

If you update a user with `password random|uniquerandom`, the `lograndompassword <FileName>` option causes GAM
to append the user email address and random password to `<FileName>`. If `<FileName` is `-`, the data is written to stdout.

Option `ignorenullpassword` causes GAM to ignore options like `password ""` or `password ~password` or `notfoundpassword ~password` where the
CSV entry `password` is null; it must appear in the command before any null passwords.
This option would typically be used when processing CSV files where only selected user's passwords are being updated.

See [Password Notification](#password-notification)
```
gam update user user@domain.com password "newpassword" notify user@home.com
```
## Update a user's primary email address
You can simply update a user's primary email address with the `primaryemail` option.
```
gam update user userold@domain.com primaryemail usernew@domain.com
```
The `updateprimaryemail <RegularExpression> <EmailReplacement>` option allows modification of the user's current primary email address.

For example, to change the domain of a set of users from the current domain to newdomain.com:
```
gam ou /Path/To/Ou update user updateprimaryemail "^(.+)@.*$" "\1@newdomain.com"
```
To change graduating students email addresses from flastname@domain.com to flastname_grad@domain.com:
```
gam ou /Path/To/Ou update user updateprimaryemail "^(.+)@(.+)$" "\1_grad@\2"
```
If the user's current primary email address does not match the <RegularExpression> then no modification is made.

## Update a user's attributes with JSON data
Users's have attributes that can take multiple values: `<UserMultiAttribute>`. Any time one of these attributes is updated,
the API requires that all values be presented; this makes it difficult to add/delete/update a single value as you have to
present all of the other values. The `json [charset <Charset>] <JSONData>` and `json file <FileName> [charset <Charset>]`
options can simplify this process. For example, a user has multiple phone numbers and you have to update their mobile number.
```
$ gam info user user@domain.com phones nogroups nolicenses
User: user@domain.com
  Settings:
  Phones:
    type: work
      primary: True
      value: 510-555-1211
    type: home
      value: 510-555-1212
    type: mobile
      value: 510-555-1213
$ gam redirect stdout ./phones.json info user user@domain.com phones formatjson nogroups nolicenses
$ more phones.json
{"phones": [{"primary": true, "type": "work", "value": "510-555-1211"}, {"type": "home", "value": "510-555-1212"}, {"type": "mobile", "value": "510-555-1213"}], "primaryEmail": "user@domain.com"}
```
Edit phones.json and change the mobile number; update.
```
$ more phones.json
{"phones": [{"primary": true, "type": "work", "value": "510-555-1211"}, {"type": "home", "value": "510-555-1212"}, {"type": "mobile", "value": "510-555-1214"}], "primaryEmail": "user@domain.com"}
$ gam update user user@domain.com json file phones.json
User: user@domain.com, Updated
$ gam info user user@domain.com phones nogroups nolicenses
User: user@domain.com
  Settings:
  Phones:
    type: work
      primary: True
      value: 510-555-1211
    type: home
      value: 510-555-1212
    type: mobile
      value: 510-555-1214
```
If you want to update a group of user's work phone number, follow this process.

Backup the current settings.
```
$ gam redirect csv ./phones.csv group group@domain.com print users phones formatjson quotechar "'"
```
Edit phones.csv and change the work number; update.
```
$ gam csv ./phones.csv quotechar "'" gam update user ~primaryEmail json ~JSON
```
## Update a user's OU based on group membership
This option would typically be used when an external service creates a Google user and assigns it to a group but does not place it in an OU.
You provide a CSV file that associates OU paths with group email addresses:
* Each group can only reference one OU
* Multiple groups can reference the same OU

### Sample CSV file GroupOrgUnitMap.csv
```
Group,OrgUnit
groupx1@domain.com,/Path/To/OUx
groupx2@domain.com,/Path/To/OUx
groupy@domain.com,/Path/To/OUy
groupz@domain.com,/Path/To/OUz
```
No update is performed if a user does not belong to any group in the CSV file or belongs to multiple groups in the CSV file.

```
[updateoufromgroup <FileName> [charset <CharSet>]
    [columndelimiter <Character>] [quotechar <Character>]
    [fields <FieldNameList>] [keyfield <FieldName>] [datafield <FieldName>]]
```
* `<FileName>` - A CSV file containing rows with columns of items
* `columndelimiter <Character>` - Columns are  separated by `<Character>`; if not specified, the value of `csv_input_column_delimiter` from `gam.cfg` will be used
* `quotechar <Character>` - The column quote characer is `<Character>`; if not specified, the value of `csv_input_quote_char` from `gam.cfg` will be used
* `fields <FieldNameList>` - The column headings of a CSV file that does not contain column headings
* `keyfield <FieldName>` - The column heading of the group column; the default is Group
* `datafield <FieldName>` - The column heading of the OU path column; the default is OrgUnit

### Example using the CSV file GroupOrgUnitMap.csv:
```
gam update user user@domain.com updateoufromgroup GroupOrgUnitMap.csv
```
## Delete or suspend users
These commands operate on a single user.
```
gam delete user <UserItem> [noactionifalias]
gam suspend user <UserItem> [noactionifalias]
```
These commands operate on multiple users.
```
gam delete users <UserTypeEntity> [noactionifalias]
gam suspend users <UserTypeEntity> [noactionifalias]

gam <UserTypeEntity> delete users [noactionifalias]
gam <UserTypeEntity> suspend users [noactionifalias]
```

When `noactionifalias` is specified, no action is performed if `<UserItem>`, `<UserEntity>` or `<UserTypeEntity>` specifies an alias rather than a primary email address.

## Undelete or unsuspend users
These commands operate on a single user.
```
gam undelete user <UserItem> [ou|org|orgunit <OrgUnitPath>]
gam unsuspend user <UserItem> [noactionifalias]
```
These commands operate on multiple users.
```
gam undelete users <UserEntity> [ou|org|orgunit <OrgUnitPath>]
gam unsuspend users <UserTypeEntity> [noactionifalias]

gam <UserEntity> undelete users [ou|org|orgunit <OrgUnitPath>]
gam <UserTypeEntity> unsuspend users [noactionifalias]
```

An undeleted user will be returned to their original OU, use `ou|org|orgunit <OrgUnitPath>` to specify a different OU.

When `noactionifalias` is specified, no action is performed if `<UserItem>`, `<UserEntity>` or `<UserTypeEntity>` specifies an alias rather than a primary email address.

## Display information about users
### Display information about a single user
```
gam info user [<UserItem>]
        [quick]
        [noaliases|aliases]
        [nobuildingnames|buildingnames]
        [nogroups|groups|grouptree]
        [nolicenses|nolicences|licenses|licences]
        [noschemas|allschemas|(schemas|custom|customschemas <SchemaNameList>)]
        [userview] <UserFieldName>* [fields <UserFieldNameList>]
        [(products|product <ProductIDList>)|(skus|sku <SKUIDList>)] [formatjson]
```
### Display information about multiple users
```
gam info users <UserTypeEntity>
        [quick]
        [noaliases|aliases]
        [nobuildingnames|buildingnames]
        [nogroups|groups|grouptree]
        [nolicenses|nolicences|licenses|licences]
        [noschemas|allschemas|(schemas|custom|customschemas <SchemaNameList>)]
        [userview] <UserFieldName>* [fields <UserFieldNameList>]
        [(products|product <ProductIDList>)|(skus|sku <SKUIDList>)] [formatjson]
gam <UserTypeEntity> info users
        [quick]
        [noaliases|aliases]
        [nobuildingnames|buildingnames]
        [nogroups|groups|grouptree]
        [nolicenses|nolicences|licenses|licences]
        [noschemas|allschemas|(schemas|custom|customschemas <SchemaNameList>)]
        [userview] <UserFieldName>* [fields <UserFieldNameList>]
        [(products|product <ProductIDList>)|(skus|sku <SKUIDList>)] [formatjson]
```
Unlike all other GAM commands, a `<UserTypeEntity>` value of `all users` is actually `all users_ns_susp` not `all users_ns`.
This is backwards compatibilty issue.

Starting in version `5.23.01`, the variable `quick_info_user` was added to `gam.cfg` to control how much information requiring additional API calls is displayed.
(Prior to version `5.23.01`, assume `quick_info_user = False`.)

`quick_info_user = False`: Gam makes additional API calls to get more information; you can selectively eliminate these calls to improve performance.

* `noaliases` - Do not get alias information
* `nobuildingnames` - Do not get building names for locations
* `nogroups` - Do not get group membership information
* `nolicenses|nolicences` - Do not get license information
* `noschemas` - Do not get custom schema information, no additional API call is made but less data is downloaded
* `quick` - Equivalent to `noaliases nobuildingnames nogroups nolicenses noschemas`

`quick_info_user = true`: none of the additional API calls are made; these new options enable display of the additional information.
* `aliases` - Display aliases
* `buildingnames` - Display building names in locations
* `groups` - Display groups of which the user is a direct member
* `grouptree` - Display groups of which the user is a direct member and those groups parent groups. This requires an Enterprise license
* `licenses` - Display licenses for all SKUs
* `allschemas` - Display all custom schemas

These existing options enable the display of additional information.
* `schemas|custom|customschemas <SchemaNameList>` - Display the specified custom schemas
* `(products|product <ProductIDList>)|(skus|sku <SKUIDList>)` - Display license information for a selected list of products/SKUs.

By default, Gam displays fields that only an adminstrator can view.
* `userview` - Only display fields that other users in the domain can view.

By default, Gam displays all fields for a user.
* `<UserFieldName>* [fields <UserFieldNameList>]` - Only display selected fields.

By default, Gam displays the information as an indented list of keys and values.
* `formatjson` - Display the fields in JSON format.

## Print user primary email addresses
### Print no header row and primaryEmail for specified users
```
gam <UserTypeEntity> print
gam <UserTypeEntity> print users
```

### Print a header row and primaryEmail for all users
```
gam print users
```

## Print user details
### Print a header row and fields for selected users

See: https://developers.google.com/admin-sdk/directory/v1/guides/search-users
```
gam print users [todrive <ToDriveAttribute>*]
        ([domain <DomainName>] [(query <QueryUser>)|(queries <QueryUserList>)]
         [limittoou <OrgUnitPath>|<OrgUnitID>] [deleted_only|only_deleted])
        [orderby <UserOrderByFieldName> [ascending|descending]]
        [groups|groupsincolumns] [license|licenses|licence|licences]
	[schemas|custom|customschemas all|<SchemaNameList>]
        [emailpart|emailparts|username]
        [userview] [allfields|basic|full|(<UserFieldName>*|fields <UserFieldNameList>)]
        [delimiter <Character>] [sortheaders [<Boolean>]] [scalarsfirst [<Boolean>]]
        [formatjson [quotechar <Character>]] [quoteplusphonenumbers]
        [issuspended <Boolean>]
```

By default, users in all domains in the account are selected; these options allow selection of subsets of users:
* `domain <DomainName>` - Limit users to those in `<DomainName>`
* `(query <QueryUser>)|(queries <QueryUserList>)` - Limit users to those that match a query
* `limittoou <OrgUnitPath>|<OrgUnitID>` - Limit users to those in the specified `<OrgUnitPath>|<OrgUnitID>`
* `deleted_only|only_deleted` - Only display deleted users
* `issuspended <Boolean>` - Limit users based on their status

### Print a header row and fields for users specified by `<UserTypeEntity>`
```
gam print users [todrive <ToDriveAttribute>*] select <UserTypeEntity>
        [orderby <UserOrderByFieldName> [ascending|descending]]
        [groups|groupsincolumns] [license|licenses|licence|licences]
	[schemas|custom|customschemas all|<SchemaNameList>]
        [emailpart|emailparts|username][schemas|custom all|<SchemaNameList>]
        [userview] [allfields|basic|full|(<UserFieldName>*|fields <UserFieldNameList>)]
        [delimiter <Character>] [sortheaders [<Boolean>]] [scalarsfirst [<Boolean>]]
        [formatjson [quotechar <Character>]] [quoteplusphonenumbers]
        [issuspended <Boolean>]
gam <UserTypeEntity> print users [todrive <ToDriveAttribute>*]
        [orderby <UserOrderByFieldName> [ascending|descending]]
        [groups|groupsincolumns] [license|licenses|licence|licences]
	[schemas|custom|customschemas all|<SchemaNameList>]
        [emailpart|emailparts|username]
        [userview] [allfields|basic|full|(<UserFieldName>*|fields <UserFieldNameList>)]
        [delimiter <Character>] [sortheaders [<Boolean>]] [scalarsfirst [<Boolean>]]
        [formatjson [quotechar <Character>]] [quoteplusphonenumbers]
        [issuspended <Boolean>]
```

By default, Gam gets no group membership information for each user. The `groups` and `groupsincolumns`
will group membership information; an additional API call per user is required

With `groups`, there will be two columns displayed: `GroupsCount` and `Groups`.
* `GroupsCount` - The number of groups to which the user belongs
* `Groups` - A list of group email addresses

With `groupsincolumns` there will be multiple columns displayed: `Groups` and `Groups.<Number>`.
* `Groups` - The number of groups to which the user belongs
* `Groups.<Number>` - A single group email address

By default, Gam gets no license information for each  user.
* `license|licenses|licence|licences` - Get license information; an additional API call per user is required

By default, Gam displays the primary email address for each user.
* `emailpart|emailparts|username` - Output two additional columns, primaryEmailLocal and primaryEmailDomain, with the components of the primary email address.

By default, Gam displays fields that only an adminstrator can view.
* `userview` - Only display fields that other users in the domain can view.

By default, Gam displays only the primary email address for each user.
* `allfields|basic` - Display all non custom schema fields for each user.
* `full` - Display all non custom schema fields and all custom schema fields for each user.
* `<UserFieldName>* [fields <UserFieldNameList>]` - Only display selected fields.
* `schemas|custom all` - Get custom schema information for all schemas.
* `schemas|custom <SchemaNameList>` - Get custom schema information for a selected list of schemas.

By default, the entries in lists of groups and licenses are separated by the `csv_output_field_delimiter` from `gam.cfg`.
* `delimiter <Character>` - Separate list items with `<Character>`

In the output, primaryEmail is the always the first column; these options control the sorting of the remaining columns.
* `allfields|basic|full` - All other columns are sorted by name.
* `sortheaders [true]` - All other columns are sorted by name.
* `<UserFieldName>*|fields <UserFieldNameList>` - The columns appear in the order that the fields are specified.
* `scalarsfirst [true]` - When columns are sorted by name, scalar fields appear before repeating fields.

By default, Gam displays the information as columns of fields; the following option causes the output to be in JSON format,
* `formatjson` - Display the fields in JSON format.

When you perform `gam print users` with the following `todrive` options to update a sheet within a Google Sheets file:
`tdfileid <DriveFileID> tdsheet <SheetEntity> tdupdatesheet`
and your data includes international phone numbers that start with a plus sign, Google Sheets generates a `Formula parse error`
for those phone numbers. Use option `quoteplusphonenumbers` to have GAM add a single quote at the front
of phone numbers that begin with a plus sign to cause Google Sheets to interpret the numbers as plain text. The single
quote remains with the phone number. This option is not required when you're not updating a sheet as the error does not occur.

By default, when writing CSV files, Gam uses a quote character of double quote `"`. The quote character is used to enclose columns that contain
the quote character itself, the column delimiter (comma by default) and new-line characters. Any quote characters within the column are doubled.
When using the `formatjson` option, double quotes are used extensively in the data resulting in hard to read/process output.
The `quotechar <Character>` option allows you to choose an alternate quote character, single quote for instance, that makes for readable/processable output.
`quotechar` defaults to `gam.cfg/csv_output_quote_char`.

## Print user domain counts
Print a CSV file with headers `domain,count` that gives the number of users in each domain
### Print domain counts for users in a specific domain and/or selected by a query
```
gam print users [todrive <ToDriveAttribute>*]
        ([domain <DomainName>] [(query <QueryUser>)|(queries <QueryUserList>)]
         [limittoou <OrgUnitPath>|<OrgUnitID>] [deleted_only|only_deleted])
        [formatjson [quotechar <Character>]] [countonly]
        [issuspended <Boolean>]
```
By default, users in all domains in the account are selected; these options allow selection of subsets of users:
* `domain <DomainName>` - Limit users to those in `<DomainName>`
* `(query <QueryUser>)|(queries <QueryUserList>)` - Limit users to those that match a query
* `limittoou <OrgUnitPath>|<OrgUnitID>` - Limit users to those in the specified `<OrgUnitPath>|<OrgUnitID>`
* `deleted_only|only_deleted` - Only display deleted users
* `issuspended <Boolean>` - Limit users based on their status

### Print domain counts for users specified by `<UserTypeEntity>`
```
gam print users [todrive <ToDriveAttribute>*] select <UserTypeEntity>
        [formatjson [quotechar <Character>]] [countonly]
gam <UserTypeEntity> print users [todrive <ToDriveAttribute>*]
        [formatjson [quotechar <Character>]] [countonly]
```
By default, Gam displays the information as columns of fields; the following option causes the output to be in JSON format,
* `formatjson` - Display the fields in JSON format.

By default, when writing CSV files, Gam uses a quote character of double quote `"`. The quote character is used to enclose columns that contain
the quote character itself, the column delimiter (comma by default) and new-line characters. Any quote characters within the column are doubled.
When using the `formatjson` option, double quotes are used extensively in the data resulting in hard to read/process output.
The `quotechar <Character>` option allows you to choose an alternate quote character, single quote for instance, that makes for readable/processable output.
`quotechar` defaults to `gam.cfg/csv_output_quote_char`.

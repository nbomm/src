# Calendars - Access
- [Notes](#Notes)
- [API documentation](#api-documentation)
- [Definitions](#definitions)
- [Manage calendar access](#manage-calendar-access)
- [Display calendar access](#display-calendar-access)
- [Old format commands](#old-format-commands)

## Notes
These commands use Client access for all commands except those that reference user's primary calendars
where Service Account access is used. When using Client access on user's secondary calendars, some operations are restricted.
In general, you should use the following commands to manage user's calendars access.
* [Users - Calendars - Access](Users-Calendars-Access)

Client access works when accessing Resource calendars.

## API documentation
* https://developers.google.com/calendar/v3/reference/acl

## Definitions
```
<CalendarItem> ::= <EmailAddress>|<String>
<CalendarList> ::= "<CalendarItem>(,<CalendarItem>)*"
<CalendarEntity> ::= <CalendarList> | <FileSelector> | <CSVkmdSelector> | <CSVDataSelector>

<CalendarACLRole> ::= editor|freebusy|freebusyreader|owner|reader|writer
<CalendarACLScope> ::= <EmailAddress>|user:<EmailAdress>|group:<EmailAddress>|domain:<DomainName>|domain|default
<CalendarACLScopeList> ::= "<CalendarACLScope>(,<CalendarACLScope>)*"
<CalendarACLScopeEntity>::= <CalendarACLScopeList> | <FileSelector> | <CSVkmdSelector> | <CSVDataSelector>
```
## Manage calendar access
```
gam calendars <CalendarEntity> add acls|calendaracls <CalendarACLRole> <CalendarACLScopeEntity> [sendnotifications <Boolean>]
gam calendars <CalendarEntity> update acls|calendaracls <CalendarACLRole> <CalendarACLScopeEntity> [sendnotifications <Boolean>]
gam calendars <CalendarEntity> delete acls|calendaracls [<CalendarACLRole>] <CalendarACLScopeEntity>
```
By default, when you add or update a calendar ACL, notification is sent to the members referenced in the `<CalendarACLScopeEntity>`.
Use `sendnotifications false' to suppress sending the notification.

## Display calendar access
```
gam calendars <CalendarEntity> info acls|calendaracls <CalendarACLScopeEntity> [formatjson]
gam calendars <CalendarEntity> show acls|calendaracls [formatjson]
```
By default, Gam displays the information as an indented list of keys and values.
* `formatjson` - Display the fields in JSON format.
```
gam calendars <CalendarEntity> print acls|calendaracls [todrive <ToDriveAttribute>*] [formatjson [quotechar <Character>]]
```
By default, when writing CSV files, Gam uses a quote character of double quote `"`. The quote character is used to enclose columns that contain
the quote character itself, the column delimiter (comma by default) and new-line characters. Any quote characters within the column are doubled.
When using the `formatjson` option, double quotes are used extensively in the data resulting in hard to read/process output.
The `quotechar <Character>` option allows you to choose an alternate quote character, single quote for instance, that makes for readable/processable output.
`quotechar` defaults to `gam.cfg/csv_output_quote_char`.

### Old format commands
These commands are backwards compatible with basic GAM.
```
gam calendar <CalendarEntity> add <CalendarACLRole> ([user] <EmailAddress>)|(group <EmailAddress>)|(domain [<DomainName>])|default [sendnotifications <Boolean>]
gam calendar <CalendarEntity> update <CalendarACLRole> ([user] <EmailAddress>)|(group <EmailAddress>)|(domain [<DomainName>])|default [sendnotifications <Boolean>]
gam calendar <CalendarEntity> delete [<CalendarACLRole>] ([user] <EmailAddress>)|(group <EmailAddress>)|(domain [<DomainName>])|default
gam calendar <CalendarEntity> showacl [formatjson]
gam calendar <CalendarEntity> printacl [todrive <ToDriveAttribute>*] [formatjson [quotechar <Character>]]
```
By default, when you add or update a calendar ACL, notification is sent to the members referenced in the `<CalendarACLScopeEntity>`.
Use `sendnotifications false' to suppress sending the notification.

# Users - Tokens
- [API documentation](#api-documentation)
- [Collections of Users](Collections-of-Users)
- [Definitions](#definitions)
- [Delete a user's token](#delete-a-users-token)
- [Display a user's tokens](#display-a-users-tokens)

## API documentation
* https://developers.google.com/admin-sdk/directory/reference/rest/v1/tokens

## Definitions
```
<ClientID> ::= <String>
```
## Delete a user's token
```
gam <UserTypeEntity> delete|del token|tokens clientid <ClientID>
```
## Display a user's tokens
```
gam <UserTypeEntity> print tokens|token [todrive <ToDriveAttributes>*] [clientid <ClientID>]
        [orderby clientid|displaytext] [delimiter <Character>]
gam <UserTypeEntity> show tokens|token|3lo|oauth [clientid <ClientID>]
        [orderby clientid|displaytext]
gam print tokens|token [todrive <ToDriveAttributes>*] [clientid <ClientID>]
        [orderby clientid|displaytext] [delimiter <Character>]
        [<UserTypeEntity>]
```
By default, all client tokens for a user are displayed, use `clientid <ClientID>` to display a specific client token.

* `delimiter <Character>` - Separate `scopes` entries with `<Character>`; the default value is `csv_output_field_delimiter` from `gam.cfg`.

### Example
You want a list of all Google Apps being used by your users.

Serial processing
```
gam config csv_output_header_filter "^user$,displayText" redirect csv UserApps.csv [todrive <ToDriveAttributes>*] all users print tokens
```
* `config csv_output_header_filter "^user$,displayText"` - Select relevant columns
* `redirect csv UserApps.csv` - Specify CSV file
* `[todrive <ToDriveAttributes>*]` - Optional, upload CSV to Google Drive
* `all users print tokens` - Get the apps

Parallel processing
```
gam config auto_batch_min 1 num_threads 10 csv_output_header_filter "^user$,displayText" redirect csv UserApps.csv multiprocess [todrive <ToDriveAttributes>*] all users print tokens
```
* `config auto_batch_min 1 num_threads 10` - Turn on parallel processing
* `csv_output_header_filter "^user$,displayText"` - Select relevant columns
* `redirect csv UserApps.csv multiprocess` - Specify CSV file with parallel processing
* `[todrive <ToDriveAttributes>*]` - Optional, upload CSV to Google Drive
* `all users print tokens` - Get the apps

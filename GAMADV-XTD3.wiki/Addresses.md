# Addresses
- [API documentation](#api-documentation)
- [Display addresses](#display-addresses)

## API documentation
* https://developers.google.com/admin-sdk/directory/reference/rest/v1/users
* https://developers.google.com/admin-sdk/directory/reference/rest/v1/groups

## Display addresses
Produces a two column CSV file (headers Type, Email) that displays all group and user primary
email addresses and aliases. The types are: Group, GroupAlias, GroupNEAlias,
SuspendedUser, User, UserAlias, UserNEAlias. 'NE' is and abbreviation for NonEditable.
```
gam print addresses [todrive <ToDriveAttribute>*]
```

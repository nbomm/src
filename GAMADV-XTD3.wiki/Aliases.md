# Aliases
- [API documentation](#api-documentation)
- [Query documentation](#query-documentation)
- [Python Regular Expressions](Python-Regular-Expressions) Match function
- [Definitions](#definitions)
- [Create an alias for a target](#create-an-alias-for-a-target)
- [Update an alias to point to a new target](#update-an-alias-to-point-to-a-new-target)
- [Delete an alias regardless of the target](#delete-an-alias-regardless-of-the-target)
- [Remove aliases from a specified target](#remove-aliases-from-a-specified-target)
- [Delete all of a user's aliases](#delete-all-of-a-users-aliases)
- [Display aliases](#display-aliases)
- [Bulk delete aliases](#bulk-delete-aliases)
- [Determine if an address is a user, user alias, group or group alias](#determine-if-an-address-is-a-user-user-alias-group-or-group-alias)

## API documentation
* https://developers.google.com/admin-sdk/directory/reference/rest/v1/users.aliases
* https://developers.google.com/admin-sdk/directory/reference/rest/v1/groups.aliases

## Query documentation
* https://developers.google.com/admin-sdk/directory/v1/guides/search-users

## Definitions
```
<DomainName> ::= <String>(.<String>)+
<EmailAddress> ::= <String>@<DomainName>
<EmailAddressList> ::= "<EmailAddress>(,<EmailAddress>)*"
<EmailAddressEntity> ::= <EmailAddressList> | <FileSelector> | <CSVkmdSelector> | <CSVDataSelector>
<UniqueID> ::= uid:<String>
```
## Create an alias for a target
```
gam create alias|aliases <EmailAddressEntity> user|group|target <UniqueID>|<EmailAddress>
        [verifynotinvitable]
```

The `verifynotinvitable` option causes GAM to verify that the alias email address being created is not that of an unmanaged account;
if it is, the command is not performed.

### Example

To allow Robert to also receive mail as Bob:

```
gam create alias bob[@yourdomain.com] user robert[@yourdomain.com]
```

### Update an alias to point to a new target
The existing alias is deleted and a new alias is created.

```
gam update alias|aliases <EmailAddressEntity> user|group|target <UniqueID>|<EmailAddress>
        [notargetverify]
```

By default, GAM makes additional API calls to verify that the target email address exists before updating the alias;
if you know that the target exists, you can suppress the verification with `notargetverify.

### Delete an alias regardless of the target
```
gam delete alias|aliases [user|group|target] <EmailAddressEntity>
```

### Remove aliases from a specified target
```
gam remove alias|aliases <EmailAddress> user|group <EmailAddressEntity>
```

## Delete all of a user's aliases
```
gam <UserTypeEntity> delete aliases
```

## Display aliases
```
gam info alias|aliases <EmailAddressEntity>
gam print aliases [todrive <ToDriveAttribute>*]
        [domain <DomainName>] [(query <QueryUser>)|(queries <QueryUserList>)]
        [aliasmatchpattern <RegularExpression>]
        [shownoneditable] [nogroups] [nousers]
        [onerowpertarget] [suppressnoaliasrows]
```
By default, group and user aliases in all domains in the account are selected; these options allow selection of subsets of aliases:
* `domain <DomainName>` - Limit aliases to those in `<DomainName>`
* `(query <QueryUser>)|(queries <QueryUserList>)` - Print aliases for selected users
* `aliasmatchpattern <RegularExpression>` - Print aliases that match a pattern
* `nogroups` - Print only user aliases
* `nousers` - Print only group aliases

By default, the CSV output has three columns: `Alias,Target,TargetType`; if a target
has multiple aliases, there will be multiple rows, one per alias.

Use `shownoneditable` to list non-editable alias email addresses; these are typically outside of the account's primary domain or subdomains.
This adds the column `NonEditableAlias`.

Specifying `onerowpertarget` changes the three columns to: `Target,TargetType,Aliases`; all aliases for the target are space-separated in the
`Aliases` column. If `shownoneditable` is specified, there will be a fourth column `NonEditableAliases` with space-separated non-editable aliases.

Specifying both `onerowpertarget` and `suppressnoaliasrows` causes GAM to not display any targets that have no aliases.

## Bulk delete aliases
You can bulk delete aliases as follows; use `(query <QueryUser>)|(queries <QueryUserList>)` and
`aliasmatchpattern <RegularExpression>` as desired.
```
gam redirect csv ./OldDomainAliases.csv print aliases aliasmatchpattern ".*@olddomain.com" onerowpertarget suppressnoaliasrows
gam csv ./OldDomainAliases.csv gam remove aliases "~Target" "~TargetType" "~Aliases"
```

## Determine if an address is a user, user alias, group or group alias
```
gam whatis <EmailItem> [noinfo] [noinvitablecheck]
```
The first line of output is: `<TypeOfEmailItem>: <EmailItem>`

There is additional output based on `<TypeOfEmailItem>`:
* User - `gam info user <EmailItem>`
* Group - `gam info group <EmailItem>`
* User Alias - `gam info alias <EmailItem>`
* Group Alias - `gam info alias <EmailItem>`
* User Invitation - `gam info userinvitation <EmailItem>`

The `noinfo` argument suppresses the additional output.

The `noinvitablecheck` argument suppresses the user invitation check
to avoid exceeding quota limits when checking a large number of addresses.

The return code is set based on `<TypeOfEmailItem>`:
* User - 20
* User Alias - 21
* Group - 22
* Group Alias - 23
* User Invitation - 24
* Unknown - 59


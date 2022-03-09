# Administrators
- [Administrator roles documentation](#administrator-roles-documentation)
- [API documentation](#api-documentation)
- [Definitions](#definitions)
- [Display administrative privileges](#display-administrative-privileges)
- [Manage administrative roles](#manage-administrative-roles)
- [Display administrative roles](#display-administrative-roles)
- [Create an administrator](#create-an-administrator)
- [Delete an administrator](#delete-an-administrator)
- [Display administrators](#display-administrators)

## Administrator roles documentation
* https://support.google.com/a/answer/33325?ref_topic=4514341

## API documentation
* https://developers.google.com/admin-sdk/directory/reference/rest/v1/privileges
* https://developers.google.com/admin-sdk/directory/reference/rest/v1/roles
* https://developers.google.com/admin-sdk/directory/reference/rest/v1/roleAssignments

## Definitions
```
<DomainName> ::= <String>(.<String>)+
<EmailAddress> ::= <String>@<DomainName>
<OrgUnitID> ::= id:<String>
<OrgUnitPath> ::= /|(/<String)+
<OrgUnitItem> ::= <OrgUnitID>|<OrgUnitPath>
<Privilege> ::= <String>
<PrivilegeList> ::= "<Privilege>(,<Privilege)*"
<RoleAssignmentID> ::= <String>
<RoleItem> ::= id:<String>|uid:<String>|<String>
<UniqueID> ::= uid:<String>
<UserItem> ::= <EmailAddress>|<UniqueID>|<String>
```
## Display administrative privileges
```
gam print privileges [todrive <ToDriveAttribute>*]
gam show privileges
```
## Manage administrative roles
```
gam create adminrole <String> privileges all|all_ou|<PrivilegeList> [description <String>]
gam update adminrole <RoleItem> [name <String>] [privileges all|all_ou|<PrivilegeList>] [description <String>]
gam delete adminrole <RoleItem>
```
* `privileges all` - All defined privileges
* `privileges all_ou` - All defined privileges than can be scoped to an OU
* `privileges <PrivilegeList>` - A specific list of privileges

## Display administrative roles
```
gam print adminroles|roles [todrive <ToDriveAttribute>*] [privileges]
gam show adminroles|roles [todrive <ToDriveAttribute>*]
```
* `privileges` - show privileges associated with each role.

## Create an administrator
```
gam create admin <UserItem> <RoleItem> customer|(org_unit <OrgUnitItem>)
        [condition securitygroup|nonsecuritygroup]
```
* `customer` - The administrator can manage all organization units
* `org_unit <OrgUnitItem>` - The administrator can manage the specified organization unit

The option `condition` limits the conditions for delegate admin access. This currently only works with the _GROUPS_EDITOR_ROLE and _GROUPS_READER_ROLE roles.
* `condition securitygroup` - limit the delegated admin to managing security groups
* `Condition nonsecuritygroup` - limit the delegated admin to managing non-security groups

## Delete an administrator
```
gam delete admin <RoleAssignmentId>
```
## Display administrators
```
gam print admins [todrive <ToDriveAttribute>*] [user <UserItem>] [role <RoleItem>] [condition]
gam show admins [user <UserItem>] [role <RoleItem>] [condition]
```
By default, all administrators and roles are displayed; choose from the following
options to limit the display:
* `user <UserItem>` -  Display only this administrator
* `role <RoleItem>` - Display only administrators with this role

Use `condition` to display any conditions associated with a role assignment.

In versions prior to 6.07.01, specification of both `user <UserItem>`
and `role <RoleItem>` generated no output due to an undocumented API rule that disallows both.

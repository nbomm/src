# Users - Drive - Cleanup
- [API documentation](#api-documentation)
- [Collections of Users](Collections-of-Users)
- [Definitions](#definitions)
- [Display empty folders on My Drive](#display-empty-folders-on-my-drive)
- [Delete empty folders on My Drive](#delete-empty-folders-on-my-drive)
- [Empty the trash on My Drive](#empty-the-trash-on-my-drive)
- [Display empty folders on a Shared Drive](#display-empty-folders-on-a-shared-drive)
- [Delete empty folders on a Shared Drive](#delete-empty-folders-on-a-shared-drive)
- [Empty the trash on a Shared Drive](#empty-the-trash-on-a-shared-drive)

## API documentation
* https://developers.google.com/drive/v3/reference/files

## Definitions
```
<SharedDriveID> ::= <String>
<SharedDriveName> ::= <String>
<SharedDriveEntity> ::=
        <SharedDriveID>|(teamdriveid <SharedDriveID>)|(teamdriveid:<SharedDriveID>)|
        (teamdrive <SharedDriveName>)|(teamdrive:<SharedDriveName>)
```
## Display empty folders on My Drive
```
gam <UserTypeEntity> print emptydrivefolders [todrive <ToDriveAttribute>*]
```
## Delete empty folders on My Drive
```
gam <UserTypeEntity> delete emptydrivefolders
```
## Empty the trash on My Drive
```
gam <UserTypeEntity> empty drivetrash
```
## Display empty folders on a Shared Drive
```
gam <UserTypeEntity> print emptydrivefolders [todrive <ToDriveAttribute>*]
        select <SharedDriveEntity>
```
## Delete empty folders on a Shared Drive
```
gam <UserTypeEntity> delete emptydrivefolders <SharedDriveEntity>
```
## Empty the trash on a Shared Drive
```
gam <UserTypeEntity> empty drivetrash <SharedDriveEntity>
```

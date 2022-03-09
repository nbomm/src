# Users - Drive - Ownership
- [API documentation](#api-documentation)
- [Query documentation](#query-documentation)
- [Collections of Users](Collections-of-Users)
- [Definitions](#definitions)
- [Transfer ownership of files that a source user owns to a target user](#transfer-ownership-of-files-that-a-source-user-owns-to-a-target-user)
- [Claim ownership of files that other users own](#claim-ownership-of-files-that-other-users-own)

## API documentation
* https://developers.google.com/drive/api/v3/reference/files

## Query documentation
* https://developers.google.com/drive/api/v3/search-files

## Definitions
See [Drive File Selection](Drive-File-Selection) for symbols not listed here, such as `<DriveFileEntity>`
```
<DomainName> ::= <String>(.<String>)+
<EmailAddress> ::= <String>@<DomainName>
<UniqueID> ::= uid:<String>
<UserItem> ::= <EmailAddress>|<UniqueID>|<String>

<DriveOrderByFieldName> ::=
        createddate|createdtime|
        folder|
        modifiedbyme|modifiedbymedate|modifiedbymetime|modifiedbyuser|
        modifieddate|modifiedtime|
        name|
        name_natural|
        quotabytesused|quotaused|
        recency|
        sharedwithmedate|sharedwithmetime|
        starred|
        title|
        title_natural|
        viewedbymedate|viewedbymetime
```
## Transfer ownership of files that a source user owns to a target user
```
gam <UserTypeEntity> transfer ownership <DriveFileEntity> <UserItem> [includetrashed]
        (orderby <DriveOrderByFieldName> [ascending|descending])*
        [preview] [filepath] [buildtree] [todrive <ToDriveAttribute>*]
```
Include files in trash as part of the transfer.
* `includetrashed` - Ownership of files in the trash will be transferred.

Specify order of file processing.
* `(orderby <DriveOrderByFieldName> [ascending|descending])*`

Preview the transfer.

Typically, the filepath option is used with the preview option so you can verify what files are going to be transferred.
If buildtree is specified, you will see the full path to each file. If buildtree is not specified, you will see the
relative file path starting from the top level folder being transferred.
* `preview` - Output a CSV file showing what files will have their ownership transferred.
* `filepath` - Show full path to files in CSV file.
* `buildtree` - Download all user files so that full filepath information is available.

## Claim ownership of files that other users own
This is typically used in a classroom setting where a teacher has shared a folder to students;
the students create files in the folder and the teacher claims ownership of the files at some
point to control the students further access to the files.
```
gam <UserTypeEntity> claim ownership <DriveFileEntity> [includetrashed]
        [skipids <DriveFileEntity>] [skipusers <UserTypeEntity>] [subdomains <DomainNameEntity>]
        [restricted [<Boolean>]] [writerscanshare|writerscantshare [<Boolean>]]
        [keepuser | (retainrole reader|commenter|writer|editor|none)] [noretentionmessages]
        (orderby <DriveOrderByFieldName> [ascending|descending])*
        [preview] [filepath] [buildtree] [todrive <ToDriveAttribute>*]
```
Include files in trash as part of the transfer.
* `includetrashed` - Ownership of files in the trash will be transferred.

Specify order of file processing.
* `(orderby <DriveOrderByFieldName> [ascending|descending])*`

These options handle special cases where you want to prevent ownership from being transferred for selected files.
* `skipids <DriveFileEntity>` - Do not transfer ownership for files with the specified IDs.
* `skipusers <UserTypeEntity>` - Do not transfer ownership for files owned by the specified users.

By default, only files owned by users in the same domain as the claiming user have their ownership transferred.
* `subdomains <DomainNameEntity>` - Transfer ownership for files in the selected sub-domains.

These options handle special cases where you want to restrict access to the claimed files.
* `restricted [<Boolean>]` - Prevent viewers and commenters from downloading, printing, and copying the files.
* `writerscanshare [<Boolean>]` - Allow writers to share the document with other users.
* `writerscantshare [<Boolean>]` - Prevent writers from sharing the document with other users.

Specify role for original owner.
* `keepuser` - Original owner retains the role of writer; this is the default
* `retainrole reader|commenter|writer|editor` - Original owner retains the specified role
* `retainrole none` - Orginal owner retains no role

* `noretentionmessages` - Suppress the owner role retention messages.

Preview the transfer.

Typically, the filepath option is used with the preview option so you can verify what files are going to be transferred.
If buildtree is specified, you will see the full path to each file. If buildtree is not specified, you will see the
relative file path starting from the top level folder being transferred.
* `preview` - Output a CSV file showing what files will have their ownership transferred.
* `filepath` - Show full path to files in CSV file.
* `buildtree` - Download all user files so that full filepath information is available.

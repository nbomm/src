# Users - Photo
- [API documentation](#api-documentation)
- [Collections of Users](Collections-of-Users)
- [Upload a user's Gmail photo specifying full path](#upload-a-users-gmail-photo-specifying-full-path)
- [Upload a user's Gmail photo specifying separate path and filename](#upload-a-users-gmail-photo-specifying-separate-path-and-filename)
- [Download a user's Gmail photo](#download-a-users-gmail-photo)
- [Delete a user's Gmail photo](#delete-a-users-gmail-photo)
- [Download a user's Profile photo](#download-a-users-profile-photo)

## API documentation
* https://developers.google.com/admin-sdk/directory/reference/rest/v1/users/photos
* https://developers.google.com/people/api/rest/v1/people

## Upload a user's Gmail photo specifying full path
```
gam <UserTypeEntity> update photo <FileNamePattern>
```
* `<FileNamePattern>` should be a full file path and name
    * `#email#` and `#user#` will be replaced by the user's full email address
    * `#username#` will be replaced by the local part of the user's email address

## Upload a user's Gmail photo specifying separate path and filename
```
gam <UserTypeEntity> update photo
        [drivedir|(sourcefolder <FilePath>)] [filename <FileNamePattern>]
```
By default, the user's photo will be uploaded from the current working directory.
* `drivedir` - The photo will be uploaded from the directory specified by `drive_dir` in gam.cfg
* `sourcefolder <FilePath>` - The photo will be uploaded from `<FilePath>`

By default, the user's photo will be named `<UserEmailAddress>.jpg`
* `filename <FileNamePattern>` - The uploaded file name is `<FileNamePattern>`
    * `#email#` and `#user#` will be replaced by the user's full email address
    * `#username#` will be replaced by the local part of the user's email address

## Download a user's Gmail photo
```
gam <UserTypeEntity> get photo
        [drivedir|(targetfolder <FilePath>)] [filename <FileNamePattern>]
        [noshow]
```
By default, the user's photo will be downloaded into the current working directory.
* `drivedir` - The photo will be downloaded to the directory specified by `drive_dir` in gam.cfg
* `targetfolder <FilePath>` - The photo will be downloaded to `<FilePath>`

By default, the user's photo will be named `<UserEmailAddress>.jpg`
* `filename <FileNamePattern>` - The downloaded file name will be `<FileNamePattern>`
    * `#email#` and `#user#` will be replaced by the user's full email address
    * `#username#` will be replaced by the local part of the user's email address

By default, the Base64 encoded data is dumped to stdout.
* `noshow` suppresses dumping the photo data to stdout.

## Delete a user's Gmail photo
```
gam <UserTypeEntity> delete|del photo
```
## Download a user's Profile photo
```
gam <UserTypeEntity> get profilephoto
        [drivedir|(targetfolder <FilePath>)] [filename <FileNamePattern>]
        [noshow] [returnurlonly]
```
By default, the user's photo will be downloaded into the current working directory.
* `drivedir` - The photo will be downloaded to the directory specified by `drive_dir` in gam.cfg
* `targetfolder <FilePath>` - The photo will be downloaded to `<FilePath>`

By default, the user's photo will be named `<UserEmailAddress>.jpg`
* `filename <FileNamePattern>` - The downloaded file name will be `<FileNamePattern>`
    * `#email#` and `#user#` will be replaced by the user's full email address
    * `#username#` will be replaced by the local part of the user's email address

By default, the Base64 encoded data is dumped to stdout.
* `noshow` suppresses dumping the photo data to stdout.

Use the `returnurlonly` option to get the URL of the profile photo but not the photo itself.

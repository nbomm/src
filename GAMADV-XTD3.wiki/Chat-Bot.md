# Chat Bot

- [Notes](#notes)
- [API documentation](#api-documentation)
- [Definitions](#definitions)
- [Set up a Chat Bot](#set-up-a-chat-bot)
- [Display Rooms and Chats to which your Bot belongs](#display-rooms-and-chats-to-which-your-bot-belongs)
- [Display Members of a Room or Chat](#display-members-of-a-room-or-chat)
- [Create a Chat Message](#create-a-chat-message)
- [Update a Chat Message](#update-a-chat-message)
- [Delete a Chat Message](#delete-a-chat-message)
- [Display a Chat Message](#display-a-chat-message)

## Notes
This Wiki page was built directly from Jay Lee's Wiki page; my sincere thanks for his efforts.

## API documentation
* https://developers.google.com/chat/concepts
* https://developers.google.com/chat/reference/rest
* https://support.google.com/chat/answer/7655820

## Definitions
* See [Drive File Selection](Drive-File-Selection) for symbols not listed here, such as `<DriveFileIDEntity>`
* See [Command data from Google Docs/Sheets](Command-Data-From-Google-Docs-Sheets)
```
<UserGoogleDoc> ::=
        <EmailAddress> <DriveFileIDEntity>|<DriveFileNameEntity>|(<SharedDriveEntity> <SharedDriveFileNameEntity>)

<UserGoogleDoc> ::=
        <EmailAddress> <DriveFileIDEntity>|<DriveFileNameEntity>|(<SharedDriveEntity> <SharedDriveFileNameEntity>)

<ChatMember> ::= spaces/<String>/members/<String>
<ChatMessage> ::= spaces/<String>/messages/<String>
<ChatSpace> ::= spaces/<String> | <String>
<ChatThread> ::= spaces/<String>/threads/<String>
```

## Set up a Chat Bot
Since GAM 6.04.00, GAM is capable of acting as a Chat Bot and sending messages to Chat Rooms or direct messages to users. You first need to configure your Chat Bot.

* Run the command `gam setup chat`; it will point you to a URL to configure your Chat Bot.
* Enter a name and description of your choosing. For the avatar URL you can use `https://dummyimage.com/384x256/4d4d4d/0011ff.png&text=+GAM` or a public URL to an image of your own choosing.
* In the Functionality section, check off both "Bot works in direct messages" and "Bot works in rooms and direct messages with multiple users"
* For Connection Settings, choose "Cloud Pub/Sub" and enter "no-topic" for the topic name. GAM doesn't yet listen to pub/sub so this option is not used.
* Configure permissions for who your bot can chat. The recommendation is everyone in your domain.
* Save changes.
* Log in to the admin console
* Go to Apps/Google Workspace Marketplace apps
* For each OU where you want the Chat Bot available
  * Click Settings in the upper right
  * Select `Allow users to install any app from Google Workspace Marketplace`
  * Click Save

----

## Display Rooms and Chats to which your Bot belongs
Display the spaces to which your Chat Bot can send messages.
A space can be a direct message to a user, a chat group or a chat room.
At first you'll have no spaces listed. Try [finding your bot and chatting it](https://support.google.com/chat/answer/7655820) and then your space will be listed.

### Display information about a specific chat space
```
gam info chatspace space <ChatSpace>
        [formatjson]
```
By default, Gam displays the information as an indented list of keys and values.
* `formatjson` - Display the fields in JSON format.

### Display information about all chat spaces
```
gam show chatspaces
        [formatjson]
```
By default, Gam displays the information as an indented list of keys and values.
* `formatjson` - Display the fields in JSON format.

```
gam print chatspaces [todrive <ToDriveAttribute>*]
        [formatjson [quotechar <Character>]]
```
By default, Gam displays the information as columns of fields; the following option causes the output to be in JSON format,
* `formatjson` - Display the fields in JSON format.

By default, when writing CSV files, Gam uses a quote character of double quote `"`. The quote character is used to enclose columns that contain
the quote character itself, the column delimiter (comma by default) and new-line characters. Any quote characters within the column are doubled.
When using the `formatjson` option, double quotes are used extensively in the data resulting in hard to read/process output.
The `quotechar <Character>` option allows you to choose an alternate quote character, single quote for instance, that makes for readable/processable output.
`quotechar` defaults to `gam.cfg/csv_output_quote_char`.

----

## Display Members of a Room or Chat
### Display information about a specific chat member
```
gam info chatmember member <ChatMember>
        [formatjson]
```
By default, Gam displays the information as an indented list of keys and values.
* `formatjson` - Display the fields in JSON format.

### Display information about all chat members in a chat space
```
gam show chatmembers space <ChatSpace>
        [formatjson]
```
By default, Gam displays the information as an indented list of keys and values.
* `formatjson` - Display the fields in JSON format.

```
gam print chatmembers [todrive <ToDriveAttribute>*] space <ChatSpace>
        [formatjson [quotechar <Character>]]
```
By default, Gam displays the information as columns of fields; the following option causes the output to be in JSON format,
* `formatjson` - Display the fields in JSON format.

By default, when writing CSV files, Gam uses a quote character of double quote `"`. The quote character is used to enclose columns that contain
the quote character itself, the column delimiter (comma by default) and new-line characters. Any quote characters within the column are doubled.
When using the `formatjson` option, double quotes are used extensively in the data resulting in hard to read/process output.
The `quotechar <Character>` option allows you to choose an alternate quote character, single quote for instance, that makes for readable/processable output.
`quotechar` defaults to `gam.cfg/csv_output_quote_char`.

----

## Create a Chat Message
Create a chat message in a space. Messages are limited to 4,096 characters and will be trimmed to that length.

Chat supports [simple formatting](https://developers.google.com/chat/reference/message-formats/basic#using_formatted_text_in_messages) allowing you to bold, underline, italics and strikethrough your text.
```
gam create chatmessage space <ChatSpace> [thread <ChatThread>]
	(text <String>)|(textfile <FileName> [charset <CharSet>])|(gdoc <UserGoogleDoc>)
```
By default, a new message thread is created; use `thread <ChatThread>` to append the message to an existing thread.

Specify the source of the message:
* `text <String>` - The message is `<String>`
* `textfile <FileName> [charset <CharSet>]` - The message is read from a local file
* `gdoc <UserGoogleDoc>` - The message is read from a Google Doc.

### Examples
This example creates a new chat message in the given room.
```
gam create chatmessage space spaces/iEMj8AAAAAE text "Hello Chat"
```
This example creates a formatted message and posts it to an existing thread
```
gam create chatmessage space spaces/AAAADi-pvqc thread spaces/AAAADi-pvqc/threads/FMNw-iE9jN4 text "*Bold* _Italics_ ~Strikethrough~"
```
This example reads the MotD.txt file and posts its contents to Chat.
```
gam create chatmessage spaces spaces/AAAADi-pvqc textfile MotD.txt
```
This example reads the Google Doc MotD and posts its contents to Chat.
```
gam create chatmessage spaces spaces/AAAADi-pvqc gdoc announcements@domain.com name "MotD"
```

----

## Update a Chat Message
Updates and rewrites an existing Chat message. Message will show as edited and no notification will be sent to members.
```
gam update chatmessage name <ChatMessage>
	(text <String>)|(textfile <FileName> [charset <CharSet>])|(gdoc <UserGoogleDoc>)
```
Specify the source of the message:
* `text <String>` - The message is `<String>`
* `textfile <FileName> [charset <CharSet>]` - The message is read from a local file
* `gdoc <UserGoogleDoc>` - The message is read from a Google Doc.

### Example
This example updates an existing chat message with new text.
```
gam update chatmessage name spaces/AAAADi-pvqc/messages/PKJrx90ooIU.PKJrx90ooIU text "HELLO CHAT?"
```

----

## Delete a Chat Message
Deletes the given Chat message. Members will no longer see the message.

```
gam delete chatmessage name <ChatMessage>
```

### Example
```
gam delete chatmessage name spaces/AAAADi-pvqc/messages/PKJrx90ooIU.PKJrx90ooIU
```

----

## Display a Chat Message
Display the given Chat message.

```
gam display chatmessage name <ChatMessage>
        [formatjson]
```
By default, Gam displays the information as an indented list of keys and values.
* `formatjson` - Display the fields in JSON format.

### Example
```
gam display chatmessage name spaces/AAAADi-pvqc/messages/PKJrx90ooIU.PKJrx90ooIU
```

----

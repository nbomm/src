# Python Regular Expressions
- [Documentation](#documentation)
- [Match function](#match-function)
- [Sub function](#sub-function)
- [Search function](#search-function)

## Documentation
* https://docs.python.org/3.9/library/re.html
* https://www.regular-expressions.info/python.html

## Match function
When matching, Gam uses the match function which always looks for a match at the beginning of a string.
* "^Foo Bar$" - match the entire string "Foo Bar"
* "Foo Bar" - match a string that starts with "Foo Bar"
* ".*Foo Bar" - match a string that contains "Foo Bar"
* ".*Foo Bar$" - match a string that ends with "Foo Bar"

```
matchfield|skipfield <FieldName> <RegularExpression>`
emailmatchpattern <RegularExpression>`
labelmatchpattern <RegularExpression>`
namematchpattern <RegularExpression>`
descriptionmatchpattern <RegularExpression>`
owneremailmatchpattern <RegularExpression>`
regex:<RegularExpression>`
attachmentnamepattern <RegularExpression>`
```

## Sub function
When substituting, Gam uses the sub function which looks for a match anywhere in a string.

* "^Foo Bar$"` - match the entire string "Foo Bar"
* "^Foo Bar"` - match a string that starts with "Foo Bar"
* "Foo Bar"` - match a string that contains "Foo Bar"
* "Foo Bar$"` - match a string that ends with "Foo Bar"

```
* `keypattern <RegularExpression> keyvalue <String>`
* `updateprimaryemail <RegularExpression> <EmailReplacement>`
* `replacefilename <RegularExpression> <String>`
* `search <RegularExpression> replace <LabelReplacement>`
```

### Examples
* `search "^Foo Bar$" replace "Doodle"` - replace the entire string "Foo Bar" with "Doodle"
* `search "^(.+) (.+)$" replace "\2 \1"` - swap the two words separated by space, e.g. "Foo Bar" becomes "Bar Foo"
* `updateprimaryemail "^(.).*_(.+)@(.+)$" <\1\2@\3>` - replace "first_last@domain.com" with "flast@domain.com"

## Search function
CSV input and output row filtering and event matching  use the search function which looks for a match anywhere in a string,

* "^Foo Bar$"` - match the entire string "Foo Bar"
* "^Foo Bar"` - match a string that starts with "Foo Bar"
* "Foo Bar"` - match a string that contains "Foo Bar"
* "Foo Bar$"` - match a string that ends with "Foo Bar"

```
<FieldNameFilter> :: = <RegularExpression>
<RowValueFilter> ::=
        [(any|all):]regex:<RegularExpression>|
        [(any|all):]regexcs:<RegularExpression>|
        [(any|all):]notregex:<RegularExpression>|
        [(any|all):]notregexcs:<RegularExpression>

<EventMatchProperty> ::=
        (matchfield attendees <EmailAddressEntity>)|
        (matchfield attendeespattern <RegularExpression>)|
        (matchfield attendeesstatus [<AttendeeAttendance>] [<AttendeeStatus>] <EmailAddressEntity>)|
        (matchfield creatoremail <RegularExpression>)|
        (matchfield creatorname <RegularExpression>)|
        (matchfield description <RegularExpression>)|
        (matchfield location <RegularExpression>)|
        (matchfield organizeremail <RegularExpression>)|
        (matchfield organizername <RegularExpression>)|
        (matchfield status <RegularExpression>)|
        (matchfield summary <RegularExpression>)|
        (matchfield transparency <RegularExpression>)|
        (matchfield visibility <RegularExpression>)
<EventSelectEntity> ::=
        (<EventSelectProperty>+ <EventMatchProperty>*)
<EventEntity> ::=
        <EventIDEntity> | <EventSelectEntity>
gam calendar|calendars <CalendarEntity> show events <EventSelectEntity>
gam calendar|calendars <CalendarEntity> print events <EventSelectEntity>
gam <UserTypeEntity> show events <UserCalendarEntity> <EventSelectEntity>
gam <UserTypeEntity> print events <UserCalendarEntity> <EventSelectEntity>
gam <UserTypeEntity> update user <UserAttribute>* updateprimaryemail <RegularExpression> <EmailReplacement>]
```

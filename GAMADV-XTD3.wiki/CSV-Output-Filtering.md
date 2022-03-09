# CSV Output Filtering
- [Python Regular Expressions](Python-Regular-Expressions) Search function
- [Definitions](#definitions)
- [Quoting rules](#quoting-rules)
- [Column header filtering](#column-header-filtering)
- [Column row filtering](#column-row-filtering)
- [Saving filters in gam.cfg](#saving-filters-in-gamcfg)

There are four values in `gam.cfg` that can be used to filter the output from `gam print` commands.
* `csv_output_header_filter` - A list of `<RegularExpressions>` used to select specific column headers to include
* `csv_output_header_drop_filter` - A list of `<RegularExpressions>` used to select specific column headers to exclude
* `csv_output_row_filter` - A list or JSON dictionary used to include specific rows based on column values
* `csv_output_row_drop_filter` - A list or JSON dictionary used to exclude specific rows based on column values

The original implementation required that row filters be expressed in JSON notation; these are almost
impossible to enter correctly in Windows; on Mac OS or Linux, it's easy. You can now enter the row filters as lists
on all platforms.

## Definitions
```
<Date> ::=
        <Year>-<Month>-<Day> |
        (+|-)<Number>(d|w|y) |
        never|
        today
<Time> ::=
        <Year>-<Month>-<Day>T<Hour>:<Minute>:<Second>[.<MilliSeconds>](Z|(+|-(<Hour>:<Minute>))) |
        (+|-)<Number>(m|h|d|w|y) |
        never|
        now|today
<Operator> ::= <|<=|>=|>|=|!=
<RegularExpression> ::= <String>
        See: https://docs.python.org/3.9/library/re.html>

<FieldNameFilter> :: = <RegularExpression>
<ColumnFieldNameFilterList> ::= "<FieldNameFilter>(,<FieldNameFilter>)*"
<RowValueFilter> ::=
        [(any|all):]count<Operator><Number>|
        [(any|all):]countrange=<Number>/<Number>|
        [(any|all):]countrange!=<Number>/<Number>|
        [(any|all):]date<Operator><Date>|
        [(any|all):]daterange=<Date>/<Date>|
        [(any|all):]daterange!=<Date>/<Date>|
        [(any|all):]time<Operator><Time>|
        [(any|all):]timerange=<Time>/<Time>|
        [(any|all):]timerange!=<Time>/<Time>|
        [(any|all):]boolean:<Boolean>|
        [(any|all):]regex:<RegularExpression>|
        [(any|all):]regexcs:<RegularExpression>|
        [(any|all):]notregex:<RegularExpression>|
        [(any|all):]notregexcs:<RegularExpression>
<RowValueFilterList> ::=
        "'<FieldNameFilter>:<RowValueFilter>'(,'<FieldNameFilter>:<RowValueFilter>')*"
<RowValueFilterJSONList> ::=
        '{"<FieldNameFilter>": "<RowValueFilter>"(,"<FieldNameFilter>": "<RowValueFilter>")*}' |
        "{\"<FieldNameFilter>\": \"<RowValueFilter>\"(,\"<FieldNameFilter>\": \"<RowValueFilter>\")*}"
```
## Quoting rules
Name:value form.
```
<RowValueFilterList> ::=
        "'<FieldNameFilter>:<RowValueFilter>'(,'<FieldNameFilter>:<RowValueFilter>')*"
```
* `<RowValueFilterList>`, even if it has one element, should be enclosed in `"`.
* Each `<FieldNameFilter>:<RowValueFilter>` pair should be enclosed in `'`.
* If `<FieldNameFilter>` contains a `:`, it should be enclosed in `\"`.

Example:
```
csv_output_row_filter "'\"accounts:used_quota_in_mb\":count>15000'"
```
JSON form.
```
<RowValueFilterJSONList> ::=
        '{"<FieldNameFilter>": "<RowValueFilter>"(,"<FieldNameFilter>": "<RowValueFilter>")*}' |
        "{\"<FieldNameFilter>\": \"<RowValueFilter>\"(,\"<FieldNameFilter>\": \"<RowValueFilter>\")*}"
```
* The first form can be used on Linux and Mac OS; it can not be used on Windows.
* The second form can be used on Linux, Mac OS and Windows.
* If `<FieldNameFilter>` contains a `:`, no additional quoting is required

Example:
```
csv_output_row_filter '{"accounts:used_quota_in_mb": "count>=150"}'
csv_output_row_filter "{\"accounts:used_quota_in_mb\": \"count>=150\"}"
```

## Column header filtering
Gam gives you the ability to select fields(column headers) in its print commands, but there may be cases
where you get more columns than is desirable.
* `csv_output_header_filter` - Used to select the column headers to include in the output
* `csv_output_header_drop_filter` - Used to select the column headers to exclude from the output

Typically, you would use the option that involes typing the fewest column names but both options can be used.
When both options are used, `csv_output_header_drop_filter` is processed first, then `csv_output_header_filter`.

Field names are specified by regular expressions; at its simplest, you specify a complete field name.
Field names are matched in a case insensitive manner.
```
gam config csv_output_header_filter <ColumnFieldNameFilterList> ...
gam config csv_output_header_drop_filter <ColumnFieldNameFilterList> ...
```
### Example
you want a list of user email addresses and full names; you do not need the given or family names.

No filtering.
```
gam print users name
primaryEmail,name.givenName,name.familyName,name.fullName
testuser1@domain.com,Test,User1,Test User1
testuser2@domain.com,Test,User2,Test User2
...
```
With inclusion filtering.
```
gam config csv_output_header_filter "primaryEmail,name.fullName" print users name
primaryEmail,name.fullName
testuser1@domain.com,Test User1
testuser2@domain.com,Test User2
...
```
With exclusion filtering.
```
gam config csv_output_header_drop_filter "name.givenName,name.familyName" print users name
primaryEmail,name.fullName
testuser1@domain.com,Test User1
testuser2@domain.com,Test User2
...
```

## Column row filtering
Row filtering includes/excludes rows based on column values.

### Field names
Field names are specified by regular expressions; at its simplest, you specify a complete field name.
Field names are matched in a case insensitive manner.

If the field name doesn't contain any of the following regular expression characters `^$*+|$[{(`,
it will be surrounded with `^$` so that it doesn't match any subfields that begin with the field name as a prefix.

The following filter will match the count field and not the subfields.
```
config csv_output_row_filter "'externalIds:countrange=1/10'"

primaryEmail,externalIds,externalIds.0.type,externalIds.0.value,externalIds.1.type,externalIds.1.value,...
```

### Inclusive filters
You can include rows generated by gam print commands based on column values. You specify a list
of fields (headers) and the values they must have. `csv_output_row_filter` is used to specify the 
fields and values. Each field name/expression can appear only once in the list.

All value filters must match for the row to be included in the output.

```
gam config csv_output_row_filter <RowValueFilterList> ...
gam config csv_output_row_filter <RowValueFilterJSONList> ...
```

### Exclusive filters
You can exclude rows generated by gam print commands based on column values. You specify a list
of fields (headers) and the values they must not have. `csv_output_row_drop_filter` is used to specify the 
fields and values. Each field name/expression can appear only once in the list.

If any value filter matches, the row is excluded from the output.

```
gam config csv_output_row_drop_filter <RowValueFilterList> ...
gam config csv_output_row_drop_filter <RowValueFilterJSONList> ...
```

### Matches
A filter matches if the field has the desired value. lf you specify a regular expression for a field name that matches
several columns, the filter matches if any of the columns has a match. In the case of `notregex|notregexcs`,
the filter matches if none (not any) of the columns has a match.

`<RowValueFilter>` allows specifying that the filter will match only if all of the columns have a match.
In the case of `notregex|notregexcs`, the filter matches if some (not all) of the columns have a match.
If neither `any` or `all` is explicitly specified, `any` is the default.

These are the row value filter types:
* `count<Operator><Number>` - Used on fields with numbers; a blank field will not match
* `countrange=<Number>/<Number>` - Used on fields with numbers; a blank field will not match
  * The field value must be `>=` the left `<Number>` and `<=` the right `<Number>`
* `countrange!=<Number>/<Number>` - Used on fields with numbers; a blank field will not match
  * The field value must be `<` the left `<Number>` or `>` the right `<Number>`
* `date<Operator><Date>` - Used on fields with dates or times; only the date portion of a time field is compared; a blank field will not match
* `daterange=<Date>/<Date>` - Used on fields with dates or times; only the date portion of a time field is compared; a blank field will not match
  * The field value must be `>=` the left `<Date>` and `<=` the right `<Date>`
* `daterange!=<Date>/<Date>` - Used on fields with dates or times; only the date portion of a time field is compared; a blank field will not match
  * The field value must be `<` the left `<Date>` or `>` the right `<Date>`
* `time<Operator><Time>` - Used on fields with times; a blank field will not match
* `timerange=<Time>/<Time>` - Used on fields with times; a blank field will not match
  * The field value must be `>=` the left `<Time>` and `<=` the right `<Time>`
* `timerange!=<Time>/<Time>` - Used on fields with times; a blank field will not match
  * The field value must be `<` the left `<Time>` or `>` the right `<Time>`
* `boolean:<Boolean>` - Used on fields with Boolean values; a blank field is considered False
* `regex:<RegularExpression>` - Used on fields with text; field value must match `<RegularExpression>`; case insensitive
* `regexcs:<RegularExpression>` - Used on fields with text; field value must match `<RegularExpression>`; case sensitive
* `notregex:<RegularExpression>` - Used on fields with text; field value must not match `<RegularExpression>`; case insensitive
* `notregexcs:<RegularExpression>` - Used on fields with text; field value must not match `<RegularExpression>`; case sensitive

### **Change in behavior.**
In versions prior to `5.12.00`, `regex:<RegularExpression>` and `notregex:<RegularExpression>` were processed in a case sensitive manner;
in many cases this is probably not desirable; e.g., matching file names which are case insensitive.

Now, `regex:<RegularExpression>` and `notregex:<RegularExpression>` are processed in a case insensitive manner.
To get the prior case sensitive processing, use `regexcs:<RegularExpression>` and `notregexcs:<RegularExpression>`.

### Examples
You want a list of groups with 100 or more direct members.
```
gam config csv_output_row_filter "'directMembersCount:count>100'" print groups fields directmemberscount
```
You want a list of users created in the last 30 days.
```
gam config csv_output_row_filter "'creationTime:date>=-30d'" print users fields creationtime
```
You want a list of users in the OU /Test that are consuming more than 15GB of storage.
Special quoting is required because the field name contains a colon.
```
gam config csv_output_row_filter "'\"accounts:used_quota_in_mb\":count>15000'" report users select ou /Test fields accounts:used_quota_in_mb
```
You want the names of users directly in the OU /Test, you do not want users in any sub-OUs of /Test.
* The Google API will only supply users in an OU and sub-OUs, GAM has to filter out the users in the sub-OU.
```
gam config csv_output_row_filter "'orgUnitPath:regex:^/Test$'" print users query "orgUnitPath=/Test" fields name,ou
```
You want the names of female users directly in the OU /Test, you do not want users in any sub-OUs of /Test.
* The Google API will only supply users in an OU and sub-OUs, GAM has to filter out the users in the sub-OU.
```
gam config csv_output_row_filter "'orgUnitPath:regex:^/Test$','gender:regex:female'" print users query "orgUnitPath=/Test" fields name,ou,gender
```
You want a list of groups not created by an administrator.
```
gam config csv_output_row_filter "'adminCreated:boolean:false'" print groups fields admincreated
```
You want a list of users with phone numbers in the area code 510; the number can be in the format `(510) ddd-dddd` or `510-ddd-dddd`.
```
gam config csv_output_header_filter "primaryEmail,name.fullName,phones.*value" csv_output_row_filter "'phones.\d+.value:regex:(?:\(510\) )|(?:510-)\d{3}-\d{4}'" print users name phones
primaryEmail,name.fullName,phones.0.value
testuser1@domain.com,Test User1,(510) 555-1212
testuser2@domain.com,Test User2,510-555-1212
```
You want a list of users not in the organization cost center "Tech Support".
```
gam config csv_output_header_filter "primaryEmail,name.fullName,orgUnitPath,organizations.*costCenter" csv_output_row_filter 'organizations.*costCenter:notregex:"Tech Support"' print users fields name,ou,organizations
gam config csv_output_header_filter "primaryEmail,name.fullName,orgUnitPath,organizations.*costCenter" csv_output_row_drop_filter 'organizations.*costCenter:regex:"Tech Support"' print users fields name,ou,organizations
primaryEmail,name.fullName,orgUnitPath,organizations.0.costCenter
testuser1@domain.com,Test User1,/Test,Sales
testuser2@domain.com,Test User2,/Test,Development
```
You want a list of recurring events with at least one external guest.
```
gam config csv_output_row_filter "'^attendees$:count>1','recurrence:count>=1','attendees.*email:all:notregex:(^$)|(.+@domain.com)'" csv_output_row_drop_filter "'attendees.*email:regex:.+@resource.calendar.google.com'" redirect csv ./externalrecurringEvents.csv calendar <CalendarEntity> print events
```
## Saving filters in gam.cfg
If you define a value for `csv_output_header_filter`, `csv_output_header_drop_filter`, `csv_output_row_filter` or  `csv_output_row_drop_filter` in the `[DEFAULT]` section of `gam.cfg`,
it will apply to every `gam print` command which is probably not desirable. You can store them in `gam.cfg` in named sections.
```
[Filter510]
csv_output_header_filter = primaryEmail,name.fullName,phones.*value
csv_output_row_filter = 'phones.\d+.value:regex:(?:\(510\) )|(?:510-)\d{3}-\d{4}'

$ gam selectfilter Filter510 print users name phone
primaryEmail,name.fullName,phones.0.value
testuser1@domain.com,Test User1,(510) 555-1212
testuser2@domain.com,Test User2,510-555-1212
```

If you have multiple customers or domains in separate sections of gam.cfg, you use `select` to choose the customer/domain
and `selectfilter` to choose a filter.
```
[foo]
domain = foo.com
customer_id = C111111111
config_dir = foo

[goo]
domain = goo.com
customer_id = C222222222
config_dir = goo

[Filter510]
csv_output_header_filter = primaryEmail,name.fullName,phones.*value
csv_output_row_filter = 'phones.\d+.value:regex:(?:\(510\) )|(?:510-)\d{3}-\d{4}'

$ gam select foo selectfilter Filter510 print users name phone
primaryEmail,name.fullName,phones.0.value
testuser1@foo.com,Test User1,(510) 555-1212
testuser2@foo.com,Test User2,510-555-1212
```
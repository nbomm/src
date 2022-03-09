# Collections of ChromeOS Devices
- [Python Regular Expressions](Python-Regular-Expressions) Match function
- [Definitions](#definitions)
- [CrOS Type Entity](#cros-type-entity)
  - [All ChromeOS devices](#all-chromeos-devices)
  - [A list of ChromeOS deviceIds](#a-list-of-chromeos-deviceids)
  - [A list of ChromeOS device serial numbers](#a-list-of-chromeos-device-serial-numbers)
  - [ChromeOS devices directly in the Organization Unit `<OrgUnitItem>`](#chromeos-devices-directly-in-the-organization-unit-orgunititem)
  - [ChromeOS devices in the Organization Unit `<OrgUnitItem>` and all of its sub Organization Units](#chromeos-devices-in-the-organization-unit-orgunititem-and-all-of-its-sub-organization-units)
  - [ChromeOS devices directly in the Organization Units `<OrgUnitList>`](#chromeos-devices-directly-in-the-organization-units-orgunitlist)
  - [ChromeOS devices in the Organization Units `<OrgUnitList>` and all of their sub Organization Units](#chromeos-devices-in-the-organization-units-orgunitlist-and-all-of-their-sub-organization-units)
  - [ChromeOS devices that match a query](#chromeos-devices-that-match-a-query)
  - [ChromeOS devices that match any query in a list of queries](#chromeos-devices-that-match-any-query-in-a-list-of-queries)
  - [ChromeOS deviceIds in a flat file/Google Doc](#chromeos-deviceids-in-a-flat-filegoogle-doc)
  - [ChromeOS serial numbers in a flat file/Google Doc](#chromeos-serial-numbers-in-a-flat-filegoogle-doc)
  - [Selected ChromeOS deviceIds in a CSV file/Google Sheet](#selected-chromeos-deviceids-in-a-csv-filegoogle-sheet)
  - [Selected ChromeOS serial numbers in a CSV file/Google Sheet](#selected-chromeos-serial-numbers-in-a-csv-filegoogle-sheet)
  - [ChromeOS devices from OUs in a flat file/Google Doc](#chromeos-devices-from-ous-in-a-flat-filegoogle-doc)
  - [ChromeOS deviceIds from OUs in a CSV file/Google Sheet](#chromeos-deviceids-from-ous-in-a-csv-filegoogle-sheet)
  - [ChromeOS devices directly in or from OUs in a CSV file/Google Sheet](#chromeos-devices-directly-in-or-from-ous-in-a-csv-filegoogle-sheet)
  - [ChromeOS deviceIds from data fields identified in a `csvkmd` argument](#chromeos-deviceids-from-data-fields-identified-in-a-csvkmd-argument)
- [Examples using CSV files](#examples-using-csv-files)
- [Examples using multiple queries or Org Units](#examples-using-multiple-queries-or-org-units)

## Definitions
[Basic Items](Basic-Items)

[List Items](List-Items)

[Command data from Google Docs/Sheets](Command-Data-From-Google-Docs-Sheets)
`gdoc <UserGoogleDoc>` and `gsheet <UserGoogleSheet>`

```
<CrOSTypeEntity> ::=
        (all cros)|
        (cros <CrOSIDList>)|
        (cros_sn <SerialNumberList>)|
        (cros_ou|cros_org <OrgUnitItem>)|
        (cros_ou_and_children|cros_org_and_children <OrgUnitItem>)|
        (cros_ous|cros_orgs <OrgUnitList>)|
        (cros_ous_and_children|cros_orgs_and_children <OrgUnitList>)|
        (crosquery <QueryCrOS>)|
        (crosqueries <QueryCrOSList>)|
        (crosfile|crosfile_sn
                (<FileName>|(gdoc <UserGoogleDoc>)
                        [charset <Charset>] [delimiter <Character>]))|
        (croscsvfile|croscsvfile_sn
                ((<FileName>(:<FieldName>)+)|(gsheet(:<FieldName>)+ <UserGoogleSheet>)
                        [charset <Charset>] [warnifnodata] [columndelimiter <Character>] [quotechar <Character>])
                [endcsv|(fields <FieldNameList>)]
                (matchfield|skipfield <FieldName> <RegularExpression>)*
                [delimiter <Character>])|
        (datafile cros|cros_sn|cros_ous|cros_ous_and_children
                (<FileName>|(gdoc <UserGoogleDoc>) [charset <Charset>] [delimiter <Character>]))|
        (csvdatafile cros|cros_sn|cros_ous|cros_ous_and_children
                ((<FileName>(:<FieldName>)+)|(gsheet(:<FieldName>)+ <UserGoogleSheet>)
                        [charset <Charset>] [warnifnodata] [columndelimiter <Character>] [quotechar <Character>])
                [endcsv|(fields <FieldNameList>)]
                (matchfield|skipfield <FieldName> <RegularExpression>)*
                [delimiter <Character>])|
        (csvkmd cros|cros_sn|cros_ous|cros_ous_and_children
                (<FileName>|(gsheet <UserGoogleSheet>)
                        [charset <Charset>] [warnifnodata] [columndelimiter <Character>] [quotechar <Character>])
                 [endcsv|(fields <FieldNameList>)]
                (keyfield <FieldName> [keypattern <RegularExpression>] [keyvalue <String>] [delimiter <Character>])+
                (subkeyfield <FieldName> [keypattern <RegularExpression>] [keyvalue <String>] [delimiter <Character>])
                (matchfield|skipfield <FieldName> <RegularExpression>)*
                (datafield <FieldName>(:<FieldName)* [delimiter <Character>])*)|
        (croscsvdata <FieldName>(:<FieldName>*))
```
## CrOS Type Entity

Use these options to select Chrome OS devices for GAM commands.

## All ChromeOS devices
* `all cros`

## A list of ChromeOS deviceIds
* `cros <CrOSList>`

## A list of ChromeOS device serial numbers
* `cros_sn <SerialNumberList>`

## ChromeOS devices directly in the Organization Unit `<OrgUnitItem>`
* `cros_ou|cros_org <OrgUnitItem>`

## ChromeOS devices in the Organization Unit `<OrgUnitItem>` and all of its sub Organization Units
* `cros_ou_and_children|cros_org_and_children <OrgUnitItem>`

## ChromeOS devices directly in the Organization Units `<OrgUnitList>`
* `cros_ous|cros_orgs <OrgUnitList>`

`<OrgUnitList>` may require special quoting based on whether the OUs contain spaces, commas or single quotes.

For quoting rules, see: [List Items](List-Items)

## ChromeOS devices in the Organization Units `<OrgUnitList>` and all of their sub Organization Units
* `cros_ous_and_children|cros_orgs_and_children <OrgUnitList>`

`<OrgUnitList>` may require special quoting based on whether the OUs contain spaces, commas or single quotes.

For quoting rules, see: [List Items](List-Items)

## ChromeOS devices that match a query
* `crosquery <QueryCrOS>`

See https://support.google.com/chrome/a/answer/1698333

## ChromeOS devices that match any query in a list of queries
* `crosqueries <QueryCrOSList>`

See https://support.google.com/chrome/a/answer/1698333

`<QueryCrOSList>` may require special quoting based on whether the queries contain spaces, commas or single quotes.

* Surround `<QueryCrOSList>` with `" "`
* Surround each query with `\" \"`, separate the queries with commas.

```
queries "\"orgUnitPath='/Path/To/OU 1'\",\"orgUnitPath='/Path/To/OU 2'\",\"orgUnitPath='/Path/To/OU 3'\""
```

## ChromeOS deviceIds in a flat file/Google Doc
* `crosfile (<FileName>|(gdoc <UserGoogleDoc>) [charset <Charset>] [delimiter <Character>])`
    * `<FileName>` - A flat file containing a single ChromeOS deviceId per row
    * `gdoc <UserGoogleDoc>` - A Google Doc containing a single ChromeOS deviceId per row
    * `delimiter <Character>` - There are multiple deviceIds per row separated by `<Character>`; if not specified, there is single deviceId per row

## ChromeOS serial numbers in a flat file/Google Doc
* `crosfile_sn (<FileName>|(gdoc <UserGoogleDoc>) [charset <Charset>] [delimiter <Character>])`
    * `<FileName>` - A flat file containing a single ChromeOS serial number per row
    * `gdoc <UserGoogleDoc>` - A Google Doc containing a single ChromeOS serial number per row
    * `delimiter <Character>` - There are multiple serial numbers per row separated by `<Character>`; if not specified, there is single serial number per row

## Selected ChromeOS deviceIds in a CSV file/Google Sheet
* `croscsvfile (<FileName>(:<FieldName>)+ [charset <Charset>] [columndelimiter <Character>] [quotechar <Character>]) [endcsv|(fields <FieldNameList>)] (matchfield|skipfield <FieldName> <RegularExpression>)* [delimiter <Character>]`
    * `<FileName>(:<FieldName>)+` - A CSV file and the one or more columns that contain ChromeOS deviceIds
    * `gsheet(:<FieldName>)+ <UserGoogleSheet>` - A Google Sheet and the one or more columns that contain ChromeOS deviceIds
    * `warnifnodata` - Issue message 'No CSV file data found' and exit with return code 60 if there is no data selected from the file
    * `columndelimiter <Character>` - Columns are  separated by `<Character>`; if not specified, the value of `csv_input_column_delimiter` from `gam.cfg` will be used
    * `quotechar <Character>` - The column quote characer is `<Character>`; if not specified, the value of `csv_input_quote_char` from `gam.cfg` will be used
    * `endcsv` - Use this option to signal the end of the csvfile parameters in the case that the next argument on the command line is `fields` but is specifying the output field list for the command not column headings
    * `fields <FieldNameList>` - The column headings of a CSV file that does not contain column headings
    * `(matchfield|skipfield <FieldName> <RegularExpression>)*` - The criteria to select rows from the CSV file; can be used multiple times; if not specified, all rows are selected
    * `delimiter <Character>` - There are multiple deviceIds per column separated by `<Character>`; if not specified, there is single deviceId per column

## Selected ChromeOS serial numbers in a CSV file/Google Sheet
* `croscsvfile_sn (<FileName>(:<FieldName>)+ [charset <Charset>] [columndelimiter <Character>] [quotechar <Character>]) [endcsv|(fields <FieldNameList>)] (matchfield|skipfield <FieldName> <RegularExpression>)* [delimiter <Character>]`
    * `<FileName>(:<FieldName>)+` - A CSV file and the one or more columns that contain ChromeOS deviceIds
    * `gsheet(:<FieldName>)+ <UserGoogleSheet>` - A Google Sheet and the one or more columns that contain ChromeOS deviceIds
    * `warnifnodata` - Issue message 'No CSV file data found' and exit with return code 60 if there is no data selected from the file
    * `columndelimiter <Character>` - Columns are  separated by `<Character>`; if not specified, the value of `csv_input_column_delimiter` from `gam.cfg` will be used
    * `quotechar <Character>` - The column quote characer is `<Character>`; if not specified, the value of `csv_input_quote_char` from `gam.cfg` will be used
    * `endcsv` - Use this option to signal the end of the csvfile parameters in the case that the next argument on the command line is `fields` but is specifying the output field list for the command not column headings
    * `fields <FieldNameList>` - The column headings of a CSV file that does not contain column headings
    * `(matchfield|skipfield <FieldName> <RegularExpression>)*` - The criteria to select rows from the CSV file; can be used multiple times; if not specified, all rows are selected
    * `delimiter <Character>` - There are multiple deviceIds per column separated by `<Character>`; if not specified, there is single deviceId per column

## ChromeOS devices from OUs in a flat file/Google Doc
* `datafile cros|cros_ous|cros_ous_and_children (<FileName>|(gdoc <UserGoogleDoc>) [charset <Charset>] [delimiter <Character>])`
    * `cros|cros_ous|cros_ous_and_children` - The type of item in the file
    * `<FileName>` - A flat file containing a single item per row
    * `gdoc <UserGoogleDoc>` - A Google Doc containing a single item per row
    * `delimiter <Character>` - There are multiple items per row separated by `<Character>`; if not specified, there is single item per row

## ChromeOS deviceIds from OUs in a CSV file/Google Sheet
* `csvdatafile cros|cros_ous|cros_ous_and_children (<FileName>(:<FieldName>)+ [charset <Charset>] [columndelimiter <Character>] [quotechar <Character>]) [endcsv|(fields <FieldNameList>)] (matchfield|skipfield <FieldName> <RegularExpression>)* [delimiter <Character>]`
    * `cros|cros_ous|cros_ous_and_children` - The type of item in the file
    * `<FileName>(:<FieldName>)+` - A CSV file and the one or more columns that contain ChromeOS deviceIds
    * `gsheet(:<FieldName>)+ <UserGoogleSheet>` - A Google Sheet and the one or more columns that contain ChromeOS deviceIds
    * `warnifnodata` - Issue message 'No CSV file data found' and exit with return code 60 if there is no data selected from the file
    * `columndelimiter <Character>` - Columns are  separated by `<Character>`; if not specified, the value of `csv_input_column_delimiter` from `gam.cfg` will be used
    * `quotechar <Character>` - The column quote characer is `<Character>`; if not specified, the value of `csv_input_quote_char` from `gam.cfg` will be used
    * `endcsv` - Use this option to signal the end of the csvfile parameters in the case that the next argument on the command line is `fields` but is specifying the output field list for the command not column headings
    * `fields <FieldNameList>` - The column headings of a CSV file that does not contain column headings
    * `(matchfield|skipfield <FieldName> <RegularExpression>)*` - The criteria to select rows from the CSV file; can be used multiple times; if not specified, all rows are selected
    * `delimiter <Character>` - There are multiple deviceIds per column separated by `<Character>`; if not specified, there is single deviceId per column

## ChromeOS devices directly in or from OUs in a CSV file/Google Sheet
* `csvkmd cros|cros_ous|cros_ous_and_children
        (<FileName>|(gsheet <UserGoogleSheet>) [charset <Charset>]
        [columndelimiter <Character>] [quotechar <Character>]) [endcsv|(fields <FieldNameList>)]
        (keyfield <FieldName> [keypattern <RegularExpression>] [keyvalue <String>] [delimiter <Character>])+
        (matchfield|skipfield <FieldName> <RegularExpression>)*
        (datafield <FieldName>(:<FieldName)* [delimiter <Character>])*`
    * `cros|cros_ous|cros_ous_and_children` - The type of item in the file
    * `<FileName>` - A CSV file containing rows with columns of the type of item specified
    * `gsheet <UserGoogleSheet>` - A Google Sheet containing rows with columns of the type of item specified
    * `warnifnodata` - Issue message 'No CSV file data found' and exit with return code 60 if there is no data selected from the file
    * `columndelimiter <Character>` - Columns are  separated by `<Character>`; if not specified, the value of `csv_input_column_delimiter` from `gam.cfg` will be used
    * `quotechar <Character>` - The column quote characer is `<Character>`; if not specified, the value of `csv_input_quote_char` from `gam.cfg` will be used
    * `endcsv` - Use this option to signal the end of the csvfile parameters in the case that the next argument on the command line is `fields` but is specifying the output field list for the command not column headings
    * `fields <FieldNameList>` - The column headings of a CSV file that does not contain column headings
    * `(keyfield <FieldName> [keypattern <RegularExpression>] [keyvalue <String>] [delimiter <Character>])+`
        * `keyfield <FieldName>` - The column containing key values
        * `[keypattern <RegularExpression>] [keyvalue <String>]` - Allows transforming the value(s) in the `keyfield` column. If only `keyvalue <String>` is specified, all instances of `<FieldName>` in `keyvalue <String>` will be replaced by the item value. If `keypattern <RegularExpression>` is specified, the item value is matched against `<RegularExpression>` and the matched segments are substituted into `keyvalue <String>`
        * `delimiter <Character>` - There are multiple values per keyfield column separated by `<Character>`; if not specified, there is single value per keyfield column
    * `(subkeyfield <FieldName> [keypattern <RegularExpression>] [keyvalue <String>] [delimiter <Character>])*`
        * `subkeyfield <FieldName>` - The column containing subkey values
        * `[keypattern <RegularExpression>] [keyvalue <String>]` - Allows transforming the value(s) in the `subkeyfield` column. If only `keyvalue <String>` is specified, all instances of `<FieldName>` in `keyvalue <String>` will be replaced by the item value. If `keypattern <RegularExpression>` is specified, the item value is matched against `<RegularExpression>` and the matched segments are substituted into `keyvalue <String>`
        * `delimiter <Character>` - There are multiple values per subkeyfield column separated by `<Character>`; if not specified, there is single value per subkeyfield column
    * `(matchfield|skipfield <FieldName> <RegularExpression>)*` - The criteria to select rows from the CSV file; can be used multiple times; if not specified, all rows are selected
    * `(datafield <FieldName>(:<FieldName)* [delimiter <Character>])*`
        * `datafield <FieldName>(:<FieldName)*` - The column(s) containing data values
        * `delimiter <Character>` - There are multiple values per datafield column separated by `<Character>`; if not specified, there is single value per datafield column

## ChromeOS deviceIds from data fields identified in a `csvkmd` argument
* `croscsvdata <FieldName>(:<FieldName>*)` - Data fields identified in a `csvkmd` argument

## Examples using CSV files

You want to print information about ChromeOS devices at your school from Org Units based on graduation year.

Example 1
CSV File OrgUnit.csv, exactly the data you want, `keypattern` and `keyvalue` are not required.
```
OrgUnit
/Students/2020
/Students/2021
...
```
For each row, the value from the OrgUnit column is used as the Org Unit  name.
```
gam csvkmd cros_ous OrgUnit.csv keyfield OrgUnit print cros
```

Example 2
CSV File GradYear.csv, you have to convert GradYear to Org Unit name `/Students/GradYear`, `keyvalue` is required.
```
GradYear
2020
2021
...
```
For each row, the value from the GradYear column replaces the keyField name in the `keyvalue` argument and that value is used as the Org Unit name.
```
gam csvkmd cros_ous GradYear.csv keyfield GradYear keyvalue "/Students/GradYear" print cros
```

Example 3
CSV File GradYear.csv, you have to convert GradYear to Org Unit name `/Students/LastTwoDigitsOfGradYear`, `keypattern` and `keyvalue` are required.
```
GradYear
2020
2021
...
```
For each row, the value from the GradYear column is matched against the `keypattern` and the matched segments are substituted into the `keyvalue` argument and that value is used as the Org Unit name.
```
gam csvkmd cros_ous GradYear.csv keyfield GradYear keypattern '20(..)' keyvalue '/Students/\1' print cros
```

## Examples using multiple queries or Org Units

Example 1
Print information about all ChromeOS devices with a serial number that starts with HY3 or 5CD.
```
gam crosqueries "id:HY3,id:5CD" print cros allfields nolists
```

Example 2
Print information about all ChromeOS devices in two Org Units that contain spaces in their names.
```
gam crosqueries "\"orgUnitPath='/Students/Middle School/2021'\",\"orgUnitPath='/Students/Middle School/2020'\"" print cros allfields nolists
```

This is equivaluent to:
```
gam cros_ous "'/Students/Middle School/2021','/Students/Middle School/2020'" print cros allfields nolists
```



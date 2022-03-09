# Chrome Policies

- [Chrome Policies](#chrome-policies)
  - [Chrome Version History](Chrome-Version-History)
  - [API documentation](#api-documentation)
  - [Notes](#notes)
  - [Definitions](#definitions)
  - [Display a specific Chrome policy schema](#display-a-specific-chrome-policy-schema)
  - [Display all or filtered Chrome policy schemas](#display-all-or-filtered-chrome-policy-schemas)
  - [Display Chrome policy schemas in same format as Standard GAM](#display-chrome-policy-schemas-in-same-format-as-standard-gam)
  - [Create a Chrome policy image](#create-a-chrome-policy-image)
  - [Update Chrome policy](#update-chrome-policy)
  - [Delete Chrome policy](#delete-chrome-policy)
  - [Display Chrome policies](#display-chrome-policies)
  - [Copy policies set directly in one OU to another OU](#copy-policies-set-directly-in-one-ou-to-another-ou)
  - [Chrome Policy Schema Table](#chrome-policy-schema-table)

## API documentation

* https://developers.google.com/chrome/policy/guides/policy-api
* https://developers.google.com/chrome/policy/guides/policy-schemas

## Notes
To use these features you must add the `Chrome Policy API` to your project and authorize
the appropriate scope: `Chrome Policy API (supports readonly)`.
```
gam update project
gam oauth create
```

## Definitions
```
<AppID> ::= <String>
<Namespace> ::= <String>
<OrgUnitID> ::= id:<String>
<OrgUnitPath> ::= /|(/<String>)+
<OrgUnitItem> ::= <OrgUnitID>|<OrgUnitPath>
<PrinterID> ::= <String>
<SchemaName> ::= <String>
<NamespaceList> ::= "<Namespace>(,<Namespace>)*"

<ChromePolicySchemaFieldName> ::=
        accessrestrictions|
        additionaltargetkeynames|
        definition|
        fielddescriptions|
        name|
        notices|
        policydescription|
        schemaname|
        supporturi
<ChromePolicySchemaFieldNameList> ::= "<ChromePolicySchemaFieldName>(,<ChromePolicySchemaFieldName>)*"
```
## Display a specific Chrome policy schema
```
gam info chromeschema <SchemaName>
        <ChromePolicySchemaFieldName>* [fields <ChromePolicySchemaFieldNameList>]
        [formatjson]
```
By default, all schema fields are displayed.
* `<ChromePolicySchemaFieldName>*` - Specify individual fields
* `fields <ChromePolicySchemaFieldNameList>` - Specify a list of fields

By default, Gam displays the information as an indented list of keys and values.
* `formatjson` - Display the fields in JSON format.

## Display all or filtered Chrome policy schemas
### Display as an indented list of keys and values.
```
gam show chromeschemas
        [filter <String>]
        <ChromePolicySchemaFieldName>* [fields <ChromePolicySchemaFieldNameList>]
        [formatjson]
```
By default, all Chrome policy schemas are displayed.
* `filter <String>` - Display schemas based on fields like its resource name, description and additionalTargetKeyNames.

By default, all schema fields are displayed.
* `<ChromePolicySchemaFieldName>*` - Specify individual fields
* `fields <ChromePolicySchemaFieldNameList>` - Specify a list of fields

By default, Gam displays the information as an indented list of keys and values.
* `formatjson` - Display the fields in JSON format.

### Display as a CSV file.
```
gam print chromeschemas [todrive <ToDriveAttribute>*]
        [filter <String>]
        <ChromePolicySchemaFieldName>* [fields <ChromePolicySchemaFieldNameList>]
        [[formatjson [quotechar <Character>]]

```
By default, all Chrome policy schemas are displayed.
* `filter <String>` - Display schemas based on fields like its resource name, description and additionalTargetKeyNames.

By default, all schema fields are displayed.
* `<ChromePolicySchemaFieldName>*` - Specify individual fields
* `fields <ChromePolicySchemaFieldNameList>` - Specify a list of fields

By default, Gam displays the information as columns of fields; the following option causes the output to be in JSON format,
* `formatjson` - Display the fields in JSON format.

By default, when writing CSV files, Gam uses a quote character of double quote `"`. The quote character is used to enclose columns that contain
the quote character itself, the column delimiter (comma by default) and new-line characters. Any quote characters within the column are doubled.
When using the `formatjson` option, double quotes are used extensively in the data resulting in hard to read/process output.
The `quotechar <Character>` option allows you to choose an alternate quote character, single quote for instance, that makes for readable/processable output.
`quotechar` defaults to `gam.cfg/csv_output_quote_char`.

## Display Chrome policy schemas in same format as Standard GAM
```
gam show chromeschemas std
        [filter <String>]
```
By default, all Chrome policy schemas are displayed; use `filter <String>` to display a particular schema based on fields like its resource name, description and additionalTargetKeyNames.

Schemas are formatted based on their field types; a schema may have multiple fields.
```
SchemaName: description
  Field: TYPE_ENUM
    Value1: description
    Value2: description
    ...
  Field: TYPE_BOOL
    true: description
    false: description
  Field: TYPE_STRING
    description
  Field: TYPE_LIST
    description
```

## Create a Chrome policy image
You must upload an image file in order to use it in Chrome policies.
* The file must be MIME type image/jpeg and the file size cannot exceed 16384kb bytes.

The data returned by the command can be used in subsequent `gam update chromepolicy` commands.
```
<ChromePolicyImageSchemaName> ::=
        chrome.devices.managedguest.avatar |
        chrome.devices.managedguest.wallpaper |
        chrome.devices.signinwallpaperimage |
        chrome.users.avatar |
        chrome.users.wallpaper

gam create chromepolicyimage <ChromePolicyImageSchemaName> <FileName>
```

## Update Chrome policy
You can update a policy for all devices/users within an OU or for a specific printer or application within an OU.
```
gam update chromepolicy (<SchemaName> (<Field> <Value>)+)+
        ou|org|orgunit <OrgUnitItem> [(printerid <PrinterID>)|(appid <AppID>)]
```
You update a schema by specifying its name and one or more fields and values.

### TYPE_ENUM fields
Here is a schema with an TYPE_ENUM field.
```
  Chrome Policy Schema: customers/C03kt1m66/policySchemas/chrome.users.DefaultPrintColor (143/279)
    definition:
      enumType:
        name: DefaultPrintColorEnum
          value:
            name: DEFAULT_PRINT_COLOR_ENUM_UNSPECIFIED
              number: 0
            name: DEFAULT_PRINT_COLOR_ENUM_COLOR
              number: 1
            name: DEFAULT_PRINT_COLOR_ENUM_MONOCHROME
              number: 2
      messageType:
        field:
          label: LABEL_OPTIONAL
            name: printingColorDefault
            number: 1
            type: TYPE_ENUM
            typeName: DefaultPrintColorEnum
          name: DefaultPrintColor
```
When specifying a value for this field you can enter the value in one of two ways:
* `DEFAULT_PRINT_COLOR_ENUM_MONOCHROME` - The full value
* `MONOCHROME` - The text following `..._ENUM_`

### Examples
Restrict student users from adding additional printers and set default printing to black and white.
```
gam update chromepolicy chrome.users.UserPrintersAllowed userPrintersAllowed false chrome.users.DefaultPrintColor printingColorDefault MONOCHROME orgunit "/Students" 
gam update chromepolicy chrome.users.UserPrintersAllowed userPrintersAllowed false chrome.users.DefaultPrintColor printingColorDefault DEFAULT_PRINT_COLOR_ENUM_MONOCHROME orgunit "/Students" 
```
For student users, specify that Chrome browsers should be updated to the latest stable Chrome browser version.
```
gam update chromepolicy chrome.users.chromeBrowserUpdates targetVersionPrefixSetting stable-0  orgunit "/Students" 
```
Restrict students from accessing Blocked URLs.
```
gam update chromepolicy chrome.users.UrlBlocking urlBlocklist "https://socialmedia.com,https://videowebsite.com" orgunit "/Students"
```
For managed browsers, specify that users can only sign into managed accounts belonging to company/school domains.
```
gam update chromepolicy chrome.users.SecondaryGoogleAccountSignin allowedDomainsForApps company.com,company.net orgunit "/Managed Browsers"
```
## Delete Chrome policy
You can delete a policy for all devices/users within an OU or for a specific printer or application within an OU.
```
gam delete chromepolicy <SchemaName>+
        ou|org|orgunit <OrgUnitItem> [(printerid <PrinterID>)|(appid <AppID>)]
```
## Display Chrome policies
You can display policies for all devices/users within an OU or for a specific printer or application within an OU.

### Display as an indented list of keys and values.
```
gam show chromepolicies
        ou|org|orgunit <OrgUnitItem> [(printerid <PrinterID>)|(appid <AppID>)]
        [filter <String>] [namespace <NamespaceList>]
        [show all|direct|inherited]
        [formatjson]
```
By default, all Chrome policies for the OU are displayed.
* `filter <String>` - Display policies based on fields like its resource name, description and additionalTargetKeyNames.
* `show all` - Display policies regardless of where set; this is the default
* `show direct` - Display policies set directly in the OU
* `show inherited` - Display policies set in a parent OU

These are the default namespaces; use `namespace <NamespaceList>` to override.
* `default`
  * chrome.users
  * chrome.users.apps
  * chrome.devices
  * chrome.devices.kiosk
  * chrome.devices.managedGuest
* `appid <AppID>`
  * chrome.users.apps
  * chrome.devices.kiosk.apps
  * chrome.devices.managedGuest.apps
* `printerid <PrinterID>`
  * chrome.printers
                    
By default, Gam displays the information as an indented list of keys and values.
* `formatjson` - Display the fields in JSON format.

### Display as a CSV file.
```
gam print chromepolicies [todrive <ToDriveAttribute>*]
        ou|org|orgunit <OrgUnitItem> [(printerid <PrinterID>)|(appid <AppID>)]
        [filter <String>] [namespace <NamespaceList>]
        [show all|direct|inherited]
        [[formatjson [quotechar <Character>]]
```
By default, all Chrome policies for the OU are displayed.
* `filter <String>` - Display policies based on fields like its resource name, description and additionalTargetKeyNames.
* `show all` - Display policies regardless of where set; this is the default
* `show direct` - Display policies set directly in the OU
* `show inherited` - Display policies set in a parent OU

These are the default namespaces; use `namespace <NamespaceList>` to override.
* `default`
  * chrome.users
  * chrome.users.apps
  * chrome.devices
  * chrome.devices.kiosk
  * chrome.devices.managedGuest
* `appid <AppID>`
  * chrome.users.apps
  * chrome.devices.kiosk.apps
  * chrome.devices.managedGuest.apps
* `printerid <PrinterID>`
  * chrome.printers
                    
By default, Gam displays the information as columns of fields; the following option causes the output to be in JSON format,
* `formatjson` - Display the fields in JSON format.

By default, when writing CSV files, Gam uses a quote character of double quote `"`. The quote character is used to enclose columns that contain
the quote character itself, the column delimiter (comma by default) and new-line characters. Any quote characters within the column are doubled.
When using the `formatjson` option, double quotes are used extensively in the data resulting in hard to read/process output.
The `quotechar <Character>` option allows you to choose an alternate quote character, single quote for instance, that makes for readable/processable output.
`quotechar` defaults to `gam.cfg/csv_output_quote_char`.

## Copy policies set directly in one OU to another OU
Display direct policies, update all
```
gam redirect csv ChromePolicies.csv print chromepolicies ou "/Path/To/OU1" show direct
gam csv ChromePolicies.csv gam update chromepolicy "~name" "~fields.0.name" "~fields.0.value" "~fields.1.name" "~fields.1.value" ou "/Path/To/OU2"
```
Display all policies, select direct on update
```
gam redirect csv ChromePolicies.csv print chromepolicies ou "/Path/To/OU1"
gam config csv_input_row_filter "direct:boolean:true" csv ChromePolicies.csv gam update chromepolicy "~name" "~fields.0.name" "~fields.0.value" "~fields.1.name" "~fields.1.value" ou "/Path/To/OU2"
```

## Chrome Policy Schema Table
chrome.devices.AdvancedBatteryChargeMode: Advanced Charge battery mode.
  advancedBatteryChargeModeEnabled: TYPE_BOOL
    true: None
    false: None
  key: TYPE_STRING
  startTime: TYPE_INT32
  endTime: TYPE_INT32

chrome.devices.AllowedBluetoothServices: Bluetooth services allowed.
  deviceAllowedBluetoothServices: TYPE_LIST
    Only allow connection to Bluetooth services in the list. Any services represented by the UUIDs in this list will be allowed. UUIDs can be in short form ('abcd' or '0xabcd') or long form 'aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee'. A list of standard service UUIDs is available at the https://www.bluetooth.com/specifications/assigned-numbers/service-discovery/ Bluetooth SIG Assigned Numbers site. When the list is empty, all services are allowed.

chrome.devices.AllowRedeemChromeOsRegistrationOffers: Redeem offers through Chrome OS registration.
  allowRedeemChromeOsRegistrationOffers: TYPE_BOOL
    true: Allow users to redeem offers through Chrome OS registration.
    false: Prevent users from redeeming offers through Chrome OS Registration.

chrome.devices.AppToPinOsVersion: App-controlled updates.
  appToPinOsVersion: TYPE_STRING
    N/A

chrome.devices.Bluetooth: Bluetooth.
  allowBluetooth: TYPE_BOOL
    true: Do not disable Bluetooth.
    false: Disable Bluetooth.

chrome.devices.BootOnAc: Boot on AC.
  bootOnAcEnabled: TYPE_BOOL
    true: Enable boot on AC.
    false: Disable boot on AC.

chrome.devices.ContentProtection: Allow web services to request proof that the device is running an unmodified version of ChromeOS that is policy compliant.
  contentProtectionEnabled: TYPE_BOOL
    true: Ensures ChromeOS devices in your organization will verify their identity to content providers.
    false: Does not ensure ChromeOS devices in your organization will verify their identity to content providers. Some premium content may be unavailable to your users.

chrome.devices.DeviceBatteryCharge: Primary battery charge configuration.
  batteryChargeMode: TYPE_ENUM
    STANDARD: Standard.
    ADAPTIVE: Adaptive.
    EXPRESS_CHARGE: Express Charge.
    PRIMARILY_AC_USE: Primarily AC.
    CUSTOM: Custom.
  customBatteryChargeStart: TYPE_INT64
    min 50; max 95. Start charging when the battery drop below (% available charge).
  customBatteryChargeStop: TYPE_INT64
    min 55; max 100. Stop charging when the battery goes above (% available charge).

chrome.devices.DeviceDebugPacketCaptureAllowed: Debug network packet captures.
  deviceDebugPacketCaptureAllowed: TYPE_BOOL
    true: Allow user to perform network packet captures.
    false: Do not allow user to perform network packet captures.

chrome.devices.DeviceLoginScreenAutocompleteDomainGroup: Autocomplete domain.
  loginScreenDomainAutoComplete: TYPE_BOOL
    true: Use the domain name set in the field 'loginScreenDomainAutoCompletePrefix' for autocomplete at sign-in.
    false: Do not display an autocomplete domain on the sign-in screen.
  loginScreenDomainAutoCompletePrefix: TYPE_STRING
    Autocomplete domain prefix.

chrome.devices.DeviceLoginScreenAutoSelectCertificateForUrls: Single sign-on client certificates.
  deviceLoginScreenAutoSelectCertificateForUrls: TYPE_LIST
    Automatically select client certificate for these single sign-on sites. Please refer to the support url for the format of this setting.

chrome.devices.DeviceLoginScreenPrivacyScreenEnabled: Privacy screen on sign-in screen.
  deviceLoginScreenPrivacyScreenEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Always disable the privacy screen on sign-in screen.
    TRUE: Always enable the privacy screen on sign-in screen.

chrome.devices.DeviceLoginScreenPromptOnMultipleMatchingCertificates: Prompt when multiple certificates match on the sign-in screen.
  deviceLoginScreenPromptOnMultipleMatchingCertificates: TYPE_BOOL
    true: Prompt the user to select the client certificate whenever the auto-selection policy matches multiple certificates on the sign-in screen.
    false: Do not prompt the user to select a client certificate on the sign-in screen.

chrome.devices.DeviceLoginScreenSystemInfoEnforced: System info on sign-in screen.
  deviceLoginScreenSystemInfoEnforced: TYPE_ENUM
    UNSET: Allow users to display system information on the sign-in screen by pressing Alt+V.
    FALSE: Do not allow users to display system information on the sign-in screen.
    TRUE: Always display system information on the sign-in screen.

chrome.devices.DevicePciPeripheralDataAccessEnabled: Data access protection for peripherals.
  devicePciPeripheralDataAccessEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Enable data access protection.
    TRUE: Disable data access protection.

chrome.devices.DevicePowerwashAllowed: Powerwash.
  devicePowerwashAllowed: TYPE_BOOL
    true: Allow powerwash to be triggered.
    false: Do not allow powerwash to be triggered.

chrome.devices.DeviceScreenSettings: Screen settings.
  allowUserDisplayChanges: TYPE_BOOL
    true: Allow users to overwrite predefined display settings (recommended).
    false: Do not allow user changes for predefined display settings.
  externalUseNativeResolution: TYPE_BOOL
    true: Always use native resolution.
    false: Use custom resolution.
  externalDisplayWidth: TYPE_INT64
    External display width (in pixels).
  externalDisplayHeight: TYPE_INT64
    External display height (in pixels).
  externalDisplayScale: TYPE_ENUM
    NOT_SET: Not set.
    50_PERCENT: 50%.
    55_PERCENT: 55%.
    60_PERCENT: 60%.
    65_PERCENT: 65%.
    70_PERCENT: 70%.
    75_PERCENT: 75%.
    80_PERCENT: 80%.
    85_PERCENT: 85%.
    90_PERCENT: 90%.
    95_PERCENT: 95%.
    100_PERCENT: 100%.
    105_PERCENT: 105%.
    110_PERCENT: 110%.
    115_PERCENT: 115%.
    120_PERCENT: 120%.
    125_PERCENT: 125%.
    130_PERCENT: 130%.
    135_PERCENT: 135%.
    140_PERCENT: 140%.
    145_PERCENT: 145%.
    150_PERCENT: 150%.
  internalDisplayScale: TYPE_ENUM
    NOT_SET: Not set.
    50_PERCENT: 50%.
    55_PERCENT: 55%.
    60_PERCENT: 60%.
    65_PERCENT: 65%.
    70_PERCENT: 70%.
    75_PERCENT: 75%.
    80_PERCENT: 80%.
    85_PERCENT: 85%.
    90_PERCENT: 90%.
    95_PERCENT: 95%.
    100_PERCENT: 100%.
    105_PERCENT: 105%.
    110_PERCENT: 110%.
    115_PERCENT: 115%.
    120_PERCENT: 120%.
    125_PERCENT: 125%.
    130_PERCENT: 130%.
    135_PERCENT: 135%.
    140_PERCENT: 140%.
    145_PERCENT: 145%.
    150_PERCENT: 150%.

chrome.devices.DeviceSecondFactorAuthentication: Integrated FIDO second factor.
  secondFactorAuthentication: TYPE_ENUM
    UNSET: Allow the user to decide.
    DISABLED: Disable integrated second factor.
    U2F: Enable integrated second factor.

chrome.devices.DeviceShowNumericKeyboardForPassword: Show numeric keyboard for password.
  deviceShowNumericKeyboardForPassword: TYPE_BOOL
    true: Default to a numeric keyboard for password input.
    false: Default to a standard keyboard for password input.

chrome.devices.DeviceVerifiedMode: Verified mode.
  deviceVerifiedModeRequired: TYPE_BOOL
    true: Require verified mode boot for verified access.
    false: Skip boot mode check for verified access.
  servicesWithFullAccess: TYPE_LIST
    Services with full access. Service accounts which are allowed to receive device ID.
  servicesWithLimitedAccess: TYPE_LIST
    Services with limited access. Service accounts which can verify devices but do not receive device ID.

chrome.devices.DeviceWebBasedAttestationAllowedUrls: Single sign-on verified access.
  deviceWebBasedAttestationAllowedUrls: TYPE_LIST
    Allowed IdP redirect URLs. Enter the list of URLs that you want to be able to perform a verified access check during SAML authentication.

chrome.devices.DeviceWilcoDtc: Dell SupportAssist.
  deviceWilcoDtcAllowed: TYPE_BOOL
    true: Enable Dell SupportAssist.
    false: Disable Dell SupportAssist.
  ackNoticeForDeviceWilcoDtcAllowedSetToTrue: TYPE_BOOL
  installSupportAssistApp: TYPE_BOOL
    true: Force-install the Dell SupportAssist app for managed users signing into Dell devices in this organizational unit.
    false: Do not automatically install the Dell SupportAssist app.
  downloadUri: TYPE_STRING

chrome.devices.DisabledDeviceReturnInstructions: Disabled device return instructions.
  deviceDisabledMessage: TYPE_STRING
    Disabled device return instructions. Custom text to display under the device locked message. We recommend including a return address and contact phone number in your message.

chrome.devices.DockMacAddress: MAC address pass through.
  dockMacAddressSource: TYPE_ENUM
    EVICE_DOCK_MAC_ADDRESS: Use pre-assigned MAC address.
    EVICE_NIC_MAC_ADDRESS: Use Chromebook built-in MAC address.
    OCK_NIC_MAC_ADDRESS: Use dock built-in MAC address.

chrome.devices.ExtensionCacheSize: Apps and extensions cache size.
  value: TYPE_INT64

chrome.devices.GuestMode: Guest mode.
  guestModeEnabled: TYPE_BOOL
    true: Allow guest mode.
    false: Disable guest mode.

chrome.devices.HostnameTemplate: Device network hostname template.
  deviceHostnameTemplate: TYPE_STRING
    Device network hostname template. Select the hostname that is passed to the DHCP server with the DHCP request. Possible variables are ${ASSET_ID}, ${SERIAL_NUM}, ${MAC_ADDR}, ${MACHINE_NAME}, and ${LOCATION}.

chrome.devices.Imprivata: Imprivata login screen integration.
  imprivataIntegrationEnabled: TYPE_BOOL
    true: Use the Imprivata extension on the login screen.
    false: Do not use the Imprivata extension on the login screen.
  ackNoticeForImprivataIntegrationEnabledSetToTrue: TYPE_BOOL
  imprivataVersion: TYPE_ENUM
    BETA: Beta (automatically updating).
    M81: Pinned to v1 (Compatible with Chrome 81+).
    M86: Pinned to v2 (Compatible with Chrome 86+).
  downloadUri: TYPE_STRING

chrome.devices.kiosk.AccessibilityShortcutsEnabled: Kiosk accessibility shortcuts.
  accessibilityShortcutsEnabled: TYPE_ENUM
    DEFAULT_USER_CHOICE: Allow the user to decide.
    ACCESSIBILITY_DISABLED: Disable accessibility shortcuts.
    ACCESSIBILITY_ENABLED: Enable accessibility shortcuts.

chrome.devices.kiosk.Alerting: Kiosk device status alerting delivery.
  deviceStatusAlertDeliveryModes: TYPE_LIST
    {'value': 'EMAIL', 'description': 'Receive alerts via email.'}

chrome.devices.kiosk.AlertingContactInfo: Kiosk device status alerting contact info.
  alertingEmail: TYPE_LIST
    Alerting emails. Email addresses (e.g. user@example.com).
  alertingMobilePhone: TYPE_LIST
    Alerting mobile phones. Phone numbers (e.g. +1XXXYYYZZZZ, +1AAABBBCCCC).

chrome.devices.kiosk.apps.ForceInstall: Force installs the app. Note: It's required in order to add an App or Extension to the set of managed apps & extensions of an Organizational Unit.
  forceInstall: TYPE_BOOL
    true: Force install the app.
    false: Do not force install the app.

chrome.devices.kiosk.apps.FunctionKeys: Allows setting Function Keys.
  allowFunctionKeys: TYPE_BOOL

chrome.devices.kiosk.apps.InstallationUrl: Specifies the url from which to install a self hosted Chrome Extension.
  installationUrl: TYPE_STRING
    The url from which to install a self hosted Chrome Extension.
  overrideInstallationUrl: TYPE_BOOL

chrome.devices.kiosk.apps.ManagedConfiguration: Allows setting of the managed configuration.
  managedConfiguration: TYPE_STRING
    Sets the managed configuration JSON format.

chrome.devices.kiosk.apps.Plugins: Allows setting Plugins.
  allowPlugins: TYPE_BOOL

chrome.devices.kiosk.apps.PowerManagement: Allows setting Power Management.
  allowPowerManagement: TYPE_BOOL

chrome.devices.kiosk.apps.UnifiedDesktop: Allows setting Unified Desktop.
  enableUnifiedDesktop: TYPE_BOOL

chrome.devices.kiosk.apps.VirtualKeyboard: Allows setting Virtual Keyboard.
  allowVirtualKeyboard: TYPE_BOOL

chrome.devices.kiosk.appsconfig.AutoLaunchApp: Allows setting of the auto-launch app.
  appId: TYPE_STRING
    Id of the app prefixed with one of either "chrome:" or "web:", depending on the app type. For Chrome apps, the app id can be found on the Chrome Web Store, example: "chrome:aapbdbdomjkkjkaonfhkkikfgjllcleb". For Web apps, the app id is simply the URL, example: "web:https://translate.google.com".
  enableHealthMonitoring: TYPE_BOOL
  screenRotation: TYPE_ENUM
    0: Rotate by 0 degrees.
    90: Rotate by 90 degrees.
    180: Rotate by 180 degrees.
    270: Rotate by 270 degrees.

chrome.devices.kiosk.AutoclickEnabled: Kiosk auto-click enabled.
  autoclickEnabled: TYPE_ENUM
    DEFAULT_USER_CHOICE: Allow the user to decide.
    ACCESSIBILITY_DISABLED: Disable auto-click.
    ACCESSIBILITY_ENABLED: Enable auto-click.

chrome.devices.kiosk.CaretHighlightEnabled: Kiosk caret highlight.
  caretHighlightEnabled: TYPE_ENUM
    DEFAULT_USER_CHOICE: Allow the user to decide.
    ACCESSIBILITY_DISABLED: Disable caret highlight.
    ACCESSIBILITY_ENABLED: Enable caret highlight.

chrome.devices.kiosk.CursorHighlightEnabled: Kiosk cursor highlight.
  cursorHighlightEnabled: TYPE_ENUM
    DEFAULT_USER_CHOICE: Allow the user to decide.
    ACCESSIBILITY_DISABLED: Disable cursor highlight.
    ACCESSIBILITY_ENABLED: Enable cursor highlight.

chrome.devices.kiosk.DictationEnabled: Kiosk dictation.
  dictationEnabled: TYPE_ENUM
    DEFAULT_USER_CHOICE: Allow the user to decide.
    ACCESSIBILITY_DISABLED: Disable dictation.
    ACCESSIBILITY_ENABLED: Enable dictation.

chrome.devices.kiosk.HighContrastEnabled: Kiosk high contrast.
  highContrastEnabled: TYPE_ENUM
    DEFAULT_USER_CHOICE: Allow the user to decide.
    ACCESSIBILITY_DISABLED: Disable high contrast.
    ACCESSIBILITY_ENABLED: Enable high contrast.

chrome.devices.kiosk.KeyboardFocusHighlightEnabled: Kiosk keyboard focus highlighting.
  keyboardFocusHighlightEnabled: TYPE_ENUM
    DEFAULT_USER_CHOICE: Allow the user to decide.
    ACCESSIBILITY_DISABLED: Disable keyboard focus highlighting.
    ACCESSIBILITY_ENABLED: Enable keyboard focus highlighting.

chrome.devices.kiosk.KioskVirtualKeyboardFeatures: Kiosk virtual keyboard features (websites only).
  virtualKeyboardFeatures: TYPE_LIST
    {'value': 'AUTO_SUGGEST', 'description': 'Auto suggest.'}

chrome.devices.kiosk.LargeCursorEnabled: Kiosk large cursor.
  largeCursorEnabled: TYPE_ENUM
    DEFAULT_USER_CHOICE: Allow the user to decide.
    ACCESSIBILITY_DISABLED: Disable large cursor.
    ACCESSIBILITY_ENABLED: Enable large cursor.

chrome.devices.kiosk.MonoAudioEnabled: Kiosk mono audio.
  monoAudioEnabled: TYPE_ENUM
    DEFAULT_USER_CHOICE: Allow the user to decide.
    ACCESSIBILITY_DISABLED: Disable mono audio.
    ACCESSIBILITY_ENABLED: Enable mono audio.

chrome.devices.kiosk.PrimaryMouseButtonSwitch: Kiosk primary mouse button.
  primaryMouseButtonSwitch: TYPE_ENUM
    DEFAULT_USER_CHOICE: Allow the user to decide.
    ACCESSIBILITY_DISABLED: Left button is primary.
    ACCESSIBILITY_ENABLED: Right button is primary.

chrome.devices.kiosk.ScreenMagnifierType: Kiosk screen magnifier.
  screenMagnifierType: TYPE_ENUM
    DEFAULT_USER_CHOICE: Allow the user to decide.
    ACCESSIBILITY_DISABLED: Disable screen magnifier.
    ACCESSIBILITY_FULL_SCREEN: Enable full-screen magnifier.
    ACCESSIBILITY_DOCKED: Enable docked magnifier.

chrome.devices.kiosk.SelectToSpeakEnabled: Kiosk select to speak.
  selectToSpeakEnabled: TYPE_ENUM
    DEFAULT_USER_CHOICE: Allow the user to decide.
    ACCESSIBILITY_DISABLED: Disable select to speak.
    ACCESSIBILITY_ENABLED: Enable select to speak.

chrome.devices.kiosk.ShowAccessibilityMenu: Kiosk floating accessibility menu.
  showAccessibilityMenu: TYPE_BOOL
    true: Show the floating accessibility menu in kiosk mode.
    false: Do not show the floating accessibility menu in kiosk mode.

chrome.devices.kiosk.SpokenFeedbackEnabled: Kiosk spoken feedback.
  spokenFeedbackEnabled: TYPE_ENUM
    DEFAULT_USER_CHOICE: Allow the user to decide.
    ACCESSIBILITY_DISABLED: Disable spoken feedback.
    ACCESSIBILITY_ENABLED: Enable spoken feedback.

chrome.devices.kiosk.StickyKeysEnabled: Kiosk sticky keys.
  stickyKeysEnabled: TYPE_ENUM
    DEFAULT_USER_CHOICE: Allow the user to decide.
    ACCESSIBILITY_DISABLED: Disable sticky keys.
    ACCESSIBILITY_ENABLED: Enable sticky keys.

chrome.devices.kiosk.UrlBlocking: URL blocking.
  urlBlocklist: TYPE_LIST
    Blocked URLs. Any URL in the URL blocklist will be blocked, unless it also appears in the URL blocklist exception list.
  urlAllowlist: TYPE_LIST
    Blocked URLs exceptions. Any URL that matches an entry in the blocklist exception list will be allowed, even if it matches an entry in the URL blocklist. Wildcards ("*") are allowed when appended to a URL, but cannot be entered alone.

chrome.devices.kiosk.VirtualKeyboardEnabled: Kiosk on-screen keyboard.
  virtualKeyboardEnabled: TYPE_ENUM
    DEFAULT_USER_CHOICE: Allow the user to decide.
    ACCESSIBILITY_DISABLED: Disable on-screen keyboard.
    ACCESSIBILITY_ENABLED: Enable on-screen keyboard.

chrome.devices.KioskAppControlChromeVersion: Kiosk-controlled updates.
  allowKioskAppControlChromeVersion: TYPE_BOOL
    false: OS version updates will not be set to a version defined in the manifest of a kiosk app.
    true: OS version updates will be set to a version defined in the manifest of a kiosk app.

chrome.devices.LoginScreenAccessibilityShortcutsEnabled: Accessibility shortcuts.
  loginScreenAccessibilityShortcutsEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable accessibility shortcuts on the sign-in screen.
    TRUE: Enable accessibility shortcuts on the sign-in screen.

chrome.devices.LoginScreenAutoclickEnabled: Auto-click enabled.
  loginScreenAutoclickEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable auto-click on the sign-in screen.
    TRUE: Enable auto-click on the sign-in screen.

chrome.devices.LoginScreenCaretHighlightEnabled: Caret highlight.
  loginScreenCaretHighlightEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable caret highlight on the sign-in screen.
    TRUE: Enable caret highlight on the sign-in screen.

chrome.devices.LoginScreenCursorHighlightEnabled: Cursor highlight.
  loginScreenCursorHighlightEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable cursor highlight on the sign-in screen.
    TRUE: Enable cursor highlight on the sign-in screen.

chrome.devices.LoginScreenDictationEnabled: Dictation.
  loginScreenDictationEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable dictation on the sign-in screen.
    TRUE: Enable dictation on the sign-in screen.

chrome.devices.LoginScreenHighContrastEnabled: High contrast.
  loginScreenHighContrastEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable high contrast on the sign-in screen.
    TRUE: Enable high contrast on the sign-in screen.

chrome.devices.LoginScreenKeyboardFocusHighlightEnabled: Keyboard focus highlighting.
  loginScreenKeyboardFocusHighlightEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable keyboard focus highlighting on the sign-in screen.
    TRUE: Enable keyboard focus highlighting on the sign-in screen.

chrome.devices.LoginScreenLargeCursorEnabled: Large cursor.
  loginScreenLargeCursorEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable large cursor on the sign-in screen.
    TRUE: Enable large cursor on the sign-in screen.

chrome.devices.LoginScreenMonoAudioEnabled: Mono audio.
  loginScreenMonoAudioEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable mono audio on the sign-in screen.
    TRUE: Enable mono audio on the sign-in screen.

chrome.devices.LoginScreenNamesAndPhotos: Show user names and photos on the sign-in screen.
  showUserNames: TYPE_BOOL
    true: Always show user names and photos.
    false: Never show user names and photos.

chrome.devices.LoginScreenPrimaryMouseButtonSwitch: Primary mouse button.
  loginScreenPrimaryMouseButtonSwitch: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Left button is primary on the sign-in screen.
    TRUE: Right button is primary on the sign-in screen.

chrome.devices.LoginScreenScreenMagnifierType: Screen magnifier.
  loginScreenScreenMagnifierType: TYPE_ENUM
    UNSET: Allow the user to decide.
    DISABLED: Disable screen magnifier on the sign-in screen.
    FULL_SCREEN: Enable full-screen magnifier on the sign-in screen.
    DOCKED: Enable docked magnifier on the sign-in screen.

chrome.devices.LoginScreenSelectToSpeakEnabled: Select to speak.
  loginScreenSelectToSpeakEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable select to speak on the sign-in screen.
    TRUE: Enable select to speak on the sign-in screen.

chrome.devices.LoginScreenSpokenFeedbackEnabled: Spoken feedback.
  loginScreenSpokenFeedbackEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable spoken feedback on the sign-in screen.
    TRUE: Enable spoken feedback on the sign-in screen.

chrome.devices.LoginScreenStickyKeysEnabled: Sticky keys.
  loginScreenStickyKeysEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable sticky keys on the sign-in screen.
    TRUE: Enable sticky keys on the sign-in screen.

chrome.devices.LoginScreenVirtualKeyboardEnabled: On-screen keyboard.
  loginScreenVirtualKeyboardEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable on-screen keyboard on the sign-in screen.
    TRUE: Enable on-screen keyboard on the sign-in screen.

chrome.devices.managedguest.AbusiveExperienceInterventionEnforce: Abusive Experience Intervention.
  abusiveExperienceInterventionEnforce: TYPE_BOOL
    true: Prevent sites with abusive experiences from opening new windows or tabs.
    false: Allow sites with abusive experiences to open new windows or tabs.

chrome.devices.managedguest.AccessibilityImageLabelsEnabled: Image descriptions.
  accessibilityImageLabelsEnabled: TYPE_ENUM
    UNSET: Let users choose to use an anonymous Google service to provide automatic descriptions for unlabeled images.
    FALSE: Do not use Google services to provide automatic image descriptions.
    TRUE: Use an anonymous Google service to provide automatic descriptions for unlabeled images.

chrome.devices.managedguest.AccessibilityShortcutsEnabled: Accessibility shortcuts.
  accessibilityShortcutsEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable accessibility shortcuts.
    TRUE: Enable accessibility shortcuts.

chrome.devices.managedguest.AdditionalDnsQueryTypesEnabled: DNS queries for additional DNS record types.
  additionalDnsQueryTypesEnabled: TYPE_BOOL
    true: Allow additional DNS query types.
    false: Prevent additional DNS query types.

chrome.devices.managedguest.AdsSettingForIntrusiveAdsSites: Sites with intrusive ads.
  adsSettingForIntrusiveAdsSites: TYPE_ENUM
    ALLOW_ADS: Allow ads on all sites.
    BLOCK_ADS: Block ads on sites with intrusive ads.

chrome.devices.managedguest.AllowDinosaurEasterEgg: Dinosaur game.
  allowDinosaurEasterEgg: TYPE_ENUM
    UNSET: Allow users to play the dinosaur game when the device is offline on Chrome browser, but not on enrolled Chrome OS devices.
    FALSE: Do not allow users to play the dinosaur game when the device is offline.
    TRUE: Allow users to play the dinosaur game when the device is offline.

chrome.devices.managedguest.AllowedInputMethods: Allowed input methods.
  allowedInputMethods: TYPE_LIST
    N/A

chrome.devices.managedguest.AllowedLanguages: Allowed Chrome OS languages.
  allowedLanguages: TYPE_LIST
    N/A

chrome.devices.managedguest.AllowPrinting: Printing.
  printingEnabled: TYPE_BOOL
    true: Enable printing.
    false: Disable printing.

chrome.devices.managedguest.AllowWakeLocks: Wake locks.
  allowScreenWakeLocks: TYPE_BOOL
    true: Allow screen wake locks for power management.
    false: Demote screen wake lock requests to system wake lock requests.
  allowWakeLocks: TYPE_BOOL
    true: Allow wake locks.
    false: Do not allow wake locks.

chrome.devices.managedguest.AlwaysOnVpn: Always on VPN.
  alwaysOnVpnApp: TYPE_STRING
    Activate Always-on VPN for all user traffic with an app from a list of force installed Android VPN apps. Please make sure the configured app is force installed.
  vpnConfigAllowed: TYPE_BOOL
    true: Allow user to disconnect from a VPN manually (VPN will reconnect on log in).
    false: Do not allow user to disconnect from a VPN manually.

chrome.devices.managedguest.AppCacheForceEnabled: AppCache.
  appCacheForceEnabled: TYPE_BOOL
    true: Allow websites to use the deprecated AppCache feature.
    false: Do not allow websites to use the deprecated AppCache feature.

chrome.devices.managedguest.AppRecommendationZeroStateEnabled: Previously installed app recommendations.
  appRecommendationZeroStateEnabled: TYPE_BOOL
    true: Show app recommendations in the Chrome OS launcher.
    false: Do not show app recommendations in the Chrome OS launcher.

chrome.devices.managedguest.apps.CertificateManagement: Allows setting of certificate management related permissions.
  allowAccessToKeys: TYPE_BOOL
  allowEnterpriseChallenge: TYPE_BOOL

chrome.devices.managedguest.apps.IncludeInChromeWebStoreCollection: Specifies whether the Chrome Application should appear in the Chrome Web Store collection.
  includeInCollection: TYPE_BOOL

chrome.devices.managedguest.apps.InstallationUrl: Specifies the url from which to install a self hosted Chrome Extension.
  installationUrl: TYPE_STRING
    The url from which to install a self hosted Chrome Extension.
  overrideInstallationUrl: TYPE_BOOL

chrome.devices.managedguest.apps.InstallType: Specifies the manner in which the app is to be installed. Note: It's required in order to add an App or Extension to the set of managed apps & extensions of an Organizational Unit.
  appInstallType: TYPE_ENUM
    NOT_INSTALLED: Not Installed.
    FORCED: Force Install.
    FORCED_AND_PIN_TO_TOOLBAR: Force Install + pin.

chrome.devices.managedguest.apps.ManagedConfiguration: Allows setting of the managed configuration.
  managedConfiguration: TYPE_STRING
    Sets the managed configuration JSON format.

chrome.devices.managedguest.apps.PermissionsAndUrlAccess: Allows setting of allowed and blocked hosts.
  blockedPermissions: TYPE_LIST
    {'value': '', 'description': 'Allow all permissions. If empty string is set, it must be the only value set for the policy.'}
  allowedPermissions: TYPE_LIST
    {'value': 'alarms', 'description': 'Alarms.'}
  blockedHosts: TYPE_LIST
    Sets extension hosts that should be blocked.
  allowedHosts: TYPE_LIST
    Sets extension hosts that should be allowed. Allowed hosts override blocked hosts.

chrome.devices.managedguest.apps.SkipPrintConfirmation: Allows the app to skip the confirmation dialog when sending print jobs via the Chrome Printing API.
  skipPrintConfirmation: TYPE_BOOL

chrome.devices.managedguest.AudioCaptureAllowedUrls: Audio input allowed URLs.
  audioCaptureAllowedUrls: TYPE_LIST
    URL patterns to allow. URLs that will be granted access to the audio input device without a prompt. Prefix domain with [*.] to include subdomains.

chrome.devices.managedguest.AudioInput: Audio input (microphone).
  audioCaptureAllowed: TYPE_BOOL
    true: Prompt user to allow each time.
    false: Disable audio input.

chrome.devices.managedguest.AudioOutput: Audio output.
  audioOutputAllowed: TYPE_BOOL
    true: Enable audio output.
    false: Disable audio output.

chrome.devices.managedguest.AuthenticationServerAllowlist: Integrated authentication servers.
  authServerAllowlist: TYPE_LIST
    Allowed authentication servers. Enter a list of servers for integrated authentication.

chrome.devices.managedguest.AutoclickEnabled: Auto-click enabled.
  autoclickEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable auto-click.
    TRUE: Enable auto-click.

chrome.devices.managedguest.AutoOpen: Auto open downloaded files.
  autoOpenAllowedForUrls: TYPE_LIST
    Auto open URLs. If this policy is set, only downloads that match these URLs and have an auto open type will be auto opened. If this policy is left unset, all downloads matching an auto open type will be auto opened. Wildcards ("*") are allowed when appended to a URL, but cannot be entered alone.
  autoOpenFileTypes: TYPE_LIST
    Auto open files types. Do not include the leading separator when listing the type. For example, use "txt", not ".txt".

chrome.devices.managedguest.AutoplayAllowlist: Autoplay video.
  autoplayAllowlist: TYPE_LIST
    Allowed URLs. URL patterns allowed to autoplay. Prefix domain with [*.] to include all subdomains. Use * to allow all domains.

chrome.devices.managedguest.Avatar: Custom avatar.
  downloadUri: TYPE_STRING

chrome.devices.managedguest.BookmarkBarEnabled: Bookmark bar.
  bookmarkBarEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable bookmark bar.
    TRUE: Enable bookmark bar.

chrome.devices.managedguest.BrowserHistory: Browser history.
  savingBrowserHistoryDisabled: TYPE_BOOL
    true: Never save browser history.
    false: Always save browser history.

chrome.devices.managedguest.BuiltInDnsClientEnabled: Built-in DNS client.
  builtInDnsClientEnabled: TYPE_ENUM
    UNSET: Use the built-in DNS client on macOS, Android and Chrome OS. Allow the user to change the setting.
    FALSE: Never use the built-in DNS client.
    TRUE: Always use the built-in DNS client if available.

chrome.devices.managedguest.CaptivePortalAuthenticationIgnoresProxy: Ignore proxy on captive portals.
  captivePortalAuthenticationIgnoresProxy: TYPE_BOOL
    true: Ignore policies for captive portal pages.
    false: Keep policies for captive portal pages.

chrome.devices.managedguest.CaretHighlightEnabled: Caret highlight.
  caretHighlightEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable caret highlight.
    TRUE: Enable caret highlight.

chrome.devices.managedguest.Cecpq2Enabled: CECPQ2 post-quantum key-agreement for TLS.
  cecpq2Enabled: TYPE_BOOL
    true: Enable default CECPQ2 rollout process.
    false: Disable CECPQ2.

chrome.devices.managedguest.CpuTaskScheduler: CPU task scheduler.
  schedulerConfiguration: TYPE_ENUM
    USER_CHOICE: Allow the user to decide.
    CONSERVATIVE: Optimize for stability.
    PERFORMANCE: Optimize for performance.

chrome.devices.managedguest.CursorHighlightEnabled: Cursor highlight.
  cursorHighlightEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable cursor highlight.
    TRUE: Enable cursor highlight.

chrome.devices.managedguest.CustomTermsOfService: Custom terms of service.
  downloadUri: TYPE_STRING

chrome.devices.managedguest.DefaultInsecureContentSetting: Control use of insecure content exceptions.
  defaultInsecureContentSetting: TYPE_ENUM
    BLOCK_INSECURE_CONTENT: Do not allow any site to load blockable mixed content.
    ALLOW_EXCEPTIONS_INSECURE_CONTENT: Allow users to add exceptions to allow blockable mixed content.

chrome.devices.managedguest.DefaultPrintColor: Default color printing mode.
  printingColorDefault: TYPE_ENUM
    COLOR: Color.
    MONOCHROME: Black and white.

chrome.devices.managedguest.DefaultPrintDuplexMode: Default page sides.
  printingDuplexDefault: TYPE_ENUM
    SIMPLEX: One-sided.
    SHORT_EDGE_DUPLEX: Short-edge two-sided printing.
    LONG_EDGE_DUPLEX: Long-edge two-sided printing.

chrome.devices.managedguest.DefaultPrinters: Print preview default.
  specifyDefaultPrinter: TYPE_BOOL
    true: Define the default printer.
    false: Use default print behavior.
  printerTypes: TYPE_ENUM
    CLOUD_AND_LOCAL: Cloud and local.
    CLOUD: Cloud only.
    LOCAL: Local only.
  printerMatching: TYPE_ENUM
    NAME: Match by name.
    ID: Match by ID.
  defaultPrinterPattern: TYPE_STRING
    Default printer. Enter a regular expression that matches the desired default printer selection. The print preview will default to the first printer to match the regular expression. For example, to match a printer named "Initech Lobby", use "Initech Lobby". To match any of {print "initech-lobby-1"}, {print "initech-lobby-2"}, etc. you could use {print "initech-lobby-.$"}. To match {print "initech-lobby-guest"} or {print "initech-partner-guest"}, you could use {print "initech-.*-guest"}.

chrome.devices.managedguest.DefaultSensorsSetting: Sensors.
  defaultSensorsSetting: TYPE_ENUM
    ALLOW_SENSORS: Allow sites to access sensors.
    BLOCK_SENSORS: Do not allow any site to access sensors.
    UNSET: Allow the user to decide if a site may access sensors.
  sensorsAllowedForUrls: TYPE_LIST
    Allow access to sensors on these sites. <br>For detailed information on valid url patterns, please see https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns. Note: using only the "*" wildcard is not valid.
  sensorsBlockedForUrls: TYPE_LIST
    Block access to sensors on these sites. For detailed information on valid url patterns, please see https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns Note: using only the "*" wildcard is not valid.

chrome.devices.managedguest.DeletePrintJobHistoryAllowed: Print job history deletion.
  deletePrintJobHistoryAllowed: TYPE_BOOL
    true: Allow print job history to be deleted.
    false: Do not allow print job history to be deleted.

chrome.devices.managedguest.DeveloperTools: Developer tools.
  developerToolsAvailability: TYPE_ENUM
    ALWAYS_ALLOW_DEVELOPER_TOOLS: Always allow use of built-in developer tools.
    ALLOW_DEVELOPER_TOOLS_EXCEPT_FORCE_INSTALLED: Allow use of built-in developer tools except for force-installed extensions.
    NEVER_ALLOW_DEVELOPER_TOOLS: Never allow use of built-in developer tools.

chrome.devices.managedguest.DeviceAllowMgsToStoreDisplayProperties: Persist display settings.
  deviceAllowMgsToStoreDisplayProperties: TYPE_BOOL
    true: Display settings set in a managed guest session will persist across sessions.
    false: Display settings set in a managed guest session will not persist across sessions.

chrome.devices.managedguest.DictationEnabled: Dictation.
  dictationEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable dictation.
    TRUE: Enable dictation.

chrome.devices.managedguest.DisableSafeBrowsingProceedAnyway: Disable bypassing Safe Browsing warnings.
  disableSafeBrowsingProceedAnyway: TYPE_BOOL
    true: Do not allow user to bypass Safe Browsing warning.
    false: Allow user to bypass Safe Browsing warning.

chrome.devices.managedguest.DisplayCapturePermissionsPolicyEnabled: Insecure Media Capture.
  displayCapturePermissionsPolicyEnabled: TYPE_BOOL
    true: Deny insecure requests to access display.
    false: Allow requests to access display from non-allowlisted contexts.

chrome.devices.managedguest.DnsInterceptionChecksEnabled: DNS interception checks enabled.
  dnsInterceptionChecksEnabled: TYPE_BOOL
    true: Perform DNS interception checks.
    false: Do not perform DNS interception checks.

chrome.devices.managedguest.DnsOverHttps: DNS-over-HTTPS.
  dnsOverHttpsMode: TYPE_ENUM
    OFF: Disable DNS-over-HTTPS.
    AUTOMATIC: Enable DNS-over-HTTPS with insecure fallback.
    SECURE: Enable DNS-over-HTTPS without insecure fallback.
    UNSET: May send DNS-over-HTTPS requests to user's configured custom name server.
  dnsOverHttpsTemplates: TYPE_LIST
    DNS-over-HTTPS templates. URI templates of desired DNS-over-HTTPS resolvers. If the URI template contains a '{?dns}' variable, requests to the resolver will use GET; otherwise requests will use POST.

chrome.devices.managedguest.DownloadRestrictions: Download restrictions.
  safeBrowsingDownloadRestrictions: TYPE_ENUM
    NO_SPECIAL_RESTRICTIONS: No special restrictions.
    BLOCK_ALL_MALICIOUS_DOWNLOAD: Block all malicious downloads.
    BLOCK_DANGEROUS_DOWNLOAD: Block dangerous downloads.
    BLOCK_POTENTIALLY_DANGEROUS_DOWNLOAD: Block potentially dangerous downloads.
    BLOCK_ALL_DOWNLOAD: Block all downloads.

chrome.devices.managedguest.EmojiSuggestionEnabled: Emoji suggestions.
  emojiSuggestionEnabled: TYPE_BOOL
    true: Enable emoji suggestions when users type.
    false: Disable emoji suggestions when users type.

chrome.devices.managedguest.EnableCaptureAllowedSettings: Screen video capture allowed by sites.
  screenCaptureAllowedByOrigins: TYPE_LIST
    Allow tab, window, and desktop video capture by these sites. Sites set in this list will be ignored in the 'screenCaptureAllowed' field.
  windowCaptureAllowedByOrigins: TYPE_LIST
    Allow tab and window video capture by these sites. Sites set in this list will be ignored in the 'screenCaptureAllowedByOrigins' and 'screenCaptureAllowed' fields.
  tabCaptureAllowedByOrigins: TYPE_LIST
    Allow tab video capture by these sites. Sites set in this list will be ignored in the 'windowCaptureAllowedByOrigins', 'screenCaptureAllowedByOrigins', and 'screenCaptureAllowed' fields.
  sameOriginTabCaptureAllowedByOrigins: TYPE_LIST
    Allow tab video capture (same site only) by these sites. Sites set in this list will be ignored in the 'tabCaptureAllowedByOrigins', 'windowCaptureAllowedByOrigins', 'screenCaptureAllowedByOrigins', and 'screenCaptureAllowed' fields.

chrome.devices.managedguest.EnableDeprecatedPrivetPrinting: Deprecated privet printing.
  enableDeprecatedPrivetPrinting: TYPE_BOOL
    true: Enable deprecated privet printing.
    false: Disable deprecated privet printing.

chrome.devices.managedguest.EnhancedNetworkVoicesInSelectToSpeakAllowed: Allow the enhanced network text-to-speech voices in Select-to-speak.
  enhancedNetworkVoicesInSelectToSpeakAllowed: TYPE_BOOL
    true: Allow the user to decide.
    false: Disallow enhanced network text-to-speech voices when using Select-to-Speak.

chrome.devices.managedguest.EnterpriseHardwarePlatformApiEnabled: Enterprise Hardware Platform API.
  enterpriseHardwarePlatformApiEnabled: TYPE_BOOL
    true: Allow managed extensions to use the Enterprise Hardware Platform API.
    false: Do not allow managed extensions to use the Enterprise Hardware Platform API.

chrome.devices.managedguest.ExplicitlyAllowedNetworkPorts: Allowed network ports.
  explicitlyAllowedNetworkPorts: TYPE_LIST
    {'value': '554', 'description': 'port 554 (expires 2021/10/15).'}

chrome.devices.managedguest.ExternalStorage: External storage devices.
  externalStorageDevices: TYPE_ENUM
    READ_WRITE: Allow external storage devices.
    READ_ONLY: Allow external storage devices (read only).
    DISALLOW: Disallow external storage devices.

chrome.devices.managedguest.FastPairEnabled: Fast Pair (fast Bluetooth pairing).
  fastPairEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Force Fast Pair (fast Bluetooth pairing) to be disabled.
    TRUE: Force Fast Pair (fast Bluetooth pairing) to be enabled.

chrome.devices.managedguest.FileSystemRead: File system read access.
  defaultFileSystemReadGuardSetting: TYPE_ENUM
    UNSET: Allow the user to decide.
    ASK_FILE_SYSTEM_READ: Allow sites to ask the user to grant read access to files and directories.
    BLOCK_FILE_SYSTEM_READ: Do not allow sites to request read access to files and directories.
  fileSystemReadAskForUrls: TYPE_LIST
    Allow file system read access on these sites. For detailed information on valid url patterns, please see URL patterns at https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns. Note: using only the "*" wildcard is not valid.
  fileSystemReadBlockedForUrls: TYPE_LIST
    Block read access on these sites. For detailed information on valid url patterns, please see URL patterns at https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns. Note: using only the "*" wildcard is not valid.

chrome.devices.managedguest.FileSystemWrite: File system write access.
  defaultFileSystemWriteGuardSetting: TYPE_ENUM
    UNSET: Allow the user to decide.
    ASK_FILE_SYSTEM_WRITE: Allow sites to ask the user to grant write access to files and directories.
    BLOCK_FILE_SYSTEM_WRITE: Do not allow sites to request write access to files and directories.
  fileSystemWriteAskForUrls: TYPE_LIST
    Allow write access to files and directories on these sites. For detailed information on valid url patterns, please see URL patterns at https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns. Note: using only the "*" wildcard is not valid.
  fileSystemWriteBlockedForUrls: TYPE_LIST
    Block write access to files and directories on these sites. For detailed information on valid url patterns, please see URL patterns at https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns. Note: using only the "*" wildcard is not valid.

chrome.devices.managedguest.ForceMaximizeOnFirstRun: Maximize window on first run.
  forceMaximizeOnFirstRun: TYPE_BOOL
    true: Maximize the first browser window on first run.
    false: Default system behavior (depends on screen size).

chrome.devices.managedguest.FullscreenAllowed: Fullscreen mode.
  fullscreenAllowed: TYPE_BOOL
    true: Allow fullscreen mode.
    false: Do not allow fullscreen mode.

chrome.devices.managedguest.GloballyScopeHttpAuthCacheEnabled: Globally scoped HTTP authentication cache.
  globallyScopeHttpAuthCacheEnabled: TYPE_BOOL
    true: HTTP authentication credentials entered in the context of one site will automatically be used in the context of another.
    false: HTTP authentication credentials are scoped to top-level sites.

chrome.devices.managedguest.GoogleCast: Cast.
  showCastIconInToolbar: TYPE_BOOL
    true: Always show the Cast icon in the toolbar.
    false: Do not show the Cast icon in the toolbar by default, but let users choose.
  enableMediaRouter: TYPE_BOOL
    true: Allow users to Cast.
    false: Do not allow users to Cast.

chrome.devices.managedguest.HighContrastEnabled: High contrast.
  highContrastEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable high contrast.
    TRUE: Enable high contrast.

chrome.devices.managedguest.HomeButton: Home button.
  showHomeButton: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Never show "Home" button.
    TRUE: Always show "Home" button.

chrome.devices.managedguest.Homepage: Homepage.
  homepageIsNewTabPage: TYPE_ENUM
    UNSET: Allow user to configure.
    FALSE: Homepage is always the URL set in 'homepageLocation'.
    TRUE: Homepage is always the new tab page.
  homepageLocation: TYPE_STRING
    Homepage URL.

chrome.devices.managedguest.HstsPolicyBypassList: HSTS policy bypass list.
  hstsPolicyBypassList: TYPE_LIST
    List of hostnames that will bypass the HSTS policy check . Enter a list of hostnames that will be exempt from the HSTS policy check.

chrome.devices.managedguest.IdleSettings: Idle settings.
  mgsActionOnDeviceIdle: TYPE_ENUM
    SLEEP: Sleep.
    LOGOUT: Logout.
    SHUTDOWN: Shutdown.
    DO_NOTHING: Do nothing.
  mgsIdleTimeoutMinutes: TYPE_STRING
    Idle time in minutes. Leave empty for system default.
  mgsActionOnLidClose: TYPE_ENUM
    SLEEP: Sleep.
    LOGOUT: Logout.
    SHUTDOWN: Shutdown.
    DO_NOTHING: Do nothing.

chrome.devices.managedguest.IncognitoMode: Incognito mode.
  incognitoModeAvailability: TYPE_ENUM
    AVAILABLE: Allow incognito mode.
    UNAVAILABLE: Disallow incognito mode.
    FORCED: Force incognito mode.

chrome.devices.managedguest.InsecureContentAllowedForUrls: Allow insecure content on these sites.
  insecureContentAllowedForUrls: TYPE_LIST
    URL patterns to allow.

chrome.devices.managedguest.InsecureContentBlockedForUrls: Block insecure content on these sites.
  insecureContentBlockedForUrls: TYPE_LIST
    URL patterns to block.

chrome.devices.managedguest.InsecureFormsWarningsEnabled: Insecure forms.
  insecureFormsWarningsEnabled: TYPE_BOOL
    true: Show warnings and disable autofill on insecure forms.
    false: Do not show warnings and disable autofill on insecure forms.

chrome.devices.managedguest.InsecurePrivateNetworkRequestsAllowed: Requests from insecure websites to more-private network endpoints.
  insecurePrivateNetworkRequestsAllowed: TYPE_BOOL
    true: Insecure websites are allowed to make requests to any network endpoint.
    false: Allow the user to decide.
  insecurePrivateNetworkRequestsAllowedForUrls: TYPE_LIST
    URL patterns to allow. Network requests to more-private endpoints, from insecure origins not covered by the patterns specified here, will use the global default value.

chrome.devices.managedguest.IntensiveWakeUpThrottlingEnabled: Javascript IntensiveWakeUpThrottling.
  intensiveWakeUpThrottlingEnabled: TYPE_ENUM
    UNSET: Allow throttling of background javascript timers to be controlled by Chrome's logic and configurable by users.
    FALSE: Force no throttling of background javajscript timers.
    TRUE: Force throttling of background javascript timers.

chrome.devices.managedguest.IntranetRedirectBehavior: Intranet Redirection Behavior.
  intranetRedirectBehavior: TYPE_ENUM
    DEFAULT: Use default browser behavior.
    DISABLE_INTERCEPTION_CHECKS_DISABLE_INFOBAR: Disable DNS interception checks and did-you-mean "http://intranetsite/" infobars.
    DISABLE_INTERCEPTION_CHECKS_ENABLE_INFOBAR: Disable DNS interception checks; allow did-you-mean "http://intranetsite/" infobars.
    ENABLE_INTERCEPTION_CHECKS_ENABLE_INFOBAR: Allow DNS interception checks and did-you-mean "http://intranetsite/" infobars.

chrome.devices.managedguest.JavaScriptJitSettings: JavaScript JIT.
  defaultJavaScriptJitSetting: TYPE_ENUM
    ALLOW_JAVA_SCRIPT_JIT: Allow sites to run JavaScript JIT.
    BLOCK_JAVA_SCRIPT_JIT: Do not allow sites to run JavaScript JIT.
  javaScriptJitAllowedForSites: TYPE_LIST
    Allow JavaScript to use JIT on these sites.
  javaScriptJitBlockedForSites: TYPE_LIST
    Block JavaScript from using JIT on these sites.

chrome.devices.managedguest.KerberosTickets: Kerberos tickets.
  kerberosEnabled: TYPE_BOOL
    false: Disable Kerberos.
    true: Enable Kerberos.

chrome.devices.managedguest.KeyboardFocusHighlightEnabled: Keyboard focus highlighting.
  keyboardFocusHighlightEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable keyboard focus highlighting.
    TRUE: Enable keyboard focus highlighting.

chrome.devices.managedguest.KeyboardFunctionKeys: Keyboard.
  keyboardDefaultToFunctionKeys: TYPE_BOOL
    true: Treat top-row keys as function keys, but allow user to change.
    false: Treat top-row keys as media keys, but allow user to change.

chrome.devices.managedguest.LargeCursorEnabled: Large cursor.
  largeCursorEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable large cursor.
    TRUE: Enable large cursor.

chrome.devices.managedguest.LensRegionSearchEnabled: Google Lens region search.
  lensRegionSearchEnabled: TYPE_BOOL
    true: Enable Google Lens region search.
    false: Disable Google Lens region search.

chrome.devices.managedguest.LockIconInAddressBarEnabled: Lock icon in the omnibox for secure connections.
  lockIconInAddressBarEnabled: TYPE_BOOL
    true: Use the lock icon for secure connections.
    false: Use default icons for secure connections.

chrome.devices.managedguest.LookalikeWarningAllowlistDomains: Suppress lookalike domain warnings on domains.
  lookalikeWarningAllowlistDomains: TYPE_LIST
    Allowlisted Domains. Enter list of domains where Chrome should prevent the display of lookalike URL warnings.

chrome.devices.managedguest.ManagedBookmarksSetting: Managed bookmarks.
  toplevelName: TYPE_STRING
  name: TYPE_STRING
  url: TYPE_STRING

chrome.devices.managedguest.ManagedGuestSession: Managed guest session.
  userDisplayName: TYPE_STRING
    Session name to display on login screen.
  managedGuestSessionAvailability: TYPE_ENUM
    NOT_ALLOWED: Do not allow managed guest sessions.
    ALLOWED: Allow managed guest sessions.
    AUTO_LAUNCH: Auto-launch managed guest session.
  autoLaunchDelaySeconds: TYPE_INT64
    Auto-launch delay. Number of seconds to delay before launching the managed guest session. During this time the sign-in screen will be visible.
  deviceHealthMonitoring: TYPE_BOOL
    true: Enable device health monitoring.
    false: Disable device health monitoring.
  systemLogUploadEnabled: TYPE_BOOL
    true: Enable device system log upload.
    false: Disable device system log upload.
  displayRotation: TYPE_ENUM
    UNSET: No policy set (allow the device to keep its current display rotation).
    ROTATE_0: 0 degrees.
    ROTATE_90: 90 degrees.
    ROTATE_180: 180 degrees.
    ROTATE_270: 270 degrees.

chrome.devices.managedguest.MaxInvalidationFetchDelay: Policy fetch delay.
  seconds: TYPE_INT64
  nanos: TYPE_INT32

chrome.devices.managedguest.MonoAudioEnabled: Mono audio.
  monoAudioEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable mono audio.
    TRUE: Enable mono audio.

chrome.devices.managedguest.NetworkFileShares: Network file shares.
  networkFileSharesAllowed: TYPE_BOOL
    true: Allow network file shares.
    false: Block network file shares.
  netBiosShareDiscoveryEnabled: TYPE_BOOL
    true: Use NetBIOS discovery.
    false: Do not allow NetBIOS discovery.
  ntlmShareAuthenticationEnabled: TYPE_BOOL
    true: Use NTLM authentication.
    false: Do not use NTLM authentication.
  mode: TYPE_ENUM
    DROP_DOWN:
    PRE_MOUNT:
  shareUrl: TYPE_STRING

chrome.devices.managedguest.NewTabPageLocation: New tab page.
  newTabPageLocation: TYPE_STRING
    New tab URL (leave empty for default).

chrome.devices.managedguest.Notifications: Notifications.
  defaultNotificationsSetting: TYPE_ENUM
    UNSET: Allow the user to decide.
    ALLOW_NOTIFICATIONS: Allow sites to show desktop notifications.
    BLOCK_NOTIFICATIONS: Do not allow sites to show desktop notifications.
    ASK_NOTIFICATIONS: Always ask the user if a site can show desktop notifications.
  notificationsAllowedForUrls: TYPE_LIST
    Allow these sites to show notifications. Urls to allow notifications. Prefix domain with [*.] to include all subdomains.
  notificationsBlockedForUrls: TYPE_LIST
    Block notifications on these sites. Urls to block notifications. Prefix domain with [*.] to include all subdomains.

chrome.devices.managedguest.OverrideSecurityRestrictionsOnInsecureOrigin: Override insecure origin restrictions.
  overrideSecurityRestrictionsOnInsecureOrigin: TYPE_LIST
    Origin or hostname patterns to ignore insecure origins security restrictions.

chrome.devices.managedguest.PaymentMethodQueryEnabled: Payment methods.
  paymentMethodQueryEnabled: TYPE_BOOL
    true: Allow websites to check if the user has payment methods saved.
    false: Always tell websites that no payment methods are saved.

chrome.devices.managedguest.Popups: Pop-ups.
  defaultPopupsSetting: TYPE_ENUM
    UNSET: Allow the user to decide.
    ALLOW_POPUPS: Allow all pop-ups.
    BLOCK_POPUPS: Block all pop-ups.
  popupsAllowedForUrls: TYPE_LIST
    Allow pop-ups on these sites. Urls to allow pop-ups.
  popupsBlockedForUrls: TYPE_LIST
    Block pop-ups on these sites. Urls to block pop-ups.

chrome.devices.managedguest.PrimaryMouseButtonSwitch: Primary mouse button.
  primaryMouseButtonSwitch: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Left button is primary.
    TRUE: Right button is primary.

chrome.devices.managedguest.PrinterTypeDenyList: Blocked printer types.
  printerTypeDenyList: TYPE_LIST
    {'value': 'privet', 'description': 'Zeroconf-based (mDNS + DNS-SD) protocol.'}

chrome.devices.managedguest.PrintHeaderFooter: Print headers and footers.
  printHeaderFooter: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Never print headers and footers.
    TRUE: Always print headers and footers.

chrome.devices.managedguest.PrintingAllowedBackgroundGraphicsModes: Background graphics printing restriction.
  printingAllowedBackgroundGraphicsModes: TYPE_ENUM
    ANY: Allow the user to decide.
    ENABLED: Always require printing of background images.
    DISABLED: Do not allow printing of background images.

chrome.devices.managedguest.PrintingAllowedPinModes: Restrict PIN printing mode.
  printingAllowedPinModes: TYPE_ENUM
    ANY_PIN_PRINTING_MODE: Do not restrict PIN printing mode.
    PIN_PRINTING_ONLY: Always require PIN printing.
    NON_PIN_PRINTING_ONLY: Do not allow PIN printing.

chrome.devices.managedguest.PrintingBackgroundGraphicsDefault: Background graphics printing default.
  printingBackgroundGraphicsDefault: TYPE_ENUM
    DISABLED: Disable background graphics printing mode by default.
    ENABLED: Enable background graphics printing mode by default.

chrome.devices.managedguest.PrintingMaxSheetsAllowed: Maximum sheets.
  value: TYPE_INT64

chrome.devices.managedguest.PrintingPaperSizeDefault: Default printing page size.
  printingPaperSizeEnum: TYPE_ENUM
    UNSET: No policy set.
    NA_LETTER_8_5X11IN: Letter.
    NA_LEGAL_8_5X14IN: Legal.
    ISO_A4_210X297MM: A4.
    NA_LEDGER_11X17IN: Tabloid.
    ISO_A3_297X420MM: A3.
    CUSTOM: Custom.
  printingPaperSizeWidth: TYPE_STRING
    Page width (in millimeters).
  printingPaperSizeHeight: TYPE_STRING
    Page height (in millimeters).

chrome.devices.managedguest.PrintingPinDefault: Default PIN printing mode.
  printingPinDefault: TYPE_ENUM
    PIN_PRINTING: With PIN.
    NOT_PIN_PRINTING: Without PIN.

chrome.devices.managedguest.PrintJobHistoryExpirationPeriodNew: Print job history retention period.
  seconds: TYPE_INT64
  nanos: TYPE_INT32

chrome.devices.managedguest.PrivacyScreenEnabled: Privacy screen.
  privacyScreenEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Always disable the privacy screen.
    TRUE: Always enable the privacy screen.

chrome.devices.managedguest.PromptForDownloadLocation: Download location prompt.
  promptForDownloadLocation: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Do not ask the user (downloads start immediately).
    TRUE: Ask the user where to save the file before downloading.

chrome.devices.managedguest.QuickAnswersEnabled: Quick Answers.
  quickAnswersEnabled: TYPE_BOOL
    true: Enable Quick Answers.
    false: Disable Quick Answers.
  quickAnswersDefinitionEnabled: TYPE_BOOL
    true: Enable Quick Answers definition.
    false: Disable Quick Answers definition.
  quickAnswersTranslationEnabled: TYPE_BOOL
    true: Enable Quick Answers translation.
    false: Disable Quick Answers translation.
  quickAnswersUnitConversionEnabled: TYPE_BOOL
    true: Enable Quick Answers unit conversion.
    false: Disable Quick Answers unit conversion.

chrome.devices.managedguest.QuicProtocol: QUIC protocol.
  quicAllowed: TYPE_BOOL
    true: Enable.
    false: Disable.

chrome.devices.managedguest.RemoteAccessHostClientDomainList: Remote access clients.
  remoteAccessHostClientDomainList: TYPE_LIST
    Remote access client domain. Configure the required domain names for remote access clients.

chrome.devices.managedguest.RemoteAccessHostDomainList: Remote access hosts.
  remoteAccessHostDomainList: TYPE_LIST
    Remote access host domain. Configure the required domain names for remote access hosts.

chrome.devices.managedguest.RemoteAccessHostFirewallTraversal: Firewall traversal.
  remoteAccessHostFirewallTraversal: TYPE_BOOL
    true: Enable firewall traversal.
    false: Disable firewall traversal.
  remoteAccessHostAllowRelayedConnection: TYPE_BOOL
    true: Enable the use of relay servers.
    false: Disable the use of relay servers.
  remoteAccessHostUdpPortRange: TYPE_STRING
    UDP port range. Format: minimum-maximum (e.g. 12400-12409). If unset, any port may be used.

chrome.devices.managedguest.RemoteDebuggingAllowed: Allow remote debugging.
  remoteDebuggingAllowed: TYPE_BOOL
    true: Allow use of the remote debugging.
    false: Do not allow use of the remote debugging.

chrome.devices.managedguest.RequireOnlineRevocationChecksForLocalAnchors: Require online OCSP/CRL checks for local trust anchors.
  requireOnlineRevocationChecksForLocalAnchors: TYPE_BOOL
    true: Perform revocation checking for successfully validated server certificates signed by locally installed CA certificates.
    false: Use existing online revocation-checking settings.

chrome.devices.managedguest.RestrictPrintColor: Restrict color printing mode.
  printingAllowedColorModes: TYPE_ENUM
    ANY_COLOR_MODE: Do not restrict color printing mode.
    COLOR_ONLY: Color only.
    MONOCHROME_ONLY: Black and white only.

chrome.devices.managedguest.RestrictPrintDuplexMode: Restrict page sides.
  printingAllowedDuplexModes: TYPE_ENUM
    ANY_DUPLEX_MODE: Do not restrict duplex printing mode.
    SIMPLEX_ONLY: One-sided only.
    DUPLEX_ONLY: Two-sided only.

chrome.devices.managedguest.SafeSearchRestrictedMode: SafeSearch and Restricted Mode.
  forceGoogleSafeSearch: TYPE_BOOL
    true: Always use SafeSearch for Google Search queries.
    false: Do not enforce SafeSearch for Google Search queries.
  forceYoutubeRestrictedMode: TYPE_ENUM
    OFF: Do not enforce Restricted Mode on YouTube.
    MODERATE: Enforce at least Moderate Restricted Mode on YouTube.
    STRICT: Enforce Strict Restricted Mode on YouTube.

chrome.devices.managedguest.SafeSitesFilterBehavior: SafeSites URL filter.
  safeSitesFilterBehavior: TYPE_ENUM
    DISABLED: Do not filter sites for adult content.
    ENABLED: Filter top level sites (but not embedded iframes) for adult content.

chrome.devices.managedguest.SandboxExternalProtocolBlocked: iframe navigation.
  sandboxExternalProtocolBlocked: TYPE_BOOL
    true: Do not allow navigation to external protocols inside a sandboxed iframe.
    false: Allow navigation to external protocols inside a sandboxed iframe.

chrome.devices.managedguest.ScreenBrightnessPercent: Screen brightness.
  brightnessEnabled: TYPE_BOOL
    true: Set initial screen brightness.
    false: Do not set initial screen brightness.
  brightnessAc: TYPE_INT64
    Screen brightness (ac power).
  brightnessBattery: TYPE_INT64
    Screen brightness (battery power).

chrome.devices.managedguest.ScreenMagnifierType: Screen magnifier.
  screenMagnifierType: TYPE_ENUM
    UNSET: Allow the user to decide.
    DISABLED: Disable screen magnifier.
    FULL_SCREEN: Enable full-screen magnifier.
    DOCKED: Enable docked magnifier.

chrome.devices.managedguest.Screenshot: Screenshot.
  disableScreenshots: TYPE_BOOL
    true: Do not allow users to take screenshots or video recordings.
    false: Allow users to take screenshots and video recordings.

chrome.devices.managedguest.ScrollToTextFragmentEnabled: Scroll to text fragment.
  scrollToTextFragmentEnabled: TYPE_BOOL
    true: Allow sites to scroll to specific text fragments via URL.
    false: Do not allow sites to scroll to specific text fragments via URL.

chrome.devices.managedguest.SearchSuggest: Search suggest.
  searchSuggestEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Never allow users to use Search Suggest.
    TRUE: Always allow users to use Search Suggest.

chrome.devices.managedguest.SecurityTokenSessionSettings: Security token removal.
  securityTokenSessionBehavior: TYPE_ENUM
    IGNORE: Nothing.
    LOGOUT: Log the user out.
    LOCK: Lock the current session.
  seconds: TYPE_INT64
  nanos: TYPE_INT32

chrome.devices.managedguest.SelectToSpeakEnabled: Select to speak.
  selectToSpeakEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable select to speak.
    TRUE: Enable select to speak.

chrome.devices.managedguest.SessionLength: Maximum user session length.
  seconds: TYPE_INT64
  nanos: TYPE_INT32

chrome.devices.managedguest.SessionLocale: Session locale.
  sessionLocalesRepeatedString: TYPE_LIST
    {'value': 'ar', 'description': 'Arabic - \u202bالعربية\u202c.'}

chrome.devices.managedguest.SharedArrayBufferUnrestrictedAccessAllowed: SharedArrayBuffer.
  sharedArrayBufferUnrestrictedAccessAllowed: TYPE_BOOL
    true: Allow sites that are not cross-origin isolated to use SharedArrayBuffers.
    false: Prevent sites that are not cross-origin isolated from using SharedArrayBuffers.

chrome.devices.managedguest.ShelfAlign: Shelf position.
  shelfAlignmentMgs: TYPE_ENUM
    BOTTOM: Bottom.
    LEFT: Left.
    RIGHT: Right.

chrome.devices.managedguest.ShowAccessibilityOptionsInSystemTrayMenu: Accessibility options in the system tray menu.
  showAccessibilityOptionsInSystemTrayMenu: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Hide accessibility options in the system tray menu.
    TRUE: Show accessibility options in the system tray menu.

chrome.devices.managedguest.ShowFullUrlsInAddressBar: URLs in the address bar.
  showFullUrlsInAddressBar: TYPE_ENUM
    UNSET: Display the default URL. Users may switch to the full URL unless on a managed Chrome OS device.
    FALSE: Display the default URL.
    TRUE: Display the full URL.

chrome.devices.managedguest.ShowLogoutButton: Show logout button in tray.
  showLogoutButtonInTray: TYPE_BOOL
    true: Show logout button in tray.
    false: Do not show logout button in tray.

chrome.devices.managedguest.SignedHttpExchangeEnabled: Signed HTTP Exchange (SXG) support.
  signedHttpExchangeEnabled: TYPE_BOOL
    true: Accept web content served as Signed HTTP Exchanges.
    false: Prevent Signed HTTP Exchanges from loading.

chrome.devices.managedguest.SimpleProxySettings: Proxy mode.
  simpleProxyMode: TYPE_ENUM
    USER_CONFIGURED: Allow user to configure.
    DIRECT: Never use a proxy.
    AUTO_DETECT: Always auto detect the proxy.
    FIXED_SERVERS: Always use the proxy specified in 'simpleProxyServerUrl'.
    PAC_SCRIPT: Always use the proxy auto-config specified in 'simpleProxyPacUrl'.
  simpleProxyServerUrl: TYPE_STRING
    Proxy server URL.
  simpleProxyPacUrl: TYPE_STRING
    Proxy server auto configuration file URL. URL of the .pac file that should be used for network connections.
  proxyBypassList: TYPE_LIST
    URLs which bypass the proxy.

chrome.devices.managedguest.SpellcheckEnabled: Spell check.
  spellcheckEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable spell check.
    TRUE: Enable spell check.

chrome.devices.managedguest.SpellCheckService: Spell check service.
  spellCheckServiceEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable the spell checking web service.
    TRUE: Enable the spell checking web service.

chrome.devices.managedguest.SpokenFeedbackEnabled: Spoken feedback.
  spokenFeedbackEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable spoken feedback.
    TRUE: Enable spoken feedback.

chrome.devices.managedguest.SslErrorOverrideAllowed: SSL error override.
  sslErrorOverrideAllowed: TYPE_BOOL
    true: Allow users to click through SSL warnings and proceed to the page.
    false: Block users from clicking through SSL warnings.

chrome.devices.managedguest.SslErrorOverrideAllowedForOrigins: SSL error override allowed domains.
  sslErrorOverrideAllowedForOrigins: TYPE_LIST
    Domains that allow clicking through SSL warnings. Enter a list of domain names.

chrome.devices.managedguest.SslVersionMin: Minimum SSL version enabled.
  sslVersionMin: TYPE_ENUM
    TL_SV_1: TLS 1.0.
    TL_SV_1_1: TLS 1.1.
    TL_SV_1_2: TLS 1.2.
    SSL_V_3: SSL3.

chrome.devices.managedguest.StartupBrowserLaunch: Browser launch on startup.
  startupBrowserWindowLaunchSuppressed: TYPE_BOOL
    true: Do not launch the browser on startup.
    false: Automatically launch the browser on startup.

chrome.devices.managedguest.StartupPages: Pages to load on startup.
  restoreOnStartupUrls: TYPE_LIST
    Startup pages. Example: https://example.com.

chrome.devices.managedguest.StickyKeysEnabled: Sticky keys.
  stickyKeysEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable sticky keys.
    TRUE: Enable sticky keys.

chrome.devices.managedguest.SuggestedContentEnabled: Suggested content.
  suggestedContentEnabled: TYPE_BOOL
    true: Enable suggested content.
    false: Disable suggested content.

chrome.devices.managedguest.SuggestLogoutAfterClosingLastWindow: Display the logout confirmation dialog.
  suggestLogoutAfterClosingLastWindow: TYPE_BOOL
    true: Show logout dialog when the last window is closed.
    false: Do not show logout dialog when the last window is closed.

chrome.devices.managedguest.SuppressCrossOriginIframeDialogs: Cross-origin JavaScript dialogs.
  suppressCrossOriginIframeDialogs: TYPE_BOOL
    true: Block JavaScript dialogs triggered from a cross-origin iframe.
    false: Allow JavaScript dialogs triggered from a cross-origin iframe.

chrome.devices.managedguest.SuppressUnsupportedOsWarning: Unsupported system warning.
  suppressUnsupportedOsWarning: TYPE_BOOL
    true: Suppress warnings when Chrome is running on an unsupported system.
    false: Allow Chrome to display warnings when running on an unsupported system.

chrome.devices.managedguest.SystemFeaturesDisableList: Disabled system features.
  systemFeaturesDisableList: TYPE_LIST
    {'value': 'camera', 'description': 'Camera.'}

chrome.devices.managedguest.SystemFeaturesDisableMode: Disabled system features visibility.
  systemFeaturesDisableMode: TYPE_ENUM
    BLOCKED: Show disabled application icons.
    HIDDEN: Hide application icons.

chrome.devices.managedguest.TargetBlankImpliesNoOpener: Popup interactions.
  targetBlankImpliesNoOpener: TYPE_BOOL
    true: Block popups opened with a target of _blank from interacting with the page that opened the popup.
    false: Allow popups opened with a target of _blank to interact with the page that opened the popup.

chrome.devices.managedguest.TaskManager: Task manager.
  taskManagerEndProcessEnabled: TYPE_BOOL
    true: Allow users to end processes with the Chrome task manager.
    false: Block users from ending processes with the Chrome task manager.

chrome.devices.managedguest.Translate: Google Translate.
  translateEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Never offer translation.
    TRUE: Always offer translation.

chrome.devices.managedguest.UnifiedDesktop: Unified Desktop (BETA).
  unifiedDesktopEnabledByDefault: TYPE_BOOL
    true: Make Unified Desktop mode available to user.
    false: Do not make Unified Desktop mode available to user.

chrome.devices.managedguest.UrlBlocking: URL blocking.
  urlBlocklist: TYPE_LIST
    Blocked URLs. Any URL in this list will be blocked, unless it also appears in the list of exceptions specified in 'urlAllowlist'. Maximum of 1000 URLs. Note: to block OS and browser settings set the 'chrome.users.SystemFeaturesDisableList' policy instead of blocking 'chrome://' URLs.
  urlAllowlist: TYPE_LIST
    Blocked URL exceptions. Any URL that matches an entry in this exception list will be allowed, even if it matches an entry in the blocked URLs. Wildcards ("*") are allowed when appended to a URL, but cannot be entered alone. Maximum of 1000 URLs. .

chrome.devices.managedguest.UserAgentClientHintsEnabled: User-Agent client hints.
  userAgentClientHintsEnabled: TYPE_BOOL
    true: Allow User-Agent client hints.
    false: Disable User-Agent client hints.

chrome.devices.managedguest.UserFeedbackAllowed: Allow user feedback.
  userFeedbackAllowed: TYPE_BOOL
    true: Allow user feedback.
    false: Do not allow user feedback.

chrome.devices.managedguest.UserPrintersAllowed: Printer management.
  userPrintersAllowed: TYPE_BOOL
    true: Allow users to add new printers.
    false: Do not allow users to add new printers.

chrome.devices.managedguest.VideoCaptureAllowedUrls: Video input allowed URLs.
  videoCaptureAllowedUrls: TYPE_LIST
    URL patterns to allow. URLs that will be granted access to the video input device without a prompt. Prefix domain with [*.] to include subdomains.

chrome.devices.managedguest.VideoInput: Built-in camera access.
  videoCaptureAllowed: TYPE_BOOL
    true: Enable camera input for websites and apps.
    false: Disable camera input for websites and apps.

chrome.devices.managedguest.VirtualKeyboardEnabled: On-screen keyboard.
  virtualKeyboardEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable on-screen keyboard.
    TRUE: Enable on-screen keyboard.

chrome.devices.managedguest.Wallpaper: Custom wallpaper.
  downloadUri: TYPE_STRING

chrome.devices.managedguest.WebRtcAllowLegacyTlsProtocols: Legacy TLS/DTLS downgrade in WebRTC.
  webRtcAllowLegacyTlsProtocols: TYPE_BOOL
    true: Enable WebRTC peer connections downgrading to obsolete versions of the TLS/DTLS (DTLS 1.0, TLS 1.0 and TLS 1.1) protocols.
    false: Disable WebRTC peer connections downgrading to obsolete versions of the TLS/DTLS (DTLS 1.0, TLS 1.0 and TLS 1.1) protocols.

chrome.devices.managedguest.WebRtcIpHandling: WebRTC IP handling.
  webRtcIpHandling: TYPE_ENUM
    EFAULT: WebRTC will use all available interfaces when searching for the best path.
    EFAULT_PUBLIC_AND_PRIVATE_INTERFACES: WebRTC will only use the interface connecting to the public Internet, but may connect using private IP addresses.
    EFAULT_PUBLIC_INTERFACE_ONLY: WebRTC will only use the interface connecting to the public Internet, and will not connect using private IP addresses.
    ISABLE_NON_PROXIED_UDP: WebRTC will use TCP on the public-facing interface, and will only use UDP if supported by a configured proxy.

chrome.devices.managedguest.WebSerialPortAccess: Serial Port API.
  defaultSerialGuardSetting: TYPE_ENUM
    BLOCK_SERIAL: Do not allow any site to request access to serial ports via the Serial Port API.
    ALLOW_ASK_SERIAL: Allow sites to ask the user to grant access to a serial ports via the Serial Port API.
    UNSET: Allow the user to decide.
  serialAskForUrls: TYPE_LIST
    Allow the Serial API on these sites. List of URLs that specify websites that will be allowed to ask users to grant them access to the serial ports. Prefix domain with [*.] to include subdomains.
  serialBlockedForUrls: TYPE_LIST
    Block the Serial API on these sites. List of URLs patterns that specify which websites can't ask users to grant them access to a serial port. Prefix domain with [*.] to include subdomains.

chrome.devices.managedguest.WebSqlInThirdPartyContextEnabled: WebSQL in third-party context.
  webSqlInThirdPartyContextEnabled: TYPE_BOOL
    true: Allow WebSQL in third-party contexts.
    false: Do not allow WebSQL in third-party contexts.

chrome.devices.managedguest.WebUsbPortAccess: Controls which websites can ask for USB access.
  defaultWebUsbGuardSetting: TYPE_ENUM
    BLOCK_WEB_USB: Do not allow any site to request access.
    ASK_WEB_USB: Allow sites to ask the user for access.
    UNSET: Allow the user to decide if sites can ask.
  webUsbAskForUrls: TYPE_LIST
    Allow these sites to ask for USB access. For detailed information on valid url patterns, please see URL patterns at https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns. Note: using only the "*" wildcard is not valid.
  webUsbBlockedForUrls: TYPE_LIST
    Block these sites from asking for USB access. For detailed information on valid url patterns, please see URL patterns at https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns. Note: using only the "*" wildcard is not valid.

chrome.devices.managedguest.WpadQuickCheckEnabled: WPAD optimization.
  wpadQuickCheckEnabled: TYPE_BOOL
    true: Enable Web Proxy Auto-Discovery (WPAD) optimization.
    false: Disable Web Proxy Auto-Discovery (WPAD) optimization.

chrome.devices.MobileDataRoaming: Mobile data roaming.
  dataRoamingEnabled: TYPE_BOOL
    true: Allow mobile data roaming.
    false: Do not allow mobile data roaming.

chrome.devices.PowerManagement: Power management.
  loginScreenPowerManagement: TYPE_BOOL
    true: Allow device to sleep/shut down when idle on the sign-in screen.
    false: Do not allow device to sleep/shut down when idle on the sign-in screen.

chrome.devices.PowerPeakShift: Peak shift power management.
  powerPeakShiftEnabled: TYPE_BOOL
    true: None
    false: None
  powerPeakShiftBatteryThreshold: TYPE_INT64
    N/A
  key: TYPE_STRING
  startTime: TYPE_INT32
  endTime: TYPE_INT32
  chargeTime: TYPE_INT32

chrome.devices.QuirksDownloadEnabled: Hardware profiles.
  deviceQuirksDownloadEnabled: TYPE_BOOL
    true: Allow hardware profiles to be downloaded from Google servers.
    false: Disable hardware profile downloads from Google servers.

chrome.devices.RebootOnShutdown: Allow shutdown.
  rebootOnShutdown: TYPE_BOOL
    true: Only allow users to turn off the device using the physical power button.
    false: Allow users to turn off the device using either the shut down icon or the physical power button.

chrome.devices.ScheduledRebootDuration: Reboot after uptime limit.
  seconds: TYPE_INT64
  nanos: TYPE_INT32

chrome.devices.ShowLowDiskSpaceNotification: Low disk space notification.
  showLowDiskSpaceNotification: TYPE_BOOL
    true: Show notification when disk space is low.
    false: Do not show notification when disk space is low.

chrome.devices.SignInKeyboard: Login screen keyboard.
  keyboardIds: TYPE_LIST

chrome.devices.SignInLanguage: Sign-in language.
  signInLanguageString: TYPE_STRING
    {'value': '', 'description': 'Use the language of the last user session.'}

chrome.devices.SignInRestriction: Sign-in restriction.
  deviceAllowNewUsers: TYPE_ENUM
    RESTRICTED_LIST: Restrict sign-in to a list of users.
    ANY_USER: Allow any user to sign in.
    NO_USERS: Do not allow any user to sign in.
  userAllowlist: TYPE_LIST
    Allowed users. Enter a list of usernames who can sign in to the device. You can also allow all email addresses in a domain with the wildcard symbol (e.g. *@example.com).

chrome.devices.SignInRestrictionsOffHours: Device off hours.
  timezone: TYPE_STRING
  dayOfWeek: TYPE_ENUM
    MONDAY:
    TUESDAY:
    WEDNESDAY:
    THURSDAY:
    FRIDAY:
    SATURDAY:
    SUNDAY:
  hours: TYPE_INT32
  minutes: TYPE_INT32

chrome.devices.SignInWallpaperImage: Device wallpaper image.
  downloadUri: TYPE_STRING

chrome.devices.SsoCameraPermissions: Single sign-on camera permissions.
  loginVideoCaptureAllowedUrls: TYPE_LIST
    Allowed single sign-on camera permissions. By enabling this policy, you are granting third parties access to your users' cameras on your users' behalf. Please ensure you read the help center articles for more clarifications around single sign-on and camera permissions.

chrome.devices.SsoCookieBehavior: Single sign-on cookie behavior.
  transferSamlCookies: TYPE_BOOL
    true: Enable transfer of SAML SSO Cookies into user session during sign-in.
    false: Disable transfer of SAML SSO Cookies into user session during sign-in.

chrome.devices.SsoIdpRedirection: Single sign-on IdP redirection.
  loginAuthenticationBehavior: TYPE_ENUM
    GAIA: Take users to the default Google sign-in screen.
    SAML_INTERSTITIAL: Allow users to go directly to SAML SSO IdP page.

chrome.devices.SystemProxySettings: Authenticated Proxy Traffic.
  systemProxyEnabled: TYPE_BOOL
    true: Allow system traffic to go through a proxy with authentication.
    false: Block system traffic from going through a proxy with authentication.
  systemServicesUsername: TYPE_STRING
    Username.
  systemServicesPassword: TYPE_STRING
    Password. You can choose to provide service account credentials (username and password). These credentials will only be used for system traffic. Browser traffic will still require the user to authenticate to the proxy with their own credentials.

chrome.devices.SystemUseTwentyFourHourClock: System clock format.
  systemUseTwentyFourHourClock: TYPE_ENUM
    UNSET: Automatic, based on current language.
    FALSE: 12 hour clock format.
    TRUE: 24 hour clock format.

chrome.devices.ThrottleDeviceBandwidth: Throttle device bandwidth.
  networkThrottlingEnabled: TYPE_BOOL
    true: Enable network throttling.
    false: Disable network throttling.
  downloadRateKbits: TYPE_INT64
    Download rate (kbits).
  uploadRateKbits: TYPE_INT64
    Upload rate (kbits).

chrome.devices.Timezone: Timezone.
  timezoneDetectionType: TYPE_ENUM
    USERS_DECIDE:
    DISABLED:
    IP_ONLY:
    SEND_WIFI_ACCESS_POINTS:
    SEND_ALL_LOCATION_INFO:
  value: TYPE_STRING

chrome.devices.TpmFirmwareUpdate: TPM firmware update.
  tpmFirmwareUpdateEnabled: TYPE_BOOL
    true: Allow users to perform TPM firmware update.
    false: Block users from performing TPM firmware update.

chrome.devices.UsbDetachableAllowlist: USB access.
  usbDetachableAllowlist: TYPE_LIST
    Allowed USB devices. A list of USB devices that Chrome apps may access via the chrome.usb API. To identify a specific hardware, enter colon separated hexadecimal pairs of USB Vendor Identifier and Product Identifier. .

chrome.devices.UsbPowerShare: USB Powershare.
  usbPowerShareEnabled: TYPE_BOOL
    true: Enable USB Powershare.
    false: Disable USB Powershare.

chrome.devices.Variations: Variations.
  deviceVariationsEnabled: TYPE_ENUM
    ENABLED: Enable Chrome variations.
    CRITICAL_FIXES_ONLY: Enable variations for critical fixes only.
    DISABLED: Disable variations.

chrome.devices.VirtualMachineAndroidAdbSideloadingAllowed: Android apps from untrusted sources.
  virtualMachinesAndroidAdbSideloadingAllowed: TYPE_ENUM
    DISALLOW: Prevent users of this device from using ADB sideloading.
    DISALLOW_WITH_POWERWASH: Prevent users of this device from using ADB sideloading and force a device powerwash if sideloading was enabled before.
    ALLOW_FOR_AFFILIATED_USERS: Allow affiliated users of this device to use ADB sideloading.

chrome.devices.VirtualMachinesAllowedUnaffiliatedUser: Linux virtual machines for unaffiliated users (BETA).
  virtualMachinesAllowedForUnaffiliatedUser: TYPE_BOOL
    true: Allow usage for virtual machines needed to support Linux apps for unaffiliated users.
    false: Block usage for virtual machines needed to support Linux apps for unaffiliated users.

chrome.devices.WilcoScheduledUpdate: Scheduled updates.
  wilcoScheduledUpdateEnabled: TYPE_BOOL
    true: None
    false: None
  wilcoScheduledUpdateTimeOfDay: TYPE_INT64
    {'value': '0', 'description': '12:00 AM.'}
  wilcoScheduledUpdateFrequency: TYPE_ENUM
    DAILY:
    WEEKLY:
    MONTHLY:
  wilcoScheduledUpdateDayOfWeek: TYPE_ENUM
    MONDAY:
    TUESDAY:
    WEDNESDAY:
    THURSDAY:
    FRIDAY:
    SATURDAY:
    SUNDAY:
  wilcoScheduledUpdateDayOfMonth: TYPE_INT64
    {'value': '1', 'description': 'The 1st day of the month.'}

chrome.devices.WipeUserData: Allows admins to make managed ChromeOS devices wipe user data after sign-out.
  ephemeralUsersEnabled: TYPE_BOOL
    true: Erase all local user data.
    false: Do not erase local user data.

chrome.printers.AllowForDevices: Allows a printer for devices in a given organization.
  allowForDevices: TYPE_BOOL

chrome.printers.AllowForManagedGuest: Allows a printer for Managed Guest in a given organization.
  allowForManagedGuest: TYPE_BOOL

chrome.printers.AllowForUsers: Allows a printer for users in a given organization.
  allowForUsers: TYPE_BOOL

chrome.users.AbusiveExperienceInterventionEnforce: Abusive Experience Intervention.
  abusiveExperienceInterventionEnforce: TYPE_BOOL
    true: Prevent sites with abusive experiences from opening new windows or tabs.
    false: Allow sites with abusive experiences to open new windows or tabs.

chrome.users.AccessibilityImageLabelsEnabled: Image descriptions.
  accessibilityImageLabelsEnabled: TYPE_ENUM
    UNSET: Let users choose to use an anonymous Google service to provide automatic descriptions for unlabeled images.
    FALSE: Do not use Google services to provide automatic image descriptions.
    TRUE: Use an anonymous Google service to provide automatic descriptions for unlabeled images.

chrome.users.AccessibilityShortcutsEnabled: Accessibility shortcuts.
  accessibilityShortcutsEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable accessibility shortcuts.
    TRUE: Enable accessibility shortcuts.

chrome.users.AdditionalDnsQueryTypesEnabled: DNS queries for additional DNS record types.
  additionalDnsQueryTypesEnabled: TYPE_BOOL
    true: Allow additional DNS query types.
    false: Prevent additional DNS query types.

chrome.users.AdsSettingForIntrusiveAdsSites: Sites with intrusive ads.
  adsSettingForIntrusiveAdsSites: TYPE_ENUM
    ALLOW_ADS: Allow ads on all sites.
    BLOCK_ADS: Block ads on sites with intrusive ads.

chrome.users.AdvancedProtectionAllowed: Advanced Protection program.
  advancedProtectionAllowed: TYPE_BOOL
    true: Users enrolled in the Advanced Protection program will receive extra protections.
    false: Users enrolled in the Advanced Protection program will only receive standard consumer protections.

chrome.users.AllowDinosaurEasterEgg: Dinosaur game.
  allowDinosaurEasterEgg: TYPE_ENUM
    UNSET: Allow users to play the dinosaur game when the device is offline on Chrome browser, but not on enrolled Chrome OS devices.
    FALSE: Do not allow users to play the dinosaur game when the device is offline.
    TRUE: Allow users to play the dinosaur game when the device is offline.

chrome.users.AllowedInputMethods: Allowed input methods.
  allowedInputMethods: TYPE_LIST
    N/A

chrome.users.AllowedLanguages: Allowed Chrome OS languages.
  allowedLanguages: TYPE_LIST
    N/A

chrome.users.AllowFileSelectionDialogs: File selection dialogs.
  allowFileSelectionDialogs: TYPE_BOOL
    true: Allow users to open file selection dialogs.
    false: Block file selection dialogs. The user is assumed to have clicked Cancel on the dialog.

chrome.users.AllowPopulateAssetIdentifier: Asset identifier during enrollment.
  allowToUpdateDeviceAttribute: TYPE_BOOL
    true: Users in this organization can provide asset ID and location during enrollment.
    false: Do not allow for users in this organization.

chrome.users.AllowPrinting: Printing.
  printingEnabled: TYPE_BOOL
    true: Enable printing.
    false: Disable printing.

chrome.users.AllowSystemNotifications: System notifications.
  allowSystemNotifications: TYPE_BOOL
    true: Allow system notifications to be used.
    false: Do not allow system notifications to be used.

chrome.users.AllowWakeLocks: Wake locks.
  allowScreenWakeLocks: TYPE_BOOL
    true: Allow screen wake locks for power management.
    false: Demote screen wake lock requests to system wake lock requests.
  allowWakeLocks: TYPE_BOOL
    true: Allow wake locks.
    false: Do not allow wake locks.

chrome.users.AlternateErrorPages: Alternate error pages.
  alternateErrorPagesEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Never use alternate error pages.
    TRUE: Always use alternate error pages.

chrome.users.AlternativeBrowserParameters: Alternative browser parameters.
  alternativeBrowserParameters: TYPE_LIST
    Command-line parameters. Parameters for the alternative browser. If a parameter contains {"${url}"}, it gets replaced with the URL. Otherwise, the URL is appended at the end of the command line.

chrome.users.AlternativeBrowserPath: Alternative browser path.
  alternativeBrowserPath: TYPE_STRING
    Path to the alternative browser. If this policy is unset, a platform-specific default is used. Only some values are supported, such as: {"${ie}"}, {"${edge}"}, and the path to iexplore.exe.

chrome.users.AlwaysOnVpn: Always on VPN.
  alwaysOnVpnApp: TYPE_STRING
    Activate Always-on VPN for all user traffic with an app from a list of force installed Android VPN apps. Please make sure the configured app is force installed.
  vpnConfigAllowed: TYPE_BOOL
    true: Allow user to disconnect from a VPN manually (VPN will reconnect on log in).
    false: Do not allow user to disconnect from a VPN manually.

chrome.users.AlwaysOpenPdfExternally: PDF files.
  alwaysOpenPdfExternally: TYPE_BOOL
    true: Chrome downloads PDF files and lets users open them with the system default application.
    false: Chrome opens PDF files, unless the PDF plugin is turned off.

chrome.users.AmbientAuthenticationInPrivateModesEnabled: Ambient authentication.
  ambientAuthenticationInPrivateModesEnabled: TYPE_ENUM
    UNSET: No policy set.
    REGULAR_ONLY: Enable in regular sessions only.
    INCOGNITO_AND_REGULAR: Enable in regular and incognito sessions.
    GUEST_AND_REGULAR: Enable in regular and guest sessions.
    ALL: Enable in regular, incognito and guest sessions.

chrome.users.AndroidBackupRestoreServiceEnabled: Control Android backup and restore service.
  arcBackupRestoreServiceEnabled: TYPE_ENUM
    DISABLED: Backup and restore disabled.
    UNDER_USER_CONTROL: Let user decides whether to enable backup and restore.

chrome.users.AndroidGoogleLocationServicesEnabled: Google location services.
  arcGoogleLocationServicesEnabled: TYPE_ENUM
    DISABLED: Disable location services for Android apps in Chrome OS.
    UNDER_USER_CONTROL: Allow the user to decide whether an Android app in Chrome OS can use location services.

chrome.users.AppCacheForceEnabled: AppCache.
  appCacheForceEnabled: TYPE_BOOL
    true: Allow websites to use the deprecated AppCache feature.
    false: Do not allow websites to use the deprecated AppCache feature.

chrome.users.AppRecommendationZeroStateEnabled: Previously installed app recommendations.
  appRecommendationZeroStateEnabled: TYPE_BOOL
    true: Show app recommendations in the Chrome OS launcher.
    false: Do not show app recommendations in the Chrome OS launcher.

chrome.users.apps.CertificateManagement: Allows setting of certificate management related permissions.
  allowAccessToKeys: TYPE_BOOL
  allowEnterpriseChallenge: TYPE_BOOL

chrome.users.apps.DefaultLaunchContainer: Allows setting of the default launch container for web apps.
  defaultLaunchContainer: TYPE_ENUM
    TAB: Browser tab.
    WINDOW: Separate window.

chrome.users.apps.IncludeInChromeWebStoreCollection: Specifies whether the Chrome Application should appear in the Chrome Web Store collection.
  includeInCollection: TYPE_BOOL

chrome.users.apps.InstallationUrl: Specifies the url from which to install a self hosted Chrome Extension.
  installationUrl: TYPE_STRING
    The url from which to install a self hosted Chrome Extension.
  overrideInstallationUrl: TYPE_BOOL

chrome.users.apps.InstallType: Specifies the manner in which the app is to be installed. Note: It's required in order to add an App or Extension to the set of managed apps & extensions of an Organizational Unit.
  appInstallType: TYPE_ENUM
    BLOCKED: Block installation of the app. Note: Web apps can't be Blocked, which means setting this option for Web Apps is disallowed.
    ALLOWED: Allow installation of the app.
    FORCED: Force install the app.
    FORCED_AND_PIN_TO_TOOLBAR: Force install and pin the app to the toolbar.

chrome.users.apps.ManagedConfiguration: Allows setting of the managed configuration.
  managedConfiguration: TYPE_STRING
    Sets the managed configuration JSON format.

chrome.users.apps.PermissionsAndUrlAccess: Allows setting of allowed and blocked hosts.
  blockedPermissions: TYPE_LIST
    {'value': '', 'description': 'Allow all permissions. If empty string is set, it must be the only value set for the policy.'}
  allowedPermissions: TYPE_LIST
    {'value': 'alarms', 'description': 'Alarms.'}
  blockedHosts: TYPE_LIST
    Sets extension hosts that should be blocked.
  allowedHosts: TYPE_LIST
    Sets extension hosts that should be allowed. Allowed hosts override blocked hosts.

chrome.users.apps.SkipPrintConfirmation: Allows the app to skip the confirmation dialog when sending print jobs via the Chrome Printing API.
  skipPrintConfirmation: TYPE_BOOL

chrome.users.appsconfig.AllowedAppTypes: Allowed types of apps and extensions.
  extensionAllowedTypes: TYPE_LIST
    {'value': 'extension', 'description': 'Extension.'}

chrome.users.appsconfig.AllowedInstallSources: Allows setting of the allowed install sources for apps. Note these must be set together.
  chromeWebStoreInstallSources: TYPE_ENUM
    ALLOW_ALL_APPS: All apps allowed, admin manages blocklist.
    BLOCK_ALL_APPS: All apps blocked, admin manages allowlist.
    BLOCK_ALL_APPS_USER_EXTENSION_REQUESTS_ALLOWED: All apps blocked, admin manages allowlist, users may request extensions.

chrome.users.appsconfig.AllowInsecureUpdates: Allow insecure extension packaging.
  extensionAllowInsecureUpdates: TYPE_BOOL
    true: Allow insecurely packaged extensions.
    false: Do not allow insecurely packaged extensions.

chrome.users.appsconfig.AndroidAppsEnabled: Android applications on Chrome devices.
  arcEnabled: TYPE_BOOL
    false: Disable letting a user install Android applications on a Chrome OS device.
    true: Enable letting a user install Android applications on a Chrome OS device.
  ackNoticeForArcEnabledSetToTrue: TYPE_BOOL

chrome.users.appsconfig.AppExtensionInstallSources: App and extension install sources.
  extensionInstallSources: TYPE_LIST
    Sources URL patterns. Chrome will offer to install app and extension packages from URLs that match the listed patterns.

chrome.users.appsconfig.BlockExtensionsByPermission: Permissions and URLs.
  extensionBlockedPermissions: TYPE_LIST
    {'value': 'alarms', 'description': 'Alarms.'}
  runtimeBlockedHosts: TYPE_LIST
    Runtime blocked hosts. This is a list of patterns for matching against hostnames. URLs that match one of these patterns cannot be modified by apps and extensions. This includes injecting Javascript, altering and viewing webRequests / webNavigation, viewing and altering cookies, exceptions to the same-origin policy, etc. The format is similar to full URL patterns except no paths may be defined. e.g. "*://*.example.com". Maximum of 100 URLs.
  runtimeAllowedHosts: TYPE_LIST
    Runtime allowed hosts. Hosts that an extension can interact with regardless of whether they are listed in "Runtime blocked hosts". This is the same format as "Runtime blocked hosts". Maximum of 100 URLs.

chrome.users.appsconfig.BlockExternalExtensions: External extensions.
  blockExternalExtensions: TYPE_BOOL
    true: Block external extensions from being installed.
    false: Allow external extensions to be installed.

chrome.users.appsconfig.ChromeWebStoreHomepage: Chrome Web Store homepage.
  cwsHomePage: TYPE_ENUM
    DEFAULT: Use the default homepage.
    COLLECTION: Use the Chrome Web Store collection.
    CUSTOM: Use a custom page.
  cwsHomePageCollectionName: TYPE_STRING
    Collection name.
  cwsHomePageCustomUrl: TYPE_STRING
    Collection URL.
  cwsHomePageCollectionIncludePrivateApps: TYPE_BOOL
    true: Include all private apps from this domain.
    false: Choose which apps are included in this collection.

chrome.users.appsconfig.ChromeWebStorePermissions: Chrome Web Store permissions.
  allowWebstorePublish: TYPE_BOOL
    true: Allow users to publish private apps that are restricted to your domain on Chrome Web Store.
    false: Do not allow users to publish private apps that are restricted to your domain on Chrome Web Store.
  allowWebstorePublishUnverified: TYPE_BOOL
    true: Allow users to publish private hosted apps even if the domain name of the app's {print "launch_web_url"} or {print "app_url"} is not owned by the organization.
    false: Do not allow users to publish private hosted apps if the domain name of the app's {print "launch_web_url"} or {print "app_url"} is not owned by the organization.

chrome.users.appsconfig.FullRestoreEnabled: Full restore.
  fullRestoreEnabled: TYPE_BOOL
    true: Restore apps and app windows after crash or reboot.
    false: Do not restore apps and app windows after crash or reboot.

chrome.users.appsconfig.GhostWindowEnabled: Android ghost windows.
  ghostWindowEnabled: TYPE_BOOL
    true: Create ghost windows while restoring Android apps.
    false: Do not create ghost windows while restoring Android apps.

chrome.users.appsconfig.HideWebStoreIcon: Chrome Web Store app icon.
  hideWebStoreIcon: TYPE_BOOL
    true: Do not show the Chrome Web Store icon in the Chrome OS launcher or on the new tab page.
    false: Show the Chrome Web Store icon in the Chrome OS launcher and on the new tab page.

chrome.users.appsconfig.ReportAndroidStatus: Android reporting for users and devices.
  reportArcStatusEnabled: TYPE_BOOL
    true: Enable Android reporting.
    false: Disable Android reporting.

chrome.users.ArcAppToWebAppSharingEnabled: Sharing from Android apps to Web apps.
  arcAppToWebAppSharingEnabled: TYPE_BOOL
    true: Enable Android to Web Apps sharing.
    false: Disable Android to Web Apps sharing.

chrome.users.AudioCaptureAllowedUrls: Audio input allowed URLs.
  audioCaptureAllowedUrls: TYPE_LIST
    URL patterns to allow. URLs that will be granted access to the audio input device without a prompt. Prefix domain with [*.] to include subdomains.

chrome.users.AudioInput: Audio input (microphone).
  audioCaptureAllowed: TYPE_BOOL
    true: Prompt user to allow each time.
    false: Disable audio input.

chrome.users.AudioOutput: Audio output.
  audioOutputAllowed: TYPE_BOOL
    true: Enable audio output.
    false: Disable audio output.

chrome.users.AudioProcessHighPriorityEnabled: Audio process priority.
  audioProcessHighPriorityEnabled: TYPE_ENUM
    UNSET: Use the system default priority for the Chrome audio process.
    FALSE: Use normal priority for the Chrome audio process.
    TRUE: Use high priority for the Chrome audio process.

chrome.users.AudioSandboxEnabled: Audio sandbox.
  audioSandboxEnabled: TYPE_ENUM
    UNSET: Use the default configuration for the audio sandbox.
    FALSE: Never sandbox the audio process.
    TRUE: Always sandbox the audio process.

chrome.users.AuthAndroidNegotiateAccountType: Account type for HTTP Negotiate authentication.
  authAndroidNegotiateAccountType: TYPE_STRING
    Account type. Specifies the account type of the accounts provided by the Android authentication app that supports HTTP Negotiate authentication. If no setting is provided, HTTP Negotiate authentication is disabled on Android.

chrome.users.AuthenticationServerAllowlist: Integrated authentication servers.
  authServerAllowlist: TYPE_LIST
    Allowed authentication servers. Enter a list of servers for integrated authentication.

chrome.users.AuthenticationServerDelegationAllowlist: Kerberos delegation servers.
  authNegotiateDelegateAllowlist: TYPE_LIST
    Allowed servers for delegation. Enter a list of servers that Chrome may delegate to for Kerberos authentication.

chrome.users.AuthSchemes: Supported authentication schemes.
  authSchemes: TYPE_LIST
    {'value': 'basic', 'description': 'Basic.'}

chrome.users.AutoclickEnabled: Auto-click enabled.
  autoclickEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable auto-click.
    TRUE: Enable auto-click.

chrome.users.AutoOpen: Auto open downloaded files.
  autoOpenAllowedForUrls: TYPE_LIST
    Auto open URLs. If this policy is set, only downloads that match these URLs and have an auto open type will be auto opened. If this policy is left unset, all downloads matching an auto open type will be auto opened. Wildcards ("*") are allowed when appended to a URL, but cannot be entered alone.
  autoOpenFileTypes: TYPE_LIST
    Auto open files types. Do not include the leading separator when listing the type. For example, use "txt", not ".txt".

chrome.users.AutoplayAllowlist: Autoplay video.
  autoplayAllowlist: TYPE_LIST
    Allowed URLs. URL patterns allowed to autoplay. Prefix domain with [*.] to include all subdomains. Use * to allow all domains.

chrome.users.AutoUpdateCheckPeriodNew: Auto-update check period.
  seconds: TYPE_INT64
  nanos: TYPE_INT32

chrome.users.Avatar: Custom avatar.
  downloadUri: TYPE_STRING

chrome.users.BackForwardCacheEnabled: Back-forward cache.
  backForwardCacheEnabled: TYPE_BOOL
    true: Enable the back-forward cache.
    false: Disable the back-forward cache.

chrome.users.BackgroundModeEnabled: Background mode.
  backgroundModeEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable background mode.
    TRUE: Enable background mode.

chrome.users.BasicAuthOverHttpEnabled: Allow Basic authentication for HTTP.
  basicAuthOverHttpEnabled: TYPE_BOOL
    true: Basic authentication scheme is allowed on HTTP connections.
    false: HTTPS is required to use Basic authentication scheme.

chrome.users.BookmarkBarEnabled: Bookmark bar.
  bookmarkBarEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable bookmark bar.
    TRUE: Enable bookmark bar.

chrome.users.BookmarkEditing: Bookmark editing.
  editBookmarksEnabled: TYPE_BOOL
    true: Enable bookmark editing.
    false: Disable bookmark editing.

chrome.users.BrowserAddPersonEnabled: Add profiles.
  browserAddPersonEnabled: TYPE_BOOL
    true: Enable adding new profiles.
    false: Disable adding new profiles.

chrome.users.BrowserGuestModeEnabled: Browser guest mode.
  browserGuestModeEnabled: TYPE_BOOL
    true: Allow guest browser logins.
    false: Prevent guest browser logins.
  browserGuestModeEnforced: TYPE_BOOL
    true: Only allow guest browser logins.
    false: Allow guest browser logins and profile logins.

chrome.users.BrowserHistory: Browser history.
  savingBrowserHistoryDisabled: TYPE_BOOL
    true: Never save browser history.
    false: Always save browser history.

chrome.users.BrowserLabsEnabled: Browser experiments icon in toolbar.
  browserLabsEnabled: TYPE_BOOL
    true: Allow users to access browser experimental features through an icon in the toolbar.
    false: Do not show browser experimental features icon in the toolbar.

chrome.users.BrowserNetworkTimeQueriesEnabled: Google time service.
  browserNetworkTimeQueriesEnabled: TYPE_BOOL
    true: Allow queries to a Google server to retrieve an accurate timestamp.
    false: Do not allow queries to Google servers to retrieve timestamps.

chrome.users.BrowserSignin: Browser sign-in settings.
  browserSignin: TYPE_ENUM
    DISABLE: Disable browser sign-in.
    ENABLE: Enable browser sign-in.
    FORCE: Force users to sign-in to use the browser.

chrome.users.BrowserSwitcher: Legacy Browser Support.
  browserSwitcherEnabled: TYPE_BOOL
    true: Enable Legacy Browser Support.
    false: Disable Legacy Browser Support.

chrome.users.BrowserSwitcherChromeParameters: Chrome parameters.
  browserSwitcherChromeParameters: TYPE_LIST
    Command-line parameters. Windows-only. Parameters for launching Chrome from the alternative browser. If a parameter contains {"${url}"}, it gets replaced with the URL. Otherwise, the URL is appended at the end of the command line.

chrome.users.BrowserSwitcherChromePath: Chrome path.
  browserSwitcherChromePath: TYPE_STRING
    Path to the Chrome executable. Windows-only. Path to the Chrome executable to launch when switching from the alternative browser to Chrome. If unset, the alternative browser will auto-detect the path to Chrome.

chrome.users.BrowserSwitcherDelayDuration: Delay before launching alternative browser.
  seconds: TYPE_INT64
  nanos: TYPE_INT32

chrome.users.BrowserSwitcherExternalGreylistUrl: URL to list of websites to open in either browser.
  browserSwitcherExternalGreylistUrl: TYPE_STRING
    URL to site list XML file.

chrome.users.BrowserSwitcherExternalSitelistUrl: Legacy Browser Support site list.
  browserSwitcherExternalSitelistUrl: TYPE_STRING
    URL to site list XML file.

chrome.users.BrowserSwitcherKeepLastChromeTab: Keep last Chrome tab.
  browserSwitcherKeepLastChromeTab: TYPE_BOOL
    true: Keep at least one Chrome tab open.
    false: Close Chrome completely.

chrome.users.BrowserSwitcherUrlGreylist: Websites to open in either browser.
  browserSwitcherUrlGreylist: TYPE_LIST
    URLs to websites to open in either browser.

chrome.users.BrowserSwitcherUrlList: Websites to open in alternative browser.
  browserSwitcherUrlList: TYPE_LIST
    URLs to websites to open in alternative browser.

chrome.users.BrowserSwitcherUseIeSitelist: Use Internet Explorer site list.
  browserSwitcherUseIeSitelist: TYPE_BOOL
    true: Use Internet Explorer's SiteList policy as a source of rules.
    false: Do not use Internet Explorer's SiteList policy as a source of rules.

chrome.users.BrowserThemeColor: Custom theme color.
  browserThemeColor: TYPE_STRING
    Hex color. Enter a valid hex color, for instance #FFFFFF.

chrome.users.BuiltInDnsClientEnabled: Built-in DNS client.
  builtInDnsClientEnabled: TYPE_ENUM
    UNSET: Use the built-in DNS client on macOS, Android and Chrome OS. Allow the user to change the setting.
    FALSE: Never use the built-in DNS client.
    TRUE: Always use the built-in DNS client if available.

chrome.users.CaCertificateManagementAllowed: User management of installed CA certificates.
  caCertificateManagementAllowed: TYPE_ENUM
    ALL: Allow users to manage all certificates.
    USER_ONLY: Allow users to manage user certificates.
    NONE: Disallow users from managing certificates.

chrome.users.CaptivePortalAuthenticationIgnoresProxy: Ignore proxy on captive portals.
  captivePortalAuthenticationIgnoresProxy: TYPE_BOOL
    true: Ignore policies for captive portal pages.
    false: Keep policies for captive portal pages.

chrome.users.CaretHighlightEnabled: Caret highlight.
  caretHighlightEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable caret highlight.
    TRUE: Enable caret highlight.

chrome.users.Cecpq2Enabled: CECPQ2 post-quantum key-agreement for TLS.
  cecpq2Enabled: TYPE_BOOL
    true: Enable default CECPQ2 rollout process.
    false: Disable CECPQ2.

chrome.users.CertificateSynchronization: Certificate synchronization.
  arcCertificatesSyncMode: TYPE_ENUM
    SYNC_DISABLED: Disable usage of Chrome OS CA Certificates in Android apps.
    COPY_CA_CERTS: Enable usage of Chrome OS CA Certificates in Android apps.

chrome.users.CertificateTransparencyEnforcementDisabledForUrls: Allowed certificate transparency URLs.
  certificateTransparencyEnforcementDisabledForUrls: TYPE_LIST
    Allowed certificate transparency URLs. Any URL listed will be exempt from Certificate Transparency enforcement. Learn more at https://cloud.google.com/docs/chrome-enterprise/policies/?policy=CertificateTransparencyEnforcementDisabledForUrls.

chrome.users.CertTransparencyCas: Certificate transparency CA allowlist.
  certificateTransparencyEnforcementDisabledForCas: TYPE_LIST
    Certificate transparency CA allowlist. Any subjectPublicKeyInfo hashes listed will be exempt from Certificate Transparency enforcement. These hashes must be listed in a particular format. Learn more at https://cloud.google.com/docs/chrome-enterprise/policies/?policy=CertificateTransparencyEnforcementDisabledForCas.

chrome.users.CertTransparencyLegacyCas: Certificate transparency legacy CA allowlist.
  certificateTransparencyEnforcementDisabledForLegacyCas: TYPE_LIST
    Certificate transparency legacy CA allowlist. Any subjectPublicKeyInfo hashes listed will be exempt from Certificate Transparency enforcement. These hashes must be listed in a particular format and must match a recognized Legacy Certificate Authority. Enter Learn more at https://cloud.google.com/docs/chrome-enterprise/policies/?policy=CertificateTransparencyEnforcementDisabledForLegacyCas.

chrome.users.ChromeBrowserUpdates: Chrome browser updates.
  rollbackToTargetVersionEnabled: TYPE_ENUM
    DISABLED: Do not rollback to target version.
    ENABLED: Rollback to target version.
  targetVersionPrefixSetting: TYPE_STRING
    Target version prefix. Specifies which version the Chrome browser should be updated to. When a value is set, Chrome will be updated to the version prefixed with this value. For example, if the value is '55.', Chrome will be updated to any minor version of 55 (e.g. 55.24.34.0 or 55.60.2.10). If the value is '55.2.', Chrome will be updated to any minor version of 55.2 (e.g. 55.2.34.100 or 55.2.2.1). If the value is '55.24.34.1', Chrome will be updated to that specific version only. Chrome may stop updating or not rollback if the specified version is more than three major milestones old.
  updateSetting: TYPE_ENUM
    UPDATES_DISABLED: Updates disabled.
    UPDATES_ENABLED: Always allow updates.
    MANUAL_UPDATES_ONLY: Manual updates only.
    AUTOMATIC_UPDATES_ONLY: Automatic updates only.

chrome.users.ChromeCleanupEnabled: Chrome Cleanup.
  chromeCleanupEnabled: TYPE_BOOL
    true: Allow Chrome Cleanup to periodically scan the system and allow manual scans.
    false: Prevent Chrome Cleanup from periodical scans and disallow manual scans.
  chromeCleanupReportingEnabled: TYPE_ENUM
    UNSET: Users may choose to share results from a Chrome Cleanup cleanup run with Google.
    FALSE: Results from a Chrome Cleanup cleanup are never shared with Google.
    TRUE: Results from a Chrome Cleanup cleanup are always shared with Google.

chrome.users.ClearBrowserHistory: Clear browser history.
  allowDeletingBrowserHistory: TYPE_BOOL
    true: Allow clearing history in settings menu.
    false: Do not allow clearing history in settings menu.

chrome.users.ClickToCall: Click to Call.
  clickToCallEnabledTristate: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Do not allow users to send phone numbers from Chrome to their phone.
    TRUE: Allow users to send phone numbers from Chrome to their phone.

chrome.users.ClientCertificateManagementAllowed: User management of installed client certificates.
  clientCertificateManagementAllowed: TYPE_ENUM
    ALL: Allow users to manage all certificates.
    USER_ONLY: Allow users to manage user certificates.
    NONE: Disallow users from managing certificates.

chrome.users.ClientCertificates: Client certificates.
  autoSelectCertificateForUrls: TYPE_LIST
    Automatically select for these sites. If a site matching a pattern specified here requests a client certificate, Chrome will automatically select one for it. More information and example values can be found in https://support.google.com/chrome/a/answer/2657289#AutoSelectCertificateForUrls.

chrome.users.CommandLineFlagSecurityWarningsEnabled: Command-line flags.
  commandLineFlagSecurityWarningsEnabled: TYPE_BOOL
    true: Show security warnings when potentially dangerous command-line flags are used.
    false: Hide security warnings when potentially dangerous command-line flags are used.

chrome.users.ComponentUpdates: Component updates.
  componentUpdatesEnabled: TYPE_BOOL
    true: Enable updates for all components.
    false: Disable updates for components.

chrome.users.ContextualSearchEnabled: Touch to search.
  contextualSearchEnabled: TYPE_BOOL
    true: Allow users to use touch to search.
    false: Disable touch to search.

chrome.users.Cookies: Cookies.
  cookiesAllowedForUrls: TYPE_LIST
    Allow cookies for URL patterns. Urls to allow cookies.
  defaultCookiesSetting: TYPE_ENUM
    UNSET: Allow the user to decide.
    ALLOW_COOKIES: Allow cookies.
    BLOCK_COOKIES: Block cookies.
    SESSION_ONLY: Session only.
  cookiesBlockedForUrls: TYPE_LIST
    Block Cookies for URL Patterns. Urls to block cookies.
  cookiesSessionOnlyForUrls: TYPE_LIST
    Allow session-only cookies for URL patterns. Urls to allow session-only cookies.

chrome.users.CpuTaskScheduler: CPU task scheduler.
  schedulerConfiguration: TYPE_ENUM
    USER_CHOICE: Allow the user to decide.
    CONSERVATIVE: Optimize for stability.
    PERFORMANCE: Optimize for performance.

chrome.users.CrossOriginAuthentication: Cross-origin authentication.
  allowCrossOriginAuthPrompt: TYPE_BOOL
    true: Allow cross-origin authentication.
    false: Block cross-origin authentication.

chrome.users.CrossOriginWebAssemblyModuleSharingEnabled: Allow WebAssembly cross-origin.
  crossOriginWebAssemblyModuleSharingEnabled: TYPE_BOOL
    true: Allow WebAssembly modules to be sent cross-origin.
    false: Prevent WebAssembly modules to be sent cross-origin.

chrome.users.CursorHighlightEnabled: Cursor highlight.
  cursorHighlightEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable cursor highlight.
    TRUE: Enable cursor highlight.

chrome.users.DataCompressionProxy: Data compression proxy.
  dataCompressionProxyEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Always disable data compression proxy.
    TRUE: Always enable data compression proxy.

chrome.users.DefaultBrowserSettingEnabled: Default browser check.
  defaultBrowserSettingEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Prevent Chrome from checking if it is the default browser and turn off user controls to make it the default browser.
    TRUE: Attempt to register Chrome as the default browser during startup if it is not already.

chrome.users.DefaultInsecureContentSetting: Control use of insecure content exceptions.
  defaultInsecureContentSetting: TYPE_ENUM
    BLOCK_INSECURE_CONTENT: Do not allow any site to load blockable mixed content.
    ALLOW_EXCEPTIONS_INSECURE_CONTENT: Allow users to add exceptions to allow blockable mixed content.

chrome.users.DefaultPrintColor: Default color printing mode.
  printingColorDefault: TYPE_ENUM
    COLOR: Color.
    MONOCHROME: Black and white.

chrome.users.DefaultPrintDuplexMode: Default page sides.
  printingDuplexDefault: TYPE_ENUM
    SIMPLEX: One-sided.
    SHORT_EDGE_DUPLEX: Short-edge two-sided printing.
    LONG_EDGE_DUPLEX: Long-edge two-sided printing.

chrome.users.DefaultPrinters: Print preview default.
  specifyDefaultPrinter: TYPE_BOOL
    true: Define the default printer.
    false: Use default print behavior.
  printerTypes: TYPE_ENUM
    CLOUD_AND_LOCAL: Cloud and local.
    CLOUD: Cloud only.
    LOCAL: Local only.
  printerMatching: TYPE_ENUM
    NAME: Match by name.
    ID: Match by ID.
  defaultPrinterPattern: TYPE_STRING
    Default printer. Enter a regular expression that matches the desired default printer selection. The print preview will default to the first printer to match the regular expression. For example, to match a printer named "Initech Lobby", use "Initech Lobby". To match any of {print "initech-lobby-1"}, {print "initech-lobby-2"}, etc. you could use {print "initech-lobby-.$"}. To match {print "initech-lobby-guest"} or {print "initech-partner-guest"}, you could use {print "initech-.*-guest"}.

chrome.users.DefaultSensorsSetting: Sensors.
  defaultSensorsSetting: TYPE_ENUM
    ALLOW_SENSORS: Allow sites to access sensors.
    BLOCK_SENSORS: Do not allow any site to access sensors.
    UNSET: Allow the user to decide if a site may access sensors.
  sensorsAllowedForUrls: TYPE_LIST
    Allow access to sensors on these sites. <br>For detailed information on valid url patterns, please see https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns. Note: using only the "*" wildcard is not valid.
  sensorsBlockedForUrls: TYPE_LIST
    Block access to sensors on these sites. For detailed information on valid url patterns, please see https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns Note: using only the "*" wildcard is not valid.

chrome.users.DeletePrintJobHistoryAllowed: Print job history deletion.
  deletePrintJobHistoryAllowed: TYPE_BOOL
    true: Allow print job history to be deleted.
    false: Do not allow print job history to be deleted.

chrome.users.DesktopSharingHubEnabled: Desktop sharing in the omnibox and 3-dot menu.
  desktopSharingHubEnabled: TYPE_BOOL
    true: Enable desktop sharing hub.
    false: Disable desktop sharing hub.

chrome.users.DeveloperTools: Developer tools.
  developerToolsAvailability: TYPE_ENUM
    ALWAYS_ALLOW_DEVELOPER_TOOLS: Always allow use of built-in developer tools.
    ALLOW_DEVELOPER_TOOLS_EXCEPT_FORCE_INSTALLED: Allow use of built-in developer tools except for force-installed extensions.
    NEVER_ALLOW_DEVELOPER_TOOLS: Never allow use of built-in developer tools.

chrome.users.DeviceEnrollment: Device enrollment.
  autoDevicePlacementEnabled: TYPE_BOOL
    true: Place Chrome device in user organization.
    false: Keep Chrome device in current location.

chrome.users.DictationEnabled: Dictation.
  dictationEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable dictation.
    TRUE: Enable dictation.

chrome.users.DisableSafeBrowsingProceedAnyway: Disable bypassing Safe Browsing warnings.
  disableSafeBrowsingProceedAnyway: TYPE_BOOL
    true: Do not allow user to bypass Safe Browsing warning.
    false: Allow user to bypass Safe Browsing warning.

chrome.users.DiskCacheDir: Disk cache directory.
  diskCacheDir: TYPE_STRING
    Disk cache directory.

chrome.users.DiskCacheSize: Disk cache size.
  diskCacheSize: TYPE_INT64
    Disk cache size in bytes.

chrome.users.DisplayCapturePermissionsPolicyEnabled: Insecure Media Capture.
  displayCapturePermissionsPolicyEnabled: TYPE_BOOL
    true: Deny insecure requests to access display.
    false: Allow requests to access display from non-allowlisted contexts.

chrome.users.DnsInterceptionChecksEnabled: DNS interception checks enabled.
  dnsInterceptionChecksEnabled: TYPE_BOOL
    true: Perform DNS interception checks.
    false: Do not perform DNS interception checks.

chrome.users.DnsOverHttps: DNS-over-HTTPS.
  dnsOverHttpsMode: TYPE_ENUM
    OFF: Disable DNS-over-HTTPS.
    AUTOMATIC: Enable DNS-over-HTTPS with insecure fallback.
    SECURE: Enable DNS-over-HTTPS without insecure fallback.
    UNSET: May send DNS-over-HTTPS requests to user's configured custom name server.
  dnsOverHttpsTemplates: TYPE_LIST
    DNS-over-HTTPS templates. URI templates of desired DNS-over-HTTPS resolvers. If the URI template contains a '{?dns}' variable, requests to the resolver will use GET; otherwise requests will use POST.

chrome.users.DownloadPreference: Cacheable URLs.
  downloadPreference: TYPE_ENUM
    NO_PREFERENCE: No preference.
    CACHEABLE: Attempt to provide cache-friendly download URLs.

chrome.users.DownloadRestrictions: Download restrictions.
  safeBrowsingDownloadRestrictions: TYPE_ENUM
    NO_SPECIAL_RESTRICTIONS: No special restrictions.
    BLOCK_ALL_MALICIOUS_DOWNLOAD: Block all malicious downloads.
    BLOCK_DANGEROUS_DOWNLOAD: Block dangerous downloads.
    BLOCK_POTENTIALLY_DANGEROUS_DOWNLOAD: Block potentially dangerous downloads.
    BLOCK_ALL_DOWNLOAD: Block all downloads.

chrome.users.EmojiSuggestionEnabled: Emoji suggestions.
  emojiSuggestionEnabled: TYPE_BOOL
    true: Enable emoji suggestions when users type.
    false: Disable emoji suggestions when users type.

chrome.users.EnableCaptureAllowedSettings: Screen video capture allowed by sites.
  screenCaptureAllowedByOrigins: TYPE_LIST
    Allow tab, window, and desktop video capture by these sites. Sites set in this list will be ignored in the 'screenCaptureAllowed' field.
  windowCaptureAllowedByOrigins: TYPE_LIST
    Allow tab and window video capture by these sites. Sites set in this list will be ignored in the 'screenCaptureAllowedByOrigins' and 'screenCaptureAllowed' fields.
  tabCaptureAllowedByOrigins: TYPE_LIST
    Allow tab video capture by these sites. Sites set in this list will be ignored in the 'windowCaptureAllowedByOrigins', 'screenCaptureAllowedByOrigins', and 'screenCaptureAllowed' fields.
  sameOriginTabCaptureAllowedByOrigins: TYPE_LIST
    Allow tab video capture (same site only) by these sites. Sites set in this list will be ignored in the 'tabCaptureAllowedByOrigins', 'windowCaptureAllowedByOrigins', 'screenCaptureAllowedByOrigins', and 'screenCaptureAllowed' fields.

chrome.users.EnableDeprecatedPrivetPrinting: Deprecated privet printing.
  enableDeprecatedPrivetPrinting: TYPE_BOOL
    true: Enable deprecated privet printing.
    false: Disable deprecated privet printing.

chrome.users.EnrollPermission: Enrollment permissions.
  deviceEnrollPermission: TYPE_ENUM
    ALLOW_ENROLL_RE_ENROLL: Allow users in this organization to enroll new or re-enroll existing devices.
    ALLOW_RE_ENROLL: Only allow users in this organization to re-enroll existing devices (cannot enroll new or deprovisioned devices).
    DISALLOW_ENROLL_RE_ENROLL: Do not allow users in this organization to enroll new or re-enroll existing devices.

chrome.users.EnterpriseHardwarePlatformApiEnabled: Enterprise Hardware Platform API.
  enterpriseHardwarePlatformApiEnabled: TYPE_BOOL
    true: Allow managed extensions to use the Enterprise Hardware Platform API.
    false: Do not allow managed extensions to use the Enterprise Hardware Platform API.

chrome.users.ExplicitlyAllowedNetworkPorts: Allowed network ports.
  explicitlyAllowedNetworkPorts: TYPE_LIST
    {'value': '554', 'description': 'port 554 (expires 2021/10/15).'}

chrome.users.ExternalProtocolDialogShowAlwaysOpenCheckbox: Show "Always open" checkbox in external protocol dialog.
  externalProtocolDialogShowAlwaysOpenCheckbox: TYPE_BOOL
    true: User may select "Always allow" to skip all future confirmation prompts.
    false: User may not select "Always allow" and will be prompted each time.

chrome.users.ExternalStorage: External storage devices.
  externalStorageDevices: TYPE_ENUM
    READ_WRITE: Allow external storage devices.
    READ_ONLY: Allow external storage devices (read only).
    DISALLOW: Disallow external storage devices.

chrome.users.FetchKeepaliveDurationSecondsOnShutdown: Keepalive duration.
  seconds: TYPE_INT64
  nanos: TYPE_INT32

chrome.users.FileSystemRead: File system read access.
  defaultFileSystemReadGuardSetting: TYPE_ENUM
    UNSET: Allow the user to decide.
    ASK_FILE_SYSTEM_READ: Allow sites to ask the user to grant read access to files and directories.
    BLOCK_FILE_SYSTEM_READ: Do not allow sites to request read access to files and directories.
  fileSystemReadAskForUrls: TYPE_LIST
    Allow file system read access on these sites. For detailed information on valid url patterns, please see URL patterns at https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns. Note: using only the "*" wildcard is not valid.
  fileSystemReadBlockedForUrls: TYPE_LIST
    Block read access on these sites. For detailed information on valid url patterns, please see URL patterns at https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns. Note: using only the "*" wildcard is not valid.

chrome.users.FileSystemWrite: File system write access.
  defaultFileSystemWriteGuardSetting: TYPE_ENUM
    UNSET: Allow the user to decide.
    ASK_FILE_SYSTEM_WRITE: Allow sites to ask the user to grant write access to files and directories.
    BLOCK_FILE_SYSTEM_WRITE: Do not allow sites to request write access to files and directories.
  fileSystemWriteAskForUrls: TYPE_LIST
    Allow write access to files and directories on these sites. For detailed information on valid url patterns, please see URL patterns at https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns. Note: using only the "*" wildcard is not valid.
  fileSystemWriteBlockedForUrls: TYPE_LIST
    Block write access to files and directories on these sites. For detailed information on valid url patterns, please see URL patterns at https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns. Note: using only the "*" wildcard is not valid.

chrome.users.ForcedLanguages: Preferred languages.
  forcedLanguages: TYPE_LIST
    N/A

chrome.users.ForceEphemeralMode: Force ephemeral mode.
  forceEphemeralProfiles: TYPE_BOOL
    true: Erase all local user data.
    false: Do not erase local user data.

chrome.users.ForceMaximizeOnFirstRun: Maximize window on first run.
  forceMaximizeOnFirstRun: TYPE_BOOL
    true: Maximize the first browser window on first run.
    false: Default system behavior (depends on screen size).

chrome.users.FullscreenAlertEnabled: Fullscreen alert.
  fullscreenAlertEnabled: TYPE_BOOL
    true: Enable fullscreen alert when waking the device.
    false: Disable fullscreen alert when waking the device.

chrome.users.FullscreenAllowed: Fullscreen mode.
  fullscreenAllowed: TYPE_BOOL
    true: Allow fullscreen mode.
    false: Do not allow fullscreen mode.

chrome.users.GaiaLockScreenOfflineSigninTimeLimitDays: Google online unlock frequency.
  value: TYPE_INT64

chrome.users.GaiaOfflineSigninTimeLimitDays: Google online login frequency.
  value: TYPE_INT64

chrome.users.Geolocation: Geolocation.
  defaultGeolocationSetting: TYPE_ENUM
    ALLOW_GEOLOCATION: Allow sites to detect users' geolocation.
    BLOCK_GEOLOCATION: Do not allow sites to detect users' geolocation.
    ASK_GEOLOCATION: Always ask the user if a site wants to detect their geolocation.
    USER_CHOICE: Allow the user to decide.

chrome.users.GloballyScopeHttpAuthCacheEnabled: Globally scoped HTTP authentication cache.
  globallyScopeHttpAuthCacheEnabled: TYPE_BOOL
    true: HTTP authentication credentials entered in the context of one site will automatically be used in the context of another.
    false: HTTP authentication credentials are scoped to top-level sites.

chrome.users.GoogleCast: Cast.
  showCastIconInToolbar: TYPE_BOOL
    true: Always show the Cast icon in the toolbar.
    false: Do not show the Cast icon in the toolbar by default, but let users choose.
  enableMediaRouter: TYPE_BOOL
    true: Allow users to Cast.
    false: Do not allow users to Cast.

chrome.users.GoogleDriveSyncing: Google Drive syncing.
  driveDisabledBool: TYPE_BOOL
    true: Disable Google Drive syncing.
    false: Enable Google Drive syncing.

chrome.users.GoogleDriveSyncingOverCellular: Google Drive syncing over cellular.
  driveDisabledOverCellular: TYPE_BOOL
    true: Disable Google Drive syncing over cellular connections.
    false: Enable Google Drive syncing over cellular connections.

chrome.users.GssapiLibraryName: GSSAPI library name.
  gssapiLibraryName: TYPE_STRING
    Library name or full path. Specify which GSSAPI library to use for HTTP authentication. You can set either just a library name, or a full path. Leave empty for default.

chrome.users.HardwareAccelerationModeEnabled: GPU.
  hardwareAccelerationModeEnabled: TYPE_BOOL
    true: Enable hardware acceleration.
    false: Disable hardware acceleration.

chrome.users.HighContrastEnabled: High contrast.
  highContrastEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable high contrast.
    TRUE: Enable high contrast.

chrome.users.HomeButton: Home button.
  showHomeButton: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Never show "Home" button.
    TRUE: Always show "Home" button.

chrome.users.Homepage: Homepage.
  homepageIsNewTabPage: TYPE_ENUM
    UNSET: Allow user to configure.
    FALSE: Homepage is always the URL set in 'homepageLocation'.
    TRUE: Homepage is always the new tab page.
  homepageLocation: TYPE_STRING
    Homepage URL.

chrome.users.HstsPolicyBypassList: HSTS policy bypass list.
  hstsPolicyBypassList: TYPE_LIST
    List of hostnames that will bypass the HSTS policy check . Enter a list of hostnames that will be exempt from the HSTS policy check.

chrome.users.IdleSettings: Idle settings.
  idleTimeoutMinutes: TYPE_STRING
    Idle time in minutes. Leave empty for system default.
  actionOnDeviceIdle: TYPE_ENUM
    SLEEP: Sleep.
    LOGOUT: Logout.
    LOCK: Lock Screen.
  actionOnLidClose: TYPE_ENUM
    SLEEP: Sleep.
    LOGOUT: Logout.
  lockOnSleep: TYPE_ENUM
    UNSET: Allow user to configure.
    FALSE: Don't lock screen.
    TRUE: Lock screen.

chrome.users.Images: Images.
  defaultImagesSettings: TYPE_ENUM
    UNSET: Allow the user to decide.
    ALLOW_IMAGES: Allow all sites to show all images.
    BLOCK_IMAGES: Do not allow any site to show images.
  imagesAllowedForUrls: TYPE_LIST
    Show images on these sites. Urls to allow images.
  imagesBlockedForUrls: TYPE_LIST
    Block images on these sites. Urls to block images.

chrome.users.ImportAutofillFormData: Import autofill data.
  importAutofillFormData: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable imports of autofill data.
    TRUE: Enable imports of autofill data.

chrome.users.ImportBookmarks: Import bookmarks.
  importBookmarks: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable imports of bookmarks.
    TRUE: Enable imports of bookmarks.

chrome.users.ImportHistory: Import browsing history.
  importHistory: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable imports of browsing history.
    TRUE: Enable imports of browsing history.

chrome.users.ImportHomepage: Import homepage.
  importHomepage: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable imports of homepage.
    TRUE: Enable imports of homepage.

chrome.users.ImportSavedPasswords: Import saved passwords.
  importSavedPasswords: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable imports of saved passwords.
    TRUE: Enable imports of saved passwords.

chrome.users.ImportSearchEngine: Import search engines.
  importSearchEngine: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable imports of search engines.
    TRUE: Enable imports of search engines.

chrome.users.IncognitoMode: Incognito mode.
  incognitoModeAvailability: TYPE_ENUM
    AVAILABLE: Allow incognito mode.
    UNAVAILABLE: Disallow incognito mode.
    FORCED: Force incognito mode.

chrome.users.InsecureContentAllowedForUrls: Allow insecure content on these sites.
  insecureContentAllowedForUrls: TYPE_LIST
    URL patterns to allow.

chrome.users.InsecureContentBlockedForUrls: Block insecure content on these sites.
  insecureContentBlockedForUrls: TYPE_LIST
    URL patterns to block.

chrome.users.InsecureFormsWarningsEnabled: Insecure forms.
  insecureFormsWarningsEnabled: TYPE_BOOL
    true: Show warnings and disable autofill on insecure forms.
    false: Do not show warnings and disable autofill on insecure forms.

chrome.users.InsecurePrivateNetworkRequestsAllowed: Requests from insecure websites to more-private network endpoints.
  insecurePrivateNetworkRequestsAllowed: TYPE_BOOL
    true: Insecure websites are allowed to make requests to any network endpoint.
    false: Allow the user to decide.
  insecurePrivateNetworkRequestsAllowedForUrls: TYPE_LIST
    URL patterns to allow. Network requests to more-private endpoints, from insecure origins not covered by the patterns specified here, will use the global default value.

chrome.users.IntegratedWebAuthenticationAllowed: Login credentials for network authentication.
  integratedWebAuthenticationAllowed: TYPE_BOOL
    true: Use login credentials for network authentication to a managed proxy.
    false: Don't use login credentials for network authentication.

chrome.users.IntensiveWakeUpThrottlingEnabled: Javascript IntensiveWakeUpThrottling.
  intensiveWakeUpThrottlingEnabled: TYPE_ENUM
    UNSET: Allow throttling of background javascript timers to be controlled by Chrome's logic and configurable by users.
    FALSE: Force no throttling of background javajscript timers.
    TRUE: Force throttling of background javascript timers.

chrome.users.IntranetRedirectBehavior: Intranet Redirection Behavior.
  intranetRedirectBehavior: TYPE_ENUM
    DEFAULT: Use default browser behavior.
    DISABLE_INTERCEPTION_CHECKS_DISABLE_INFOBAR: Disable DNS interception checks and did-you-mean "http://intranetsite/" infobars.
    DISABLE_INTERCEPTION_CHECKS_ENABLE_INFOBAR: Disable DNS interception checks; allow did-you-mean "http://intranetsite/" infobars.
    ENABLE_INTERCEPTION_CHECKS_ENABLE_INFOBAR: Allow DNS interception checks and did-you-mean "http://intranetsite/" infobars.

chrome.users.Javascript: JavaScript.
  defaultJavascriptSetting: TYPE_ENUM
    UNSET: Allow the user to decide.
    ALLOW_JAVASCRIPT: Allow sites to run JavaScript.
    BLOCK_JAVASCRIPT: Do not allow any site to run JavaScript.
  javascriptAllowedForUrls: TYPE_LIST
    Allow these sites to run JavaScript. Urls to allow JavaScript.
  javascriptBlockedForUrls: TYPE_LIST
    Block JavaScript on these sites. Urls to block JavaScript.

chrome.users.JavaScriptJitSettings: JavaScript JIT.
  defaultJavaScriptJitSetting: TYPE_ENUM
    ALLOW_JAVA_SCRIPT_JIT: Allow sites to run JavaScript JIT.
    BLOCK_JAVA_SCRIPT_JIT: Do not allow sites to run JavaScript JIT.
  javaScriptJitAllowedForSites: TYPE_LIST
    Allow JavaScript to use JIT on these sites.
  javaScriptJitBlockedForSites: TYPE_LIST
    Block JavaScript from using JIT on these sites.

chrome.users.KerberosAddAccountsAllowed: Kerberos accounts.
  kerberosAddAccountsAllowed: TYPE_BOOL
    true: Allow users to add Kerberos accounts.
    false: Do not allow users to add Kerberos accounts.

chrome.users.KerberosRememberPasswordEnabled: Remember Kerberos passwords.
  kerberosRememberPasswordEnabled: TYPE_BOOL
    true: Allow users to remember Kerberos passwords.
    false: Do not allow users to remember Kerberos passwords.

chrome.users.KerberosServicePrincipalName: Kerberos service principal name.
  disableAuthNegotiateCnameLookup: TYPE_BOOL
    true: Use original name entered.
    false: Use canonical DNS name.

chrome.users.KerberosSpnPort: Kerberos SPN port.
  enableAuthNegotiatePort: TYPE_BOOL
    true: Include non-standard port.
    false: Do not include non-standard port.

chrome.users.KerberosTicketDelegation: Kerberos ticket delegation.
  authNegotiateDelegateByKdcPolicy: TYPE_BOOL
    true: Respect KDC policy.
    false: Ignore KDC policy.

chrome.users.KerberosTickets: Kerberos tickets.
  kerberosEnabled: TYPE_BOOL
    false: Disable Kerberos.
    true: Enable Kerberos.
  kerberosPrincipal: TYPE_STRING
    Principal name. Define a Kerberos account to be added on behalf of user. The following placeholders are supported: - ${LOGIN_ID}: Username part of principal, e.g. "user" if the user logs in as "user@REALM"- ${LOGIN_EMAIL}: Full principal, e.g. "user@REALM" if the user logs in as "user@REALM".
  kerberosConfiguration: TYPE_LIST
    Kerberos configuration.
  kerberosAutoAccountEnabled: TYPE_BOOL
    false: Do not automatically add a Kerberos account.
    true: Automatically add a Kerberos account.
  kerberosCustomConfigurationEnabled: TYPE_BOOL
    false: Use default Kerberos configuration.
    true: Customize Kerberos configuration.

chrome.users.KeyboardFocusHighlightEnabled: Keyboard focus highlighting.
  keyboardFocusHighlightEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable keyboard focus highlighting.
    TRUE: Enable keyboard focus highlighting.

chrome.users.KeyboardFunctionKeys: Keyboard.
  keyboardDefaultToFunctionKeys: TYPE_BOOL
    true: Treat top-row keys as function keys, but allow user to change.
    false: Treat top-row keys as media keys, but allow user to change.

chrome.users.LargeCursorEnabled: Large cursor.
  largeCursorEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable large cursor.
    TRUE: Enable large cursor.

chrome.users.LegacySameSiteCookieBehaviorEnabled: Default legacy SameSite cookie behavior.
  legacySameSiteCookieBehaviorEnabled: TYPE_ENUM
    LEGACY_SAME_SITE_COOKIE_BEHAVIOR: Revert to legacy SameSite behavior for cookies on all sites.
    SAME_SITE_BY_DEFAULT_COOKIE_BEHAVIOR: Use SameSite-by-default behavior for cookies on all sites.
    USER_PERSONAL_CONFIGURATION: Use the user's personal configuration for SameSite features.

chrome.users.LegacySameSiteCookieBehaviorEnabledForDomainList: Per-site legacy SameSite cookie behavior.
  legacySameSiteCookieBehaviorEnabledForDomainList: TYPE_LIST
    Revert to legacy SameSite cookie behavior on these sites. Prefix domain with [*.] to include all subdomains.

chrome.users.LensCameraAssistedSearchEnabled: Google Lens camera assisted search.
  lensCameraAssistedSearchEnabled: TYPE_BOOL
    true: Allow enterprise user to use Google Lens camera assisted search.
    false: Do not allow enterprise user to use Google Lens camera assisted search.

chrome.users.LensRegionSearchEnabled: Google Lens region search.
  lensRegionSearchEnabled: TYPE_BOOL
    true: Enable Google Lens region search.
    false: Disable Google Lens region search.

chrome.users.LockIconInAddressBarEnabled: Lock icon in the omnibox for secure connections.
  lockIconInAddressBarEnabled: TYPE_BOOL
    true: Use the lock icon for secure connections.
    false: Use default icons for secure connections.

chrome.users.LockScreen: Lock screen.
  allowScreenLock: TYPE_BOOL
    true: Allow locking screen.
    false: Do not allow locking screen.

chrome.users.LockScreenMediaPlaybackEnabled: Lock screen media playback.
  lockScreenMediaPlaybackEnabled: TYPE_BOOL
    true: Allow users to play media when the device is locked.
    false: Do not allow users to play media when the device is locked .

chrome.users.LoginDisplayPasswordButtonEnabled: Display password button.
  loginDisplayPasswordButtonEnabled: TYPE_BOOL
    true: Show the display password button on the login and lock screen.
    false: Do not show the display password button on the login and lock screen.

chrome.users.LookalikeWarningAllowlistDomains: Suppress lookalike domain warnings on domains.
  lookalikeWarningAllowlistDomains: TYPE_LIST
    Allowlisted Domains. Enter list of domains where Chrome should prevent the display of lookalike URL warnings.

chrome.users.ManagedBookmarksSetting: Managed bookmarks.
  toplevelName: TYPE_STRING
  name: TYPE_STRING
  url: TYPE_STRING

chrome.users.MaxConnectionsPerProxy: Max connections per proxy.
  maxConnectionsPerProxy: TYPE_INT64
    Maximium number of concurrent connections to the proxy server. Specifies the maximal number of simultaneous connections to the proxy server. The value of this policy should be lower than 100 and higher than 6 and the default value is 32.

chrome.users.MaxInvalidationFetchDelay: Policy fetch delay.
  seconds: TYPE_INT64
  nanos: TYPE_INT32

chrome.users.MediaRecommendationsEnabled: Media Recommendations.
  mediaRecommendationsEnabled: TYPE_BOOL
    true: Show personalized media recommendations.
    false: Do not show personalized media recommendations.

chrome.users.MetricsReportingEnabled: Metrics reporting.
  metricsReportingEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Do not send anonymous reports of usage and crash-related data to Google.
    TRUE: Send anonymous reports of usage and crash-related data to Google.

chrome.users.MobileManagement: Chrome Mobile (BETA).
  enableMobileChromePolicies: TYPE_BOOL
    true: Apply supported user settings to Chrome on Android.
    false: Do not apply supported user settings to Chrome on Android.

chrome.users.MonoAudioEnabled: Mono audio.
  monoAudioEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable mono audio.
    TRUE: Enable mono audio.

chrome.users.MultipleSignInAccess: Multiple sign-in access.
  newChromeOsMultiProfileUserBehavior: TYPE_ENUM
    PRIMARY_ONLY: Managed user must be the primary user (secondary users are allowed).
    UNRESTRICTED: Unrestricted user access (allow any user to be added to any other user's session).
    NOT_ALLOWED: Block multiple sign-in access for users in this organization.

chrome.users.NativeMessagingAllowed: Native Messaging allowed hosts.
  nativeMessagingAllowlist: TYPE_LIST
    Native Messaging hosts not subject to the blocklist. Domains to allow native messaging.

chrome.users.NativeMessagingBlocked: Native Messaging blocked hosts.
  nativeMessagingBlocklist: TYPE_LIST
    Prohibited Native Messaging hosts. Domains to block native messaging. A pattern of "*" will block all hosts not specified in the allowlist.

chrome.users.NativeMessagingUserHosts: Native Messaging user-level hosts.
  nativeMessagingUserLevelHosts: TYPE_BOOL
    true: Allow usage of Native Messaging hosts installed at the user level.
    false: Only allow usage of Native Messaging hosts installed at the system level.

chrome.users.NetworkFileShares: Network file shares.
  networkFileSharesAllowed: TYPE_BOOL
    true: Allow network file shares.
    false: Block network file shares.
  netBiosShareDiscoveryEnabled: TYPE_BOOL
    true: Use NetBIOS discovery.
    false: Do not allow NetBIOS discovery.
  ntlmShareAuthenticationEnabled: TYPE_BOOL
    true: Use NTLM authentication.
    false: Do not use NTLM authentication.
  mode: TYPE_ENUM
    DROP_DOWN:
    PRE_MOUNT:
  shareUrl: TYPE_STRING

chrome.users.NetworkServiceSandboxEnabled: Network service sandbox.
  networkServiceSandboxEnabled: TYPE_ENUM
    UNSET: Default network service sandbox configuration.
    FALSE: Disable the network service sandbox.
    TRUE: Enable the network service sandbox.

chrome.users.NewTabPageLocation: New tab page.
  newTabPageLocation: TYPE_STRING
    New tab URL (leave empty for default).

chrome.users.Notifications: Notifications.
  defaultNotificationsSetting: TYPE_ENUM
    UNSET: Allow the user to decide.
    ALLOW_NOTIFICATIONS: Allow sites to show desktop notifications.
    BLOCK_NOTIFICATIONS: Do not allow sites to show desktop notifications.
    ASK_NOTIFICATIONS: Always ask the user if a site can show desktop notifications.
  notificationsAllowedForUrls: TYPE_LIST
    Allow these sites to show notifications. Urls to allow notifications. Prefix domain with [*.] to include all subdomains.
  notificationsBlockedForUrls: TYPE_LIST
    Block notifications on these sites. Urls to block notifications. Prefix domain with [*.] to include all subdomains.

chrome.users.NtlmV2Enabled: NTLMv2 authentication.
  ntlmV2Enabled: TYPE_BOOL
    true: Enable NTLMv2 authentication.
    false: Disable NTLMv2 authentication.

chrome.users.NtpCardsVisible: Show cards on the New Tab Page.
  ntpCardsVisible: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Do not show cards on the New Tab Page.
    TRUE: Show cards on the New Tab Page if content is available.

chrome.users.NtpContentSuggestionsEnabled: New Tab page content suggestions.
  ntpContentSuggestionsEnabled: TYPE_BOOL
    true: Show content suggestions on the New Tab page .
    false: Do not show content suggestions on the New Tab page .

chrome.users.NtpCustomBackgroundEnabled: New Tab page background.
  ntpCustomBackgroundEnabled: TYPE_BOOL
    true: Allow users to customize the background on the New Tab page.
    false: Do not allow users to customize the background on the New Tab page.

chrome.users.OnlineRevocationChecks: Online revocation checks.
  enableOnlineRevocationChecks: TYPE_BOOL
    true: Perform online OCSP/CRL checks.
    false: Do not perform online OCSP/CRL checks.

chrome.users.OverrideSecurityRestrictionsOnInsecureOrigin: Override insecure origin restrictions.
  overrideSecurityRestrictionsOnInsecureOrigin: TYPE_LIST
    Origin or hostname patterns to ignore insecure origins security restrictions.

chrome.users.PasswordAlert: Password alert.
  passwordProtectionWarningTrigger: TYPE_ENUM
    NO_WARNING: No password protection warning.
    WARN_ON_PASSWORD_REUSE: Trigger on password reuse.
    WARN_ON_PHISHING_REUSE: Trigger on password reuse on phishing page.
  passwordProtectionChangePasswordUrl: TYPE_STRING
    URL for password change. Enter the URL of the webpage where users can change their password.
  passwordProtectionLoginUrls: TYPE_LIST
    Login URLs. Enter list of enterprise login URLs where password protection service should capture fingerprint of password.

chrome.users.PasswordLeakDetection: Enable leak detection for entered credentials.
  passwordLeakDetection: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable Leak detection for entered credentials.
    TRUE: Enable Leak detection for entered credentials.

chrome.users.PasswordManager: Password manager.
  passwordManagerEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Never allow use of password manager.
    TRUE: Always allow use of password manager.

chrome.users.PaymentMethodQueryEnabled: Payment methods.
  paymentMethodQueryEnabled: TYPE_BOOL
    true: Allow websites to check if the user has payment methods saved.
    false: Always tell websites that no payment methods are saved.

chrome.users.PdfAnnotationsEnabled: PDF Annotations.
  pdfAnnotationsEnabled: TYPE_BOOL
    true: Allow the PDF viewer to annotate PDFs.
    false: Do not allow the PDF viewer to annotate PDFs.

chrome.users.PhoneHub: Phone Hub.
  phoneHubAllowed: TYPE_BOOL
    true: Allow Phone Hub to be enabled.
    false: Do not allow Phone Hub to be enabled.
  phoneHubNotificationsAllowed: TYPE_BOOL
    true: Allow Phone Hub notifications to be enabled. .
    false: Do not allow Phone Hub notifications to be enabled. .
  phoneHubTaskContinuationAllowed: TYPE_BOOL
    true: Allow Phone Hub task continuation to be enabled.
    false: Do not allow Phone Hub task continuation to be enabled.

chrome.users.PinUnlockAutosubmitEnabled: PIN auto-submit.
  pinUnlockAutosubmitEnabled: TYPE_BOOL
    true: Enable PIN auto-submit on the lock and login screen.
    false: Disable PIN auto-submit on the lock and login screen.

chrome.users.PluginVmAllowed: Parallels Desktop.
  pluginVmAllowed: TYPE_BOOL
    true: Allow users to use Parallels Desktop.
    false: Do not allow users to use Parallels Desktop.
  ackNoticeForPluginVmAllowedSetToTrue: TYPE_BOOL

chrome.users.PluginVmDataCollection: Diagnostic information.
  pluginVmDataCollectionAllowed: TYPE_BOOL
    true: Enable sharing diagnostics data to Parallels.
    false: Disable sharing diagnostics data to Parallels.

chrome.users.PluginVmImage: Parallels Desktop Windows image.
  pluginVmImageUrl: TYPE_STRING
    N/A
  pluginVmImageHash: TYPE_STRING
    SHA-256 hash. Enter the SHA-256 hash of the Windows image for Parallels Desktop.

chrome.users.PluginVmRequiredDiskSpace: Required disk space.
  pluginVmRequiredFreeDiskSpace: TYPE_INT64
    Required free disk space (GB).

chrome.users.Popups: Pop-ups.
  defaultPopupsSetting: TYPE_ENUM
    UNSET: Allow the user to decide.
    ALLOW_POPUPS: Allow all pop-ups.
    BLOCK_POPUPS: Block all pop-ups.
  popupsAllowedForUrls: TYPE_LIST
    Allow pop-ups on these sites. Urls to allow pop-ups.
  popupsBlockedForUrls: TYPE_LIST
    Block pop-ups on these sites. Urls to block pop-ups.

chrome.users.PrimaryMouseButtonSwitch: Primary mouse button.
  primaryMouseButtonSwitch: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Left button is primary.
    TRUE: Right button is primary.

chrome.users.PrinterTypeDenyList: Blocked printer types.
  printerTypeDenyList: TYPE_LIST
    {'value': 'privet', 'description': 'Zeroconf-based (mDNS + DNS-SD) protocol.'}

chrome.users.PrintHeaderFooter: Print headers and footers.
  printHeaderFooter: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Never print headers and footers.
    TRUE: Always print headers and footers.

chrome.users.PrintingAllowedBackgroundGraphicsModes: Background graphics printing restriction.
  printingAllowedBackgroundGraphicsModes: TYPE_ENUM
    ANY: Allow the user to decide.
    ENABLED: Always require printing of background images.
    DISABLED: Do not allow printing of background images.

chrome.users.PrintingAllowedPinModes: Restrict PIN printing mode.
  printingAllowedPinModes: TYPE_ENUM
    ANY_PIN_PRINTING_MODE: Do not restrict PIN printing mode.
    PIN_PRINTING_ONLY: Always require PIN printing.
    NON_PIN_PRINTING_ONLY: Do not allow PIN printing.

chrome.users.PrintingBackgroundGraphicsDefault: Background graphics printing default.
  printingBackgroundGraphicsDefault: TYPE_ENUM
    DISABLED: Disable background graphics printing mode by default.
    ENABLED: Enable background graphics printing mode by default.

chrome.users.PrintingMaxSheetsAllowed: Maximum sheets.
  value: TYPE_INT64

chrome.users.PrintingPaperSizeDefault: Default printing page size.
  printingPaperSizeEnum: TYPE_ENUM
    UNSET: No policy set.
    NA_LETTER_8_5X11IN: Letter.
    NA_LEGAL_8_5X14IN: Legal.
    ISO_A4_210X297MM: A4.
    NA_LEDGER_11X17IN: Tabloid.
    ISO_A3_297X420MM: A3.
    CUSTOM: Custom.
  printingPaperSizeWidth: TYPE_STRING
    Page width (in millimeters).
  printingPaperSizeHeight: TYPE_STRING
    Page height (in millimeters).

chrome.users.PrintingPinDefault: Default PIN printing mode.
  printingPinDefault: TYPE_ENUM
    PIN_PRINTING: With PIN.
    NOT_PIN_PRINTING: Without PIN.

chrome.users.PrintingSendUsernameAndFilenameEnabled: CUPS Print job information.
  printingSendUsernameAndFilenameEnabled: TYPE_BOOL
    true: Include user account and filename in print job.
    false: Do not include user account and filename in print job.

chrome.users.PrintJobHistoryExpirationPeriodNew: Print job history retention period.
  seconds: TYPE_INT64
  nanos: TYPE_INT32

chrome.users.PrintPostScriptMode: PostScript printer mode.
  printPostScriptMode: TYPE_ENUM
    DEFAULT: Default.
    TYPE_42: Type 42.

chrome.users.PrintPreview: Print preview.
  disablePrintPreview: TYPE_BOOL
    true: Always use the system print dialog instead of print preview.
    false: Allow using print preview.

chrome.users.PrintPreviewUseSystemDefaultPrinter: System Default Printer.
  printPreviewUseSystemDefaultPrinter: TYPE_BOOL
    true: Use the system default printer as the default choice in Print Preview.
    false: Use the most recently used printer as the default choice in Print Preview.

chrome.users.PrintRasterizationMode: Print rasterization mode.
  printRasterizationMode: TYPE_ENUM
    ULL: Full.
    AST: Fast.

chrome.users.PrivacyScreenEnabled: Privacy screen.
  privacyScreenEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Always disable the privacy screen.
    TRUE: Always enable the privacy screen.

chrome.users.ProfilePickerOnStartupAvailability: Profile picker availability on browser startup.
  profilePickerOnStartupAvailability: TYPE_ENUM
    ENABLED: Allow the user to decide.
    DISABLED: Do not show profile picker at browser startup.
    FORCED: Always show profile picker at browser startup.

chrome.users.PromotionalTabsEnabled: Promotional content.
  promotionalTabsEnabled: TYPE_BOOL
    true: Enable showing full-tab promotional content.
    false: Disable showing full-tab promotional content.

chrome.users.PromptForDownloadLocation: Download location prompt.
  promptForDownloadLocation: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Do not ask the user (downloads start immediately).
    TRUE: Ask the user where to save the file before downloading.

chrome.users.PromptOnMultipleMatchingCertificates: Prompt when multiple certificates match.
  promptOnMultipleMatchingCertificates: TYPE_BOOL
    true: Prompt the user to select the client certificate whenever the auto-selection policy matches multiple certificates.
    false: Only prompt the user when no certificate matches the auto-selection.

chrome.users.QuickAnswersEnabled: Quick Answers.
  quickAnswersEnabled: TYPE_BOOL
    true: Enable Quick Answers.
    false: Disable Quick Answers.
  quickAnswersDefinitionEnabled: TYPE_BOOL
    true: Enable Quick Answers definition.
    false: Disable Quick Answers definition.
  quickAnswersTranslationEnabled: TYPE_BOOL
    true: Enable Quick Answers translation.
    false: Disable Quick Answers translation.
  quickAnswersUnitConversionEnabled: TYPE_BOOL
    true: Enable Quick Answers unit conversion.
    false: Disable Quick Answers unit conversion.

chrome.users.QuickUnlockModeAllowlist: Quick unlock.
  quickUnlockModeAllowlist: TYPE_LIST
    {'value': 'PIN', 'description': 'PIN.'}

chrome.users.QuicProtocol: QUIC protocol.
  quicAllowed: TYPE_BOOL
    true: Enable.
    false: Disable.

chrome.users.RegisteredProtocolHandlersSetting: Custom Protocol Handlers.
  scheme: TYPE_STRING
  handler: TYPE_STRING

chrome.users.RelaunchNotificationWithDuration: Relaunch notification.
  relaunchNotificationEnum: TYPE_ENUM
    NO_NOTIFICATION: No relaunch notification.
    RECOMMENDED: Show notification recommending relaunch.
    REQUIRED: Force relaunch after a period.
  seconds: TYPE_INT32
  nanos: TYPE_INT32
  hours: TYPE_INT32
  minutes: TYPE_INT32

chrome.users.RemoteAccessHostClientDomainList: Remote access clients.
  remoteAccessHostClientDomainList: TYPE_LIST
    Remote access client domain. Configure the required domain names for remote access clients.

chrome.users.RemoteAccessHostDomainList: Remote access hosts.
  remoteAccessHostDomainList: TYPE_LIST
    Remote access host domain. Configure the required domain names for remote access hosts.

chrome.users.RemoteAccessHostFirewallTraversal: Firewall traversal.
  remoteAccessHostFirewallTraversal: TYPE_BOOL
    true: Enable firewall traversal.
    false: Disable firewall traversal.
  remoteAccessHostAllowRelayedConnection: TYPE_BOOL
    true: Enable the use of relay servers.
    false: Disable the use of relay servers.
  remoteAccessHostUdpPortRange: TYPE_STRING
    UDP port range. Format: minimum-maximum (e.g. 12400-12409). If unset, any port may be used.

chrome.users.RemoteDebuggingAllowed: Allow remote debugging.
  remoteDebuggingAllowed: TYPE_BOOL
    true: Allow use of the remote debugging.
    false: Do not allow use of the remote debugging.

chrome.users.RendererCodeIntegrityEnabled: Enable renderer code integrity.
  rendererCodeIntegrityEnabled: TYPE_BOOL
    true: Renderer code integrity enabled.
    false: Renderer code integrity disabled.

chrome.users.RequireOnlineRevocationChecksForLocalAnchors: Require online OCSP/CRL checks for local trust anchors.
  requireOnlineRevocationChecksForLocalAnchors: TYPE_BOOL
    true: Perform revocation checking for successfully validated server certificates signed by locally installed CA certificates.
    false: Use existing online revocation-checking settings.

chrome.users.RestrictAccountsToPatterns: Visible Accounts.
  restrictAccountsToPatterns: TYPE_LIST
    Restrict accounts that are visible in Chrome to those matching one of the patterns specified. Use the wildcard character '*' to match zero or more arbitrary characters. The escape character is '', so to match actual '*' or '' characters, put a '' in front of them.

chrome.users.RestrictPrintColor: Restrict color printing mode.
  printingAllowedColorModes: TYPE_ENUM
    ANY_COLOR_MODE: Do not restrict color printing mode.
    COLOR_ONLY: Color only.
    MONOCHROME_ONLY: Black and white only.

chrome.users.RestrictPrintDuplexMode: Restrict page sides.
  printingAllowedDuplexModes: TYPE_ENUM
    ANY_DUPLEX_MODE: Do not restrict duplex printing mode.
    SIMPLEX_ONLY: One-sided only.
    DUPLEX_ONLY: Two-sided only.

chrome.users.RestrictSigninToPattern: Restrict sign-in to pattern.
  restrictSigninToPattern: TYPE_STRING
    Pattern. A regular expression which is used to determine which Google accounts can be set as browser primary accounts in Google Chrome (i.e. the account that is chosen during the Sync opt-in flow). For example, the value .*@example.com would restrict sign in to accounts in the example.com domain.

chrome.users.SafeBrowsingAllowlistDomain: Safe Browsing allowed domains.
  safeBrowsingAllowlistDomains: TYPE_LIST
    Allowed domains. Enter the list of domains that you want to be excluded from Safe Browsing checks.

chrome.users.SafeBrowsingExtendedReporting: Help improve Safe Browsing.
  safeBrowsingExtendedReportingEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable sending extra information to help improve Safe Browsing.
    TRUE: Enable sending extra information to help improve Safe Browsing.

chrome.users.SafeBrowsingForTrustedSourcesEnabled: Safe Browsing for trusted sources.
  safeBrowsingForTrustedSourcesEnabled: TYPE_BOOL
    true: Perform Safe Browsing checks on all downloaded files.
    false: Skip Safe Browsing checks for files downloaded from trusted sources.

chrome.users.SafeSearchRestrictedMode: SafeSearch and Restricted Mode.
  forceGoogleSafeSearch: TYPE_BOOL
    true: Always use SafeSearch for Google Search queries.
    false: Do not enforce SafeSearch for Google Search queries.
  forceYoutubeRestrictedMode: TYPE_ENUM
    OFF: Do not enforce Restricted Mode on YouTube.
    MODERATE: Enforce at least Moderate Restricted Mode on YouTube.
    STRICT: Enforce Strict Restricted Mode on YouTube.

chrome.users.SafeSitesFilterBehavior: SafeSites URL filter.
  safeSitesFilterBehavior: TYPE_ENUM
    DISABLED: Do not filter sites for adult content.
    ENABLED: Filter top level sites (but not embedded iframes) for adult content.

chrome.users.SamlLockScreenOfflineSigninTimeLimitDays: SAML single sign-on unlock frequency.
  value: TYPE_INT64

chrome.users.SandboxExternalProtocolBlocked: iframe navigation.
  sandboxExternalProtocolBlocked: TYPE_BOOL
    true: Do not allow navigation to external protocols inside a sandboxed iframe.
    false: Allow navigation to external protocols inside a sandboxed iframe.

chrome.users.ScreenBrightnessPercent: Screen brightness.
  brightnessEnabled: TYPE_BOOL
    true: Set initial screen brightness.
    false: Do not set initial screen brightness.
  brightnessAc: TYPE_INT64
    Screen brightness (ac power).
  brightnessBattery: TYPE_INT64
    Screen brightness (battery power).

chrome.users.ScreenCaptureAllowed: Screen video capture.
  screenCaptureAllowed: TYPE_BOOL
    true: Allow sites to prompt the user to share a video stream of their screen.
    false: Do not allow sites to prompt the user to share a video stream of their screen.

chrome.users.ScreenMagnifierType: Screen magnifier.
  screenMagnifierType: TYPE_ENUM
    UNSET: Allow the user to decide.
    DISABLED: Disable screen magnifier.
    FULL_SCREEN: Enable full-screen magnifier.
    DOCKED: Enable docked magnifier.

chrome.users.Screenshot: Screenshot.
  disableScreenshots: TYPE_BOOL
    true: Do not allow users to take screenshots or video recordings.
    false: Allow users to take screenshots and video recordings.

chrome.users.ScrollToTextFragmentEnabled: Scroll to text fragment.
  scrollToTextFragmentEnabled: TYPE_BOOL
    true: Allow sites to scroll to specific text fragments via URL.
    false: Do not allow sites to scroll to specific text fragments via URL.

chrome.users.SearchSuggest: Search suggest.
  searchSuggestEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Never allow users to use Search Suggest.
    TRUE: Always allow users to use Search Suggest.

chrome.users.SecondaryGoogleAccountSignin: Sign-in to secondary accounts.
  secondaryGoogleAccountSigninAllowed: TYPE_ENUM
    UNSET: Allow users to sign in to any secondary Google Accounts.
    FALSE: Block users from signing in to or out of secondary Google Accounts.
    TRUE: Allow users to only sign in to the Google Workspace domains set in 'allowedDomainsForApps'.
  allowedDomainsForApps: TYPE_LIST
    N/A

chrome.users.SecurityKeyAttestation: Security key attestation.
  securityKeyPermitAttestation: TYPE_LIST
    Enter URL or domain. Specifies URLs and domains for which no prompt will be shown when attestation certificates from security keys are requested. Additionally, a signal will be sent to the security key indicating that individual attestation may be used. Without this, users will be prompted in Chrome 65+ when sites request attestation of security keys. URLs (like "https://example.com/some/path") will only match as U2F AppIDs. Domains (like "example.com") only match as WebAuthn RP IDs. Thus, to cover both U2F and WebAuthn APIs for a given site, both the AppID URL and domain would need to be listed.

chrome.users.SecurityTokenSessionSettings: Security token removal.
  securityTokenSessionBehavior: TYPE_ENUM
    IGNORE: Nothing.
    LOGOUT: Log the user out.
    LOCK: Lock the current session.
  seconds: TYPE_INT64
  nanos: TYPE_INT32

chrome.users.SelectToSpeakEnabled: Select to speak.
  selectToSpeakEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable select to speak.
    TRUE: Enable select to speak.

chrome.users.SessionLength: Maximum user session length.
  seconds: TYPE_INT64
  nanos: TYPE_INT32

chrome.users.SharedArrayBufferUnrestrictedAccessAllowed: SharedArrayBuffer.
  sharedArrayBufferUnrestrictedAccessAllowed: TYPE_BOOL
    true: Allow sites that are not cross-origin isolated to use SharedArrayBuffers.
    false: Prevent sites that are not cross-origin isolated from using SharedArrayBuffers.

chrome.users.SharedClipboardEnabled: Shared clipboard.
  sharedClipboardEnabled: TYPE_BOOL
    true: Enable the shared clipboard feature.
    false: Disable the shared clipboard feature.

chrome.users.ShelfAlign: Shelf position.
  shelfAlignment: TYPE_ENUM
    USER_CHOICE: Allow the user to decide.
    BOTTOM: Bottom.
    LEFT: Left.
    RIGHT: Right.

chrome.users.ShelfAutoHideBehavior: Shelf auto-hiding.
  shelfAutoHideBehavior: TYPE_ENUM
    USER_CHOICE: Allow the user to decide.
    ALWAYS_AUTO_HIDE_SHELF: Always auto-hide the shelf.
    NEVER_AUTO_HIDE_SHELF: Never auto-hide the shelf.

chrome.users.ShowAccessibilityOptionsInSystemTrayMenu: Accessibility options in the system tray menu.
  showAccessibilityOptionsInSystemTrayMenu: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Hide accessibility options in the system tray menu.
    TRUE: Show accessibility options in the system tray menu.

chrome.users.ShowAppsShortcutInBookmarkBar: Apps shortcut in the bookmark bar.
  showAppsShortcutInBookmarkBar: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Hide the apps shortcut from the bookmark bar.
    TRUE: Show the apps shortcut in the bookmark bar.

chrome.users.ShowFullUrlsInAddressBar: URLs in the address bar.
  showFullUrlsInAddressBar: TYPE_ENUM
    UNSET: Display the default URL. Users may switch to the full URL unless on a managed Chrome OS device.
    FALSE: Display the default URL.
    TRUE: Display the full URL.

chrome.users.ShowLogoutButton: Show logout button in tray.
  showLogoutButtonInTray: TYPE_BOOL
    true: Show logout button in tray.
    false: Do not show logout button in tray.

chrome.users.SideSearchEnabled: Side panel search history.
  sideSearchEnabled: TYPE_BOOL
    true: Enable showing the most recent <ph name="GOOGLE_SEARCH_PRODUCT_NAME">Google Search</ph> results in a Browser side panel.
    false: Disable showing the most recent <ph name="GOOGLE_SEARCH_PRODUCT_NAME">Google Search</ph> results in a Browser side panel.

chrome.users.SignedHttpExchangeEnabled: Signed HTTP Exchange (SXG) support.
  signedHttpExchangeEnabled: TYPE_BOOL
    true: Accept web content served as Signed HTTP Exchanges.
    false: Prevent Signed HTTP Exchanges from loading.

chrome.users.SigninInterceptionEnabled: Signin interception.
  signinInterceptionEnabled: TYPE_BOOL
    true: Enable signin interception.
    false: Disable signin interception.

chrome.users.SimpleProxySettings: Proxy mode.
  simpleProxyMode: TYPE_ENUM
    USER_CONFIGURED: Allow user to configure.
    DIRECT: Never use a proxy.
    AUTO_DETECT: Always auto detect the proxy.
    FIXED_SERVERS: Always use the proxy specified in 'simpleProxyServerUrl'.
    PAC_SCRIPT: Always use the proxy auto-config specified in 'simpleProxyPacUrl'.
  simpleProxyServerUrl: TYPE_STRING
    Proxy server URL.
  simpleProxyPacUrl: TYPE_STRING
    Proxy server auto configuration file URL. URL of the .pac file that should be used for network connections.
  proxyBypassList: TYPE_LIST
    URLs which bypass the proxy.

chrome.users.SingleSignOn: Single sign-on.
  idpRedirectEnabled: TYPE_BOOL
    true: Enable SAML-based single sign-on for Chrome devices.
    false: Disable SAML-based single sign-on for Chrome devices.

chrome.users.SingleSignOnLoginFrequency: SAML single sign-on login frequency.
  samlOfflineSigninTimeLimit: TYPE_ENUM
    SAML_ONE_DAY: Every day.
    SAML_THREE_DAYS: Every 3 days.
    SAML_ONE_WEEK: Every week.
    SAML_TWO_WEEKS: Every 2 weeks.
    SAML_THREE_WEEKS: Every 3 weeks.
    SAML_FOUR_WEEKS: Every 4 weeks.
    EVERY_TIME: Every Time.
    SAML_NEVER: Never.

chrome.users.SiteIsolationAndroid: Site isolation (Chrome on Android).
  sitePerProcessAndroid: TYPE_ENUM
    UNSET: Turn on site isolation only for login sites, as well as any origins specified in 'isolateOriginsAndroid'.
    FALSE: Turn off site isolation for all websites, except those set in 'isolateOriginsAndroid'.
    TRUE: Turn on site isolation for all websites, as well as any origins specified in 'isolateOriginsAndroid'.
  isolateOriginsAndroid: TYPE_LIST
    Isolated origins (Android). Enter a list of origins to isolate within a website on Android, for instance https://login.example.com or https://[*.]example.com.

chrome.users.SiteIsolationBrowser: Site isolation.
  isolateOrigins: TYPE_LIST
    Isolated origins. Enter a list of origins to isolate within a website, for instance https://login.example.com or https://[*.]example.com. .
  sitePerProcess: TYPE_BOOL
    true: Require site isolation for all websites, as well as any origins specified in 'isolateOrigins'.
    false: Turn off site isolation for all websites, except those set in 'isolateOrigins'.

chrome.users.SmartLockAllowed: Smart Lock.
  smartLockAllowed: TYPE_BOOL
    true: Allow Smart Lock.
    false: Do not allow Smart Lock.

chrome.users.SpellcheckEnabled: Spell check.
  spellcheckEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable spell check.
    TRUE: Enable spell check.
  spellcheckLanguage: TYPE_LIST
    N/A
  spellcheckLanguageBlocklist: TYPE_LIST
    N/A

chrome.users.SpellCheckService: Spell check service.
  spellCheckServiceEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable the spell checking web service.
    TRUE: Enable the spell checking web service.

chrome.users.SpokenFeedbackEnabled: Spoken feedback.
  spokenFeedbackEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable spoken feedback.
    TRUE: Enable spoken feedback.

chrome.users.SslErrorOverrideAllowed: SSL error override.
  sslErrorOverrideAllowed: TYPE_BOOL
    true: Allow users to click through SSL warnings and proceed to the page.
    false: Block users from clicking through SSL warnings.

chrome.users.SslErrorOverrideAllowedForOrigins: SSL error override allowed domains.
  sslErrorOverrideAllowedForOrigins: TYPE_LIST
    Domains that allow clicking through SSL warnings. Enter a list of domain names.

chrome.users.SslVersionMin: Minimum SSL version enabled.
  sslVersionMin: TYPE_ENUM
    TL_SV_1: TLS 1.0.
    TL_SV_1_1: TLS 1.1.
    TL_SV_1_2: TLS 1.2.
    SSL_V_3: SSL3.

chrome.users.StartupPages: Pages to load on startup.
  restoreOnStartupUrls: TYPE_LIST
    Startup pages. Example: https://example.com.

chrome.users.StickyKeysEnabled: Sticky keys.
  stickyKeysEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable sticky keys.
    TRUE: Enable sticky keys.

chrome.users.SuggestedContentEnabled: Suggested content.
  suggestedContentEnabled: TYPE_BOOL
    true: Enable suggested content.
    false: Disable suggested content.

chrome.users.SuppressCrossOriginIframeDialogs: Cross-origin JavaScript dialogs.
  suppressCrossOriginIframeDialogs: TYPE_BOOL
    true: Block JavaScript dialogs triggered from a cross-origin iframe.
    false: Allow JavaScript dialogs triggered from a cross-origin iframe.

chrome.users.SuppressUnsupportedOsWarning: Unsupported system warning.
  suppressUnsupportedOsWarning: TYPE_BOOL
    true: Suppress warnings when Chrome is running on an unsupported system.
    false: Allow Chrome to display warnings when running on an unsupported system.

chrome.users.SyncSettingsCbcm: Chrome Sync and Roaming Profiles (Chrome Browser - Cloud Managed).
  syncTypeCbcm: TYPE_ENUM
    CLOUD_DEFAULT_VALUE: Allow Chrome Sync.
    ROAMING_PROFILES: Allow Roaming Profiles.
    DISABLED: Disallow Sync.
  syncTypesListDisabledCbcm: TYPE_LIST
    {'value': 'apps', 'description': 'Apps.'}
  clearBrowsingDataOnExitListCbcm: TYPE_LIST
    {'value': 'browsing_history', 'description': 'Browsing history.'}
  roamingProfileLocationCbcm: TYPE_STRING
    Roaming profile directory.

chrome.users.SyncSettingsCros: Chrome Sync (Chrome OS).
  syncDisabledCros: TYPE_BOOL
    true: Disable Chrome Sync.
    false: Allow Chrome Sync.
  syncTypesListDisabledCros: TYPE_LIST
    {'value': 'apps', 'description': 'Apps.'}
  clearBrowsingDataOnExitListCros: TYPE_LIST
    {'value': 'browsing_history', 'description': 'Browsing history.'}

chrome.users.SystemFeaturesDisableList: Disabled system features.
  systemFeaturesDisableList: TYPE_LIST
    {'value': 'camera', 'description': 'Camera.'}

chrome.users.TargetBlankImpliesNoOpener: Popup interactions.
  targetBlankImpliesNoOpener: TYPE_BOOL
    true: Block popups opened with a target of _blank from interacting with the page that opened the popup.
    false: Allow popups opened with a target of _blank to interact with the page that opened the popup.

chrome.users.TaskManager: Task manager.
  taskManagerEndProcessEnabled: TYPE_BOOL
    true: Allow users to end processes with the Chrome task manager.
    false: Block users from ending processes with the Chrome task manager.

chrome.users.ThirdPartyBlockingEnabled: Third party code.
  thirdPartyBlockingEnabled: TYPE_BOOL
    true: Prevent third party code from being injected into Chrome.
    false: Allow third party code to be injected into Chrome.

chrome.users.ThirdPartyCookieBlocking: Third-party cookie blocking.
  blockThirdPartyCookies: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Allow third-party cookies.
    TRUE: Disallow third-party cookies.

chrome.users.ThreeDContent: 3D content.
  disable3dApis: TYPE_BOOL
    true: Never allow display of 3D content.
    false: Always allow display of 3D content.

chrome.users.TotalMemoryLimitMb: Chrome browser memory limit.
  totalMemoryLimitMb: TYPE_INT64
    Memory consumption limit in MB (minimum 1024).

chrome.users.Translate: Google Translate.
  translateEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Never offer translation.
    TRUE: Always offer translation.

chrome.users.TripleDesEnabled: 3DES cipher suites in TLS.
  tripleDesEnabled: TYPE_ENUM
    UNSET: Use the default setting for 3DES cipher suites in TLS.
    FALSE: Disable 3DES cipher suites in TLS.
    TRUE: Enable 3DES cipher suites in TLS.

chrome.users.UnifiedDesktop: Unified Desktop (BETA).
  unifiedDesktopEnabledByDefault: TYPE_BOOL
    true: Make Unified Desktop mode available to user.
    false: Do not make Unified Desktop mode available to user.

chrome.users.UpdatesSuppressed: Suppress auto-update check.
  updatesSuppressedDurationMin: TYPE_INT64
    Duration (minutes). Auto-update checks will begin to be suppressed at the start time specified in 'updatesSuppressedStartTime', for the duration specified here, in minutes. This duration does not take into account daylight savings time.
  hours: TYPE_INT32
  minutes: TYPE_INT32
  seconds: TYPE_INT32
  nanos: TYPE_INT32

chrome.users.UrlBlocking: URL blocking.
  urlBlocklist: TYPE_LIST
    Blocked URLs. Any URL in this list will be blocked, unless it also appears in the list of exceptions specified in 'urlAllowlist'. Maximum of 1000 URLs. Note: to block OS and browser settings set the 'chrome.users.SystemFeaturesDisableList' policy instead of blocking 'chrome://' URLs.
  urlAllowlist: TYPE_LIST
    Blocked URL exceptions. Any URL that matches an entry in this exception list will be allowed, even if it matches an entry in the blocked URLs. Wildcards ("*") are allowed when appended to a URL, but cannot be entered alone. Maximum of 1000 URLs. .

chrome.users.UrlKeyedAnonymizedDataCollectionEnabled: Enable URL-keyed anonymized data collection.
  urlKeyedAnonymizedDataCollectionEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Data collection is never active.
    TRUE: Data collection is always active.

chrome.users.UserAgentClientHintsEnabled: User-Agent client hints.
  userAgentClientHintsEnabled: TYPE_BOOL
    true: Allow User-Agent client hints.
    false: Disable User-Agent client hints.

chrome.users.UserDataSnapshotRetentionLimit: User data snapshot limits.
  userDataSnapshotRetentionLimit: TYPE_INT64
    The maximum number of user data snapshots retained. Set to 0 to disable taking snapshots.

chrome.users.UserDownloadDirectory: Download location.
  downloadDirectory: TYPE_ENUM
    LOCAL_FOLDER_DEFAULT: Set local Downloads folder as default, but allow user to change.
    GOOGLE_DRIVE_DEFAULT: Set Google Drive as default, but allow user to change.
    GOOGLE_DRIVE_FORCED: Force Google Drive.

chrome.users.UserFeedbackAllowed: Allow user feedback.
  userFeedbackAllowed: TYPE_BOOL
    true: Allow user feedback.
    false: Do not allow user feedback.

chrome.users.UserPrintersAllowed: Printer management.
  userPrintersAllowed: TYPE_BOOL
    true: Allow users to add new printers.
    false: Do not allow users to add new printers.

chrome.users.UTwoFSecurityKeyApiEnabled: U2F Security Key API.
  uTwoFSecurityKeyApiEnabled: TYPE_BOOL
    true: Allow use of the deprecated U2F Security Key API.
    false: Apply default settings for U2F API deprecation.

chrome.users.Variations: Variations.
  variationsEnabled: TYPE_ENUM
    ENABLED: Enable Chrome variations.
    CRITICAL_FIXES_ONLY: Enable variations for critical fixes only.
    DISABLED: Disable variations.

chrome.users.VerifiedMode: Verified Mode.
  userVerifiedModeRequired: TYPE_BOOL
    true: Require verified mode boot for Verified Access.
    false: Skip boot mode check for Verified Access.
  servicesWithFullAccess: TYPE_LIST
    Service accounts which are allowed to receive user data. Service accounts allowed to receive user data.
  servicesWithLimitedAccess: TYPE_LIST
    Service accounts which can verify users but do not receive user data. Service accounts which can verify users but do not receive user data.

chrome.users.VideoCaptureAllowedUrls: Video input allowed URLs.
  videoCaptureAllowedUrls: TYPE_LIST
    URL patterns to allow. URLs that will be granted access to the video input device without a prompt. Prefix domain with [*.] to include subdomains.

chrome.users.VideoInput: Built-in camera access.
  videoCaptureAllowed: TYPE_BOOL
    true: Enable camera input for websites and apps.
    false: Disable camera input for websites and apps.

chrome.users.VirtualKeyboardEnabled: On-screen keyboard.
  virtualKeyboardEnabled: TYPE_ENUM
    UNSET: Allow the user to decide.
    FALSE: Disable on-screen keyboard.
    TRUE: Enable on-screen keyboard.

chrome.users.VirtualMachinesAllowed: Linux virtual machines (BETA).
  virtualMachinesAllowed: TYPE_BOOL
    true: Allow usage for virtual machines needed to support Linux apps for users.
    false: Block usage for virtual machines needed to support Linux apps for users.

chrome.users.VirtualMachinesAndroidAdbSideloadingAllowed: Android apps from untrusted sources.
  virtualMachinesAndroidAdbSideloadingAllowed: TYPE_ENUM
    DISALLOW: Prevent the user from using Android apps from untrusted sources.
    ALLOW: Allow the user to use Android apps from untrusted sources.

chrome.users.VirtualMachinesCommandLineAccessAllowed: Command line access.
  virtualMachinesCommandLineAccessAllowed: TYPE_BOOL
    true: Enable VM command line access.
    false: Disable VM command line access.

chrome.users.VirtualMachinesPortForwardingAllowed: Port forwarding.
  virtualMachinesPortForwardingAllowed: TYPE_BOOL
    true: Allow users to enable and configure port forwarding into the VM container.
    false: Do not allow users to enable and configure port forwarding into the VM container.

chrome.users.Wallpaper: Custom wallpaper.
  downloadUri: TYPE_STRING

chrome.users.WebBluetoothAccess: Web Bluetooth API.
  defaultWebBluetoothGuardSetting: TYPE_ENUM
    UNSET: Allow the user to decide.
    BLOCK_WEB_BLUETOOTH: Do not allow sites to request access to Bluetooth devices via the Web Bluetooth API.
    ASK_WEB_BLUETOOTH: Allow sites to request access to Bluetooth devices via the Web Bluetooth API.

chrome.users.WebRtcAllowLegacyTlsProtocols: Legacy TLS/DTLS downgrade in WebRTC.
  webRtcAllowLegacyTlsProtocols: TYPE_BOOL
    true: Enable WebRTC peer connections downgrading to obsolete versions of the TLS/DTLS (DTLS 1.0, TLS 1.0 and TLS 1.1) protocols.
    false: Disable WebRTC peer connections downgrading to obsolete versions of the TLS/DTLS (DTLS 1.0, TLS 1.0 and TLS 1.1) protocols.

chrome.users.WebrtcEventLogCollectionAllowed: WebRTC event log collection.
  webRtcEventLogCollectionAllowed: TYPE_BOOL
    true: Allow WebRTC event log collection.
    false: Do not allow WebRTC event log collection.

chrome.users.WebRtcIpHandling: WebRTC IP handling.
  webRtcIpHandling: TYPE_ENUM
    EFAULT: WebRTC will use all available interfaces when searching for the best path.
    EFAULT_PUBLIC_AND_PRIVATE_INTERFACES: WebRTC will only use the interface connecting to the public Internet, but may connect using private IP addresses.
    EFAULT_PUBLIC_INTERFACE_ONLY: WebRTC will only use the interface connecting to the public Internet, and will not connect using private IP addresses.
    ISABLE_NON_PROXIED_UDP: WebRTC will use TCP on the public-facing interface, and will only use UDP if supported by a configured proxy.

chrome.users.WebRtcLocalIpsAllowedUrls: WebRTC ICE candidate URLs for local IPs.
  webRtcLocalIpsAllowedUrls: TYPE_LIST
    URLs for which local IPs are exposed in WebRTC ICE candidates. . Patterns in this list will be matched against the security origin of the requesting URL. If a match is found the local IP addresses are shown in WebRTC ICE candidates. Otherwise, local IP addresses are concealed with mDNS hostnames. Please note that this policy weakens the protection of local IPs if needed by administrators. .

chrome.users.WebRtcUdpPortRange: WebRTC UDP ports.
  webRtcUdpPortsEnabled: TYPE_BOOL
    false: Allow WebRTC to pick any UDP port (1024-65535).
    true: Specify range of UDP ports allowed for WebRTC.
  webRtcUdpPortsMin: TYPE_INT64
    Minimum value for allowed UDP ports. This setting can only be set after setting web_rtc_udp_ports_enabled = true.
  webRtcUdpPortsMax: TYPE_INT64
    Maximum value for allowed UDP ports. This setting can only be set after setting web_rtc_udp_ports_enabled = true.

chrome.users.WebSerialPortAccess: Serial Port API.
  defaultSerialGuardSetting: TYPE_ENUM
    BLOCK_SERIAL: Do not allow any site to request access to serial ports via the Serial Port API.
    ALLOW_ASK_SERIAL: Allow sites to ask the user to grant access to a serial ports via the Serial Port API.
    UNSET: Allow the user to decide.
  serialAskForUrls: TYPE_LIST
    Allow the Serial API on these sites. List of URLs that specify websites that will be allowed to ask users to grant them access to the serial ports. Prefix domain with [*.] to include subdomains.
  serialBlockedForUrls: TYPE_LIST
    Block the Serial API on these sites. List of URLs patterns that specify which websites can't ask users to grant them access to a serial port. Prefix domain with [*.] to include subdomains.

chrome.users.WebSqlInThirdPartyContextEnabled: WebSQL in third-party context.
  webSqlInThirdPartyContextEnabled: TYPE_BOOL
    true: Allow WebSQL in third-party contexts.
    false: Do not allow WebSQL in third-party contexts.

chrome.users.WebUsbPortAccess: Controls which websites can ask for USB access.
  defaultWebUsbGuardSetting: TYPE_ENUM
    BLOCK_WEB_USB: Do not allow any site to request access.
    ASK_WEB_USB: Allow sites to ask the user for access.
    UNSET: Allow the user to decide if sites can ask.
  webUsbAskForUrls: TYPE_LIST
    Allow these sites to ask for USB access. For detailed information on valid url patterns, please see URL patterns at https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns. Note: using only the "*" wildcard is not valid.
  webUsbBlockedForUrls: TYPE_LIST
    Block these sites from asking for USB access. For detailed information on valid url patterns, please see URL patterns at https://cloud.google.com/docs/chrome-enterprise/policies/url-patterns. Note: using only the "*" wildcard is not valid.

chrome.users.WebXrImmersiveArEnabled: WebXR immersive-ar sessions.
  webXrImmersiveArEnabled: TYPE_BOOL
    true: Allow creating WebXR immersive-ar sessions.
    false: Prevent creating WebXR immersive-ar sessions.

chrome.users.WifiSyncAndroidAllowed: Wi-Fi network configurations sync.
  wifiSyncAndroidAllowed: TYPE_BOOL
    true: Allow Wi-Fi network configurations to be synced across Google Chrome OS devices and a connected Android phone.
    false: Do not allow Wi-Fi network configurations to be synced across Google Chrome OS devices and a connected Android phone.

chrome.users.WindowOcclusionEnabled: Occluded window rendering.
  windowOcclusionEnabled: TYPE_BOOL
    true: Allow detection of window occlusion.
    false: Disable detection of window occlusion.

chrome.users.WpadQuickCheckEnabled: WPAD optimization.
  wpadQuickCheckEnabled: TYPE_BOOL
    true: Enable Web Proxy Auto-Discovery (WPAD) optimization.
    false: Disable Web Proxy Auto-Discovery (WPAD) optimization.

```
```

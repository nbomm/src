# Basic Items
- [Primitives](#primitives)
- [Items built from primitives](#items-built-from-primitives)
- [Named items](#named-items)
- [List Items](List-Items)

## Primitives
```
<Character> ::= a single character
<Digit> ::= 0|1|2|3|4|5|6|7|8|9
<Number> ::= <Digit>+
<Float> ::= <Digit>*.<Digit>+
<Hex> ::= <Digit>|a|b|c|d|e|f|A|B|C|D|E|F
<Space> ::= an actual space character
<String> ::= a string of characters, surrounded by " if it contains spaces
<FalseValues>= false|off|no|disabled|0
<TrueValues> ::= true|on|yes|enabled|1

<Charset> ::= ascii|latin1|mbcs|utf-8|utf-8-sig|utf-16|<String>
<CalendarColorIndex> ::= <Number in range 1-24>
<CalendarColorName> ::=
        amethyst|avocado|banana|basil|birch|blueberry|
        cherryblossom|citron|cobalt|cocoa|eucalyptus|flamingo|
        grape|graphite|lavender|mango|peacock|pistachio|
        pumpkin|radicchio|sage|tangerine|tomato|wisteria|
<ColorHex> ::= "#<Hex><Hex><Hex><Hex><Hex><Hex>"
<ColorNameGoogle> ::=
        asparagus|bluevelvet|bubblegum|cardinal|chocolateicecream|denim|desertsand|
        earthworm|macaroni|marsorange|mountaingray|mountaingrey|mouse|oldbrickred|
        pool|purpledino|purplerain|rainysky|seafoam|slimegreen|spearmint|
        toyeggplant|vernfern|wildstrawberries|yellowcab
<ColorNameWeb> ::=
        aliceblue|antiquewhite|aqua|aquamarine|azure|beige|bisque|black|blanchedalmond|
        blue|blueviolet|brown|burlywood|cadetblue|chartreuse|chocolate|coral|
        cornflowerblue|cornsilk|crimson|cyan|darkblue|darkcyan|darkgoldenrod|darkgray|
        darkgrey|darkgreen|darkkhaki|darkmagenta|darkolivegreen|darkorange|darkorchid|
        darkred|darksalmon|darkseagreen|darkslateblue|darkslategray|darkslategrey|
        darkturquoise|darkviolet|deeppink|deepskyblue|dimgray|dimgrey|dodgerblue|
        firebrick|floralwhite|forestgreen|fuchsia|gainsboro|ghostwhite|gold|goldenrod|
        gray|grey|green|greenyellow|honeydew|hotpink|indianred|indigo|ivory|khaki|
        lavender|lavenderblush|lawngreen|lemonchiffon|lightblue|lightcoral|lightcyan|
        lightgoldenrodyellow|lightgray|lightgrey|lightgreen|lightpink|lightsalmon|
        lightseagreen|lightskyblue|lightslategray|lightslategrey|lightsteelblue|
        lightyellow|lime|limegreen|linen|magenta|maroon|mediumaquamarine|mediumblue|
        mediumorchid|mediumpurple|mediumseagreen|mediumslateblue|mediumspringgreen|
        mediumturquoise|mediumvioletred|midnightblue|mintcream|mistyrose|moccasin|
        navajowhite|navy|oldlace|olive|olivedrab|orange|orangered|orchid|
        palegoldenrod|palegreen|paleturquoise|palevioletred|papayawhip|peachpuff|
        peru|pink|plum|powderblue|purple|red|rosybrown|royalblue|saddlebrown|salmon|
        sandybrown|seagreen|seashell|sienna|silver|skyblue|slateblue|slategray|
        slategrey|snow|springgreen|steelblue|tan|teal|thistle|tomato|turquoise|violet|
        wheat|white|whitesmoke|yellow|yellowgreen
<ColorName> ::= <ColorNameGoogle>|<ColorNameWeb>
<ColorValue> ::= <ColorName>|<ColorHex>
<DayOfWeek> ::= mon|tue|wed|thu|fri|sat|sun
<EventColorIndex> ::= <Number in range 1-11>
<EventColorName> ::=
        banana|basil|blueberry|flamingo|graphite|grape|
        lavender|peacock|sage|tangerine|tomato
<FileFormat> ::=
        csv|doc|dot|docx|dotx|epub|html|jpeg|jpg|mht|odp|ods|odt|
        pdf|png|ppt|pot|potx|pptx|rtf|svg|tsv|txt|xls|xlt|xlsx|xltx|zip|
        ms|microsoft|openoffice|
<LabelColorHex> ::=
        #000000|#076239|#0b804b|#149e60|#16a766|#1a764d|#1c4587|#285bac|
        #2a9c68|#3c78d8|#3dc789|#41236d|#434343|#43d692|#44b984|#4a86e8|
        #653e9b|#666666|#68dfa9|#6d9eeb|#822111|#83334c|#89d3b2|#8e63ce|
        #999999|#a0eac9|#a46a21|#a479e2|#a4c2f4|#aa8831|#ac2b16|#b65775|
        #b694e8|#b9e4d0|#c6f3de|#c9daf8|#cc3a21|#cccccc|#cf8933|#d0bcf1|
        #d5ae49|#e07798|#e4d7f5|#e66550|#eaa041|#efa093|#efefef|#f2c960|
        #f3f3f3|#f691b3|#f6c5be|#f7a7c0|#fad165|#fb4c2f|#fbc8d9|#fcda83|
        #fcdee8|#fce8b3|#fef1d1|#ffad47|#ffbc6b|#ffd6a2|#ffe6c7|#ffffff
<LanguageCode> ::=
        ach|af|ag|ak|am|ar|az|be|bem|bg|bn|br|bs|ca|chr|ckb|co|crs|cs|cy|da|de|
        ee|el|en|en-gb|en-us|eo|es|es-419|et|eu|fa|fi|fil|fo|fr|fr-ca|fy|
        ga|gaa|gd|gl|gn|gu|ha|haw|he|hi|hr|ht|hu|hy|ia|id|ig|in|is|it|iw|ja|jw|
        ka|kg|kk|km|kn|ko|kri|ku|ky|la|lg|ln|lo|loz|lt|lua|lv|
        mfe|mg|mi|mk|ml|mn|mo|mr|ms|mt|my|ne|nl|nn|no|nso|ny|nyn|oc|om|or|
        pa|pcm|pl|ps|pt-br|pt-pt|qu|rm|rn|ro|ru|rw|
        sd|sh|si|sk|sl|sn|so|sq|sr|sr-me|st|su|sv|sw|
        ta|te|tg|th|ti|tk|tl|tn|to|tr|tt|tum|tw|
        ug|uk|ur|uz|vi|wo|xh|yi|yo|zh-cn|zh-hk|zh-tw|zu
<Language> ::=
        <LanguageCode>[+|-]|
        <String>
<Locale> ::=
        ''|    #Not defined
        ar_eg| #Arabic, Egypt
        az_az| #Azerbaijani, Azerbaijan
        be_by| #Belarusian, Belarus
        bg_bg| #Bulgarian, Bulgaria
        bn_in| #Bengali, India
        ca_es| #Catalan, Spain
        cs_cz| #Czech, Czech Republic
        cy_gb| #Welsh, United Kingdom
        da_dk| #Danish, Denmark
        de_ch| #German, Switzerland
        de_de| #German, Germany
        el_gr| #Greek, Greece
        en_au| #English, Australia
        en_ca| #English, Canada
        en_gb| #English, United Kingdom
        en_ie| #English, Ireland
        en_us| #English, U.S.A.
        es_ar| #Spanish, Argentina
        es_bo| #Spanish, Bolivia
        es_cl| #Spanish, Chile
        es_co| #Spanish, Colombia
        es_ec| #Spanish, Ecuador
        es_es| #Spanish, Spain
        es_mx| #Spanish, Mexico
        es_py| #Spanish, Paraguay
        es_uy| #Spanish, Uruguay
        es_ve| #Spanish, Venezuela
        fi_fi| #Finnish, Finland
        fil_ph| #Filipino, Philippines
        fr_ca| #French, Canada
        fr_fr| #French, France
        gu_in| #Gujarati, India
        hi_in| #Hindi, India
        hr_hr| #Croatian, Croatia
        hu_hu| #Hungarian, Hungary
        hy_am| #Armenian, Armenia
        in_id| #Indonesian, Indonesia
        it_it| #Italian, Italy
        iw_il| #Hebrew, Israel
        ja_jp| #Japanese, Japan
        ka_ge| #Georgian, Georgia
        kk_kz| #Kazakh, Kazakhstan
        kn_in| #Kannada, India
        ko_kr| #Korean, Korea
        lt_lt| #Lithuanian, Lithuania
        lv_lv| #Latvian, Latvia
        ml_in| #Malayalam, India
        mn_mn| #Mongolian, Mongolia
        mr_in| #Marathi, India
        my_mn| #Burmese, Myanmar
        nl_nl| #Dutch, Netherlands
        nn_no| #Nynorsk, Norway
        no_no| #Bokmal, Norway
        pa_in| #Punjabi, India
        pl_pl| #Polish, Poland
        pt_br| #Portuguese, Brazil
        pt_pt| #Portuguese, Portugal
        ro_ro| #Romanian, Romania
        ru_ru| #Russian, Russia
        sk_sk| #Slovak, Slovakia
        sl_si| #Slovenian, Slovenia
        sr_rs| #Serbian, Serbia
        sv_se| #Swedish, Sweden
        ta_in| #Tamil, India
        te_in| #Telugu, India
        th_th| #Thai, Thailand
        tr_tr| #Turkish, Turkey
        uk_ua| #Ukrainian, Ukraine
        vi_vn| #Vietnamese, Vietnam
        zh_cn| #Simplified Chinese, China
        zh_hk| #Traditional Chinese, Hong Kong SAR China
        zh_tw  #Traditional Chinese, Taiwan
<MimeTypeShortcut> ::=
        gdoc|gdocument|
        gdrawing|
        gfile|
        gfolder|gdirectory|
        gform|
        gfusion|
        gmap|
        gpresentation|
        gscript|
        gsheet|gspreadsheet|
        gshortcut|
        g3pshortcut|
        gsite|
        shortcut
<MimeTypeName> ::= application|audio|font|image|message|model|multipart|text|video
<MimeType> ::= <MimeTypeShortcut>|(<MimeTypeName>/<String>)
<ProductID> ::=
        nv:<String> |
        101001 |
        101005 |
        101031 |
        101033 |
        101034 |
        101035 |
        101037 |
        Google-Apps |
        Google-Chrome-Device-Management |
        Google-Drive-storage |
        Google-Vault
<SKUID> ::=
        nv:<String>:<String> |
        20gb | drive20gb | googledrivestorage20gb | Google-Drive-storage-20GB |
        50gb | drive50gb | googledrivestorage50gb | Google-Drive-storage-50GB |
        200gb | drive200gb | googledrivestorage200gb | Google-Drive-storage-200GB |
        400gb | drive400gb | googledrivestorage400gb | Google-Drive-storage-400GB |
        1tb | drive1tb | googledrivestorage1tb | Google-Drive-storage-1TB |
        2tb | drive2tb | googledrivestorage2tb | Google-Drive-storage-2TB |
        4tb | drive4tb | googledrivestorage4tb | Google-Drive-storage-4TB |
        8tb | drive8tb | googledrivestorage8tb | Google-Drive-storage-8TB |
        16tb | drive16tb | googledrivestorage16tb | Google-Drive-storage-16TB |
        cdm | chrome | googlechromedevicemanagement | Google-Chrome-Device-Management |
        cloudidentity | identity | 1010010001 |
        cloudidentitypremium | identitypremium | 1010050001 |
        cloudsearch | 1010350001 |
        gsuitebasic | gafb | gafw | basic | Google-Apps-For-Business |
        gsuitebusiness | gau | gsb | unlimited | Google-Apps-Unlimited |
        gsuitebusinessarchived | gsbau | businessarchived | 1010340002 |
        gsuiteenterprisearchived | gseau | enterprisearchived | 1010340001 |
        gsuiteenterpriseeducation | gsefe | e4e | 1010310002 |
        gsuiteenterpriseeducationstudent | gsefes | e4es | 1010310003 |
        gsuitegov | gafg | gsuitegovernment | Google-Apps-For-Government |
        gsuitelite | gal | gsl | lite | Google-Apps-Lite |
        gwep | workspaceeducationplus | 1010310008 |
        gwepstaff | workspaceeducationplusstaff | 1010310009 |
        gwepstudent | workspaceeducationplusstudent | 1010310010 |
        gwes | workspaceeducationstandard | 1010310005 |
        gwesstaff | workspaceeducationstandardstaff | 1010310006 |
        gwesstudent | workspaceeducationstandardstudent | 1010310007 |
        gwetlu | workspaceeducationupgrade | 1010370001 |
        postini | gams | gsuitegams | gsuitepostini | gsuitemessagesecurity | Google-Apps-For-Postini |
        standard | free | Google-Apps |
        vault | googlevault | Google-Vault |
        vfe | googlevaultformeremployee | Google-Vault-Former-Employee |
        voicepremier | gvpremier | googlevoicepremier | 1010330002 |
        voicestandard | gvstandard | googlevoicestandard | 1010330004 |
        voicestarter | gvstarter | googlevoicestarter | 1010330003 |
        workspacefrontline | workspacefrontlineworker | 1010020030 |
        wsbizplus | workspacebusinessplus | 1010020025 |
        wsbizplusarchived | workspacebusinessplusarchived | 1010340003 |
        wsbizstan | workspacebusinessstandard | 1010020028 |
        wsbizstart | workspacebusinessstarter | 1010020027 |
        wsentess | workspaceenterpriseessentials | 1010060003 |
        wsentplus | workspaceenterpriseplus | gae | gse | enterprise | gsuiteenterprise | 1010020020 |
        wsentstan | workspaceenterprisestandard | 1010020026 |
        wsentstanarchived | workspaceenterprisestandardarchived | 1010340004 |
        wsess | workspaceesentials | gsuiteessentials | essentials | d4e | driveenterprise | drive4enterprise | 1010060001
```
## Items built from primitives
```
<Boolean> ::= <TrueValues>|<FalseValues>
<ByteCount> ::= <Number>[m|k|b]
<CIDRnetmask> ::= <Number>.<Number>.<Number>.<Number>/<Number>
<Year> ::= <Digit><Digit><Digit><Digit>
<Month> ::= <Digit><Digit>
<Day> ::= <Digit><Digit>
<Hour> ::= <Digit><Digit>
<Minute> ::= <Digit><Digit>
<Second> ::= <Digit><Digit>
<MilliSeconds> ::= <Digit><Digit><Digit>
<Date> ::=
        <Year>-<Month>-<Day> |
        (+|-)<Number>(d|w|y) |
        never|
        today
<DateTime> ::=
        <Year>-<Month>-<Day>(<Space>|T)<Hour>:<Minute> |
        (+|-)<Number>(m|h|d|w|y) |
        never|
        now|today
<Time> ::=
        <Year>-<Month>-<Day>(<Space>|T)<Hour>:<Minute>:<Second>[.<MilliSeconds>](Z|(+|-(<Hour>:<Minute>))) |
        (+|-)<Number>(m|h|d|w|y) |
        never|
        now|today
<RegularExpression> ::= <String>
        See: https://docs.python.org/3/library/re.html
<ProjectID> ::= <String>
        Must match this Python Regular Expression: [a-z][a-z0-9-]{4,28}[a-z0-9]
<ServiceAccountName> ::= <String>
        Must match this Python Regular Expression: [a-z][a-z0-9-]{4,28}[a-z0-9]
<SiteName> ::= [a-z,0-9,-]+
<UniqueID> ::= id:<String>|uid:<String>
```
## Named items
```
<AccessToken> ::= <String>
<AlertID> ::= <String>
<APIScopeURL> ::= <String>
<APPID> ::= <String>
<ASPID> ::= <String>
<AssetTag> ::= <String>
<BrowserTokenPermanentID> ::= <String>
<BuildingID> ::= <String>|id:<String>
<CalendarACLScope> ::=
        <EmailAddress>|user:<EmailAddress>|group:<EmailAddress>|
        domain:<DomainName>)|domain|default
<CalendarItem> ::= <EmailAddress>|<String>
<GIGroupAlias> ::= <EmailAddress>|<String>
<GIGroupItem> ::= <EmailAddress>|<UniqueID>|groups/<String>
<CIGroupType> ::= customer|group|other|serviceaccount|user
<ChatMember> ::= spaces/<String>/members/<String>
<ChatMessage> ::= spaces/<String>/messages/<String>
<ChatSpace> ::= spaces/<String> | <String>
<ChatThread> ::= spaces/<String>/threads/<String>
<ClassroomInvitationID> ::= <String>
<ClientID> ::= <String>
<CommandID> ::= <String>
<ContactID> ::= <String>
<ContactGroupID> ::= id:<String>
<ContactGroupName> ::= <String>
<ContactGroupItem> ::= <ContactGroupID>|<ContactGroupName>
<CorporaAttribute> ::= alldrives|allteamdrives|domain|onlyteamdrives|user
<CourseAlias> ::= <String>
<CourseAnnouncementID> ::= <Number>
<CourseAnnouncementState> ::= draft|published|deleted
<CourseID> ::= <Number>|d:<CourseAlias>
<CourseMaterialID> ::= <Number>
<CourseMaterialState> ::= draft|published|deleted
<CourseParticipantType> ::= teacher|teachers|student|students
<CourseState> ::= active|archived|provisioned|declined|suspended
<CourseSubmissionID> ::= <Number>
<CourseSubmissionState> ::= new|created|turned_in|returned|reclaimed_by_student
<CourseTopic> ::= <String>
<CourseTopicID> ::= <Number>
<CourseWorkID> ::= <Number>
<CourseWorkState> ::= draft|published|deleted
<CrOSID> ::= <String>
<CustomerID> ::= <String>
<DataStudioAssetID> ::= <String>
<DataStudioPermission> ::=
        user:<EmailAddress>|
        group:<EmailAddress>|
        domain:<DomainName>|
        serviceAccount:<EmailAddress>
<DeliverySetting> ::=
        allmail|
        abridged|daily|
        digest|
        disabled|
        none|nomail
<DeviceID> ::= devices/<String>
<DeviceType> ::= android|chrome_os|google_sync|linux|mac_os|windows
<DeviceUserID> ::= devices/<String>/deviceUsers/<String>
<DomainAlias> ::= <String>
<DomainName> ::= <String>(.<String>)+
<DriveFileACLRole> ::=
        commenter|
        contentmanager|fileorganizer|
        contributor|editor|writer|
        manager|organizer|owner|
        reader|viewer
<DriveFileACLType> ::= anyone|domain|group|user
<DriveFileID> ::= <String>
<DriveFileURL> ::=
        https://drive.google.com/open?id=<DriveFileID>
        https://drive.google.com/drive/files/<DriveFileID>
        https://drive.google.com/drive/folders/<DriveFileID>
        https://drive.google.com/drive/folders/<DriveFileID>?resourcekey=<String>
        https://drive.google.com/file/d/<DriveFileID>/<String>
        https://docs.google.com>/document/d/<DriveFileID>/<String>
        https://docs.google.com>/drawings/d/<DriveFileID>/<String>
        https://docs.google.com>/forms/d/<DriveFileID>/<String>
        https://docs.google.com>/presentation/d/<DriveFileID>/<String>
        https://docs.google.com>/spreadsheets/d/<DriveFileID>/<String>
<DriveFileItem> ::= <DriveFileID>|<DriveFileURL>
<DriveFileName> ::= <String>
<DriveFolderID> ::= <String>
<DriveFolderName> ::= <String>
<DriveFilePermission> ::=
        anyone;<DriveFileACLRole>|
        anyonewithlink;<DriveFileACLRole>|
        domain:<DomainName>;<DriveFileACLRole>|
        domainwithlink:<DomainName>;<DriveFileACLRole>|
        group:<EmailAddress>;<DriveFileACLRole>|
        user:<EmailAddress>;<DriveFileACLRole>
<DriveFilePermissionID> ::= anyone|anyonewithlink|id:<String>
<DriveFilePermissionIDorEmail> ::= <DriveFilePermissionID>|<EmailAddress>
<DriveFileRevisionID> ::= <String>
<EmailAddress> ::= <String>@<DomainName>
<EmailItem> ::= <EmailAddress>|<UniqueID>|<String>
<EmailReplacement> ::= <String>
<EventID> ::= <String>
<EventName> ::= <String>
<ExportItem> ::= <UniqueID>|<String>
<ExportStatus> ::= completed|failed|inprogrsss
<FeatureName> ::= <String>
<FieldName> ::= <String>
<FileName> ::= <String>
<FileNamePattern> ::= <String>
<FilterID> ::= <String>
<FloorName> ::= <String>
<GroupItem> ::= <EmailAddress>|<UniqueID>|<String>
<GroupRole> ::= owner|manager|member
<GroupType> ::= customer|group|user
<GuardianItem> ::= <EmailAddress>|<UniqueID>|<String>
<GuardianInvitationID> ::= <String>
<HoldItem> ::= <UniqueID>|<String>
<HostName> ::= <String>
<iCalUID> ::= <String>
<JSONData> ::= <String>
<Key> ::= <String>
<LabelID> ::= Label_<String>
<LabelName> ::= <String>
<LabelReplacement> ::= <String>
<Marker> ::= <String>
<MatterItem> ::= <UniqueID>|<String>
<MatterState> ::= open|closed|deleted
<MaximumNumberOfSeats> ::= <Number>
<MessageID> ::= <String>
<Namespace> ::= <String>
<NotesName> ::= notes/<String>
<NumberOfSeats> ::= <Number>
<OrgUnitID> ::= id:<String>
<OrgUnitPath> ::= /|(/<String>)+
<OrgUnitItem> ::= <OrgUnitID>|<OrgUnitPath>
<OtherContactsResourceName> ::= otherContacts/<String>
<ParameterKey> ::= <String>
<ParameterValue> ::= <String>
<Password> ::= <String>
<PeopleResourceName> ::= people/<String>
<PrinterID> ::= <String>
<ProjectID> ::= <String>
        Must match this Python Regular Expression: [a-z][a-z0-9-]{4,28}[a-z0-9]
<ProjectName> ::= <String>
        Must match this Python Regular Expression: [a-zA-Z0-9 '"!-]{4,30}
<PropertyKey> ::= <String>
<PropertyValue> ::= <String>
<QueryAlert> ::= <String>
        See: https://developers.google.com/admin-sdk/alertcenter/guides/query-filters
<QueryBrowser> ::= <String>
        See: https://support.google.com/chrome/a/answer/9681204#retrieve_all_chrome_devices_for_an_account
<QueryBrowserToken> ::= <String>
        See: https://support.google.com/chrome/a/answer/9949706?ref_topic=9301744
<QueryCalendar> ::= <String>
<QueryContact> ::= <String>
        See: https://developers.google.com/google-apps/contacts/v3/reference#contacts-query-parameters-reference
<QueryCrOS> ::= <String>
        See: https://support.google.com/chrome/a/answer/1698333
<QueryDevice> ::= <String>
        See: https://support.google.com/a/answer/7549103
<QueryDriveFile> ::= <String>
        See: https://developers.google.com/drive/api/v3/search-files
<QueryDynamicGroup> ::= <String>
        See: https://cloud.google.com/identity/docs/reference/rest/v1/groups#dynamicgroupquery
<QueryGmail> ::= <String>
        See: https://support.google.com/mail/answer/7190
<QueryGroup> ::= <String>
        See: https://developers.google.com/admin-sdk/directory/v1/guides/search-groups
<QueryMemberRestrictions> ::= <String>
        See: https://cloud.google.com/identity/docs/reference/rest/v1beta1/SecuritySettings#MemberRestriction
<QueryMobile> ::= <String>
        See: https://support.google.com/a/answer/7549103
<QueryTeamDrive> ::= <String>
        See: https://developers.google.com/drive/api/v3/search-parameters
<QueryUser> ::= <String>
        See: https://developers.google.com/admin-sdk/directory/v1/guides/search-users
<QueryVaultCorpus> ::= <String>
        See: https://developers.google.com/vault/reference/rest/v1/matters.holds#CorpusQuery
<RequestID> ::= <String>
<ResourceID> ::= <String>
<SchemaName> ::= <String>
<Section> ::= <String>
<SerialNumber> ::= <String>
<ServiceAccountName> ::= <String>
        Must match this Python Regular Expression: [a-z][a-z0-9-]{4,28}[a-z0-9]
<ServiceAccountDisplayName> ::= <String>
        Maximum of 100 characters
<ServiceAccountDescrition> ::= <String>
       Maximumof 256 chcracters
<ServiceAccountEmail> ::= <ServiceAccountName>@<ProjectID>.iam.gserviceaccount.com
<ServiceAccountUniqueID> ::= <Number>
<ServiceAccountKey> ::= <String>
<SheetEntity> ::= <String>|id:<Number>
<SiteACLScope> ::=
        <EmailAddress>|user:<EmailAdress>|group:<EmailAddress>|
        domain:<DomainName>|domain|default
<SiteItem> ::= [<DomainName>/]<SiteName>
<S/MIMEID> ::= <String>
<SMTPHostName> ::= <String>
<StudentItem> ::= <EmailAddress>|<UniqueID>|<String>
<Tag> ::= <String>
<SharedDriveACLRole> ::=
        commenter|
        contentmanager|fileorganizer|
        contributor|editor|writer|
        manager|organizer|owner|
        reader|viewer
<SharedDriveID> ::= <String>
<SharedDriveName> ::= <String>
<ThreadID> ::= <String>
<TimeZone> ::= <String>
        See: https://en.wikipedia.org/wiki/List_of_tz_database_time_zones
<Title> ::= <String>
<ToDriveAttribute> ::=
        (tdaddsheet [<Boolean>])|
        (tdbackupsheet (id:<Number>)|<String>)|
        (tdclearfilter [<Boolean>])|
        (tdcopysheet (id:<Number>)|<String>)|
        (tddescription <String>)|
        (tdfileid <DriveFileID>)|
        (tdlocalcopy [<Boolean>])|
        (tdlocale <Locale>)|
        (tdnobrowser [<Boolean>])|
        (tdnoemail [<Boolean>])|
        (tdparent (id:<DriveFolderID>)|<DriveFolderName>)|
        (tdsheet (id:<Number>)|<String>)|
        (tdsheettimestamp [<Boolean>] [tdsheettimeformat <String>])
        ([tdsheetdaysoffset <Number>] [tdsheethoursoffset <Number])|
        (tdtimestamp [<Boolean>] [tdtimeformat <String>]
            [tddaysoffset <Number>] [tdhoursoffset <Number])|
        (tdtimezone <TimeZone>)|
        (tdtitle <String>)|
        (tdcellwrap clip|overflow|wrap)|
        (tdupdatesheet [<Boolean>])|
        (tduploadnodata [<Boolean>])|
        (tduser <EmailAddress>)
<TransferID> ::= <String>
<URI> ::= <String>
<URL> ::= <String>
<UserItem> ::= <EmailAddress>|<UniqueID>|<String>
<UserName> ::= <<String>
```

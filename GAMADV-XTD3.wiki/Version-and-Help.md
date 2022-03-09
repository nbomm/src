# Version and Help

Print the current version of Gam with details
```
gam version
GAMADV-XTD3 6.16.09 - https://github.com/taers232c/GAMADV-XTD3
Ross Scroggs <ross.scroggs@gmail.com>
Python 3.10.2 64-bit final
MacOS High Sierra 10.13.6 x86_64
Path: /Users/Admin/bin/gamadv-xtd3
Config File: /Users/admin/GAMConfig/gam.cfg, Section: DEFAULT, customer_id: my_customer, domain.com
```

Print the current version of Gam with details and time offset information
```
gam version timeoffset
GAMADV-XTD3 6.16.09 - https://github.com/taers232c/GAMADV-XTD3
Ross Scroggs <ross.scroggs@gmail.com>
Python 3.10.2 64-bit final
MacOS High Sierra 10.13.6 x86_64
Path: /Users/Admin/bin/gamadv-xtd3
Config File: /Users/admin/GAMConfig/gam.cfg, Section: DEFAULT, customer_id: my_customer, domain.com
Your system time differs from www.googleapis.com by less than 1 second
```

Print the current version of Gam with details and SSL information
```
gam version extended
GAMADV-XTD3 6.16.09 - https://github.com/taers232c/GAMADV-XTD3 - pythonsource
Ross Scroggs <ross.scroggs@gmail.com>
Python 3.10.2 64-bit final
MacOS High Sierra 10.13.6 x86_64
Path: /Users/Admin/bin/gamadv-xtd3
Config File: /Users/admin/GAMConfig/gam.cfg, Section: DEFAULT, customer_id: my_customer, domain.com
Your system time differs from admin.googleapis.com by less than 1 second
OpenSSL 1.1.1m  24 Aug 2021
cryptography 36.0.1
filelock 3.4.2
google-api-python-client 2.35.0
google-auth 2.3.3
google-auth-httplib2 0.1.0
google-auth-oauthlib 0.4.6
httplib2 0.20.2
passlib 1.7.4
python-dateutil 2.8.2
admin.googleapis.com connects using TLSv1.3 TLS_AES_256_GCM_SHA384###
Your system time differs from www.googleapis.com by less than 1 second
```

Print the current and latest versions of Gam and:
* set the return code to 0 if the current version is the latest version
* set the return code to 1 if the current version is not the latest
```
gam version checkrc
GAM 5.35.08 - https://github.com/taers232c/GAMADV-XTD3
Ross Scroggs <ross.scroggs@gmail.com>
Python 3.8.1 64-bit final
google-api-python-client 1.7.11
httplib2 0.16.0
oauth2client 4.1.3
MacOS High Sierra 10.13.6 x86_64
Path: /Users/Admin/bin/gamadv-xtd3
Version Check:
  Current: 5.35.08
   Latest: 6.16.09
echo $?
1
```

Print the current version number without details
```
gam version simple
6.16.09
```
In Linux/MacOS you can do:
```
VER=`gam version simple`
echo $VER
```
Print the current version of Gam and address of this Wiki
```
gam help
GAM 6.16.09 - https://github.com/taers232c/GAMADV-XTD3
Ross Scroggs <ross.scroggs@gmail.com>
Python 3.10.2 64-bit final
MacOS High Sierra 10.13.6 x86_64
Path: /Users/Admin/bin/gamadv-xtd3
Config File: /Users/admin/GAMConfig/gam.cfg, Section: DEFAULT, customer_id: my_customer, domain.com
Help: Syntax in file /Users/Admin/bin/gamadv-xtd3/GamCommands.txt
Help: Documentation is at https://github.com/taers232c/GAMADV-XTD3/wiki
```

# Install GAM as Python Library

Thanks to Jay Lee for showing me how to do this.

You can install GAM as a Python library with pip.
```
pip install git+https://github.com/taers232c/GAMADV-XTD3.git#subdirectory=src
```

```
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
""" Sample Python script to call GAM"""

import multiprocessing
import sys

import gam

if __name__ == '__main__':
# One time initialization
  if sys.platform == 'darwin':
    multiprocessing.set_start_method('fork')
  gam.initializeLogging()
#
  gam.CallGAMCommand(['gam', 'version'])
  gam.CallGAMCommand(['gam', 'info', 'domain'])
```
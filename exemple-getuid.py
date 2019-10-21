#! /usr/bin/env python3
from __future__ import print_function
import os
print("Real UID =", os.getuid(),
    " Effective UID=" os.geteuid())

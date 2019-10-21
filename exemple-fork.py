#! /usr/bin/env python3
from __future__ import print_function
import os

try:
    child_pid = os.fork()
except OSerror:
    print("Error in fork()")
    sys.exit(-1)
if (child_pid == 0):
    print("Child: PID =", os.getpid(),
            " PPID =", os.getpid())
else:
    print("Parent: PID =", os.getpid(),
            " PPID =", os.getpid(),
            " Child =", child_pid)
    os.wait()

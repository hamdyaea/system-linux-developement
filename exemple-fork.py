#!/usr/bin/env python3
# Developer: Hamdy Abou El Anein
# Contact: hamdy.aea@protonmail.com
# SPDX-License-Identifier: GPL-3.0-or-later
"""Demonstrate POSIX fork() with correct parent/child process IDs."""
import os
import sys


def main() -> int:
    if not hasattr(os, "fork"):
        print("fork() is not supported on this platform", file=sys.stderr)
        return 1
    sys.stdout.flush()
    try:
        pid = os.fork()
    except OSError as exc:
        print(f"fork failed: {exc}", file=sys.stderr)
        return 1
    if pid == 0:
        print(f"Child: PID={os.getpid()}, PPID={os.getppid()}", flush=True)
        os._exit(0)
    print(f"Parent: PID={os.getpid()}, child={pid}", flush=True)
    try:
        _, status = os.waitpid(pid, 0)
    except OSError as exc:
        print(f"waitpid failed: {exc}", file=sys.stderr)
        return 1
    return 0 if os.waitstatus_to_exitcode(status) == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
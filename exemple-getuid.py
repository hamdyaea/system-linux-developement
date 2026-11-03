#!/usr/bin/env python3
# Developer: Hamdy Abou El Anein
# Contact: hamdy.aea@protonmail.com
# SPDX-License-Identifier: GPL-3.0-or-later
"""Print the current process real and effective user IDs."""
import os


def main() -> None:
    print(f"Real UID={os.getuid()}, Effective UID={os.geteuid()}")


if __name__ == "__main__":
    main()
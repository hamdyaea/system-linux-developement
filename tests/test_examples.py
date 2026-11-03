#!/usr/bin/env python3
# Developer: Hamdy Abou El Anein
# Contact: hamdy.aea@protonmail.com
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compile/run POSIX examples without root, setuid bits or external hosts."""
from pathlib import Path
import re
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class LinuxExamplesTests(unittest.TestCase):
    def test_c_programs_compile_and_run(self):
        with tempfile.TemporaryDirectory() as directory:
            for name in ("exemple-fork", "exemple-getuid", "exemple-setuid"):
                with self.subTest(program=name):
                    binary = Path(directory) / name
                    subprocess.run(
                        ["cc", "-std=c11", "-D_POSIX_C_SOURCE=200809L",
                         "-Wall", "-Wextra", "-Werror", "-pedantic",
                         str(ROOT / (name + ".c")), "-o", str(binary)],
                        check=True, capture_output=True, text=True, timeout=30,
                    )
                    result = subprocess.run([str(binary)], capture_output=True,
                                            text=True, timeout=10)
                    self.assertEqual(result.returncode, 0, result.stderr)
                    if name == "exemple-fork":
                        self.assertIn("Child: PID=", result.stdout)
                        self.assertIn("Parent: PID=", result.stdout)
                    else:
                        self.assertIn("UID=", result.stdout)

    def test_python_programs_run(self):
        for name in ("exemple-fork.py", "exemple-getuid.py"):
            with self.subTest(program=name):
                result = subprocess.run([sys.executable, str(ROOT / name)],
                                        capture_output=True, text=True, timeout=10)
                self.assertEqual(result.returncode, 0, result.stderr)
                self.assertRegex(result.stdout, r"(?:PID|UID)=\d+")

    def test_source_has_no_privilege_restoration(self):
        source = (ROOT / "exemple-setuid.c").read_text()
        self.assertIn("setuid(real_uid)", source)
        self.assertNotIn("setuid(effective_uid)", source)


if __name__ == "__main__":
    unittest.main()
# Linux system programming examples

Developer: Hamdy Abou El Anein
Contact: hamdy.aea@protonmail.com
License: GNU GPL v3 (see LICENSE).

Small, educational POSIX/Linux examples demonstrating process creation and user IDs in **C and Python 3**.

## Programs

- `exemple-fork.c` and `exemple-fork.py`: fork a child, display correct process IDs, wait for the child and handle errors.
- `exemple-getuid.c` and `exemple-getuid.py`: display real and effective user IDs without changing privileges.
- `exemple-setuid.c`: demonstrate dropping to the real user ID using `setuid(getuid())`, with proper error checking. This program **must never be installed setuid-root**.

## Build and test on Linux

```sh
cc -std=c11 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Werror -pedantic exemple-fork.c -o /tmp/exemple-fork
cc -std=c11 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Werror -pedantic exemple-getuid.c -o /tmp/exemple-getuid
cc -std=c11 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Werror -pedantic exemple-setuid.c -o /tmp/exemple-setuid
python3 -m unittest discover -s tests -v
```

The test suite compiles C sources into an isolated temporary directory and executes all five examples as the current **unprivileged** user. No `sudo`, root privileges, networking or installation is required.

## Notes

These examples are for learning, not a privilege-escalation utility. The original `setuid` sample did not compile because it referenced undeclared variables. The previous `fork` example did not wait for the child. Both are corrected. Prebuilt executable files have been removed from the modern source branch because their provenance and architecture cannot be verified; they remain in the historical `old` branch.
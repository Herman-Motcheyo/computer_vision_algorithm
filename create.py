#!/usr/bin/env python3
"""
scaffold_tcvf.py
------------------
Creates the tcvf project directory structure with empty placeholder files.

Usage:
    python scaffold_tcvf.py                  # creates ./tcvf/
    python scaffold_tcvf.py --output /path   # creates /path/tcvf/
"""

import os
import argparse
from pathlib import Path

# ── ANSI colors ───────────────────────────────────────────────────────────────
GREEN  = "\033[92m"
CYAN   = "\033[96m"
YELLOW = "\033[93m"
BOLD   = "\033[1m"
RESET  = "\033[0m"

# ── Project structure definition ──────────────────────────────────────────────
# Each entry is either:
#   - a file path (str)       → created as an empty file
#   - a dir path ending "/"   → created as a directory (with .gitkeep)

STRUCTURE = [
    # ── Headers ──────────────────────────────────────────────────────────────
    "include/tcvf/common.h",
    "include/tcvf/image.h",
    "include/tcvf/intensity.h",
    "include/tcvf/geometry.h",
    "include/tcvf/filter.h",
    "include/tcvf/segment.h",
    "include/tcvf/edge.h",

    # ── Sources ───────────────────────────────────────────────────────────────
    "src/image.c",
    "src/intensity.c",
    "src/geometry.c",
    "src/filter.c",
    "src/segment.c",
    "src/edge.c",
    "src/cli/main.c",
    "src/cli/cli_intensity.c",
    "src/cli/cli_filter.c",
    "src/cli/cli_segment.c",
    "src/cli/cli_edge.c",

    # ── Tests ─────────────────────────────────────────────────────────────────
    "tests/fixtures/",
    "tests/test_image.c",
    "tests/test_intensity.c",
    "tests/test_filter.c",
    "tests/test_segment.c",
    "tests/test_edge.c",

    # ── Kernels ───────────────────────────────────────────────────────────────
    "kernels/",

    # ── Data ──────────────────────────────────────────────────────────────────
    "data/samples/",

    # ── Docs ──────────────────────────────────────────────────────────────────
    "docs/Doxyfile",
    "docs/paper/",
    "docs/algorithms/intensity.md",
    "docs/algorithms/geometry.md",
    "docs/algorithms/filter.md",
    "docs/algorithms/segment.md",
    "docs/algorithms/edge.md",

    # ── CI ────────────────────────────────────────────────────────────────────
    ".github/workflows/ci.yml",

    # ── Root files ────────────────────────────────────────────────────────────
    "CMakeLists.txt",
    "README.md",
    "CHANGELOG.md",
    "CONTRIBUTING.md",
    "LICENSE",
]


def create_structure(root: Path) -> None:
    files_created = 0
    dirs_created  = 0

    for entry in STRUCTURE:
        path = root / entry

        if entry.endswith("/"):
            # Directory: create it + add .gitkeep so git tracks it
            path.mkdir(parents=True, exist_ok=True)
            (path / ".gitkeep").touch()
            print(f"  {CYAN}DIR {RESET} {entry}")
            dirs_created += 1
        else:
            # File: create parent dirs then touch the file
            path.parent.mkdir(parents=True, exist_ok=True)
            path.touch()
            print(f"  {GREEN}FILE{RESET} {entry}")
            files_created += 1

    print()
    print(f"{BOLD}Done.{RESET}  "
          f"{GREEN}{files_created} files{RESET}  |  "
          f"{CYAN}{dirs_created} directories{RESET}  →  "
          f"{YELLOW}{root}{RESET}")


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Scaffold the tcvf project structure."
    )
    parser.add_argument(
        "--output", "-o",
        default=".",
        help="Parent directory where tcvf/ will be created (default: current directory)",
    )
    args = parser.parse_args()

    root = Path(args.output).resolve() / "tcvf"

    if root.exists():
        print(f"{YELLOW}Warning:{RESET} '{root}' already exists — files will be added/skipped.")
    else:
        root.mkdir(parents=True)

    print(f"\n{BOLD}Scaffolding tcvf →{RESET} {root}\n")
    create_structure(root)


if __name__ == "__main__":
    main()
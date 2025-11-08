# Repository Guidelines

This repo contains the ncurses-based `cspeedtest`; the notes below keep contributions shippable and easy to review.

## Project Structure & Module Organization
`src/` holds all C sources, grouped by responsibility (`cspeedtest.c` entry point, `curslib.*` for terminal helpers, `timecurses.*` for timing). Shell tests live in `test/`, `man/` stores the installed manual page, and `snapcraft.yaml` tracks packaging metadata. Autotools outputs (`configure`, `Makefile.in`, `aclocal.m4`) are generated—only edit `configure.ac` or `Makefile.am`, then regenerate via `./autogen`.

## Build, Test, and Development Commands
- `./autogen && ./configure --prefix=$PWD/build` regenerates the GNU build scripts and prepares an isolated install tree.
- `make -j$(nproc)` compiles the ncurses binary and linked helpers.
- `make check` executes the autotools-defined test targets; it invokes helper scripts plus the `cspeedtest -x` self-test flag.
- `./test/helptest.sh` or `./test/linktest.sh` can be run directly when iterating on CLI/help output.
- `snapcraft` (run from the repo root) produces the snap package using the included recipe.

## Coding Style & Naming Conventions
Follow the prevailing C99 style: three-space indentation, braces on the same line as control statements, and `snake_case` for functions or globals (`screen_table`, `print_options`). Keep macros uppercase (`GRAPH_N`), confine module-scoped state to `static` globals, and prefer helper functions inside `curslib.*` instead of duplicating curses calls.

## Testing Guidelines
Automated scripts expect `cspeedtest -x` to exit quickly once argument parsing succeeds; keep that behavior intact. Add new shell tests under `test/` with descriptive filenames and wire them into `Makefile.am` so `make check` picks them up. CLI or rendering changes should extend `helptest.sh` (options) or add a deterministic pattern script to guard regressions.

## Commit & Pull Request Guidelines
Git history favors short, imperative subjects such as `fix snapcraft.yaml`; match that style and keep body text for rationale or references. Each PR should describe the user-facing impact, list the exact commands used for verification (`make`, `make check`, ad-hoc scripts), and link any related issues. UI or rendering tweaks benefit from including a terminal capture so reviewers can validate color-mode changes without rebuilding locally.

## Security & Configuration Tips
Coordinate disclosure-sensitive fixes via the process in `SECURITY.md` before landing public patches, and avoid logging secrets when touching verbose/debug modes. Deploy `cspeedtest` under unprivileged accounts and document any site-specific `~/.config/termcap` requirements in the PR so operators can reproduce the environment.

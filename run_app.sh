#!/bin/bash
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

cd "$SCRIPT_DIR" || exit

x-terminal-emulator -e "./my_program"

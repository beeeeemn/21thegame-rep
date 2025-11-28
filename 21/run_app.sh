#!/bin/bash
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

cd "$SCRIPT_DIR" || exit

gnome-terminal -e "./my_program"

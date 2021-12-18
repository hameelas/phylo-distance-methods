#!/bin/bash

problem_name=PROBLEM_NAME_PLACE_HOLDER
main_file=MAIN_FILE_NAME_PLACE_HOLDER
shell_cmd=SHELL_CMD_PLACE_HOLDER
sandbox=$(dirname "$0")

"${shell_cmd}" "${sandbox}/${main_file}.sh" "$@"

#!/bin/sh

set -e

# Base variables
CFLAGS_LANGUAGE="-std=c99 -pedantic"
CFLAGS_OPTIMIZE="-O0 -g"
CFLAGS_WARNINGS="-Wall -Wextra -Wno-unused"
CFLAGS="${CFLAGS_LANGUAGE} ${CFLAGS_WARNINGS} ${CFLAGS_OPTIMIZE}"
LIBS=

# Get us some color
normal="$(tput sgr0)"
red="$(tput setaf 1)"
green="$(tput setaf 2)"

# newline
#
# Output a newline.
newline() {
  echo ""
}

# say [-ne] <msg>...
#
# Say MSG and reset tty attrs afterwards.
say() {
  echo "$@" "${normal}"
}

# fail <msg>
#
# Crash and burn.
fail() {
  say -n "\n${red}Error"
  echo ":" $@
  exit 1
}

# log <cmd>...
#
# Log and execute command
log() {
  echo $@
  $@
}

# verbose <cmd>...
#
# Run command verbosely.
verbose() {
    say "[exec] $*"
    "$@"
    local rc=$?
    if [ ${rc} -ne 0 ]; then
	say "\n[${red}FAIL${normal}] [rc=${rc}]"
    fi
    return ${rc}
}

newline

for file in bin2brl brl2bin; do
    verbose gcc $CFLAGS -o "${file}" "${file}.c"
done

newline

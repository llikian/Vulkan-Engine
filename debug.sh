#!/bin/bash

RED="\e[0;31m"
NO_COLOR="\e[0m"

cmake -B ./build -DCMAKE_BUILD_TYPE=Debug && cmake --build build -j
if [[ ! $? -eq 0 ]] ; then
  echo -e "${RED}Compilation Failed.${NO_COLOR}" 1>&2
  exit 1
fi

mkdir -p bin
BINARIES_COUNT="$(ls bin -1 | wc -l)"

if [[ $BINARIES_COUNT -gt 0 ]] ; then
  if [[ $BINARIES_COUNT -gt 1 ]] ; then
    if [[ $# -eq 0 ]] ; then
      echo -e "${RED}Multiple binary files found. Please provide filename.${NO_COLOR}" 1>&2
      exit 1
    else
      BINARY_FILENAME="$1"
    fi
  else
    BINARY_FILENAME="$(ls bin)"
  fi

  echo -e "\nExecuting program '${BINARY_FILENAME}':\n"
  "bin/$BINARY_FILENAME"
  echo -e "\nProgram exited with code $?\n"
else
  echo -e "${RED}Couldn't execute binary.${NO_COLOR}" 1>&2
  exit 1
fi

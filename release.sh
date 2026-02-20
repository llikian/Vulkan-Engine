#!/bin/bash

RED="\e[0;31m"
NO_COLOR="\e[0m"

cmake -B ./build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j

BINARIES_COUNT="$(ls bin -1 | wc -l)"

if [[ $? -eq 0 || $BINARIES_COUNT -gt 0 ]] ; then
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
  echo "${RED}Couldn't execute binary.${NO_COLOR}" 1>&2
  exit 1
fi

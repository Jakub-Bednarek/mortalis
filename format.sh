#! /bin/bash

MORTALIS_SOURCE_DIR=$(pwd)/Source/Mortalis

FILES=$(find $MORTALIS_SOURCE_DIR -type f -regex ".*\.[h|cpp]")

for FILE in $FILES; do clang-format -i $FILE; done

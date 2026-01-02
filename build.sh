#!/usr/bin/env bash
echo "Building Program..."
SOURCE_FILES=$(find source -name "*.c")
echo "Files included:"
echo $SOURCE_FILES
if gcc -Wall -Wextra -Wpedantic -Werror -fsanitize=address -g \
  $SOURCE_FILES -o myprogram; then
  echo "Program Built and Running..."
  echo "============================"
  ./myprogram
else
  echo "XXXXXXXXXX Error Building Program XXXXXXXXXX"
fi

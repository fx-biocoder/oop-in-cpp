#!/bin/bash

# Quick compile script for individual files with g++ (C++17)
# Usage: ./compile.sh <file.cpp>

if [ $# -eq 0 ]; then
    echo "Usage: ./compile.sh <file.cpp>"
    echo ""
    echo "Examples:"
    echo "  ./compile.sh ../examples/01-abstraction/01_basic_class.cpp"
    echo "  ./compile.sh ../examples/02-encapsulation/01_bank_account.cpp"
    exit 1
fi

FILE="$1"
FILENAME=$(basename "$FILE" .cpp)

echo "Compiling $FILE..."

g++ -std=c++17 -Wall -Wextra -O2 -o "$FILENAME" "$FILE"

if [ $? -eq 0 ]; then
    echo "✓ Compiled successfully: $FILENAME"
    echo "Run with: ./$FILENAME"
else
    echo "✗ Compilation failed!"
    exit 1
fi

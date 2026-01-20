#!/bin/bash

# Script to compile all examples with GCC (C++17)

echo "Building OOP in C++ examples with GCC..."
echo "=========================================="

# Directories
BUILD_DIR="build"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Create build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Run CMake
echo "Running CMake..."
cmake -DCMAKE_CXX_STANDARD=17 -DCMAKE_CXX_COMPILER=g++ ..

# Build
echo "Building..."
make

if [ $? -eq 0 ]; then
    echo ""
    echo "✓ Build successful!"
    echo ""
    echo "Run examples with:"
    echo "  ./abstraction_01_basic"
    echo "  ./abstraction_02_attributes"
    echo "  ./abstraction_03_abstract"
    echo "  ./encapsulation_01_bank"
    echo "  ./encapsulation_02_access"
    echo "  ./inheritance_01_basic"
    echo "  ./inheritance_02_virtual"
    echo "  ./inheritance_03_abstract"
    echo "  ./polymorphism_01_animals"
    echo "  ./polymorphism_02_payment"
    echo "  ./polymorphism_03_vtables"
else
    echo "✗ Build failed!"
    exit 1
fi

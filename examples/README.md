# Compilable Examples

This directory contains fully compilable, runnable examples for all OOP concepts covered in this guide.

## Quick Start

### Using CMake (Recommended)

```bash
# From the project root directory
./scripts/build.sh
cd build

# Run an example
./abstraction_01_basic
./polymorphism_01_animals
# ... etc
```

### Quick Compilation with GCC

```bash
# Compile and run a single file
g++ -std=c++17 -Wall -Wextra examples/01-abstraction/01_basic_class.cpp -o demo
./demo
```

### Using the Compilation Script

```bash
cd scripts
chmod +x compile.sh
./compile.sh ../examples/01-abstraction/01_basic_class.cpp
./01_basic_class
```

## Examples Overview

### Abstraction (01-abstraction/)

1. **01_basic_class.cpp** - Basic class with public/private members
   - Demonstrates abstraction and interface design
   - Run: `./abstraction_01_basic`

2. **02_attributes_and_methods.cpp** - Car class with attributes and methods
   - Shows const-correctness and method types
   - Run: `./abstraction_02_attributes`

3. **03_abstract_classes.cpp** - Abstract shape classes with virtual functions
   - Demonstrates abstract classes and polymorphism
   - Run: `./abstraction_03_abstract`

### Encapsulation (02-encapsulation/)

1. **01_bank_account.cpp** - Bank account with proper encapsulation
   - Private members with public interface
   - Validation and transaction history
   - Run: `./encapsulation_01_bank`

2. **02_access_modifiers.cpp** - Demonstrates public, protected, private access
   - Shows how access modifiers work with inheritance
   - Run: `./encapsulation_02_access`

### Inheritance (03-inheritance/)

1. **01_basic_inheritance.cpp** - Vehicle, Car, and Motorcycle classes
   - Shows base class initialization and method inheritance
   - Run: `./inheritance_01_basic`

2. **02_virtual_functions.cpp** - Demonstrates virtual functions and override
   - Shows virtual, pure virtual, and non-virtual methods
   - Run: `./inheritance_02_virtual`

3. **03_abstract_classes.cpp** - Employee hierarchy with abstract base class
   - Abstract base class with multiple derived classes
   - Run: `./inheritance_03_abstract`

### Polymorphism (04-polymorphism/)

1. **01_animal_example.cpp** - Animals making different sounds
   - Classic polymorphism example
   - Run: `./polymorphism_01_animals`

2. **02_payment_processors.cpp** - Payment processing system
   - Real-world polymorphism pattern
   - Credit card, PayPal, Apple Pay processors
   - Run: `./polymorphism_02_payment`

3. **03_vtable_explanation.cpp** - Understanding virtual tables
   - Explains how virtual function dispatch works
   - Run: `./polymorphism_03_vtables`

## Compiling Requirements

- **C++ Standard:** C++17 minimum (C++20 recommended)
- **Compilers Tested:**
  - GCC 7+
  - Clang 5+
  - MSVC 2017+
- **Build System:** CMake 3.15+

## Compiler Flags Used

```bash
-std=c++17          # Use C++17 standard
-Wall -Wextra       # Enable all warnings
-Wpedantic          # Strict standard compliance
-O2                 # Optimize for performance
```

## What You'll Learn

Running these examples will help you understand:

✅ **Abstraction** - How to hide complexity behind clean interfaces  
✅ **Encapsulation** - How to protect data and control access  
✅ **Inheritance** - How to reuse code through class hierarchies  
✅ **Polymorphism** - How to write flexible code that works with multiple types  
✅ **Smart Pointers** - Modern memory management techniques  
✅ **Virtual Functions** - Runtime polymorphic behavior  
✅ **Const-Correctness** - Making intentions explicit to the compiler  

---

**Happy Learning!** These examples are designed to be educational and compile cleanly with modern C++ compilers. If you find any issues, please report them!

Licensed under CC BY-NC-SA 4.0

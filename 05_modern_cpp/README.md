# Modern C++ Overview (C++17/20)

## Introduction

This guide focuses on **modern C++ standards (C++17 and C++20)**, which have introduced significant improvements to memory management, type safety, and expressiveness. This document provides a quick reference for the key features you'll encounter throughout this OOP guide.

## Key Features Used in This Guide

### 1. Smart Pointers (C++11+)

Smart pointers help manage **ownership and lifetime** of dynamically allocated objects, reducing the need for manual `new`/`delete`.

```cpp
#include <memory>

// Unique pointer: exclusive ownership
std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>();

// Shared pointer: shared ownership with reference counting
std::shared_ptr<MyClass> ptr2 = std::make_shared<MyClass>();
```

**Why they matter:** Reduce memory leaks and make ownership semantics explicit.

### 2. Move Semantics (C++11+)

Enables efficient transfer of resources without copying.

```cpp
class MyClass {
public:
    // Move constructor
    MyClass(MyClass&& other) noexcept 
        : data(std::move(other.data)) {}
    
    // Move assignment operator
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }
private:
    std::vector<int> data;
};
```

**Why it matters:** Improves performance by avoiding unnecessary copies.

### 3. Const-Correctness

Declares intent and allows compiler to enforce correctness.

```cpp
class MyClass {
public:
    // const method: cannot modify member variables
    int getValue() const { return value; }
    
    // const reference parameter: won't modify the argument
    void process(const std::string& input) { /* ... */ }
private:
    int value;
};
```

**Why it matters:** Catches bugs at compile-time and makes code intentions clear.

### 4. RAII (Resource Acquisition Is Initialization)

Resources are acquired in constructor and released in destructor.

```cpp
class FileHandler {
public:
    explicit FileHandler(const std::string& filename)
        : file(filename) {}

private:
    std::ifstream file;  // Automatically closed by destructor
};

```

**Why it matters:** Guarantees cleanup even if exceptions occur.

### 5. Structured Bindings (C++17)

Unpack values from pairs, tuples, and aggregate types.

```cpp
auto [name, age] = getPerson();

for (auto& [key, value] : map) {
    std::cout << key << ": " << value << std::endl;
}

```

**Why it matters:** More readable and less error-prone code.

### 6. `override` and `final` Keywords (C++11+)

Explicitly mark virtual function overrides and prevent further overriding.

```cpp
class Base {
public:
    virtual void method() = 0;
};

class Derived : public Base {
public:
    void method() override {  // Error if method doesn't exist in Base
        // Implementation
    }
};

class Final : public Derived {
public:
    void method() final {  // Prevents further overriding
        // Implementation
    }
};
```

**Why it matters:** Compiler catches signature mistakes and prevents accidental overrides.

### 7. Default Member Initializers (C++11+)

Initialize members at declaration time.

```cpp
class MyClass {
private:
    int count = 0;               
    std::string name = "default";
    std::vector<int> items;      
};
```

**Why it matters:** Ensures predictable initialization.

### 8. `= default` and `= delete` (C++11+)

Explicitly request or forbid compiler-generated methods.

```cpp
class Copyable {
public:
    Copyable(const Copyable&) = default;
    Copyable& operator=(const Copyable&) = default;
};

class NonCopyable {
public:
    // Prevent copying
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};
```

**Why it matters:** Makes class semantics explicit.

### 9. `noexcept` Specification (C++11+)

Declares that a function doesn't throw exceptions.

```cpp
class MyClass {
public:
    // Promises this function won't throw
    void swap(MyClass& other) noexcept {
        std::swap(data, other.data);
    }
private:
    std::vector<int> data;
};
```

**Why it matters:** Enables optimizations and improves correctness guarantees.

### 10. Namespaces and Header Organization

Organize code logically and prevent naming conflicts.

```cpp
// MyLib/MyClass.h
#ifndef MYLIB_MYCLASS_H
#define MYLIB_MYCLASS_H

namespace mylib {
    class MyClass {
    public:
        MyClass();
        ~MyClass();
    };
}

#endif
```

**Why it matters:** Professional code organization and maintainability.

### 11. Standard Library Containers

Prefer standard containers over raw arrays.

```cpp
#include <vector>
#include <string>
#include <map>

std::vector<int> numbers = {1, 2, 3, 4, 5};
std::string name = "John";
std::map<std::string, int> ages = {{"Alice", 30}, {"Bob", 25}};
```

**Why it matters:** Type-safe, feature-rich, and well-tested.

### 12. Range-Based For Loop (C++11+)

Iterate over containers more readably.

```cpp
for (int num : numbers) {
    std::cout << num << std::endl;
}

for (auto& person : people) {
    person.updateAge();
}

```

**Why it matters:** Improves clarity and reduces indexing errors.

## Building and Compiling

### Compilation Examples

```bash
# With GCC (C++17)
g++ -std=c++17 -Wall -Wextra myfile.cpp -o myfile

# With GCC (C++20)
g++ -std=c++20 -Wall -Wextra myfile.cpp -o myfile

# With CMake
mkdir build && cd build
cmake -DCMAKE_CXX_STANDARD=17 ..
make
```

### Recommended Compiler Flags

```bash
# Enable all warnings and treat as errors
-Wall -Wextra -Werror

# Enable optimization
-O3

# Enable debugging symbols
-g

# Combined example
g++ -std=c++20 -Wall -Wextra -O3 -g myfile.cpp -o myfile
```

## Common Pitfalls to Avoid

### 1. Owning Raw Pointers

❌ **Bad:**
```cpp
void function() {
    int* ptr = new int(42);
    // ... code ...
    delete ptr;  // Easy to forget!
}
```

✅ **Good:**
```cpp
void function() {
    auto ptr = std::make_unique<int>(42);
}
```

### 2. Not Using const

❌ **Bad:**
```cpp
void processData(std::string input) {
    // Can accidentally modify input
}
```

✅ **Good:**
```cpp
void processData(const std::string& input) {
    // Cannot modify input
}
```

### 3. Owning Resources Manually

❌ **Bad:**
```cpp
class MyClass {
    ~MyClass() {
        delete ptr;  // Prone to errors
    }
    int* ptr;
};
```

✅ **Good:**
```cpp
class MyClass {
    std::unique_ptr<int> ptr;
};
```

### 4. Forgetting `override`

❌ **Bad:**
```cpp
class Derived : public Base {
    void method() {  // Did this override Base::method()?
        // Implementation
    }
};
```

✅ **Good:**
```cpp
class Derived : public Base {
    void method() override {  // Error if method doesn't exist in Base
        // Implementation
    }
};
```
---

**Article Updated:** January 2026 | Licensed under CC BY-NC-SA 4.0
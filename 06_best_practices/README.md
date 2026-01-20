# Best Practices Guide for Modern C++ OOP

## Table of Contents

1. [Class Design](#class-design)
2. [Memory Management](#memory-management)
3. [Inheritance Guidelines](#inheritance-guidelines)
4. [Polymorphism Best Practices](#polymorphism-best-practices)
5. [Code Organization](#code-organization)
6. [Performance Considerations](#performance-considerations)
7. [Encapsulation](#encapsulation)

---

## Class Design

### The Rule of Five (or Zero)

In modern C++, if you define any of the following, define all five:

- Destructor
- Copy constructor
- Copy assignment operator
- Move constructor
- Move assignment operator

**Or use the "Rule of Zero":** Prefer designs where you define none of these. If your class only owns well-behaved RAII members, let the compiler generate everything.

```cpp
// Rule of Zero: Let compiler handle everything
class SimpleClass {
private:
    std::string name;
    std::vector<int> data;
    // No explicit constructor/destructor needed
};

// Rule of Five: When you need custom behavior
class ResourceOwner {
public:
    explicit ResourceOwner(const std::string& filename);
    ~ResourceOwner() = default;

    ResourceOwner(const ResourceOwner&) = delete;
    ResourceOwner& operator=(const ResourceOwner&) = delete;

    ResourceOwner(ResourceOwner&&) noexcept = default;
    ResourceOwner& operator=(ResourceOwner&&) noexcept = default;

private:
    std::unique_ptr<std::ofstream> file;
};
```

### Constructor Patterns

**Prefer member initializer lists:**

```cpp
// Good: Efficient initialization
class Person {
public:
    Person(const std::string& name, int age, const std::string& email)
        : name(name), age(age), email(email) {}
private:
    std::string name;
    int age;
    std::string email;
};

// Bad: Inefficient, members initialized twice
class Person {
public:
    Person(const std::string& name, int age, const std::string& email) {
        this->name = name;
        this->age = age;
        this->email = email;
    }
private:
    std::string name;
    int age;
    std::string email;
};
```

**Use in-class initializers for default values:**

```cpp
class Configuration {
private:
    int timeout = 5000;              // Default value
    bool debug = false;              // Default value
    std::string logFile = "app.log"; // Default value
};
```

**Prefer `= default` and `= delete`:**

```cpp
class NonCopyable {
public:
    NonCopyable() = default;
    ~NonCopyable() = default;
    
    // Explicitly delete copy operations
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    
    // Allow move operations
    NonCopyable(NonCopyable&&) = default;
    NonCopyable& operator=(NonCopyable&&) = default;
};
```

---

## Memory Management

### Prefer RAII and Value Semantics

Do not allocate dynamically unless ownership or lifetime requires it.

**Use `std::unique_ptr` for exclusive ownership:**

```cpp
class Application {
private:
    std::unique_ptr<Database> db;
    std::unique_ptr<Logger> logger;

public:
    Application()
        : db(std::make_unique<Database>()),
          logger(std::make_unique<Logger>()) {}
};

```

**Use `std::shared_ptr` only when shared ownership is semantically required:**

```cpp
class EventHandler {
private:
    std::shared_ptr<EventBus> bus;

public:
    explicit EventHandler(std::shared_ptr<EventBus> bus)
        : bus(std::move(bus)) {}
};

```

**For non-owning access, use references or clearly documented raw pointers:**

```cpp
class Observer {
public:
    void onEvent(Model& model);   // preferred when non-null is guaranteed
};

```

### RAII (Resource Acquisition Is Initialization)

Tie resource lifetime to object lifetime and rely on destructors:

```cpp
class FileReader {
public:
    explicit FileReader(const std::string& filename)
        : file(filename)
    {
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file");
        }
    }

    std::string readLine() {
        std::string line;
        std::getline(file, line);
        return line;
    }

private:
    std::ifstream file; // closes automatically
};

```

---

## Inheritance Guidelines

### Prefer Composition Over Inheritance

**Inheritance** models "is-a" relationships (strong coupling):

```cpp
class Animal {
public:
    virtual ~Animal() = default;
    virtual void makeSound() const = 0;
};

class Dog final : public Animal {
public:
    void makeSound() const override { std::cout << "Woof\n"; }
};

```

**Composition** models "has-a" relationships (loose coupling):

```cpp
// Better for capabilities
class Engine {
public:
    void start() { /* ... */ }
};

class Car {
private:
    Engine engine;  // Composition
public:
    void drive() {
        engine.start();
        // ...
    }
};
```

### Virtual Destructors

A base class **must** have a virtual destructor if objects are deleted through base-class pointers.

```cpp
class BaseClass {
public:
    virtual ~BaseClass() = default;  // REQUIRED for polymorphic classes
};

class DerivedClass : public BaseClass {
public:
    ~DerivedClass() override { /* cleanup */ }
};
```

If the class is not used polymorphically, a virtual destructor is unnecessary.

### Use `override` and `final`

```cpp
class Base {
public:
    virtual void method() {}
    virtual void locked() final {}
};

class Derived : public Base {
public:
    void method() override {}
};

```

---

## Polymorphism Best Practices

Use abstract base classes to define interfaces:

```cpp
class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};
```

Virtual dispatch has a small but real cost and prevents inlining. This is acceptable in most designs but should be considered in performance-critical code.

Use base-class references or pointers when polymorphism is required:

```cpp
void printArea(const Shape& shape) {
    std::cout << shape.area();
}

```

Using a derived type directly is not "wrong"; it simply does not use polymorphism.

---

## Code Organization

### Header and Implementation Separation

**MyClass.h** (Header file):

```cpp
#ifndef MYLIB_MYCLASS_H
#define MYLIB_MYCLASS_H

#include <string>

namespace mylib {
    class MyClass {
    public:
        MyClass(const std::string& name);
        ~MyClass();
        
        void doSomething();
        const std::string& getName() const;
        
    private:
        std::string name;
        int internalState = 0;
    };
}

#endif
```

**MyClass.cpp** (Implementation file):

```cpp
#include "MyClass.h"

namespace mylib {
    MyClass::MyClass(const std::string& name) : name(name) {}
    
    MyClass::~MyClass() {}
    
    void MyClass::doSomething() {
        // Implementation
    }
    
    const std::string& MyClass::getName() const {
        return name;
    }
}
```

### Include Guards and Forward Declarations

```cpp
#ifndef MYLIB_MYCLASS_H
#define MYLIB_MYCLASS_H

class Logger;
class Database;

class Application {
private:
    std::unique_ptr<Logger> logger;
    std::unique_ptr<Database> database;
};

#endif
```

---

## Performance Considerations

### Const-Correctness

```cpp
class DataProcessor {
public:
    // Mark getters as const
    int getValue() const { return value; }
    
    // Use const references for read-only parameters
    void process(const std::vector<int>& data) { /* ... */ }
    
    // Return const references when possible
    const std::string& getStatus() const { return status; }
    
private:
    int value = 0;
    std::string status = "ready";
};
```

### Avoid Unnecessary Copies

```cpp
// Bad: Copies the entire vector
void processData(std::vector<int> data) { /* ... */ }

// Good: Uses reference, no copy
void processData(const std::vector<int>& data) { /* ... */ }

// Good: Takes ownership with move
void processData(std::vector<int>&& data) { /* ... */ }
```

### Use `noexcept` for Optimization

```cpp
class MovableClass {
public:
    // Mark move operations as noexcept for optimization
    MovableClass(MovableClass&&) noexcept;
    MovableClass& operator=(MovableClass&&) noexcept;
    
    // Swap operations should not throw
    void swap(MovableClass& other) noexcept;
};
```

---

## Encapsulation

Keep data private and expose behavior through valid interfaces:

```cpp
class BankAccount {
public:
    void deposit(double amount);
    bool withdraw(double amount);
    double balance() const;

private:
    double currentBalance = 0.0;
};

```

Getters and setters are acceptable when they enforce invariants rather than merely exposing data.

---

**Article Updated:** January 2026 | Licensed under CC BY-NC-SA 4.0
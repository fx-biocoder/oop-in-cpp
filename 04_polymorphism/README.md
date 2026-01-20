# Polymorphism

## 1. Introduction

Polymorphism means "many forms." In C++, it allows objects of different derived classes to be treated through a common base class interface. This is one of the most powerful features of OOP.

**Two types of polymorphism:**

1. **Compile-time (Static) Polymorphism:**
   - Function overloading
   - Operator overloading
   - Template specialization
   - Resolved at compilation

2. **Runtime (Dynamic) Polymorphism:**
   - Virtual functions
   - Virtual pointers/references
   - Resolved at runtime through virtual tables (vtables)
   - More flexible but slightly more overhead

This guide focuses on **runtime polymorphism**, the most important type for OOP.

## 2. Virtual Functions and Runtime Polymorphism

Virtual functions enable runtime polymorphism. When you call a virtual function through a base class pointer or reference, the correct derived class implementation is called:

```cpp
#include <iostream>
#include <memory>
#include <vector>

// Base class with virtual functions
class Animal {
public:
    virtual ~Animal() = default;  // Virtual destructor
    
    // Virtual function - can be overridden
    virtual void makeSound() const {
        std::cout << "Generic animal sound\n";
    }
    
    // Virtual function with no default implementation
    virtual void describe() const = 0;
    
    // Non-virtual function - always same behavior
    void sleep() const {
        std::cout << "Zzzzz...\n";
    }
};

class Dog : public Animal {
private:
    std::string breed;
    
public:
    Dog(const std::string& breed) : breed(breed) {}
    
    void makeSound() const override {
        std::cout << "Woof! Woof!\n";
    }
    
    void describe() const override {
        std::cout << "I am a " << breed << " dog\n";
    }
};

class Cat : public Animal {
private:
    std::string color;
    
public:
    Cat(const std::string& color) : color(color) {}
    
    void makeSound() const override {
        std::cout << "Meow! Meow!\n";
    }
    
    void describe() const override {
        std::cout << "I am a " << color << " cat\n";
    }
};

class Bird : public Animal {
private:
    std::string species;
    
public:
    Bird(const std::string& species) : species(species) {}
    
    void makeSound() const override {
        std::cout << "Tweet! Tweet!\n";
    }
    
    void describe() const override {
        std::cout << "I am a " << species << "\n";
    }
};

int main() {
    // Store different animals in a vector
    std::vector<std::unique_ptr<Animal>> animals;
    
    animals.push_back(std::make_unique<Dog>("Golden Retriever"));
    animals.push_back(std::make_unique<Cat>("Orange"));
    animals.push_back(std::make_unique<Bird>("Parrot"));
    
    // Polymorphic behavior: same code, different results
    std::cout << "=== Making sounds ===\n";
    for (const auto& animal : animals) {
        animal->makeSound();  // Calls correct derived class method
    }
    
    std::cout << "\n=== Describing ===\n";
    for (const auto& animal : animals) {
        animal->describe();  // Calls correct derived class method
    }
    
    std::cout << "\n=== Sleeping ===\n";
    for (const auto& animal : animals) {
        animal->sleep();  // Same for all (non-virtual)
    }
    
    return 0;
}
```

**Output:**
```
=== Making sounds ===
Woof! Woof!
Meow! Meow!
Tweet! Tweet!

=== Describing ===
I am a Golden Retriever
I am a Orange cat
I am a Parrot

=== Sleeping ===
Zzzzz...
Zzzzz...
Zzzzz...
```

**Key points:**
- The **same code** in the loop calls **different implementations**
- This is the power of polymorphism
- Virtual functions enable this through dynamic dispatch
- Non-virtual functions (`sleep()`) have the same behavior everywhere

## 3. Polymorphism Through Base Class Interfaces

The power of polymorphism comes from using base class pointers/references:

```cpp
#include <iostream>
#include <memory>

class PaymentProcessor {
public:
    virtual ~PaymentProcessor() = default;
    virtual bool process(double amount) = 0;
    virtual void refund(double amount) = 0;
};

class CreditCardProcessor : public PaymentProcessor {
public:
    bool process(double amount) override {
        std::cout << "Processing $" << amount << " via credit card\n";
        return true;
    }
    
    void refund(double amount) override {
        std::cout << "Refunding $" << amount << " to credit card\n";
    }
};

class PayPalProcessor : public PaymentProcessor {
public:
    bool process(double amount) override {
        std::cout << "Processing $" << amount << " via PayPal\n";
        return true;
    }
    
    void refund(double amount) override {
        std::cout << "Refunding $" << amount << " to PayPal account\n";
    }
};

class CryptoCurrencyProcessor : public PaymentProcessor {
public:
    bool process(double amount) override {
        std::cout << "Processing $" << amount << " via Bitcoin\n";
        return true;
    }
    
    void refund(double amount) override {
        std::cout << "Refunding $" << amount << " to wallet\n";
    }
};

// Function that works with ANY payment processor
void checkoutOrder(PaymentProcessor& processor, double total) {
    std::cout << "\nProcessing order of $" << total << "\n";
    if (processor.process(total)) {
        std::cout << "Order successful!\n";
    } else {
        std::cout << "Payment failed\n";
    }
}

int main() {
    double orderTotal = 99.99;
    
    // Create different processors
    CreditCardProcessor cc;
    PayPalProcessor paypal;
    CryptoCurrencyProcessor crypto;
    
    // Same function, different behavior
    checkoutOrder(cc, orderTotal);
    checkoutOrder(paypal, orderTotal);
    checkoutOrder(crypto, orderTotal);
    
    // Polymorphism with pointers (useful in real systems)
    std::unique_ptr<PaymentProcessor> processor;
    
    processor = std::make_unique<CreditCardProcessor>();
    processor->process(50.0);
    
    processor = std::make_unique<PayPalProcessor>();
    processor->process(50.0);
    
    return 0;
}
```

**Output:**
```
Processing order of $99.99
Processing $99.99 via credit card
Order successful!

Processing order of $99.99
Processing $99.99 via PayPal
Order successful!

Processing order of $99.99
Processing $99.99 via Bitcoin
Order successful!

Processing $50 via credit card
Processing $50 via PayPal
```

This demonstrates the key benefit: **The checkout function doesn't need to know about specific processor types**. Any new processor can be added without changing the checkout code!

## 4. Virtual Tables (vtables)

Virtual tables are the mechanism C++ uses to implement dynamic polymorphism at runtime.

### How vtables Work

When a class has virtual functions, the compiler:

1. Creates a virtual table (vtable) for that class
2. Stores it as static data
3. Adds a hidden pointer (vpointer) to each object

```cpp
// This class will have a vtable
class Base {
public:
    virtual ~Base() = default;
    virtual void method1() {}
    virtual void method2() {}
};

// At compile time, this is created:
// 
// Base::vtable
// ├── &Base::~Base
// ├── &Base::method1
// └── &Base::method2

class Derived : public Base {
public:
    void method1() override {}  // Replaces Base::method1
    // method2() uses Base::method2
};

// Derived::vtable
// ├── &Derived::~Derived  (new implementation)
// ├── &Derived::method1   (overridden)
// └── &Base::method2      (inherited)
```

### Virtual Function Call Overhead

Virtual function calls have minimal overhead - just one extra indirection:

```
Direct call:        call func_address
Virtual call:       call *obj.vpointer[index]
```

Modern CPUs handle this very efficiently through:
- Branch prediction
- Instruction caches
- CPU speculation

### Practical Example

```cpp
#include <iostream>
#include <typeinfo>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing circle\n";
    }
};

int main() {
    Circle c;
    Shape* s = &c;
    
    // Virtual function call: 
    // 1. Follow object's vpointer to Circle::vtable
    // 2. Find draw() in the table
    // 3. Call Circle::draw()
    s->draw();
    
    return 0;
}
```

**Key points:**
- ✅ Virtual calls are resolved at runtime
- ✅ Overhead is typically negligible
- ✅ Enables polymorphic behavior
- ❌ Cannot be inlined across translation units
- ❌ Requires virtual destructor in base classes


---

**Article Updated:** January 2026 | Licensed under CC BY-NC-SA 4.0

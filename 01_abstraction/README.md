# Abstraction

## 1. Introduction

In Object-Oriented Programming, abstraction can be defined as the process of exposing only the essential characteristics of an object while hiding its internal implementation details. This allows us to interact with complex systems in a simplified way.

**Key principle:** Hide complexity, expose only what matters.

For example, driving a car illustrates abstraction perfectly:

1. You interact with a steering wheel, pedals, and a gearshift (the interface)
2. You don't need to understand the fuel injection system, transmission mechanics, or electrical circuitry
3. The car encapsulates all this complexity internally

As a driver, you only need to know **what** the car does, not **how** it does it. This is abstraction.

## Benefits of Abstraction

- **Simplicity:** Users interact with simple interfaces, not complex internals
- **Maintainability:** Implementation can change without affecting users
- **Reliability:** Reduces errors by limiting what users can do
- **Scalability:** Complex systems become manageable through layered abstractions

## 2. Classes and Objects in Modern C++

A **class** is a blueprint that defines the structure and behavior of objects. An **object** is a runtime instance of a class.

In modern C++, the basic syntax for declaring a class is:

```cpp
#include <iostream>
#include <string>

// Class declaration
class ClassName {
private:
    // Private members (hidden implementation details)
    int internalValue = 0;
    
public:
    // Public members (exposed interface)
    ClassName() = default;              // Constructor
    ~ClassName() = default;             // Destructor
    
    void publicMethod() const {
        std::cout << "Public method called" << std::endl;
    }
};

int main() {
    // Create objects (instantiate the class)
    ClassName object1;
    ClassName object2;
    
    // Call public methods
    object1.publicMethod();
    
    return 0;
}
```




## 3. Attributes and Methods

Classes consist of two main components:

- **Attributes (Member Variables):** Data that describes the object's state
- **Methods (Member Functions):** Functions that define what the object can do

```cpp
#include <iostream>
#include <string>

class Car {
private:
    // Private attributes - hidden from users
    std::string engineType;
    bool isRunning = false;
    
public:
    // Public attributes (generally avoid this, use getters/setters instead)
    std::string brand = "Toyota";
    
    // Public methods - this is the object's interface
    
    // Accessor (getter) - const method, doesn't modify state
    bool getEngineStatus() const {
        return isRunning;
    }
    
    // Mutator (setter) - modifies state with validation
    void startEngine() {
        if (!isRunning) {
            isRunning = true;
            std::cout << "Engine started" << std::endl;
        }
    }
    
    void stopEngine() {
        if (isRunning) {
            isRunning = false;
            std::cout << "Engine stopped" << std::endl;
        }
    }
};

int main() {
    Car myCar;
    
    std::cout << "Brand: " << myCar.brand << std::endl;
    myCar.startEngine();
    std::cout << "Running: " << (myCar.getEngineStatus() ? "Yes" : "No") << std::endl;
    myCar.stopEngine();
    
    return 0;
}
```

**Output:**
```
Brand: Toyota
Engine started
Running: Yes
Engine stopped
```


## 4. Data Abstraction and Information Hiding

Abstraction doesn't mean hiding *everything*, it means exposing a clean interface while hiding implementation details.

**The goal:** Users interact with the interface, not the implementation.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

class Calculator {
public:
    // Public interface - simple and clean
    int add(int a, int b) const {
        return a + b;
    }
    
    int multiply(int a, int b) const {
        return a * b;
    }
    
    double getAverageOfResults() const {
        if (results.empty()) return 0.0;
        double sum = 0;
        for (int r : results) {
            sum += r;
        }
        return sum / results.size();
    }
    
private:
    // Private implementation details - hidden from users
    std::vector<int> results;  // Internal state
    
    void recordResult(int result) {
        results.push_back(result);
    }
};

int main() {
    Calculator calc;
    
    // Users only see the simple public interface
    int result1 = calc.add(5, 3);
    int result2 = calc.multiply(4, 6);
    
    std::cout << "Result 1: " << result1 << std::endl;
    std::cout << "Result 2: " << result2 << std::endl;
    std::cout << "Average: " << calc.getAverageOfResults() << std::endl;
    
    // Users don't know or care about:
    // - How results are stored internally
    // - The `recordResult()` method
    // - The `results` vector
    
    return 0;
}
```

**Output:**
```
Result 1: 8
Result 2: 24
Average: 0
```



## 5. Constructors and Destructors in Modern C++

**Constructors** initialize an object when it's created. **Destructors** clean up when it's destroyed.

### Modern Constructor Patterns

```cpp
#include <iostream>
#include <string>
#include <memory>

class Person {
private:
    std::string name;
    int age;
    
public:
    // Default constructor with in-class initializers
    Person() = default;
    
    // Parameterized constructor using member initializer list
    Person(const std::string& name, int age)
        : name(name), age(age) {
        std::cout << "Person created: " << name << ", age " << age << std::endl;
    }
    
    // Copy constructor (compiler-generated is fine)
    Person(const Person&) = default;
    
    // Destructor
    ~Person() {
        std::cout << "Person destroyed: " << name << std::endl;
    }
    
    // Getters
    const std::string& getName() const { return name; }
    int getAge() const { return age; }
    
    // Setters with validation
    void setAge(int newAge) {
        if (newAge > 0 && newAge < 150) {
            age = newAge;
        }
    }
};

int main() {
    // Stack allocation - automatic cleanup
    {
        Person p1("Alice", 30);
        Person p2("Bob", 25);
        
        std::cout << p1.getName() << " is " << p1.getAge() << " years old\n";
    }  // p1 and p2 destroyed here automatically
    
    // Heap allocation with smart pointers - safe and automatic
    {
        auto p3 = std::make_unique<Person>("Charlie", 35);
        std::cout << p3->getName() << " is " << p3->getAge() << " years old\n";
    }  // p3 automatically deleted here
    
    return 0;
}
```

**Output:**
```
Person created: Alice, age 30
Person created: Bob, age 25
Alice is 30 years old
Person destroyed: Bob
Person destroyed: Alice
Person created: Charlie, age 35
Charlie is 35 years old
Person destroyed: Charlie
```

### Key Modern C++ Constructor Practices

| Practice | Why | Example |
|----------|-----|---------|
| Member initializer lists | More efficient than assignment | `Person(const std::string& n) : name(n) {}` |
| Default member initializers | Ensures all members initialized | `int value = 0;` |
| `= default` | Explicit, leverages compiler | `Person() = default;` |
| `= delete` | Prevents unwanted operations | `Person(const Person&) = delete;` |
| `noexcept` | Enables optimizations | `Person(Person&&) noexcept {}` |
| Smart pointers | Automatic memory management | `std::make_unique<Person>()` |

## 6. Inheritance and Polymorphism as advanced concepts related to Abstraction

So far, we have provided a brief introduction to Object-Oriented Programming. Abstraction becomes more intricate as it intertwines with other concepts such as inheritance and polymorphism.

Inheritance enables the creation of class hierarchies, facilitating the sharing of common behaviors among classes. On the other hand, polymorphism allows you to treat objects from derived classes as objects of their own base class. For further information on inheritance and polymorphism, you can refer to resources available [here](https://github.com/fx-biocoder/oop-in-cpp/tree/main/03%20-%20Inheritance) and [here](https://github.com/fx-biocoder/oop-in-cpp/tree/main/04%20-%20Polymorphism).

## 6. Abstraction in Practice: Advanced Concepts

### Abstract Base Classes

Abstract classes define a contract that derived classes must fulfill:

```cpp
#include <iostream>
#include <memory>
#include <vector>

// Abstract base class - defines what all vehicles must do
class Vehicle {
public:
    virtual ~Vehicle() = default;  // IMPORTANT: virtual destructor
    
    // Pure virtual functions - must be implemented by derived classes
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void displayInfo() const = 0;
};

// Concrete implementation
class Car : public Vehicle {
private:
    std::string brand;
    int doors;
    
public:
    Car(const std::string& brand, int doors)
        : brand(brand), doors(doors) {}
    
    void start() override {
        std::cout << "Car engine started: " << brand << std::endl;
    }
    
    void stop() override {
        std::cout << "Car engine stopped" << std::endl;
    }
    
    void displayInfo() const override {
        std::cout << brand << " (" << doors << " doors)" << std::endl;
    }
};

class Motorcycle : public Vehicle {
private:
    std::string model;
    
public:
    Motorcycle(const std::string& model) : model(model) {}
    
    void start() override {
        std::cout << "Motorcycle engine started: " << model << std::endl;
    }
    
    void stop() override {
        std::cout << "Motorcycle engine stopped" << std::endl;
    }
    
    void displayInfo() const override {
        std::cout << "Motorcycle: " << model << std::endl;
    }
};

int main() {
    // We cannot create a Vehicle object - it's abstract
    // Vehicle v;  // ERROR!
    
    // But we can use base class pointers for polymorphism
    std::vector<std::unique_ptr<Vehicle>> vehicles;
    
    vehicles.push_back(std::make_unique<Car>("Toyota", 4));
    vehicles.push_back(std::make_unique<Motorcycle>("Harley-Davidson"));
    
    // Polymorphic behavior through abstract interface
    for (auto& vehicle : vehicles) {
        vehicle->displayInfo();
        vehicle->start();
        vehicle->stop();
        std::cout << "---\n";
    }
    
    return 0;
}
```

**Output:**
```
Toyota (4 doors)
Car engine started: Toyota
Car engine stopped
---
Motorcycle: Harley-Davidson
Motorcycle engine started: Harley-Davidson
Motorcycle engine stopped
---
```

### Why This Matters

The `Vehicle` class abstracts the concept of "something that can start and stop." Derived classes provide specific implementations. Users work with the abstract interface, not concrete details.

**Compilable examples are in the `examples/` directory. See the README for compilation instructions.**

---

**Article Updated:** January 2026 | Licensed under CC BY-NC-SA 4.0

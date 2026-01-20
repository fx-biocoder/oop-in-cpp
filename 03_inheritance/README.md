# Inheritance

## 1. Introduction

Inheritance is a mechanism for creating new classes based on existing classes, establishing a "is-a" relationship. A derived class (child) inherits members from a base class (parent), promoting code reuse and establishing hierarchies.

**Benefits of inheritance:**
- **Code reuse:** Share common functionality across classes
- **Extensibility:** Derived classes can extend or override parent behavior
- **Hierarchy:** Model real-world "is-a" relationships
- **Polymorphism:** Treat derived classes through base class interfaces

**When to use inheritance:**
- Clear "is-a" relationship (Dog is-a Animal)
- Need to override functionality in derived classes
- Want to establish a contract via abstract base classes

**When NOT to use inheritance:**
- Simple "has-a" relationship (prefer composition)
- Only sharing a single method (composition is better)
- Deep inheritance hierarchies (hard to maintain)

## 2. Base Classes and Derived Classes

Here's a modern C++ example of inheritance:

```cpp
#include <iostream>
#include <string>
#include <memory>

// Base class - defines common functionality
class Vehicle {
protected:
    // Protected: accessible to derived classes but not to external users
    std::string brand;
    int year;
    
public:
    // Constructor
    Vehicle(const std::string& brand, int year)
        : brand(brand), year(year) {}
    
    // Virtual destructor - REQUIRED for polymorphic classes
    virtual ~Vehicle() = default;
    
    // Virtual methods - can be overridden in derived classes
    virtual void start() {
        std::cout << brand << " vehicle starting...\n";
    }
    
    virtual void stop() {
        std::cout << brand << " vehicle stopping...\n";
    }
    
    // Non-virtual method - same implementation in all classes
    void printYear() const {
        std::cout << "Year: " << year << "\n";
    }
};

// Derived class - inherits from Vehicle
class Car : public Vehicle {
private:
    int numberOfDoors;
    
public:
    // Constructor - must initialize base class
    Car(const std::string& brand, int year, int doors)
        : Vehicle(brand, year), numberOfDoors(doors) {}
    
    // Destructor
    ~Car() override = default;
    
    // Override base class virtual methods
    void start() override {
        std::cout << brand << " car with " << numberOfDoors << " doors starting...\n";
    }
    
    void stop() override {
        std::cout << brand << " car stopping...\n";
    }
    
    // New method specific to Car
    void openTrunk() const {
        std::cout << "Trunk opened\n";
    }
};

// Another derived class
class Motorcycle : public Vehicle {
private:
    bool hasSidecar;
    
public:
    Motorcycle(const std::string& brand, int year, bool hasSidecar)
        : Vehicle(brand, year), hasSidecar(hasSidecar) {}
    
    ~Motorcycle() override = default;
    
    void start() override {
        std::cout << brand << " motorcycle starting...\n";
    }
    
    void stop() override {
        std::cout << brand << " motorcycle stopping...\n";
    }
};

int main() {
    // Create derived class objects
    Car myCar("Toyota", 2023, 4);
    Motorcycle myBike("Harley", 2022, false);
    
    // Base class functionality available on derived classes
    myCar.printYear();
    myBike.printYear();
    
    // Call overridden methods
    myCar.start();
    myBike.start();
    
    myCar.stop();
    myBike.stop();
    
    // Car-specific functionality
    myCar.openTrunk();
    
    // Polymorphism: use base class pointers/references
    Vehicle& vehicleRef1 = myCar;
    Vehicle& vehicleRef2 = myBike;
    
    vehicleRef1.start();  // Calls Car::start()
    vehicleRef2.start();  // Calls Motorcycle::start()
    
    return 0;
}
```

**Output:**
```
Year: 2023
Year: 2022
Toyota car with 4 doors starting...
Harley motorcycle starting...
Toyota car stopping...
Harley motorcycle stopping...
Trunk opened
Toyota car with 4 doors starting...
Harley motorcycle starting...
```

## 3. Inheritance Types and Access Control

When you inherit from a base class, the type of inheritance determines how base class members are accessible:

```cpp
class Base {
public:
    void publicMethod() {}
protected:
    void protectedMethod() {}
private:
    void privateMethod() {}
};

// Public inheritance: "is-a" relationship (most common)
class PublicDerived : public Base {
    // public methods remain public
    // protected methods remain protected
    // private methods are NOT accessible
};

// Protected inheritance: used rarely
class ProtectedDerived : protected Base {
    // All public members become protected
    // protected members stay protected
};

// Private inheritance: used very rarely
class PrivateDerived : private Base {
    // All public and protected members become private
    // Breaks the "is-a" relationship
};
```

**Rule of thumb:** Use `public` inheritance 99% of the time. Private/protected inheritance is almost never the right choice.

### Detailed Inheritance Access

| Original | public | protected | private |
|----------|--------|-----------|---------|
| public | public | protected | private |
| protected | protected | protected | private |
| private | N/A | N/A | N/A |

## 4. Virtual Functions and Function Overriding

### Types of Member Functions

There are three types of member functions based on their behavior in inheritance:

1. **Pure Virtual Functions:** Must be overridden in derived classes
   ```cpp
   virtual void method() = 0;  // No implementation in base
   ```

2. **Virtual Functions:** Can be overridden; have default implementation
   ```cpp
   virtual void method() { /* default implementation */ }
   ```

3. **Non-Virtual Functions:** Cannot be overridden; same implementation everywhere
   ```cpp
   void method() { /* implementation */ }
   ```

### Using `override` and `final`

Modern C++ provides keywords to make intentions explicit:

```cpp
class Base {
public:
    virtual ~Base() = default;
    
    virtual void method1() = 0;              // Pure virtual
    virtual void method2() { }               // Virtual with default
    void method3() { }                       // Non-virtual
    virtual void method4() final { }         // Cannot be overridden further
};

class Derived : public Base {
public:
    // MUST override pure virtual functions
    void method1() override {
        std::cout << "Derived::method1\n";
    }
    
    // CAN override virtual functions
    void method2() override {
        std::cout << "Derived::method2\n";
    }
    
    // CANNOT override non-virtual functions (this shadows, doesn't override)
    // void method3() { }  // Hides Base::method3, but doesn't override
    
    // CANNOT override final methods
    // void method4() override { }  // COMPILER ERROR
};

class FurtherDerived : public Derived {
public:
    void method1() override {
        std::cout << "FurtherDerived::method1\n";
    }
    
    // Cannot override method4 - it's final
    // void method4() override { }  // COMPILER ERROR
};
```

**Best practices:**
- ✅ Always use `override` when overriding virtual functions
- ✅ Always use `virtual` in base classes
- ✅ Always mark destructors as virtual in base classes
- ✅ Use `final` to prevent further overriding when appropriate
- ❌ Never shadow (hide) functions - use `override` instead

## 5. Abstract Classes and Interfaces

### Abstract Classes

Abstract classes define a contract that derived classes must implement. They cannot be instantiated directly:

```cpp
#include <iostream>
#include <memory>
#include <vector>

// Abstract base class
class Shape {
protected:
    std::string name;
    
public:
    Shape(const std::string& name) : name(name) {}
    virtual ~Shape() = default;
    
    // Pure virtual functions - must be overridden
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    
    // Virtual function with default implementation
    virtual void display() const {
        std::cout << "Shape: " << name << std::endl;
    }
};

// Concrete implementation
class Circle : public Shape {
private:
    double radius;
    static constexpr double PI = 3.14159;
    
public:
    Circle(const std::string& name, double radius)
        : Shape(name), radius(radius) {}
    
    double getArea() const override {
        return PI * radius * radius;
    }
    
    double getPerimeter() const override {
        return 2 * PI * radius;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(const std::string& name, double width, double height)
        : Shape(name), width(width), height(height) {}
    
    double getArea() const override {
        return width * height;
    }
    
    double getPerimeter() const override {
        return 2 * (width + height);
    }
};

int main() {
    // ❌ Cannot create abstract class
    // Shape s("Invalid");  // COMPILER ERROR
    
    // ✅ Can create derived classes
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>("Circle", 5.0));
    shapes.push_back(std::make_unique<Rectangle>("Rectangle", 3.0, 4.0));
    
    // ✅ Use polymorphism through base class
    for (const auto& shape : shapes) {
        shape->display();
        std::cout << "  Area: " << shape->getArea() << std::endl;
        std::cout << "  Perimeter: " << shape->getPerimeter() << std::endl;
    }
    
    return 0;
}
```

**Output:**
```
Shape: Circle
  Area: 78.54
  Perimeter: 31.42
Shape: Rectangle
  Area: 12
  Perimeter: 14
```

### Interfaces (Pure Abstract Classes)

An interface is a class with only pure virtual functions (and no data members):

```cpp
// Interface - defines a contract
class Drawable {
public:
    virtual ~Drawable() = default;
    virtual void draw() const = 0;
    virtual void erase() const = 0;
};

class Serializable {
public:
    virtual ~Serializable() = default;
    virtual std::string serialize() const = 0;
    virtual void deserialize(const std::string& data) = 0;
};

// Class implementing multiple interfaces
class Document : public Drawable, public Serializable {
private:
    std::string content;
    
public:
    void draw() const override {
        std::cout << "Drawing document: " << content << std::endl;
    }
    
    void erase() const override {
        std::cout << "Erasing document\n";
    }
    
    std::string serialize() const override {
        return content;
    }
    
    void deserialize(const std::string& data) override {
        content = data;
    }
};
```

**Key differences:**
- **Abstract classes:** Can have data members and mixed virtual/non-virtual methods
- **Interfaces:** Only pure virtual methods, no data members
- C++ doesn't distinguish syntactically, but the pattern matters for design


## 6. Constructor and Destructor Behavior in Inheritance

When creating and destroying derived class objects, constructors and destructors are called in a specific order:

### Constructor Execution Order

Base class constructor executes **first**, then derived class constructor:

```cpp
#include <iostream>

class Base {
public:
    Base() {
        std::cout << "1. Base constructor\n";
    }
    
    virtual ~Base() {
        std::cout << "4. Base destructor\n";
    }
};

class Derived : public Base {
public:
    Derived() {
        std::cout << "2. Derived constructor\n";
    }
    
    ~Derived() override {
        std::cout << "3. Derived destructor\n";
    }
};

class FurtherDerived : public Derived {
public:
    FurtherDerived() {
        std::cout << "2. FurtherDerived constructor\n";
    }
    
    ~FurtherDerived() override {
        std::cout << "3. FurtherDerived destructor\n";
    }
};

int main() {
    {
        std::cout << "Creating Derived object:\n";
        Derived d;
    }  // Destructed here
    
    std::cout << "\nCreating FurtherDerived object:\n";
    {
        FurtherDerived fd;
    }  // Destructed here
    
    return 0;
}
```

**Output:**
```
Creating Derived object:
1. Base constructor
2. Derived constructor
3. Derived destructor
4. Base destructor

Creating FurtherDerived object:
1. Base constructor
2. FurtherDerived constructor
3. FurtherDerived destructor
4. Base destructor
```

### Initializing Base Classes

When a derived class constructor runs, base class members must be initialized:

```cpp
class Animal {
protected:
    std::string name;
    int age;
    
public:
    // Constructor that takes parameters
    Animal(const std::string& name, int age)
        : name(name), age(age) {
        std::cout << "Animal created: " << name << std::endl;
    }
    
    virtual ~Animal() = default;
};

class Dog : public Animal {
private:
    std::string breed;
    
public:
    // MUST call base class constructor
    Dog(const std::string& name, int age, const std::string& breed)
        : Animal(name, age),  // Initialize base class
          breed(breed) {
        std::cout << "Dog created: " << breed << std::endl;
    }
};

int main() {
    Dog dog("Buddy", 5, "Golden Retriever");
    return 0;
}
```

**Output:**
```
Animal created: Buddy
Dog created: Golden Retriever
```

### IMPORTANT: Virtual Destructors

Always make destructors virtual in base classes:

```cpp
// WRONG - Memory leak possible
class BadBase {
public:
    ~BadBase() { }  // Non-virtual destructor
};

// CORRECT - Safe polymorphic deletion
class GoodBase {
public:
    virtual ~GoodBase() = default;  // Virtual destructor
};

class Derived : public GoodBase {
private:
    int* data = new int[1000];
    
public:
    ~Derived() override {
        delete[] data;  // Will be called correctly
    }
};

int main() {
    GoodBase* obj = new Derived();
    delete obj;  // Calls Derived destructor, then GoodBase destructor
    return 0;
}
```

Without a virtual destructor, `Derived::~Derived()` won't be called, causing a memory leak!

---

**Article Updated:** January 2026 | Licensed under CC BY-NC-SA 4.0

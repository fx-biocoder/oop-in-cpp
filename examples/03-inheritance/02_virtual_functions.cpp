#include <iostream>

// Example: Virtual functions and override keyword
class BaseClass {
public:
    virtual ~BaseClass() = default;
    
    virtual void method1() {
        std::cout << "BaseClass::method1\n";
    }
    
    virtual void method2() = 0;  // Pure virtual
    
    void nonVirtualMethod() {
        std::cout << "BaseClass::nonVirtualMethod (not virtual)\n";
    }
};

class DerivedClass : public BaseClass {
public:
    ~DerivedClass() override = default;
    
    // Override virtual method
    void method1() override {
        std::cout << "DerivedClass::method1 (overridden)\n";
    }
    
    // Implement pure virtual
    void method2() override {
        std::cout << "DerivedClass::method2 (implemented)\n";
    }
    
    // This does NOT override nonVirtualMethod - it hides it
    // (not recommended - use override for safety)
    void nonVirtualMethod() {
        std::cout << "DerivedClass::nonVirtualMethod (shadows, not overrides)\n";
    }
};

class FurtherDerived : public DerivedClass {
public:
    void method1() override {
        std::cout << "FurtherDerived::method1\n";
    }
    
    void method2() override {
        std::cout << "FurtherDerived::method2\n";
    }
    
    // Cannot override - would cause compiler error
    // virtual void nonVirtualMethod() override { }  // ERROR
};

int main() {
    BaseClass* base = new DerivedClass();
    
    std::cout << "=== Virtual function calls ===\n";
    base->method1();      // Calls DerivedClass::method1
    base->method2();      // Calls DerivedClass::method2
    base->nonVirtualMethod();  // Calls BaseClass::nonVirtualMethod (not virtual)
    
    delete base;
    
    std::cout << "\n=== Direct object calls ===\n";
    DerivedClass derived;
    derived.method1();
    derived.method2();
    derived.nonVirtualMethod();  // Calls DerivedClass::nonVirtualMethod
    
    std::cout << "\n=== Multiple levels ===\n";
    BaseClass* ptr = new FurtherDerived();
    ptr->method1();  // Calls FurtherDerived::method1
    ptr->method2();  // Calls FurtherDerived::method2
    
    delete ptr;
    
    return 0;
}

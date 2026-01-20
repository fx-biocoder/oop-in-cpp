#include <iostream>

// Example: Demonstrating access modifiers and inheritance
class Animal {
private:
    std::string privateSecret = "I am a private member";
    
protected:
    std::string protectedInfo = "I am protected - derived classes can access";
    
public:
    std::string publicInfo = "I am public - everyone can access";
    
    // Public method
    void publicMethod() const {
        std::cout << "Public method called\n";
    }
    
    // Destructor
    virtual ~Animal() = default;
};

// Derived class
class Dog : public Animal {
public:
    void demonstrateAccess() const {
        std::cout << "\n=== Inside Dog class ===\n";
        
        // Can access public members
        std::cout << "Public: " << publicInfo << std::endl;
        
        // Can access protected members
        std::cout << "Protected: " << protectedInfo << std::endl;
        
        // Cannot access private members (compiler error if uncommented)
        // std::cout << privateSecret << std::endl;  // ERROR
    }
    
    // Call protected method
    void useProtectedMethod() {
        publicMethod();  // Inherited public method
    }
};

int main() {
    Animal animal;
    Dog dog;
    
    std::cout << "=== Outside all classes ===\n";
    
    // Can access public members
    std::cout << "Public: " << animal.publicInfo << std::endl;
    animal.publicMethod();
    
    // Cannot access protected (compiler error if uncommented)
    // std::cout << animal.protectedInfo << std::endl;  // ERROR
    
    // Cannot access private (compiler error if uncommented)
    // std::cout << animal.privateSecret << std::endl;  // ERROR
    
    dog.demonstrateAccess();
    dog.useProtectedMethod();
    
    return 0;
}

#include <iostream>
#include <memory>
#include <vector>

// Base class with virtual functions
class Animal {
public:
    virtual ~Animal() = default;
    
    virtual void makeSound() const {
        std::cout << "Generic animal sound\n";
    }
    
    virtual void move() const = 0;
    
    virtual void describe() const = 0;
};

class Dog : public Animal {
private:
    std::string breed;
    
public:
    Dog(const std::string& breed) : breed(breed) {}
    
    void makeSound() const override {
        std::cout << "Woof! Woof!\n";
    }
    
    void move() const override {
        std::cout << "Running on four legs\n";
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
    
    void move() const override {
        std::cout << "Walking silently on four legs\n";
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
    
    void move() const override {
        std::cout << "Flying in the sky\n";
    }
    
    void describe() const override {
        std::cout << "I am a " << species << "\n";
    }
};

int main() {
    // Create a vector of animals
    std::vector<std::unique_ptr<Animal>> animals;
    
    animals.push_back(std::make_unique<Dog>("Golden Retriever"));
    animals.push_back(std::make_unique<Cat>("Orange"));
    animals.push_back(std::make_unique<Bird>("Parrot"));
    animals.push_back(std::make_unique<Dog>("Husky"));
    animals.push_back(std::make_unique<Cat>("Black"));
    
    // Polymorphic behavior - same code, different results
    std::cout << "=== All Animals Making Sounds ===\n";
    for (const auto& animal : animals) {
        animal->makeSound();
    }
    
    std::cout << "\n=== All Animals Moving ===\n";
    for (const auto& animal : animals) {
        animal->move();
    }
    
    std::cout << "\n=== All Animals Describing ===\n";
    for (const auto& animal : animals) {
        animal->describe();
    }
    
    std::cout << "\n=== Full Interaction ===\n";
    for (const auto& animal : animals) {
        std::cout << "\n";
        animal->describe();
        animal->makeSound();
        animal->move();
    }
    
    return 0;
}

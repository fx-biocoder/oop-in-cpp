#include <iostream>
#include <string>

// Base class: Vehicle
class Vehicle {
protected:
    // Protected: accessible to derived classes
    std::string brand;
    int year;
    
public:
    // Constructor with member initializer list
    Vehicle(const std::string& brand, int year)
        : brand(brand), year(year) {}
    
    // Virtual destructor - REQUIRED for polymorphic classes
    virtual ~Vehicle() = default;
    
    // Virtual methods that can be overridden
    virtual void start() {
        std::cout << brand << " vehicle starting...\n";
    }
    
    virtual void stop() {
        std::cout << brand << " vehicle stopping...\n";
    }
    
    // Non-virtual method - same implementation everywhere
    void printInfo() const {
        std::cout << "Brand: " << brand << ", Year: " << year << std::endl;
    }
};

// Derived class: Car
class Car : public Vehicle {
private:
    int numberOfDoors;
    
public:
    // Constructor calling base class constructor
    Car(const std::string& brand, int year, int doors)
        : Vehicle(brand, year), numberOfDoors(doors) {}
    
    ~Car() override = default;
    
    // Override virtual methods
    void start() override {
        std::cout << brand << " car with " << numberOfDoors 
                  << " doors starting...\n";
    }
    
    void stop() override {
        std::cout << brand << " car is parking...\n";
    }
    
    // Car-specific method
    void openTrunk() const {
        std::cout << "Trunk opened\n";
    }
};

// Derived class: Motorcycle
class Motorcycle : public Vehicle {
private:
    bool hasSidecar;
    
public:
    Motorcycle(const std::string& brand, int year, bool hasSidecar)
        : Vehicle(brand, year), hasSidecar(hasSidecar) {}
    
    ~Motorcycle() override = default;
    
    void start() override {
        std::cout << brand << " motorcycle engine roaring...\n";
    }
    
    void stop() override {
        std::cout << brand << " motorcycle stopped\n";
    }
    
    // Motorcycle-specific method
    void wheelie() const {
        std::cout << "Performing a wheelie!\n";
    }
};

int main() {
    // Create derived class objects
    Car myCar("Toyota", 2023, 4);
    Motorcycle myBike("Harley-Davidson", 2022, false);
    
    std::cout << "=== Car Info ===\n";
    myCar.printInfo();  // Inherited non-virtual method
    myCar.start();      // Calls Car::start()
    myCar.stop();
    myCar.openTrunk();  // Car-specific method
    
    std::cout << "\n=== Motorcycle Info ===\n";
    myBike.printInfo();  // Inherited non-virtual method
    myBike.start();      // Calls Motorcycle::start()
    myBike.stop();
    myBike.wheelie();    // Motorcycle-specific method
    
    // Polymorphism: use base class references
    std::cout << "\n=== Using Base Class References ===\n";
    Vehicle& v1 = myCar;
    Vehicle& v2 = myBike;
    
    v1.start();  // Calls Car::start()
    v1.printInfo();
    
    v2.start();  // Calls Motorcycle::start()
    v2.printInfo();
    
    return 0;
}

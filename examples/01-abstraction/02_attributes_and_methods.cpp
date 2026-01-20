#include <iostream>
#include <string>

// Example: Attributes and methods with const-correctness
class Car {
private:
    // Private attributes with default initialization (modern C++)
    std::string brand = "Unknown";
    std::string model = "Unknown";
    int year = 0;
    bool isRunning = false;
    int speed = 0;
    
public:
    // Constructor using member initializer list
    Car(const std::string& brand, const std::string& model, int year)
        : brand(brand), model(model), year(year) {}
    
    // Destructor
    ~Car() = default;
    
    // Getters - const methods that don't modify state
    const std::string& getBrand() const { return brand; }
    const std::string& getModel() const { return model; }
    int getYear() const { return year; }
    bool isCarRunning() const { return isRunning; }
    int getSpeed() const { return speed; }
    
    // Methods that modify state
    void startEngine() {
        if (!isRunning) {
            isRunning = true;
            std::cout << brand << " " << model << " engine started\n";
        }
    }
    
    void stopEngine() {
        if (isRunning) {
            isRunning = false;
            speed = 0;
            std::cout << brand << " " << model << " engine stopped\n";
        }
    }
    
    void accelerate() {
        if (isRunning && speed < 200) {
            speed += 10;
            std::cout << "Speed: " << speed << " km/h\n";
        }
    }
    
    void decelerate() {
        if (speed > 0) {
            speed -= 10;
            std::cout << "Speed: " << speed << " km/h\n";
        }
    }
    
    // Method to display all car info
    void displayInfo() const {
        std::cout << "\n=== Car Information ===\n";
        std::cout << "Brand: " << brand << "\n";
        std::cout << "Model: " << model << "\n";
        std::cout << "Year: " << year << "\n";
        std::cout << "Running: " << (isRunning ? "Yes" : "No") << "\n";
        std::cout << "Speed: " << speed << " km/h\n";
    }
};

int main() {
    Car myCar("Toyota", "Corolla", 2023);
    
    myCar.displayInfo();
    
    std::cout << "\n--- Driving ---\n";
    myCar.startEngine();
    myCar.accelerate();
    myCar.accelerate();
    myCar.decelerate();
    myCar.stopEngine();
    
    myCar.displayInfo();
    
    return 0;
}

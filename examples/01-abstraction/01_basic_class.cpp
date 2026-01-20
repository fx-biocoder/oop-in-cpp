#include <iostream>
#include <string>

// Modern C++ example: Basic class with abstraction
class Calculator {
private:
    // Private members - hidden implementation
    int lastResult = 0;
    
    // Private method - internal use only
    void storeResult(int result) {
        lastResult = result;
    }
    
public:
    // Constructor
    Calculator() = default;
    
    // Destructor
    ~Calculator() = default;
    
    // Public interface - only what users need to see
    int add(int a, int b) const {
        return a + b;
    }
    
    int subtract(int a, int b) const {
        return a - b;
    }
    
    int multiply(int a, int b) const {
        return a * b;
    }
    
    double divide(int a, int b) const {
        if (b == 0) {
            std::cerr << "Error: Division by zero\n";
            return 0.0;
        }
        return static_cast<double>(a) / b;
    }
    
    int getLastResult() const {
        return lastResult;
    }
};

int main() {
    Calculator calc;
    
    // Users only see the clean public interface
    std::cout << "Add 10 + 5 = " << calc.add(10, 5) << std::endl;
    std::cout << "Subtract 10 - 3 = " << calc.subtract(10, 3) << std::endl;
    std::cout << "Multiply 4 * 7 = " << calc.multiply(4, 7) << std::endl;
    std::cout << "Divide 20 / 4 = " << calc.divide(20, 4) << std::endl;
    
    // Users cannot access private members
    // calc.storeResult(100);  // COMPILER ERROR: private
    // std::cout << calc.lastResult << std::endl;  // COMPILER ERROR: private
    
    return 0;
}

#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Abstract base class (interface)
class Employee {
protected:
    std::string name;
    
public:
    Employee(const std::string& name) : name(name) {}
    
    virtual ~Employee() = default;
    
    virtual void work() const = 0;
    virtual void getSalary() const = 0;
    
    const std::string& getName() const {
        return name;
    }
};

class Engineer : public Employee {
private:
    double salary = 80000.0;
    
public:
    Engineer(const std::string& name) : Employee(name) {}
    
    void work() const override {
        std::cout << name << " is writing code and debugging\n";
    }
    
    void getSalary() const override {
        std::cout << name << "'s salary: $" << salary << std::endl;
    }
};

class Manager : public Employee {
private:
    double salary = 100000.0;
    
public:
    Manager(const std::string& name) : Employee(name) {}
    
    void work() const override {
        std::cout << name << " is managing the team\n";
    }
    
    void getSalary() const override {
        std::cout << name << "'s salary: $" << salary << std::endl;
    }
};

class Designer : public Employee {
private:
    double salary = 75000.0;
    
public:
    Designer(const std::string& name) : Employee(name) {}
    
    void work() const override {
        std::cout << name << " is designing user interfaces\n";
    }
    
    void getSalary() const override {
        std::cout << name << "'s salary: $" << salary << std::endl;
    }
};

int main() {
    // Create a company with different employees
    std::vector<std::unique_ptr<Employee>> company;
    
    company.push_back(std::make_unique<Engineer>("Alice"));
    company.push_back(std::make_unique<Manager>("Bob"));
    company.push_back(std::make_unique<Designer>("Charlie"));
    company.push_back(std::make_unique<Engineer>("David"));
    
    std::cout << "=== Company Staff ===\n";
    
    // Iterate through employees - polymorphic behavior
    for (const auto& employee : company) {
        std::cout << "\n" << employee->getName() << ":\n";
        employee->work();
        employee->getSalary();
    }
    
    std::cout << "\n=== Today's Work Day ===\n";
    std::cout << "Everyone at work:\n";
    for (const auto& employee : company) {
        std::cout << "  - ";
        employee->work();
    }
    
    return 0;
}

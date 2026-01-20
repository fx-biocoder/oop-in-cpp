#include <iostream>
#include <memory>
#include <vector>

// Abstract base class
class Shape {
protected:
    std::string name;
    
public:
    Shape(const std::string& name) : name(name) {}
    
    // Virtual destructor - CRITICAL for polymorphic classes
    virtual ~Shape() = default;
    
    // Pure virtual functions - must be implemented by derived classes
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    
    // Virtual method with default implementation
    virtual void display() const {
        std::cout << "Shape: " << name << std::endl;
    }
};

// Concrete implementation: Circle
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

// Concrete implementation: Rectangle
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

// Concrete implementation: Triangle
class Triangle : public Shape {
private:
    double a, b, c;  // side lengths
    
public:
    Triangle(const std::string& name, double a, double b, double c)
        : Shape(name), a(a), b(b), c(c) {}
    
    double getArea() const override {
        // Heron's formula
        double s = (a + b + c) / 2.0;
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }
    
    double getPerimeter() const override {
        return a + b + c;
    }
};

int main() {
    // Cannot create abstract class
    // Shape s("Invalid");  // COMPILER ERROR
    
    // Create derived classes and store in vector
    std::vector<std::unique_ptr<Shape>> shapes;
    
    shapes.push_back(std::make_unique<Circle>("My Circle", 5.0));
    shapes.push_back(std::make_unique<Rectangle>("My Rectangle", 4.0, 6.0));
    shapes.push_back(std::make_unique<Triangle>("My Triangle", 3.0, 4.0, 5.0));
    
    // Polymorphic behavior: iterate through base class pointers
    std::cout << "=== Shape Information ===\n";
    for (const auto& shape : shapes) {
        shape->display();
        std::cout << "Area: " << shape->getArea() << std::endl;
        std::cout << "Perimeter: " << shape->getPerimeter() << std::endl;
        std::cout << std::endl;
    }
    
    return 0;
}

#include <iostream>
#include <typeinfo>

// Example: Understanding virtual tables (vtables)
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual void rotate(int degrees) const = 0;
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing circle\n";
    }
    
    void rotate(int degrees) const override {
        std::cout << "Rotating circle " << degrees << " degrees\n";
        std::cout << "(Note: rotation has no visual effect on circle)\n";
    }
};

class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing square\n";
    }
    
    void rotate(int degrees) const override {
        std::cout << "Rotating square " << degrees << " degrees\n";
    }
};

class Triangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing triangle\n";
    }
    
    void rotate(int degrees) const override {
        std::cout << "Rotating triangle " << degrees << " degrees\n";
    }
};

int main() {
    Circle circle;
    Square square;
    Triangle triangle;
    
    std::cout << "=== Object Information ===\n";
    std::cout << "Circle size: " << sizeof(circle) << " bytes\n";
    std::cout << "Square size: " << sizeof(square) << " bytes\n";
    std::cout << "Triangle size: " << sizeof(triangle) << " bytes\n";
    
    // Base class pointers
    Shape* shapes[3] = { &circle, &square, &triangle };
    
    std::cout << "Drawing all shapes:\n";
    for (Shape* shape : shapes) {
        shape->draw();  // Virtual call - looks up in vtable
    }
    
    std::cout << "\nRotating all shapes by 45 degrees:\n";
    for (Shape* shape : shapes) {
        shape->rotate(45);  // Virtual call - looks up in vtable
    }
    
    return 0;
}

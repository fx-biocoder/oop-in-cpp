# Inheritance

## 1. Introduction

Inheritance can be defined as a mechanism that enables you to utilize a class as the foundation for a new class derived from it. This implies that the new class inherits the behavior of the parent class. The advantages of inheritance are as follows:

- Code reusability, which leads to time and effort savings.
- The ability to extend the behavior of a class, as the child class inherits both the behavior and attributes of the parent class.
- Flexibility and simplified maintenance by inheriting from abstract classes (further exploration on this topic will be covered later on).

## 2. Base class and derived classes

In the context of Object-Oriented Programming, a base class serves as the foundation for classes that derive from it. Let's consider a class that defines the fundamental structure of any car. We are aware that certain characteristics are common to all car models, regardless of their brand, such as having four wheels, three pedals, and a license plate ID. Additionally, we know that a car engine can be started and turned off, and we can determine whether a car is running or not. Now, let's see how we can represent this in actual code:

```cpp
#include <string>
class Car
{
	private:
		int numberOfWheels = 4;
		int numberOfPedals = 3;
		std::string licensePlate;
		bool isRunning = false;
	
	protected:
		std::string transmission = "Manual";
		
	public:
		// Constructor, destructor
		Car(std::string plate) { this->licensePlate = plate; }
		~Car() = default;
	
		// Start or stop engine
		void startEngine() { this->isRunning = true; }
		void stopEngine() { this->isRunning = false; }
		
		// Tells if the car is running
		std::string isTheCarRunning() 
		{
			if (isRunning) { return "The car is running"; }
			else { return "The car is not running"; }
		}
};
```

***Note:** For the sake of simplicity, I have defined inline methods. In a real project, it is recommended to separate the declaration of the class from the implementation of its methods in a separate source file.*

Now that we have a base class, let's consider how we can define a class that takes into account the car brand. Fortunately, we can achieve that by defining a new class specific to a particular brand, such as Toyota:

```cpp
#include <string>

class Toyota : public Car
{
	private:
		int numberOfWheels = 4;
		int numberOfPedals = 3;
		std::string licensePlate;
		bool isRunning = false;
		std::string carModel;
		
	public:
		Toyota(std::string model, std::string plate) 
		{ 
			this->carModel = model;
			this->licensePlate = plate;
		}
		~Toyota() { std::cout << "Toyota car destroyed" << std::endl; }
		std::string getCarModel() { return "Car model: Toyota " + carModel; }
		std::string getTransmissionType() { return transmission; }
};
```

Let's test the following:

1. Did the class Toyota inherit the public methods from the base class Car?
2. Can the class Toyota access the protected attribute present in the base class Car?

To find out, let's execute the following script:

```cpp
int main() 
{
	// Creating the object
	Toyota toyota("Hilux", "AFK123");

	// Testing the methods to see if anything went wrong
	toyota.startEngine();
	toyota.stopEngine();
	std::string model = toyota.getCarModel();
	std::string transmission = toyota.getTransmissionType();

	// Print the result
	std::cout << model + ". Transmission: " + transmission << std::endl;

	return 0;
}
```

The output is:

```
Car model: Toyota Hilux. Transmission: Manual
Toyota car destroyed
```

## 3. Public, private and protected inheritance

Success! In the previous example, we successfully created a child class. In this case, we utilized public inheritance. However, it's worth considering the implications of using private or protected inheritance:

1. **Private inheritance:** In this case, both public and protected members from the base class Car would become private members in the class Toyota.
2. **Protected inheritance:** In this scenario, both public and protected members from the base class Car would become protected members in the class Toyota.

It's important to keep these outcomes in mind when deciding which type of inheritance is appropriate for your specific situation.

## 4. Function override in class inheritance

When establishing a class hierarchy, there are situations where we need to define parent classes with methods that are either not implemented or likely to be changed in child classes. This is known as function overriding and serves various purposes in C++. How do we determine which functions can be overridden? There are three types of member functions that can exist in a class:

1. **Pure virtual functions:** These are functions whose implementation is not provided in the base class and must be overridden in derived classes. They are typically defined as follows:

`virtual void myFunction() = 0;`

2. **Virtual functions:** These functions can be overridden in derived classes, but they can also have their own specific implementation. They are usually defined as follows:

`virtual void myFunction() { // Implementation... }`

3. **Non-virtual functions:** These are regular functions without the virtual keyword, and they behave as you would expect. They are defined as follows:

`void myFunction() { // Implementation... }`

By understanding these three types of member functions, you can determine which functions can be overridden and choose the appropriate approach based on your requirements.

## 5. Resolving virtual functions with dynamic linking in the context of class inheritance

So, now that we have established what virtual functions are, how do we implement them in real code? Let's consider an abstract class called Polygon, from which we derive subclasses representing specific types of polygons - triangles, squares, pentagons, and so on. Let's see how we can translate this into actual code:

```cpp
#include <iostream>

// Abstract polygon
class Polygon
{
	public:
		Polygon() { std::cout << "Polygon created" << std::endl; }
		virtual ~Polygon() { std::cout << "Polygon destroyed" << std::endl; }
		virtual void typeOfPolygon() 
		{
			// Empty...
		}
};

// Triangle
class Triangle : public Polygon
{
	public:
		Triangle() { std::cout << "Triangle created" << std::endl; }
		~Triangle() { std::cout << "Triangle destroyed" << std::endl; }
		void typeOfPolygon() override 	// See? The method is overridden
		{
			std::cout << "This is a triangle" << std::endl; // Implementation
		}
};

// Square
class Square : public Polygon
{
	public:
		Square() { std::cout << "Square created" << std::endl; }
		~Square() { std::cout << "Square destroyed" << std::endl; }
		void typeOfPolygon() override
		{
			std::cout << "This is a square" << std::endl;
		}
		
};
```

We have defined an abstract Polygon class and two subclasses - Triangle and Square. However, there is a difference in the implementation of the `typeOfPolygon()` function in these subclasses. Now, the question arises: if I create an object of the Polygon class, how can I specify which implementation to use? Let me demonstrate.

```cpp
int main()
{
	// Dynamic memory allocation
	Polygon* polygon1 = new Triangle;
	Polygon* polygon2 = new Square;
	
	// First output
	polygon1->typeOfPolygon();
	
	// Second output
	polygon2->typeOfPolygon();
	
	// Always remember to deallocate!
	delete polygon1;
	delete polygon2;
	
	return 0;
}
```

And the console output:

```
This is a triangle
This is a square
```
***Note:** In case you're wondering - yes, I have omitted the output of the constructor/destructor. We will review that in the next section.*

Now, let me explain in detail. I have created two pointers of type `Polygon` that store the memory addresses of two different objects belonging to the child classes of `Polygon` (if you need to revisit this topic, you can refer to my brief cheatsheet on dynamic memory allocation for beginners). Then, I proceeded to call the overridden method using these pointers, and each of them produced output specific to their respective classes.


## 6. Constructors and destructors in class inheritance

We have seen how to handle virtual functions with dynamic linking, but we are still unsure about the order in which constructors and destructors are called during runtime. Let's execute the following program:

```cpp
int main()
{
	// Dynamic memory allocation
	std::cout << "==== Creating Triangle ====" << std::endl;
	Polygon* polygon1 = new Triangle;
	
	std::cout << "==== Creating Square ====" << std::endl;
	Polygon* polygon2 = new Square;
	
	// Delete the objects
	std::cout << "==== Deleting Triangle ====" << std::endl;
	delete polygon1;
	
	std::cout << "==== Deleting Square ====" << std::endl;
	delete polygon2;
	
	return 0;
}
```

And the output is...

```
==== Creating Triangle ====
Polygon created
Triangle created
==== Creating Square ====
Polygon created
Square created
==== Deleting Triangle ====
Triangle destroyed
Polygon destroyed
==== Deleting Square ====
Square destroyed
Polygon destroyed
```

Have you noticed the pattern?

The program starts by invoking the constructor method of Polygon, followed by the constructor method of Triangle. The same sequence occurs with Square. However, when it comes to deallocating the allocated memory, the order is reversed - the destructor of the child class is invoked first, followed by the destructor of the parent class.

***IMPORTANT NOTE:** The parent class must have a virtual destructor; otherwise, it will not be called after deleting the object of the child class, resulting in a memory leak.*

## 7. Abstract classes and interfaces

With all that we have learned so far, we can utilize inheritance to define abstract classes and interfaces.

An abstract class is a class type that represents an entity with behavior that is challenging to implement. It contains virtual member functions that may or may not be overridden in the derived classes. It serves as a foundational structure, providing a basic framework for the derived classes to specialize the behavior of the parent class.

On the other hand, an interface is a class that relies entirely on pure virtual functions. Its purpose is to define a behavior, which is a set of related public, pure virtual member functions, that another class must inherit and define. In doing so, it establishes a contract between itself and the derived class.

Let's apply these concepts to the previous example:

```cpp
// Section in progress...
```

## Final notes

This article was created by Facundo Martínez © 2023. It is licensed under CC BY-NC-SA 4.0

If you have found it beneficial, kindly consider [supporting me on Ko-Fi](https://ko-fi.com/biocoder). Your contribution will assist me in creating more high-quality free content for the benefit of all. 

# Inheritance

## 1. Introduction

Inheritance can be defined as a mechanism that lets you use a class as the backbone of a new class that derives from it. This means that the new class will inherit the behaviour of the parent class. The advantages of inheritance include:

- Code reusability, which saves time and effort.
- Allows to extend the behaviour of a class, since the child class inherits both the behaviour and attributes of the parent class.
- Flexibility and easier maintenance by inheriting from abstract classes (we will see more about this later on).

## 2. Base class and derived classes

In the context of Object-Oriented Programming, a base class is that which serves as the backbone of the classes which derive from it. Suppose we have a class that defines the basic structure of every car in existence. We know that every car, regardless of its brand, has certain characteristics that repeat across all models - four wheels, three pedals, one license plate ID... and the list goes on. We also know that a car engine can be started and turned off, and that we can know if a car is running or not. How can we write that in real code?

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

***Note:** I have defined inline methods for the sake of simplicity. When you work on a real project, you should separate the declaration of the class from the implementation of its methods in a separate source file.*

Okay, now we have a base class. But what if I want to define a class that lets me take into account the car brand? Fortunately, we can do that. We will define a new class that defines a specific brand, let's say, Toyota:

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

We want to test the following:

1. Did Toyota inherit the public methods from Car?
2. Can Toyota access the protected attribute present in Car?

Let's run this script:

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

Success! In the previous example, we have created a child class without any problem. In this case, we have used public inheritance, but what would happen if we used private or protected inheritance?

1. **Private inheritance:** Both public and protected members from Car would be transformed into private members in Toyota.
2. **Protected inheritance:** Both public and protected members from Car would be transformed into protected members in Toyota.

Keep that in mind when you decide which type of inheritance you wish to apply.

## 4. Function override in class inheritance

When we establish a class hierarchy, sometimes we will need to define parent classes which methods will not be implemented, or methods which implementations are prone to change in a child class. This is known as *function override*, and has many uses in C++. How do we know which functions can be overridden? There are three types of member functions that can be present in a class:

1. **Pure virtual functions:** classes which implementation is not defined in a class, and therefore override must take place. They usually look like this:

`virtual void myFunction() = 0;`
2. **Virtual functions:** functions that can be overridden, but that can also possess a specific implementation. They usually look like this:

`virtual void myFunction() { // Implementation... }`
3. **Normal functions:** your standard, non-virtual functions that you probably know already. They look like this:

`void myFunction() { // Implementation... }`

When you redefine an inherited function body in a child class, you must use the keyword `override`. 


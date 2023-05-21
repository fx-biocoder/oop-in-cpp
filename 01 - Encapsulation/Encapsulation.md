# Encapsulation

## 1. Introduction

Encapsulation can be defined as the process of storing attributes and methods into a specific container called an object. This results in a separation between how the objects behaves internally, and the way its information is accessed and used by other components of the system.

Different programming languages have different approaches to encapsulating data. In the case of C++, the data members and member functions of a class can be categorized into three differents access modifiers - public (anyone can interact with these members), private (the members can only be accessed by the object itself) and protected (the members can only be accessed by the object itself and the objects that belong to a child class).

## 2. An example

Let me provide you with an example. Suppose we have a class that represents the basic structure of a human person. For the sake of simplicity, let's limit the definition to three fundamental characteristics - age, name and gender. Age, name and gender will be defined as private attributes. The class will have a constructor method (one that is called when we want to create a Person object) and a destructor method (one that deletes the person once the program is closed). These methods are public. The class will also have three additional public methods that are used to retrieve the age, name and gender of the person. Lastly, we have a protected attribute called "protectedString" (we will ignore this for the moment, I don't want to spoil "Inheritance"):

```cpp
#include <string>

class Person
{
private:
	std::string personName;				// Name
	int personAge;						// Age
	std::string personGender;			// Gender
public:
	Person(std::string name, int age, std::string gender)
	{
		// We pass the constructor parameters to the private members
		this->personName = name;
		this->personAge = age;
		this->personGender = gender;
	}
	~Person() {}
	int getPersonAge() { return this->personAge; }
	std::string getPersonName() { return this->personName; }
	std::string getPersonGender() { return this->personGender; }
protected:
	std::string protectedString = "can be accessed by child class";
};
```

Now that we have defined our Person class, let's define a child class that inherits from Person:

```cpp
class Worker : public Person 
{
	private:
		std::string personName;
		int personAge;
		std::string personGender;
	public:
		Worker(std::string name, int age, std::string gender)
		{
			// We pass the constructor parameters to the private members
			this->personName = name;
			this->personAge = age;
			this->personGender = gender;
		}
		~Worker() {}
		std::string getProtectedString() { return protectedString; }
};
```
As you can see above, you do not need to define the public methods that were present in Person, since Worker has already inherited them. You will still need to define the necessary private attributes to access them. Let's see what happens when we try to run the following program:

```cpp
int main()
{
	// Create a man named Edward who's 25 years old
	Person p1("Edward", 25, "Male");

	// Let's access his name and age
	std::cout << "Hello, I am " << p1.getPersonName() << " and I'm " << p1.getPersonAge() << " years old." << std::endl;

	// Now, let's create a female worker that inherits from the class Person
	Worker w1("Carla", 19, "Female");
	
	// Let's see if we can access Person's protected string through Carla
	std::cout << "Protected string: " << w1.getProtectedString();

	return 0;
}
```

This is the output:

```
Hello, I am Edward and I'm 25 years old.
Protected string: can be accessed by child class
```

Success! We have been able to create a Person object, access its private attributes through its public methods, and access its protected attribute through a child class (Worker).

What would happen if we tried to access a private attribute by calling it directly? Let's see:

```cpp
int main()
{
	// Create a man named Edward who's 25 years old
	Person p1("Edward", 25, "Male");

	// Let's access his name
	std::cout << p1.personName << std::endl; // Error!
	
	// Let's access its protected attribute
	std::cout << p1.protectedString << std::endl; // Error!
	
	return 0;
}
```

This code will throw a compiler error, because we're trying to access data members that are not accessible from outside of the class.

## 3. Important notes

- All class members are private by default. If you do not specify an access modifier, the compiler will assume you have defined a private class member. 
- To handle private data members, you must define getter/setter public methods. These are methods that "get" and "set" the values that correspond to private attributes. It's common practice to name them as "getX()" and "setX()" (X being the attribute you need to get/set)
- As you could see, my getter methods contain the keyword "this". It is a special type of pointer that refers to the class instance that is being worked on. In this case, "this" points to the memory address of an object that belongs to the Person class. 

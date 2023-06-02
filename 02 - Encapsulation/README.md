# Encapsulation

## 1. Introduction

Encapsulation can be defined as the process of encapsulating attributes and methods within a specific container known as an object. This creates a separation between the internal behavior of the object and the manner in which its information is accessed and utilized by other components of the system.

Various programming languages adopt different approaches to data encapsulation. In the case of C++, the data members and member functions of a class can be classified into three distinct access modifiers: public (allowing any entity to interact with these members), private (restricting access to only the object itself), and protected (permitting access to the object itself and other objects that belong to a derived class).

## 2. An example

Let me provide you with an example. Consider a class that represents the basic structure of a human person. For simplicity, let's focus on three fundamental characteristics: age, name, and gender. These attributes, age, name, and gender, will be defined as private within the class. Additionally, the class will include a constructor method (used to create a Person object) and a destructor method (used to delete the person when the program is closed), both of which are public. Furthermore, the class will feature three additional public methods that allow retrieval of the person's age, name, and gender. Lastly, we have a protected attribute named "protectedString".

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

Now that we have defined our Person class, let's proceed to define a child class that inherits from Person:

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

As you can observe from the code above, there is no need to redefine the public methods that were already present in the Person class since the Worker class inherits them. However, you will still need to define the appropriate private attributes to access them within the Worker class. Now, let's examine what happens when we attempt to execute the following program:

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

Success! We have successfully created a Person object, accessed its private attributes through its public methods, and accessed its protected attribute through a child class (Worker).

Now, let's explore what would happen if we attempted to directly access a private attribute by calling it. Let's examine the outcome:

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

This code will result in a compiler error because we are attempting to access data members that are not accessible from outside of the class. Private attributes cannot be accessed directly from outside the class, hence the compiler error will be thrown.

## 3. Important notes

- By default, all class members are private. If you do not specify an access modifier, the compiler assumes that you have defined a private class member.
- To handle private data members, you need to define public getter and setter methods. These methods are responsible for "getting" and "setting" the values of private attributes. It is a common convention to name them as "getX()" and "setX()" (where X represents the attribute you want to get or set).
- As you observed, the getter methods in the example code use the keyword "this". "this" is a special pointer that refers to the instance of the class currently being operated on. In this case, "this" points to the memory address of an object belonging to the Person class.


## Final notes

This article was created by Facundo Martínez © 2023. It is licensed under CC BY-NC-SA 4.0

I love creating free content for everyone. If my articles and repos were useful to you, please consider supporting me on Github Sponsors, Ko-Fi or PayPal. It would be of great help and I would really appreciate it!

[![Github-sponsors](https://img.shields.io/badge/sponsor-30363D?style=for-the-badge&logo=GitHub-Sponsors&logoColor=#EA4AAA)](https://github.com/sponsors/fx-biocoder) [![Ko-Fi](https://img.shields.io/badge/Ko--fi-F16061?style=for-the-badge&logo=ko-fi&logoColor=white)](https://ko-fi.com/biocoder) [![PayPal](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://paypal.me/facumartinez680)

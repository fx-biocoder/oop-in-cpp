# Polymorphism

## 1. Introduction

Polymorphism is a fundamental concept in Object-Oriented Programming that enables us to alter the implementation of an operator, function, or class based on its context. While it may be challenging, I assure you that you will gain a better understanding of Polymorphism once we're done. There are two types of polymorphism:

1. Static polymorphism, also known as static linking, occurs during compile-time when your program is being compiled before execution. Static polymorphism can be achieved through methods such as operator overloading or function overloading, allowing operators or functions to have different implementations.
2. Dynamic polymorphism, also known as dynamic linking, occurs during runtime and is achieved through inheritance and virtual functions. It enables the use of a base-class pointer or reference to point to an object of a derived class and call the appropriate implementation of a virtual function during runtime.


## 2. Virtual functions

To delve into a more comprehensive explanation of virtual functions, please click here.

## 3. Inheritance and polymorphism

We have covered inheritance in the previous section. These two principles are closely intertwined, as polymorphism is typically achieved through inheritance and the use of pointers or references to a base class.

Allow me to provide you with an example:

```cpp
class BaseClass
{
	public:
		BaseClass() = default;
		~BaseClass() = default;
		virtual void myMethod() = 0;
};

class DerivedClass : public BaseClass
{
	public:
		DerivedClass() = default;
		~DerivedClass() = default;
		void myMethod() override { std::cout << "Method was overridden" << std::endl; }
};

int main()
{
	BaseClass* myPointer = new DerivedClass;
	myPointer->myMethod();
}
```

Output:

```
Method was overridden
```

In the previous example, we have defined a class that inherits from a base class, and it overrides its public method `myMethod()`. Then, we have used a base class pointer to create a derived class object. What's the purpose of this? By defining a base class pointer, we are using dynamic memory allocation and ensuring that we will only access the virtual method through the base class. This has many uses that will not be covered in this tutorial (yet).

## Final notes

This article was created by Facundo Martínez © 2023. It is licensed under CC BY-NC-SA 4.0

If you have found it beneficial, kindly consider [supporting me on Ko-Fi](https://ko-fi.com/biocoder). Your contribution will assist me in creating more high-quality free content for the benefit of all.

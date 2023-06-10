# Polymorphism

## 1. Introduction

Polymorphism is a fundamental concept in Object-Oriented programming that enables us to alter the implementation of an operator, function or class based on its context. While it may be challenging, I assure you that you will gain a better understanding of Polymorphism once we're done. There are two types of polymorphism:

1. Static polymorphism, also known as static binding, occurs during compile-time when your program is being compiled before execution. Static polymorphism can be achieved through methods such as operator overloading or function overloading, allowing operators or functions to have different implementations.
2. Dynamic polymorphism, also known as dynamic binding, occurs during runtime and is achieved through inheritance and virtual functions. It enables the use of a base-class pointer or reference to point to an object of a derived class and call the appropriate implementation of a virtual function during runtime.

## 2. Virtual functions

A virtual function can be defined as a member function that is declared in a class, and is to be redefined by a child class (this process is also known as function override). For each child class that inherits this member function, we could have one implementation of said virtual function, which means this function can take many forms depending on its context. Due to their particular nature, virtual functions are used for runtime polymorphism.

In the previous chapter, we have discussed the behaviour of virtual functions. If you need to revisit this topic, please follow these links:

- [Read: Function override in class inheritance](https://github.com/fx-biocoder/oop-in-cpp/tree/main/03%20-%20Inheritance#4-function-override-in-class-inheritance)
- [Read: Resolving virtual functions with dynamic binding in the context of class inheritance](https://github.com/fx-biocoder/oop-in-cpp/tree/main/03%20-%20Inheritance#5-resolving-virtual-functions-with-dynamic-binding-in-the-context-of-class-inheritance)

## 3. Inheritance and polymorphism

Inheritance and polymorphism are closely intertwined, as the latter is typically achieved through inheritance and the use of pointers or references to a base class.

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

In the previous example, we have defined a class that inherits from a base class, and it overrides its public method `myMethod()`. Then, we have used a base class pointer to create a derived class object. What's the purpose of this? By defining a base class pointer, we are using dynamic memory allocation and ensuring that we will only access the virtual method through the base class.

## 4. Virtual tables (vtables) in C++

A virtual table, commonly known as a "vtable," is a mechanism utilized for dynamic binding, also referred to as dynamic dispatch, of virtual functions.

In the previous example, we encountered a class that declares a virtual function. As a result, the compiler generates a vtable specific to that class. Additionally, each object of the class possesses a concealed pointer, known as the vpointer, which directs to its respective vtable.

The vtable stores pointers to the virtual functions of the class in the order of their declaration. When a derived class overrides a virtual function, it substitutes the corresponding pointer in the vtable with a pointer to its own implementation. Consequently, even when working with objects through a base class pointer or reference, the virtual function invocation will execute the implementation from the derived class. So, vtables enable the attainment of dynamic polymorphism and ensuring the invocation of the correct virtual function implementation.

## Final notes

This article was created by Facundo Martínez © 2023. It is licensed under CC BY-NC-SA 4.0

I love creating free content for everyone. If my articles and repos were useful to you, please consider supporting me on Github Sponsors, Ko-Fi or PayPal. It would be of great help and I would really appreciate it!

[![Github-sponsors](https://img.shields.io/badge/sponsor-30363D?style=for-the-badge&logo=GitHub-Sponsors&logoColor=#EA4AAA)](https://github.com/sponsors/fx-biocoder) [![Ko-Fi](https://img.shields.io/badge/Ko--fi-F16061?style=for-the-badge&logo=ko-fi&logoColor=white)](https://ko-fi.com/biocoder) [![PayPal](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://paypal.me/facumartinez680)

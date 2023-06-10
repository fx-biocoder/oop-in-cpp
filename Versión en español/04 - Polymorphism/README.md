# Polimorfismo

## 1. Introducción

El polimorfismo es un concepto fundamental en la programación orientada a objetos que nos permite alterar la implementación de un operador, función o clase en función de su contexto. Aunque puede ser desafiante, te aseguro que comprenderás mejor el polimorfismo una vez que terminemos. Hay dos tipos de polimorfismo:

1. Polimorfismo estático, también conocido como enlace estátic. Ocurre durante la compilación de tu programa antes de su ejecución. El polimorfismo estático se logra mediante métodos como la sobrecarga de operadores o la sobrecarga de funciones, lo que permite que los operadores o funciones tengan diferentes implementaciones.
2. Polimorfismo dinámico, también conocido como enlace dinámico. Ocurre durante la ejecución del programa y se logra mediante la herencia y las funciones virtuales. Permite utilizar un puntero o referencia a la clase base para apuntar a un objeto de una clase derivada y llamar a la implementación apropiada de una función virtual durante la ejecución del programa.


## 2. Funciones virtuales

Una función virtual puede ser definida como una función miembro declarada en una clase y que debe ser redefinida por una clase hija (este proceso también es conocido como sobreescritura de función). Para cada clase hija que herede esta función miembro, podríamos tener una implementación de dicha función virtual, lo que significa que esta función puede tomar muchas formas dependiendo de su contexto. Debido a su naturaleza particular, las funciones virtuales se utilizan para lograr el polimorfismo en tiempo de ejecución.

En el capítulo anterior, hemos discutido el comportamiento de las funciones virtuales. Si necesitas revisar este tema, por favor sigue estos enlaces:

- [Leer: Anulación de funciones en la herencia de clases](https://github.com/fx-biocoder/oop-in-cpp/tree/main/Versi%C3%B3n%20en%20espa%C3%B1ol/04%20-%20Polymorphism)
- [Leer: Resolución de funciones virtuales con enlace dinámico en el contexto de la herencia de clases](https://github.com/fx-biocoder/oop-in-cpp/tree/main/Versi%C3%B3n%20en%20espa%C3%B1ol/04%20-%20Polymorphism)

## 3. Herencia y polimorfismo

La herencia y el polimorfismo están estrechamente relacionados, ya que este último se logra típicamente a través de la herencia y el uso de punteros o referencias a una clase base.

Permíteme proporcionarte un ejemplo:

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

Salida de consola:

```
Method was overridden
```

En el ejemplo anterior, hemos definido una clase que hereda de una clase base y sobrescribe su método público `myMethod()`. Luego, hemos utilizado un puntero de clase base para crear un objeto de la clase derivada. ¿Cuál es el propósito de esto? Al definir un puntero de clase base, estamos utilizando asignación de memoria dinámica y asegurándonos de que solo accederemos al método virtual a través de la clase base.

## 4. Tablas virtuales (vtables) en C++

Una tabla virtual, comúnmente conocida como "vtable" o "tabla de funciones virtuales", es un mecanismo utilizado para el enlace dinámico, también conocido como despacho dinámico, de funciones virtuales.

En el ejemplo anterior, nos encontramos con una clase que declara una función virtual. Como resultado, el compilador genera una vtable específica para esa clase. Además, cada objeto de la clase posee un puntero oculto, conocido como vpointer o puntero a vtable, que apunta a su vtable respectiva.

La vtable almacena punteros a las funciones virtuales de la clase en el orden de su declaración. Cuando una clase derivada sobrescribe una función virtual, sustituye el puntero correspondiente en la vtable con un puntero a su propia implementación. En consecuencia, incluso cuando se trabaja con objetos a través de un puntero o referencia a la clase base, la invocación de la función virtual ejecutará la implementación de la clase derivada. Así, las vtables permiten lograr el polimorfismo dinámico y aseguran la invocación de la implementación correcta de la función virtual.


## Notas finales

Este artículo fue creado por Facundo Martínez © 2023. Está licenciado bajo CC BY-NC-SA 4.0.

Me encanta crear contenido gratuito para todos. Si mis artículos y repositorios te han sido útiles, considera apoyarme en Github Sponsors, Ko-Fi o PayPal. Sería de gran ayuda y lo apreciaría mucho.

[![Github-sponsors](https://img.shields.io/badge/sponsor-30363D?style=for-the-badge&logo=GitHub-Sponsors&logoColor=#EA4AAA)](https://github.com/sponsors/fx-biocoder) [![Ko-Fi](https://img.shields.io/badge/Ko--fi-F16061?style=for-the-badge&logo=ko-fi&logoColor=white)](https://ko-fi.com/biocoder) [![PayPal](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://paypal.me/facumartinez680)


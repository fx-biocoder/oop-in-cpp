# Herencia

## 1. Introducción


La herencia se puede definir como un mecanismo que te permite utilizar una clase como base para una nueva clase derivada de ella. Esto implica que la nueva clase hereda el comportamiento de la clase padre. Las ventajas de la herencia son las siguientes:

- Reutilización de código, lo que conlleva ahorro de tiempo y esfuerzo.
- La capacidad de ampliar el comportamiento de una clase, ya que la clase hija hereda tanto el comportamiento como los atributos de la clase padre.
- Flexibilidad y mantenimiento simplificado al heredar de clases abstractas (este tema se explorará más adelante).

## 2. Clase base y clases derivadas

En el contexto de la Programación Orientada a Objetos, una clase base sirve como fundamento para las clases que se derivan de ella. Consideremos una clase que define la estructura fundamental de cualquier automóvil. Sabemos que ciertas características son comunes a todos los modelos de automóviles, independientemente de su marca, como tener cuatro ruedas, tres pedales y una identificación de matrícula. Además, sabemos que se puede encender y apagar el motor de un automóvil, y podemos determinar si un automóvil está en funcionamiento o no. Ahora veamos cómo podemos representar esto en código real:

```cpp
#include <string>
class Car
{
	protected:
		int numberOfWheels = 4;
		int numberOfPedals = 3;
		std::string licensePlate;
		bool isRunning = false;
		std::string transmission = "Manual";

	public:
		// Constructor, destructor
		Car() = default;
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

***Nota:** Por simplicidad, he definido los métodos de forma inline. En un proyecto real, se recomienda separar la declaración de la clase de la implementación de sus métodos en un archivo fuente separado.*

Ahora que tenemos una clase base, consideremos cómo podemos definir una clase que tenga en cuenta la marca del automóvil. Afortunadamente, podemos lograr eso definiendo una nueva clase específica para una marca en particular, como Toyota:

```cpp
#include <string>

class Toyota : public Car
{
	private:
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

Probemos lo siguiente:

1. ¿La clase Toyota heredó los métodos públicos de la clase base Car?
2. ¿Puede la clase Toyota acceder a los atributos protegidos presentes en la clase base Car?

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

La salida es:

```
Car model: Toyota Hilux. Transmission: Manual
Toyota car destroyed
```

## 3. Herencia pública, privada y protegida

¡Genial! En el ejemplo anterior, creamos con éxito una clase hija. En este caso, utilizamos la herencia pública. Sin embargo, vale la pena considerar las implicaciones de utilizar la herencia privada o protegida:

1. **Herencia privada:** En este caso, tanto los miembros públicos como protegidos de la clase base Car se convertirían en miembros privados en la clase Toyota.
2. **Herencia protegida:** En este escenario, tanto los miembros públicos como protegidos de la clase base Car se convertirían en miembros protegidos en la clase Toyota.

Es importante tener en cuenta estos resultados al decidir qué tipo de herencia es apropiada para tu situación específica.

## 4. Anulación (override) de funciones en herencia de clase

Cuando se establece una jerarquía de clases, existen situaciones en las que necesitamos definir clases padre con métodos que no están implementados o es probable que se cambien en las clases hijas. Esto se conoce como anulación de funciones y sirve para diversos propósitos en C++. ¿Cómo determinamos qué funciones se pueden anular? Hay tres tipos de funciones miembro que pueden existir en una clase:

1. **Funciones virtuales puras:** Estas son funciones cuya implementación no se proporciona en la clase base y deben ser anuladas en las clases derivadas. Por lo general, se definen de la siguiente manera:

`virtual void myFunction() = 0;`

2. **Funciones virtuales:** Estas funciones pueden ser anuladas en las clases derivadas, pero también pueden tener su propia implementación específica. Por lo general, se definen de la siguiente manera:

`virtual void myFunction() { // Implementation... }`

3. **Funciones no virtuales:** Estas son funciones regulares sin la palabra clave "virtual", y se comportan como esperarías. Se definen de la siguiente manera:

`void myFunction() { // Implementation... }`

Al entender estos tres tipos de funciones miembro, puedes determinar qué funciones se pueden anular y elegir el enfoque adecuado según tus requisitos.

## 5. Resolviendo funciones virtuales con enlace dinámico en el contexto de la herencia de clases

Entonces, ahora que hemos establecido qué son las funciones virtuales, ¿cómo las implementamos en código real? Consideremos una clase abstracta llamada Polygon (Polígono), de la cual derivamos subclases que representan tipos específicos de polígonos, como triángulos, cuadrados, pentágonos, y así sucesivamente. Veamos cómo podemos traducir esto a código real:

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

Hemos definido una clase abstracta Polygon (Polígono) y dos subclases: Triangle (Triángulo) y Square (Cuadrado). Sin embargo, hay una diferencia en la implementación de la función `typeOfPolygon()` en estas subclases. Ahora, surge la pregunta: si creo un objeto de la clase Polygon, ¿cómo puedo especificar qué implementación utilizar? Permíteme demostrártelo.

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

Y la salida en consola:

```
This is a triangle
This is a square
```
***Nota:** En caso de que te lo estés preguntando, sí, he omitido la salida del constructor/destructor. Lo revisaremos en la siguiente sección.*

Ahora, déjame explicarlo en detalle. He creado dos punteros de tipo `Polygon` que almacenan las direcciones de memoria de dos objetos diferentes pertenecientes a las clases hijas de `Polygon` (si necesitas repasar este tema, puedes consultar mi breve guía de referencia sobre asignación de memoria dinámica para principiantes). Luego, procedí a llamar al método anulado utilizando estos punteros, y cada uno de ellos produjo una salida específica de sus respectivas clases.


## 6. Constructores y destructores en herencia de clase

Hemos visto cómo manejar funciones virtuales con enlace dinámico, pero todavía no estamos seguros del orden en el que se llaman los constructores y destructores durante el tiempo de ejecución. Ejecutemos el siguiente programa:

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

Y la salida es...

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

¿Has notado el patrón?

El programa comienza invocando el método constructor de Polygon, seguido del método constructor de Triangle. La misma secuencia ocurre con Square. Sin embargo, cuando se trata de liberar la memoria asignada, el orden se invierte: se invoca primero el destructor de la clase hija, seguido por el destructor de la clase padre.

***NOTA IMPORTANTE:** La clase padre debe tener un destructor virtual; de lo contrario, no se llamará después de eliminar el objeto de la clase hija, lo que resultará en una fuga de memoria.*

## 7. Clases abstractas e interfaces

Con todo lo que hemos aprendido hasta ahora, podemos utilizar la herencia para definir clases abstractas e interfaces.

Una clase abstracta es un tipo de clase que representa una entidad con un comportamiento difícil de implementar. Contiene funciones miembro virtuales que pueden o no anularse en las clases derivadas. Sirve como una estructura fundamental, proporcionando un marco básico para que las clases derivadas especialicen el comportamiento de la clase padre.

Por otro lado, una interfaz es una clase que se basa completamente en funciones virtuales puras. Su propósito es definir un comportamiento, que es un conjunto de funciones miembro públicas virtuales puras relacionadas, que otra clase debe heredar y definir. Al hacerlo, establece un contrato entre sí misma y la clase derivada.

Apliquemos estos conceptos al ejemplo anterior:

```cpp
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

// Interface
class IPolygon
{
	public:
		IPolygon() = default;
		virtual ~IPolygon() = default;
		virtual int calculateArea() = 0;	// Pure virtual function!
};

// Polygon's child class that also implements the interface
class Square : public Polygon, public IPolygon
{
	private:
		int sideLenght = 5;
	public:
		Square() = default;
		~Square() = default;

		void typeOfPolygon() override { std::cout << "It's a square." << std::endl; }
		int calculateArea() override { return sideLenght * 2; }
};
```


## Notas finales

Este artículo fue creado por Facundo Martínez © 2023. Está licenciado bajo CC BY-NC-SA 4.0

Me encanta crear contenido gratuito para todos. Si mis artículos y repositorios te han sido útiles, por favor considera apoyarme en Github Sponsors, Ko-Fi o PayPal. Sería de gran ayuda y lo apreciaría mucho.

[![Github-sponsors](https://img.shields.io/badge/sponsor-30363D?style=for-the-badge&logo=GitHub-Sponsors&logoColor=#EA4AAA)](https://github.com/sponsors/fx-biocoder) [![Ko-Fi](https://img.shields.io/badge/Ko--fi-F16061?style=for-the-badge&logo=ko-fi&logoColor=white)](https://ko-fi.com/biocoder) [![PayPal](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://paypal.me/facumartinez680)


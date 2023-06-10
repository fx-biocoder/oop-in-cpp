# Abstracción


## 1. Introducción

En el contexto de la Programación Orientada a Objetos, la abstracción puede definirse como las características distintivas de un objeto que lo diferencian de otros tipos de objetos, estableciendo así límites conceptuales entre ellos.

El objetivo principal de la abstracción es permitirnos representar conceptos complejos de manera simplificada, enfatizando los aspectos relevantes mientras se ocultan los detalles internos sobre cómo funciona el objeto.

Por ejemplo, consideremos la tarea de conducir un automóvil. Usted está consciente de los siguientes pasos básicos:

1. Sentarse en el asiento del conductor.
2. Abrochar el cinturón de seguridad.
3. Colocar la palanca de cambios en punto muerto.
4. Insertar la llave y encender el motor.
5. Presionar el embrague, cambiar de marcha y permitir que el coche se mueva.

Aunque estos procesos pueden parecer sencillos, en realidad involucran mecanismos mucho más complejos. El asiento del conductor está firmemente sujeto al piso del automóvil de una manera específica, el cinturón de seguridad incorpora un mecanismo especializado para garantizar un ajuste seguro, el sistema de cambios posee un mecanismo complejo que puede resultar desconocido, la llave tiene una configuración específica que activa un circuito electrónico responsable de encender el motor, y así sucesivamente.

Como conductor, no se requiere que tengas un conocimiento profundo de estos detalles para operar un automóvil. En general, puedes simplemente darlos por sentados.

## 2. Clases y objetos

Podemos definir una clase como un concepto que especifica las características compartidas de un grupo de objetos. Por otro lado, un objeto se refiere a cualquier entidad asociada con una clase en particular. En C++, al declarar clases y objetos, debemos seguir una sintaxis específica, que es la siguiente:

```cpp
// Declarar una clase
class ClassName
{
	private:
		// Lista de miembros de clase privados...
	public:
		// Lista de miembros de clase públicos...
	protected:
		// Lista de miembros de clase protegidos...
};

int main()
{
	// Crear objeto a partir de una clase
	ClassName objectName;
	
	// Crear otro objeto a partir de la misma clase
	ClassName anotherObject;
	
	return 0;
}
```

Como puedes observar, podemos instanciar una clase (es decir, crear un objeto) simplemente invocando el nombre de la clase seguido del nombre deseado para el objeto. Además, tenemos la flexibilidad de crear múltiples instancias según sea necesario para asegurar la funcionalidad de nuestro programa.


## 3. Atributos y métodos

Cuando definimos el comportamiento de una clase, utilizamos dos tipos distintos de componentes:

- Atributos: Estos abarcan constantes y/o variables que establecen las características fundamentales de un objeto.

- Métodos: Estas son funciones que delimitan las acciones típicamente realizadas por un objeto que pertenece a la clase.

Examinemos estos componentes dentro de un marco contextual:

```cpp
#include <iostream>

class ClassName
{
	public:
		int integerVariable = 4;
		bool booleanVariable = true;
		void objectMethod() { std::cout << "I have called a method" << std::endl; }
};

int main()
{
	ClassName myObject;
	
	// Access its variables and print them in console
	std::cout << myObject.integerVariable << std::endl;
	std::cout << myObject.booleanVariable << std::endl;
	
	// Call the method
	myObject.objectMethod();
	
	return 0;	
}
```

La salida generada al ejecutar este script es:

```
4
true
I have called a method
```

Como puedes observar, puedo acceder a los atributos y métodos del objeto haciendo referencia al nombre del objeto seguido de un punto y el nombre del atributo o método deseado.

***Nota:** Para lograr esto, los atributos y métodos deben declararse como públicos. No es posible acceder directamente a miembros privados llamándolos. Se pueden encontrar más detalles sobre esto en el tema de la Encapsulación.*

## 4. Abstracción de datos

Como se mencionó anteriormente, existen numerosos detalles internos de un objeto que desconocemos y que no necesitamos conocer. Esto es intencional y cumple un propósito valioso. Considera el escenario en el que tuviéramos que poseer un conocimiento detallado de los aspectos específicos del motor de un automóvil solo para operar el vehículo, solo los ingenieros serían capaces de conducir. Además, la abstracción de datos opera de manera que protege contra modificaciones no deseadas en las características internas de una clase, evitando cambios no deseados o indeseables.

No obstante, sería ventajoso si pudiéramos acceder a estos detalles internos sin comprometer el funcionamiento adecuado de un objeto. Permíteme proporcionar un ejemplo:

```cpp
#include <iostream>

class ClassName
{
	private:
		int privateVariable = 10;
		
	public:
		// Access the private
		int classMethod() { return privateVariable; }
};

int main()
{
	// Create an object from a class
	ClassName myObject;
	
	// Access and store the private attribute
	int objectVariable = myObject.classMethod();
	
	// Print it
	std::cout << objectVariable << std::endl; // Prints '10' in console
	
	return 0;
}
```

¡Genial! Hemos obtenido exitosamente acceso a los detalles internos de un objeto. En la práctica, logramos esto utilizando lo que comúnmente se conoce como *getters* y *setters* - métodos que recuperan y modifican valores de atributos privados y protegidos de la clase. Permíteme demostrarte:

```cpp
class ClassName
{
	private:
		int privateVariable = 10;
		
	public:
		// Getter
		int getPrivateVariable() { return privateVariable; }
		
		// Setter
		void setPrivateVariable(int newValue) { privateVariable = newValue; }
};
```

El método getter recupera el valor de un atributo privado, mientras que el método setter actualiza el atributo privado con un nuevo valor pasado como parámetro a la función. Esta es la funcionalidad fundamental de los getters y setters.

## 5. Constructores y destructores

El enfoque actual que hemos utilizado para definir objetos no nos permite establecer dinámicamente su estado inicial tan pronto como creamos una instancia de una clase. ¿Y si quisiera crear un objeto donde `privateVariable` se establezca inicialmente en 8 en lugar de 10?

Si bien es posible crear el objeto y luego usar `myObject.setPrivateVariable(8)`, se vuelve ineficiente cuando se trata de múltiples atributos privados. Por ejemplo, si el objeto tiene cinco atributos privados, ¿necesitaría llamar a cinco setters? ¿Y si necesito configurar diez o incluso cien atributos? Este enfoque carece de eficiencia. Es precisamente por eso que tenemos un método público especial llamado constructor.

Además, tenemos otro método especial llamado destructor. Cuando creamos un objeto, ocupa una porción de memoria. Una vez que el programa termina su ejecución, se invoca el método destructor para liberar la memoria utilizada por el objeto. La gestión de memoria puede ser un tema complejo y recomiendo leer más al respecto para obtener una mejor comprensión.

Permíteme mostrarte la sintaxis correcta para estos métodos:

```cpp
class ClassName
{
	private:
		int integerVariable;
		bool booleanVariable;
	public:
		// Constructor method
		ClassName()
		{
			this->integerVariable = 10;	// Setting the integer to 10
			this->booleanVariable = true;	// Setting the boolean to true
		}
	
		// Destructor method
		~ClassName() = default; // I'm using the default destructor generated by the compiler
};
```

¡Genial! Hemos utilizado exitosamente un constructor y hemos cubierto la implementación de un método destructor. Si bien esto es fantástico, hagámoslo un poco más complejo. Hasta ahora, hemos pasado valores codificados en el constructor, pero ¿qué pasa si deseamos tener la flexibilidad de proporcionar diferentes valores según nuestras necesidades? En esos casos, podemos pasar estos valores como parámetros al constructor. Permíteme mostrarte:

```cpp
// Constructor
ClassName(int integer, bool boolean)
{
	this->integerVariable = integer;
	this->booleanVariable = boolean;
}
```

## 6. Herencia y Polimorfismo como conceptos avanzados relacionados con la Abstracción

Hasta ahora, hemos proporcionado una breve introducción a la Programación Orientada a Objetos. La abstracción se vuelve más compleja a medida que se entrelaza con otros conceptos como la herencia y el polimorfismo.

La herencia permite la creación de jerarquías de clases, facilitando el compartir comportamientos comunes entre las clases. Por otro lado, el polimorfismo te permite tratar objetos de clases derivadas como objetos de su propia clase base. Para obtener más información sobre la herencia y el polimorfismo, puedes consultar recursos disponibles [aquí](https://github.com/fx-biocoder/oop-in-cpp/tree/main/03%20-%20Inheritance) y [aquí](https://github.com/fx-biocoder/oop-in-cpp/tree/main/04%20-%20Polymorphism).

Eso concluye nuestra discusión por ahora. ¡Confío en que hayas encontrado este artículo informativo y útil!


## Notas finales

Este artículo fue creado por Facundo Martínez © 2023. Está licenciado bajo CC BY-NC-SA 4.0.

Me encanta crear contenido gratuito para todos. Si mis artículos y repositorios te resultaron útiles, considera apoyarme en Github Sponsors, Ko-Fi o PayPal. Sería de gran ayuda y lo apreciaría mucho.

[![Github-sponsors](https://img.shields.io/badge/sponsor-30363D?style=for-the-badge&logo=GitHub-Sponsors&logoColor=#EA4AAA)](https://github.com/sponsors/fx-biocoder) [![Ko-Fi](https://img.shields.io/badge/Ko--fi-F16061?style=for-the-badge&logo=ko-fi&logoColor=white)](https://ko-fi.com/biocoder) [![PayPal](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://paypal.me/facumartinez680)



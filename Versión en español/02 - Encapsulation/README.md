# Encapsulación

## 1. Introducción

La encapsulación se puede definir como el proceso de almacenar atributos y métodos dentro de un contenedor específico conocido como objeto. Esto crea una separación entre el comportamiento interno del objeto y la forma en que su información es accedida y utilizada por otros componentes del sistema.

Varios lenguajes de programación adoptan enfoques diferentes para la encapsulación de datos. En el caso de C++, los miembros de datos y funciones miembro de una clase se pueden clasificar en tres modificadores de acceso distintos: público (permitiendo que cualquier entidad interactúe con estos miembros), privado (restringiendo el acceso solo al objeto en sí) y protegido (permitiendo el acceso al objeto en sí y a otros objetos que pertenecen a una clase derivada).


## 2. Un ejemplo

Permíteme proporcionarte un ejemplo. Considera una clase que representa la estructura básica de una persona humana. Para simplificar, centrémonos en tres características fundamentales: edad, nombre y género. Estos atributos, edad, nombre y género, se definirán como privados dentro de la clase. Además, la clase incluirá un método constructor (utilizado para crear un objeto Persona) y un método destructor (utilizado para eliminar a la persona cuando se cierre el programa), ambos públicos. Además, la clase contará con tres métodos públicos adicionales que permiten obtener la edad, el nombre y el género de la persona. Por último, tenemos un atributo protegido llamado "protectedString".

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

Ahora que hemos definido nuestra clase Person, procedamos a definir una clase hija que hereda de Person:

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

Como puedes observar en el código anterior, no es necesario volver a definir los métodos públicos que ya estaban presentes en la clase Person, ya que la clase Worker los hereda. Sin embargo, aún necesitarás definir los atributos privados apropiados para acceder a ellos dentro de la clase Worker. Ahora, examinemos qué sucede cuando intentamos ejecutar el siguiente programa:

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

Esta es la salida del programa:

```
Hello, I am Edward and I'm 25 years old.
Protected string: can be accessed by child class
```


¡Genial! Hemos creado con éxito un objeto Person, accedido a sus atributos privados a través de sus métodos públicos y accedido a su atributo protegido a través de una clase hija (Worker).

Ahora, exploremos qué sucedería si intentáramos acceder directamente a un atributo privado llamándolo. Examinemos el resultado:

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

Este código dará como resultado un error del compilador porque estamos intentando acceder a miembros de datos que no son accesibles desde fuera de la clase. Los atributos privados no pueden ser accedidos directamente desde fuera de la clase, por lo tanto, se lanzará un error del compilador.

## 3. Notas importantes

- Por defecto, todos los miembros de una clase son privados. Si no especificas un modificador de acceso, el compilador asume que has definido un miembro de clase privado.
- Para manejar los miembros de datos privados, necesitas definir métodos getter y setter públicos. Estos métodos son responsables de "obtener" y "establecer" los valores de los atributos privados. Es una convención común nombrarlos como "getX()" y "setX()" (donde X representa el atributo que deseas obtener o establecer).
- Como observaste, los métodos getter en el código de ejemplo utilizan la palabra clave "this"; "this" es un puntero especial que se refiere a la instancia de la clase en la que se está operando actualmente. En este caso, "this" apunta a la dirección de memoria de un objeto que pertenece a la clase Persona.


## Notas finales

Este artículo fue creado por Facundo Martínez © 2023. Está licenciado bajo CC BY-NC-SA 4.0.

Me encanta crear contenido gratuito para todos. Si mis artículos y repositorios te han sido útiles, considera apoyarme en Github Sponsors, Ko-Fi o PayPal. Sería de gran ayuda y realmente lo apreciaría.

[![Github-sponsors](https://img.shields.io/badge/sponsor-30363D?style=for-the-badge&logo=GitHub-Sponsors&logoColor=#EA4AAA)](https://github.com/sponsors/fx-biocoder) [![Ko-Fi](https://img.shields.io/badge/Ko--fi-F16061?style=for-the-badge&logo=ko-fi&logoColor=white)](https://ko-fi.com/biocoder) [![PayPal](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://paypal.me/facumartinez680)


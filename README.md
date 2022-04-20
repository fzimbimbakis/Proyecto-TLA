[![✗](https://img.shields.io/badge/Release-v0.1.0-ffb600.svg?style=for-the-badge)](https://github.com/fzimbimbakis/Proyecto-TLA)

# Compilador Flex/Bison

Un compilador vacío construido con Flex y Bison.

## Requerimientos

Para construir el compilador, se requieren las siguientes dependencias:

* [Bison v3.8.2](https://www.gnu.org/software/bison/)
* [CMake v3.22.2](https://cmake.org/)
* [Flex v2.6.4](https://github.com/westes/flex)
* [GCC v11.1.0](https://gcc.gnu.org/)
* [Make v4.3](https://www.gnu.org/software/make/)

Si en lugar de trabajar con un entorno _Linux_, se está construyendo el proyecto sobre un entorno _Microsoft Windows_, se debe instalar _Microsoft Visual Studio 2022_ con las extensiones para desarrollar aplicaciones en _C/C++_, así como también las herramientas requeridas, con excepción del compilador _GCC_ y la herramienta _Make_.

## Construcción y ejecución de tests

Se utiliza el script run.sh que puede recibir los siguientes argumentos (en el llamado hay que respetar el orden de esta lista):

###Ayuda
* --help: Muestra los posibles argumentos para el run.sh.

###Construcción
* --cmake: Para correr el Cmake y Make.
* --make: Para correr el Make

###Tests
* --all: Correr todos los tests en la carpeta tests.
* TEST_#: Nombre de archivo que esta en la carpeta tests.

```bash
./run.sh [--cmake] [--make] [--all] [TEST_1 TEST_2 ...]
```

El run.sh no toma en cuenta que:
En un entorno _Microsoft Windows_, en lugar de ejecutar el comando `make`, se deberá abrir la solución generada `bin/Compiler.sln` con el IDE _Microsoft Visual Studio 2022_. Los ejecutables que este sistema construye se depositan dentro del directorio `bin/Debug` y `bin/Release` según corresponda.

###Cheat sheet
Construcción y ejecución de todos los tests
```bash
./run.sh --cmake --all
```

##Información de tests disponibles

###Tests aceptados
* prueba1: Crear una clase con métodos y atributos, y utilizarlos en la función main.
* prueba2: Crear una superclase y una subclase, y utilizar los métodos de ambas desde el mismo objeto.
* prueba3: Crear instancias de cada tipo y de alguna clase, y asignarles valores a todos.
* prueba4: Crear una clase que genere el siguiente número de Fibonacci cada vez que se lo solicita.
* prueba5: Crear un algoritmo que utilice saltos condicionales y bucles/iteraciones.
* prueba6: Un programa que ordene una lista de objetos “Persona” por DNI y luego por nombre.
* prueba7: Un programa que lea una lista de números de la entrada, los modifique y los imprima en la salida.
* prueba8: Un programa que crea objetos de una clase cuyos atributos son de otra clase.
* prueba9: Crear una superclase cuya subclase redefine uno de sus métodos.
* prueba10: Un programa que utilice todos los operadores aritméticos y lógicos.

###Tests rechazados ( !!! Los tests del 12 al 15 se rechazan en el back-end. Por lo tanto, hasta el momento son aceptados )
* prueba11: Un programa que intente crear una clase heredando de múltiples clases.
* prueba12: Un programa que cree 2 objetos de diferente clase e intente asignar uno en el otro.
* prueba13: Un programa que intente llamar a un método que no posee.
* prueba14: Un programa que llame a un método/constructor con una cantidad errónea de parámetros.
* prueba15: Un programa que use variables definidas en otro scope.


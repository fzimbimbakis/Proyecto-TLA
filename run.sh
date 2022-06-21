if [ "$1" = "--help" ]; then
    echo "
    Construcción y ejecución de tests

         Se utiliza el script run.sh que puede recibir los siguientes argumentos (los argumentos deben respetar el orden de esta lista):

         # Ayuda
         * --help: Muestra los posibles argumentos para el run.sh.

         # Construcción
         * --cmake: Para correr el Cmake y Make.
         * --make: Para correr el Make

         # Tests
         * --all: Correr todos los tests en la carpeta tests.
         * TEST_#: Nombre de archivo que esta en la carpeta tests.

         ./run.sh [--cmake] [--make] [--all] [TEST_1 TEST_2 ...]

         El run.sh no toma en cuenta que:
         En un entorno Microsoft Windows, en lugar de ejecutar el comando make, se deberá abrir la solución generada bin/Compiler.sln con el IDE Microsoft Visual Studio 2022. Los ejecutables que este sistema construye se depositan dentro del directorio bin/Debug y bin/Release según corresponda.

         Información de tests disponibles

         Tests aceptados
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

         Tests rechazados ( !!! Los tests del 12 al 15 se rechazan en el back-end. Por lo tanto, hasta el momento son aceptados )
         * prueba11: Un programa que intente crear una clase heredando de múltiples clases.
         * prueba12: Un programa que cree 2 objetos de diferente clase e intente asignar uno en el otro.
         * prueba13: Un programa que intente llamar a un método que no posee.
         * prueba14: Un programa que llame a un método/constructor con una cantidad errónea de parámetros.
         * prueba15: Un programa que use variables definidas en otro scope.
         "
    shift 1
fi
if [ "$1" = "--cmake" ]; then
    rm -r bin;
    cd src/frontend/lexical-analysis;
    rm flex-scanner.c;
    cd ../syntactic-analysis;
    rm bison-parser.c bison-parser.h;
    cd ../../..;
    cmake -S . -B bin;
    cd bin || exit;
    make;
    cd .. || exit;
    shift 1
fi
if [ "$1" = "--make" ]; then
    cd src/frontend/lexical-analysis;
    rm flex-scanner.c;
    cd ../syntactic-analysis;
    rm bison-parser.c bison-parser.h;
    cd ../../..;
    cd bin || exit;
    make;
    cd .. || exit;
    shift 1
fi
if [ "$1" = "--all" ]; then
    for i in {1..15}
    do
    	echo prueba"$i"
          if test -f ./test/accept/prueba"$i"; then
          ./bin/Compiler ./results/prueba"$i".c < ./test/accept/prueba"$i"
          elif test -f ./test/reject/prueba"$i"; then
              ./bin/Compiler ./results/prueba"$i".c < ./test/reject/prueba"$i"
          else
            echo "No existe el test $i"
          fi
          echo -e '\n'
    done
    shift 1
fi
if [ "$1" = "--compile" ]; then
    shift 1
    echo "$1"
              if test -f ./test/accept/"$1"; then
              ./bin/Compiler ./results/"$1".c < ./test/accept/"$1"
              gcc -o ./results/"$1" ./results/"$1".c
              rm ./results/"$1".c
              elif test -f ./test/reject/"$1"; then
                  ./bin/Compiler ./results/"$1".c < ./test/reject/"$1"
                  gcc -o ./results/"$1" ./results/"$1".c
                  rm ./results/"$1".c
              else
                echo "No existe el test $1"
              fi
              echo -e '\n'
fi
if [ "$1" = "--compileall" ]; then
    for i in {1..15}
    do
    	echo prueba"$i"
          if test -f ./test/accept/prueba"$i"; then
              ./bin/Compiler ./results/prueba"$i".c < ./test/accept/prueba"$i"
              gcc -o ./results/prueba"$i" ./results/prueba"$i".c
              rm ./results/prueba"$i".c
          elif test -f ./test/reject/prueba"$i"; then
              ./bin/Compiler ./results/prueba"$i".c < ./test/reject/prueba"$i"
              gcc -o ./results/prueba"$i" ./results/prueba"$i".c
              rm ./results/prueba"$i".c
          else
            echo "No existe el test $i"
          fi
          echo -e '\n'
    done
    shift 1
fi
for var in "$@"
do
    echo "$var"
    if test -f ./test/accept/"$var"; then
    ./bin/Compiler ./results/"$var".c < ./test/accept/"$var"
    elif test -f ./test/reject/"$var"; then
        ./bin/Compiler ./results/"$var".c < ./test/reject/"$var"
    else
      echo "No existe el test $var"
    fi
    echo -e '\n'
done

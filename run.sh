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
    	echo "Compiling test$i"
    	source ./run.sh prueba$i | egrep "INFO"
    	echo -e '\n'
    done
    shift 1
fi

for var in "$@"
do
    echo "$var"
    ./bin/Compiler < ./test/"$var" | egrep "INFO"
    echo -e '\n'
done
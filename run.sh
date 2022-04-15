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

for var in "$@"
do
    ./bin/Compiler < ./test/"$var"
done
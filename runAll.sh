#!/bin/bash
for i in {1..15}
do
	echo "Compiling test$i"
	source ./run.sh prueba$i | egrep "INFO"
	echo -e '\n'
done

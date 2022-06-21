#include "backend/code-generation/generator.h"
#include "backend/support/logger.h"
#include "backend/support/shared.h"
#include "frontend/syntactic-analysis/bison-parser.h"
#include "backend/semantic-analysis/semantic-analysis.h"
#include <stdio.h>
#include "./backend/support/supermalloc.h"
//Estado de la aplicación.
CompilerState state;

// Punto de entrada principal del compilador.
const int main(const int argumentCount, const char ** arguments) {
	// Inicializar estado de la aplicación.
	state.result = 0;
	state.succeed = false;
    initMemory();
    FILE * file;
    if(argumentCount > 1) {
        file = fopen(arguments[1], "w");
        if(file == NULL){
            printf("Fail opening file\n");
            exit(0);
        }
    }else
        file = fopen("result.c", "w");

	// Mostrar parámetros recibidos por consola.
	for (int i = 0; i < argumentCount; ++i) {
		LogInfo("Argumento %d: '%s'", i, arguments[i]);
	}

	// Compilar el programa de entrada.
	LogInfo("Compilando...\n");
    int final_result;
	const int result = yyparse();
	switch (result) {
		case 0:
			if (state.succeed) {
                generateSymbolTable(state.root);
                final_result = Generator(state.root, file);
                if(final_result >= 0 )
                    LogInfo("La compilacion fue exitosa.");
            }
			else {
				LogError("Se produjo un error en la aplicacion.");
				return -1;
			}
			break;
		case 1:
			LogError("Bison finalizo debido a un error de sintaxis.");
			break;
		case 2:
			LogError("Bison finalizo abruptamente debido a que ya no hay memoria disponible.");
			break;
		default:
			LogError("Error desconocido mientras se ejecutaba el analizador Bison (codigo %d).", result);
	}
	LogInfo("Fin.");
    if(final_result != 0){
        LogError("Se produjo un error en la aplicacion.");
    }
    superFree();
    fclose(file);
	return result;
}

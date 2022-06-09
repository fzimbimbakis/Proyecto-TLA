#include "../support/logger.h"
#include "generator.h"

/**
 * Implementación de "generator.h".
 */

int recursiveProgram(tProgram * program);
int Class(tClass * class);
int Main(tMainFunction * mainFunction);
int Attributes(tAttributes * attributes);
int Constructor(tConstructor * attributes);
int Methods(tMethods * attributes);
int Declaration(tDeclaration * declaration);
int DeclarationsRecursive(tDeclarations * declarations);
FILE * fd;

int Generator(tProgram * program, FILE * filedescriptor) {
//	LogInfo("El resultado de la expresion computada es: '%d'.", program);
    fd = filedescriptor;
    int final_result = 0;
    if(program->classesAndMain != NULL){         //// Class + Program
        printf("Class\n");
        final_result = Class(program->classesAndMain->class);
        if(final_result != 0)
            return final_result;

        if(program->classesAndMain->program != NULL)
            final_result = recursiveProgram(program->classesAndMain->program);
        if(final_result != 0)
            return final_result;

    } else{    //// Main

        final_result = Main(program->mainFunction);
        if(final_result != 0)
            return final_result;
    }
    return final_result;
    return 0;
}

int recursiveProgram(tProgram * program){
    int result = 0;
    if(program->classesAndMain != NULL){

        result = Class(program->classesAndMain->class);
        if(result != 0)
            return result;

        result = recursiveProgram(program->classesAndMain->program);

    } else{
        result = Main(program->mainFunction);
    }
    return result;
}

int Class(tClass * class){
    //// Creo la struct si tengo o atributos o extiendo alguna clase
    if(class->classIn->attributes != NULL || class->extendsName != NULL){
        printf("Tiene atts o extends algo\n");
        fprintf(fd, "struct %s{\n", class->varname->associated_value.varname);

        if (class->extendsName != NULL) {
            printf("Extiende algo\n");
            fprintf(fd, "struct %s extended_%s;\n", class->extendsName->extendedClassName->associated_value.varname,
                    class->extendsName->extendedClassName->associated_value.varname);
        }

        if (class->classIn->attributes != NULL) {
            printf("Atts\n");
            Attributes(class->classIn->attributes);
        }
        fprintf(fd, "}\n");
    }

//    Constructor(class->classIn->constructor);
//
//    if(class->classIn->methods != NULL) {
//        Methods(class->classIn->methods);
//    }

}

int Attributes(tAttributes * attributes){
    int result;
    result = Declaration(attributes->declarations->declaration);
    if(attributes->declarations->declarations != NULL)
        result = DeclarationsRecursive(attributes->declarations->declarations);
    return result;
}

int Declaration(tDeclaration * declaration){
    int result = 0;
    fprintf(fd, "Declaración\n");
    return result;
}
int DeclarationsRecursive(tDeclarations * declarations){
    int result;
    result = Declaration(declarations->declaration);
    if(declarations->declarations != NULL)
        result = DeclarationsRecursive(declarations->declarations);
    return result;
}


int Constructor(tConstructor * attributes){
    int result = 0;
    return result;
}

int Methods(tMethods * attributes){
    int result = 0;
    return result;
}

int Main(tMainFunction * mainFunction){
    int result = 0;
    return result;
}
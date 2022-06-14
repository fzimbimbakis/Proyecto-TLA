//
// Created by shadad on 14/06/22.
//

#ifndef COMPILER_SEMANTIC_ANALYSIS_H
#define COMPILER_SEMANTIC_ANALYSIS_H
#include <stdio.h>
#include "../support/shared.h"
#include <stdlib.h>
#include <string.h>
#include "../../frontend/syntactic-analysis/bison-parser.h"

enum type{
    VOID_TYPE,
    INT_TYPE,
    CHAR_TYPE,
    INTARRAY_TYPE,
    CHARARRAY_TYPE,
    OBJECT_TYPE,
    OBJECTARRAY_TYPE,
};



 struct variable{
    char * varname ;
    char * objectType;
    int type;
    struct variable * next;
};

 struct  function{
    char * functionName;
    struct variable * parameters;
    struct variable * definedVariables;
    int returnType;
    struct function * next ;
};

 struct class{
    char * className;
    char * fatherName;
    struct variable * attributes;
    struct function * constructor;
    struct function * methods;
    struct class * next;
};



 struct global {
    struct class * classes;
    struct  function main;
};

void addMain(tMainFunction * mainFunction);
void  addClass(tClass * aClass);
struct function *  addFunction(tFunction * function);
struct variable * addVariableDeclaration(tDeclaration declaration);
struct function * addConstructor(tConstructor * constructor);
struct variable * addAttribute(tAttributes * attributes);
struct function * addMethods(tMethods * methods);
//struct variable * addParameters(tParameters * parameters);
struct variable * addDefinedVariables(tProgramStatements * programStatements);

#endif //COMPILER_SEMANTIC_ANALYSIS_H

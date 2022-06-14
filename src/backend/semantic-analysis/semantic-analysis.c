#include "semantic-analysis.h"
static struct variable * fromDeclarationToVariable(struct tDeclaration * declaration);
static int fromDataTypeToType(char * dataType);
static struct variable * fromParameterToVariable(tParameters * parameters );

static struct global globalScope={.main=NULL,.classes=NULL};




void addMain(tMainFunction * mainFunction);

void addClass(tClass * aClass){
    struct class * newNode = malloc(sizeof(struct class)); 
    newNode->className = aClass->varname->associated_value.varname;
    if(aClass->extendsName != NULL && aClass->extendsName->extendedClassName->associated_value.varname!=NULL) newNode->fatherName = aClass->extendsName->extendedClassName->associated_value.varname;
    newNode->attributes = addAttribute(aClass->classIn->attributes);
    newNode->constructor = addConstructor(aClass->classIn->constructor);
    newNode->methods = addMethods(aClass->classIn->methods);
}


struct function * addConstructor(tConstructor * constructor){
    struct function * newNode = malloc(sizeof(struct function));
    newNode->parameters = fromParameterToVariable(constructor->function->parameters);
    newNode->definedVariables = addDefinedVariables(constructor->function->programStatements);
    newNode->returnType = VOID_TYPE;
    newNode->next = NULL;
    return newNode;
}

struct variable * addAttribute(tAttributes * attributes){
    tDeclarations  * current = attributes->declarations;
    struct variable * currentVariable;
    struct variable * first  = NULL ;
    struct variable * prev  = NULL;
    while(current != NULL ){
        currentVariable =  fromDeclarationToVariable(current->declaration);
        if(first == NULL) {
            first = currentVariable ;
            prev = first;
        }
        current = current->declarations;
        prev->next = currentVariable;
        prev = currentVariable;
        currentVariable = currentVariable->next;
    }
    return  first;
}


struct function * addMethods(tMethods * methods){
    struct tMethods  * currentMethod = methods;
    struct function * first = NULL;
    struct function * current = currentMethod->function;
    while(currentMethod != NULL ){
        current = addFunction(currentMethod->function);
        if(first == NULL ) first = current ;
        currentMethod = currentMethod -> methods;
        current = current ->next;
    }
    return first;
}


struct function *  addFunction(tFunction * function){
    struct function * newNode = malloc(sizeof(struct function )) ;
    newNode->parameters = fromParameterToVariable(function->parameters);
    newNode->parameters = addDefinedVariables(function->programStatements);
    if(function->type == DATATYPE_FUNCTION )
        newNode->returnType = fromDataTypeToType(function->datatype->type->associated_value.varname);
    else if (function->type == VOID_FUNCTION)
        newNode->returnType = VOID_TYPE;
    return newNode;
}


struct variable * addDefinedVariables(tProgramStatements * programStatements){
    if(programStatements == NULL )
        return NULL;

    struct variable * newNode = NULL;
    struct variable * first = NULL ;
    tProgramStatements *  ps = programStatements;
    while (ps != NULL && ps->programUnitStatements != NULL ){
        if(ps->programUnitStatements->type == PUS_DECLARATION){
            newNode = fromDeclarationToVariable(ps->programUnitStatements->declaration);
            if(first == NULL ) first = newNode;
            newNode = newNode->next;
        }
        ps = ps->ProgramStatements;
    }
    return first;
}



static struct variable * fromDeclarationToVariable(struct tDeclaration * declaration){
    struct variable * newNode = malloc(sizeof(struct variable));
    newNode->objectType = NULL;
    switch (declaration->type) {
        case CHAR_DECLARATION:
            newNode->type = CHAR_TYPE;
            newNode->varname = declaration->charDeclaration->varname->associated_value.varname;
            break;
        case INTEGER_DECLARATION:
            newNode-> type = INT_TYPE;
            newNode->varname = declaration->integerDeclaration->varname->associated_value.varname;
            break;
        case INTEGER_ARRAY_DECLARATION:
            newNode-> type = INTARRAY_TYPE;
            newNode->varname = declaration->integerArrayDeclaration->varname->associated_value.varname;
            break;
        case CHAR_ARRAY_DECLARATION:
            newNode-> type = CHARARRAY_TYPE;
            newNode->varname = declaration->charArrayDeclaration->varname->associated_value.varname;
            break;
        case INTEGER_ASSIGNATION_DECLARATION:
            newNode->type= INT_TYPE;
            newNode->varname = declaration->integerAssignationDeclaration->varname->associated_value.varname;
            break;
        case CHAR_ASSIGNATION_DECLARATION_DECLARATION:
            newNode-> type = CHAR_TYPE;
            newNode->varname = declaration->charAssignationDeclaration->varname->associated_value.varname;
            break;
        case INTEGER_ARRAY_ASSIGNATION_DECLARATION:
            newNode->type = INTARRAY_TYPE;
            newNode->varname = declaration->integerArrayAssignationDeclaration->varname->associated_value.varname;
            break;
        case CHAR_ARRAY_ASSIGNATION_DECLARATION:
            newNode-> type = CHARARRAY_TYPE;
            newNode->varname = declaration->charArrayAssignationDeclaration->name->associated_value.varname;
            break;
        case DECLARATION_WITH_OBJECT_TYPE:
            newNode->type = OBJECT_TYPE;
            newNode->varname = declaration->declarationAux->name;
            newNode->objectType = declaration->declarationAux->objectDataType;
            break;
    }
    return newNode;
}


static struct variable * fromParameterToVariable(tParameters * parameters ){
    if(parameters == NULL)
        return NULL;

    struct variable * newNode = malloc(sizeof(struct variable));
    newNode->varname = parameters->paramName->associated_value.varname;

    switch (parameters->type) {
        case BASIC_PARAMETERS:
                newNode ->type = fromDataTypeToType(parameters->datatype->type->associated_value.varname);
            break;
        case MULTIBASIC_PARAMETERS:
            newNode ->type = fromDataTypeToType(parameters->datatype->type->associated_value.varname);
            newNode->next = fromParameterToVariable(parameters->nextParameters->nextParameters);
            break;
        case OBJECT_PARAMETERS:
            newNode->type = OBJECT_TYPE;
            newNode->objectType = parameters->objectTypeName->associated_value.varname;
            break;
        case MULTIOBJECT_PARAMETERS:
            newNode->type = OBJECT_TYPE;
            newNode->objectType = parameters->objectTypeName->associated_value.varname;
            newNode->next = fromParameterToVariable(parameters->nextParameters->nextParameters);
            break;
        case ARRAY_PARAMETERS:
            newNode->type = fromDataTypeToType(parameters->datatype->type->associated_value.varname);
            break;
        case MULTIARRAY_PARAMETERS:
            newNode->next = fromParameterToVariable(parameters->nextParameters->nextParameters);
            break;
        case OBJECTARRAY_PARAMETERS:
            newNode->type = OBJECTARRAY_TYPE;
            newNode->objectType = parameters->objectTypeName->associated_value.varname;
            break;
        case MULTIOBJECTARRAY_PARAMETERS:
            newNode->type = OBJECTARRAY_TYPE;
            newNode->objectType = parameters->objectTypeName->associated_value.varname;
            newNode->next = fromParameterToVariable(parameters->nextParameters->nextParameters);
            break;
    }
    return  newNode;

}

static int fromDataTypeToType(char * dataType){
    if(strcmp(dataType,"int")== 0 )
        return INT_TYPE;
    else return CHAR_TYPE;

}
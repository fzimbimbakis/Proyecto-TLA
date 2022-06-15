#include "semantic-analysis.h"
static struct variable * fromDeclarationToVariable(struct tDeclaration * declaration);
static struct variable * fromParameterToVariable(tParameters * parameters );
static int fromDataTypeToTypeTokenId(int  dataType);
static int fromDeclarationTypeToVariableType(tParameters  * parameters);
struct  class * getClassByName(char * name );
struct function * getMethodByName(char * class , char * name );
struct variable * getVarByName(char * class , char * methodName , char * name );
struct variable * getVarFromMain();
struct variable * getVarByName(char * class , char * methodName , char * name );
struct function * getMain();
int getParametersNeed(struct function * function );

struct global  symbolTable;

boolean  isMethodOnFatherAndSon(char * methodName, char * class ){
    struct class * currentClass = getClassByName(class);
    if(currentClass ->fatherName == NULL)
        return false;
    struct function * methodCall  = getMethodByName(class ,methodName);
    if(methodCall == NULL )
        return  false;
    methodCall = getMethodByName(currentClass->fatherName ,methodName);
    if(methodCall == NULL)
        return false;
    return true;
}



// >= 0 si es valido, si es del padre setea fromFather en true.
//< 0 si no es valido
boolean isMethodFromFather(char * varname ,char * methodName){

    struct variable * variableStruct = getVarFromMain(varname);
    if(variableStruct == NULL)
        return false;
    struct class * currentClass = getClassByName(variableStruct->objectType);
    if(currentClass == NULL )
        return false;
    struct function * methodCall  = getMethodByName(variableStruct->objectType,methodName);
    if(methodCall == NULL && currentClass->fatherName == NULL  )
        return  false;
    else if(methodCall == NULL  && currentClass->fatherName != NULL ){
        methodCall = getMethodByName(currentClass->fatherName,methodName);
        if(methodCall == NULL)
            return false;
        else
            return true;

    }
    return false ;

}


int  isMethodCallValid(char * methodName,char * variable , tArgumentValues * parameters){
    struct variable * currentVariable = getVarFromMain(variable);
    if(currentVariable == NULL )
        return -4;
    if(currentVariable -> type != OBJECT_TYPE)
        return -2 ;
    struct function * methodCall = getMethodByName(currentVariable->objectType , methodName);
    struct class * currentClass = getClassByName(currentVariable->objectType);
    if(methodCall == NULL && currentClass->fatherName == NULL  )
        return  -3;
    else if(methodCall == NULL  && currentClass->fatherName != NULL ){
        methodCall = getMethodByName(currentClass->fatherName,methodName);
        if(methodCall == NULL)
            return -3;
    }

    int NeedParameters = getParametersNeed(methodCall);
    tArgumentValues  * counting = parameters;
    int parametersC = 0 ;
    while (counting != NULL){
        parametersC++;
        if(counting->commaNextArgumentValue == NULL)
            break;
        counting = counting->commaNextArgumentValue->nextArgument;
    }
    if( parametersC - 1 == NeedParameters)
        return 1 ;
    else return -1;
}

int getParametersNeed(struct function * function ){
    if(function == NULL )
        return 0;
    struct variable * var = function->parameters;
    int count = 0 ;
    while(var!=NULL){
        count++;
        var = var->next;
    }
    return count;
}



boolean isAssignationValid(char * class ,char  * method ,char * leftValue, char * rightValue){
    struct variable * leftVariable = getVarByName(class,method,leftValue);
    struct variable * rightVariable = getVarByName(class,method,rightValue);
    if(leftVariable == NULL || rightVariable == NULL)
        return false;
    if(leftVariable -> type == 5 && rightVariable->type == 5 ){
        return strcmp(leftVariable->objectType,rightVariable->objectType)==0;
    }
    return (leftVariable->type == rightVariable->type);
}



boolean isAttributeValid(char * className , char * variable){
    struct class * currentClass = getClassByName(className);

    if(currentClass == NULL)
        return false; //no class with such name
    else{
        struct variable * currentAttribute = currentClass->attributes;
        while(currentAttribute!=NULL){
            if(strcmp(currentAttribute->varname,variable) == 0)
                return true;
            currentAttribute = currentAttribute->next;
        }
        return false;
    }
}

struct variable * getVarFromMain(char * name ){
    struct function * method = getMain();
    struct variable * currentVariable = method->parameters;
    while(currentVariable != NULL ){
        if(strcmp(name, currentVariable->varname ) == 0 )
            return currentVariable;
        currentVariable = currentVariable->next;
    }

    currentVariable = method->definedVariables;
    while(currentVariable != NULL ){
        if(strcmp(name, currentVariable->varname ) == 0 )
            return currentVariable;
        currentVariable = currentVariable->next;
    }

    return NULL ;

}



struct function * getMain(){
    return symbolTable.main;
}


struct variable * getVarByName(char * class , char * methodName , char * name ){
    struct function * method;
    if(strcmp(methodName , "main") == 0 ){
            method = symbolTable.main;
    }else method = getMethodByName(class,methodName);
    struct variable * currentVariable = method->parameters;
    while(currentVariable != NULL ){
        if(strcmp(name, currentVariable->varname ) == 0 )
            return currentVariable;
        currentVariable = currentVariable->next;
    }

    currentVariable = method->definedVariables;
    while(currentVariable != NULL ){
        if(strcmp(name, currentVariable->varname ) == 0 )
            return currentVariable;
        currentVariable = currentVariable->next;
    }

    return NULL ;
}


struct function * getMethodByName(char * class , char * name ){
    struct class * currentClass = getClassByName(class);
    if(currentClass == NULL)
        return NULL;
    struct function * currentMethod = currentClass->methods;
    while (currentMethod != NULL ){
        if(strcmp(currentMethod->functionName,name) == 0 )
            return currentMethod;
        currentMethod = currentMethod -> next ;
    }
    return NULL;
}



struct  class * getClassByName(char * name ){
    struct class * currentClass = symbolTable.classes;
    while(currentClass != NULL){
        if(strcmp(currentClass->className,name) == 0 )
            return currentClass;
        currentClass = currentClass->next;
    }
    return NULL ;
}


struct global * generateSymbolTable(tProgram * program){
    struct global * newNode = &symbolTable; //malloc(sizeof(struct global));
    if(program->type == PROGRAM_MAIN){
        newNode->main = addMain(program->mainFunction);
    }
    else {
        newNode = generateSymbolTable(program->classesAndMain->program);
        if(newNode->classes == NULL)
            newNode->classes = addClass(program->classesAndMain->class);
        else {
            struct class * class  = addClass(program -> classesAndMain->class);
            class->next = newNode -> classes;
            newNode->classes = class;
        }
    }
    return newNode;
}




struct function * addMain(tMainFunction * mainFunction){
    struct function * newNode = malloc(sizeof(struct function )) ;
    newNode->functionName = "main";
    newNode->parameters = fromParameterToVariable(mainFunction->parameters);
    newNode->definedVariables = addDefinedVariables(mainFunction->programStatements);
    newNode->returnType = INT_TYPE;
    return  newNode;
}

struct class * addClass(tClass * aClass){
    if(aClass == NULL )
        return NULL;
    struct class * newNode = malloc(sizeof(struct class)); 
    newNode->className = aClass->varname->associated_value.varname;
    if(aClass->extendsName != NULL && aClass->extendsName->extendedClassName->associated_value.varname!=NULL) newNode->fatherName = aClass->extendsName->extendedClassName->associated_value.varname;
    newNode->attributes = addAttribute(aClass->classIn->attributes);
    newNode->constructor = addConstructor(aClass->classIn->constructor);
    newNode->methods = addMethods(aClass->classIn->methods);
    return newNode;
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
    if(attributes == NULL )
        return NULL;
    tDeclarations  * current = attributes->declarations;
    struct variable * currentVariable;
    struct variable * first  = NULL ;
    struct variable * prev  = NULL;
    while(current != NULL ){
        currentVariable =  fromDeclarationToVariable(current->declaration);
        if(first == NULL) {
            first = currentVariable ;
        }
        current = current->declarations;
        if(prev!=NULL && prev != currentVariable ) prev->next = currentVariable;
        prev = currentVariable;
        currentVariable = currentVariable->next;
    }
    return  first;
}



struct function * addMethods(tMethods * methods){
    if(methods == NULL )
        return NULL ;

    struct tMethods  * currentMethod = methods;
    struct function * first = NULL;
    struct function * prev  = NULL;
    struct function * current ;
    while(currentMethod != NULL ){
        current = addFunction(currentMethod->function);
        if(first == NULL )
            first = current ;

        if(prev != NULL && prev != current) prev->next = current;
        prev = current;

        currentMethod = currentMethod -> methods;
    }
    return first;
}




struct function *  addFunction(tFunction * function){
    struct function * newNode = malloc(sizeof(struct function )) ;
    newNode->functionName = function->varname->associated_value.varname;
    newNode->parameters = fromParameterToVariable(function->parameters);
    newNode->definedVariables = addDefinedVariables(function->programStatements);
    if(function->type == DATATYPE_FUNCTION )
        newNode->returnType = fromDataTypeToTypeTokenId(function->datatype->type->tokenId);
    else if (function->type == VOID_FUNCTION)
        newNode->returnType = VOID_TYPE;
    return newNode;
}


struct variable * addDefinedVariables(tProgramStatements * programStatements){
    if(programStatements == NULL )
        return NULL;

    struct variable * newNode = NULL;
    struct variable * first = NULL ;
    struct variable * prev = NULL ;
    tProgramStatements *  ps = programStatements;
    while (ps != NULL && ps->programUnitStatements != NULL ){
        if(ps->programUnitStatements->type == PUS_DECLARATION){
            newNode = fromDeclarationToVariable(ps->programUnitStatements->declaration);
            if(first == NULL ) {
                first = newNode;
            }
            if(prev != NULL && prev != newNode )prev -> next = newNode;
            prev = newNode;

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
            newNode->varname = declaration->declarationAux->objectDataType->associated_value.varname;
            newNode->objectType = declaration->declarationAux->name->associated_value.varname;
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
                newNode ->type = fromDeclarationTypeToVariableType(parameters);
            break;
        case MULTIBASIC_PARAMETERS:
            newNode ->type = fromDeclarationTypeToVariableType(parameters);
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
            newNode->type = fromDeclarationTypeToVariableType(parameters);
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

//struct assignation * getAssignationSubNode(tSuperSubnode * subnode);
//struct assignation * getAssignationArray(tArrayAssignation * subnode);
//
//
//struct assignation * getAssignation(tAssignation * assignation ){
//    if(assignation->type == ASSIGNATION_ARRAY_ASSIG)
//        return getAssignationSubNode(assignation->assignationSubnode);
//    else
//        return getAssignationArray(assignation->arrayAssignation);
//
//}
//
//struct assignation * getAssignationSubNode(tSuperSubnode * subnode){
//    switch (subnode->typeVariable) {
//
//    }
//
//    switch (subnode->typeAssignation) {
//        case SUPER_SUB_NODE_VARNAME:
//            break;
//
//        case SUPER_SUB_NODE_OBJECT_ATT:
//            break;
//
//        case SUPER_SUB_NODE_ARRAY_ASSIG_SUB_NODE:
//            break;
//
//        case SUPER_SUB_NODE_SIMPLE_ASSIG_SUB_NODE:
//            break;
//
//    }
//
//}
//
//struct assignation * getAssignationArrayAssignationSubnode(tArrayAssignationSubnode * assignationSubnode){
//    struct assignation * newNode = malloc(sizeof(struct assignation));
//    switch (assignationSubnode->type) {
//        case ARRAY_ASSIG_SUB_NODE_GENERIC_ARRAY_WITH_BRACKETS:
//                  newNode->rightType = assignationSubnode->genericArrayWithBrackets->genericValueArray->genericValue-
//            break;
//        case ARRAY_ASSIG_SUB_NODE_INTEGER_ARRAY:
//
//            break;
//        case ARRAY_ASSIG_SUB_NODE_CHARACTER_ARRAY:
//
//            break;
//        case ARRAY_ASSIG_SUB_NODE_STRING:
//
//            break;
//    }
//
//
//}
//
//
//
//struct assignation * getAssignationArray(tArrayAssignation * subnode){
//
//
//}
//
//
//
//
//
//
//struct assignation * assignationFromSuperSubNode(tSuperSubnode * subnode){
//    struct assignation * newNode = malloc(sizeof(struct assignation));
////            VARNAME ASSIGNATION generic_value SEMICOLON
////
//    switch(subnode->typeAssignation){
//        case  SUPER_SUB_NODE_SIMPLE_ASSIG_SUB_NODE:
//            newNode->leftVarname = subnode->varname->associated_value.varname;
//            newNode->leftType  =
//
//        break;
//    }
//
//
//}
//
//
//


static int fromDataTypeToTypeTokenId(int  dataType){
    if(dataType == INT )
        return INT_TYPE;
    else return CHAR_TYPE;
}


static int fromDeclarationTypeToVariableType(tParameters  * parameters){
    if(parameters->datatype->type->tokenId == INT) {
        if (parameters->squareBrackets == NULL) return INT_TYPE;
        else return INTARRAY_TYPE;
    }else if(parameters->squareBrackets == NULL ) return CHAR_TYPE;
    else return CHARARRAY_TYPE;
}
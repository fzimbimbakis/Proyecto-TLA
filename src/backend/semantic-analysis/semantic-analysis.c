#include "semantic-analysis.h"
#include "../support/logger.h"
#include "../support/supermalloc.h"


int getParametersNeed(struct function * function );
boolean  checkIfExistsVarname(char * varname   , struct  variable * list );
boolean checkIfExistsFunction(char * function , struct function * function1);
boolean checkIfExistsAttribute(char * attributeName, struct variable * attributeList);
boolean checkIfExistsClass(char * className, struct class * classList);
boolean checkIfMatches(char * leftVarname, char * rightVarname, struct pair  * type);
struct variable * getAttributeFromVarname(struct class * currentClass , char * varname);



struct variable * getAttribute(struct class  * class , char * attribute);
struct function * getMain();
struct  class * getClassByName(char * name );
struct function * getMethodByName(struct class * class , char * name );
struct variable * getVarByName(struct class  * class , struct function * methodName , char * name );
struct variable * getVarFromMain();

static struct variable * fromDeclarationToVariable(struct tDeclaration * declaration, struct variable * list );
static struct variable * fromParameterToVariable(tParameters * parameters );
static struct pair * fromDataTypeToTypeTokenId(int  dataType);
struct pair *  getTypeFromVarname(char * varname) ;
struct pair * comparationT(tComparation * comparation);
static struct pair * fromDeclarationTypeToVariableType(tParameters  * parameters);
struct pair * factorT(tFactor * factor ) ;
void programUnitStatementsT(tProgramUnitStatements * programUnitStatements);
struct pair *  objectAttribute(tObjectAttribute * objectAttribute );
struct pair * integerExpression(tIntegerExpression * expression);
struct function * getMain();
struct pair * genericValueT(tGenericValue * genericValue );
struct pair * instantiation(tInstantiation * instantiation);
struct pair * functionCallT(tFunctionCall * functionCall);
struct pair * methodCallT(tMethodCall * methodCall);
struct pair * arrayDesreferencingT(tArrayDesreferencing * arrayDesreferencing);
struct variable * programStatements(tProgramStatements * programStatements1);
struct pair * charArrayWithBracketRecursive(tCharacterArray * characterArray);
struct pair * charArrayWithBrackets(tCharArrayWithBrackets * charArrayWithBrackets);
struct pair * integerArrayWithBracketRecursive(tIntegerArray * genericValueArray);
struct pair * genericArrayWithBracketRecursive(tGenericValueArray * genericValueArray);
struct pair * simpleAssignationSubnode(tSimpleAssignationSubnode * simpleAssignationSubnode);
struct pair * objectAttributeDesreferencing(tObjectAttributeDesreferencing * objectAttributeDesreferencing);
struct pair * innerAttribute(tInnerAttribute * attribute,char * className );
struct pair * conditionUnit(tConditionUnit * conditionUnit);
struct pair * varname(tTokenNode * varname);
struct pair * integer(tTokenNode * integer);
struct pair * subInteger(tSubInteger *subInteger);

void checkInstantiation(tInstantiation * instantiation);
void checkAssignation(tAssignation * assignation);
void equalPairs(struct pair * p1, struct pair * p2);
void fail();


struct global  * symbolTable = NULL ;
struct class * currentClassGlobal;
struct function * currentMethodGlobal;



//deberia sacar de currentScope
struct variable * getVarByName(struct class  * class , struct function * methodName , char * name ){
    struct function * method;


    if(class == NULL && methodName == NULL )
        method = symbolTable->main;
    else
        method =methodName;
        struct variable * currentVariable;

        if(currentMethodGlobal != NULL)
            currentVariable = currentMethodGlobal->definedVariables;
        else currentVariable = symbolTable->main->definedVariables;

        while(currentVariable != NULL ){
            if(strcmp(name, currentVariable->varname ) == 0 )
                return currentVariable;
            currentVariable = currentVariable->next;
        }

        currentVariable = method->parameters;
        while(currentVariable != NULL ){
            if(strcmp(name, currentVariable->varname ) == 0 )
                return currentVariable;
            currentVariable = currentVariable->next;
        }

        struct class * currentClassLocal = currentClassGlobal;
        while(currentClassLocal != NULL){
            currentVariable = currentClassGlobal->attributes;
            while(currentVariable != NULL ){
                if(strcmp(name, currentVariable->varname ) == 0 )
                    return currentVariable;
                currentVariable = currentVariable->next;
            }
            if(currentClassLocal->fatherName != NULL )
                currentClassLocal = getClassByName(currentClassLocal->fatherName);
            else
                currentClassLocal = NULL;
        }


        LogError("Variable %s not defined on Class %s Method %s\n", name, class->className, methodName->functionName);
        fail();
        return NULL ;

}


struct function * getMethodByName(struct class  * currentClass1 , char * name ){

    while(currentClass1 != NULL ){
        struct function * currentMethod1 = currentClass1->methods;

        while (currentMethod1 != NULL ){
            if(strcmp(currentMethod1->functionName,name) == 0 )
                return currentMethod1;
            currentMethod1 = currentMethod1 -> next ;
        }
        if(currentClass1->fatherName != NULL)
            currentClass1 = getClassByName(currentClass1->fatherName);
        else currentClass1= NULL;
    }
    if(currentClass1 != NULL)
    LogError("Method %s not found in class %s\n", name, currentClass1->className);
    else LogError("Method %s not found\n", name);
    fail();
    return NULL;
}



struct  class * getClassByName(char * name ){
    if(currentClassGlobal!=NULL && strcmp(name , currentClassGlobal->className) ==  0)
        return currentClassGlobal;

    struct class * currentClass1 = symbolTable->classes;
    while(currentClass1 != NULL){
        if(strcmp(currentClass1->className,name) == 0 )
            return currentClass1;
        currentClass1 = currentClass1->next;
    }
    LogError("Class %s not found\n", name);
    fail();
    return NULL ;
}


struct global * generateSymbolTable(tProgram * program){
    struct global * newNode;
    if(symbolTable == NULL ) {
        symbolTable = superMalloc(1,sizeof(struct global)) ;
    }
    newNode = symbolTable;
    if(program->type == PROGRAM_MAIN){
        currentClassGlobal = NULL;
        newNode->main = addMain(program->mainFunction);
    }else {
            struct class * auxClass = addClass(program->classesAndMain->class);
            auxClass->next = newNode->classes;
            newNode->classes = auxClass;
            newNode = generateSymbolTable(program->classesAndMain->program);
            return newNode;
    }


//    struct global * newNode = &symbolTable; //superMalloc(1,sizeof(struct global));
//    if(program->type == PROGRAM_MAIN){
//        currentClass = NULL;
//        newNode->main = addMain(program->mainFunction);
//    }
//    else {
//        newNode = generateSymbolTable(program->classesAndMain->program);
//        if(newNode->classes == NULL){
//            newNode->classes = addClass(program->classesAndMain->class);
//        }
//        else {
//            struct class * class  = addClass(program -> classesAndMain->class);
//            checkIfExistsClass(class->className,newNode->classes);
//            class->next = newNode -> classes;
//            newNode->classes = class;
//        }
//    }
//    return newNode;
}




struct function * addMain(tMainFunction * mainFunction){
    currentClassGlobal = NULL;
    currentMethodGlobal = NULL ;
    struct function * newNode = symbolTable->main = superMalloc(1,sizeof(struct function )) ;
    newNode->functionName = "main";
    newNode->returnType = superMalloc(1,sizeof(struct pair));
    newNode->returnType->type = INT_TYPE;
    newNode->parameters = fromParameterToVariable(mainFunction->parameters);
    newNode->definedVariables = programStatements(mainFunction->programStatements);
    return  newNode;
}

struct class * addClass(tClass * aClass){
    if(aClass == NULL )
        return NULL;
    struct class * newNode = superMalloc(1,sizeof(struct class));
    currentClassGlobal = newNode;
    newNode->className = aClass->varname->associated_value.varname;
    if(aClass->extendsName != NULL && aClass->extendsName->extendedClassName->associated_value.varname!=NULL) newNode->fatherName = aClass->extendsName->extendedClassName->associated_value.varname;
    newNode->attributes = addAttribute(aClass->classIn->attributes);
    newNode->constructor = addConstructor(aClass->classIn->constructor);
    newNode->methods = addMethods(aClass->classIn->methods);
    return newNode;
}


struct function * addConstructor(tConstructor * constructor){
    struct function * newNode = superMalloc(1,sizeof(struct function));
    currentMethodGlobal = newNode;
    newNode->parameters = fromParameterToVariable(constructor->function->parameters);
    newNode->definedVariables = programStatements(constructor->function->programStatements);
    struct pair * returnType = superMalloc(1,sizeof(struct pair));
    returnType->type = OBJECT_TYPE;
    returnType->name = currentClassGlobal->className;
    newNode->returnType = returnType;
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
        currentVariable =  fromDeclarationToVariable(current->declaration, first);
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

struct pair * returnType(tReturn * returnType){
    struct pair * returnFunction= superMalloc(1,sizeof(struct pair));
    if(currentClassGlobal != NULL) {
        if(currentMethodGlobal == NULL) {
            returnFunction->type = INT_TYPE;
        }
        returnFunction = currentMethodGlobal->returnType;
    }else
        returnFunction->type = INT_TYPE;
    struct pair * pair = superMalloc(1,sizeof(struct pair ));
    switch (returnType->type) {
        case RETURN_VALUE:
                  pair= genericValueT(returnType->valueUnion.value);
                  break;
        case RETURN_CONDITION:
                pair=  conditionUnit(returnType->valueUnion.conditionUnit);
                break;
        case RETURN_VOID:
                        pair->type = VOID_TYPE;
                        break;
    }
    equalPairs(returnFunction,pair);
    return returnFunction;


}


struct pair * genericValueT(tGenericValue * genericValue ){
    struct pair * currentPair = superMalloc(1,sizeof(struct pair ));
    switch (genericValue->type) {
        case GENERIC_VALUE_INTEGER_EXPRESSION:
            return integerExpression(genericValue->integerExpression);
        case GENERIC_VALUE_STRING:
            currentPair->type = CHARARRAY_TYPE ;
            break;
        case GENERIC_VALUE_CHARACTER:
            currentPair->type = CHAR_TYPE;
            break;
    }
    return currentPair;

}



struct function * addMethods(tMethods * methods){
    if(methods == NULL )
        return NULL ;
    struct tMethods  * cM = methods;
    struct function * first = NULL;
    struct function * prev  = NULL;
    struct function * current ;
    while(cM != NULL ){
        current = addFunction(cM->function);
        currentMethodGlobal = current;
        if(checkIfExistsFunction(current->functionName,first)){
            LogError("Method %s has already been defined\n",current->functionName);
            fail();
        }

        if(first == NULL ) {
            first = current;
            currentClassGlobal->methods = first;
        }

        if(prev != NULL && prev != current) prev->next = current;
        prev = current;

        cM = cM -> methods;
    }
    return first;
}




struct function *  addFunction(tFunction * function){
    struct function * newNode = superMalloc(1,sizeof(struct function )) ;
    currentMethodGlobal = newNode;
    newNode->functionName = function->varname->associated_value.varname;
    newNode->parameters = fromParameterToVariable(function->parameters);
    if(function->type == DATATYPE_FUNCTION ) {
        newNode->returnType = fromDataTypeToTypeTokenId(function->datatype->type->tokenId);
    }
    else if (function->type == VOID_FUNCTION){
        newNode->returnType = superMalloc(1,sizeof(struct pair ));
        newNode->returnType->type = VOID_TYPE;
    }
    newNode->definedVariables = programStatements(function->programStatements);
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
            newNode = fromDeclarationToVariable(ps->programUnitStatements->declaration,first);
            if(first == NULL ) {
                first = newNode;
            }
            if(prev != NULL && prev != newNode )prev -> next = newNode;
            prev = newNode;

            newNode = newNode->next;
        }
        if(ps->programUnitStatements->type == PUS_INSTANTIATION){
            checkInstantiation(ps->programUnitStatements->instantiation);
        }
        if(ps->programUnitStatements->type == PUS_ASSIGNATION){
            checkAssignation(ps->programUnitStatements->assignation);
        }
        ps = ps->ProgramStatements;
    }
    return first;
}

struct class * checkConstructorClassExists(struct class * classes, char * name){

}

void checkInstantiation(tInstantiation * instantiation){
//    struct class * constructorClass = checkConstructorClassExists(symbolTable.classes, instantiation->functionCall->functionName->associated_value.varname);
//    tArgumentValues * argument = instantiation->functionCall->firstArgument;
//    struct variable * parameters = constructorClass->constructor->parameters;
//    while (argument != NULL){
//        if(parameters == NULL)
//            fail();
//        if(argument->value->type != parameters->type)
//            fail();
//        parameters = parameters->next;
//        if(argument->commaNextArgumentValue != NULL)
//            argument = argument->commaNextArgumentValue->nextArgument;
//        else argument = NULL;
//    }
//    if(parameters != NULL)
//        fail();
}



void checkArrayAssignation(tArrayAssignation * arrayAssignation){
    switch (arrayAssignation->typeVariable) {
        case ARRAY_ASSIG_VARNAME:
            switch (arrayAssignation->typeAssignatedValue) {
                case ARRAY_ASSIG_INSTANTIATION:

                    break;
                case ARRAY_ASSIG_VALUE_SEMICOLON:

                    break;
            }
            break;
        case ARRAY_ASSIG_OBJECT_ATT:
            switch (arrayAssignation->typeAssignatedValue) {
                case ARRAY_ASSIG_INSTANTIATION:

                    break;
                case ARRAY_ASSIG_VALUE_SEMICOLON:

                    break;
            }
            break;
    }
}

void checkAssignation(tAssignation * assignation){
    switch (assignation->type) {
        case ASSIGNATION_ARRAY_ASSIG:
            checkArrayAssignation(assignation->arrayAssignation);
            break;
        case ASSIGNATION_SUBNODE:

            break;
    }
}

static struct variable * fromDeclarationToVariable(struct tDeclaration * declaration , struct variable * list ){
    struct variable * newNode = superMalloc(1,sizeof(struct variable));
    newNode->type = superMalloc(1,sizeof (struct pair ));
    newNode->objectType = NULL;
    switch (declaration->type) {
        case CHAR_DECLARATION:
            newNode->type->type= CHAR_TYPE;
            newNode->varname = declaration->charDeclaration->varname->associated_value.varname;
            break;
        case INTEGER_DECLARATION:
            newNode-> type->type = INT_TYPE;
            newNode->varname = declaration->integerDeclaration->varname->associated_value.varname;
            break;
        case INTEGER_ARRAY_DECLARATION:
            newNode-> type-> type = INTARRAY_TYPE;
            newNode->varname = declaration->integerArrayDeclaration->varname->associated_value.varname;
            break;
        case CHAR_ARRAY_DECLARATION:
            newNode-> type -> type= CHARARRAY_TYPE;
            newNode->varname = declaration->charArrayDeclaration->varname->associated_value.varname;
            break;
        case INTEGER_ASSIGNATION_DECLARATION:
            newNode->type-> type= INT_TYPE;
            newNode->varname = declaration->integerAssignationDeclaration->varname->associated_value.varname;
            break;
        case CHAR_ASSIGNATION_DECLARATION_DECLARATION:
            newNode-> type-> type = CHAR_TYPE;
            newNode->varname = declaration->charAssignationDeclaration->varname->associated_value.varname;
            break;
        case INTEGER_ARRAY_ASSIGNATION_DECLARATION:
            newNode->type-> type = INTARRAY_TYPE;
            newNode->varname = declaration->integerArrayAssignationDeclaration->varname->associated_value.varname;
            break;
        case CHAR_ARRAY_ASSIGNATION_DECLARATION:
            newNode-> type -> type= CHARARRAY_TYPE;
            newNode->varname = declaration->charArrayAssignationDeclaration->name->associated_value.varname;
            break;
        case DECLARATION_WITH_OBJECT_TYPE:

            switch (declaration->declarationAux->type) {
                        case ONLY_DECLARATION:
                            newNode->type-> type = OBJECT_TYPE;
                            newNode->varname = declaration->declarationAux->objectDataType->associated_value.varname;
                            newNode->objectType = declaration->declarationAux->name->associated_value.varname;
                            newNode->type->name = declaration->declarationAux->name->associated_value.varname;
                            break;
                        case ARRAY_ONLY_DECLARATION:
                            newNode->type-> type = OBJECTARRAY_TYPE;
                            newNode->varname = declaration->declarationAux->objectDataType->associated_value.varname;
                            newNode->objectType = declaration->declarationAux->name->associated_value.varname;
                            newNode->type->name = declaration->declarationAux->name->associated_value.varname;
                            break;
                        case ARRAY_WITH_INDEX_DECLARATION:
                            newNode->type-> type = OBJECTARRAY_TYPE;
                            newNode->varname = declaration->declarationAux->objectDataType->associated_value.varname;
                            newNode->objectType = declaration->declarationAux->name->associated_value.varname;
                            newNode->type->name = declaration->declarationAux->name->associated_value.varname;
                            break;
                        case INSTANTIATION:
                            newNode->type-> type = OBJECT_TYPE;
                            newNode->objectType = declaration->declarationAux->name->associated_value.varname;
                            newNode->varname = declaration->declarationAux->objectDataType->associated_value.varname;
                            newNode->type->name = declaration->declarationAux->name->associated_value.varname;
                            struct pair * aux = instantiation(declaration->declarationAux->assignationWithMethodFunctionInstantiation->instantiation);
                            equalPairs(newNode->type, aux);
                            break;
            }
            break;
    }
    if ( checkIfExistsVarname(newNode->varname  , list ) ){
        LogError("Variable with name %s has already been defined\n",newNode->varname);
        fail();
        return NULL;
    }
    return newNode;
}


static struct variable * fromParameterToVariable(tParameters * parameters ){
    if(parameters == NULL)
        return NULL;

    struct variable * newNode = superMalloc(1,sizeof(struct variable));
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
            newNode->type = superMalloc(1,sizeof(struct  pair )) ;
            newNode->type->type = OBJECT_TYPE;
            newNode->type->name = parameters->objectTypeName->associated_value.varname;
            newNode->objectType = parameters->objectTypeName->associated_value.varname;
            break;
        case MULTIOBJECT_PARAMETERS:
            newNode->type = superMalloc(1,sizeof(struct pair ));
            newNode->type->type = OBJECT_TYPE;
            newNode->type->name = parameters->objectTypeName->associated_value.varname;
            newNode->objectType = parameters->objectTypeName->associated_value.varname;
            newNode->next = fromParameterToVariable(parameters->nextParameters->nextParameters);
            break;
        case ARRAY_PARAMETERS:
            newNode->type = fromDeclarationTypeToVariableType(parameters);
            break;
        case MULTIARRAY_PARAMETERS:
            newNode->type = fromDeclarationTypeToVariableType(parameters);
            newNode->next = fromParameterToVariable(parameters->nextParameters->nextParameters);
            break;
        case OBJECTARRAY_PARAMETERS:
            newNode->type = superMalloc(1,sizeof(struct pair) );
            newNode->type->type =OBJECTARRAY_TYPE;
            newNode->type->name = parameters->objectTypeName->associated_value.varname;
            newNode->objectType = parameters->objectTypeName->associated_value.varname;
            break;
        case MULTIOBJECTARRAY_PARAMETERS:
            newNode->type = superMalloc(1,sizeof(struct pair));
            newNode->type->type = OBJECTARRAY_TYPE;
            newNode->type->name = parameters->objectTypeName->associated_value.varname;
            newNode->objectType = parameters->objectTypeName->associated_value.varname;
            newNode->next = fromParameterToVariable(parameters->nextParameters->nextParameters);
            break;
    }
    return  newNode;

}






static struct pair  * fromDataTypeToTypeTokenId(int  dataType){
    struct pair * pairType = superMalloc(1,sizeof (struct pair));
    pairType->name = NULL;
    if(dataType == INT )
            pairType->type = INT_TYPE;
    else pairType->type =  CHAR_TYPE;
    return pairType;
}


static struct pair *  fromDeclarationTypeToVariableType(tParameters  * parameters){
    struct pair * pairType  =superMalloc(1,sizeof(struct pair));
    if(parameters->datatype->type->tokenId == INT) {
        if (parameters->squareBrackets == NULL)  pairType->type=INT_TYPE;
        else  pairType->type=INTARRAY_TYPE;
    }else if(parameters->squareBrackets == NULL )  pairType->type=CHAR_TYPE;
    else  pairType->type=CHARARRAY_TYPE;
    return pairType;
}


struct pair * varname(tTokenNode * varname){
    return getVarByName(currentClassGlobal,currentMethodGlobal,varname->associated_value.varname)->type;
}

struct pair * arrayDesreferencingT(tArrayDesreferencing * arrayDesreferencing){
    struct variable * currentVariable = getVarByName(currentClassGlobal, currentMethodGlobal, arrayDesreferencing->varname->associated_value.varname);
    struct pair  * pair = superMalloc(1,sizeof(struct pair ))  ;
    if(currentVariable->type->type == INTARRAY_TYPE ){
        pair->type = INT_TYPE;
    } else if (currentVariable->type->type == CHARARRAY_TYPE){
        pair->type = CHAR_TYPE;
    }else if (currentVariable->type->type == OBJECTARRAY_TYPE){
        pair->type = OBJECT_TYPE;
        pair->name = currentVariable->objectType;
    } else {
        LogError("Variable %s is not an array\n", arrayDesreferencing->varname->associated_value.varname);
        fail();
    }
    return pair;
}

struct pair * integerExpression(tIntegerExpression * expression){
    struct pair * returnPair =superMalloc(1,sizeof(struct pair) );
    returnPair->type = INT_TYPE;
    switch (expression->type) {
            case INTEGER_EXPRESSION_COMMON :
                    integerExpression(expression->commonIntegerExpression->leftIntegerExpression);
                    integerExpression(expression->commonIntegerExpression->rightIntegerExpression);
                break;
            case INTEGER_EXPRESSION_FACTOR :
                return factorT(expression->factor);
                break;
            case INTEGER_EXPRESSION_ENCLOSED :
                integerExpression(expression->enclosedCommonIntegerExpression->integerExpression);
                break;
            case INTEGER_EXPRESSION_INCREMENT_DECREMENT :
                integerExpression(expression->decrementIncrementIntegerExpression->leftIntegerExpression);
                break;
    }
    return returnPair;

}


struct pair * factorT(tFactor * factor ) {
    switch (factor->type) {
        case FACTOR_OBJECT_ATT:
            return objectAttribute(factor->object_attribute);
            break;
        case FACTOR_FUNCTION_CALL:
            return functionCallT(factor->function_call);
            break;
        case FACTOR_VARNAME:
            return varname(factor->varname);
            break;
        case FACTOR_METHOD_CALL:
            return methodCallT(factor->method_call);
            break;
        case FACTOR_ARRAY_DESR:
            return arrayDesreferencingT(factor->array_desreferencing);
            break;
        case FACTOR_SUB_INT:
            return subInteger(factor->subInteger);
            break;
        case FACTOR_INT:
            return integer(factor->integer);
            break;
        case FACTOR_OBJECT_ARRAY_DESREFERENCING:
            return objectAttributeDesreferencing(factor->objectAttributeDesreferencing);
    }
    return NULL;
}

struct pair * innerAttribute(tInnerAttribute * attribute,char * className ){
    struct variable * currentVariable = getAttribute(getClassByName(className),attribute->innerAttributeName->associated_value.varname);
    return currentVariable->type ;
}


struct pair * objectAttributeDesreferencing(tObjectAttributeDesreferencing * objectAttributeDesreferencing){

    if(objectAttributeDesreferencing->innerAttribute == NULL ){
        struct pair * returnPair = superMalloc(1,sizeof(struct pair ));
        struct pair * left = objectAttribute(objectAttributeDesreferencing->objectAttribute);
        if(left->type == INTARRAY_TYPE ){
            returnPair->type = INT_TYPE;
        } else if (left->type == CHARARRAY_TYPE){
            returnPair->type = CHAR_TYPE;
        }else if (left->type == OBJECTARRAY_TYPE){
            returnPair->type = OBJECT_TYPE;
            returnPair->name = left->name;
        } else {
            LogError("Attribute %s is not an array\n", objectAttributeDesreferencing->objectAttribute->varnameRight->associated_value.varname);
            fail();
        }
        return returnPair;
    }else {
        struct pair * left = objectAttribute(objectAttributeDesreferencing->objectAttribute);
        if (left->type == OBJECTARRAY_TYPE){
            return innerAttribute(objectAttributeDesreferencing->innerAttribute,left->name);
        } else {
            LogError("Attribute %s is not an object array\n", objectAttributeDesreferencing->objectAttribute->varnameRight->associated_value.varname);
            fail();
        }

    }


}


struct pair * integer(tTokenNode * integer){
     struct pair * pair = superMalloc(1,sizeof( struct pair ));
     pair ->type = INT_TYPE;
     return pair;
}

struct pair * subInteger(tSubInteger *subInteger){
    struct pair * pair = superMalloc(1,sizeof( struct pair ));
    pair ->type = INT_TYPE;
    return pair;
}


struct pair * methodCallT(tMethodCall * methodCall){
    struct variable * cc = getVarByName(currentClassGlobal,currentMethodGlobal, methodCall->varname->associated_value.varname);
    if(cc->type->type != OBJECT_TYPE) {
        LogError("Variable %s is not an object\n", cc->varname);
        fail();
    }
    struct function * cM = getMethodByName(getClassByName(cc->type->name),methodCall->functionCall->functionName->associated_value.varname);
    struct variable * currentParameter = cM->parameters;
    tArgumentValues * passParameter = methodCall->functionCall->firstArgument;
    struct pair * currentParameterType;
    struct pair * receivedType ;
    while(currentParameter != NULL && passParameter != NULL){
        currentParameterType = currentParameter->type;
        receivedType = genericValueT(passParameter->value);
        equalPairs(receivedType,currentParameterType);
        currentParameter= currentParameter->next;
        if(passParameter->commaNextArgumentValue != NULL )
        passParameter = passParameter->commaNextArgumentValue->nextArgument;
        else passParameter = NULL;
    }
    if(currentParameter != NULL || passParameter != NULL){
        LogError("Wrong amount of parameters on %s call\n", methodCall->functionCall->functionName);
        fail();
    }
    return cM->returnType;
}


struct pair * functionCallT(tFunctionCall * functionCall ){
    struct pair * int_type = superMalloc(1,sizeof(struct pair));
    int_type->type = INT_TYPE;
    return int_type;
}


struct pair *  objectAttribute(tObjectAttribute * objectAttribute1 ){
    struct pair * leftPair, * aux;
//    if(strcmp(objectAttribute1->varnameLeft->associated_value.varname , "this") != 0 ){
        switch (objectAttribute1->type) {
            case OBJECT_ATTRIBUTE_VARNAME:
                if(strcmp(objectAttribute1->varnameLeft->associated_value.varname , "this") == 0 ){
                    if(currentClassGlobal == NULL){
                        LogError("this is a reserved word to refer objects attributes.\n");
                        fail();
                    }
                    leftPair = getAttributeFromVarname(currentClassGlobal,objectAttribute1->varnameRight->associated_value.varname)->type;
                }else{
                    leftPair = getAttributeFromVarname(getClassByName(objectAttribute1->varnameLeft->associated_value.varname),objectAttribute1->varnameRight->associated_value.varname)->type;
                }
                break;
            case OBJECT_ATTRIBUTE_OBJECT_ATTRIBUTE:
                aux = objectAttribute(objectAttribute1->objectAttribute);
                if(aux->type != OBJECT_TYPE){
                    LogError("Intentando acceder a los atributos de un tipo built-in.\n");
                    fail();
                }
                leftPair = getAttributeFromVarname(getClassByName(aux->name),objectAttribute1->varnameRight->associated_value.varname)->type;
                break;
            case OBJECT_ATTRIBUTE_ARRAY_DESREF:
                aux = arrayDesreferencingT(objectAttribute1->arrayDesreferencing);
                if(aux->type != OBJECT_TYPE){
                    LogError("Intentando acceder a los atributos de un tipo built-in.\n");
                    fail();
                }
                leftPair = getAttributeFromVarname(getClassByName(aux->name),objectAttribute1->varnameRight->associated_value.varname)->type;
                break;
        }

    return leftPair;
}

struct pair * instantiation(tInstantiation * instantiation){
    if(checkIfExistsClass(instantiation->functionCall->functionName->associated_value.varname, symbolTable->classes)){
        LogError("La clase %s no fue definida.\n",instantiation->functionCall->functionName->associated_value.varname);
        fail();
    }
    struct pair * p = superMalloc(1,sizeof(struct pair));
    p->type = OBJECT_TYPE;
    p->name = instantiation->functionCall->functionName->associated_value.varname;
    return p;
}

struct pair * charValueT(tCharValue * charValue){
    struct pair * p;
    switch (charValue->type) {
        case CHARACTER_CHARVALUE: {
            p = superMalloc(1,sizeof(struct pair));
            p->type = CHAR_TYPE;
            return p;
        }
        case OBJECTATTRIBUTE_CHARVALUE:{
            p = objectAttribute(charValue->objectAttribute);
            break;
        }
        case VARNAME_CHARVALUE:{
            p = getTypeFromVarname(charValue->varname->associated_value.varname);
            break;
        }
        case FUNCTIONCALL_CHARVALUE:{
            p = functionCallT(charValue->functionCall);
            break;
        }
        case METHODCALL_CHARVALUE:{
            p = methodCallT(charValue->methodCall);
            break;
        }
        case ARRAYDESREFERENCING_CHARVALUE:{
            p = arrayDesreferencingT(charValue->arrayDesreferencing);
            break;
        }
    }
    if(p->type == CHAR_TYPE)
        return p;
    LogError("Una expresion esta siendo tratada como caracter de manera incorrecta.\n");
    fail();
}

struct pair * genericArrayWithBracket(tGenericArrayWithBracket * genericArrayWithBracket){
    return genericArrayWithBracketRecursive(genericArrayWithBracket->genericValueArray);
}

struct pair * genericArrayWithBracketRecursive(tGenericValueArray * genericValueArray){
    struct pair * p1 = genericValueT(genericValueArray->genericValue);
    struct pair * p2;
    if(genericValueArray->commaGenericValueArray != NULL){
        p2 = genericArrayWithBracketRecursive(genericValueArray->commaGenericValueArray->genericValueArray);
    } else return p1;
    equalPairs(p1, p2);
    return p1;
}

struct pair * integerArrayWithBrackets(tIntegerArrayWithBrackets * integerArrayWithBrackets){
    return integerArrayWithBracketRecursive(integerArrayWithBrackets->integerArray);
}

struct pair * integerArrayWithBracketRecursive(tIntegerArray * integerArray){
    if(integerArray->commaIntegerArray != NULL)
        integerArrayWithBracketRecursive(integerArray->commaIntegerArray->next);
    return integerExpression(integerArray->integerExpression);
}

struct pair * charArrayWithBrackets(tCharArrayWithBrackets * charArrayWithBrackets){
    return charArrayWithBracketRecursive(charArrayWithBrackets->characterArray);
}

struct pair * charArrayWithBracketRecursive(tCharacterArray * characterArray){
    if(characterArray->commaCharacterArray != NULL)
        charArrayWithBracketRecursive(characterArray->commaCharacterArray->next);
    return charValueT(characterArray->charValue);
}

struct pair * arrayAssignationSubnode(tArrayAssignationSubnode * arrayAssignationSubnode){
    switch (arrayAssignationSubnode->type) {
        case ARRAY_ASSIG_SUB_NODE_CHARACTER_ARRAY:{
            return charArrayWithBrackets(arrayAssignationSubnode->characterArray);
        }
        case ARRAY_ASSIG_SUB_NODE_GENERIC_ARRAY_WITH_BRACKETS:{
            return genericArrayWithBracket(arrayAssignationSubnode->genericArrayWithBrackets);
        }
        case ARRAY_ASSIG_SUB_NODE_INTEGER_ARRAY:{
            integerArrayWithBrackets(arrayAssignationSubnode->integerArray);
            break;
        }
        case ARRAY_ASSIG_SUB_NODE_STRING:{
            struct pair * p = superMalloc(1,sizeof(struct pair));
            p->type = CHARARRAY_TYPE;
            break;
        }
    }
    return NULL;
}

struct pair * simpleAssignationSubnode(tSimpleAssignationSubnode * simpleAssignationSubnode){
    switch (simpleAssignationSubnode->type) {
        case SIMPLE_ASSIG_SUB_NODE_INSTANTIATION:
            return instantiation(simpleAssignationSubnode->instantiation);
        case SIMPLE_ASSIG_SUB_NODE_ARRAY_VALUE_SEMICOLON:
            return genericValueT(simpleAssignationSubnode->arrayValueSemicolon->value);
    }
    return NULL;
}

struct pair * superSubnode(tSuperSubnode * subnode){
    struct pair * p1, * p2;
    switch (subnode->typeVariable) {
        case SUPER_SUB_NODE_VARNAME: {
            p1 = varname(subnode->varname);
            break;
        }
        case SUPER_SUB_NODE_OBJECT_ATT:{
            p1 = objectAttribute(subnode->objectAttribute);
            break;
        }
    }
    switch (subnode->typeAssignation) {
        case SUPER_SUB_NODE_ARRAY_ASSIG_SUB_NODE:{
            p2 = arrayAssignationSubnode(subnode->arrayAssignationSubnode);
            break;
        }
        case SUPER_SUB_NODE_SIMPLE_ASSIG_SUB_NODE:{
            p2 = simpleAssignationSubnode(subnode->simpleAssignationSubnode);
            break;
        }
    }
    equalPairs(p1, p2);
    return p1;
}

struct pair * arrayAssignation(tArrayAssignation * arrayAssignation){
    struct pair * p1, * p2, *p3 = superMalloc(1,sizeof(struct pair));
    switch (arrayAssignation->typeVariable) {
        case ARRAY_ASSIG_VARNAME: {
            p1 = varname(arrayAssignation->varname);
            break;
        }
        case ARRAY_ASSIG_OBJECT_ATT:{
            p1 = objectAttribute(arrayAssignation->objectAttribute);
            switch (p1->type) {
                case OBJECTARRAY_TYPE:{
                    p3->type = OBJECT_TYPE;
                    p3->name = p1->name;
                    break;
                }
                case INTARRAY_TYPE:
                    p3->type = INT_TYPE;
                    break;
                case CHARARRAY_TYPE:
                    p3->type = CHAR_TYPE;
                    break;

            }
            break;
        }
    }
    switch (arrayAssignation->typeAssignatedValue) {
        case ARRAY_ASSIG_INSTANTIATION:{
            p2 = instantiation(arrayAssignation->instantiation);
            break;
        }
        case ARRAY_ASSIG_VALUE_SEMICOLON:{
            p2 = genericValueT(arrayAssignation->valueSemicolon->value);
            break;
        }
    }
    equalPairs(p3, p2);
    return p3;
}

struct pair * assignation(tAssignation * assignation){
    switch (assignation->type) {
        case ASSIGNATION_ARRAY_ASSIG:{
          return arrayAssignation(assignation->arrayAssignation);
        }
        case ASSIGNATION_SUBNODE:{
          return superSubnode(assignation->assignationSubnode);
        }
    }
    return NULL;
}

struct pair * comparationT(tComparation * comparation){
    genericValueT(comparation->lValue);
    genericValueT(comparation->rValue);
    struct pair * p = superMalloc(1,sizeof(struct pair));
    p->type = INT_TYPE;
    return p;
}

struct pair * valueComparatorValue(tValueComparatorValue * valueComparatorValue){
    genericValueT(valueComparatorValue->lValue);
    genericValueT(valueComparatorValue->rValue);
    struct pair * p = superMalloc(1,sizeof(struct pair));
    p->type = INT_TYPE;
    return p;
}

struct pair * logicalComparationUnit(tLogicalComparationUnit * logicalComparationUnit){
    comparationT(logicalComparationUnit->comparation);
    conditionUnit(logicalComparationUnit->conditionUnit);
    struct pair * p = superMalloc(1,sizeof(struct pair));
    p->type = INT_TYPE;
    return p;
}

struct pair * conditionUnit(tConditionUnit * conditionUnit1){
    switch (conditionUnit1->type) {
        case CUT_COMPARATION:{
            return comparationT(conditionUnit1->comparation);
        }
        case CUT_CONDITION:{
            return conditionUnit(conditionUnit1->condition->conditionUnit);
        }
        case CUT_LOGICAL_COMPARATION_UNIT:{
            return logicalComparationUnit(conditionUnit1->logicalComparationUnit);
        }
        case CUT_VALUE_COMPARATOR_VALUE:{
            return valueComparatorValue(conditionUnit1->valueComparatorValue);
        }
    }
}

struct pair * whileLoopT(tWhileLoop * loop){
    conditionUnit(loop->conditionClause->conditionUnit);
    programStatements(loop->clause->programStatements);
    return NULL;
}

struct pair * ifType(tIf * ifBlock){
    conditionUnit(ifBlock->condition->conditionUnit);
    programStatements(ifBlock->clause->programStatements);
    return NULL;
}

void equalPairs(struct pair * p1, struct pair * p2){
    if(p1->type == p2->type){
        if(p1->type == OBJECT_TYPE) {
            if(strcmp(p1->name, p2->name) == 0)
                return;
            else {
                LogError("Existe una asignacion incorrecta, los tipos no coinciden.\n");
                fail();
            }
        }
        return;
    }
    LogError("Existe una asignacion incorrecta, los tipos no coinciden.\n");
    fail();
}

void  programUnitStatementsT(tProgramUnitStatements * programUnitStatements){
    switch (programUnitStatements->type){
                case PUS_WHILE_LOOP:
                     whileLoopT(programUnitStatements->whileLoop);
                     break;
                case PUS_IF_CONDITION:
                     ifType(programUnitStatements->ifCondition);
                    break;
                case PUS_ASSIGNATION:
                     assignation(programUnitStatements->assignation);
                    break;
                case PUS_RETURN_RESERVED:
                     returnType(programUnitStatements->returnReserved);
                    break;
                case PUS_INSTANTIATION:
                     instantiation(programUnitStatements->instantiation);
                    break ;
                case PUS_INTEGER_EXPRESSION_SEMICOLON:
                     integerExpression(programUnitStatements->integerExpressionSemicolon->integerExpression);
    }
}

struct variable * programStatements(tProgramStatements * programStatements1){
    if(programStatements1 == NULL )
        return NULL;

    struct variable * newNode = NULL;
    struct variable * first = NULL ;
    struct variable * prev = NULL ;
    struct variable * this;
    if(currentMethodGlobal != NULL && currentMethodGlobal->definedVariables == NULL) {
        this = superMalloc(1,sizeof(*this));
            this->type = superMalloc(1,sizeof(struct pair));
            this->varname = "this";
            this->type->type = OBJECT_TYPE ;
            this->type->name = currentClassGlobal->className;
            this->objectType = currentClassGlobal->className;
            currentMethodGlobal->definedVariables = this;
    }
    tProgramStatements *  ps = programStatements1;
    while (ps != NULL && ps->programUnitStatements != NULL ){
        if(ps->programUnitStatements->type == PUS_DECLARATION){
            newNode = fromDeclarationToVariable(ps->programUnitStatements->declaration,first);
            if(first == NULL ){
                first = newNode;
                struct variable * aux;
                if(currentMethodGlobal == NULL) {
                    aux = symbolTable->main->definedVariables;
                    if(aux == NULL)
                        symbolTable->main->definedVariables = first;
                    else{
                        while (aux ->next!= NULL) aux = aux->next;
                        aux->next = first;
                    }
                }else{
                    aux = currentMethodGlobal->definedVariables;
                    while (aux ->next!= NULL) aux = aux->next;
                    aux->next = first;
                }

            }
            if(prev != NULL && prev != newNode )prev -> next = newNode;
            prev = newNode;

            newNode = newNode->next;
        }
        else programUnitStatementsT(ps->programUnitStatements);
        ps = ps->ProgramStatements;
    }
    if(currentMethodGlobal == NULL )
        return symbolTable->main->definedVariables;
    else return currentMethodGlobal->definedVariables;
}


void fail(){
    //// free
    superFree();
    exit(EXIT_FAILURE);
}


boolean checkIfExistsAttribute(char * attributeName, struct variable * attributeList){
    struct variable * currentClass = attributeList ;
    while(currentClass != NULL ){
        if(strcmp(attributeName,attributeList->varname ) ==  0)
            return true;
        currentClass = currentClass -> next;
    }
    return false;
}





boolean  checkIfExistsVarname(char * varname   , struct  variable * list ){
    struct variable * current  = list ;
    while(current != NULL ){
        if(strcmp(varname, current->varname) == 0 )
            return true;
        current = current->next;
    }
    return false;
}

boolean checkIfExistsFunction(char * functionName, struct function * functions ){
   if(functions == NULL )
       return false;
   struct function * currentFunction = functions;
   while(currentFunction != NULL ){
       if(strcmp( functionName , currentFunction->functionName) == 0 )
           return true;
       currentFunction = currentFunction->next;
   }
   return false;


}


boolean checkIfExistsClass(char * className, struct class * classList){
    struct class * currentClass = classList;
    while(currentClass != NULL){
        if( strcmp(className,currentClass->className) ==0 )
            return false;
        currentClass  = currentClass -> next;
    }
    return true;
}


struct variable * getAttribute(struct class  * currentClass , char * attribute){
    struct variable * currentAttribute = currentClass->attributes;
    while(currentAttribute!=NULL){
        if(strcmp(attribute,currentAttribute->varname ) == 0 )
            return currentAttribute;
        currentAttribute = currentAttribute ->next;
    }
    LogError("Attribute %s is not defined on %s\n",varname,currentClass->className);
    fail();
    return NULL ;
}



struct pair *  getTypeFromVarname(char * varname) {


    struct variable * leftVariable = getVarByName(currentClassGlobal,currentMethodGlobal,varname);
    if(leftVariable == NULL ){
        LogError("Variable %s is not defined \n",varname);
        fail();
    }
    else return leftVariable->type ;

}


struct variable * getAttributeFromVarname(struct class * currentClass , char * varname){
    struct class * currentClassLocal = currentClass;
    struct variable * currentVariable;
    while(currentClassLocal!= NULL ){
         currentVariable = currentClassLocal->attributes;
        while (currentVariable!= NULL ) {
            if (strcmp(varname, currentVariable->varname) == 0)
                return currentVariable;
            currentVariable = currentVariable->next;
        }
        if(currentClassLocal->fatherName != NULL)
            currentClassLocal = getClassByName(currentClassLocal->fatherName);
        else currentClassLocal = NULL;
    }

    LogError("Attribute %s is not defined on %s\n",varname,currentClass->className);
    fail();
    return NULL ;
}



struct  class * getClassByNameAux(char * name ){
    if(currentClassGlobal!=NULL && strcmp(name , currentClassGlobal->className) ==  0)
        return currentClassGlobal;

    struct class * currentClass1 = symbolTable->classes;
    while(currentClass1 != NULL){
        if(strcmp(currentClass1->className,name) == 0 )
            return currentClass1;
        currentClass1 = currentClass1->next;
    }
    return NULL ;
}


boolean  isMethodOnFatherAndSon(char * methodName, char * class ){
    struct class * currentClass = getClassByNameAux(class);
    boolean  present;
    if(currentClass ->fatherName == NULL)
        return false;
    struct class * fatherClass = getClassByNameAux(currentClass->fatherName);
    struct function * fatherMethods = fatherClass->methods;
    while(fatherMethods!=NULL){
        if(strcmp(fatherMethods->functionName,methodName) == 0 )
            present = true;
        fatherMethods = fatherMethods->next;
    }
    if(!present)
        return false;

    struct function *sonMethods= currentClass->methods;
    while(sonMethods !=NULL){
        if(strcmp(sonMethods->functionName,methodName) == 0 )
            return true;
        sonMethods= sonMethods->next;
    }
    return false;
}



boolean isMethodFromFather(char * className ,char * methodName) {
    struct class * currentClass = getClassByNameAux(className);
    if(currentClass->fatherName == NULL )
        return false;

    struct class *fatherClass = getClassByNameAux(currentClass->fatherName);
    if (fatherClass == NULL)
        return false;

    struct function *fatherMethods = fatherClass->methods;
    while (fatherMethods != NULL) {
        if (strcmp(fatherMethods->functionName, methodName) == 0)
            return true;
        fatherMethods = fatherMethods->next;
    }
    return false;

}





boolean isMethodFromFatherMain(char * varname ,char * methodName) {
    struct variable *mainVariables = symbolTable->main->definedVariables;
    while (mainVariables != NULL) {
        if (strcmp(varname, mainVariables->varname) == 0)
            break;
        mainVariables = mainVariables->next;
    }
    if (mainVariables == NULL)
        return false;
    struct class *currentClass = getClassByNameAux(mainVariables->objectType);
    if (currentClass == NULL || currentClass->fatherName == NULL)
        return false;
    struct class *fatherClass = getClassByNameAux(currentClass->fatherName);
    struct function *fatherMethods = fatherClass->methods;
    while (fatherMethods != NULL) {
        if (strcmp(fatherMethods->functionName, methodName) == 0)
            return true;
        fatherMethods = fatherMethods->next;
    }
    return false;
}

#include "semantic-analysis.h"
int getParametersNeed(struct function * function );
boolean  checkIfExistsVarname(char * varname   , struct  variable * list );
boolean checkIfExistsFunction(char * function , char * className);
boolean checkIfExistsAttribute(char * attributeName, struct variable * attributeList);
boolean checkIfExistsClass(char * className, struct class * classList);
boolean checkIfMatches(char * leftVarname, char * rightVarname, struct pair  * type);


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


struct global  symbolTable;
struct class * currentClass;
struct function * currentMethod;
struct variable * scopeVariables;



boolean  isMethodOnFatherAndSon(char * methodName, char * class ){
//    struct class * currentClass = getClassByName(class);
//    if(currentClass ->fatherName == NULL)
//        return false;
//    struct function * methodCall  = getMethodByName(class ,methodName);
//    if(methodCall == NULL )
//        return  false;
//    methodCall = getMethodByName(currentClass->fatherName ,methodName);
//    if(methodCall == NULL)
//        return false;
    return true;
}
boolean isMethodFromFather(char * varname ,char * methodName){
//
//    struct variable * variableStruct = getVarFromMain(varname);
//    if(variableStruct == NULL)
//        return false;
//    struct class * currentClass = getClassByName(variableStruct->objectType);
//    if(currentClass == NULL )
//        return false;
//    struct function * methodCall  = getMethodByName(variableStruct->objectType,methodName);
//    if(methodCall == NULL && currentClass->fatherName == NULL  )
//        return  false;
//    else if(methodCall == NULL  && currentClass->fatherName != NULL ){
//        methodCall = getMethodByName(currentClass->fatherName,methodName);
//        if(methodCall == NULL)
//            return false;
//        else
//            return true;
//
//    }
//    return false ;
return true;

}
int  isMethodCallValid(char * methodName,char * variable , tArgumentValues * parameters){
//    struct variable * currentVariable = getVarFromMain(variable);
//    if(currentVariable == NULL )
//        return -4;
//    if(currentVariable -> type != OBJECT_TYPE)
//        return -2 ;
//    struct function * methodCall = getMethodByName(currentVariable->objectType , methodName);
//    struct class * currentClass = getClassByName(currentVariable->objectType);
//    if(methodCall == NULL && currentClass->fatherName == NULL  )
//        return  -3;
//    else if(methodCall == NULL  && currentClass->fatherName != NULL ){
//        methodCall = getMethodByName(currentClass->fatherName,methodName);
//        if(methodCall == NULL)
//            return -3;
//    }
//
//    int NeedParameters = getParametersNeed(methodCall);
//    tArgumentValues  * counting = parameters;
//    int parametersC = 0 ;
//    while (counting != NULL){
//        parametersC++;
//        if(counting->commaNextArgumentValue == NULL)
//            break;
//        counting = counting->commaNextArgumentValue->nextArgument;
//    }
//    if( parametersC - 1 == NeedParameters)
//        return 1 ;
//    else return -1;
    return true;
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
//    struct variable * leftVariable = getVarByName(class,method,leftValue);
//    struct variable * rightVariable = getVarByName(class,method,rightValue);
//    if(leftVariable == NULL || rightVariable == NULL)
//        return false;
//    if(leftVariable -> type == 5 && rightVariable->type == 5 ){
//        return strcmp(leftVariable->objectType,rightVariable->objectType)==0;
//    }
//    return (leftVariable->type == rightVariable->type);
    return true;
}
boolean isAttributeValid(char * className , char * variable){
//    struct class * currentClass = getClassByName(className);
//
//    if(currentClass == NULL)
//        return false; //no class with such name
//    else{
//        struct variable * currentAttribute = currentClass->attributes;
//        while(currentAttribute!=NULL){
//            if(strcmp(currentAttribute->varname,variable) == 0)
//                return true;
//            currentAttribute = currentAttribute->next;
//        }
//        return false;
//    }
    return true;
}

struct variable * getVarFromMainT(char * name ){
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



//deberia sacar de currentScope
struct variable * getVarByName(struct class  * class , struct function * methodName , char * name ){
    struct function * method;

        //return
    //if(strcmp(methodName , "main") == 0 ){
    if(class == NULL && methodName == NULL ) method = symbolTable.main;
    else method =methodName;

        struct variable * currentVariable = scopeVariables;
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
        fail();
        return NULL ;

}


struct function * getMethodByName(struct class  * currentClass1 , char * name ){
    if(currentClass1 == NULL){
        fail();
        return NULL;
    }
    struct function * currentMethod1 = currentClass1->methods;
    while (currentMethod1 != NULL ){
        if(strcmp(currentMethod1->functionName,name) == 0 )
            return currentMethod1;
        currentMethod1 = currentMethod1 -> next ;
    }
    fail();
    return NULL;
}



struct  class * getClassByName(char * name ){
    struct class * currentClass1 = symbolTable.classes;
    while(currentClass1 != NULL){
        if(strcmp(currentClass1->className,name) == 0 )
            return currentClass1;
        currentClass1 = currentClass1->next;
    }
    fail();
    return NULL ;
}


struct global * generateSymbolTable(tProgram * program){
    struct global * newNode = malloc(sizeof(struct global)) ;
    if(program->type == PROGRAM_MAIN){
        currentClass = NULL;
        newNode->main = addMain(program->mainFunction);
    }else {
            struct class * auxClass = addClass(program->classesAndMain->class);
            newNode = generateSymbolTable(program->classesAndMain->program);
            auxClass->next = newNode->classes;
            newNode->classes = auxClass;
            return newNode;
    }


//    struct global * newNode = &symbolTable; //malloc(sizeof(struct global));
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
    currentClass = NULL;
    currentMethod = NULL ;
    struct function * newNode = malloc(sizeof(struct function )) ;
    newNode->functionName = "main";
    newNode->parameters = fromParameterToVariable(mainFunction->parameters);
    newNode->definedVariables = programStatements(mainFunction->programStatements);
    newNode->returnType = malloc(sizeof(struct pair));
    newNode->returnType->type = INT_TYPE;
    return  newNode;
}

struct class * addClass(tClass * aClass){
    if(aClass == NULL )
        return NULL;
    struct class * newNode = malloc(sizeof(struct class));
    currentClass = newNode;
    newNode->className = aClass->varname->associated_value.varname;
    currentClass = newNode->className;
    if(aClass->extendsName != NULL && aClass->extendsName->extendedClassName->associated_value.varname!=NULL) newNode->fatherName = aClass->extendsName->extendedClassName->associated_value.varname;
    newNode->attributes = addAttribute(aClass->classIn->attributes);
    newNode->constructor = addConstructor(aClass->classIn->constructor);
    newNode->methods = addMethods(aClass->classIn->methods);
    return newNode;
}


struct function * addConstructor(tConstructor * constructor){
    struct function * newNode = malloc(sizeof(struct function));
    currentMethod = newNode;
    newNode->parameters = fromParameterToVariable(constructor->function->parameters);
    newNode->definedVariables = programStatements(constructor->function->programStatements);
    struct pair * returnType = malloc(sizeof(struct pair));
    returnType->type = OBJECT_TYPE;
    returnType->name = currentClass;
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
//        if ( checkIfExistsAttribute(currentVariable->varname, first) ) {
//            printf("Error: This class has an attribute defined twice ");
//            fail();
//        }
            current = current->declarations;
        if(prev!=NULL && prev != currentVariable ) prev->next = currentVariable;
        prev = currentVariable;
        currentVariable = currentVariable->next;
    }
    return  first;
}

struct pair * returnType(tReturn * returnType){
    struct pair * returnFunction;
    if(currentClass != NULL) {
        returnFunction = getMethodByName(currentClass, currentMethod)->returnType;
    }else
        returnFunction = getMain()->returnType;
    struct pair * pair = malloc(sizeof(struct pair ));
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
    struct pair * currentPair = malloc(sizeof(struct pair ));
    switch (genericValue->type) {
        case GENERIC_VALUE_INTEGER:
            return integerExpression(genericValue->integerExpression);
        case GENERIC_VALUE_STRING:
            currentPair->type = CHARARRAY_TYPE ;
            break;
        case GENERIC_VALUE_CHARACTER:
            currentPair->type = CHAR_TYPE;
            break;
    }

}



struct function * addMethods(tMethods * methods){
    if(methods == NULL )
        return NULL ;
    currentMethod = methods->function->varname->associated_value.varname;
    struct tMethods  * cM = methods;
    struct function * first = NULL;
    struct function * prev  = NULL;
    struct function * current ;
    while(cM != NULL ){
        current = addFunction(cM->function);
        if(checkIfExistsFunction(current->functionName,currentClass)){
            printf("Error: method %s has already been defined\n",current->functionName);
            fail();
        }

        if(first == NULL )
            first = current ;

        if(prev != NULL && prev != current) prev->next = current;
        prev = current;

        cM = cM -> methods;
    }
    return first;
}




struct function *  addFunction(tFunction * function){
    struct function * newNode = malloc(sizeof(struct function )) ;
    currentMethod = newNode;
    newNode->functionName = function->varname->associated_value.varname;
    newNode->parameters = fromParameterToVariable(function->parameters);
    newNode->definedVariables = programStatements(function->programStatements);
    if(function->type == DATATYPE_FUNCTION )
        newNode->returnType = fromDataTypeToTypeTokenId(function->datatype->type->tokenId);
    else if (function->type == VOID_FUNCTION){
        newNode->returnType = malloc(sizeof(struct pair ));
        newNode->returnType->type = VOID_TYPE;
    }
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
    struct variable * newNode = malloc(sizeof(struct variable));
    newNode->type = malloc(sizeof (struct pair ));
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
            newNode->type-> type = OBJECT_TYPE;
            newNode->varname = declaration->declarationAux->objectDataType->associated_value.varname;
            newNode->objectType = declaration->declarationAux->name->associated_value.varname;
            newNode->type->name = declaration->declarationAux->name->associated_value.varname;
            break;
    }
    if ( checkIfExistsVarname(newNode->varname  , list ) ){
        printf("Error : variable with name %s has already been defined\n",newNode->varname);
        fail();
        return NULL;
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
            newNode->type = malloc(sizeof(struct  pair )) ;
            newNode->type->type = OBJECT_TYPE;
            newNode->objectType = parameters->objectTypeName->associated_value.varname;
            break;
        case MULTIOBJECT_PARAMETERS:
            newNode->type = malloc(sizeof(struct pair ));
            newNode->type->type = OBJECT_TYPE;
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
            newNode->type = malloc(sizeof(struct pair) );
            newNode->type->type =OBJECTARRAY_TYPE;
            newNode->objectType = parameters->objectTypeName->associated_value.varname;
            break;
        case MULTIOBJECTARRAY_PARAMETERS:
            newNode->type = malloc(sizeof(struct pair));
            newNode->type->type = OBJECTARRAY_TYPE;
            newNode->objectType = parameters->objectTypeName->associated_value.varname;
            newNode->next = fromParameterToVariable(parameters->nextParameters->nextParameters);
            break;
    }
    return  newNode;

}






static struct pair  * fromDataTypeToTypeTokenId(int  dataType){
    struct pair * pairType = malloc(sizeof (struct pair));
    pairType->name = NULL;
    if(dataType == INT )
            pairType->type = INT_TYPE;
    else pairType->type =  CHAR_TYPE;
    return pairType;
}


static struct pair *  fromDeclarationTypeToVariableType(tParameters  * parameters){
    struct pair * pairType  =malloc(sizeof(struct pair));
    if(parameters->datatype->type->tokenId == INT) {
        if (parameters->squareBrackets == NULL)  pairType->type=INT_TYPE;
        else  pairType->type=INTARRAY_TYPE;
    }else if(parameters->squareBrackets == NULL )  pairType->type=CHAR_TYPE;
    else  pairType->type=CHARARRAY_TYPE;
    return pairType;
}


struct pair * varname(tTokenNode * varname){
    return getVarByName(currentClass,currentMethod,varname->associated_value.varname)->type;
}

struct pair * arrayDesreferencingT(tArrayDesreferencing * arrayDesreferencing){
    struct variable * currentVariable = getVarByName(currentClass, currentMethod, arrayDesreferencing->varname->associated_value.varname);
    struct pair  * pair = malloc(sizeof(struct pair ))  ;
    if(currentVariable->type->type == INTARRAY_TYPE ){
        pair->type = INT_TYPE;
    } else if (currentVariable->type->type == CHARARRAY_TYPE){
        pair->type = CHAR_TYPE;
    }else if (currentVariable->type->type == OBJECTARRAY_TYPE){
        pair->type = OBJECT_TYPE;
        pair->name = currentVariable->objectType;
    } else fail();
    return pair;
}

struct pair * integerExpression(tIntegerExpression * expression){
    struct pair * returnPair =malloc(sizeof(struct pair) );
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
    }
    return NULL;
}

struct pair * innerAttribute(tInnerAttribute * attribute,char * className ){
    struct variable * currentVariable = getAttribute(className,attribute->innerAttributeName->associated_value.varname);
    return currentVariable->type ;
}


struct pair * objectAttributeDesreferencing(tObjectAttributeDesreferencing * objectAttributeDesreferencing){

    if(objectAttributeDesreferencing->innerAttribute == NULL ){
        struct pair * returnPair = malloc(sizeof(struct pair ));
        struct pair * left = objectAttribute(objectAttributeDesreferencing->objectAttribute);
        if(left->type == INTARRAY_TYPE ){
            returnPair->type = INT_TYPE;
        } else if (left->type == CHARARRAY_TYPE){
            returnPair->type = CHAR_TYPE;
        }else if (left->type == OBJECTARRAY_TYPE){
            returnPair->type = OBJECT_TYPE;
            returnPair->name = left->name;
        } else fail();
    }else {
        return innerAttribute(objectAttributeDesreferencing->innerAttribute,objectAttributeDesreferencing->objectAttribute->varnameRight->associated_value.varname);
    }


}


struct pair * integer(tTokenNode * integer){
     struct pair * pair = malloc(sizeof( struct pair ));
     pair ->type = INT_TYPE;
     return pair;
}

struct pair * subInteger(tSubInteger *subInteger){
    struct pair * pair = malloc(sizeof( struct pair ));
    pair ->type = INT_TYPE;
    return pair;
}


struct pair * methodCallT(tMethodCall * methodCall){
    struct variable * cc = getVarByName(currentClass,currentMethod, methodCall->varname->associated_value.varname);
    struct function * cM = getMethodByName(cc->type->name,methodCall->functionCall->functionName->associated_value.varname);
    struct pair * cp =  functionCallT(methodCall->functionCall);
    equalPairs(cM->returnType, cp) ;
    return cp;

}


struct pair * functionCallT(tFunctionCall * functionCall ){
    struct function * getFunction = getMethodByName(currentClass, functionCall->functionName->associated_value.varname);
    struct variable * currentParameter = getFunction->parameters;
    tArgumentValues * passParameter = functionCall->firstArgument;
    struct pair * currentParameterType;
    struct pair * receivedType ;
    while(currentParameter != NULL ){
        currentParameterType = currentParameter->type;
        receivedType = genericValueT(passParameter->value);
        equalPairs(receivedType,currentParameterType);
        currentParameter= currentParameter->next;
        passParameter = passParameter->commaNextArgumentValue->nextArgument;
    }
    return getFunction->returnType;
}


struct pair *  objectAttribute(tObjectAttribute * objectAttribute1 ){
    struct pair * leftPair;
    switch (objectAttribute1->type) {
        case OBJECT_ATTRIBUTE_VARNAME:
            leftPair = getTypeFromVarname(objectAttribute1->varnameLeft->associated_value.varname);
            break;
        case OBJECT_ATTRIBUTE_OBJECT_ATTRIBUTE:
            leftPair = objectAttribute(objectAttribute1->objectAttribute);
            break;
        case OBJECT_ATTRIBUTE_ARRAY_DESREF:
            leftPair = arrayDesreferencingT(objectAttribute1->arrayDesreferencing);
            break;
    }
    struct pair * rightPair = getTypeFromVarname(objectAttribute1->varnameRight->associated_value.varname);
    equalPairs(leftPair,rightPair);
    return leftPair;
}

struct pair * instantiation(tInstantiation * instantiation){
    if(checkIfExistsClass(instantiation->functionCall->functionName->associated_value.varname, symbolTable.classes))
        fail();
    struct pair * p = malloc(sizeof(struct pair));
    p->type = OBJECT_TYPE;
    p->name = instantiation->functionCall->functionName->associated_value.varname;
    return p;
}

struct pair * charValueT(tCharValue * charValue){
    struct pair * p;
    switch (charValue->type) {
        case CHARACTER_CHARVALUE: {
            p = malloc(sizeof(struct pair));
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
            struct pair * p = malloc(sizeof(struct pair));
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
            arrayAssignationSubnode(subnode->arrayAssignationSubnode);
            break;
        }
        case SUPER_SUB_NODE_SIMPLE_ASSIG_SUB_NODE:{
            simpleAssignationSubnode(subnode->simpleAssignationSubnode);
            break;
        }
    }
    equalPairs(p1, p2);
    return p1;
}

struct pair * arrayAssignation(tArrayAssignation * arrayAssignation){
    struct pair * p1, * p2;
    switch (arrayAssignation->typeVariable) {
        case ARRAY_ASSIG_VARNAME: {
            p1 = varname(arrayAssignation->varname);
            break;
        }
        case ARRAY_ASSIG_OBJECT_ATT:{
            p1 = objectAttribute(arrayAssignation->objectAttribute);
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
    equalPairs(p1, p2);
    return p1;
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
    struct pair * p = malloc(sizeof(struct pair));
    p->type = INT_TYPE;
    return p;
}

struct pair * valueComparatorValue(tValueComparatorValue * valueComparatorValue){
    genericValueT(valueComparatorValue->lValue);
    genericValueT(valueComparatorValue->rValue);
    struct pair * p = malloc(sizeof(struct pair));
    p->type = INT_TYPE;
    return p;
}

struct pair * logicalComparationUnit(tLogicalComparationUnit * logicalComparationUnit){
    comparationT(logicalComparationUnit->comparation);
    conditionUnit(logicalComparationUnit->conditionUnit);
    struct pair * p = malloc(sizeof(struct pair));
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
            else fail();
        }
        return;
    }
    fail();
}

void  programUnitStatementsT(tProgramUnitStatements * programUnitStatements){
    switch (programUnitStatements->type){
                case PUS_WHILE_LOOP:
                     whileLoopT(programUnitStatements->whileLoop);
                case PUS_IF_CONDITION:
                     ifType(programUnitStatements->ifCondition);
                case PUS_ASSIGNATION:
                     assignation(programUnitStatements->assignation);
                case PUS_RETURN_RESERVED:
                     returnType(programUnitStatements->returnReserved);
                case PUS_INSTANTIATION:
                     instantiation(programUnitStatements->instantiation);
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
    tProgramStatements *  ps = programStatements1;
    while (ps != NULL && ps->programUnitStatements != NULL ){
        if(ps->programUnitStatements->type == PUS_DECLARATION){
            newNode = fromDeclarationToVariable(ps->programUnitStatements->declaration,first);
            if(first == NULL ) {
                first = newNode;
                scopeVariables = first;
            }
            if(prev != NULL && prev != newNode )prev -> next = newNode;
            prev = newNode;

            newNode = newNode->next;
        }
        else programUnitStatementsT(ps->programUnitStatements);
        ps = ps->ProgramStatements;
    }
    scopeVariables = NULL ;
    return first;
}


void fail(){
    //// free
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

boolean checkIfExistsFunction(char * functionName, char * class ){
    struct class * currentClass = getClassByName(class);
    while(class != NULL ){
        if(strcmp(functionName,currentClass->className) == 0 )
            return true;
        currentClass = currentClass->next ;
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

boolean checkIfMatches(char * leftVarname, char * rightVarname, struct pair  * type){
//    struct variable * leftVariable = getVarByName(currentClass,currentMethod,leftVarname);
//    struct variable * rightVariable = getVarByName(currentClass,currentMethod,rightVarname);
//    if(leftVariable == NULL || rightVarname == NULL)
//        return false ;
//    else{
//        type ->type = rightVariable->type->type;
//        if(rightVariable->type == OBJECT_TYPE || rightVariable->type == OBJECTARRAY_TYPE)
//            type->name = rightVariable->objectType;
//        return rightVariable->type == leftVariable->type;
//    }
    return true;
}

struct variable * getAttribute(struct class  * currentClass , char * attribute){
    struct variable * currentAttribute = currentClass->attributes;
    while(currentAttribute!=NULL){
        if(strcmp(attribute,currentAttribute->varname ) == 0 )
            return currentAttribute;
        currentAttribute = currentAttribute ->next;
    }
    fail();
    return NULL ;
}



struct pair *  getTypeFromVarname(char * varname) {
    struct variable * leftVariable = getVarByName(currentClass,currentMethod,varname);
    if(leftVariable == NULL ){
        fail();
    }
    else return leftVariable->type ;

}

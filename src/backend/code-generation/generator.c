#include <stdlib.h>
#include "../support/logger.h"
#include "generator.h"
#include "../../frontend/syntactic-analysis/bison-parser.h"
#include "../semantic-analysis/semantic-analysis.h"
#include "../support/supermalloc.h"


/**
 * Implementación de "generator.h".
 */

int recursiveProgram(tProgram * program);//
int Class(tClass * class);//
void Methods(tMethods * methods);
void Main(tMainFunction * mainFunction);
int Attributes(tAttributes * attributes);
int Constructor(tConstructor * attributes);
int MethodsRecursive(tMethods * attributes,char * className);
void Function(tFunction * function,char * className);
int Declaration(tDeclaration * declaration);
int DeclarationsRecursive(tDeclarations * declarations);
int IntegerArrayRecursive(tCommaIntegerArray * array);
void CharValue(tCharValue * value);
int Operator(int operator);
int Factor(tFactor * factor);
void ObjectAttribute(tObjectAttribute* objectAttribute);
void FunctionCall(tFunctionCall * objectAttribute);
void MethodCall(tMethodCall * objectAttribute);
void ArrayDesreferencing(tArrayDesreferencing * objectAttribute);
void Parameters(tParameters * parameters);
void ProgramStatements(tProgramStatements * programStatements);
void BasicParameters(tParameters * parameters);
void MultiBasicParameters(tParameters * parameters);
int IntegerExpression(tIntegerExpression * integerExpression);
void ObjectParameters(tParameters * parameters);
void MultiObjectParameters(tParameters * parameters);
void ProgramUnitStatements(tProgramUnitStatements * programUnitStatements);
void WhileLoop(tWhileLoop * whileLoop);
void ConditionUnit(tConditionUnit * conditionUnit);
void DataType(tDataType * dataType);
void Comparation(tComparation * comparation);
void ComparisonOperator(tComparisonOperator * comparisonOperator);
void LogicalOperator(tLogicalOperator * logicalOperator);
void ArrayParameters(tParameters * parameters);
void MultiArrayParameters(tParameters * parameters);
void ObjectArrayParameters(tParameters * parameters);
void MultiObjectArrayParameters(tParameters * parameters );
//void Value(tValue * value);
void ArgumentValues(tArgumentValues * argumentValues);
void If(tIf * if_node);
void Assignation(tAssignation * assignation);
void Instantiation(tInstantiation * instantiation);
void Return(tReturn * return_node);
void ArrayAssignation(tArrayAssignation * assignation);
void GenericValue(tGenericValue* genericValue);
void DeclarationWithObjectType(tDeclarationWithObjectDataType * declarationWithObjectDataType);


void Methods(tMethods * methods);
void ClassIn(tClassIn* classIn);
void IntegerAssignationDeclaration(tIntegerAssignationDeclaration* integerAssignationDeclaration);
void CharAssignationDeclaration(tCharAssignationDeclaration* charAssignationDeclaration);
void IntegerArrayAssignationDeclaration(tIntegerArrayAssignationDeclaration integerArrayAssignationDeclaration);
void CharArrayAssignationDeclaration(tCharArrayAssignationDeclaration* charArrayAssignationDeclaration);
void IntegerArray(tIntegerArray* integerArray);
void CharacterArray(tCharacterArray* characterArray);
void CharDeclaration(tCharDeclaration* charDeclaration);
void IntegerArrayDeclaration(tIntegerArrayDeclaration * integerArrayDeclaration);
void CharArrayDeclaration(tCharArrayDeclaration * charArrayDeclaration);



FILE * fd;
char * fatherName = NULL;
boolean  isExtended = false;
boolean isCorrect = true;
char * currentClass;
char * currentFunction ;
char * msg;
char * leftName;
char * callingVariable;
char * calllingMethod;


int Generator(tProgram * program, FILE * filedescriptor) {
//	LogInfo("El resultado de la expresion computada es: '%d'.", program);
    fd = filedescriptor;
    int final_result = 0;
    fprintf(fd,"#include <stdio.h>\n");
    fprintf(fd,"#include <stdlib.h>\n");
    recursiveProgram(program);
    if(isCorrect)
        return final_result;
    else{
//        printf("%s",msg);
        return -1 ;
    }
}

void IntegerAssignationDeclaration(tIntegerAssignationDeclaration* integerAssignationDeclaration) {
    fprintf(fd, " int %s =", integerAssignationDeclaration->varname->associated_value.varname);
    IntegerExpression(integerAssignationDeclaration->integerExpression);
    fprintf(fd, ";/n");
}

void CharAssignationDeclaration(tCharAssignationDeclaration* charAssignationDeclaration) {
    fprintf(fd, " char %s =", charAssignationDeclaration->varname->associated_value.varname);
    CharValue(charAssignationDeclaration->charValue);
    fprintf(fd, ";/n");
}



//void Methods(tMethods * methods){
//    Function(methods->function);
//    if(methods->methods != NULL )
//        Methods(methods->methods);
//}

int recursiveProgram(tProgram * program){

    if(program->type == PROGRAM_MAIN){
        Main(program->mainFunction);

    } else{
        Class(program->classesAndMain->class);

        if(program->classesAndMain->program != NULL)
        recursiveProgram(program->classesAndMain->program);
    }
    return 0;
}
boolean haveClassStruct;
int Class(tClass * class){
    currentClass = class->varname->associated_value.varname;
    //// Creo la struct si tengo o atributos o extiendo alguna clase
    if((class->classIn->attributes != NULL && class->classIn->attributes->declarations != NULL) || class->extendsName != NULL){
        fprintf(fd, "struct %s{\n", class->varname->associated_value.varname);

        if (class->extendsName != NULL) {
            fprintf(fd, "struct %s * extended_%s;\n", class->extendsName->extendedClassName->associated_value.varname,
                    class->extendsName->extendedClassName->associated_value.varname);
            isExtended = true;
            fatherName = class->extendsName->extendedClassName->associated_value.varname;
        }

        if (class->classIn->attributes != NULL && class->classIn->attributes->declarations != NULL) {

            Attributes(class->classIn->attributes);
        }
        fprintf(fd, "};\n");
        Constructor(class->classIn->constructor);
    } else {
        //// Minimal reference
        fprintf(fd, "struct %s{char minReference;};\n", class->varname->associated_value.varname);
        Constructor(class->classIn->constructor);
    }

    if(class->classIn->methods != NULL) {
        Function(class->classIn->methods->function, class->varname->associated_value.varname);
        if(class->classIn->methods->methods != NULL) {
            MethodsRecursive(class->classIn->methods->methods, class->varname->associated_value.varname);
        }
    }
    return 0;
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
if(CHAR_DECLARATION == declaration->type){
    fprintf(fd, "char %s;\n", declaration->charDeclaration->varname->associated_value.varname);
}
if(INTEGER_DECLARATION == declaration->type){
    fprintf(fd, "int %s;\n", declaration->integerDeclaration->varname->associated_value.varname);
}
if(INTEGER_ARRAY_DECLARATION == declaration->type){
    if(declaration->integerArrayDeclaration->integerExpression != NULL) {
        fprintf(fd, "int %s[", declaration->integerArrayDeclaration->varname->associated_value.varname);
        IntegerExpression(declaration->integerArrayDeclaration->integerExpression);
        fprintf(fd, "];\n");
    } else fprintf(fd, "int * %s;\n", declaration->integerArrayDeclaration->varname->associated_value.varname);
}
if(CHAR_ARRAY_DECLARATION == declaration->type){
    if(declaration->charArrayDeclaration->integerExpression != NULL) {
        fprintf(fd, "char %s[", declaration->charArrayDeclaration->varname->associated_value.varname);
        IntegerExpression(declaration->charArrayDeclaration->integerExpression);
        fprintf(fd, "];\n");
    } else fprintf(fd, "char * %s;\n", declaration->charArrayDeclaration->varname->associated_value.varname);
}
if(INTEGER_ASSIGNATION_DECLARATION == declaration->type){
    fprintf(fd, "int %s = ", declaration->integerAssignationDeclaration->varname->associated_value.varname);
    IntegerExpression(declaration->integerAssignationDeclaration->integerExpression);
    fprintf(fd, ";\n");
}
if(CHAR_ASSIGNATION_DECLARATION_DECLARATION == declaration->type){
    fprintf(fd, "char %s = '%c';\n", declaration->charAssignationDeclaration->varname->associated_value.varname, declaration->charAssignationDeclaration->charValue->character->associated_value.charValue);
}
if(INTEGER_ARRAY_ASSIGNATION_DECLARATION == declaration->type){
    fprintf(fd, "int %s[] = {", declaration->integerArrayAssignationDeclaration->varname->associated_value.varname);
    IntegerExpression(declaration->integerArrayAssignationDeclaration->integerArray->integerExpression);
    IntegerArrayRecursive(declaration->integerArrayAssignationDeclaration->integerArray->commaIntegerArray);
    fprintf(fd, "};\n");
}
if(CHAR_ARRAY_ASSIGNATION_DECLARATION == declaration->type){
    fprintf(fd, "char %s[] = ", declaration->charArrayAssignationDeclaration->name->associated_value.varname);
    if(declaration->charArrayAssignationDeclaration->type == CHAR_ARRAY_WITH_BRACKETS){

        tCharacterArray * array = declaration->charArrayAssignationDeclaration->charArrayWithBrackets->characterArray;
        while(array->charValue != NULL){
            CharValue(array->charValue);
            if(array->commaCharacterArray == NULL)
                array = NULL;
            else
                array = array->commaCharacterArray->next;
        }

    }
    if(declaration->charArrayAssignationDeclaration->type == CHAR_ARRAY_STRING)
        fprintf(fd, "\"%s\"", declaration->charArrayAssignationDeclaration->string->associated_value.varname);

    fprintf(fd, ";\n");
}
if(DECLARATION_WITH_OBJECT_TYPE == declaration->type){
    DeclarationWithObjectType(declaration->declarationAux);
}
    return result;
}

void DeclarationWithObjectType(tDeclarationWithObjectDataType * declarationWithObjectDataType){
    fprintf(fd,"struct %s * ",declarationWithObjectDataType->name->associated_value.varname);
    fprintf(fd,"%s ", declarationWithObjectDataType->objectDataType->associated_value.varname);
    switch (declarationWithObjectDataType->type) {
        case  ONLY_DECLARATION:
            fprintf(fd,";\n");
            break;
        case  ARRAY_ONLY_DECLARATION:
            fprintf(fd,"[];\n");
            break;
        case  ARRAY_WITH_INDEX_DECLARATION:
            fprintf(fd,"[");
            IntegerExpression(declarationWithObjectDataType->squareBracketsWithSize->size);
            fprintf(fd,"];\n");
            break;
        case  INSTANTIATION:
            fprintf(fd," = ");
            Instantiation(declarationWithObjectDataType->assignationWithMethodFunctionInstantiation->instantiation);
            break;

    }

}




int IntegerExpression(tIntegerExpression * integerExpression){

    if(integerExpression->type == INTEGER_EXPRESSION_FACTOR){
        Factor(integerExpression->factor);
    }
    if(integerExpression->type == INTEGER_EXPRESSION_COMMON){
        IntegerExpression(integerExpression->commonIntegerExpression->leftIntegerExpression);
        Operator(integerExpression->commonIntegerExpression->operator->tokenId);
        IntegerExpression(integerExpression->commonIntegerExpression->rightIntegerExpression);
    }
    if(integerExpression->type == INTEGER_EXPRESSION_ENCLOSED){
        fprintf(fd, "(");
        IntegerExpression(integerExpression->enclosedCommonIntegerExpression->integerExpression);
        fprintf(fd, ")");
    }
    if(integerExpression->type == INTEGER_EXPRESSION_INCREMENT_DECREMENT){
        IntegerExpression(integerExpression->decrementIncrementIntegerExpression->leftIntegerExpression);
        Operator(integerExpression->decrementIncrementIntegerExpression->operator->tokenId);
    }

    return 0;

}

int Factor(tFactor * factor){
if(FACTOR_OBJECT_ATT == factor->type){
    ObjectAttribute(factor->object_attribute);
}
if(FACTOR_FUNCTION_CALL == factor->type){
    FunctionCall(factor->function_call);
}
if(FACTOR_VARNAME == factor->type){
        fprintf(fd, "%s", factor->varname->associated_value.varname);
}
if(FACTOR_METHOD_CALL == factor->type){
    MethodCall(factor->method_call);
}
if(FACTOR_ARRAY_DESR == factor->type){
    ArrayDesreferencing(factor->array_desreferencing);
}
if(FACTOR_SUB_INT == factor->type){
    fprintf(fd, "-%d", factor->subInteger->integer->associated_value.integerValue);
}
if(FACTOR_INT == factor->type){
    fprintf(fd, "%d", factor->integer->associated_value.integerValue);
}
    if(factor->type == FACTOR_OBJECT_ARRAY_DESREFERENCING){
        ObjectAttribute(factor->objectAttributeDesreferencing->objectAttribute);
    fprintf(fd, "[");
    IntegerExpression(factor->objectAttributeDesreferencing->index);
    fprintf(fd, "]");
    if(factor->objectAttributeDesreferencing->innerAttribute != NULL){
        fprintf(fd, "->%s", factor->objectAttributeDesreferencing->innerAttribute->innerAttributeName->associated_value.varname);
    }
    }
    return 0;
}

int Operator(int operator){
    if(operator == ADD)
        fprintf(fd, "+");
    if(operator == SUB)
        fprintf(fd, "-");
    if(operator == DIV)
        fprintf(fd, "/");
    if(operator == MUL)
        fprintf(fd, "*");
    if(operator == INCREMENT)
        fprintf(fd, "++");
    if(operator == DECREMENT)
        fprintf(fd, "--");
    return 0;
}

int IntegerArrayRecursive(tCommaIntegerArray * array){
    if(array == NULL)
        return 0;
    fprintf(fd, ", ");
    IntegerExpression(array->next->integerExpression);
    return IntegerArrayRecursive(array->next->commaIntegerArray);
}

int DeclarationsRecursive(tDeclarations * declarations){
    int result;
    result = Declaration(declarations->declaration);
    if(declarations->declarations != NULL)
        result = DeclarationsRecursive(declarations->declarations);
    return result;
}


int Constructor(tConstructor * constructor){
    char * className=constructor->function->varname->associated_value.varname;
    fprintf(fd, "struct %s * constructor_%s(", className, className);
    Parameters(constructor->function->parameters);
    fprintf(fd, "){\n");

    fprintf(fd, "struct %s *  this = malloc(sizeof(struct %s));\n",className,className);
    if(isExtended)
        fprintf(fd,"this->extended_%s = malloc(sizeof(struct %s));\n",fatherName,fatherName);

    ProgramStatements(constructor->function->programStatements);

    fprintf(fd, "return this;\n");
    fprintf(fd, "}\n");
    return 0;
}

int MethodsRecursive(tMethods * methods, char * className){
    if(methods == NULL)
        return 0;
    Function(methods->function, className);
    if(methods->methods != NULL)
        MethodsRecursive(methods->methods,className);
    return 0;
}

void Main(tMainFunction * mainFunction){
    currentFunction = "main";
    fprintf(fd,"int main("); 
    Parameters(mainFunction->parameters); 
    fprintf(fd,"){\n");
    ProgramStatements(mainFunction->programStatements); 
    fprintf(fd,"\n}");
    currentFunction = NULL ;
}

void Function(tFunction * function,char * className){
    currentFunction = function->varname->associated_value.varname;
    switch(function->type){
       case DATATYPE_FUNCTION:
           DataType(function->datatype);
           break;
       case VOID_FUNCTION:
           fprintf(fd,"void ");
           break;
    };
    if(currentFunction != NULL && currentClass != NULL && isMethodOnFatherAndSon(currentFunction,currentClass))
        fprintf(fd,"override_");
    fprintf(fd,"%s",function->varname->associated_value.varname);
    fprintf(fd,"(");
    if(className != NULL) {
        if(function->parameters != NULL)
            fprintf(fd, "struct  %s  * this, ",className);
        else fprintf(fd, "struct  %s  * this",className);
    }

    Parameters(function->parameters);
    fprintf(fd,")");
    fprintf(fd,"{\n");
    ProgramStatements(function->programStatements);
    fprintf(fd,"}\n");
}

void CharValue(tCharValue * value){

    switch (value->type) {
         case CHARACTER_CHARVALUE:
             fprintf(fd,"'%c'",value->character->associated_value.charValue);
             break;
         case OBJECTATTRIBUTE_CHARVALUE:
             ObjectAttribute(value->objectAttribute);
             break;
         case FUNCTIONCALL_CHARVALUE:
             FunctionCall(value->functionCall);
             break;
         case METHODCALL_CHARVALUE:
             MethodCall(value->methodCall);
             break;
         case VARNAME_CHARVALUE:
             fprintf(fd,"%s",value->varname->associated_value.varname);
             break;
         case ARRAYDESREFERENCING_CHARVALUE:
             ArrayDesreferencing(value->arrayDesreferencing);
             break;
    }
}

void ObjectAttribute(tObjectAttribute* objectAttribute){
    switch (objectAttribute->type) {
        case OBJECT_ATTRIBUTE_VARNAME:{
            if(isExtended)
                fprintf(fd, "%s->extended_%s->%s", objectAttribute->varnameLeft->associated_value.varname,fatherName, objectAttribute->varnameRight->associated_value.varname);
            else{
                fprintf(fd, "%s->%s", objectAttribute->varnameLeft->associated_value.varname, objectAttribute->varnameRight->associated_value.varname);
            }
            break;
        }
        case OBJECT_ATTRIBUTE_OBJECT_ATTRIBUTE:{
            ObjectAttribute(objectAttribute->objectAttribute);
            fprintf(fd, "->%s", objectAttribute->varnameRight->associated_value.varname);
        }
        case OBJECT_ATTRIBUTE_ARRAY_DESREF:{
            ArrayDesreferencing(objectAttribute->arrayDesreferencing);
            fprintf(fd, "->%s", objectAttribute->varnameRight->associated_value.varname);
        }
    }
}
void FunctionCall(tFunctionCall * objectAttribute){
    fprintf(fd,"%s",objectAttribute->functionName->associated_value.varname);
//    if( calllingMethod != NULL &&   isMethodFromFatherClass(currentClass,calllingMethod) ){
//        fprintf(fd, "%s->extended_%s", genericValue->varname->associated_value.varname,fatherName);
//    }
    fprintf(fd,"(");
    ArgumentValues(objectAttribute->firstArgument);
    fprintf(fd,")");
}


void ArgumentValues(tArgumentValues * argumentValues){
    if(argumentValues == NULL)
        return;
    GenericValue(argumentValues->value);
    if(argumentValues->commaNextArgumentValue!=NULL){
        fprintf(fd,",");
        ArgumentValues(argumentValues->commaNextArgumentValue->nextArgument);
    }
}


void MethodCall(tMethodCall * objectAttribute){
    //// Agrego un Argument más que sea la estructura de la clase.
    calllingMethod = objectAttribute->functionCall->functionName->associated_value.varname;
    tArgumentValues * argumentValues = superMalloc(1,sizeof(tArgumentValues));
    argumentValues->value = superMalloc(1,sizeof(tGenericValue));
    argumentValues->value->type = GENERIC_VALUE_VARNAME;
    argumentValues->value->varname = objectAttribute->varname;
    callingVariable = objectAttribute->varname->associated_value.varname;
    if(objectAttribute->functionCall->firstArgument != NULL) {
        argumentValues->commaNextArgumentValue = superMalloc(1,sizeof(tCommaNextArgumentValue));
        argumentValues->commaNextArgumentValue->nextArgument = objectAttribute->functionCall->firstArgument;
        argumentValues->commaNextArgumentValue->comma = superMalloc(1,sizeof(tTokenNode));
        argumentValues->commaNextArgumentValue->comma->tokenId = COMMA;
    }
    objectAttribute->functionCall->firstArgument = argumentValues;
    FunctionCall(objectAttribute->functionCall);
}
void ArrayDesreferencing(tArrayDesreferencing * objectAttribute){
    fprintf(fd,"%s",objectAttribute->varname->associated_value.varname);
    fprintf(fd,"[");
    IntegerExpression(objectAttribute->integerExpression);
    fprintf(fd,"]");
}

void Parameters(tParameters * parameters){
    if(parameters == NULL)
        return;
    switch (parameters->type) {
        case BASIC_PARAMETERS:
            BasicParameters(parameters);
            break;
        case MULTIBASIC_PARAMETERS:
            MultiBasicParameters(parameters);
            break;
        case OBJECT_PARAMETERS:
            ObjectParameters(parameters);
            break;
        case MULTIOBJECT_PARAMETERS:
            MultiObjectParameters(parameters);
            break;
        case ARRAY_PARAMETERS:
            ArrayParameters(parameters);
            break;
        case MULTIARRAY_PARAMETERS:
            MultiArrayParameters(parameters);
            break;
        case OBJECTARRAY_PARAMETERS:
            ObjectArrayParameters(parameters);
            break;
        case MULTIOBJECTARRAY_PARAMETERS:
            MultiObjectArrayParameters(parameters);
            break;
    }
    
}

void BasicParameters(tParameters * parameters){
    DataType(parameters->datatype);
    fprintf(fd, "%s",parameters->paramName->associated_value.varname);
}

void MultiBasicParameters(tParameters * parameters){
    BasicParameters(parameters);
    if(parameters->nextParameters != NULL ){
        fprintf(fd,",");
        Parameters(parameters->nextParameters->nextParameters);
    }
}

void ObjectParameters(tParameters * parameters){
    fprintf(fd, "struct %s * %s",parameters->objectTypeName->associated_value.varname,parameters->paramName->associated_value.varname);
}

void MultiObjectParameters(tParameters * parameters){
    ObjectParameters(parameters) ;
    if(parameters->nextParameters != NULL ){
        fprintf(fd,",");
        Parameters(parameters->nextParameters->nextParameters);
    }
}

void ArrayParameters(tParameters * parameters){
    DataType(parameters->datatype);
    fprintf(fd,"%s",parameters->paramName->associated_value.varname);
    fprintf(fd,"[]");
}


void MultiArrayParameters(tParameters * parameters){
    ArrayParameters(parameters);
    if(parameters->nextParameters!=NULL) {
        fprintf(fd,",");
        Parameters(parameters->nextParameters->nextParameters);
    }
}


void ObjectArrayParameters(tParameters * parameters){
    ObjectParameters(parameters);
    fprintf(fd,"[]");
}

void MultiObjectArrayParameters(tParameters * parameters ){
    ObjectParameters(parameters);
    if(parameters->nextParameters != NULL ) {
        fprintf(fd,",");
        Parameters(parameters);
    }
}




void ComparisonOperator(tComparisonOperator * comparisonOperator){
    switch (comparisonOperator->greaterOp->tokenId) {
        case EQUAL_OP:{
            fprintf(fd, " == ");
            break;
        }
        case NOT_EQUAL_OP:{
            fprintf(fd, " != ");
            break;
        }
        case LOWER_OP:{
            fprintf(fd, " < ");
            break;
        }
        case LOWEREQ_OP:{
            fprintf(fd, " <= ");
            break;
        }
        case GREATER_OP:{
            fprintf(fd, " > ");
            break;
        }
        case GREATEREQ_OP:{
            fprintf(fd, " >= ");
            break;
        }
    }
}

void LogicalOperator(tLogicalOperator * logicalOperator){
    switch (logicalOperator->orToken->tokenId) {
        case AND:{
            fprintf(fd, " && ");
            break;
        }
        case OR:{
            fprintf(fd, " || ");
            break;
        }
    }
}


void Comparation(tComparation * comparation){
    GenericValue(comparation->lValue);
    ComparisonOperator(comparation->comparisonOperator);
    GenericValue(comparation->rValue);
}

void ConditionUnit(tConditionUnit * conditionUnit){
    switch (conditionUnit->type) {
        case CUT_COMPARATION:{
            Comparation(conditionUnit->comparation);
            break;
        }
        case CUT_VALUE_COMPARATOR_VALUE:{
            GenericValue(conditionUnit->valueComparatorValue->lValue);
            LogicalOperator(conditionUnit->valueComparatorValue->logicalOperator);
            GenericValue(conditionUnit->valueComparatorValue->rValue);
            break;
        }
        case CUT_LOGICAL_COMPARATION_UNIT:{
            Comparation(conditionUnit->logicalComparationUnit->comparation);
            fprintf(fd, " ");
            LogicalOperator(conditionUnit->logicalComparationUnit->logicalOperator);
            fprintf(fd, " ");
            ConditionUnit(conditionUnit->logicalComparationUnit->conditionUnit);
            break;
        }
        case CUT_CONDITION:{
            fprintf(fd, "(");
            ConditionUnit(conditionUnit->condition->conditionUnit);
            fprintf(fd, ")");
            break;
        }
    }
}

//void Value(tValue * value){
//    switch (value->type) {
//        case VALUE_CHARACTER:{
//            fprintf(fd, "'%c'", value->character->associated_value.charValue);
//            break;
//        }
//        case VALUE_STRING:{
//            fprintf(fd, "\"%s\"", value->string->associated_value.varname);
//            break;
//        }
//        case VALUE_INTEGER_EXPRESSION:{
//            IntegerExpression(value->integerExpression);
//            break;
//        }
//        case VALUE_OBJECT_ATTRIBUTE_DESREFERENCING:{
//            ObjectAttribute(value->objectAttributeDesreferencing->objectAttribute);
//            fprintf(fd, "[");
//            IntegerExpression(value->objectAttributeDesreferencing->index);
//            fprintf(fd, "]->%s", value->objectAttributeDesreferencing->pointInnerAtributte->innerAttributeName->associated_value.varname);
//            break;
//        }
//    }
//}

void WhileLoop(tWhileLoop * whileLoop){
    fprintf(fd, "while(");
    ConditionUnit(whileLoop->conditionClause->conditionUnit);
    fprintf(fd, "){\n");
    ProgramStatements(whileLoop->clause->programStatements);
    fprintf(fd, "}\n");
}

void If_translation(tIf * if_node){
    fprintf(fd, "if( ");
    ConditionUnit(if_node->condition->conditionUnit);
    fprintf(fd, " ){\n");
    ProgramStatements(if_node->clause->programStatements);
    fprintf(fd, " }\n");
    if(if_node->ifElseStatement != NULL){
        fprintf(fd, "else{\n");
        ProgramStatements(if_node->ifElseStatement->clause->programStatements);
        fprintf(fd, " }\n");
    }
}

void ArrayAssignation(tArrayAssignation * assignation){
    switch (assignation->typeVariable)
    {
    case ARRAY_ASSIG_VARNAME:
        fprintf(fd, "%s", assignation->varname->associated_value.varname);
        break;
    case ARRAY_ASSIG_OBJECT_ATT:
        ObjectAttribute(assignation->objectAttribute);
        break;
    default:
        break;
    }

    fprintf(fd, " [ ");
    IntegerExpression(assignation->index);
    fprintf(fd, " ] = ");
    switch(assignation->typeAssignatedValue){
        case ARRAY_ASSIG_VALUE_SEMICOLON:
            GenericValue(assignation->valueSemicolon->value);
            fprintf(fd, ";\n");
            break;
        case ARRAY_ASSIG_INSTANTIATION:
            Instantiation(assignation->instantiation);
    }

}

void GenericValueArray(tGenericValueArray * genericValueArray){
    if(genericValueArray == NULL)
        return;
    if(genericValueArray->genericValue == NULL)
        return;
    GenericValue(genericValueArray->genericValue);
    if(genericValueArray->commaGenericValueArray != NULL){
        fprintf(fd, ", ");
        GenericValueArray(genericValueArray->commaGenericValueArray->genericValueArray);
    }
}

void CharValueArray(tCharacterArray * characterArray){
    if(characterArray == NULL)
        return;
    if(characterArray->charValue == NULL)
        return;
    CharValue(characterArray->charValue);
    if(characterArray->commaCharacterArray != NULL){
        fprintf(fd, ", ");
        CharValueArray(characterArray->commaCharacterArray->next);
    }
}

void SuperSubnode(tSuperSubnode * subnode){
    switch (subnode->typeVariable) {
        case SUPER_SUB_NODE_VARNAME:{
            fprintf(fd, "%s", subnode->varname->associated_value.varname);
            leftName = subnode->varname->associated_value.varname;
            break;
        }
        case SUPER_SUB_NODE_OBJECT_ATT:{
            ObjectAttribute(subnode->objectAttribute);
            break;
        }
    }
    switch (subnode->typeAssignation) {
        case SUPER_SUB_NODE_ARRAY_ASSIG_SUB_NODE:{
            fprintf(fd, "[] = ");
            switch (subnode->arrayAssignationSubnode->type) {
                case ARRAY_ASSIG_SUB_NODE_GENERIC_ARRAY_WITH_BRACKETS:{
                    fprintf(fd, "{ ");
                    GenericValueArray(subnode->arrayAssignationSubnode->genericArrayWithBrackets->genericValueArray);
                    fprintf(fd, " }\n");
                    break;
                }
                case ARRAY_ASSIG_SUB_NODE_INTEGER_ARRAY:{
                    fprintf(fd, "{ ");
                    IntegerExpression(subnode->arrayAssignationSubnode->integerArray->integerArray->integerExpression);
                    IntegerArrayRecursive(subnode->arrayAssignationSubnode->integerArray->integerArray->commaIntegerArray);
                    fprintf(fd, " }\n");
                    break;
                }
                case ARRAY_ASSIG_SUB_NODE_CHARACTER_ARRAY:{
                    fprintf(fd, "{ ");
                    CharValueArray(subnode->arrayAssignationSubnode->characterArray->characterArray);
                    fprintf(fd, " }\n");
                    break;
                }
                case ARRAY_ASSIG_SUB_NODE_STRING:{
                    fprintf(fd, "\"%s\"", subnode->arrayAssignationSubnode->string->associated_value.varname);
                    break;
                }
            }
            fprintf(fd, ";\n");
            break;
        }
        case SUPER_SUB_NODE_SIMPLE_ASSIG_SUB_NODE:{
            fprintf(fd, " = ");
            switch (subnode->simpleAssignationSubnode->type)
            {
            case SIMPLE_ASSIG_SUB_NODE_ARRAY_VALUE_SEMICOLON:{
                GenericValue(subnode->simpleAssignationSubnode->arrayValueSemicolon->value);
                fprintf(fd, ";\n");
                break;
            }
            case SIMPLE_ASSIG_SUB_NODE_INSTANTIATION:
                Instantiation(subnode->simpleAssignationSubnode->instantiation);
                break;
            }
            break;
        }
    }
    leftName = NULL ;
}

void Assignation(tAssignation * assignation){
    switch (assignation->type) {
        case ASSIGNATION_SUBNODE:{
            SuperSubnode(assignation->assignationSubnode);
            break;
        }
        case ASSIGNATION_ARRAY_ASSIG:{
            ArrayAssignation(assignation->arrayAssignation);
            break;
        }
    }
}

void Return(tReturn * return_node){
    fprintf(fd, "return ");

    switch (return_node->type) {
        case RETURN_CONDITION:
            ConditionUnit(return_node->valueUnion.conditionUnit);
            break;
        case RETURN_VALUE:
            GenericValue(return_node->valueUnion.value);
            break;
        case RETURN_VOID:
            break;
    }

    fprintf(fd, ";\n");
}

void Instantiation(tInstantiation * instantiation){

    fprintf(fd, "constructor_%s(", instantiation->functionCall->functionName->associated_value.varname);
    ArgumentValues(instantiation->functionCall->firstArgument);
    fprintf(fd, ");\n");
}

void ProgramUnitStatements(tProgramUnitStatements * programUnitStatements){
    switch (programUnitStatements->type) {
        case PUS_DECLARATION:{
            Declaration(programUnitStatements->declaration);
            break;
        }
        case PUS_WHILE_LOOP:{
            WhileLoop(programUnitStatements->whileLoop);
            break;
        }
        case PUS_IF_CONDITION:{
            If_translation(programUnitStatements->ifCondition);
            break;
        }
        case PUS_ASSIGNATION:{
            Assignation(programUnitStatements->assignation);
            break;
        }
        case PUS_RETURN_RESERVED:{
            Return(programUnitStatements->returnReserved);
            break;
        }
        case PUS_INSTANTIATION:{
            Instantiation(programUnitStatements->instantiation);
            break;
        }
        case PUS_INTEGER_EXPRESSION_SEMICOLON:{
            IntegerExpression(programUnitStatements->integerExpressionSemicolon->integerExpression);
            fprintf(fd, ";\n");
            break;
        }
    }
}
void ProgramStatements(tProgramStatements * programStatements){
    if(programStatements == NULL)
        return;
    ProgramUnitStatements(programStatements->programUnitStatements);
    if(programStatements->ProgramStatements != NULL)
        ProgramStatements(programStatements->ProgramStatements);
}



void DataType(tDataType * dataType){
    if(dataType->type->tokenId == CHAR)
        fprintf(fd,"char ");
    else if(dataType->type->tokenId == INT)
        fprintf(fd,"int ");
}

void CharacterArray(tCharacterArray * characterArray){
    CharValue(characterArray->charValue);
    if(characterArray->commaCharacterArray!=NULL){
        fprintf(fd,",");
        CharacterArray(characterArray->commaCharacterArray->next);
    }
}


void IntegerArray(tIntegerArray* integerArray){
    IntegerExpression(integerArray->integerExpression);
    if(integerArray->commaIntegerArray != NULL ){
        fprintf(fd,",");
        IntegerArray(integerArray->commaIntegerArray->next);
    }
}


void GenericValue(tGenericValue* genericValue){
    switch(genericValue->type){
        case GENERIC_VALUE_CHARACTER:
            fprintf(fd,"%c",genericValue->character->associated_value.charValue); 
        break;
        case GENERIC_VALUE_INTEGER:
            fprintf(fd,"%d",genericValue->integer->associated_value.integerValue);
        break;
        case GENERIC_VALUE_OBJECT_ATTRIBUTE:
            ObjectAttribute(genericValue->objectAttribute);
        break;
        case GENERIC_VALUE_METHOD_CALL:
            MethodCall(genericValue->methodCall); 
        break;
        case GENERIC_VALUE_FUNCTION_CALL:
            FunctionCall(genericValue->functionCall);
        break;
        case GENERIC_VALUE_VARNAME:
            if( calllingMethod != NULL &&   isMethodFromFatherMain(genericValue->varname->associated_value.varname,calllingMethod) ){
                fprintf(fd, "%s->extended_%s", genericValue->varname->associated_value.varname,fatherName);
            }
            else if( calllingMethod != NULL &&   isMethodFromFather(currentClass,calllingMethod) ){
                fprintf(fd, "%s->extended_%s", genericValue->varname->associated_value.varname,fatherName);
            }
            else fprintf(fd, "%s", genericValue->varname->associated_value.varname);
        break;
        case GENERIC_VALUE_ARRAY_DESREFERENCING:
            ArrayDesreferencing(genericValue->arrayDesreferencing);
        break;
//        case GENERIC_VALUE_OBJECT_ARRAY_DESREFERENCING:
//            fprintf(fd, "%s->",genericValue->objectArrayDesreferencing->objectName->associated_value.varname);
//            ArrayDesreferencing(genericValue->arrayDesreferencing);
//            break;
        case GENERIC_VALUE_INTEGER_EXPRESSION:
            IntegerExpression(genericValue->integerExpression);
            break;
        case GENERIC_VALUE_STRING:
            fprintf(fd, "\"%s\"", genericValue->string->associated_value.varname);
            break;
    }
}
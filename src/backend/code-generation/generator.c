#include "../support/logger.h"
#include "generator.h"
#include "../../frontend/syntactic-analysis/bison-parser.h"
/**
 * Implementación de "generator.h".
 */

int recursiveProgram(tProgram * program);
int Class(tClass * class);
int Main(tMainFunction * mainFunction);
int Attributes(tAttributes * attributes);
int Constructor(tConstructor * attributes);
int MethodsRecursive(tMethods * attributes);
void Function(tFunction * function);
int Declaration(tDeclaration * declaration);
int DeclarationsRecursive(tDeclarations * declarations);
int IntegerArrayRecursive(tCommaIntegerArray * array);
int CharValue(tCharValue * value);
int Operator(int operator);
int Factor(tFactor * factor);
void ObjectAttribute(tObjectAttribute* objectAttribute);
void FunctionCall(tFunctionCall * objectAttribute);
void MethodCall(tMethodCall * objectAttribute);
void ArrayDesreferencing(tArrayDesreferencing * objectAttribute);
void Parameters(tParameters * parameters);
void ProgramStatements(tProgramStatements * programStatements);
int IntegerExpression(tIntegerExpression * integerExpression);
FILE * fd;

int Generator(tProgram * program, FILE * filedescriptor) {
//	LogInfo("El resultado de la expresion computada es: '%d'.", program);
    fd = filedescriptor;
    int final_result = 0;
    recursiveProgram(program);
    return final_result;
}

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

int Class(tClass * class){
    //// Creo la struct si tengo o atributos o extiendo alguna clase
    if((class->classIn->attributes != NULL && class->classIn->attributes->declarations != NULL) || class->extendsName != NULL){
        fprintf(fd, "struct %s{\n", class->varname->associated_value.varname);

        if (class->extendsName != NULL) {
            fprintf(fd, "struct %s * extended_%s;\n", class->extendsName->extendedClassName->associated_value.varname,
                    class->extendsName->extendedClassName->associated_value.varname);
        }

        if (class->classIn->attributes != NULL && class->classIn->attributes->declarations != NULL) {
            Attributes(class->classIn->attributes);
        }
        fprintf(fd, "}\n");
        Constructor(class->classIn->constructor);
    }

    if(class->classIn->methods != NULL) {
        Function(class->classIn->methods->function);
        MethodsRecursive(class->classIn->methods->methods);
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
    fprintf(fd, "int %s[", declaration->integerArrayDeclaration->varname->associated_value.varname);
    IntegerExpression(declaration->integerArrayDeclaration->integerExpression);
    fprintf(fd, "];\n");
}
if(CHAR_ARRAY_DECLARATION == declaration->type){
    fprintf(fd, "char %s[", declaration->integerArrayDeclaration->varname->associated_value.varname);
    if(declaration->integerArrayDeclaration->integerExpression != NULL)
    IntegerExpression(declaration->integerArrayDeclaration->integerExpression);
    fprintf(fd, "];\n");
}
if(INTEGER_ASSIGNATION_DECLARATION == declaration->type){
    fprintf(fd, "int %s = ", declaration->integerAssignationDeclaration->varname->associated_value.varname);
    IntegerExpression(declaration->integerAssignationDeclaration->integerExpression);
    fprintf(fd, ";\n");
}
if(CHAR_ASSIGNATION_DECLARATION_DECLARATION == declaration->type){
    fprintf(fd, "char %s = %c;\n", declaration->charAssignationDeclaration->varname->associated_value.varname, declaration->charAssignationDeclaration->character->associated_value.charValue);
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

    } else
        fprintf(fd, "\"%s\"", declaration->charArrayAssignationDeclaration->string->associated_value.varname);

    fprintf(fd, ";\n");
}
if(DECLARATION_WITH_OBJECT_TYPE == declaration->type){

}
    return result;
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
    fprintf(fd, "struct %s * constructor_%s(", constructor->function->varname->associated_value.varname, constructor->function->varname->associated_value.varname);
    Parameters(constructor->function->parameters);
    fprintf(fd, "){\n");
    ProgramStatements(constructor->function->programStatements);
    fprintf(fd, "}\n");
    return 0;
}

int MethodsRecursive(tMethods * methods){
    Function(methods->function);
    if(methods->methods != NULL)
        MethodsRecursive(methods->methods);
    return 0;
}

int Main(tMainFunction * mainFunction){
    int result = 0;
    return result;
}

void Function(tFunction * function){
    // TODO
}

int CharValue(tCharValue * value){
    // TODO
    return 0;
}

void ObjectAttribute(tObjectAttribute* objectAttribute){
    // TODO
}
void FunctionCall(tFunctionCall * objectAttribute){
    // TODO
}
void MethodCall(tMethodCall * objectAttribute){
    // TODO
}
void ArrayDesreferencing(tArrayDesreferencing * objectAttribute){
    // TODO
}

void Parameters(tParameters * parameters){
    // TODO
}

void ProgramStatements(tProgramStatements * programStatements){
    // TODO
}
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include "bison-parser.h"
#include <string.h>
#include <ctype.h>

/**
 * Implementación de "bison-grammar.h".
 */

void yyerror(const char * string) {
	LogError("Mensaje: '%s' debido a '%s' (linea %d).", string, yytext, yylineno);
	LogError("En ASCII es:");
	LogErrorRaw("\t");
	const int length = strlen(yytext);
	for (int i = 0; i < length; ++i) {
		LogErrorRaw("[%d]", yytext[i]);
	}
	LogErrorRaw("\n\n");
}

int strl(char * name){
    int x =0;
//    while(isalpha(name[x]) || isnumber(name[x])){
    while(isalpha(name[x])){
        x++;
    }

    return x;

}
tTokenNode * String(char * string){
    tTokenNode *  node = calloc(1,sizeof (tTokenNode));
    int stringLen = 1  ;
    while( string[stringLen++] != 34);
    node->associated_value.varname = calloc(1,sizeof(char)*stringLen+1);
    strncpy(node->associated_value.varname, string+1, stringLen);
    node->associated_value.varname[stringLen-2] = 0;
    return node;
}

tTokenNode * varnameNode(char * varname){
    tTokenNode * node = calloc(1,sizeof(tTokenNode));
    node->tokenId=VARNAME;
    int n = strl(varname);
    node->associated_value.varname = calloc(1,sizeof(char)*n+1);
    strncpy(node->associated_value.varname, varname, n);
    node->associated_value.varname[n] = 0;
//    printf("%s\n", node->associated_value.varname);
    return node;
}

tTokenNode * integerNode(int intValue){
    tTokenNode * node = calloc(1,sizeof(tTokenNode));
    node->tokenId=INTEGER;
    node->associated_value.integerValue = intValue;
//    printf("%d\n", intValue);
    return node;
}



tTokenNode * charNode(char character){
    tTokenNode * node = calloc(1,sizeof(tTokenNode));
    node->tokenId=CHARACTER;
    node->associated_value.charValue = character;
//    printf("%c\n", character);
    return node;
}

tTokenNode * tokenNode(int token){
    tTokenNode * node = calloc(1,sizeof(tTokenNode));
    node->tokenId=token;
    return node;
}



////program
tProgram * ProgramGrammarActionWithMain( tMainFunction * mainFunction) {
    tProgram *  newNode = malloc (sizeof (tProgram));
    newNode->mainFunction = mainFunction;
    newNode->type = PROGRAM_MAIN;
    return newNode;
}

tProgram  *  ProgramGrammarActionWithClassAndProg(tClass * class , tProgram * program ){
    tProgram* newNode  = calloc(1,sizeof (tProgram));
    newNode->classesAndMain = calloc(1,sizeof(*(newNode->classesAndMain)));
    newNode->classesAndMain->class = class;
    newNode->classesAndMain->program = program;
    newNode->type = PROGRAM_CLASS;
    return newNode;
}
////class
//
tClass  * ClassGrammarAction(int class, char * varname, int openBrace ,tClassIn * classIn , int closeBrace){
    tClass  * newNode = calloc(1,sizeof(tClass));

    newNode->class= tokenNode(class);

    newNode->varname = varnameNode(varname);

    newNode->extendsName = NULL;

    newNode->openBrace = tokenNode(openBrace);

    newNode->classIn = classIn ;

    newNode->closeBrace = tokenNode(closeBrace);

    return newNode;
}

//
tClass * ClassGrammarActionWithHerency(int class, char * className,int extends,char * fatherName , int openBrace ,tClassIn * classIn , int closeBrace){
    tClass  * newNode = calloc(1,sizeof(tClass));

    newNode->class= tokenNode(class);

    newNode->varname = varnameNode(className);
    /** newNode->varname->associated_value.varname */

    //// extends name
    newNode->extendsName  = calloc(1,sizeof(tExtendsName));
    newNode->extendsName->extendedClassName = varnameNode(fatherName);
    newNode->extendsName->extends = tokenNode(extends);


    newNode->openBrace = tokenNode(openBrace);
    newNode->classIn = classIn ;
    newNode->closeBrace = tokenNode(closeBrace);
    return newNode;
}

////class_in
tClassIn  * classInGrammarAction(tAttributes * attributes , tConstructor * constructor , tMethods * methods){
    tClassIn  * newNode = calloc(1,sizeof(tClassIn));
    newNode->attributes = attributes;
    newNode->constructor = constructor;
    newNode->methods= methods;
    return  newNode;
}

////instantiation
//
tInstantiation * instantiationGrammarAction(int  new , tFunctionCall * functionCall , int semicolon ){
    tInstantiation  * newNode = calloc(1,sizeof(tInstantiation));
    newNode->new = tokenNode(new);
    newNode->functionCall = functionCall;
    newNode->semicolon  = tokenNode(semicolon);
    return newNode;

}

////declaration
tDeclaration  * charDeclarationGrammarAction(tCharDeclaration * charDeclaration ){
    tDeclaration  * newNode = calloc(1,sizeof(tDeclaration));
    newNode->charDeclaration = charDeclaration;
    newNode->type = CHAR_DECLARATION;
    return newNode;
}

tDeclaration * integerDeclarationGrammarAction( struct tIntDeclaration * tIntegerDeclaration ){
    tDeclaration  * newNode = calloc(1,sizeof(tDeclaration));
    newNode->integerDeclaration = tIntegerDeclaration;
    newNode->type = INTEGER_DECLARATION;
    return newNode;
}

tDeclaration * charArrayDeclarationGrammarAction( struct tCharArrayDeclaration * tCharArrayDeclaration){
    tDeclaration  * newNode = calloc(1,sizeof(tDeclaration));
    newNode->charArrayDeclaration = tCharArrayDeclaration;
    newNode->type = CHAR_ARRAY_DECLARATION;
    return newNode;
}

tDeclaration * integerArrayDeclarationGrammarAction( struct tIntegerArrayDeclaration * tIntegerArrayDeclaration){
    tDeclaration  * newNode = calloc(1,sizeof(tDeclaration));
    newNode->integerArrayDeclaration = tIntegerArrayDeclaration;
    newNode->type = INTEGER_ARRAY_DECLARATION;
    return newNode;
}

tDeclaration * integerAssignationDeclarationGrammarAction( struct tIntegerAssignationDeclaration * tIntegerAssignationDeclaration){
    tDeclaration  * newNode = calloc(1,sizeof(tDeclaration));
    newNode->integerAssignationDeclaration = tIntegerAssignationDeclaration;
    newNode->type = INTEGER_ASSIGNATION_DECLARATION;
    return newNode;
}

tDeclaration * charAssignationDeclarationGrammarAction( struct tCharAssignationDeclaration * tCharAssignationDeclaration){
    tDeclaration  * newNode = calloc(1,sizeof(tDeclaration));
    newNode->charAssignationDeclaration= tCharAssignationDeclaration;
    newNode->type = CHAR_ASSIGNATION_DECLARATION_DECLARATION;
    return newNode;
}

tDeclaration * integerArrayAssignationDeclaration( tIntegerArrayAssignationDeclaration * IntegerArrayAssignationDeclaration){
    tDeclaration  * newNode = calloc(1,sizeof(tDeclaration));
    newNode->integerArrayAssignationDeclaration= IntegerArrayAssignationDeclaration;
    newNode->type = INTEGER_ARRAY_ASSIGNATION_DECLARATION;
    return newNode;
}

tDeclaration * charArrayAssignationDeclarationGrammarAction(  tCharArrayAssignationDeclaration * CharArrayAssignationDeclaration){
    tDeclaration  * newNode = calloc(1,sizeof(tDeclaration));
    newNode->charArrayAssignationDeclaration = CharArrayAssignationDeclaration;
    newNode->type = CHAR_ARRAY_ASSIGNATION_DECLARATION;
    return newNode;
}

tDeclaration * declarationWithObjectDataTypeGrammarActionBasic(char* name, char* datatype, int semicolon){
    tDeclaration  * newNode = calloc(1,sizeof(tDeclaration));
    newNode->declarationAux = calloc(1,sizeof(*(newNode->declarationAux)));
    newNode->declarationAux->name = varnameNode(name);
    newNode->declarationAux->objectDataType = varnameNode(datatype);
    newNode->declarationAux->semicolon = tokenNode(semicolon);
    newNode->declarationAux->type= ONLY_DECLARATION;
    newNode->type = DECLARATION_WITH_OBJECT_TYPE;
    return newNode;
}
tDeclaration * declarationWithObjectDataTypeGrammarActionMethodFunction(char * name, char * datatype, int assignation, void * call, int semicolon){
    tDeclaration  * newNode = calloc(1,sizeof(tDeclaration));
    newNode->declarationAux = calloc(1,sizeof(*(newNode->declarationAux)));
    newNode->declarationAux->name = varnameNode(name);
    newNode->declarationAux->objectDataType = varnameNode(datatype);
    newNode->declarationAux->assignationWithMethodFunctionInstantiation = calloc(1,sizeof(*(newNode->declarationAux->assignationWithMethodFunctionInstantiation)));
    newNode->declarationAux->assignationWithMethodFunctionInstantiation->assignation = tokenNode(assignation);
    newNode->declarationAux->assignationWithMethodFunctionInstantiation->auxStructForMethodCallFunctionCall = calloc(1,
            sizeof(*(newNode->declarationAux->assignationWithMethodFunctionInstantiation->auxStructForMethodCallFunctionCall)));
    newNode->declarationAux->assignationWithMethodFunctionInstantiation->auxStructForMethodCallFunctionCall->functionCall = call;
    newNode->declarationAux->assignationWithMethodFunctionInstantiation->auxStructForMethodCallFunctionCall->semicolon = tokenNode(semicolon);
    newNode->type = DECLARATION_WITH_OBJECT_TYPE;
    return newNode;
}
//
tDeclaration * declarationWithObjectDataTypeGrammarActionInstantiation(char* name, char* datatype, int assignation, tInstantiation* instantiation){
    tDeclaration  * newNode = calloc(1,sizeof(tDeclaration));
    newNode->declarationAux = calloc(1,sizeof(*(newNode->declarationAux)));
    newNode->declarationAux->type = INSTANTIATION;
    newNode->declarationAux->name = varnameNode(name);
    newNode->declarationAux->objectDataType = varnameNode(datatype);
    newNode->declarationAux->assignationWithMethodFunctionInstantiation = calloc(1,sizeof(*(newNode->declarationAux->assignationWithMethodFunctionInstantiation)));
    newNode->declarationAux->assignationWithMethodFunctionInstantiation->instantiation = instantiation;
    newNode->declarationAux->assignationWithMethodFunctionInstantiation->assignation = tokenNode(assignation);
    newNode->type = DECLARATION_WITH_OBJECT_TYPE;
    return newNode;
}
tDeclaration * declarationWithObjectDataTypeGrammarActionArrayNoSize(char * name, char * datatype, int openSQ, int closeSQ, int semicolon){
    tDeclaration  * newNode = calloc(1,sizeof(tDeclaration));
    newNode->declarationAux = calloc(1,sizeof(*(newNode->declarationAux)));
    newNode->declarationAux->type = ARRAY_ONLY_DECLARATION;
    newNode->declarationAux->name = varnameNode(name);
    newNode->declarationAux->objectDataType = varnameNode(datatype);
    newNode->declarationAux->emptySquareBrackets = calloc(1,sizeof(*(newNode->declarationAux->emptySquareBrackets)));
    newNode->declarationAux->emptySquareBrackets->closeSquareBracket = tokenNode(closeSQ);
    newNode->declarationAux->emptySquareBrackets->openSquareBracket = tokenNode(openSQ);
    newNode->declarationAux->emptySquareBrackets->semicolon = tokenNode(semicolon);
    newNode->type = DECLARATION_WITH_OBJECT_TYPE;
    return newNode;
}




//
tDeclaration * declarationWithObjectDataTypeGrammarActionArrayWithSize(char* name, char* datatype, int openSQ, tIntegerExpression* integerExpression, int closeSQ, int semicolon){
    tDeclaration  * newNode = calloc(1,sizeof(tDeclaration));
    newNode->declarationAux = calloc(1,sizeof(*(newNode->declarationAux)));
    newNode->declarationAux->type = ARRAY_WITH_INDEX_DECLARATION;
    newNode->declarationAux->name = varnameNode(name);
    newNode->declarationAux->objectDataType = varnameNode(datatype);
    newNode->declarationAux->squareBracketsWithSize = calloc(1,sizeof(*(newNode->declarationAux->squareBracketsWithSize)));
    newNode->declarationAux->squareBracketsWithSize->size=integerExpression;
    newNode->declarationAux->squareBracketsWithSize->closeSquareBracket = tokenNode(closeSQ);
    newNode->declarationAux->squareBracketsWithSize->openSquareBracket = tokenNode(openSQ);
    newNode->declarationAux->squareBracketsWithSize->semicolon = tokenNode(semicolon);
    newNode->type = DECLARATION_WITH_OBJECT_TYPE;
    return newNode;
}

////integer_assignation_declaration
tIntegerAssignationDeclaration * integerAssignationDeclarationRuleGrammarAction(int intReserved , char * varname , int assignation , tIntegerExpression * integerExpression , int semicolon){
    tIntegerAssignationDeclaration * newNode = calloc(1,sizeof(tIntegerAssignationDeclaration));
    newNode -> integer = tokenNode(intReserved);
    newNode->varname = varnameNode(varname);
    newNode->assignation = tokenNode(assignation) ;
    newNode->integerExpression = integerExpression ;
    newNode->semicolon = tokenNode(semicolon) ;
    return newNode;
}

////char_assignation_declaration
tCharAssignationDeclaration  * charAssignationDeclarationRuleGrammarAction (int character , char * varname , int assignation , tCharValue * charValue , int semicolon){
    tCharAssignationDeclaration * newNode = calloc(1,sizeof(tCharAssignationDeclaration ));
    newNode -> character= tokenNode(character);
    newNode->varname = varnameNode(varname);
    newNode->assignation = tokenNode(assignation) ;
    newNode->charValue = charValue ;
    newNode->semicolon = tokenNode(semicolon) ;
    return newNode;

}
////integer_array_assignation_declaration
tIntegerArrayAssignationDeclaration * integerArrayAssignationDeclarationGrammarAction(int intReserved , char * varname ,int openSquareBracket,int closeSquareBracket, int assignation, int openBrace , tIntegerArray * integerArray , int closeBrace ,int semicolon ){
    tIntegerArrayAssignationDeclaration * newNode = calloc(1,sizeof(tIntegerArrayAssignationDeclaration));
    newNode-> integer= tokenNode(intReserved);
    newNode->varname = varnameNode(varname) ;
    newNode -> openSquareBracket = tokenNode(openSquareBracket);
    newNode -> closeSquareBracket = tokenNode(closeSquareBracket)  ;
    newNode -> assignation = tokenNode(assignation);
    newNode -> openBrace = tokenNode(openBrace);
    newNode->integerArray = integerArray ;
    newNode -> closeBrace = tokenNode(closeBrace );
    newNode -> semicolon = tokenNode(semicolon);
    return newNode;
}
////char_array_assignation_declaration
//
tCharArrayAssignationDeclaration * charArrayAssignationDeclarationRuleGrammarAction(int charReserved , char * varname , int openSquareBracket,int closeSquareBracket,int assignation , int openBrace , tCharacterArray * characterArray , int closeBrace , int semicolon ){
    tCharArrayAssignationDeclaration * newNode  = calloc(1,sizeof(tCharArrayAssignationDeclaration));
    newNode->charType = tokenNode(charReserved) ;
    newNode->name = varnameNode(varname) ;
    tEmptySquareBrackets  * emptySquareBrackets = calloc(1,sizeof(tEmptySquareBrackets));
    emptySquareBrackets -> openSquareBracket = tokenNode(openSquareBracket) ;
    emptySquareBrackets->closeSquareBracket = tokenNode(closeSquareBracket);
    newNode->emptySquareBrackets = emptySquareBrackets;
    newNode->assignation = tokenNode(assignation);
    tCharArrayWithBrackets  * arrayWithBrackets = calloc(1,sizeof (tCharArrayWithBrackets));
    arrayWithBrackets->openBrace = tokenNode(openBrace);
    arrayWithBrackets->characterArray = characterArray;
    arrayWithBrackets->closeBrace = tokenNode(closeBrace);
    newNode->type = CHAR_ARRAY_WITH_BRACKETS;
    newNode->charArrayWithBrackets = arrayWithBrackets;
    newNode->semicolon = tokenNode(semicolon);
    return newNode;
}

tCharArrayAssignationDeclaration  * charArrayAssignationDeclarationRule2GrammarAction(int charReserved , char * varname , int openSquareBracket,int closeSquareBracket,int assignation , char* string, int semicolon){
    tCharArrayAssignationDeclaration * newNode = calloc(1,sizeof (tCharArrayAssignationDeclaration));
    newNode->charType = tokenNode(charReserved);
    newNode->name= varnameNode(varname);
    tEmptySquareBrackets  * emptySquareBrackets = calloc(1,sizeof(tEmptySquareBrackets));
    emptySquareBrackets -> openSquareBracket = tokenNode(openSquareBracket) ;
    emptySquareBrackets->closeSquareBracket = tokenNode(closeSquareBracket);
    newNode->emptySquareBrackets = emptySquareBrackets;
    newNode->assignation = tokenNode(assignation);
    newNode->type = CHAR_ARRAY_STRING;
    newNode->string = String(string);
    newNode -> semicolon = tokenNode(semicolon);
    return newNode;
}

////integer_array
tIntegerArray  * tIntegerArrayGrammarAction(tIntegerExpression * integerExpression ){
    tIntegerArray * newNode = calloc(1,sizeof(tIntegerArray));
    newNode->integerExpression = integerExpression ;
    return newNode;
}

//
tIntegerArray  * tIntegerArrayWithCommaGrammarAction(tIntegerExpression * integerExpression ,int comma , tIntegerArray * integerArray){
    tIntegerArray * newNode = calloc(1,sizeof(tIntegerArray));
    newNode->integerExpression = integerExpression ;
    tCommaIntegerArray * commaIntegerArray = calloc(1,sizeof(tCommaIntegerArray));
    commaIntegerArray->comma = tokenNode(comma);
    commaIntegerArray->next = integerArray ;
    newNode->commaIntegerArray = commaIntegerArray;
    return newNode;
}
////character_array
tCharacterArray  * characterArrayGrammarAction(tCharValue * charValue ){
    tCharacterArray  * newNode = calloc(1,sizeof (tCharacterArray));
    newNode->charValue = charValue ;
    return newNode;
}

tCharacterArray  * characterArrayRule2GrammarAction(tCharValue * charValue ,int comma , tCharacterArray * characterArray ){
    tCharacterArray  * newNode = calloc(1,sizeof (tCharacterArray));
    newNode->charValue = charValue ;
    tCommaCharacterArray  * commaCharacterArray = calloc(1,sizeof(tCommaCharacterArray));
    commaCharacterArray->comma = tokenNode(comma) ;
    commaCharacterArray->next = characterArray ;
    newNode->commaCharacterArray = commaCharacterArray;
    return newNode;
}


////integer_declaration
tIntDeclaration * integerDeclarationRuleGrammarAction(int intReserved , char * varname , int semicolon ){
    tIntDeclaration * newNode = calloc(1,sizeof(tIntDeclaration));
    newNode->integer = tokenNode(intReserved) ;
    newNode -> varname = varnameNode(varname);
    newNode->semicolon = tokenNode(semicolon) ;
    return newNode ;
}

////char_declaration
tCharDeclaration * charDeclarationRuleGrammarAction(int charReserved , char * varname , int semicolon ){
    tCharDeclaration * newNode = calloc(1,sizeof(tCharDeclaration));
    newNode->character = tokenNode(charReserved) ;
    newNode -> varname = varnameNode(varname);
    newNode->semicolon = tokenNode(semicolon) ;
    return newNode ;
}

////integer_array_declaration
tIntegerArrayDeclaration * integerArrayDeclarationRuleGrammarAction(int intReserved, char * varname, int openSquareBracket , tIntegerExpression  * integerExpression,int closeSquareBracket,  int semicolon){
    tIntegerArrayDeclaration * newNode  = calloc(1,sizeof(tIntegerArrayDeclaration));
    newNode->integer = tokenNode(intReserved);
    newNode->varname = varnameNode(varname);
    newNode->openSquareBracket = tokenNode(openSquareBracket) ;
    newNode ->integerExpression = integerExpression ;
    newNode -> closeSquareBracket = tokenNode(closeSquareBracket);
    newNode->semicolon =tokenNode(semicolon) ;
    return newNode;
}

////char_array_declaration
tCharArrayDeclaration * charArrayDeclarationRuleGrammarAction(int charReserved , char * varname , int openSquareBracket, tIntegerExpression  * integerExpression , int closeSquareBracket, int semicolon){
    tCharArrayDeclaration * newNode = calloc(1,sizeof(tCharArrayDeclaration));
    newNode->character = tokenNode(charReserved);
    newNode->varname = varnameNode(varname);
    newNode->openSquareBracket = tokenNode(openSquareBracket);
    newNode->integerExpression = integerExpression ;
    newNode->closeSquareBracket = tokenNode(closeSquareBracket);
    newNode->semicolon = tokenNode(semicolon);
    return newNode;
}

tCharArrayDeclaration * charArrayDeclarationRule2GrammarAction(int charReserved , char * varname , int openSquareBracket, int closeSquareBracket, int semicolon){
    tCharArrayDeclaration * newNode = calloc(1,sizeof(tCharArrayDeclaration));
    newNode->character = charNode(charReserved);
    newNode->varname = varnameNode(varname);
    newNode->openSquareBracket = tokenNode(openSquareBracket);
    newNode->closeSquareBracket = tokenNode(closeSquareBracket);
    newNode->semicolon = tokenNode(semicolon);
    return newNode;
}
////assignation
tAssignation  * assignationGrammarAction(char * varname, int assignation , tGenericValue * value , int semicolon){
    tAssignation  * newNode = calloc(1,sizeof(tAssignation));
    tSuperSubnode  * subnode = calloc(1,sizeof(tSuperSubnode));
    subnode->typeVariable = SUPER_SUB_NODE_VARNAME;
    subnode->varname = varnameNode(varname);

    tSimpleAssignationSubnode * simpleAssignationSubnode = calloc(1,sizeof(tSimpleAssignationSubnode));
    simpleAssignationSubnode->assignation = tokenNode(assignation);

    tArrayValueSemicolon  * arrayValueSemicolon = calloc(1,sizeof(tArrayValueSemicolon));
    arrayValueSemicolon->value = value;
    arrayValueSemicolon ->semicolon = tokenNode(semicolon) ;

    simpleAssignationSubnode->arrayValueSemicolon = arrayValueSemicolon ;
    simpleAssignationSubnode->type = SIMPLE_ASSIG_SUB_NODE_ARRAY_VALUE_SEMICOLON;

    subnode->typeAssignation = SUPER_SUB_NODE_SIMPLE_ASSIG_SUB_NODE;
    subnode->simpleAssignationSubnode= simpleAssignationSubnode;

    newNode->type = ASSIGNATION_SUBNODE;
    newNode->assignationSubnode = subnode;

    return newNode;
}


tAssignation  * assignationRule2GrammarAction(char * varname, int assignation , tInstantiation * instantiation){
    tAssignation  * newNode = calloc(1,sizeof(tAssignation));
    tSuperSubnode  * subnode = calloc(1,sizeof(tSuperSubnode));
    subnode->varname = varnameNode(varname);
    subnode->typeVariable = SUPER_SUB_NODE_VARNAME;

    tSimpleAssignationSubnode * simpleAssignationSubnode = calloc(1,sizeof(tSimpleAssignationSubnode));
    simpleAssignationSubnode->assignation = tokenNode(assignation);
    simpleAssignationSubnode->instantiation = instantiation;
    simpleAssignationSubnode->type = SIMPLE_ASSIG_SUB_NODE_INSTANTIATION;
    subnode->typeAssignation = SUPER_SUB_NODE_SIMPLE_ASSIG_SUB_NODE;
    subnode->simpleAssignationSubnode= simpleAssignationSubnode;
    newNode->assignationSubnode = subnode;
    newNode->type = ASSIGNATION_SUBNODE;
    return newNode;
}

tAssignation  * assignationRule3GrammarAction(char * varname,int openSquareBracket, int closeSquareBracket, int assignation, int openBrace , tGenericValueArray * genericValueArray  ,  int closeBrace , int semicolon ){
        tAssignation  * newNode = calloc(1,sizeof(tAssignation));

    tGenericArrayWithBracket * genericArrayWithBracket  = calloc(1,sizeof(tGenericArrayWithBracket));
    genericArrayWithBracket->openBracket = tokenNode(openBrace)  ;
    genericArrayWithBracket->genericValueArray = genericValueArray ;
    genericArrayWithBracket->closeBracket = tokenNode(closeBrace);

    tArrayAssignationSubnode * arrayAssignationSubNode = calloc(1,sizeof(tArrayAssignationSubnode));

    arrayAssignationSubNode->assignation = tokenNode(assignation)  ;
    arrayAssignationSubNode->genericArrayWithBrackets = genericArrayWithBracket;
    arrayAssignationSubNode->semicolon = tokenNode(semicolon);

    tEmptySquareBrackets * emptySquareBrackets = calloc(1,sizeof(tEmptySquareBrackets));
    emptySquareBrackets->openSquareBracket = tokenNode(openBrace);
    emptySquareBrackets->closeSquareBracket = tokenNode(closeBrace);

    arrayAssignationSubNode->emptySquareBrackets = emptySquareBrackets;

    tSuperSubnode  * subnode = calloc(1,sizeof(tSuperSubnode));
    subnode->varname = varnameNode(varname);
    subnode->arrayAssignationSubnode=arrayAssignationSubNode;

    newNode->assignationSubnode = subnode;

    newNode->type = ASSIGNATION_SUBNODE;
    subnode->typeVariable = SUPER_SUB_NODE_VARNAME;
    subnode->typeAssignation = SUPER_SUB_NODE_ARRAY_ASSIG_SUB_NODE;
    arrayAssignationSubNode->type = ARRAY_ASSIG_SUB_NODE_GENERIC_ARRAY_WITH_BRACKETS;
    return newNode;
}

tAssignation  * assignationRule4GrammarAction(char * varname , int openSquareBracket, int closeSquareBracket, int assignation , char* string , int semicolon){
    tAssignation  * newNode = calloc(1,sizeof(tAssignation));

    tSuperSubnode  * superSubnode = calloc(1,sizeof(tSuperSubnode));
    superSubnode->varname = varnameNode(varname);
    superSubnode->typeVariable = SUPER_SUB_NODE_VARNAME;
    newNode->type = ASSIGNATION_SUBNODE;
    tEmptySquareBrackets * emptySquareBrackets = calloc(1,sizeof(tEmptySquareBrackets));
    emptySquareBrackets->openSquareBracket = tokenNode(openSquareBracket);
    emptySquareBrackets->closeSquareBracket = tokenNode(closeSquareBracket);

    tArrayAssignationSubnode * arrayAssignationSubnode = calloc(1,sizeof(tArrayAssignationSubnode));
    arrayAssignationSubnode->assignation= tokenNode(assignation);
    arrayAssignationSubnode->emptySquareBrackets = emptySquareBrackets ;
    arrayAssignationSubnode->string = String(string) ;
    arrayAssignationSubnode->semicolon = tokenNode(semicolon);
    arrayAssignationSubnode->type = ARRAY_ASSIG_SUB_NODE_STRING;

    superSubnode->arrayAssignationSubnode = arrayAssignationSubnode;
    superSubnode->typeAssignation = SUPER_SUB_NODE_ARRAY_ASSIG_SUB_NODE;

    newNode->assignationSubnode = superSubnode;

    return newNode;
}



tAssignation  * assignationRule5GrammarAction(tArrayAssignation* arrayAssignation){
    tAssignation * newNode= calloc(1,sizeof(tAssignation));
    newNode->arrayAssignation=arrayAssignation;
    newNode->type = ASSIGNATION_ARRAY_ASSIG;
    return newNode;
}

tAssignation  * assignationRule6GrammarAction(tObjectAttribute* objectAttribute, int assignation,
                                              tGenericValue * value, int semicolon){
    tAssignation * newNode= calloc(1,sizeof(tAssignation));
    newNode->assignationSubnode= calloc(1,sizeof(tSuperSubnode));
    newNode->assignationSubnode->objectAttribute=objectAttribute;
    newNode->assignationSubnode->simpleAssignationSubnode= calloc(1,sizeof(tSimpleAssignationSubnode));
    newNode->type = ASSIGNATION_SUBNODE;
    newNode->assignationSubnode->simpleAssignationSubnode->assignation=tokenNode(assignation);
    newNode->assignationSubnode->simpleAssignationSubnode->arrayValueSemicolon=calloc(1,sizeof(tArrayValueSemicolon));
    newNode->assignationSubnode->simpleAssignationSubnode->arrayValueSemicolon->value=value;
    newNode->assignationSubnode->simpleAssignationSubnode->arrayValueSemicolon->semicolon=tokenNode(semicolon);
    newNode->assignationSubnode->typeVariable = SUPER_SUB_NODE_OBJECT_ATT;
    newNode->assignationSubnode->typeAssignation = SUPER_SUB_NODE_SIMPLE_ASSIG_SUB_NODE;
    newNode->assignationSubnode->simpleAssignationSubnode->type = SIMPLE_ASSIG_SUB_NODE_ARRAY_VALUE_SEMICOLON;
    return newNode;

}


tAssignation  * assignationRule7GrammarAction(tObjectAttribute* objectAttribute, int assignation,
                                              tInstantiation* instantiation){
    tAssignation * newNode= calloc(1,sizeof(tAssignation));
    newNode->assignationSubnode= calloc(1,sizeof(tSuperSubnode));
    newNode->assignationSubnode->objectAttribute=objectAttribute;
    newNode->assignationSubnode->typeVariable = SUPER_SUB_NODE_OBJECT_ATT;
    newNode->assignationSubnode->simpleAssignationSubnode= calloc(1,sizeof(tSimpleAssignationSubnode));
    newNode->type = ASSIGNATION_SUBNODE;
    newNode->assignationSubnode->typeAssignation = SUPER_SUB_NODE_SIMPLE_ASSIG_SUB_NODE;
    newNode->assignationSubnode->simpleAssignationSubnode->type = SIMPLE_ASSIG_SUB_NODE_INSTANTIATION;
    newNode->assignationSubnode->simpleAssignationSubnode->assignation=tokenNode(assignation);
    newNode->assignationSubnode->simpleAssignationSubnode->instantiation=instantiation;
    return newNode;
}

tAssignation* assignationRule8GrammarAction(tObjectAttribute* objectAttribute, int openSquareBracket, int closeSquareBracket,
                                            int assignation, int openBrace, tGenericValueArray * genericValueArray ,
                                            int closeBrace, int semicolon){
    tAssignation * newNode= calloc(1,sizeof(tAssignation));
    newNode->assignationSubnode = calloc(1,sizeof(tSuperSubnode));
    newNode->assignationSubnode->objectAttribute = objectAttribute;
    newNode->assignationSubnode->arrayAssignationSubnode = calloc(1,sizeof (tArrayAssignationSubnode));
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets= calloc(1,sizeof(tEmptySquareBrackets));
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets->openSquareBracket=tokenNode(openSquareBracket);
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets->closeSquareBracket=tokenNode(closeSquareBracket);

    newNode->type = ASSIGNATION_SUBNODE;
    newNode->assignationSubnode->typeVariable = SUPER_SUB_NODE_OBJECT_ATT;
    newNode->assignationSubnode->typeAssignation = SUPER_SUB_NODE_ARRAY_ASSIG_SUB_NODE;
    newNode->assignationSubnode->arrayAssignationSubnode->assignation=tokenNode(assignation);

    newNode->assignationSubnode->arrayAssignationSubnode->genericArrayWithBrackets= calloc(1,sizeof(tGenericArrayWithBracket));
    newNode->assignationSubnode->arrayAssignationSubnode->type = ARRAY_ASSIG_SUB_NODE_GENERIC_ARRAY_WITH_BRACKETS;
    newNode->assignationSubnode->arrayAssignationSubnode->genericArrayWithBrackets->openBracket=tokenNode(openBrace);
    newNode->assignationSubnode->arrayAssignationSubnode->genericArrayWithBrackets->genericValueArray=genericValueArray;
    newNode->assignationSubnode->arrayAssignationSubnode->genericArrayWithBrackets->closeBracket=tokenNode(closeBrace);


    newNode->assignationSubnode->arrayAssignationSubnode->semicolon=tokenNode(semicolon);

    return newNode;

}

tAssignation  * assignationRule9GrammarAction(tObjectAttribute* objectAttribute, int openSquareBracket, int closeSquareBracket,  int assignation, char* string, int semicolon){
    tAssignation * newNode= calloc(1,sizeof(tAssignation));
    newNode->assignationSubnode = calloc(1,sizeof(*(newNode->arrayAssignation)));
    newNode->assignationSubnode->objectAttribute = objectAttribute;
    newNode->assignationSubnode->typeVariable = SUPER_SUB_NODE_OBJECT_ATT;
    newNode->assignationSubnode->typeAssignation = SUPER_SUB_NODE_ARRAY_ASSIG_SUB_NODE;
    newNode->type = ASSIGNATION_ARRAY_ASSIG;
    newNode->assignationSubnode->arrayAssignationSubnode = calloc(1,sizeof(*(newNode->assignationSubnode->arrayAssignationSubnode)));
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets = calloc(1,sizeof(*(newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets)));
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets->openSquareBracket = tokenNode(openSquareBracket);
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets->closeSquareBracket = tokenNode(closeSquareBracket);
    newNode->assignationSubnode->arrayAssignationSubnode->assignation = tokenNode(assignation);
    newNode->assignationSubnode->arrayAssignationSubnode->string = String(string);
    newNode->assignationSubnode->arrayAssignationSubnode->semicolon = tokenNode(semicolon);
    newNode->assignationSubnode->arrayAssignationSubnode->type = ARRAY_ASSIG_SUB_NODE_STRING;
    return newNode;
}
/**
 * @section
 * value
 */
//tGenericValue * valueSingle(void * value){
//    tGenericValue * result = calloc(1,sizeof(tGenericValue));
//    result->integerExpression = value;
//    return result;
//}
//tGenericValue * valueSingleCharacter(char  value){
//    tGenericValue * result = calloc(1,sizeof(tGenericValue));
//    result->character = charNode(value);
//    return result;
//}
//tGenericValue * valueSingleString(char * value){
//    tGenericValue * result = calloc(1,sizeof(tGenericValue));
//    result->string = varnameNode(value);
//    return result;
//}
//tGenericValue * valueObjectAttributeDesreferencing(tObjectAttribute* objectAttribute, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket){
//    tGenericValue * result = calloc(1,sizeof(tGenericValue));
//    result->objectAttributeDesreferencing = calloc(1,sizeof(*(result->objectAttributeDesreferencing)));
//    result->objectAttributeDesreferencing->objectAttribute = objectAttribute;
//    result->objectAttributeDesreferencing->openSquareBracket = tokenNode(openSquareBracket);
//    result->objectAttributeDesreferencing->index = integerExpression;
//    result->objectAttributeDesreferencing->closeSquareBracket = tokenNode(closeSquareBracket);
//    return result;
//}
//tGValue * valueObjectAttributeDesreferencingAttribute(tObjectAttribute* objectAttribute, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int point, char * varname){
//    tGValue * result = calloc(1,sizeof(tGValue));
//    result->objectAttributeDesreferencing = calloc(1,sizeof(*(result->objectAttributeDesreferencing)));
//    result->objectAttributeDesreferencing->objectAttribute = objectAttribute;
//    result->objectAttributeDesreferencing->openSquareBracket = tokenNode(openSquareBracket);
//    result->objectAttributeDesreferencing->index = integerExpression;
//    result->objectAttributeDesreferencing->closeSquareBracket = tokenNode(closeSquareBracket);
//    result->objectAttributeDesreferencing->pointInnerAtributte = calloc(1,sizeof(*(result->objectAttributeDesreferencing->pointInnerAtributte)));
//    result->objectAttributeDesreferencing->pointInnerAtributte->point = tokenNode(point);
//    result->objectAttributeDesreferencing->pointInnerAtributte->innerAttributeName = varnameNode(varname);
//    return result;
//}

/**
 * @section
 * generic_value_array
 */
tGenericValueArray * genericValueArraySingle(tGenericValue * value){
    tGenericValueArray * genericValueArray = calloc(1,sizeof(tGenericValueArray));
    genericValueArray->genericValue = value;
    return genericValueArray;
}
tGenericValueArray * genericValueArrayPlural(tGenericValue * value, int comma, tGenericValueArray * argumentValues1){
    tGenericValueArray * genericValueArray = calloc(1,sizeof(tGenericValueArray));
    genericValueArray->genericValue = value;
    genericValueArray->commaGenericValueArray = calloc(1,sizeof(*(genericValueArray->commaGenericValueArray)));
    genericValueArray->commaGenericValueArray->comma = tokenNode(comma);
    genericValueArray->commaGenericValueArray->genericValueArray = argumentValues1;
    return genericValueArray;
}

/**
 * @section
 * generic_value
 */

tGenericValue * genericValue(void * value, int type){
    tGenericValue * result = calloc(1,sizeof(tGenericValue));
    result->type = type;
    result->varname = value;
    return result;
}
tGenericValue * genericValueCharacter(char value){
    tGenericValue * result = calloc(1,sizeof(tGenericValue));
    result->type = GENERIC_VALUE_CHARACTER;
    result->varname = charNode(value);
    return result;
}
tGenericValue * genericValueInteger(int value){
    tGenericValue * result = calloc(1,sizeof(tGenericValue));
    result->type = GENERIC_VALUE_INTEGER;
    result->varname = integerNode(value);
    return result;
}
tGenericValue * genericValueVarname(char * value){
    tGenericValue * result = calloc(1,sizeof(tGenericValue));
    result->type = GENERIC_VALUE_VARNAME;
    result->varname = varnameNode(value);
    return result;
}
//tGenericValue * genericValueString(char * value){
//    tGenericValue * result = calloc(1,sizeof(tGenericValue));
//    result->type = GENERIC_VALUE_STRING;
//    result->string = varnameNode(value);
//    return result;
//}
tGenericValue * genericValueIntegerExpression(tIntegerExpression * integerExpression){
    tGenericValue * result = calloc(1,sizeof(tGenericValue));
    result->type = GENERIC_VALUE_INTEGER_EXPRESSION;
    result->integerExpression = integerExpression;
    return result;
}


tGenericValue * genericValueString(char * string){
    tGenericValue * result = calloc(1,sizeof(tGenericValue));
    tTokenNode *  node = calloc(1,sizeof (tTokenNode));
    int stringLen = 1  ;
    while( string[stringLen++] != 34);
    result->type = GENERIC_VALUE_STRING;
    node->associated_value.varname = calloc(1,sizeof(char)*stringLen+1);
    strncpy(node->associated_value.varname, string+1, stringLen);
    node->associated_value.varname[stringLen-2] = 0;
    result->string = node ;
    return result;
}



//tGenericValue  * genericValuePointArrayDesreferencing(char * varname, int point , tArrayDesreferencing * arrayDesreferencing){
//    tGenericValue  * newNode = calloc(1,sizeof(tGenericValue));
//    newNode->type = GENERIC_VALUE_OBJECT_ARRAY_DESREFERENCING;
//    newNode->objectArrayDesreferencing = calloc(1,sizeof(struct ObjectArrayDesreferencing));
//    newNode->objectArrayDesreferencing->objectName = varnameNode(varname);
//    newNode->objectArrayDesreferencing->point= tokenNode(point);
//    newNode->objectArrayDesreferencing->arrayDesreferencing = arrayDesreferencing;
//    return newNode;
//
//}


//tGenericValue* genericValuePointArrayDesreferencingPointVarname(char * varname, tTokenNode* point, tArrayDesreferencing* arrayDesreferencing,
//                                                                tTokenNode* point, tTokenNode* varname){
//    tGenericValue* newNode= calloc(1,sizeof(tGenericValue));
//    newNode->
//
//}
tFactor * genericValueObjectAttributeDesreferencing(tObjectAttribute* objectAttribute, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket){
    tFactor * result = calloc(1,sizeof(tFactor));
    result->type = GENERIC_VALUE_OBJECT_ARRAY_DESREFERENCING;
    result->objectAttributeDesreferencing = calloc(1,sizeof(tObjectAttributeDesreferencing));
    result->objectAttributeDesreferencing->index = integerExpression;
    result->objectAttributeDesreferencing->objectAttribute = objectAttribute;
    result->objectAttributeDesreferencing->openSquareBracket = tokenNode(openSquareBracket);
    result->objectAttributeDesreferencing->closeSquareBracket = tokenNode(closeSquareBracket);
    return result;
}
tFactor * genericValueObjectAttributeDesreferencingInnerAtt(tObjectAttribute* objectAttribute, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int point, char * innerAtt){
    tFactor * result = calloc(1,sizeof(tFactor));
    result->type = GENERIC_VALUE_OBJECT_ARRAY_DESREFERENCING;
    result->objectAttributeDesreferencing = calloc(1,sizeof(tObjectAttributeDesreferencing));
    result->objectAttributeDesreferencing->index = integerExpression;
    result->objectAttributeDesreferencing->objectAttribute = objectAttribute;
    result->objectAttributeDesreferencing->openSquareBracket = tokenNode(openSquareBracket);
    result->objectAttributeDesreferencing->closeSquareBracket = tokenNode(closeSquareBracket);
    tInnerAttribute * innerAttribute = result->objectAttributeDesreferencing->innerAttribute = calloc(1,sizeof(tInnerAttribute));
    innerAttribute->innerAttributeName = varnameNode(innerAtt);
    innerAttribute->point = tokenNode(point);
    return result;
}
/**
 * @section
 * char_value
 */
tCharValue * charValue(void * value , int type){
    tCharValue * result = calloc(1,sizeof(tCharValue));
    result->type = type;
    result->varname = value;
    return result;
}
tCharValue * charValueCharacter(char value){
    tCharValue * result = calloc(1,sizeof(tCharValue));
    result->type = CHARACTER_CHARVALUE;
    result->varname = charNode(value);
    return result;
}
tCharValue * charValueVarname(char * value){
    tCharValue * result = calloc(1,sizeof(tCharValue));
    result->type = VARNAME_CHARVALUE;
    result->varname = varnameNode(value);
    return result;
}
/**
 * @section
 * array_assignation
 */
tArrayAssignation * arrayAssignationValueA(char * name, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int assignation, tGenericValue* value, int semicolon){
    tArrayAssignation * arrayAssignation = calloc(1,sizeof(tArrayAssignation));
    arrayAssignation->varname = varnameNode(name);
    arrayAssignation->typeVariable = ARRAY_ASSIG_VARNAME;
    arrayAssignation->typeAssignatedValue = ARRAY_ASSIG_VALUE_SEMICOLON;
    arrayAssignation->openSquareBracket = tokenNode(openSquareBracket);
    arrayAssignation->index = integerExpression;
    arrayAssignation->closeSquareBracket = tokenNode(closeSquareBracket);
    arrayAssignation->assignation = tokenNode(assignation);
    arrayAssignation->valueSemicolon = calloc(1,sizeof(*(arrayAssignation->valueSemicolon)));
    arrayAssignation->valueSemicolon->value = value;
    arrayAssignation->valueSemicolon->semicolon = tokenNode(semicolon);
    return arrayAssignation;
}
tArrayAssignation * arrayAssignationValueB(tObjectAttribute * name, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int assignation, tGenericValue* value, int semicolon){
    tArrayAssignation * arrayAssignation = calloc(1,sizeof(tArrayAssignation));
    arrayAssignation->objectAttribute = name;
    arrayAssignation->typeVariable = ARRAY_ASSIG_OBJECT_ATT;
    arrayAssignation->typeAssignatedValue = ARRAY_ASSIG_VALUE_SEMICOLON;
    arrayAssignation->openSquareBracket = tokenNode(openSquareBracket);
    arrayAssignation->index = integerExpression;
    arrayAssignation->closeSquareBracket = tokenNode(closeSquareBracket);
    arrayAssignation->assignation = tokenNode(assignation);
    arrayAssignation->valueSemicolon = calloc(1,sizeof(*(arrayAssignation->valueSemicolon)));
    arrayAssignation->valueSemicolon->value = value;
    arrayAssignation->valueSemicolon->semicolon = tokenNode(semicolon);
    return arrayAssignation;
}
tArrayAssignation * arrayAssignationSemicolonA(char * name, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int assignation, tInstantiation* instantiation){
    tArrayAssignation * arrayAssignation = calloc(1,sizeof(tArrayAssignation));
    arrayAssignation->varname = varnameNode(name);
    arrayAssignation->typeVariable = ARRAY_ASSIG_VARNAME;
    arrayAssignation->typeAssignatedValue = ARRAY_ASSIG_INSTANTIATION;
    arrayAssignation->openSquareBracket = tokenNode(openSquareBracket);
    arrayAssignation->index = integerExpression;
    arrayAssignation->closeSquareBracket = tokenNode(closeSquareBracket);
    arrayAssignation->assignation = tokenNode(assignation);
    arrayAssignation->valueSemicolon = calloc(1,sizeof(*(arrayAssignation->valueSemicolon)));
    arrayAssignation->instantiation = instantiation;
    return arrayAssignation;
}
tArrayAssignation * arrayAssignationSemicolonB(tObjectAttribute * name, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int assignation, tInstantiation* instantiation){
    tArrayAssignation * arrayAssignation = calloc(1,sizeof(tArrayAssignation));
    arrayAssignation->objectAttribute = name;
    arrayAssignation->typeVariable = ARRAY_ASSIG_OBJECT_ATT;
    arrayAssignation->typeAssignatedValue = ARRAY_ASSIG_INSTANTIATION;
    arrayAssignation->openSquareBracket = tokenNode(openSquareBracket);
    arrayAssignation->index = integerExpression;
    arrayAssignation->closeSquareBracket = tokenNode(closeSquareBracket);
    arrayAssignation->assignation = tokenNode(assignation);
    arrayAssignation->valueSemicolon = calloc(1,sizeof(*(arrayAssignation->valueSemicolon)));
    arrayAssignation->instantiation = instantiation;
    return arrayAssignation;
}

////methods

tMethods * methods(tFunction* function, tMethods* methods){
    tMethods * newNode= calloc(1,sizeof(tMethods));
    newNode->function=function;
    newNode->methods=methods;
    return newNode;
}

////method_call

tMethodCall * methodCall(char * varname, int point,
                         tFunctionCall* functionCall){
    tMethodCall * newNode= calloc(1,sizeof(tMethodCall));
    newNode->varname=varnameNode(varname);
    newNode->point=tokenNode(point);
    newNode->functionCall=functionCall;
    return newNode;
}

////datatype
tDataType * dataType(int token){
    tDataType * newNode= calloc(1,sizeof(tDataType));
    newNode->type=tokenNode(token);
    return newNode;
}

////parameters

tParameters * basicParameters(tDataType* dataType, char * varname){
    tParameters * newNode= calloc(1,sizeof(tParameters));
    newNode->type = BASIC_PARAMETERS ;
    newNode->datatype=dataType;
    newNode->paramName=varnameNode(varname);
    newNode->nextParameters = NULL ;
    return newNode;
}
//
tParameters * multiBasicParameters(tDataType* dataType, char* paramName,
                                   int comma, tParameters* parameters){
    tParameters * newNode= basicParameters(dataType, paramName);
    newNode->type = MULTIBASIC_PARAMETERS;
    newNode->nextParameters= calloc(1,sizeof(tCommaNextParameters));
    newNode->nextParameters->comma=tokenNode(comma);
    newNode->nextParameters->nextParameters=parameters;
    return newNode;
}

tParameters * objectParameters( char * objectType, char * paramName){
    tParameters * newNode= calloc(1,sizeof(tParameters));
    newNode->type = OBJECT_PARAMETERS;
    newNode->objectTypeName=varnameNode(objectType);
    newNode->paramName=varnameNode(paramName);
    return newNode;
}

tParameters * multiObjectParameters( char* objectType, char* paramName,
                                     int comma, tParameters* parameters){
    tParameters * newNode= objectParameters(objectType, paramName);
    newNode->type = MULTIOBJECT_PARAMETERS;
    newNode->nextParameters= calloc(1,sizeof(tCommaNextParameters));
    newNode->nextParameters->comma=tokenNode(comma);
    newNode->nextParameters->nextParameters=parameters;
    return newNode;
}

tParameters * arrayParameters(tDataType* dataType, char * paramName,
                              int openSquareBracket, int closeSquareBracket){
    tParameters * newNode= basicParameters(dataType, paramName);
    newNode->type = ARRAY_PARAMETERS;
    newNode->squareBrackets= calloc(1,sizeof(tEmptySquareBrackets));
    newNode->squareBrackets->closeSquareBracket=tokenNode(closeSquareBracket);
    newNode->squareBrackets->openSquareBracket=tokenNode(openSquareBracket);
    return newNode;
}

tParameters * multiArrayParameters(tDataType* dataType, char * paramName,
                              int openSquareBracket, int closeSquareBracket,
                              int comma, tParameters* parameters){
    tParameters * newNode= arrayParameters(dataType, paramName, openSquareBracket, closeSquareBracket);
    newNode->nextParameters= calloc(1,sizeof(tCommaNextParameters));
    newNode->type = MULTIARRAY_PARAMETERS ;
    newNode->nextParameters->comma=tokenNode(comma);
    newNode->nextParameters->nextParameters=parameters;
    return newNode;
}

tParameters * objectArrayParameters(char * objectType, char * paramName,
                              int openSquareBracket, int closeSquareBracket){
    tParameters * newNode= objectParameters(objectType,paramName);
    newNode->squareBrackets= calloc(1,sizeof(tEmptySquareBrackets));
    newNode->type = OBJECTARRAY_PARAMETERS;
    newNode->squareBrackets->closeSquareBracket=tokenNode(closeSquareBracket);
    newNode->squareBrackets->openSquareBracket=tokenNode(openSquareBracket);
    return newNode;
}

tParameters * multiObjectArrayParameters(char *  objectType, char * paramName,
                                    int openSquareBracket, int closeSquareBracket,
                                    int comma, tParameters* parameters) {
    tParameters * newNode= objectArrayParameters(objectType,paramName, openSquareBracket, closeSquareBracket);
    newNode->type = MULTIOBJECTARRAY_PARAMETERS ;
    newNode->nextParameters= calloc(1,sizeof(tCommaNextParameters));
    newNode->nextParameters->comma=tokenNode(comma);
    newNode->nextParameters->nextParameters=parameters;
    return newNode;

}

/**
 * @section
 * main_function
 */
tMainFunction * mainFunctionRule(int integerType, int main, int openP, tParameters * parameters, int closeP, int openBrace, tProgramStatements* programStatements, int closeBrace){
    tMainFunction * function = calloc(1,sizeof(tFunction));
    function->integer = tokenNode(integerType);
    function->main = tokenNode(main);
    function->openParenthesis = tokenNode(openP);
    function->parameters = parameters;
    function->closeParenthesis = tokenNode(closeP);
    function->openBrace = tokenNode(openBrace);
    function->programStatements = programStatements;
    function->closeBrace = tokenNode(closeBrace);
    return function;
}


/**
 * @section
 * function
 */

tFunction * functionRule3GrammarAction(char * varname, int openP, tParameters * parameters, int closeP, int openBrace, tProgramStatements* programStatements, int closeBrace){
    tFunction * function = calloc(1,sizeof(tFunction));
    function->varname = varnameNode(varname);
    function->openP = tokenNode(openP);
    function->parameters = parameters;
    function->closeP = tokenNode(closeP);
    function->openBrace = tokenNode(openBrace);
    function->programStatements = programStatements;
    function->closeBrace = tokenNode(closeBrace);
    return function;

}

tFunction * functionRuleWithType(tDataType * type, char * varname, int openP, tParameters * parameters, int closeP, int openBrace, tProgramStatements* programStatements, int closeBrace){
    tFunction * newNode =functionRule3GrammarAction(varname,openP,parameters,closeP,openBrace,programStatements,closeBrace);
    newNode->type = DATATYPE_FUNCTION;
    newNode->datatype = type;
    return newNode;
}


tFunction * functionRuleNoType(int voidToken ,char * varname, int openP, tParameters * parameters, int closeP, int openBrace, tProgramStatements* programStatements, int closeBrace){
    tFunction * newNode = functionRule3GrammarAction( varname, openP, parameters, closeP, openBrace, programStatements, closeBrace);
    newNode->type = VOID_FUNCTION;
    newNode->voidReserved = tokenNode(voidToken);
    return newNode;
}
////constructor
tConstructor * constructor(int constructor, tFunction* function){
    tConstructor  * newNode = calloc(1,sizeof(tConstructor));
    newNode->constructor=tokenNode(constructor);
    newNode->function=function;
    return newNode;
}
////declarations
tDeclarations* declarations(tDeclaration * declaration, tDeclarations* declarations){
    tDeclarations * newNode= calloc(1,sizeof(tDeclarations));
    newNode->declarations= declarations;
    newNode->declaration= declaration;
    return newNode;
}
////attributes
tAttributes* attributes(int attributes, int openBrace,
                        tDeclarations* declarations, int closeBrace){
    tAttributes * newNode= calloc(1,sizeof(tAttributes));
    newNode->attributes=tokenNode(attributes);
    newNode->operBrace=tokenNode(openBrace);
    newNode->declarations=declarations;
    newNode->closeBrace=tokenNode(closeBrace);
    return newNode;
}

////comparison_operator
tComparisonOperator * comparisonOperator(int token){
    tComparisonOperator* newNode= calloc(1,sizeof(tComparisonOperator));
//    switch (token->tokenId) {
//        case EQUAL_OP:
//            newNode->equalOp=token;
//            break;
//        case NOT_EQUAL_OP:
//            newNode->notEqualOp=token;
//            break;
//        case LOWER_OP:
//            newNode->lowerOp=token;
//            break;
//        case LOWEREQ_OP:
//            newNode->lowerEqOp=token;
//            break;
//        case GREATER_OP:
//            newNode->greaterOp=token;
//            break;
//        case GREATEREQ_OP:
//            newNode->greaterEqOp=token;
//            break;
//
//    }
    newNode->lowerEqOp= tokenNode(token);
    return newNode;
}
//
////logical_operator
tLogicalOperator * logicalOperator(int tokenId){
    tTokenNode * newToken = tokenNode(tokenId);
    tLogicalOperator * newNode= calloc(1,sizeof(tLogicalOperator));
    newNode->andToken = newToken;
    return newNode;
}
////comparation
tComparation * comparation(tGenericValue * lValue, tComparisonOperator* comparisonOperator,
                           tGenericValue* rValue){
    tComparation * newNode= calloc(1,sizeof(tComparation));
    newNode->lValue=lValue;
    newNode->comparisonOperator=comparisonOperator;
    newNode->rValue=rValue;
    return newNode;
}
////condition_unit
tConditionUnit * simpleConditionUnit(tCondition* condition){
    tConditionUnit * newNode= calloc(1,sizeof(tConditionUnit));
    newNode->type = CUT_CONDITION;
    newNode->condition=condition;
    return newNode;
}

tConditionUnit * conditionUnitValOpVal(tGenericValue* lValue, struct tLogicalOperator* logicalOperator,
                                       tGenericValue* rValue){
    tConditionUnit * newNode= calloc(1,sizeof(tConditionUnit));
    newNode->valueComparatorValue= calloc(1,sizeof(tValueComparatorValue));
    newNode->valueComparatorValue->lValue=lValue;
    newNode->valueComparatorValue->logicalOperator=logicalOperator;
    newNode->valueComparatorValue->rValue=rValue;
    newNode->type = CUT_VALUE_COMPARATOR_VALUE;
    return newNode;
}

tConditionUnit * conditionUnitCompOpCond(tComparation* comparation,tLogicalOperator* logicalOperator,
                                         tConditionUnit* conditionUnit){
    tConditionUnit * newNode= calloc(1,sizeof(tConditionUnit));
    newNode->logicalComparationUnit= calloc(1,sizeof(tLogicalComparationUnit));
    newNode->logicalComparationUnit->comparation=comparation;
    newNode->logicalComparationUnit->logicalOperator=logicalOperator;
    newNode->logicalComparationUnit->conditionUnit=conditionUnit;
    newNode->type = CUT_LOGICAL_COMPARATION_UNIT;
    return newNode;
}

tConditionUnit * conditionUnitComparation(tComparation* comparation){
    tConditionUnit * newNode= calloc(1,sizeof(tConditionUnit));
    newNode->comparation= comparation;
    newNode->type = CUT_COMPARATION;
    return newNode;
}
////condition
tCondition * condition(int openParenthesis, tConditionUnit* conditionUnit,
                       int closeParenthesis){
    tCondition * newNode= calloc(1,sizeof(tCondition));
    newNode->openP=tokenNode(openParenthesis);
    newNode->conditionUnit=conditionUnit;
    newNode->closeP=tokenNode(closeParenthesis);
    return newNode;
}

////clause
//
tClause * clause(int openBrace, tProgramStatements* programStatements,
                 int closeBrace){
    tClause * newNode= calloc(1,sizeof(tClause));
    newNode->openBrace= tokenNode(openBrace);
    newNode->programStatements=programStatements;
    newNode->closeBrace= tokenNode(closeBrace);
    return newNode;
}
////while_loop
//
tWhileLoop * whileLoop(int whileToken, tCondition* condition,
                       tClause* clause){
    tWhileLoop * newNode= calloc(1,sizeof(tWhileLoop));
    newNode->whileReserved= tokenNode(whileToken);
    newNode->conditionClause=condition;
    newNode->clause=clause;
    return newNode;
}
////if
//
tIf* If(int ifToken, struct tCondition* condition, tClause* clause){
    tIf * newNode = calloc(1,sizeof(tIf));
    newNode->ifReserved=tokenNode(ifToken);
    newNode->condition = condition;
    newNode->clause=clause;
    return newNode;
}
//
tIf* IfElse(int ifToken, struct tCondition* condition, tClause* ifClause, int elseToken, tClause* elseClause){
    tIf* newNode= If(ifToken, condition, ifClause);
    newNode->ifElseStatement= calloc(1,sizeof(tIfElseStatement));
    newNode->ifElseStatement->elseReserved= tokenNode(elseToken);
    newNode->ifElseStatement->clause=elseClause;
    return newNode;
}

/**
 * @section
 * argument_values
 */
 //
tArgumentValues * argumentValuesSingle(tGenericValue * value){
    tArgumentValues * argumentValues = calloc(1,sizeof(tArgumentValues));
    argumentValues->value = value;
    return argumentValues;
}
//
tArgumentValues * argumentValuesPlural(tGenericValue * value, int comma, tArgumentValues * argumentValues1){
    tArgumentValues * argumentValues = calloc(1,sizeof(tArgumentValues));
    argumentValues->value = value;
    argumentValues->commaNextArgumentValue = calloc(1,sizeof(*(argumentValues->commaNextArgumentValue)));
    argumentValues->commaNextArgumentValue->comma = tokenNode(comma);
    argumentValues->commaNextArgumentValue->nextArgument = argumentValues1;
    return argumentValues;
}

/**
 * @section
 * program_unit_statements
 */
 //
tProgramUnitStatements * programUnitStatements(void * unit, int type){
    tProgramUnitStatements * programUnitStatements1 = calloc(1,sizeof(tProgramUnitStatements));
    programUnitStatements1->type = type;
    programUnitStatements1->assignation = unit;
    return programUnitStatements1;
}
//
tProgramUnitStatements * programUnitStatementsIntegerExpression(tIntegerExpression * integerExpression, int semicolon){
    tProgramUnitStatements * programUnitStatements1 = calloc(1,sizeof(tProgramUnitStatements));
    programUnitStatements1->integerExpressionSemicolon = calloc(1,sizeof(*(programUnitStatements1->integerExpressionSemicolon)));
    programUnitStatements1->integerExpressionSemicolon->integerExpression = integerExpression;
    programUnitStatements1->integerExpressionSemicolon->semicolon = tokenNode(semicolon);
    programUnitStatements1->type = PUS_INTEGER_EXPRESSION_SEMICOLON;
    return programUnitStatements1;
}

/**
 * @section
 * program_statements
 */
 //
tProgramStatements * programStatementsRule(tProgramUnitStatements * programUnitStatements, tProgramStatements * programStatements){
    tProgramStatements * newProgramStatements = calloc(1,sizeof(tProgramStatements));
    newProgramStatements->programUnitStatements = programUnitStatements;
    newProgramStatements->ProgramStatements = programStatements;
    return newProgramStatements;
}

/**
 * @section
 * array_desreferencing
 */
 //
tArrayDesreferencing * arrayDesreferencing(char * varname, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket){
    tArrayDesreferencing * arrayDesreferencing1 = calloc(1,sizeof(tArrayDesreferencing));
    arrayDesreferencing1->varname = varnameNode(varname);
    arrayDesreferencing1->openSquareBracket = tokenNode(openSquareBracket);
    arrayDesreferencing1->integerExpression = integerExpression;
    arrayDesreferencing1->closeSquareBracket = tokenNode(closeSquareBracket);
    return arrayDesreferencing1;
}

/**
 * @section
 * return
 */
 //
tReturn * returnRuleValue(int ret, void * value, int type, int semicolon){
    tReturn * aReturn = calloc(1,sizeof(tReturn));
    aReturn->type=type;
    aReturn->semicolon = tokenNode(semicolon);
    aReturn->returnToken = tokenNode(ret);
    aReturn->valueUnion.value = value;
    //TODO revisar el value void*
    return aReturn;
}
//
tReturn * returnRuleNoValue(int ret, int semicolon){
    tReturn * aReturn = calloc(1,sizeof(tReturn));
    aReturn->semicolon = tokenNode(ret);
    aReturn->returnToken = tokenNode(semicolon);
    aReturn->type=RETURN_VOID;
    return aReturn;
}


/**
 * @section
 * integer_expression
 */
 //
tIntegerExpression * integerExpressionCommon(tIntegerExpression * integerExpression1, int operator, tIntegerExpression * integerExpression2){
    tIntegerExpression * integerExpression = calloc(1,sizeof(tIntegerExpression));
    integerExpression->commonIntegerExpression = calloc(1,sizeof(*(integerExpression->commonIntegerExpression)));
    integerExpression->commonIntegerExpression->leftIntegerExpression = integerExpression1;
    integerExpression->commonIntegerExpression->operator = tokenNode(operator);
    integerExpression->commonIntegerExpression->rightIntegerExpression = integerExpression2;
    integerExpression->type = INTEGER_EXPRESSION_COMMON;
    return integerExpression;
}
//
tIntegerExpression  * integerExpressionFactor(tFactor * factor){
    tIntegerExpression * integerExpression = calloc(1,sizeof(tIntegerExpression));
    integerExpression->factor = factor;
    integerExpression->type = INTEGER_EXPRESSION_FACTOR;
    return integerExpression;
}
//
tIntegerExpression * integerExpressionIncrementDecrement(tIntegerExpression * expression, int operator){
    tIntegerExpression * integerExpression = calloc(1,sizeof(tIntegerExpression));
    integerExpression->decrementIncrementIntegerExpression = calloc(1,sizeof(*(integerExpression->decrementIncrementIntegerExpression)));
    integerExpression->decrementIncrementIntegerExpression->leftIntegerExpression = expression;
    integerExpression->decrementIncrementIntegerExpression->operator = tokenNode(operator);
    integerExpression->type = INTEGER_EXPRESSION_INCREMENT_DECREMENT;
    return integerExpression;
}
//
tIntegerExpression * integerExpressionEnclosed(int openP, tIntegerExpression * expression, int closeP){
    tIntegerExpression * integerExpression = calloc(1,sizeof(tIntegerExpression));
    integerExpression->enclosedCommonIntegerExpression = calloc(1,sizeof(*(integerExpression->enclosedCommonIntegerExpression)));
    integerExpression->enclosedCommonIntegerExpression->openParenthesis = tokenNode(openP);
    integerExpression->enclosedCommonIntegerExpression->integerExpression = expression;
    integerExpression->enclosedCommonIntegerExpression->closeParenthesis = tokenNode(closeP);
    integerExpression->type = INTEGER_EXPRESSION_ENCLOSED;
    return integerExpression;
}

/**
 * @section
 * factor
 */

 tFactor * factorObjectAttribute(tObjectAttribute * objectAttribute){
    tFactor * factor = calloc(1,sizeof(tFactor));
    factor->object_attribute = objectAttribute;
    factor->type = FACTOR_OBJECT_ATT;
    return factor;
 }
 //
tFactor * factorFunctionCall(tFunctionCall * functionCall){
    tFactor * factor = calloc(1,sizeof(tFactor));
    factor->function_call = functionCall;
     factor->type = FACTOR_FUNCTION_CALL;
    return factor;
}
//
tFactor * factorMethodCall(tMethodCall * methodCall){
    tFactor * factor = calloc(1,sizeof(tFactor));
    factor->method_call = methodCall;
    factor->type = FACTOR_METHOD_CALL;
    return factor;
}
//
tFactor * factorVarname(char * varname){
    tFactor * factor = calloc(1,sizeof(tFactor));
    factor->varname = varnameNode(varname);
    factor->type = FACTOR_VARNAME;
    return factor;
}
//
tFactor * factorArrayDesreferencing(tArrayDesreferencing * arrayDesreferencing){
    tFactor * factor = calloc(1,sizeof(tFactor));
    factor->array_desreferencing = arrayDesreferencing;
    factor->type = FACTOR_ARRAY_DESR;
    return factor;
}
//
tFactor * factorSubInteger(int sub, int integer){
    tFactor * factor = calloc(1,sizeof(tFactor));
    tSubInteger * subInteger = calloc(1,sizeof(tSubInteger));
    subInteger->integer = integerNode(integer);
    subInteger->sub = tokenNode(sub);
    factor->subInteger = subInteger;
    factor->type = FACTOR_SUB_INT;
    return factor;
}
//
tFactor * factorInteger(int integer){
    tFactor * factor = calloc(1,sizeof(tFactor));
    factor->integer = integerNode(integer);
    factor->type = FACTOR_INT;
    return factor;
}

/**
 * @section
 * object_attribute
 */
//
tObjectAttribute * objectAttributeFromVarname(char * object, int point, char * attributeName){
    tObjectAttribute * objectAttribute = calloc(1,sizeof(tObjectAttribute));
    objectAttribute->type = OBJECT_ATTRIBUTE_VARNAME;
    objectAttribute->varnameLeft = varnameNode(object);
    //// Falta tipo de varnameLeft acá?
    objectAttribute->point = tokenNode(point);
    objectAttribute->varnameRight = varnameNode(attributeName);
    return objectAttribute;
}
//
tObjectAttribute * objectAttributeFromObjectAttribute(tObjectAttribute * object, int point, char * attributeName){
    tObjectAttribute * objectAttribute = calloc(1,sizeof(tObjectAttribute));
    objectAttribute->objectAttribute = object;
    objectAttribute->type = OBJECT_ATTRIBUTE_OBJECT_ATTRIBUTE;
    objectAttribute->point = tokenNode(point);
    objectAttribute->varnameRight = varnameNode(attributeName);
    return objectAttribute;
}
//
tObjectAttribute * objectAttributeFromArrayDesreferencing(tArrayDesreferencing* object, int point, char * attributeName){
    tObjectAttribute * objectAttribute = calloc(1,sizeof(tObjectAttribute));
    objectAttribute->arrayDesreferencing = object;
    objectAttribute->type = OBJECT_ATTRIBUTE_ARRAY_DESREF;
    objectAttribute->point = tokenNode(point);
    objectAttribute->varnameRight = varnameNode(attributeName);
    return objectAttribute;
}


/**
 * @section
 * function_call
 */
//
tFunctionCall * functionCall(char * functionName, int openP, tArgumentValues* argumentValues, int closeP){
    tFunctionCall * functionCall = calloc(1,sizeof(tFunctionCall));
    functionCall->functionName = varnameNode(functionName);
    functionCall->openP = tokenNode(openP);
    functionCall->firstArgument = argumentValues;
    functionCall->closeP = tokenNode(closeP);
    return functionCall;
}


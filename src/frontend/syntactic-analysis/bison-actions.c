#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include "bison-parser.h"
#include <stdio.h>
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
    while(isalpha(name[x])){
        x++;
    }

    return x;

}

tTokenNode * varnameNode(char * varname){
    tTokenNode * node = malloc(sizeof(tTokenNode));
    node->tokenId=VARNAME;
    node->associated_value.varname = malloc(sizeof(char)*strl(varname)+1);
    strcpy(node->associated_value.varname, varname);
    node->associated_value.varname[strl(varname)] = 0;
    printf("%s\n", node->associated_value.varname);
    return node;
}

tTokenNode * integerNode(int intValue){
    tTokenNode * node = malloc(sizeof(tTokenNode));
    node->tokenId=INTEGER;
    node->associated_value.integerValue = intValue;
    printf("%d\n", intValue);
    return node;
}



tTokenNode * charNode(char character){
    tTokenNode * node = malloc(sizeof(tTokenNode));
    node->tokenId=CHARACTER;
    node->associated_value.charValue = character;
    printf("%c\n", character);
    return node;
}

tTokenNode * tokenNode(int token){
    tTokenNode * node = malloc(sizeof(tTokenNode));
    node->tokenId=token;
//    switch (token) {
//        case expression:
//
//    }
//    printf("%d\n", token);
    return node;
}



////program
tProgram * ProgramGrammarActionWithMain( tMainFunction * mainFunction) {
    tProgram *  newNode = malloc (sizeof (tProgram));
    newNode->mainFunction = mainFunction;
    return newNode;
}

tProgram  *  ProgramGrammarActionWithClassAndProg(tClass * class , tProgram * program ){
    tProgram* newNode  = malloc(sizeof (tProgram));
    newNode->classesAndMain = malloc(sizeof(*(newNode->classesAndMain)));
    newNode->classesAndMain->class = class;
    newNode->classesAndMain->program = program;
    return newNode;
}
////class
//
tClass  * ClassGrammarAction(int class, char * varname, int openBrace ,tClassIn * classIn , int closeBrace){
    tClass  * newNode = malloc(sizeof(tClass));

    newNode->class= tokenNode(class);

    newNode->varname = varnameNode(varname);

    newNode->openBrace = tokenNode(openBrace);

    newNode->classIn = classIn ;

    newNode->closeBrace = tokenNode(closeBrace);

    return newNode;
}

//
tClass * ClassGrammarActionWithHerency(int class, char * fatherName,int extends,char * className , int openBrace ,tClassIn * classIn , int closeBrace){
    tClass  * newNode = malloc(sizeof(tClass));

    newNode->class= tokenNode(class);

    newNode->varname = varnameNode(className);
    /** newNode->varname->associated_value.varname */

    //// extends name
    newNode->extendsName  = malloc(sizeof(tExtendsName));
    newNode->extendsName->extendedClassName = varnameNode(fatherName);
    newNode->extendsName->extends = tokenNode(extends);


    newNode->openBrace = tokenNode(openBrace);
    newNode->classIn = classIn ;
    newNode->closeBrace = tokenNode(closeBrace);
    return newNode;
}

////class_in
tClassIn  * classInGrammarAction(tAttributes * attributes , tConstructor * constructor , tMethods * methods){
    tClassIn  * newNode = malloc(sizeof(tClassIn));
    newNode->attributes = attributes;
    newNode->constructor = constructor;
    newNode->methods= methods;
    return  newNode;
}

////instantiation
//
tInstantiation * instantiationGrammarAction(int  new , tFunctionCall * functionCall , int semicolon ){
    tInstantiation  * newNode = malloc(sizeof(tInstantiation));
    newNode->new = tokenNode(new);
    newNode->functionCall = functionCall;
    newNode->semicolon  = tokenNode(semicolon);
    return newNode;

}

////declaration
tDeclaration  * charDeclarationGrammarAction(tCharDeclaration * charDeclaration ){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->charDeclaration = charDeclaration;
    return newNode;
}

tDeclaration * integerDeclarationGrammarAction( struct tIntDeclaration * tIntegerDeclaration ){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->integerDeclaration = tIntegerDeclaration;
    return newNode;
}

tDeclaration * charArrayDeclarationGrammarAction( struct tCharArrayDeclaration * tCharArrayDeclaration){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->charArrayDeclaration = tCharArrayDeclaration;
    return newNode;
}

tDeclaration * integerArrayDeclarationGrammarAction( struct tIntegerArrayDeclaration * tIntegerArrayDeclaration){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->integerArrayDeclaration = tIntegerArrayDeclaration;
    return newNode;
}

tDeclaration * integerAssignationDeclarationGrammarAction( struct tIntegerAssignationDeclaration * tIntegerAssignationDeclaration){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->integerAssignationDeclaration = tIntegerAssignationDeclaration;
    return newNode;
}

tDeclaration * charAssignationDeclarationGrammarAction( struct tCharAssignationDeclaration * tCharAssignationDeclaration){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->charAssignationDeclaration= tCharAssignationDeclaration;
    return newNode;
}

tDeclaration * integerArrayAssignationDeclaration( tIntegerArrayAssignationDeclaration * IntegerArrayAssignationDeclaration){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->integerArrayAssignationDeclaration= IntegerArrayAssignationDeclaration;
    return newNode;
}

tDeclaration * charArrayAssignationDeclarationGrammarAction(  tCharArrayAssignationDeclaration * CharArrayAssignationDeclaration){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->charArrayAssignationDeclaration = CharArrayAssignationDeclaration;
    return newNode;
}

//
tDeclaration * declarationWithObjectDataTypeGrammarActionBasic(char* name, char* datatype, int semicolon){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->declarationAux = malloc(sizeof(*(newNode->declarationAux)));
    newNode->declarationAux->name = varnameNode(name);
    newNode->declarationAux->objectDataType = varnameNode(datatype);
    newNode->declarationAux->semicolon = tokenNode(semicolon);
    return newNode;
}
tDeclaration * declarationWithObjectDataTypeGrammarActionMethodFunction(char * name, char * datatype, int assignation, void * call, int semicolon){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->declarationAux = malloc(sizeof(*(newNode->declarationAux)));
    newNode->declarationAux->name = varnameNode(name);
    newNode->declarationAux->objectDataType = varnameNode(datatype);
    newNode->declarationAux->assignationWithMethodFunctionInstantiation = malloc(sizeof(*(newNode->declarationAux->assignationWithMethodFunctionInstantiation)));
    newNode->declarationAux->assignationWithMethodFunctionInstantiation->assignation = tokenNode(assignation);
    newNode->declarationAux->assignationWithMethodFunctionInstantiation->auxStructForMethodCallFunctionCall = malloc(
            sizeof(*(newNode->declarationAux->assignationWithMethodFunctionInstantiation->auxStructForMethodCallFunctionCall)));
    newNode->declarationAux->assignationWithMethodFunctionInstantiation->auxStructForMethodCallFunctionCall->functionCall = call;
    newNode->declarationAux->assignationWithMethodFunctionInstantiation->auxStructForMethodCallFunctionCall->semicolon = tokenNode(semicolon);
    return newNode;
}
//
tDeclaration * declarationWithObjectDataTypeGrammarActionInstantiation(char* name, char* datatype, int assignation, tInstantiation* instantiation){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->declarationAux = malloc(sizeof(*(newNode->declarationAux)));
    newNode->declarationAux->name = varnameNode(name);
    newNode->declarationAux->objectDataType = varnameNode(datatype);
    newNode->declarationAux->assignationWithMethodFunctionInstantiation = malloc(sizeof(*(newNode->declarationAux->assignationWithMethodFunctionInstantiation)));
    newNode->declarationAux->assignationWithMethodFunctionInstantiation->instantiation = instantiation;
    newNode->declarationAux->assignationWithMethodFunctionInstantiation->assignation = tokenNode(assignation);
    return newNode;
}
tDeclaration * declarationWithObjectDataTypeGrammarActionArrayNoSize(char * name, char * datatype, int openSQ, int closeSQ, int semicolon){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->declarationAux = malloc(sizeof(*(newNode->declarationAux)));
    newNode->declarationAux->name = varnameNode(name);
    newNode->declarationAux->objectDataType = varnameNode(datatype);
    newNode->declarationAux->emptySquareBrackets = malloc(sizeof(*(newNode->declarationAux->emptySquareBrackets)));
    newNode->declarationAux->emptySquareBrackets->closeSquareBracket = tokenNode(closeSQ);
    newNode->declarationAux->emptySquareBrackets->openSquareBracket = tokenNode(openSQ);
    newNode->declarationAux->emptySquareBrackets->semicolon = tokenNode(semicolon);
    return newNode;
}

//
tDeclaration * declarationWithObjectDataTypeGrammarActionArrayWithSize(char* name, char* datatype, int openSQ, tIntegerExpression* integerExpression, int closeSQ, int semicolon){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->declarationAux = malloc(sizeof(*(newNode->declarationAux)));
    newNode->declarationAux->name = varnameNode(name);
    newNode->declarationAux->objectDataType = varnameNode(datatype);
    newNode->declarationAux->squareBracketsWithSize = malloc(sizeof(*(newNode->declarationAux->squareBracketsWithSize)));
    newNode->declarationAux->squareBracketsWithSize->size=integerExpression;
    newNode->declarationAux->squareBracketsWithSize->closeSquareBracket = tokenNode(closeSQ);
    newNode->declarationAux->squareBracketsWithSize->openSquareBracket = tokenNode(openSQ);
    newNode->declarationAux->squareBracketsWithSize->semicolon = tokenNode(semicolon);
    return newNode;
}

////integer_assignation_declaration
tIntegerAssignationDeclaration * integerAssignationDeclarationRuleGrammarAction(int intReserved , char * varname , int assignation , tIntegerExpression * integerExpression , int semicolon){
    tIntegerAssignationDeclaration * newNode = malloc(sizeof(tIntegerAssignationDeclaration));
    newNode -> integer = tokenNode(intReserved);
    newNode->varname = varnameNode(varname);
    newNode->assignation = tokenNode(assignation) ;
    newNode->integerExpression = integerExpression ;
    newNode->semicolon = tokenNode(semicolon) ;
    return newNode;
}

////char_assignation_declaration
tCharAssignationDeclaration  * charAssignationDeclarationRuleGrammarAction (int character , char * varname , int assignation , tCharValue * charValue , int semicolon){
    tCharAssignationDeclaration * newNode = malloc(sizeof(tCharAssignationDeclaration ));
    newNode -> character= tokenNode(character);
    newNode->varname = varnameNode(varname);
    newNode->assignation = tokenNode(assignation) ;
    newNode->charValue = charValue ;
    newNode->semicolon = tokenNode(semicolon) ;
    return newNode;

}
////integer_array_assignation_declaration
tIntegerArrayAssignationDeclaration * integerArrayAssignationDeclarationGrammarAction(int intReserved , char * varname ,int openSquareBracket,int closeSquareBracket, int assignation, int openBrace , tIntegerArray * integerArray , int closeBrace ,int semicolon ){
    tIntegerArrayAssignationDeclaration * newNode = malloc(sizeof(tIntegerArrayAssignationDeclaration));
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
    tCharArrayAssignationDeclaration * newNode  = malloc(sizeof(tCharArrayAssignationDeclaration));
    newNode->charType = tokenNode(charReserved) ;
    newNode->name = varnameNode(varname) ;
    tEmptySquareBrackets  * emptySquareBrackets = malloc(sizeof(tEmptySquareBrackets));
    emptySquareBrackets -> openSquareBracket = tokenNode(openSquareBracket) ;
    emptySquareBrackets->closeSquareBracket = tokenNode(closeSquareBracket);
    newNode->emptySquareBrackets = emptySquareBrackets;
    newNode->assignation = tokenNode(assignation);
    tCharArrayWithBrackets  * arrayWithBrackets = malloc(sizeof (tCharArrayWithBrackets));
    arrayWithBrackets->openBrace = tokenNode(openBrace);
    arrayWithBrackets->characterArray = characterArray;
    arrayWithBrackets->closeBrace = tokenNode(closeBrace);
    newNode->charArrayWithBrackets = arrayWithBrackets;
    newNode->semicolon = tokenNode(semicolon);
    return newNode;
}

tCharArrayAssignationDeclaration  * charArrayAssignationDeclarationRule2GrammarAction(int charReserved , char * varname , int openSquareBracket,int closeSquareBracket,int assignation , char* string, int semicolon){
    tCharArrayAssignationDeclaration * newNode = malloc(sizeof (tCharArrayAssignationDeclaration));
    newNode->charType = tokenNode(charReserved);
    newNode->name= varnameNode(varname);
    tEmptySquareBrackets  * emptySquareBrackets = malloc(sizeof(tEmptySquareBrackets));
    emptySquareBrackets -> openSquareBracket = tokenNode(openSquareBracket) ;
    emptySquareBrackets->closeSquareBracket = tokenNode(closeSquareBracket);
    newNode->emptySquareBrackets = emptySquareBrackets;
    newNode->assignation = tokenNode(assignation);
    newNode->string = varnameNode(string);
    newNode -> semicolon = tokenNode(semicolon);
    return newNode;
}

////integer_array
tIntegerArray  * tIntegerArrayGrammarAction(tIntegerExpression * integerExpression ){
    tIntegerArray * newNode = malloc(sizeof(tIntegerArray));
    newNode->integerExpression = integerExpression ;
    return newNode;
}

//
tIntegerArray  * tIntegerArrayWithCommaGrammarAction(tIntegerExpression * integerExpression ,int comma , tIntegerArray * integerArray){
    tIntegerArray * newNode = malloc(sizeof(tIntegerArray));
    newNode->integerExpression = integerExpression ;
    tCommaIntegerArray * commaIntegerArray = malloc(sizeof(tCommaIntegerArray));
    commaIntegerArray->comma = tokenNode(comma);
    commaIntegerArray->next = integerArray ;
    newNode->commaIntegerArray = commaIntegerArray;
    return newNode;
}
////character_array
tCharacterArray  * characterArrayGrammarAction(tCharValue * charValue ){
    tCharacterArray  * newNode = malloc(sizeof (tCharacterArray));
    newNode->charValue = charValue ;
    return newNode;
}

tCharacterArray  * characterArrayRule2GrammarAction(tCharValue * charValue ,int comma , tCharacterArray * characterArray ){
    tCharacterArray  * newNode = malloc(sizeof (tCharacterArray));
    newNode->charValue = charValue ;
    tCommaCharacterArray  * commaCharacterArray = malloc(sizeof(tCommaCharacterArray));
    commaCharacterArray->comma = tokenNode(comma) ;
    commaCharacterArray->next = characterArray ;
    newNode->commaCharacterArray = commaCharacterArray;
    return newNode;
}


////integer_declaration
tIntDeclaration * integerDeclarationRuleGrammarAction(int intReserved , char * varname , int semicolon ){
    tIntDeclaration * newNode = malloc(sizeof(tIntDeclaration));
    newNode->integer = tokenNode(intReserved) ;
    newNode -> varname = varnameNode(varname);
    newNode->semicolon = tokenNode(semicolon) ;
    return newNode ;
}

////char_declaration
tCharDeclaration * charDeclarationRuleGrammarAction(int charReserved , char * varname , int semicolon ){
    tCharDeclaration * newNode = malloc(sizeof(tCharDeclaration));
    newNode->character = tokenNode(charReserved) ;
    newNode -> varname = varnameNode(varname);
    newNode->semicolon = tokenNode(semicolon) ;
    return newNode ;
}

////integer_array_declaration
tIntegerArrayDeclaration * integerArrayDeclarationRuleGrammarAction(int intReserved, char * varname, int openSquareBracket , tIntegerExpression  * integerExpression,int closeSquareBracket,  int semicolon){
    tIntegerArrayDeclaration * newNode  = malloc(sizeof(tIntegerArrayDeclaration));
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
    tCharArrayDeclaration * newNode = malloc(sizeof(tCharArrayDeclaration));
    newNode->character = tokenNode(charReserved);
    newNode->varname = varnameNode(varname);
    newNode->openSquareBracket = tokenNode(openSquareBracket);
    newNode->integerExpression = integerExpression ;
    newNode->closeSquareBracket = tokenNode(closeSquareBracket);
    newNode->semicolon = tokenNode(semicolon);
    return newNode;
}

tCharArrayDeclaration * charArrayDeclarationRule2GrammarAction(int charReserved , char * varname , int openSquareBracket, int closeSquareBracket, int semicolon){
    tCharArrayDeclaration * newNode = malloc(sizeof(tCharArrayDeclaration));
    newNode->character = charNode(charReserved);
    newNode->varname = varnameNode(varname);
    newNode->openSquareBracket = tokenNode(openSquareBracket);
    newNode->closeSquareBracket = tokenNode(closeSquareBracket);
    newNode->semicolon = tokenNode(semicolon);
    return newNode;
}
////assignation
tAssignation  * assignationGrammarAction(char * varname, int assignation , tValue * value , int semicolon){
    tAssignation  * newNode = malloc(sizeof(tAssignation));
    tSuperSubnode  * subnode = malloc(sizeof(tSuperSubnode));
    subnode->varname = varnameNode(varname);

    tSimpleAssignationSubnode * simpleAssignationSubnode = malloc(sizeof(tSimpleAssignationSubnode));
    simpleAssignationSubnode->assignation = tokenNode(assignation);

    tArrayValueSemicolon  * arrayValueSemicolon = malloc(sizeof(tArrayValueSemicolon));
    arrayValueSemicolon->value = value;
    arrayValueSemicolon ->semicolon = tokenNode(semicolon) ;
    simpleAssignationSubnode->arrayValueSemicolon = arrayValueSemicolon ;

    subnode->simpleAssignationSubnode= simpleAssignationSubnode;
    newNode->assignationSubnode = subnode;

    return newNode;
}


tAssignation  * assignationRule2GrammarAction(char * varname, int assignation , tInstantiation * instantiation){
    tAssignation  * newNode = malloc(sizeof(tAssignation));
    tSuperSubnode  * subnode = malloc(sizeof(tSuperSubnode));
    subnode->varname = varnameNode(varname);

    tSimpleAssignationSubnode * simpleAssignationSubnode = malloc(sizeof(tSimpleAssignationSubnode));
    simpleAssignationSubnode->assignation = tokenNode(assignation);
    simpleAssignationSubnode->instantation = instantiation;

    subnode->simpleAssignationSubnode= simpleAssignationSubnode;
    newNode->assignationSubnode = subnode;

    return newNode;
}

tAssignation  * assignationRule3GrammarAction(char * varname,int openSquareBracket, int closeSquareBracket, int assignation, int openBrace , tGenericValueArray * genericValueArray  ,  int closeBrace , int semicolon ){
        tAssignation  * newNode = malloc(sizeof(tAssignation));

    tGenericArrayWithBracket * genericArrayWithBracket  = malloc(sizeof(tGenericArrayWithBracket));
    genericArrayWithBracket->openBracket = tokenNode(openBrace)  ;
    genericArrayWithBracket->genericValueArray = genericValueArray ;
    genericArrayWithBracket->closeBracket = tokenNode(closeBrace);

    tArrayAssignationSubnode * arrayAssignationSubNode = malloc(sizeof(tArrayAssignationSubnode));

    arrayAssignationSubNode->assignation = tokenNode(assignation)  ;
    arrayAssignationSubNode->genericArrayWithBrackets = genericArrayWithBracket;
    arrayAssignationSubNode->semicolon = tokenNode(semicolon);

    tEmptySquareBrackets * emptySquareBrackets = malloc(sizeof(tEmptySquareBrackets));
    emptySquareBrackets->openSquareBracket = tokenNode(openBrace);
    emptySquareBrackets->closeSquareBracket = tokenNode(closeBrace);

    arrayAssignationSubNode->emptySquareBrackets = emptySquareBrackets;

    tSuperSubnode  * subnode = malloc(sizeof(tSuperSubnode));
    subnode->varname = varnameNode(varname);
    subnode->arrayAssignationSubnode=arrayAssignationSubNode;

    return newNode;
}

tAssignation  * assignationRule4GrammarAction(char * varname , int openSquareBracket, int closeSquareBracket, int assignation , char* string , int semicolon){
    tAssignation  * newNode = malloc(sizeof(tAssignation));

    tSuperSubnode  * superSubnode = malloc(sizeof(tSuperSubnode));
    superSubnode->varname = varnameNode(varname);

    tEmptySquareBrackets * emptySquareBrackets = malloc(sizeof(tEmptySquareBrackets));
    emptySquareBrackets->openSquareBracket = tokenNode(openSquareBracket);
    emptySquareBrackets->closeSquareBracket = tokenNode(closeSquareBracket);

    tArrayAssignationSubnode * arrayAssignationSubnode = malloc(sizeof(tArrayAssignationSubnode));
    arrayAssignationSubnode->assignation= tokenNode(assignation);
    arrayAssignationSubnode->emptySquareBrackets = emptySquareBrackets ;
    arrayAssignationSubnode->string = varnameNode(string) ;
    arrayAssignationSubnode->semicolon = tokenNode(semicolon);

    superSubnode->arrayAssignationSubnode = arrayAssignationSubnode;

    newNode->assignationSubnode = superSubnode;

    return newNode;
}



tAssignation  * assignationRule5GrammarAction(tArrayAssignation* arrayAssignation){
    tAssignation * newNode= malloc(sizeof(tAssignation));
    newNode->arrayAssignation=arrayAssignation;

    return newNode;
}

tAssignation  * assignationRule6GrammarAction(tObjectAttribute* objectAttribute, int assignation,
                                              tValue* value, int semicolon){
    tAssignation * newNode= malloc(sizeof(tAssignation));
    newNode->assignationSubnode= malloc(sizeof(tSuperSubnode));
    newNode->assignationSubnode->objectAttribute=objectAttribute;
    newNode->assignationSubnode->simpleAssignationSubnode= malloc(sizeof(tSimpleAssignationSubnode));

    newNode->assignationSubnode->simpleAssignationSubnode->assignation=tokenNode(assignation);
    newNode->assignationSubnode->simpleAssignationSubnode->arrayValueSemicolon=malloc(sizeof(tArrayValueSemicolon));
    newNode->assignationSubnode->simpleAssignationSubnode->arrayValueSemicolon->value=value;
    newNode->assignationSubnode->simpleAssignationSubnode->arrayValueSemicolon->semicolon=tokenNode(semicolon);

    return newNode;

}


tAssignation  * assignationRule7GrammarAction(tObjectAttribute* objectAttribute, int assignation,
                                              tInstantiation* instantiation){
    tAssignation * newNode= malloc(sizeof(tAssignation));
    newNode->assignationSubnode= malloc(sizeof(tSuperSubnode));
    newNode->assignationSubnode->objectAttribute=objectAttribute;
    newNode->assignationSubnode->simpleAssignationSubnode= malloc(sizeof(tSimpleAssignationSubnode));

    newNode->assignationSubnode->simpleAssignationSubnode->assignation=tokenNode(assignation);
    newNode->assignationSubnode->simpleAssignationSubnode->instantation=instantiation;
    return newNode;
}

tAssignation* assignationRule8GrammarAction(tObjectAttribute* objectAttribute, int openSquareBracket, int closeSquareBracket,
                                            int assignation, int openBrace, tGenericValueArray * genericValueArray ,
                                            int closeBrace, int semicolon){
    tAssignation * newNode= malloc(sizeof(tAssignation));
    newNode->assignationSubnode = malloc(sizeof(tSuperSubnode));
    newNode->assignationSubnode->objectAttribute = objectAttribute;
    newNode->assignationSubnode->arrayAssignationSubnode = malloc(sizeof (tArrayAssignationSubnode));
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets= malloc(sizeof(tEmptySquareBrackets));
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets->openSquareBracket=tokenNode(openSquareBracket);
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets->closeSquareBracket=tokenNode(closeSquareBracket);


    newNode->assignationSubnode->arrayAssignationSubnode->assignation=tokenNode(assignation);

    newNode->assignationSubnode->arrayAssignationSubnode->genericArrayWithBrackets= malloc(sizeof(tGenericArrayWithBracket));

    newNode->assignationSubnode->arrayAssignationSubnode->genericArrayWithBrackets->openBracket=tokenNode(openBrace);
    newNode->assignationSubnode->arrayAssignationSubnode->genericArrayWithBrackets->genericValueArray=genericValueArray;
    newNode->assignationSubnode->arrayAssignationSubnode->genericArrayWithBrackets->closeBracket=tokenNode(closeBrace);


    newNode->assignationSubnode->arrayAssignationSubnode->semicolon=tokenNode(semicolon);

    return newNode;

}

tAssignation  * assignationRule9GrammarAction(tObjectAttribute* objectAttribute, int openSquareBracket, int closeSquareBracket,  int assignation, char* string, int semicolon){
    tAssignation * newNode= malloc(sizeof(tAssignation));
    newNode->assignationSubnode = malloc(sizeof(*(newNode->arrayAssignation)));
    newNode->assignationSubnode->objectAttribute = objectAttribute;
    newNode->assignationSubnode->arrayAssignationSubnode = malloc(sizeof(*(newNode->assignationSubnode->arrayAssignationSubnode)));
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets = malloc(sizeof(*(newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets)));
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets->openSquareBracket = tokenNode(openSquareBracket);
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets->closeSquareBracket = tokenNode(closeSquareBracket);
    newNode->assignationSubnode->arrayAssignationSubnode->assignation = tokenNode(assignation);
    newNode->assignationSubnode->arrayAssignationSubnode->string = varnameNode(string);
    newNode->assignationSubnode->arrayAssignationSubnode->semicolon = tokenNode(semicolon);
    return newNode;
}
/**
 * @section
 * value
 */
tValue * valueSingle(void * value){
    tValue * result = malloc(sizeof(tValue));
    result->integerExpression = value;
    return result;
}
tValue * valueSingleCharacter(char * value){
    tValue * result = malloc(sizeof(tValue));
    result->integerExpression = varnameNode(value);
    return result;
}
tValue * valueSingleString(char value){
    tValue * result = malloc(sizeof(tValue));
    result->integerExpression = charNode(value);
    return result;
}
tValue * valueObjectAttributeDesreferencing(tObjectAttribute* objectAttribute, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket){
    tValue * result = malloc(sizeof(tValue));
    result->objectAttributeDesreferencing = malloc(sizeof(*(result->objectAttributeDesreferencing)));
    result->objectAttributeDesreferencing->objectAttribute = objectAttribute;
    result->objectAttributeDesreferencing->openSquareBracket = tokenNode(openSquareBracket);
    result->objectAttributeDesreferencing->index = integerExpression;
    result->objectAttributeDesreferencing->closeSquareBracket = tokenNode(closeSquareBracket);
    return result;
}
tValue * valueObjectAttributeDesreferencingAttribute(tObjectAttribute* objectAttribute, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int point, char * varname){
    tValue * result = malloc(sizeof(tValue));
    result->objectAttributeDesreferencing = malloc(sizeof(*(result->objectAttributeDesreferencing)));
    result->objectAttributeDesreferencing->objectAttribute = objectAttribute;
    result->objectAttributeDesreferencing->openSquareBracket = tokenNode(openSquareBracket);
    result->objectAttributeDesreferencing->index = integerExpression;
    result->objectAttributeDesreferencing->closeSquareBracket = tokenNode(closeSquareBracket);
    result->objectAttributeDesreferencing->pointInnerAtributte = malloc(sizeof(*(result->objectAttributeDesreferencing->pointInnerAtributte)));
    result->objectAttributeDesreferencing->pointInnerAtributte->point = tokenNode(point);
    result->objectAttributeDesreferencing->pointInnerAtributte->innerAttributeName = varnameNode(varname);
    return result;
}

/**
 * @section
 * generic_value_array
 */
tGenericValueArray * genericValueArraySingle(tGenericValue * value){
    tGenericValueArray * genericValueArray = malloc(sizeof(tGenericValueArray));
    genericValueArray->genericValue = value;
    return genericValueArray;
}
tGenericValueArray * genericValueArrayPlural(tGenericValue * value, int comma, tGenericValueArray * argumentValues1){
    tGenericValueArray * genericValueArray = malloc(sizeof(tGenericValueArray));
    genericValueArray->genericValue = value;
    genericValueArray->commaGenericValueArray = malloc(sizeof(*(genericValueArray->commaGenericValueArray)));
    genericValueArray->commaGenericValueArray->comma = tokenNode(comma);
    genericValueArray->commaGenericValueArray->genericValueArray = argumentValues1;
    return genericValueArray;
}

/**
 * @section
 * generic_value
 */
tGenericValue * genericValue(void * value){
    tGenericValue * result = malloc(sizeof(tGenericValue));
    result->varname = value;
    return result;
}
tGenericValue * genericValueCharacter(char value){
    tGenericValue * result = malloc(sizeof(tGenericValue));
    result->varname = charNode(value);
    return result;
}
tGenericValue * genericValueInteger(int value){
    tGenericValue * result = malloc(sizeof(tGenericValue));
    result->varname = integerNode(value);
    return result;
}
tGenericValue * genericValueVarname(char * value){
    tGenericValue * result = malloc(sizeof(tGenericValue));
    result->varname = varnameNode(value);
    return result;
}
/**
 * @section
 * char_value
 */
tCharValue * charValue(void * value){
    tCharValue * result = malloc(sizeof(tCharValue));
    result->varname = value;
    return result;
}
tCharValue * charValueCharacter(char value){
    tCharValue * result = malloc(sizeof(tCharValue));
    result->varname = charNode(value);
    return result;
}
tCharValue * charValueVarname(char * value){
    tCharValue * result = malloc(sizeof(tCharValue));
    result->varname = varnameNode(value);
    return result;
}
/**
 * @section
 * array_assignation
 */
tArrayAssignation * arrayAssignationValueA(char * name, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int assignation, tValue* value, int semicolon){
    tArrayAssignation * arrayAssignation = malloc(sizeof(tArrayAssignation));
    arrayAssignation->varname = varnameNode(name);
    arrayAssignation->openSquareBracket = tokenNode(openSquareBracket);
    arrayAssignation->index = integerExpression;
    arrayAssignation->closeSquareBracket = tokenNode(closeSquareBracket);
    arrayAssignation->assignation = tokenNode(assignation);
    arrayAssignation->valueSemicolon = malloc(sizeof(*(arrayAssignation->valueSemicolon)));
    arrayAssignation->valueSemicolon->value = value;
    arrayAssignation->valueSemicolon->semicolon = tokenNode(semicolon);
    return arrayAssignation;
}
tArrayAssignation * arrayAssignationValueB(tObjectAttribute * name, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int assignation, tValue* value, int semicolon){
    tArrayAssignation * arrayAssignation = malloc(sizeof(tArrayAssignation));
    arrayAssignation->objectAttribute = name;
    arrayAssignation->openSquareBracket = tokenNode(openSquareBracket);
    arrayAssignation->index = integerExpression;
    arrayAssignation->closeSquareBracket = tokenNode(closeSquareBracket);
    arrayAssignation->assignation = tokenNode(assignation);
    arrayAssignation->valueSemicolon = malloc(sizeof(*(arrayAssignation->valueSemicolon)));
    arrayAssignation->valueSemicolon->value = value;
    arrayAssignation->valueSemicolon->semicolon = tokenNode(semicolon);
    return arrayAssignation;
}
tArrayAssignation * arrayAssignationSemicolonA(char * name, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int assignation, tInstantiation* instantiation){
    tArrayAssignation * arrayAssignation = malloc(sizeof(tArrayAssignation));
    arrayAssignation->varname = varnameNode(name);
    arrayAssignation->openSquareBracket = tokenNode(openSquareBracket);
    arrayAssignation->index = integerExpression;
    arrayAssignation->closeSquareBracket = tokenNode(closeSquareBracket);
    arrayAssignation->assignation = tokenNode(assignation);
    arrayAssignation->valueSemicolon = malloc(sizeof(*(arrayAssignation->valueSemicolon)));
    arrayAssignation->instantiation = instantiation;
    return arrayAssignation;
}
tArrayAssignation * arrayAssignationSemicolonB(tObjectAttribute * name, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int assignation, tInstantiation* instantiation){
    tArrayAssignation * arrayAssignation = malloc(sizeof(tArrayAssignation));
    arrayAssignation->objectAttribute = name;
    arrayAssignation->openSquareBracket = tokenNode(openSquareBracket);
    arrayAssignation->index = integerExpression;
    arrayAssignation->closeSquareBracket = tokenNode(closeSquareBracket);
    arrayAssignation->assignation = tokenNode(assignation);
    arrayAssignation->valueSemicolon = malloc(sizeof(*(arrayAssignation->valueSemicolon)));
    arrayAssignation->instantiation = instantiation;
    return arrayAssignation;
}

////methods

tMethods * methods(tFunction* function, tMethods* methods){
    tMethods * newNode= malloc(sizeof(tMethods));
    newNode->function=function;
    newNode->methods=methods;
    return newNode;
}

////method_call

tMethodCall * methodCall(char * varname, int point,
                         tFunctionCall* functionCall){
    tMethodCall * newNode= malloc(sizeof(tMethodCall));
    newNode->varname=varnameNode(varname);
    newNode->point=tokenNode(point);
    newNode->functionCall=functionCall;
    return newNode;
}

////datatype
tDataType * dataType(int token){
    tDataType * newNode= malloc(sizeof(tDataType));
    newNode->type=tokenNode(token);
    return newNode;
}

////parameters

tParameters * basicParameters(tDataType* dataType, char * varname){
    tParameters * newNode= malloc(sizeof(tParameters));
    newNode->datatype=dataType;
    newNode->paramName=varnameNode(varname);
    return newNode;
}
//
tParameters * multiBasicParameters(tDataType* dataType, char* paramName,
                                   int comma, tParameters* parameters){
    tParameters * newNode= basicParameters(dataType, paramName);
    newNode->nextParameters= malloc(sizeof(tCommaNextParameters));
    newNode->nextParameters->comma=tokenNode(comma);
    newNode->nextParameters->nextParameters=parameters;
    return newNode;
}

tParameters * objectParameters( char * objectType, char * paramName){
    tParameters * newNode= malloc(sizeof(tParameters));
    newNode->objectTypeName=varnameNode(objectType);
    newNode->paramName=varnameNode(paramName);
    return newNode;
}

tParameters * multiObjectParameters( char* objectType, char* paramName,
                                     int comma, tParameters* parameters){
    tParameters * newNode= objectParameters(objectType, paramName);
    newNode->nextParameters= malloc(sizeof(tCommaNextParameters));
    newNode->nextParameters->comma=tokenNode(comma);
    newNode->nextParameters->nextParameters=parameters;
    return newNode;
}

tParameters * arrayParameters(tDataType* dataType, char * paramName,
                              int openSquareBracket, int closeSquareBracket){
    tParameters * newNode= basicParameters(dataType, paramName);
    newNode->squareBrackets= malloc(sizeof(tEmptySquareBrackets));
    newNode->squareBrackets->closeSquareBracket=tokenNode(closeSquareBracket);
    newNode->squareBrackets->openSquareBracket=tokenNode(openSquareBracket);
    return newNode;
}

tParameters * multiArrayParameters(tDataType* dataType, int paramName,
                              int openSquareBracket, int closeSquareBracket,
                              int comma, tParameters* parameters){
    tParameters * newNode= arrayParameters(dataType, paramName, openSquareBracket, closeSquareBracket);
    newNode->nextParameters= malloc(sizeof(tCommaNextParameters));
    newNode->nextParameters->comma=tokenNode(comma);
    newNode->nextParameters->nextParameters=parameters;
    return newNode;
}

tParameters * objectArrayParameters(int objectType, int paramName,
                              int openSquareBracket, int closeSquareBracket){
    tParameters * newNode= objectParameters(objectType,paramName);
    newNode->squareBrackets= malloc(sizeof(tEmptySquareBrackets));
    newNode->squareBrackets->closeSquareBracket=tokenNode(closeSquareBracket);
    newNode->squareBrackets->openSquareBracket=tokenNode(openSquareBracket);
    return newNode;
}

tParameters * multiObjectArrayParameters(int objectType, int paramName,
                                    int openSquareBracket, int closeSquareBracket,
                                    int comma, tParameters* parameters) {
    tParameters * newNode= objectArrayParameters(objectType,paramName, openSquareBracket, closeSquareBracket);
    newNode->nextParameters= malloc(sizeof(tCommaNextParameters));
    newNode->nextParameters->comma=tokenNode(comma);
    newNode->nextParameters->nextParameters=parameters;
    return newNode;

}

/**
 * @section
 * main_function
 */
tMainFunction * mainFunctionRule(int integerType, int main, int openP, tParameters * parameters, int closeP, int openBrace, tProgramStatements* programStatements, int closeBrace){
    tMainFunction * function = malloc(sizeof(tFunction));
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
tFunction * functionRuleWithType(void * type, char * varname, int openP, tParameters * parameters, int closeP, int openBrace, tProgramStatements* programStatements, int closeBrace){
    tFunction * function = malloc(sizeof(tFunction));
    function->datatype = type;
    function->varname = varnameNode(varname);
    function->openP = tokenNode(openP);
    function->parameters = parameters;
    function->closeP = tokenNode(closeP);
    function->openBrace = tokenNode(openBrace);
    function->programStatements = programStatements;
    function->closeBrace = tokenNode(closeBrace);
    return function;
}
tFunction * functionRuleNoType(char * varname, int openP, tParameters * parameters, int closeP, int openBrace, tProgramStatements* programStatements, int closeBrace){
    return functionRuleWithType(NULL, varname, openP, parameters, closeP, openBrace, programStatements, closeBrace);
}
////constructor
tConstructor * constructor(int constructor, tFunction* function){
    tConstructor  * newNode = malloc(sizeof(tConstructor));
    newNode->constructor=tokenNode(constructor);
    newNode->function=function;
    return newNode;
}
////declarations
tDeclarations* declarations(tDeclaration * declaration, tDeclarations* declarations){
    tDeclarations * newNode= malloc(sizeof(tDeclarations));
    newNode->declarations= declarations;
    newNode->declaration= declaration;
    return newNode;
}
////attributes
tAttributes* attributes(int attributes, int openBrace,
                        tDeclarations* declarations, int closeBrace){
    tAttributes * newNode= malloc(sizeof(tAttributes));
    newNode->attributes=tokenNode(attributes);
    newNode->operBrace=tokenNode(openBrace);
    newNode->declarations=declarations;
    newNode->closeBrace=tokenNode(closeBrace);
    return newNode;
}

////comparison_operator
tComparisonOperator * comparisonOperator(int token){
    tComparisonOperator* newNode= malloc(sizeof(tComparisonOperator));
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
    tLogicalOperator * newNode= malloc(sizeof(tLogicalOperator));
    newNode->andToken = newToken;
    return newNode;
}
////comparation
tComparation * comparation(tValue* lValue, tComparisonOperator* comparisonOperator,
                           tValue* rValue){
    tComparation * newNode= malloc(sizeof(tComparation));
    newNode->lValue=lValue;
    newNode->comparisonOperator=comparisonOperator;
    newNode->rValue=rValue;
    return newNode;
}
////condition_unit
tConditionUnit * simpleConditionUnit(tCondition* condition){
    tConditionUnit * newNode= malloc(sizeof(tConditionUnit));
    newNode->condition=condition;
    return newNode;
}

tConditionUnit * conditionUnitValOpVal(tValue* lValue, struct tLogicalOperator* logicalOperator,
                                       tValue* rValue){
    tConditionUnit * newNode= malloc(sizeof(tConditionUnit));
    newNode->valueComparatorValue= malloc(sizeof(tValueComparatorValue));
    newNode->valueComparatorValue->lValue=lValue;
    newNode->valueComparatorValue->logicalOperator=logicalOperator;
    newNode->valueComparatorValue->rValue=rValue;
    return newNode;
}

tConditionUnit * conditionUnitCompOpCond(tComparation* comparation,tLogicalOperator* logicalOperator,
                                         tConditionUnit* conditionUnit){
    tConditionUnit * newNode= malloc(sizeof(tConditionUnit));
    newNode->logicalComparationUnit= malloc(sizeof(tLogicalComparationUnit));
    newNode->logicalComparationUnit->comparation=comparation;
    newNode->logicalComparationUnit->logicalOperator=logicalOperator;
    newNode->logicalComparationUnit->conditionUnit=conditionUnit;
    return newNode;
}

tConditionUnit * conditionUnitComparation(tComparation* comparation){
    tConditionUnit * newNode= malloc(sizeof(tConditionUnit));
    newNode->comparation= comparation;
    return newNode;
}
////condition
tCondition * condition(int openParenthesis, tConditionUnit* conditionUnit,
                       int closeParenthesis){
    tCondition * newNode= malloc(sizeof(tCondition));
    newNode->openP=tokenNode(openParenthesis);
    newNode->conditionUnit=conditionUnit;
    newNode->closeP=tokenNode(closeParenthesis);
    return newNode;
}

////clause
//
tClause * clause(int openBrace, tProgramStatements* programStatements,
                 int closeBrace){
    tClause * newNode= malloc(sizeof(tClause));
    newNode->openBrace= tokenNode(openBrace);
    newNode->programStatements=programStatements;
    newNode->closeBrace= tokenNode(closeBrace);
    return newNode;
}
////while_loop
//
tWhileLoop * whileLoop(int whileToken, tCondition* condition,
                       tClause* clause){
    tWhileLoop * newNode= malloc(sizeof(tWhileLoop));
    newNode->whileReserved= tokenNode(whileToken);
    newNode->conditionClause=condition;
    newNode->clause=clause;
    return newNode;
}
////if
//
tIf* If(int ifToken, struct tCondition* condition, tClause* clause){
    tIf * newNode = malloc(sizeof(tIf));
    newNode->ifReserved=tokenNode(ifToken);
    newNode->condition = condition;
    newNode->clause=clause;
    return newNode;
}
//
tIf* IfElse(int ifToken, struct tCondition* condition, tClause* ifClause, int elseToken, tClause* elseClause){
    tIf* newNode= If(ifToken, condition, ifClause);
    newNode->ifElseStatement= malloc(sizeof(tIfElseStatement));
    newNode->ifElseStatement->elseReserved= tokenNode(elseToken);
    newNode->ifElseStatement->clause=elseClause;
    return newNode;
}

/**
 * @section
 * argument_values
 */
 //
tArgumentValues * argumentValuesSingle(tValue * value){
    tArgumentValues * argumentValues = malloc(sizeof(tArgumentValues));
    argumentValues->value = value;
    return argumentValues;
}
//
tArgumentValues * argumentValuesPlural(tValue * value, int comma, tArgumentValues * argumentValues1){
    tArgumentValues * argumentValues = malloc(sizeof(tArgumentValues));
    argumentValues->value = value;
    argumentValues->commaNextArgumentValue = malloc(sizeof(*(argumentValues->commaNextArgumentValue)));
    argumentValues->commaNextArgumentValue->comma = tokenNode(comma);
    argumentValues->commaNextArgumentValue->nextArgument = argumentValues1;
    return argumentValues;
}

/**
 * @section
 * program_unit_statements
 */
 //
tProgramUnitStatements * programUnitStatements(void * unit){
    tProgramUnitStatements * programUnitStatements1 = malloc(sizeof(tProgramUnitStatements));
    programUnitStatements1->assignation = unit;
    return programUnitStatements1;
}
//
tProgramUnitStatements * programUnitStatementsIntegerExpression(tIntegerExpression * integerExpression, int semicolon){
    tProgramUnitStatements * programUnitStatements1 = malloc(sizeof(tProgramUnitStatements));
    programUnitStatements1->integerExpressionSemicolon = malloc(sizeof(*(programUnitStatements1->integerExpressionSemicolon)));
    programUnitStatements1->integerExpressionSemicolon->integerExpression = integerExpression;
    programUnitStatements1->integerExpressionSemicolon->semicolon = tokenNode(semicolon);
    return programUnitStatements1;
}

/**
 * @section
 * program_statements
 */
 //
tProgramStatements * programStatementsRule(tProgramUnitStatements * programUnitStatements, tProgramStatements * programStatements){
    tProgramStatements * newProgramStatements = malloc(sizeof(tProgramStatements));
    newProgramStatements->programUnitStatements = programUnitStatements;
    newProgramStatements->programUnitStatements = programUnitStatements;
    return newProgramStatements;
}

/**
 * @section
 * array_desreferencing
 */
 //
tArrayDesreferencing * arrayDesreferencing(char * varname, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket){
    tArrayDesreferencing * arrayDesreferencing1 = malloc(sizeof(tArrayDesreferencing));
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
tReturn * returnRuleValue(int ret, void * value, int semicolon){
    tReturn * aReturn = malloc(sizeof(tReturn));
    aReturn->semicolon = tokenNode(semicolon);
    aReturn->returnToken = tokenNode(ret);
    aReturn->valueUnion.value = value;
    return aReturn;
}
//
tReturn * returnRuleNoValue(int ret, int semicolon){
    tReturn * aReturn = malloc(sizeof(tReturn));
    aReturn->semicolon = tokenNode(ret);
    aReturn->returnToken = tokenNode(semicolon);
    return aReturn;
}


/**
 * @section
 * integer_expression
 */
 //
tIntegerExpression * integerExpressionCommon(tIntegerExpression * integerExpression1, int operator, tIntegerExpression * integerExpression2){
    tIntegerExpression * integerExpression = malloc(sizeof(tIntegerExpression));
    integerExpression->commonIntegerExpression = malloc(sizeof(*(integerExpression->commonIntegerExpression)));
    integerExpression->commonIntegerExpression->leftIntegerExpression = integerExpression1;
    integerExpression->commonIntegerExpression->operator = tokenNode(operator);
    integerExpression->commonIntegerExpression->rightIntegerExpression = integerExpression2;
    return integerExpression;
}
//
tIntegerExpression  * integerExpressionFactor(tFactor * factor){
    tIntegerExpression * integerExpression = malloc(sizeof(tIntegerExpression));
    integerExpression->factor = factor;
    return integerExpression;
}
//
tIntegerExpression * integerExpressionIncrementDecrement(tIntegerExpression * expression, int operator){
    tIntegerExpression * integerExpression = malloc(sizeof(tIntegerExpression));
    integerExpression->decrementIncrementIntegerExpression = malloc(sizeof(*(integerExpression->decrementIncrementIntegerExpression)));
    integerExpression->decrementIncrementIntegerExpression->leftIntegerExpression = expression;
    integerExpression->decrementIncrementIntegerExpression->operator = tokenNode(operator);
    return integerExpression;
}
//
tIntegerExpression * integerExpressionEnclosed(int openP, tIntegerExpression * expression, int closeP){
    tIntegerExpression * integerExpression = malloc(sizeof(tIntegerExpression));
    integerExpression->enclosedCommonIntegerExpression = malloc(sizeof(*(integerExpression->enclosedCommonIntegerExpression)));
    integerExpression->enclosedCommonIntegerExpression->openParenthesis = tokenNode(openP);
    integerExpression->enclosedCommonIntegerExpression->integerExpression = expression;
    integerExpression->enclosedCommonIntegerExpression->closeParenthesis = tokenNode(closeP);
    return integerExpression;
}

/**
 * @section
 * factor
 */
 //
 tFactor * factorObjectAttribute(tObjectAttribute * objectAttribute){
    tFactor * factor = malloc(sizeof(tFactor));
    factor->object_attribute = objectAttribute;
    return factor;
 }
 //
tFactor * factorFunctionCall(tFunctionCall * functionCall){
    tFactor * factor = malloc(sizeof(tFactor));
    factor->function_call = functionCall;
    return factor;
}
//
tFactor * factorMethodCall(tMethodCall * methodCall){
    tFactor * factor = malloc(sizeof(tFactor));
    factor->method_call = methodCall;
    return factor;
}
//
tFactor * factorVarname(char * varname){
    tFactor * factor = malloc(sizeof(tFactor));
    factor->varname = varnameNode(varname);
    return factor;
}
//
tFactor * factorArrayDesreferencing(tArrayDesreferencing * arrayDesreferencing){
    tFactor * factor = malloc(sizeof(tFactor));
    factor->array_desreferencing = arrayDesreferencing;
    return factor;
}
//
tFactor * factorSubInteger(int sub, int integer){
    tFactor * factor = malloc(sizeof(tFactor));
    tSubInteger * subInteger = malloc(sizeof(tSubInteger));
    subInteger->integer = integerNode(integer);
    subInteger->sub = tokenNode(sub);
    factor->subInteger = subInteger;
    return factor;
}
//
tFactor * factorInteger(int integer){
    tFactor * factor = malloc(sizeof(tFactor));
    factor->integer = integerNode(integer);
    return factor;
}

/**
 * @section
 * object_attribute
 */
//
tObjectAttribute * objectAttributeFromVarname(char * object, int point, char * attributeName){
    tObjectAttribute * objectAttribute = malloc(sizeof(tObjectAttribute));
    objectAttribute->varnameLeft = varnameNode(object);
    objectAttribute->point = tokenNode(point);
    objectAttribute->varnameRight = varnameNode(attributeName);
    return objectAttribute;
}
//
tObjectAttribute * objectAttributeFromObjectAttribute(tObjectAttribute * object, int point, char * attributeName){
    tObjectAttribute * objectAttribute = malloc(sizeof(tObjectAttribute));
    objectAttribute->objectAttribute = object;
    objectAttribute->point = tokenNode(point);
    objectAttribute->varnameRight = varnameNode(attributeName);
    return objectAttribute;
}
//
tObjectAttribute * objectAttributeFromArrayDesreferencing(tArrayDesreferencing* object, int point, char * attributeName){
    tObjectAttribute * objectAttribute = malloc(sizeof(tObjectAttribute));
    objectAttribute->arrayDesreferencing = object;
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
    tFunctionCall * functionCall = malloc(sizeof(tFunctionCall));
    functionCall->functionName = varnameNode(functionName);
    functionCall->openP = tokenNode(openP);
    functionCall->firstArgument = argumentValues;
    functionCall->closeP = tokenNode(closeP);
    return functionCall;
}


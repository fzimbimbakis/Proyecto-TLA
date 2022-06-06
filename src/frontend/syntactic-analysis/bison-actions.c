#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include "bison-parser.h"
#include <stdio.h>
#include <string.h>

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











tTokenNode * tokenGrammarActionWithChar(const int tokenId,char character){
    tTokenNode  * newNode = malloc(sizeof (tTokenNode));
    newNode->tokenId = tokenId;
    newNode->associated_value.charValue = character;
    return newNode;
}


tTokenNode * tokenGrammarActionWithInt(const int tokenId,int integer){
    tTokenNode  * newNode = malloc(sizeof (tTokenNode));
    newNode->tokenId = tokenId;
    newNode->associated_value.integerValue = integer;
    return newNode;
}


tTokenNode * tokenGrammarActionWitString(const int tokenId,char * string){
    tTokenNode  * newNode = malloc(sizeof (tTokenNode));
    newNode->tokenId = tokenId;
    newNode->associated_value.varname = malloc(strlen(string));
    strcpy(newNode->associated_value.varname,string);
    return newNode;
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
tClass  * ClassGrammarAction(tTokenNode * class, tTokenNode * varname, tTokenNode * openBrace ,tClassIn * classIn , tTokenNode * closeBrace){
    tClass  * newNode = malloc(sizeof(tClass));
    newNode->class = class ;
    newNode->varname = varname;
    newNode->openBrace = openBrace;
    newNode->classIn = classIn ;
    newNode->closeBrace = closeBrace;
    return newNode;
}

tClass * ClassGrammarActionWithHerency(tTokenNode * class, tTokenNode * fatherName,tTokenNode * extends,tTokenNode  *className , tTokenNode * openBrace ,tClassIn * classIn , tTokenNode * closeBrace){
    tClass  * newNode = malloc(sizeof(tClass));
    newNode->class = class ;
    newNode->varname = className;

    tExtendsName * extendsName = malloc(sizeof(tExtendsName));
    extendsName->extendedClassName = fatherName;
    extendsName->extends = extends ;
    newNode->extendsName=extendsName;

    newNode->openBrace = openBrace;
    newNode->classIn = classIn ;
    newNode->closeBrace = closeBrace;
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
tInstantiation * instantiationGrammarAction(tTokenNode *  new , tFunctionCall * functionCall , tTokenNode * semicolon ){
    tInstantiation  * newNode = malloc(sizeof(tInstantiation));
    newNode->new = new;
    newNode->functionCall = functionCall;
    newNode->semicolon  = semicolon;
    return newNode;

}

////declaration
tDeclaration  * charDeclarationGrammarAction(tCharDeclaration * charDeclaration ){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->charDeclaration = charDeclaration;
    return newNode;
}

tDeclaration * integerDeclarationGrammarAction( struct tIntegerDeclaration * tIntegerDeclaration ){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->integerAssignationDeclaration = tIntegerDeclaration;
    return newNode;
}

tDeclaration * charArrayDeclarationGrammarAction( struct tCharArrayDeclaration * tCharArrayDeclaration){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->charArrayDeclaration = tCharArrayDeclaration;
    return newNode;
}

tDeclaration * integerArrayDeclarationGrammarAction( struct tIntegerArrayDeclaration * tIntegerArrayDeclaration){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->integerAssignationDeclaration = tIntegerArrayDeclaration;
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
    newNode->integerArrayAssignationDeclaration= CharArrayAssignationDeclaration;
    return newNode;
}

tDeclaration * declarationWithObjectDataTypeGrammarAction(  tDeclarationWithObjectDataType * declarationWithObjectDataType){
    tDeclaration  * newNode = malloc(sizeof(tDeclaration));
    newNode->declarationAux= declarationWithObjectDataType;
    return newNode;
}

////integer_assignation_declaration
tIntegerAssignationDeclaration * integerAssignationDeclarationRuleGrammarAction(tTokenNode * intReserved , tTokenNode * varname , tTokenNode * assignation , tIntegerExpression * integerExpression , tTokenNode * semicolon){
    tIntegerAssignationDeclaration * newNode = malloc(sizeof(tIntegerAssignationDeclaration));
    newNode -> integer = intReserved;
    newNode->varname = varname;
    newNode->assignation = assignation ;
    newNode->integerExpression = integerExpression ;
    newNode->semicolon = semicolon ;
    return newNode;
}

////char_assignation_declaration
tCharAssignationDeclaration  * charAssignationDeclarationRuleGrammarAction (tTokenNode * character , tTokenNode * varname , tTokenNode * assignation , tCharValue * charValue , tTokenNode * semicolon){
    tCharAssignationDeclaration * newNode = malloc(sizeof(tCharAssignationDeclaration ));
    newNode -> character= character;
    newNode->varname = varname;
    newNode->assignation = assignation ;
    newNode->charValue = charValue ;
    newNode->semicolon = semicolon ;
    return newNode;

}
////integer_array_assignation_declaration
tIntegerArrayAssignationDeclaration * integerArrayAssignationDeclarationGrammarAction(tTokenNode * intReserved , tTokenNode * varname ,tTokenNode * openSquareBracket,tTokenNode * closeSquareBracket, tTokenNode * assignation, tTokenNode * openBrace , tIntegerArray * integerArray , tTokenNode * closeBrace ,tTokenNode * semicolon ){
    tIntegerArrayAssignationDeclaration * newNode = malloc(sizeof(tIntegerArrayAssignationDeclaration));
    newNode-> integer= intReserved;
    newNode->varname = varname ;
    newNode -> openSquareBracket = openSquareBracket;
    newNode -> closeSquareBracket = closeSquareBracket  ;
    newNode -> assignation = assignation;
    newNode -> openBrace = openBrace;
    newNode->integerArray = integerArray ;
    newNode -> closeBrace = closeBrace ;
    newNode -> semicolon = semicolon;
    return newNode;
}
////char_array_assignation_declaration
tCharArrayAssignationDeclaration * charArrayAssignationDeclarationRuleGrammarAction(tTokenNode * charReserved , tTokenNode * varname , tTokenNode * openSquareBracket,tTokenNode * closeSquareBracket,tTokenNode * assignation , tTokenNode * openBrace , tCharacterArray * characterArray , tTokenNode * closeBrace , tTokenNode * semicolon ){
    tCharArrayAssignationDeclaration * newNode  = malloc(sizeof(tCharArrayAssignationDeclaration));
    newNode->charType = charReserved ;
    newNode->name = varname ;
    tEmptySquareBrackets  * emptySquareBrackets = malloc(sizeof(tEmptySquareBrackets));
    emptySquareBrackets -> openSquareBracket = openSquareBracket ;
    emptySquareBrackets->closeSquareBracket = closeSquareBracket;
    newNode->emptySquareBrackets = emptySquareBrackets;
    newNode->assignation = assignation;
    tCharArrayWithBrackets  * arrayWithBrackets = malloc(sizeof (tCharArrayWithBrackets));
    arrayWithBrackets->openBrace = openBrace;
    arrayWithBrackets->characterArray = characterArray;
    arrayWithBrackets->closeBrace = closeBrace;
    newNode->charArrayWithBrackets = arrayWithBrackets;
    newNode->semicolon = semicolon;
    return newNode;
}

tCharArrayAssignationDeclaration  * charArrayAssignationDeclarationRule2GrammarAction(tTokenNode * charReserved , tTokenNode * varname , tTokenNode * openSquareBracket,tTokenNode * closeSquareBracket,tTokenNode * assignation , tTokenNode  * string, tTokenNode * semicolon){
    tCharArrayAssignationDeclaration * newNode = malloc(sizeof (tCharArrayAssignationDeclaration));
    newNode->charType = charReserved;
    newNode->name= varname;
    tEmptySquareBrackets  * emptySquareBrackets = malloc(sizeof(tEmptySquareBrackets));
    emptySquareBrackets -> openSquareBracket = openSquareBracket ;
    emptySquareBrackets->closeSquareBracket = closeSquareBracket;
    newNode->emptySquareBrackets = emptySquareBrackets;
    newNode->assignation = assignation;
    newNode->string = string;
    newNode -> semicolon = semicolon;
    return newNode;
}

////integer_array
tIntegerArray  * tIntegerArrayGrammarAction(tIntegerExpression * integerExpression ){
    tIntegerArray * newNode = malloc(sizeof(tIntegerArray));
    newNode->integerExpression = integerExpression ;
    return newNode;
}
tIntegerArray  * tIntegerArraywithCommaGrammarAction(tIntegerExpression * integerExpression ,tTokenNode * comma , tIntegerArray * integerArray){
    tIntegerArray * newNode = malloc(sizeof(tIntegerArray));
    newNode->integerExpression = integerExpression ;
    tCommaIntegerArray * commaIntegerArray = malloc(sizeof(tCommaIntegerArray));
    commaIntegerArray->comma = comma;
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

tCharacterArray  * characterArrayRule2GrammarAction(tCharValue * charValue ,tTokenNode * comma , tCharacterArray * characterArray ){
    tCharacterArray  * newNode = malloc(sizeof (tCharacterArray));
    newNode->charValue = charValue ;
    tCommaCharacterArray  * commaCharacterArray = malloc(sizeof(tCommaCharacterArray));
    commaCharacterArray->comma = comma ;
    commaCharacterArray->next = characterArray ;
    newNode->commaCharacterArray = commaCharacterArray;
    return newNode;
}


////integer_declaration
tIntDeclaration * integerDeclarationRuleGrammarAction(tTokenNode * intReserved , tTokenNode * varname , tTokenNode * semicolon ){
    tIntDeclaration * newNode = malloc(sizeof(tIntDeclaration));
    newNode->integer = intReserved ;
    newNode -> varname = varname;
    newNode->semicolon = semicolon ;
    return newNode ;
}

////char_declaration
tCharDeclaration * charDeclarationRuleGrammarAction(tTokenNode * charReserved , tTokenNode * varname , tTokenNode * semicolon ){
    tCharDeclaration * newNode = malloc(sizeof(tCharDeclaration));
    newNode->character = charReserved ;
    newNode -> varname = varname;
    newNode->semicolon = semicolon ;
    return newNode ;
}

////integer_array_declaration
tIntegerArrayDeclaration * integerArrayDeclarationRuleGrammarAction(tTokenNode * intReserved, tTokenNode * varname, tTokenNode * openSquareBracket , tIntegerExpression  * integerExpression,tTokenNode * closeSquareBracket,  tTokenNode * semicolon){
    tIntegerArrayDeclaration * newNode  = malloc(sizeof(tIntegerArrayDeclaration));
    newNode->integer = intReserved;
    newNode->varname = varname;
    newNode->openSquareBracket = openSquareBracket ;
    newNode ->integerExpression = integerExpression ;
    newNode -> closeSquareBracket = closeSquareBracket;
    newNode->semicolon = semicolon ;
    return newNode;
}

////char_array_declaration
tCharArrayDeclaration * charArrayDeclarationRuleGrammarAction(tTokenNode * charReserved , tTokenNode * varname , tTokenNode * openSquareBracket, tIntegerExpression  * integerExpression , tTokenNode * closeSquareBracket, tTokenNode * semicolon){
    tCharArrayDeclaration * newNode = malloc(sizeof(tCharArrayDeclaration));
    newNode->character = charReserved;
    newNode->varname = varname;
    newNode->openSquareBracket = openSquareBracket;
    newNode->integerExpression = integerExpression ;
    newNode->closeSquareBracket = closeSquareBracket;
    newNode->semicolon = semicolon;
    return newNode;
}

tCharArrayDeclaration * charArrayDeclarationRule2GrammarAction(tTokenNode * charReserved , tTokenNode * varname , tTokenNode * openSquareBracket, tTokenNode * closeSquareBracket, tTokenNode * semicolon){
    tCharArrayDeclaration * newNode = malloc(sizeof(tCharArrayDeclaration));
    newNode->character = charReserved;
    newNode->varname = varname;
    newNode->openSquareBracket = openSquareBracket;
    newNode->closeSquareBracket = closeSquareBracket;
    newNode->semicolon = semicolon;
    return newNode;
}
////assignation
tAssignation  * assignationGrammarAction(tTokenNode * varname, tTokenNode * assignation , tValue * value , tTokenNode * semicolon){
    tAssignation  * newNode = malloc(sizeof(tAssignation));
    tSuperSubnode  * subnode = malloc(sizeof(tSuperSubnode));
    subnode->varname = varname;

    tSimpleAssignationSubnode * simpleAssignationSubnode = malloc(sizeof(tSimpleAssignationSubnode));
    simpleAssignationSubnode->assignation = assignation;

    tArrayValueSemicolon  * arrayValueSemicolon = malloc(sizeof(tArrayValueSemicolon));
    arrayValueSemicolon->value = value;
    arrayValueSemicolon ->semicolon = semicolon ;
    simpleAssignationSubnode->arrayValueSemicolon = arrayValueSemicolon ;

    subnode->simpleAssignationSubnode= simpleAssignationSubnode;
    newNode->assignationSubnode = subnode;

    return newNode;
}


tAssignation  * assignationRule2GrammarAction(tTokenNode * varname, tTokenNode * assignation , tInstantiation * instantiation){
    tAssignation  * newNode = malloc(sizeof(tAssignation));
    tSuperSubnode  * subnode = malloc(sizeof(tSuperSubnode));
    subnode->varname = varname;

    tSimpleAssignationSubnode * simpleAssignationSubnode = malloc(sizeof(tSimpleAssignationSubnode));
    simpleAssignationSubnode->assignation = assignation;
    simpleAssignationSubnode->instantation = instantiation;

    subnode->simpleAssignationSubnode= simpleAssignationSubnode;
    newNode->assignationSubnode = subnode;

    return newNode;
}

tAssignation  * assignationRule3GrammarAction(tTokenNode * varname,tTokenNode * openSquareBracket, tTokenNode * closeSquareBracket, tTokenNode *assignation, tTokenNode * openBrace , tGenericValueArray * genericValueArray  ,  tTokenNode * closeBrace , tTokenNode * semicolon ){
        tAssignation  * newNode = malloc(sizeof(tAssignation));

    tGenericArrayWithBracket * genericArrayWithBracket  = malloc(sizeof(tGenericArrayWithBracket));
    genericArrayWithBracket->openBracket = openBrace  ;
    genericArrayWithBracket->genericValueArray = genericValueArray ;
    genericArrayWithBracket->closeBracket = closeBrace;

    tArrayAssignationSubnode * arrayAssignationSubNode = malloc(sizeof(tArrayAssignationSubnode));

    arrayAssignationSubNode->assignation = assignation  ;
    arrayAssignationSubNode->genericArrayWithBrackets = genericArrayWithBracket;
    arrayAssignationSubNode->semicolon = semicolon;

    tEmptySquareBrackets * emptySquareBrackets = malloc(sizeof(tEmptySquareBrackets));
    emptySquareBrackets->openSquareBracket = openBrace;
    emptySquareBrackets->closeSquareBracket = closeBrace;

    arrayAssignationSubNode->emptySquareBrackets = emptySquareBrackets;

    tSuperSubnode  * subnode = malloc(sizeof(tSuperSubnode));
    subnode->varname = varname;
    subnode->arrayAssignationSubnode=arrayAssignationSubNode;

    return newNode;
}

tAssignation  * assignationRule4GrammarAction(tTokenNode * varname , tTokenNode * openSquareBracket, tTokenNode * closeSquareBracket, tTokenNode * assignation , tTokenNode * string , tTokenNode * semicolon){
    tAssignation  * newNode = malloc(sizeof(tAssignation));

    tSuperSubnode  * superSubnode = malloc(sizeof(tSuperSubnode));
    superSubnode->varname = varname;

    tEmptySquareBrackets * emptySquareBrackets = malloc(sizeof(tEmptySquareBrackets));
    emptySquareBrackets->openSquareBracket = openSquareBracket;
    emptySquareBrackets->closeSquareBracket = closeSquareBracket;

    tArrayAssignationSubnode * arrayAssignationSubnode = malloc(sizeof(arrayAssignationSubnode));
    arrayAssignationSubnode->assignation= assignation;
    arrayAssignationSubnode->emptySquareBrackets = emptySquareBrackets ;
    arrayAssignationSubnode->string = string ;
    arrayAssignationSubnode->semicolon = semicolon;

    superSubnode->arrayAssignationSubnode = arrayAssignationSubnode;

    newNode->assignationSubnode = superSubnode;

    return newNode;
}



tAssignation  * assignationRule5GrammarAction(tArrayAssignation* arrayAssignation){
    tAssignation * newNode= malloc(sizeof(tAssignation));
    newNode->arrayAssignation=arrayAssignation;

    return newNode;
}

tAssignation  * assignationRule6GrammarAction(tObjectAttribute* objectAttribute, tTokenNode* assignation,
                                              tValue* value, tTokenNode* semicolon){
    tAssignation * newNode= malloc(sizeof(tAssignation));
    newNode->assignationSubnode= malloc(sizeof(tSuperSubnode));
    newNode->assignationSubnode->objectAttribute=objectAttribute;
    newNode->assignationSubnode->simpleAssignationSubnode= malloc(sizeof(tSimpleAssignationSubnode));

    newNode->assignationSubnode->simpleAssignationSubnode->assignation=assignation;
    newNode->assignationSubnode->simpleAssignationSubnode->arrayValueSemicolon=malloc(sizeof(tArrayValueSemicolon));
    newNode->assignationSubnode->simpleAssignationSubnode->arrayValueSemicolon->value=value;
    newNode->assignationSubnode->simpleAssignationSubnode->arrayValueSemicolon->semicolon=semicolon;

    return newNode;

}


tAssignation  * assignationRule7GrammarAction(tObjectAttribute* objectAttribute, tTokenNode* assignation,
                                              tInstantiation* instantiation){
    tAssignation * newNode= malloc(sizeof(tAssignation));
    newNode->assignationSubnode= malloc(sizeof(tSuperSubnode));
    newNode->assignationSubnode->objectAttribute=objectAttribute;
    newNode->assignationSubnode->simpleAssignationSubnode= malloc(sizeof(tSimpleAssignationSubnode));

    newNode->assignationSubnode->simpleAssignationSubnode->assignation=assignation;
    newNode->assignationSubnode->simpleAssignationSubnode->instantation=instantiation;
    return newNode;
}

tAssignation* assignationRule8GrammarAction(tObjectAttribute* objectAttribute, tTokenNode* openSquareBracket, tTokenNode* closeSquareBracket,
                                            tTokenNode * assignation, tTokenNode* openBrace, tGenericValueArray * genericValueArray ,
                                            tTokenNode* closeBrace, tTokenNode* semicolon){
    tAssignation * newNode= malloc(sizeof(tAssignation));
    newNode->assignationSubnode = malloc(sizeof(tSuperSubnode));
    newNode->assignationSubnode->objectAttribute = objectAttribute;
    newNode->assignationSubnode->arrayAssignationSubnode = malloc(sizeof (tArrayAssignationSubnode));
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets= malloc(sizeof(tEmptySquareBrackets));
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets->openSquareBracket=openSquareBracket;
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets->closeSquareBracket=closeSquareBracket;


    newNode->assignationSubnode->arrayAssignationSubnode->assignation=assignation;

    newNode->assignationSubnode->arrayAssignationSubnode->genericArrayWithBrackets= malloc(sizeof(tGenericArrayWithBracket));

    newNode->assignationSubnode->arrayAssignationSubnode->genericArrayWithBrackets->openBracket=openBrace;
    newNode->assignationSubnode->arrayAssignationSubnode->genericArrayWithBrackets->genericValueArray=genericValueArray;
    newNode->assignationSubnode->arrayAssignationSubnode->genericArrayWithBrackets->closeBracket=closeBrace;


    newNode->assignationSubnode->arrayAssignationSubnode->semicolon=semicolon;

    return newNode;

}

tAssignation  * assignationRule9GrammarAction(tObjectAttribute* objectAttribute, tTokenNode* openSquareBracket, tTokenNode* closeSquareBracket,  tTokenNode * assignation, tTokenNode* string, tTokenNode* semicolon){
    tAssignation * newNode= malloc(sizeof(tAssignation));
    newNode->assignationSubnode = malloc(sizeof(*(newNode->arrayAssignation)));
    newNode->assignationSubnode->objectAttribute = objectAttribute;
    newNode->assignationSubnode->arrayAssignationSubnode = malloc(sizeof(*(newNode->assignationSubnode->arrayAssignationSubnode)));
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets = malloc(sizeof(*(newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets)));
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets->openSquareBracket =openSquareBracket;
    newNode->assignationSubnode->arrayAssignationSubnode->emptySquareBrackets->closeSquareBracket = closeSquareBracket;
    newNode->assignationSubnode->arrayAssignationSubnode->assignation = assignation;
    newNode->assignationSubnode->arrayAssignationSubnode->string = string;
    newNode->assignationSubnode->arrayAssignationSubnode->semicolon = semicolon;
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
tValue * valueObjectAttributeDesreferencing(tObjectAttribute* objectAttribute, tTokenNode* openSquareBracket, tIntegerExpression* integerExpression, tTokenNode* closeSquareBracket){
    tValue * result = malloc(sizeof(tValue));
    result->objectAttributeDesreferencing = malloc(sizeof(*(result->objectAttributeDesreferencing)));
    result->objectAttributeDesreferencing->objectAttribute = objectAttribute;
    result->objectAttributeDesreferencing->openSquareBracket = openSquareBracket;
    result->objectAttributeDesreferencing->index = integerExpression;
    result->objectAttributeDesreferencing->closeSquareBracket = closeSquareBracket;
    return result;
}
tValue * valueObjectAttributeDesreferencingAttribute(tObjectAttribute* objectAttribute, tTokenNode* openSquareBracket, tIntegerExpression* integerExpression, tTokenNode* closeSquareBracket, tTokenNode* point, tTokenNode* varname){
    tValue * result = malloc(sizeof(tValue));
    result->objectAttributeDesreferencing = malloc(sizeof(*(result->objectAttributeDesreferencing)));
    result->objectAttributeDesreferencing->objectAttribute = objectAttribute;
    result->objectAttributeDesreferencing->openSquareBracket = openSquareBracket;
    result->objectAttributeDesreferencing->index = integerExpression;
    result->objectAttributeDesreferencing->closeSquareBracket = closeSquareBracket;
    result->objectAttributeDesreferencing->pointInnerAtributte = malloc(sizeof(*(result->objectAttributeDesreferencing->pointInnerAtributte)));
    result->objectAttributeDesreferencing->pointInnerAtributte->point = point;
    result->objectAttributeDesreferencing->pointInnerAtributte->innerAttributeName = varname;
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
tGenericValueArray * genericValueArrayPlural(tGenericValue * value, tTokenNode * comma, tGenericValueArray * argumentValues1){
    tGenericValueArray * genericValueArray = malloc(sizeof(tGenericValueArray));
    genericValueArray->genericValue = value;
    genericValueArray->commaGenericValueArray = malloc(sizeof(*(genericValueArray->commaGenericValueArray)));
    genericValueArray->commaGenericValueArray->comma = comma;
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
/**
 * @section
 * char_value
 */
tCharValue * charValue(void * value){
    tCharValue * result = malloc(sizeof(tCharValue));
    result->varname = value;
    return result;
}
/**
 * @section
 * array_assignation
 */
tArrayAssignation * arrayAssignationValue(void * name, tTokenNode* openSquareBracket, tIntegerExpression* integerExpression, tTokenNode* closeSquareBracket, tTokenNode* assignation, tValue* value, tTokenNode* semicolon){
    tArrayAssignation * arrayAssignation = malloc(sizeof(tArrayAssignation));
    arrayAssignation->varname = name;
    arrayAssignation->openSquareBracket = openSquareBracket;
    arrayAssignation->index = integerExpression;
    arrayAssignation->closeSquareBracket = closeSquareBracket;
    arrayAssignation->assignation = assignation;
    arrayAssignation->valueSemicolon = malloc(sizeof(*(arrayAssignation->valueSemicolon)));
    arrayAssignation->valueSemicolon->value = value;
    arrayAssignation->valueSemicolon->semicolon = semicolon;
    return arrayAssignation;
}
tArrayAssignation * arrayAssignationSemicolon(void * name, tTokenNode* openSquareBracket, tIntegerExpression* integerExpression, tTokenNode* closeSquareBracket, tTokenNode* assignation, tInstantiation* instantiation){
    tArrayAssignation * arrayAssignation = malloc(sizeof(tArrayAssignation));
    arrayAssignation->varname = name;
    arrayAssignation->openSquareBracket = openSquareBracket;
    arrayAssignation->index = integerExpression;
    arrayAssignation->closeSquareBracket = closeSquareBracket;
    arrayAssignation->assignation = assignation;
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

tMethodCall * methodCall(tTokenNode* varname, tTokenNode* point,
                         tFunctionCall* functionCall){
    tMethodCall * newNode= malloc(sizeof(tMethodCall));
    newNode->varname=varname;
    newNode->point=point;
    newNode->functionCall=functionCall;
    return newNode;
}

////datatype

tDataType * dataType(tTokenNode* token){
    tDataType * newNode= malloc(sizeof(tDataType));
    newNode->type=token;
    return newNode;
}

////parameters

tParameters * basicParameters(tDataType* dataType, tTokenNode* varname){
    tParameters * newNode= malloc(sizeof(tParameters));
    newNode->datatype=dataType;
    newNode->paramName=varname;
    return newNode;
}

tParameters * multiBasicParameters(tDataType* dataType, tTokenNode* paramName,
                                   tTokenNode* comma, tParameters* parameters){
    tParameters * newNode= basicParameters(dataType, paramName);
    newNode->nextParameters= malloc(sizeof(tCommaNextParameters));
    newNode->nextParameters->comma=comma;
    newNode->nextParameters->nextParameters=parameters;
    return newNode;
}

tParameters * objectParameters( tTokenNode* objectType, tTokenNode* paramName){
    tParameters * newNode= malloc(sizeof(tParameters));
    newNode->objectTypeName=objectType;
    newNode->paramName=paramName;
    return newNode;
}

tParameters * multiObjectParameters( tTokenNode* objectType, tTokenNode* paramName,
                                     tTokenNode* comma, tParameters* parameters){
    tParameters * newNode= objectParameters(objectType,paramName);
    newNode->nextParameters= malloc(sizeof(tCommaNextParameters));
    newNode->nextParameters->comma=comma;
    newNode->nextParameters->nextParameters=parameters;
    return newNode;
}

tParameters * arrayParameters(tDataType* dataType, tTokenNode* paramName,
                              tTokenNode* openSquareBracket, tTokenNode* closeSquareBracket){
    tParameters * newNode= basicParameters(dataType, paramName);
    newNode->squareBrackets= malloc(sizeof(tEmptySquareBrackets));
    newNode->squareBrackets->closeSquareBracket=closeSquareBracket;
    newNode->squareBrackets->openSquareBracket=openSquareBracket;
    return newNode;
}

tParameters * multiArrayParameters(tDataType* dataType, tTokenNode* paramName,
                              tTokenNode* openSquareBracket, tTokenNode* closeSquareBracket,
                              tTokenNode* comma, tParameters* parameters){
    tParameters * newNode= arrayParameters(dataType, paramName, openSquareBracket, closeSquareBracket);
    newNode->nextParameters= malloc(sizeof(tCommaNextParameters));
    newNode->nextParameters->comma=comma;
    newNode->nextParameters->nextParameters=parameters;
    return newNode;
}

tParameters * objectArrayParameters(tTokenNode * objectType, tTokenNode* paramName,
                              tTokenNode* openSquareBracket, tTokenNode* closeSquareBracket){
    tParameters * newNode= objectParameters(objectType,paramName);
    newNode->squareBrackets= malloc(sizeof(tEmptySquareBrackets));
    newNode->squareBrackets->closeSquareBracket=closeSquareBracket;
    newNode->squareBrackets->openSquareBracket=openSquareBracket;
    return newNode;
}

tParameters * multiObjectArrayParameters(tTokenNode * objectType, tTokenNode* paramName,
                                    tTokenNode* openSquareBracket, tTokenNode* closeSquareBracket,
                                    tTokenNode* comma, tParameters* parameters) {
    tParameters * newNode= objectArrayParameters(objectType,paramName, openSquareBracket, closeSquareBracket);
    newNode->nextParameters= malloc(sizeof(tCommaNextParameters));
    newNode->nextParameters->comma=comma;
    newNode->nextParameters->nextParameters=parameters;
    return newNode;

}

/**
 * @section
 * main_function
 */
tMainFunction * mainFunctionRule(tTokenNode * integerType, tTokenNode * main, tTokenNode * openP, tParameters * parameters, tTokenNode * closeP, tTokenNode* openBrace, tProgramStatements* programStatements, tTokenNode* closeBrace){
    tMainFunction * function = malloc(sizeof(tFunction));
    function->integer = integerType;
    function->main = main;
    function->openParenthesis = openP;
    function->parameters = parameters;
    function->closeParenthesis = closeP;
    function->openBrace = openBrace;
    function->programStatements = programStatements;
    function->closeBrace = closeBrace;
    return function;
}


/**
 * @section
 * function
 */
tFunction * functionRuleWithType(void * type, tTokenNode * varname, tTokenNode* openP, tParameters * parameters, tTokenNode* closeP, tTokenNode* openBrace, tProgramStatements* programStatements, tTokenNode* closeBrace){
    tFunction * function = malloc(sizeof(tFunction));
    function->datatype = type;
    function->varname = varname;
    function->openP = openP;
    function->parameters = parameters;
    function->closeP = closeP;
    function->openBrace = openBrace;
    function->programStatements = programStatements;
    function->closeBrace = closeBrace;
    return function;
}
tFunction * functionRuleNoType(tTokenNode * varname, tTokenNode* openP, tParameters * parameters, tTokenNode* closeP, tTokenNode* openBrace, tProgramStatements* programStatements, tTokenNode* closeBrace){
    return functionRuleWithType(NULL, varname, openP, parameters, closeP, openBrace, programStatements, closeBrace);
}
////constructor
tConstructor * constructor(tTokenNode* constructor, tFunction* function){
    tConstructor  * newNode = malloc(sizeof(tConstructor));
    newNode->constructor=constructor;
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
tAttributes* attributes(tTokenNode* attributes, tTokenNode* openBrace,
                        tDeclarations* declarations, tTokenNode* closeBrace){
    tAttributes * newNode= malloc(sizeof(tAttributes));
    newNode->attributes=attributes;
    newNode->operBrace=openBrace;
    newNode->declarations=declarations;
    newNode->closeBrace=closeBrace;
    return newNode;
}

////comparison_operator
tComparisonOperator * comparisonOperator(tTokenNode* token){
    tComparisonOperator* newNode= malloc(sizeof(tComparisonOperator));
    switch (token->tokenId) {
        case EQUAL_OP:
            newNode->equalOp=token;
            break;
        case NOT_EQUAL_OP:
            newNode->notEqualOp=token;
            break;
        case LOWER_OP:
            newNode->lowerOp=token;
            break;
        case LOWEREQ_OP:
            newNode->lowerEqOp=token;
            break;
        case GREATER_OP:
            newNode->greaterOp=token;
            break;
        case GREATEREQ_OP:
            newNode->greaterEqOp=token;
            break;

    }

    return newNode;
}
////logical_operator
tLogicalOperator * logicalOperator(tTokenNode* token){
    tLogicalOperator * newNode= malloc(sizeof(tLogicalOperator));
    switch (token->tokenId) {
        case AND:
            newNode->andToken=token;
            break;
        case OR:
            newNode->orToken=token;
            break;
    }
    return newNode;
}
////comparation
tComparation * comparation(tValue* lValue, tComparisonOperator* comparisonOperator,
                           tValue* rValue){
    tComparation * newNode= malloc(sizeof(tComparation));
    newNode->lValue=lValue;
    newNode->comparisonOperator=comparisonOperator;
    newNode->rValue=rValue;
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
tCondition * condition(tTokenNode* openParenthesis, tConditionUnit* conditionUnit,
                       tTokenNode* closeParenthesis){
    tCondition * newNode= malloc(sizeof(tCondition));
    newNode->openP=openParenthesis;
    newNode->conditionUnit=conditionUnit;
    newNode->closeP=closeParenthesis;
    return newNode;
}

////clause

tClause * clause(tTokenNode* openBrace, tProgramStatements* programStatements,
                 tTokenNode* closeBrace){
    tClause * newNode= malloc(sizeof(tClause));
    newNode->openBrace=openBrace;
    newNode->programStatements=programStatements;
    newNode->closeBrace=closeBrace;
    return newNode;
}
////while_loop

tWhileLoop * whileLoop(tTokenNode* whileToken, tCondition* condition,
                       tClause* clause){
    tWhileLoop * newNode= malloc(sizeof(tWhileLoop));
    newNode->whileReserved=whileToken;
    newNode->conditionClause=condition;
    newNode->clause=clause;
    return newNode;
}
////if

tIf* If(tTokenNode* ifToken, tCondition* condition, tClause* clause){
    tIf * newNode = malloc(sizeof(tIf));
    newNode->ifReserved=ifToken;
    newNode->condition=condition;
    newNode->clause=clause;
    return newNode;
}

tIf* IfElse(tTokenNode* ifToken, tCondition* condition, tClause* ifClause,
            tTokenNode* elseToken, tClause* elseClause){
    tIf* newNode= If(ifToken, condition, ifClause);
    newNode->ifElseStatement= malloc(sizeof(tIfElseStatement));
    newNode->ifElseStatement->elseReserved=elseToken;
    newNode->ifElseStatement->clause=elseClause;
    return newNode;
}

/**
 * @section
 * argument_values
 */
tArgumentValues * argumentValuesSingle(tValue * value){
    tArgumentValues * argumentValues = malloc(sizeof(tArgumentValues));
    argumentValues->value = value;
    return argumentValues;
}
tArgumentValues * argumentValuesPlural(tValue * value, tTokenNode * comma, tArgumentValues * argumentValues1){
    tArgumentValues * argumentValues = malloc(sizeof(tArgumentValues));
    argumentValues->value = value;
    argumentValues->commaNextArgumentValue = malloc(sizeof(*(argumentValues->commaNextArgumentValue)));
    argumentValues->commaNextArgumentValue->comma = comma;
    argumentValues->commaNextArgumentValue->nextArgument = argumentValues1;
    return argumentValues;
}

/**
 * @section
 * program_unit_statements
 */
tProgramUnitStatements * programUnitStatements(void * unit){
    tProgramUnitStatements * programUnitStatements1 = malloc(sizeof(tProgramUnitStatements));
    programUnitStatements1->assignation = unit;
    return programUnitStatements1;
}
tProgramUnitStatements * programUnitStatementsIntegerExpression(tIntegerExpression * integerExpression, tTokenNode * semicolon){
    tProgramUnitStatements * programUnitStatements1 = malloc(sizeof(tProgramUnitStatements));
    programUnitStatements1->integerExpressionSemicolon = malloc(sizeof(*(programUnitStatements1->integerExpressionSemicolon)));
    programUnitStatements1->integerExpressionSemicolon->integerExpression = integerExpression;
    programUnitStatements1->integerExpressionSemicolon->semicolon = semicolon;
    return programUnitStatements1;
}

/**
 * @section
 * program_statements
 */
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
tArrayDesreferencing * arrayDesreferencing(tTokenNode * varname, tTokenNode* openSquareBracket, tIntegerExpression* integerExpression, tTokenNode * closeSquareBracket){
    tArrayDesreferencing * arrayDesreferencing1 = malloc(sizeof(tArrayDesreferencing));
    arrayDesreferencing1->varname = varname;
    arrayDesreferencing1->openSquareBracket = openSquareBracket;
    arrayDesreferencing1->integerExpression = integerExpression;
    arrayDesreferencing1->closeSquareBracket = closeSquareBracket;
    return arrayDesreferencing1;
}

/**
 * @section
 * return
 */
tReturn * returnRuleValue(tTokenNode * ret, void * value, tTokenNode * semicolon){
    tReturn * aReturn = malloc(sizeof(tReturn));
    aReturn->semicolon = semicolon;
    aReturn->returnToken = ret;
    aReturn->valueUnion.value = value;
    return aReturn;
}
tReturn * returnRuleNoValue(tTokenNode * ret, tTokenNode * semicolon){
    tReturn * aReturn = malloc(sizeof(tReturn));
    aReturn->semicolon = semicolon;
    aReturn->returnToken = ret;
    return aReturn;
}


/**
 * @section
 * integer_expression
 */
tIntegerExpression * integerExpressionCommon(tIntegerExpression * integerExpression1, tTokenNode * operator, tIntegerExpression * integerExpression2){
    tIntegerExpression * integerExpression = malloc(sizeof(tIntegerExpression));
    integerExpression->commonIntegerExpression = malloc(sizeof(*(integerExpression->commonIntegerExpression)));
    integerExpression->commonIntegerExpression->leftIntegerExpression = integerExpression1;
    integerExpression->commonIntegerExpression->operator = operator;
    integerExpression->commonIntegerExpression->rightIntegerExpression = integerExpression2;
    return integerExpression;
}
tIntegerExpression  * integerExpressionFactor(tFactor * factor){
    tIntegerExpression * integerExpression = malloc(sizeof(tIntegerExpression));
    integerExpression->factor = factor;
    return integerExpression;
}
tIntegerExpression * integerExpressionIncrementDecrement(tIntegerExpression * expression, tTokenNode* operator){
    tIntegerExpression * integerExpression = malloc(sizeof(tIntegerExpression));
    integerExpression->decrementIncrementIntegerExpression = malloc(sizeof(*(integerExpression->decrementIncrementIntegerExpression)));
    integerExpression->decrementIncrementIntegerExpression->leftIntegerExpression = expression;
    integerExpression->decrementIncrementIntegerExpression->operator = operator;
    return integerExpression;
}

tIntegerExpression * integerExpressionEnclosed(tTokenNode * openP, tIntegerExpression * expression, tTokenNode * closeP){
    tIntegerExpression * integerExpression = malloc(sizeof(tIntegerExpression));
    integerExpression->enclosedCommonIntegerExpression = malloc(sizeof(*(integerExpression->enclosedCommonIntegerExpression)));
    integerExpression->enclosedCommonIntegerExpression->openParenthesis = openP;
    integerExpression->enclosedCommonIntegerExpression->integerExpression = expression;
    integerExpression->enclosedCommonIntegerExpression->closeParenthesis = closeP;
}

/**
 * @section
 * factor
 */
 tFactor * factorObjectAttribute(tObjectAttribute * objectAttribute){
    tFactor * factor = malloc(sizeof(tFactor));
    factor->object_attribute = objectAttribute;
    return factor;
 }
tFactor * factorFunctionCall(tFunctionCall * functionCall){
    tFactor * factor = malloc(sizeof(tFactor));
    factor->function_call = functionCall;
    return factor;
}
tFactor * factorMethodCall(tMethodCall * methodCall){
    tFactor * factor = malloc(sizeof(tFactor));
    factor->method_call = methodCall;
    return factor;
}
tFactor * factorVarname(tTokenNode * varname){
    tFactor * factor = malloc(sizeof(tFactor));
    factor->varname = varname;
    return factor;
}
tFactor * factorArrayDesreferencing(tArrayDesreferencing * arrayDesreferencing){
    tFactor * factor = malloc(sizeof(tFactor));
    factor->array_desreferencing = arrayDesreferencing;
    return factor;
}
tFactor * factorSubInteger(tTokenNode * sub, tTokenNode * integer){
    tFactor * factor = malloc(sizeof(tFactor));
    tSubInteger * subInteger = malloc(sizeof(tSubInteger));
    subInteger->integer = integer;
    subInteger->sub = sub;
    factor->subInteger = subInteger;
    return factor;
}
tFactor * factorInteger(tTokenNode * integer){
    tFactor * factor = malloc(sizeof(tFactor));
    factor->integer = integer;
    return factor;
}

/**
 * @section
 * object_attribute
 */

tObjectAttribute * objectAttributeFromVarname(tTokenNode* object, tTokenNode * point, tTokenNode * attributeName){
    tObjectAttribute * objectAttribute = malloc(sizeof(tObjectAttribute));
    objectAttribute->varnameLeft = object;
    objectAttribute->point = point;
    objectAttribute->varnameRight = attributeName;
    return objectAttribute;
}

tObjectAttribute * objectAttributeFromObjectAttribute(tObjectAttribute * object, tTokenNode * point, tTokenNode * attributeName){
    tObjectAttribute * objectAttribute = malloc(sizeof(tObjectAttribute));
    objectAttribute->objectAttribute = object;
    objectAttribute->point = point;
    objectAttribute->varnameRight = attributeName;
    return objectAttribute;
}

tObjectAttribute * objectAttributeFromArrayDesreferencing(tArrayDesreferencing* object, tTokenNode * point, tTokenNode * attributeName){
    tObjectAttribute * objectAttribute = malloc(sizeof(tObjectAttribute));
    objectAttribute->arrayDesreferencing = object;
    objectAttribute->point = point;
    objectAttribute->varnameRight = attributeName;
    return objectAttribute;
}


/**
 * @section
 * function_call
 */

tFunctionCall * functionCall(tTokenNode* functionName, tTokenNode* openP, tArgumentValues* argumentValues, tTokenNode* closeP){
    tFunctionCall * functionCall = malloc(sizeof(tFunctionCall));
    functionCall->functionName = functionName;
    functionCall->openP = openP;
    functionCall->firstArgument = argumentValues;
    functionCall->closeP = closeP;
    return functionCall;
}

#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include <stdlib.h>
/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

/////program
tProgram *ProgramGrammarAction(tMainFunction * mainFunction) ;
tProgram *ProgramGrammarActionWithClassAndProg(tClass * Class,tProgram * programs);
/////class
tClass  * ClassGrammarAction(tTokenNode * class, tTokenNode * varname, tTokenNode * openBrace ,tClassIn * classIn , tTokenNode * closeBrace);
tClass * ClassGrammarActionWithHerency(tTokenNode * class, tTokenNode * fatherName,tTokenNode * extends,tTokenNode  *className , tTokenNode * openBrace ,tClassIn * classIn , tTokenNode * closeBrace);

////class_in
tClassIn  * classInGrammarAction(tAttributes * attributes , tConstructor * constructor , tMethods * methods);

////instantiation
tInstantiation * instantiationGrammarAction(tTokenNode *  new , tFunctionCall * functionCall , tTokenNode * semicolon )

////declaration
tDeclaration  * charDeclarationGrammarAction(tCharDeclaration * charDeclaration );
tDeclaration * integerDeclarationGrammarAction( struct tIntegerDeclaration * tIntegerDeclaration );
tDeclaration * charArrayDeclarationGrammarAction( struct tCharArrayDeclaration * tCharArrayDeclaration);
tDeclaration * integerArrayDeclarationGrammarAction( struct tIntegerArrayDeclaration * tIntegerArrayDeclaration);
tDeclaration * integerAssignationDeclarationGrammarAction( struct tIntegerAssignationDeclaration * tIntegerAssignationDeclaration);
tDeclaration * charAssignationDeclarationGrammarAction( struct tCharAssignationDeclaration * tCharAssignationDeclaration);
tDeclaration * integerArrayAssignationDeclaration( tIntegerArrayAssignationDeclaration * IntegerArrayAssignationDeclaration) ;
tDeclaration * charArrayAssignationDeclarationGrammarAction(  tCharArrayAssignationDeclaration * CharArrayAssignationDeclaration);
tDeclaration * declarationWithObjectDataTypeGrammarAction(  tDeclarationWithObjectDataType * declarationWithObjectDataType);

////integer_assignation_declaration
tIntegerAssignationDeclaration * integerAssignationDeclarationRuleGrammarAction(tTokenNode * intReserved , tTokenNode * varname , tTokenNode * assignation , tIntegerExpression * integerExpression , tTokenNode * semicolon);

///char_assignation_declaration
tCharAssignationDeclaration  * charAssignationDeclarationRuleGrammarAction (tTokenNode * character , tTokenNode * varname , tTokenNode * assignation , tCharValue * charValue , tTokenNode * semicolon);

////integer_array_assignation_declaration
tIntegerArrayAssignationDeclaration * integerArrayAssignationDeclarationGrammarAction(tTokenNode * intReserved , tTokenNode * varname ,tTokenNode * openSquareBracket,tTokenNode * closeSquareBracket, tTokenNode * assignation, tTokenNode * openBrace , tIntegerArray * integerArray , tTokenNode * closeBrace ,tTokenNode * semicolon );

////char_array_assignation_declaration
tCharArrayAssignationDeclaration * charArrayAssignationDeclarationRuleGrammarAction(tTokenNode * charReserved , tTokenNode * varname , tTokenNode * openSquareBracket,tTokenNode * closeSquareBracket,tTokenNode * assignation , tTokenNode * openBrace , tCharacterArray * characterArray , tTokenNode * closeBrace , tTokenNode * semicolon );

////integer_array
tIntegerArray  * tIntegerArrayGrammarAction(tIntegerExpression * integerExpression );
tIntegerArray  * tIntegerArraywithCommaGrammarAction(tIntegerExpression * integerExpression ,tTokenNode * comma , tIntegerArray * integerArray);

////character_array
tCharacterArray  * characterArrayGrammarAction(tCharValue * charValue );

///integer_declaration
tIntDeclaration * integerDeclarationRuleGrammarAction(tTokenNode * intReserved , tTokenNode * varname , tTokenNode * semicolon );

////char_declaration
tCharDeclaration * charDeclarationRuleGrammarAction(tTokenNode * charReserved , tTokenNode * varname , tTokenNode * semicolon );

////integer_array_declaration
tIntegerArrayDeclaration * integerArrayDeclarationRuleGrammarAction(tTokenNode * intReserved, tTokenNode * varname, tTokenNode * openSquareBracket , tIntegerExpression  * integerExpression,tTokenNode * closeSquareBracket,  tTokenNode * semicolon);

////char_array_declaration
tCharArrayDeclaration * charArrayDeclarationRuleGrammarAction(tTokenNode * charReserved , tTokenNode * varname , tTokenNode * openSquareBracket, tIntegerExpression  * integerExpression , tTokenNode * closeSquareBracket, tTokenNode * semicolon);
tCharArrayDeclaration * charArrayDeclarationRule2GrammarAction(tTokenNode * charReserved , tTokenNode * varname , tTokenNode * openSquareBracket, tTokenNode * closeSquareBracket, tTokenNode * semicolon);

////assignation
tAssignation  * assignationGrammarAction(tTokenNode * varname, tTokenNode * assignation , tValue * value , tTokenNode * semicolon);
tAssignation  * assignationRule2GrammarAction(tTokenNode * varname, tTokenNode * assignation , tInstantiation * instantiation);

tTokenNode * tokenGrammarActionWithChar(const int tokenId,char character);
tTokenNode * tokenGrammarActionWithInt(const int tokenId,int integer);
tTokenNode * tokenGrammarActionWitString(const int tokenId,char * string);

/**
 * @section
 * generic_value_array
 */
tGenericValueArray * genericValueArraySingle(tGenericValue * value);
tGenericValueArray * genericValueArrayPlural(tGenericValue * value, tTokenNode * comma, tGenericValueArray * argumentValues1);

/**
 * @section
 * char_value
 */
tCharValue * charValue(void * value);

/**
 * @section
 * array_assignation
 */
tArrayAssignation * arrayAssignationSemicolon(void * name, tTokenNode* openSquareBracket, tIntegerExpression* integerExpression, tTokenNode* closeSquareBracket, tTokenNode* assignation, tInstantiation* instantiation);
tArrayAssignation * arrayAssignationValue(void * name, tTokenNode* openSquareBracket, tIntegerExpression* integerExpression, tTokenNode* closeSquareBracket, tTokenNode* assignation, tValue* value, tTokenNode* semicolon);

/**
 * @section
 * main_function
 */
tMainFunction * mainFunctionRule(tTokenNode * integerType, tTokenNode * main, tTokenNode * openP, tParameters * parameters, tTokenNode * closeP, tTokenNode* openBrace, tProgramStatements* programStatements, tTokenNode* closeBrace);

/**
 * @section
 * function
 */
tFunction * functionRuleWithType(void * type, tTokenNode * varname, tTokenNode* openP, tParameters * parameters, tTokenNode* closeP, tTokenNode* openBrace, tProgramStatements* programStatements, tTokenNode* closeBrace);
tFunction * functionRuleNoType(tTokenNode * varname, tTokenNode* openP, tParameters * parameters, tTokenNode* closeP, tTokenNode* openBrace, tProgramStatements* programStatements, tTokenNode* closeBrace);

/**
 * @section
 * argument_values
 */
tArgumentValues * argumentValuesSingle(tValue * value);
tArgumentValues * argumentValuesPlural(tValue * value, tTokenNode * comma, tArgumentValues * argumentValues1);

/**
 * @section
 * program_unit_statements
 */
tProgramUnitStatements * programUnitStatements(void * unit);
tProgramUnitStatements * programUnitStatementsIntegerExpression(tIntegerExpression * integerExpression, tTokenNode * semicolon);

/**
 * @section
 * program_statements
 */
tProgramStatements * programStatementsRule(tProgramUnitStatements * programUnitStatements, tProgramStatements * programStatements);

/**
 * @section
 * array_desreferencing
 */
tArrayDesreferencing * arrayDesreferencing(tTokenNode * varname, tTokenNode* openSquareBracket, tIntegerExpression* integerExpression, tTokenNode * closeSquareBracket);

/**
 * @section
 * return
 */
tReturn * returnRuleValue(tTokenNode * ret, void * value, tTokenNode * semicolon);
tReturn * returnRuleNoValue(tTokenNode * ret, tTokenNode * semicolon);


/**
 * @section
 * integer_expression
 */
tIntegerExpression * integerExpressionCommon(tIntegerExpression * integerExpression1, tTokenNode * operator, tIntegerExpression * integerExpression2);
tIntegerExpression  * integerExpressionFactor(tFactor * factor);
tIntegerExpression * integerExpressionIncrementDecrement(tIntegerExpression * expression, tTokenNode* operator);
tIntegerExpression * integerExpressionEnclosed(tTokenNode * openP, tIntegerExpression * expression, tTokenNode * closeP);

/**
 * @section
 * factor
 */
tFactor * factorObjectAttribute(tObjectAttribute * objectAttribute);
tFactor * factorFunctionCall(tFunctionCall * functionCall);
tFactor * factorMethodCall(tMethodCall * methodCall);
tFactor * factorVarname(tTokenNode * varname);
tFactor * factorArrayDesreferencing(tArrayDesreferencing * arrayDesreferencing);
tFactor * factorSubInteger(tTokenNode * sub, tTokenNode * integer);
tFactor * factorInteger(tTokenNode * integer);

/**
 * @section
 * object_attribute
 */
tObjectAttribute * objectAttributeFromVarname(tTokenNode* object, tTokenNode * point, tTokenNode * attributeName);
tObjectAttribute * objectAttributeFromObjectAttribute(tObjectAttribute * object, tTokenNode * point, tTokenNode * attributeName);
tObjectAttribute * objectAttributeFromArrayDesreferencing(tArrayDesreferencing* object, tTokenNode * point, tTokenNode * attributeName);


/**
 * @section
 * function_call
 */
tFunctionCall * functionCall(tTokenNode* functionName, tTokenNode* openP, tArgumentValues* argumentValues, tTokenNode* closeP);

#endif

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

/**
 * Implementación de "bison-grammar.h".
 */

void yyerror(const char * string);


tTokenNode * varnameNode(char * varname);

tTokenNode * integerNode(int intValue);



tTokenNode * charNode(char character);

tTokenNode * tokenNode(int token);



////program
tProgram * ProgramGrammarActionWithMain( tMainFunction * mainFunction);

tProgram  *  ProgramGrammarActionWithClassAndProg(tClass * class , tProgram * program );
////class
//
tClass  * ClassGrammarAction(int class, char * varname, int openBrace ,tClassIn * classIn , int closeBrace);

//
tClass * ClassGrammarActionWithHerency(int class, char * fatherName,int extends,char * className , int openBrace ,tClassIn * classIn , int closeBrace);

////class_in
tClassIn  * classInGrammarAction(tAttributes * attributes , tConstructor * constructor , tMethods * methods);

////instantiation
//
tInstantiation * instantiationGrammarAction(int  new , tFunctionCall * functionCall , int semicolon );

////declaration
tDeclaration  * charDeclarationGrammarAction(tCharDeclaration * charDeclaration );

tDeclaration * integerDeclarationGrammarAction( struct tIntDeclaration * tIntegerDeclaration );

tDeclaration * charArrayDeclarationGrammarAction( struct tCharArrayDeclaration * tCharArrayDeclaration);

tDeclaration * integerArrayDeclarationGrammarAction( struct tIntegerArrayDeclaration * tIntegerArrayDeclaration);

tDeclaration * integerAssignationDeclarationGrammarAction( struct tIntegerAssignationDeclaration * tIntegerAssignationDeclaration);

tDeclaration * charAssignationDeclarationGrammarAction( struct tCharAssignationDeclaration * tCharAssignationDeclaration);

tDeclaration * integerArrayAssignationDeclaration( tIntegerArrayAssignationDeclaration * IntegerArrayAssignationDeclaration);

tDeclaration * charArrayAssignationDeclarationGrammarAction(  tCharArrayAssignationDeclaration * CharArrayAssignationDeclaration);

//
tDeclaration * declarationWithObjectDataTypeGrammarActionBasic(char* name, char* datatype, int semicolon);
//
tDeclaration * declarationWithObjectDataTypeGrammarActionInstantiation(char* name, char* datatype, int assignation, tInstantiation* instantiation);
tDeclaration * declarationWithObjectDataTypeGrammarActionArrayNoSize(char * name, char * datatype, int openSQ, int closeSQ, int semicolon);

//
tDeclaration * declarationWithObjectDataTypeGrammarActionArrayWithSize(char* name, char* datatype, int openSQ, tIntegerExpression* integerExpression, int closeSQ, int semicolon);

////integer_assignation_declaration
tIntegerAssignationDeclaration * integerAssignationDeclarationRuleGrammarAction(int intReserved , char * varname , int assignation , tIntegerExpression * integerExpression , int semicolon);

////char_assignation_declaration
tCharAssignationDeclaration  * charAssignationDeclarationRuleGrammarAction (int character , char * varname , int assignation , tCharValue * charValue , int semicolon);
////integer_array_assignation_declaration
tIntegerArrayAssignationDeclaration * integerArrayAssignationDeclarationGrammarAction(int intReserved , char * varname ,int openSquareBracket,int closeSquareBracket, int assignation, int openBrace , tIntegerArray * integerArray , int closeBrace ,int semicolon );
////char_array_assignation_declaration
//
tCharArrayAssignationDeclaration * charArrayAssignationDeclarationRuleGrammarAction(int charReserved , char * varname , int openSquareBracket,int closeSquareBracket,int assignation , int openBrace , tCharacterArray * characterArray , int closeBrace , int semicolon );
tCharArrayAssignationDeclaration  * charArrayAssignationDeclarationRule2GrammarAction(int charReserved , char * varname , int openSquareBracket,int closeSquareBracket,int assignation , char* string, int semicolon);

////integer_array
tIntegerArray  * tIntegerArrayGrammarAction(tIntegerExpression * integerExpression );

//
tIntegerArray  * tIntegerArrayWithCommaGrammarAction(tIntegerExpression * integerExpression ,int comma , tIntegerArray * integerArray);
////character_array
tCharacterArray  * characterArrayGrammarAction(tCharValue * charValue );

tCharacterArray  * characterArrayRule2GrammarAction(tCharValue * charValue ,int comma , tCharacterArray * characterArray );


////integer_declaration
tIntDeclaration * integerDeclarationRuleGrammarAction(int intReserved , char * varname , int semicolon );

////char_declaration
tCharDeclaration * charDeclarationRuleGrammarAction(int charReserved , char * varname , int semicolon );
////integer_array_declaration
tIntegerArrayDeclaration * integerArrayDeclarationRuleGrammarAction(int intReserved, char * varname, int openSquareBracket , tIntegerExpression  * integerExpression,int closeSquareBracket,  int semicolon);

////char_array_declaration
tCharArrayDeclaration * charArrayDeclarationRuleGrammarAction(int charReserved , char * varname , int openSquareBracket, tIntegerExpression  * integerExpression , int closeSquareBracket, int semicolon);

tCharArrayDeclaration * charArrayDeclarationRule2GrammarAction(int charReserved , char * varname , int openSquareBracket, int closeSquareBracket, int semicolon);
////assignation
tAssignation  * assignationGrammarAction(char * varname, int assignation , tValue * value , int semicolon);


tAssignation  * assignationRule2GrammarAction(char * varname, int assignation , tInstantiation * instantiation);

tAssignation  * assignationRule3GrammarAction(char * varname,int openSquareBracket, int closeSquareBracket, int assignation, int openBrace , tGenericValueArray * genericValueArray  ,  int closeBrace , int semicolon );

tAssignation  * assignationRule4GrammarAction(char * varname , int openSquareBracket, int closeSquareBracket, int assignation , char* string , int semicolon);



tAssignation  * assignationRule5GrammarAction(tArrayAssignation* arrayAssignation);


tAssignation  * assignationRule7GrammarAction(tObjectAttribute* objectAttribute, int assignation,
                                              tInstantiation* instantiation);

tAssignation* assignationRule8GrammarAction(tObjectAttribute* objectAttribute, int openSquareBracket, int closeSquareBracket,
                                            int assignation, int openBrace, tGenericValueArray * genericValueArray ,
                                            int closeBrace, int semicolon);

tAssignation  * assignationRule9GrammarAction(tObjectAttribute* objectAttribute, int openSquareBracket, int closeSquareBracket,  int assignation, char* string, int semicolon);
/**
 * @section
 * value
 */
tValue * valueSingle(void * value);
tValue * valueSingleCharacter(char * value);
tValue * valueSingleString(char value);
tValue * valueObjectAttributeDesreferencing(tObjectAttribute* objectAttribute, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket);
tValue * valueObjectAttributeDesreferencingAttribute(tObjectAttribute* objectAttribute, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int point, char * varname);

/**
 * @section
 * generic_value_array
 */
tGenericValueArray * genericValueArraySingle(tGenericValue * value);
tGenericValueArray * genericValueArrayPlural(tGenericValue * value, int comma, tGenericValueArray * argumentValues1);

/**
 * @section
 * generic_value
 */
tGenericValue * genericValue(void * value);
tGenericValue * genericValueCharacter(char value);
tGenericValue * genericValueInteger(int value);
tGenericValue * genericValueVarname(char * value);
/**
 * @section
 * char_value
 */
tCharValue * charValue(void * value);
tCharValue * charValueCharacter(char value);
tCharValue * charValueVarname(char * value);
/**
 * @section
 * array_assignation
 */
tArrayAssignation * arrayAssignationValueA(char * name, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int assignation, tValue* value, int semicolon);
tArrayAssignation * arrayAssignationValueB(tObjectAttribute * name, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int assignation, tValue* value, int semicolon);
tArrayAssignation * arrayAssignationSemicolonA(char * name, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int assignation, tInstantiation* instantiation);
tArrayAssignation * arrayAssignationSemicolonB(tObjectAttribute * name, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket, int assignation, tInstantiation* instantiation);

////methods

tMethods * methods(tFunction* function, tMethods* methods);

////method_call

tMethodCall * methodCall(char * varname, int point,
                         tFunctionCall* functionCall);

////datatype
tDataType * dataType(int token);

////parameters

tParameters * basicParameters(tDataType* dataType, char * varname);
//
tParameters * multiBasicParameters(tDataType* dataType, char* paramName,
                                   int comma, tParameters* parameters);

tParameters * objectParameters( char * objectType, char * paramName);

tParameters * multiObjectParameters( char* objectType, char* paramName,
                                     int comma, tParameters* parameters);

tParameters * arrayParameters(tDataType* dataType, char * paramName,
                              int openSquareBracket, int closeSquareBracket);

tParameters * multiArrayParameters(tDataType* dataType, int paramName,
                                   int openSquareBracket, int closeSquareBracket,
                                   int comma, tParameters* parameters);

tParameters * objectArrayParameters(int objectType, int paramName,
                                    int openSquareBracket, int closeSquareBracket);

tParameters * multiObjectArrayParameters(int objectType, int paramName,
                                         int openSquareBracket, int closeSquareBracket,
                                         int comma, tParameters* parameters) ;

/**
 * @section
 * main_function
 */
tMainFunction * mainFunctionRule(int integerType, int main, int openP, tParameters * parameters, int closeP, int openBrace, tProgramStatements* programStatements, int closeBrace);


/**
 * @section
 * function
 */
tFunction * functionRuleWithType(void * type, char * varname, int openP, tParameters * parameters, int closeP, int openBrace, tProgramStatements* programStatements, int closeBrace);
tFunction * functionRuleNoType(char * varname, int openP, tParameters * parameters, int closeP, int openBrace, tProgramStatements* programStatements, int closeBrace);
////constructor
tConstructor * constructor(int constructor, tFunction* function);
////declarations
tDeclarations* declarations(tDeclaration * declaration, tDeclarations* declarations);
////attributes
tAttributes* attributes(int attributes, int openBrace,
                        tDeclarations* declarations, int closeBrace);

////comparison_operator
tComparisonOperator * comparisonOperator(int token);
//
////logical_operator
tLogicalOperator * logicalOperator(int tokenId);
////comparation
tComparation * comparation(tValue* lValue, tComparisonOperator* comparisonOperator,
                           tValue* rValue);
////condition_unit
tConditionUnit * simpleConditionUnit(tCondition* condition);

tConditionUnit * conditionUnitValOpVal(tValue* lValue, struct tLogicalOperator* logicalOperator,
                                       tValue* rValue);

tConditionUnit * conditionUnitCompOpCond(tComparation* comparation,tLogicalOperator* logicalOperator,
                                         tConditionUnit* conditionUnit);

tConditionUnit * conditionUnitComparation(tComparation* comparation);
////condition
tCondition * condition(int openParenthesis, tConditionUnit* conditionUnit,
                       int closeParenthesis);

////clause
//
tClause * clause(int openBrace, tProgramStatements* programStatements,
                 int closeBrace);
////while_loop
//
tWhileLoop * whileLoop(int whileToken, tCondition* condition,
                       tClause* clause);
////if
//
tIf* If(int ifToken, struct tCondition* condition, tClause* clause);
//
tIf* IfElse(int ifToken, struct tCondition* condition, tClause* ifClause, int elseToken, tClause* elseClause);

/**
 * @section
 * argument_values
 */
//
tArgumentValues * argumentValuesSingle(tValue * value);
//
tArgumentValues * argumentValuesPlural(tValue * value, int comma, tArgumentValues * argumentValues1);

/**
 * @section
 * program_unit_statements
 */
//
tProgramUnitStatements * programUnitStatements(void * unit);
//
tProgramUnitStatements * programUnitStatementsIntegerExpression(tIntegerExpression * integerExpression, int semicolon);

/**
 * @section
 * program_statements
 */
//
tProgramStatements * programStatementsRule(tProgramUnitStatements * programUnitStatements, tProgramStatements * programStatements);

/**
 * @section
 * array_desreferencing
 */
//
tArrayDesreferencing * arrayDesreferencing(char * varname, int openSquareBracket, tIntegerExpression* integerExpression, int closeSquareBracket);

/**
 * @section
 * return
 */
//
tReturn * returnRuleValue(int ret, void * value, int semicolon);
//
tReturn * returnRuleNoValue(int ret, int semicolon);


/**
 * @section
 * integer_expression
 */
//
tIntegerExpression * integerExpressionCommon(tIntegerExpression * integerExpression1, int operator, tIntegerExpression * integerExpression2);

//
tIntegerExpression  * integerExpressionFactor(tFactor * factor);
//
tIntegerExpression * integerExpressionIncrementDecrement(tIntegerExpression * expression, int operator);
//
tIntegerExpression * integerExpressionEnclosed(int openP, tIntegerExpression * expression, int closeP);

/**
 * @section
 * factor
 */
//
tFactor * factorObjectAttribute(tObjectAttribute * objectAttribute);
//
tFactor * factorFunctionCall(tFunctionCall * functionCall);
//
tFactor * factorMethodCall(tMethodCall * methodCall);
//
tFactor * factorVarname(char * varname);
//
tFactor * factorArrayDesreferencing(tArrayDesreferencing * arrayDesreferencing);
//
tFactor * factorSubInteger(int sub, int integer);
//
tFactor * factorInteger(int integer);

/**
 * @section
 * object_attribute
 */
//
tObjectAttribute * objectAttributeFromVarname(char * object, int point, char * attributeName);
//
tObjectAttribute * objectAttributeFromObjectAttribute(tObjectAttribute * object, int point, char * attributeName);
//
tObjectAttribute * objectAttributeFromArrayDesreferencing(tArrayDesreferencing* object, int point, char * attributeName);


/**
 * @section
 * function_call
 */
//
tFunctionCall * functionCall(char * functionName, int openP, tArgumentValues* argumentValues, int closeP);


#endif

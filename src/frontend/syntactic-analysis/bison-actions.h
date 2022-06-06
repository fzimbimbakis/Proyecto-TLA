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
tInstantiation * instantiationGrammarAction(tTokenNode *  new , tFunctionCall * functionCall , tTokenNode * semicolon );

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
        tAssignation  * assignationRule3GrammarAction(tTokenNode * varname,tTokenNode * openSquareBracket, tTokenNode * closeSquareBracket, tTokenNode *assignation, tTokenNode * openBrace , tGenericValueArray * genericValueArray  ,  tTokenNode * closeBrace , tTokenNode * semicolon );
        tAssignation  * assignationRule4GrammarAction(tTokenNode * varname , tTokenNode * openSquareBracket, tTokenNode * closeSquareBracket, tTokenNode * assignation , tTokenNode * string , tTokenNode * semicolon);
tAssignation  * assignationRule5GrammarAction(tArrayAssignation* arrayAssignation);
tAssignation  * assignationRule6GrammarAction(tObjectAttribute* objectAttribute, tTokenNode* assignation,tValue* value, tTokenNode* semicolon);
tAssignation  * assignationRule7GrammarAction(tObjectAttribute* objectAttribute, tTokenNode* assignation,tInstantiation* instantiation);
tAssignation * assignationRule8GrammarAction(tObjectAttribute* objectAttribute, tTokenNode* openSquareBracket, tTokenNode* closeSquareBracket,tTokenNode * assignation, tTokenNode* openBrace, tGenericValueArray * genericValueArray ,tTokenNode* closeBrace, tTokenNode* semicolon);
tAssignation  * assignationRule9GrammarAction(tObjectAttribute* objectAttribute, tTokenNode* openSquareBracket, tTokenNode* closeSquareBracket,  tTokenNode * assignation, tTokenNode* string, tTokenNode* semicolon);

;
tTokenNode * tokenGrammarActionWithChar(const int tokenId,char character);
tTokenNode * tokenGrammarActionWithInt(const int tokenId,int integer);
tTokenNode * tokenGrammarActionWitString(const int tokenId,char * string);


/**
 * @section
 * value
 */
tValue * valueSingle(void * value);
tValue * valueObjectAttributeDesreferencing(tObjectAttribute* objectAttribute, tTokenNode* openSquareBracket, tIntegerExpression* integerExpression, tTokenNode* closeSquareBracket);
tValue * valueObjectAttributeDesreferencingAttribute(tObjectAttribute* objectAttribute, tTokenNode* openSquareBracket, tIntegerExpression* integerExpression, tTokenNode* closeSquareBracket, tTokenNode* point, tTokenNode* varname);

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


////methods
tMethods * methods(tFunction* function, tMethods* methods);

////method_call
tMethodCall * methodCall(tTokenNode* varname, tTokenNode* point,tFunctionCall* functionCall);

////datatype
tDataType * dataType(tTokenNode* token);

////parameters
tParameters * basicParameters(tDataType* dataType, tTokenNode* varname);
tParameters * multiBasicParameters(tDataType* dataType, tTokenNode* paramName,
                                   tTokenNode* comma, tParameters* parameters);
tParameters * objectParameters( tTokenNode* objectType, tTokenNode* paramName);
tParameters * multiObjectParameters( tTokenNode* objectType, tTokenNode* paramName,
                                     tTokenNode* comma, tParameters* parameters);
tParameters * arrayParameters(tDataType* dataType, tTokenNode* paramName,
                              tTokenNode* openSquareBracket, tTokenNode* closeSquareBracket);
tParameters * multiArrayParameters(tDataType* dataType, tTokenNode* paramName,
                                   tTokenNode* openSquareBracket, tTokenNode* closeSquareBracket,
                                   tTokenNode* comma, tParameters* parameters);
tParameters * objectArrayParameters(tTokenNode * objectType, tTokenNode* paramName,
                                    tTokenNode* openSquareBracket, tTokenNode* closeSquareBracket);
tParameters * multiObjectArrayParameters(tTokenNode * objectType, tTokenNode* paramName,
                                         tTokenNode* openSquareBracket, tTokenNode* closeSquareBracket,
                                         tTokenNode* comma, tParameters* parameters);

////declarations
tDeclarations* declarations(tDeclaration * declaration, tDeclarations* declarations);

////attributes
tAttributes* attributes(tTokenNode* attributes, tTokenNode* openBrace,
                        tDeclarations* declarations, tTokenNode* closeBrace);

////comparison_operator
tComparisonOperator * comparisonOperator(tTokenNode* token);

////logical_operator
tLogicalOperator * logicalOperator(tTokenNode* token);

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
tCondition * condition(tTokenNode* openParenthesis, tConditionUnit* conditionUnit,
                       tTokenNode* closeParenthesis);

////clause
tClause * clause(tTokenNode* openBrace, tProgramStatements* programStatements,
                 tTokenNode* closeBrace);

////while_loop
tWhileLoop * whileLoop(tTokenNode* whileToken, tCondition* condition,
                       tClause* clause);

////if
tIf* If(tTokenNode* ifToken, tCondition* condition, tClause* clause);
tIf* IfElse(tTokenNode* ifToken, tCondition* condition, tClause* ifClause,
            tTokenNode* elseToken, tClause* elseClause);

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

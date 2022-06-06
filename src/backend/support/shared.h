#ifndef SHARED_HEADER
#define SHARED_HEADER

#include <stdio.h>
#include "../../frontend/lexical-analysis/flex-actions.h"
#include "../../frontend/syntactic-analysis/bison-parser.h"

// Descriptor del archivo de entrada que utiliza Bison.
extern FILE * yyin;

// Descriptor del archivo de salida que utiliza Bison.
extern FILE * yyout;

// Variable global que contiene el número escaneado.
extern int yylval;

// Variable global que contiene el número de la línea analizada.
extern int yylineno;

// Token actual en el tope de la pila del analizador Bison.
extern char * yytext;

// Función global de manejo de errores en Bison.
extern void yyerror(const char * string);

// Función global del analizador léxico Flex.
extern int yylex(void);

// Función global del analizador sintáctico Bison.
extern int yyparse(void);

// Emular tipo "boolean".
typedef enum {
	false = 0,
	true = 1
} boolean;

// Estado global de toda la aplicación.
typedef struct {

	// Indica si la compilación tuvo problemas hasta el momento:
	boolean succeed;

	// Indica el resultado de la compilación:
	int result;

	// Agregar una pila para almacenar tokens/nodos.
	// Agregar un nodo hacia la raíz del árbol de sintaxis abstracta.
	// Agregar una tabla de símbolos.
	// ...

} CompilerState;

// El estado se define e inicializa en el archivo "main.c":
extern CompilerState state;


/**
 * @node Token nodes (Tree leaves)
 *
 * Every possible token
 */
typedef struct tTokenNode{
    unsigned tokenId;
    union {
        char * varname;
        int integerValue;
        char charValue;
    }associated_value;
} tTokenNode;

/**
 * @node Data types
 *
 * CHAR
 * INT
 */
typedef struct tDataType{
    struct tTokenNode * type;
}tDataType;

///**
// * @node Basic Variable Declaration
// *
// * type varname;
// *
// */
//typedef struct tVarDeclaration{
//    struct tDataType* dataType;
//    struct tTokenNode * varname;
//    struct tTokenNode * semicolon;
//} VarDeclaration;

/**
 * @node Factor
 *
 * Object.attribute
 * functionCall
 * methodCall
 * variable
 * array[ index ]
 * -integer
 * integer
 *
 * @note Uses @subnode tSubInteger
 */
typedef struct tFactor{
    union{
        struct tObjectAttribute * object_attribute;
        struct tFunctionCall * function_call;
        struct tMethodCall * method_call;
        struct tTokenNode *  varname;
        struct tArrayDesreferencing * array_desreferencing;
        struct tSubInteger * subInteger;
        struct tTokenNode * integer;
    };
} tFactor;


/**
 * @node Value
 *
 * string
 * character
 * integer_expression
 * Object.attribute[ index ]
 * Object.attribute[ index ].innerAttribute
 *
 * @note Uses @subnode tObjectAttributeDesreferencing
 */
typedef struct tValue{
    union {
        struct tTokenNode * character;
        struct tTokenNode * string;
        struct tIntegerExpression * integerExpression;
        struct tObjectAttributeDesreferencing * objectAttributeDesreferencing;
    };
}tValue;

/**
 * @subnode Object Attribute Desreferencing
 *
 * Object.attribute[ index ]
 * Object.attribute[ index ].innerAttribute
 *
 * @note Used in @node tValue
 * @note Uses @subnode tInnerAttribute
 */
typedef struct tObjectAttributeDesreferencing{
    struct tObjectAttribute * objectAttribute;
    struct tTokenNode * openSquareBracket;
    struct tIntegerExpression * index;
    struct tTokenNode * closeSquareBracket;
    struct tInnerAttribute * pointInnerAtributte;
}tObjectAttributeDesreferencing;

/**
 * @subnode Getting inner atribute
 *
 * ".InnerAttributeName"
 *
 * @note Used in @subnode tObjectAttributeDesreferencing
 */
typedef struct tInnerAttribute{
    tTokenNode * point;
    tTokenNode * innerAttributeName;
}tInnerAttribute;

/**
 * @node Argument Values
 *
 * Value, NextArgument
 *
 * @note Uses @subnode tCommaNextArgumentValue
 */
typedef struct tArgumentValues{
    struct tValue * value;
    struct tCommaNextArgumentValue * commaNextArgumentValue;
}tArgumentValues;
/**
 * @subnode Comma Argument Values
 *
 * ", NextArgument"
 *
 * @note Used in @node tArgumentValues
 */
typedef struct tCommaNextArgumentValue{
    struct tTokenNode * comma;
    struct tArgumentValues * nextArgument; //// Nullable
}tCommaNextArgumentValue;

/**
 * @node Function Call
 *
 * functionName( tArgument )
 * functionName( )
 */
typedef struct tFunctionCall{
    struct tTokenNode * functionName;
    struct tTokenNode * openP;
    struct tArgumentValues * firstArgument;
    struct tTokenNode * closeP;
}tFunctionCall;

/**
 * @node Program
 *
 * classes main
 * main
 *
 * @note Uses @subnode tClassesAndMain
 */
typedef struct tProgram{
    union {
        struct tMainFunction* mainFunction;
        struct tClassesAndMain* classesAndMain;
    };
}tProgram;



/**
 * @node Class
 *
 * class Name { class_in }
 * class Name extends ExtendedClassName { class_in }
 *
 * @note Uses @subnode tExtendsName
 */
typedef struct tClass{
    struct tTokenNode* class;
    struct tTokenNode* varname;
    struct tExtendsName* extendsName;
    struct tTokenNode* openBrace;
    struct tClassIn* classIn;
    struct tTokenNode* closeBrace;
}tClass;


/**
 * @node Class sections
 *
 * attributes constructor methods
 *
 */
typedef struct tClassIn{
    struct tAttributes* attributes;
    struct tConstructor* constructor;
    struct tMethods* methods;
}tClassIn;

/**
 * @node Char Array
 *
 * character
 * character, char_array
 *
 * @note Uses @subnode tCommaCharacterArray
 */
typedef struct tCharacterArray{
    struct tCharValue* charValue;
    struct tCommaCharacterArray* commaCharacterArray;   //// Nullable
}tCharacterArray;



/**
 * @node Integer Array
 *
 * integer_expression
 * integer_expression, integer_array
 *
 * @note Uses @subnode tCommaIntegerArray
 */
typedef struct tIntegerArray{
    struct tIntegerExpression* integerExpression;
    struct tCommaIntegerArray * commaIntegerArray;  //// Nullable
}tIntegerArray;



typedef struct tCharDeclaration{
    struct tTokenNode* character;
    struct tTokenNode* varname;
    struct tTokenNode* semicolon;
}tCharDeclaration;

typedef struct tIntDeclaration{
    struct tTokenNode* integer;
    struct tTokenNode* varname;
    struct tTokenNode* semicolon;
}tIntDeclaration;

typedef struct tIntegerArrayDeclaration{
    struct tTokenNode* integer;
    struct tTokenNode* varname;
    struct tTokenNode* openSquareBracket;
    struct tIntegerExpression* integerExpression;  //// Nullable
    struct tTokenNode* closeSquareBracket;
    struct tTokenNode* semicolon;

}tIntegerArrayDeclaration;


typedef struct tCharArrayDeclaration{
    struct tTokenNode* character;
    struct tTokenNode* varname;
    struct tTokenNode* openSquareBracket;
    struct tIntegerExpression* integerExpression;  //// Nullable
    struct tTokenNode* closeSquareBracket;
    struct tTokenNode* semicolon;

}tCharArrayDeclaration;


typedef struct tGenericArrayWithBracket{
    struct tTokenNode * openBracket;
    struct tGenericValueArray * genericValueArray;
    struct tTokenNode * closeBracket;
}tGenericArrayWithBracket;


/**
 * genericValueArray
 *
 * genericValue
 * genericValue , genericValueArray
 *
 * @note Node uses @subnode tCommaGenericValueArray
 */
typedef struct tGenericValueArray{
    tGenericValue* genericValue;
    tCommaGenericValueArray* commaGenericValueArray; //// Nullable
}tGenericValueArray;

typedef struct tGenericValue{
    union{
        tTokenNode* character;
        tTokenNode* integer;
        tObjectAttribute* objectAttribute;
        tFunctionCall* fUnctionCall;
        tMethodCall* methodCall;
        tTokenNode* varname;
        tArrayDesreferencing* arrayDesreferencing;
    };
}tGenericValue;


typedef struct tObjectAttribute{
        union {
            struct tTokenNode *varnameLeft;
            struct tObjectAttribute *objectAttribute;
            struct tArrayDesreferencing *arrayDesreferencing;
        };
        struct tTokenNode * point ;
        struct tTokenNode * varnameRight;
}tObjectAttribute;

typedef struct tReturn{
    struct tTokenNode * returnToken ;
    union valueUnion{
        struct tValue * value;
        struct tConditionUnit * conditionUnit;
    }valueUnion;
    struct tTokenNode *  semicolon;
}tReturn;


typedef struct tArrayDesreferencing{
    struct tTokenNode * varname ;
    struct tTokenNode * openSquareBracket;
    struct tIntegerExpression * integerExpression;
    struct tTokenNode * closeSquareBracket ;
} tArrayDesreferencing;

typedef struct commonIntegerExpression{
    struct tIntegerExpression * leftIntegerExpression;
    struct tTokenNode * operator;
    struct tIntegerExpression * rightIntegerExpression;
} commonIntegerExpression;

typedef struct decrementIncrementIntegerExpression{
    struct tIntegerExpression * leftIntegerExpression;
    struct tTokenNode * operator;
} decrementIncrementIntegerExpression;

typedef  struct enclosedCommonIntegerExpression{
    struct tTokenNode * openParenthesis;
    struct tIntegerExpression * integerExpression;
    struct tTokenNode * closeParenthesis;

} enclosedCommonIntegerExpression;



typedef  struct tIntegerExpression{
    union {
        struct commonIntegerExpression * commonIntegerExpression;
        struct tFactor * factor;
        struct enclosedCommonIntegerExpression * enclosedCommonIntegerExpression;
        struct decrementIncrementIntegerExpression * decrementIncrementIntegerExpression;
    };
}tIntegerExpression;

typedef struct tProgramStatements{// can be empty
    struct tProgramUnitStatements * programUnitStatements;
    struct tProgramStatements* ProgramStatements;
}tProgramStatements;


typedef struct IntegerExpressionSemicolon{
    struct tIntegerExpression * integerExpression;
    struct tTokenNode * semicolon;
} IntegerExpressionSemicolon;

typedef struct tProgramUnitStatements{
    union {
        struct tWhileLoop * whileLoop;
        struct tIf * ifCondition;
        struct tAssignation * assignation;
        struct tReturn* returnReserved;
        struct tInstantiation * instantiation;
        struct IntegerExpressionSemicolon * integerExpressionSemicolon;
    };
}tProgramUnitStatements;


typedef struct tCharValue{
    union {
        struct tTokenNode * character;
        struct tObjectAttribute* objectAttribute;
        struct tFunctionCall* functionCall;
        struct tMethodCall* methodCall;
        struct tTokenNode * varname;
        struct tArrayDesreferencing* arrayDesreferencing;
    };
}tCharValue;



typedef struct tIf{
    struct tTokenNode * ifReserved;
    struct tConditionClause * condition;
    struct tClause * clause ;
    tIfElseStatement* ifElseStatement; //// Nullable

}tIf;

typedef struct tIfElseStatement{
    struct tTokenNode * elseReserved;
    struct tClause * clause;
}tIfElseStatement;


typedef struct tWhileLoop{
    struct tTokenNode * whileReserved;
    struct tCondition * conditionClause ;
    struct tClause * clause;
}tWhileLoop;

/**
 * Array assignation
 *
 * varname[ index ] = value;
 * varname[ index ] = new Function();
 * Object.attribute[ index ] = value;
 * Object.attribute[ index ] = new Function();
 *
 * @note Uses sub-node tArrayValueSemicolon for value;
 *
 */
typedef struct tArrayAssignation{
    union{
        struct tTokenNode * varname;
        struct tObjectAttribute * objectAttribute;
    };
    struct tTokenNode * openSquareBracket;
    struct tIntegerExpression * index;
    struct tTokenNode * closeSquareBracket;
    struct tTokenNode * assignation;
    union {
        struct tArrayValueSemicolon * valueSemicolon;
        struct tInstantiation * instantiation;
    };
}tArrayAssignation;


typedef struct tClause{
    struct tTokenNode* openBrace;
    struct tProgramStatements* programStatements;
    struct tTokenNode* closeBrace;
}tClause;

typedef struct tComparation{
    struct tValue* lValue;
    struct tComparisonOperator* comparisonOperator;
    struct tValue* rValue;
}tComparation;

typedef struct tLogicalOperator{
    union {
        struct tTokenNode* andToken;
        struct tTokenNode* orToken;
    };
}tLogicalOperator;

typedef struct tComparisonOperator{
    union {
        struct tTokenNode* equalOp;
        struct tTokenNode* notEqualOp;
        struct tTokenNode* lowerOp;
        struct tTokenNode* lowerEqOp;
        struct tTokenNode* greaterOp;
        struct tTokenNode* greaterEqOp;
    };
}tComparisonOperator;

typedef struct tAttributes{
    struct tTokenNode* attributes;
    struct tTokenNode* operBrace;
    struct tDeclarations* declarations;
    struct tTokenNode* closeBrace;
}tAttributes; //puede ser empty

typedef struct tDeclarations{
    struct tDeclaration * declaration;
    struct tDeclarations * declarations; //// Nullable
}tDeclarations; ////TODO checkear empty

typedef struct tConstructor{
    struct tTokenNode* constructor;
    struct tFunction* function;
}tConstructor;

typedef struct tConditionUnit{
    union {
        struct tComparation* comparation;
        struct tValueComparatorValue* valueComparatorValue;
        struct tLogicalComparationUnit* logicalComparationUnit;
        struct tCondition * condition;
    };
}tConditionUnit;

typedef struct tValueComparatorValue{
    struct tValue* lValue;
    struct tLogicalOperator* logicalOperator;
    struct tValue* rValue;
}tValueComparatorValue;

typedef struct tLogicalComparationUnit{
    struct tComparation* comparation;
    struct tLogicalOperator* logicalOperator;
    struct tConditionUnit* conditionUnit;
}tLogicalComparationUnit;

typedef struct tCondition{
    struct tTokenNode * openP;
    struct tConditionUnit * conditionUnit;
    struct tTokenNode * closeP;
}tCondition;


typedef struct tMethods{
    struct  tFunction * function;
    struct tMethods * methods; //// Nullable
}tMethods;

typedef struct tMethodCall{
    struct tTokenNode * varname;
    struct tTokenNode * point;
    struct tFunctionCall * functionCall;
}tMethodCall;


typedef struct tMainFunction{
    struct tTokenNode* integer;
    struct tTokenNode* main;
    struct tTokenNode* openParenthesis;
    struct tParameters* parameters;
    struct tTokenNode* closeParenthesis;
    struct tTokenNode* openBrace;
    struct tProgramStatements* programStatements;
    struct tTokenNode* closeBrace;
}tMainFunction;

typedef struct tInstantiation{
    struct tTokenNode* new;
    struct tFunctionCall* functionCall;
    struct tTokenNode* semicolon;
}tInstantiation;

typedef struct tIntegerAssignationDeclaration{
    struct tTokenNode* integer;
    struct tTokenNode* varname;
    struct tTokenNode* assignation;
    struct tIntegerExpression* integerExpression;
    struct tTokenNode* semicolon;
}tIntegerAssignationDeclaration;

typedef struct tCharAssignationDeclaration{
    struct tTokenNode* character;
    struct tTokenNode* varname;
    struct tTokenNode* assignation;
    struct tCharValue* charValue;
    struct tTokenNode* semicolon;
}tCharAssignationDeclaration;

typedef struct tIntegerArrayAssignationDeclaration{
    struct tTokenNode* integer;
    struct tTokenNode* varname;
    struct tTokenNode* openSquareBracket;
    struct tTokenNode* closeSquareBracket;
    struct tTokenNode* assignation;
    struct tTokenNode* openBrace;
    struct tIntegerArray* integerArray;
    struct tTokenNode* closeBrace;
    struct tTokenNode* semicolon;
}tIntegerArrayAssignationDeclaration;

/**
 *  Assignation
 *
 *  arrayAssignation
 *  varname assignation instantiation
 *  objectAttribute assignation value ;
 *  objectAttribute assignation instantiation
 *  varname assignation value ;
 *  varname [ ] assignation { integerArray } ;
 *  varname [ ] assignation { characterArray } ;
 *  varname [ ] assignation string ;
 *  objectAttribute [ ] assignation { integerArray } ;
 *  objectAttribute [ ] assignation { characterArray } ;
 *  objectAttribute [ ] assignation string ;
 *
 * @note Node uses @subnode tSuperSubnode.
 */

typedef struct tAssignation{
    union {
        struct tArrayAssignation* arrayAssignation;
        struct  tSuperSubnode* assignationSubnode;
    };
}tAssignation;


/**
 * @Subnode
 *
 *  varname assignation instantiation
 *  varname assignation value ;
 *  varname [ ] assignation { integerArray } ;
 *  varname [ ] assignation { characterArray } ;
 *  varname [ ] assignation string ;
 *  objectAttribute assignation value ;
 *  objectAttribute assignation instantiation
 *  objectAttribute [ ] assignation { integerArray } ;
 *  objectAttribute [ ] assignation { characterArray } ;
 *  objectAttribute [ ] assignation string ;
 *  
 *  @note Node uses @subnode tAssignation.
 */
typedef struct tSuperSubnode{
    union{
        struct tTokenNode* varname;
        struct tObjectAttribute* objectAttribute;
    };
    union{
        struct tArrayAssignationSubnode* arrayAssignationSubnode;
        struct tSimpleAssignationSubnode* simpleAssignationSubnode;
    };
}tSuperSubnode;

/**
 * @Subnode
 *
 * [ ] assignation { integerArray } ;
 * [ ] assignation { characterArray } ;
 * [ ] assignation string ;
 *
 * @note Node uses @subnode tCharArrayWithBrackets, tIntegerArrayWithBrackets.
 *
 * Used in tSuperSubnode
 */

typedef struct tArrayAssignationSubnode{
    struct tEmptySquareBrackets* emptySquareBrackets;
    struct tTokenNode* assignation;
    union{
        struct tGenericArrayWithBracket * genericArrayWithBrackets;
        struct tIntegerArrayWithBrackets* integerArray;
        struct tCharArrayWithBrackets* characterArray;
        struct tTokenNode* string;
    };
    struct tTokenNode* semicolon;
}tArrayAssignationSubnode;

/**
 * @Subnode
 *
 * assignation value ;
 * assignation instantation
 *
 * @note Node uses @subnode tValueWithSemicolon.
 *
 * Used in tSuperSubnode
 */

typedef struct tSimpleAssignationSubnode{
    struct tTokenNode* assignation;
    union{
        struct tArrayValueSemicolon* arrayValueSemicolon;
        struct tInstantation* instantation;
    };
}tSimpleAssignationSubnode;



/**
 *  Function
 *
 *  datatype functionName( parameters ){ programStatements }
 *  void functionName( parameters ){ programStatements }
 *  functionName( parameters ){ programStatements }
 */
typedef struct tFunction{
    union {     //// Nullable
        struct tDataType * datatype;
        struct tTokenNode * voidReserved;
        //// Nothing
    };
    struct tTokenNode * varname;
    struct tTokenNode * openP;
    struct tParameters * parameters;
    struct tTokenNode * closeP;
    struct tTokenNode * openBrace;
    struct tProgramStatements * programStatements;
    struct tTokenNode * closeBrace;
}tFunction;

/**
 * Parameters
 *
 * datatype name
 * datatype name, parameters
 * datatype name[]
 * datatype name[], parameters
 * objectTypeName name
 * objectTypeName name, parameters
 * objectTypeName name[]
 * objectTypeName name[], parameters
 *
 * @note Node uses sub-node tCommaNextparameters for ", parameters".
 */
typedef struct tParameters{
    union {
        struct tDataType * datatype;
        struct tTokenNode * objectTypeName;
    };
    struct tTokenNode * paramName;
    struct tEmptySquareBrackets * squareBrackets;       //// Nullable
    struct tCommaNextParameters * nextParameters;  //// Nullable
}tParameters;

/**
 * @node Declaration
 *
 * char name;
 * int name;
 * int name[ size ];
 * char name[ size ];
 * int name = expression;
 * char name = charValue;
 * int name[] = { integerValues };
 * char name[] = { charValues };
 * char name[] = "string";
 * ObjectDataType name;
 * ObjectDataType name = methodCall;
 * ObjectDataType name = functionCall;
 * ObjectDataType name = instantiation;
 * ObjectDataType name[];
 * ObjectDataType name[ size ];
 *
 * @note Uses @subnode tDeclarationWithObjectDataType for declarations with an Object as DataType
 */
typedef struct tDeclaration{
    union {
        struct tCharDeclaration * charDeclaration;
        struct tIntegerDeclaration * integerDeclaration;
        struct tIntegerArrayDeclaration * integerArrayDeclaration;
        struct tCharArrayDeclaration * charArrayDeclaration;
        struct tIntegerAssignationDeclaration * integerAssignationDeclaration;
        struct tCharAssignationDeclaration * charAssignationDeclaration;
        struct tIntegerArrayAssignationDeclaration * integerArrayAssignationDeclaration;
        struct tCharArrayAssignationDeclaration * charArrayAssignationDeclaration;
        struct tDeclarationWithObjectDataType * declarationAux;
    };
}tDeclaration;



  /**
   * @node Char Array Assignation Declaration
   *
   * char name[] = { charValues };
   *
   * char name[] = "string";
   *
   * @note Uses @subnode tEmptySquareBrackets
   */
   typedef struct tCharArrayAssignationDeclaration{
       struct tTokenNode * charType;
       struct tTokenNode * name;
       struct tEmptySquareBrackets * emptySquareBrackets;
       struct tTokenNode * assignation;
       union {
           struct tCharArrayWithBrackets * charArrayWithBrackets;
           struct tTokenNode * string;
       };
       struct tTokenNode * semicolon;
   }tCharArrayAssignationDeclaration;




/**
 * @section SUB-NODES
 */

/**
 * @Subnode
 * "{ charValues }"
 * 
 * Used in @node tCharArrayAssignationDeclaration
 *
 * Used in tArraysAssignationSubnode
 */
 typedef struct tCharArrayWithBrackets{
     struct tTokenNode * openBrace;
     struct tCharacterArray * characterArray;
     struct tTokenNode * closeBrace;
 }tCharArrayWithBrackets;

/**
* @Subnode
* "{ integerValues }"
*
* Used in @node tIntegerArrayAssignationDeclaration
 *
 * Used in tArraysAssignationSubnode
*/
typedef struct tIntegerArrayWithBrackets{
    struct tTokenNode * openBrace;
    struct tIntegerArray * integerArray;
    struct tTokenNode * closeBrace;
}tIntegerArrayWithBrackets;

/**
 * @Subnode
 * "[]"
 * Used in tParameters, tAssignation, tDeclarationWithObjectDataType and tCharArrayAssignationDeclaration.
 */
typedef struct tEmptySquareBrackets{
    struct tTokenNode * openSquareBracket;
    struct tTokenNode * closeSquareBracket;
}tEmptySquareBrackets;

/**
 * @Subnode
 * ", parameters"
 *
 * Used in tParameters.
 */
typedef struct tCommaNextParameters{
    struct tTokenNode * comma;
    struct tParameters * nextParameters;
}tCommaNextParameters;

/**
 * @Subnode
 * "value;"
 *
 * Subnode used in tArrayAssignation, tSimpleAssignationSubnode.
 */
typedef struct tArrayValueSemicolon{
    struct tValue * value;
    struct tTokenNode * semicolon;
}tArrayValueSemicolon;


/**
* @subnode Declaration with Object as data type
*
* ObjectDataType name;
* ObjectDataType name = methodCall;
* ObjectDataType name = functionCall;
* ObjectDataType name = instantiation;
* ObjectDataType name[];
* ObjectDataType name[ size ];
*
* Used in @node tDeclaration
*
* @note Uses @subnode tEmptySquareBrackets, tSquareBracketsWithSize and tAssignationWithMethodFunctionInstantiation
*/
typedef struct tDeclarationWithObjectDataType{
    struct tTokenNode * objectDataType;
    struct tTokenNode * name;
    union {
        struct tTokenNode * semicolon;
        struct tEmptySquareBrackets * emptySquareBrackets;
        struct tSquareBracketsWithSize * squareBracketsWithSize;
        struct tAssignationWithMethodFunctionInstantiation * assignationWithMethodFunctionInstantiation;
    };
}tDeclarationWithObjectDataType;

/**
 * @subnode Square brackets with size
 *
 * [ size ]
 *
 * Used in @subnode tDeclarationWithObjectDataType
 *
 * @note size is an integer expression
 */
typedef struct tSquareBracketsWithSize{
    struct tTokenNode * openSquareBracket;
    struct tIntegerExpression * size;
    struct tTokenNode * closeSquareBracket;
}tSquareBracketsWithSize;

/**
 * @subnode Assignation with Function, Method or instantiation
 *
 * = functionCall
 * = methodCall
 * = instantiation
 *
 * Used in @subnode tDeclarationWithObjectDataType
 */
typedef struct tAssignationWithMethodFunctionInstantiation{
    struct tTokenNode * assignation;
    union {
        struct tFunctionCall * functionCall;
        struct tMethodCall * methodCall;
        struct tInstantiation * instantiation;
    };
}tAssignationWithMethodFunctionInstantiation;

/**
 * @subnode Extends Name
 *
 * extends ExtendedClassName
 *
 * @note Used in @node tClass
 */
typedef struct tExtendsName{
    struct tTokenNode * extends;
    struct tTokenNode * extendedClassName;
}tExtendsName;

/**
 * @subnode Classes and main
 *
 * classes main
 *
 * @note Used in @node tProgram
 */
typedef struct tClassesAndMain{
    union {
        struct tClassAux* class;
        struct tProgram * program;
    };
}tClassesAndMain;

/**
 * @subnode Comma Character Array
 *
 * ", character_array"
 *
 * @note Used in tCharacterArray
 */
typedef struct tCommaCharacterArray{
    struct tTokenNode* comma;
    struct tCharacterArray* next;
}tCommaCharacterArray;


/**
 * @subnode Comma Integer Array
 *
 * ", integer_array"
 *
 * @note Used in tIntegerArray
 */
typedef struct tCommaIntegerArray{
    struct tTokenNode* comma;
    struct tIntegerArray* next;
}tCommaIntegerArray;

/**
 * @subnode -Integer
 *
 * -Integer
 *
 * @note Used in @node tFactor
 */
typedef struct tSubInteger{
    tTokenNode * sub;
    tTokenNode * integer;
}tSubInteger;

/**
 * @Subnode
 *
 * , genericValueArray
 *
 * Used in tGenericValueArray
 */

typedef struct tCommaGenericValueArray{
    tTokenNode* comma;
    tGenericValueArray* genericValueArray;
};
#endif

#ifndef SHARED_HEADER
#define SHARED_HEADER

#include <stdio.h>
#include "../../frontend/lexical-analysis/flex-actions.h"

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
 * Token nodes (Hojas)
 */
typedef struct tTokenNode{
    TokenID tokenId;
    union associated_value{
        char * varname;
        int integerValue;
        char charValue;
    };
} tTokenNode;

/**
 * Data types
 */
typedef struct tDataType{
    tTokenNode * type;
}tDataType;

/**
 * type varname;
 */
typedef struct tVarDeclaration{
    tDataType* dataType;
    tTokenNode * varname;
    tTokenNode * semicolon;
} VarDeclaration;

/**
 *
 */
typedef struct tFactor{
    union{
        tObjectAttribute * object_attribute;
        tFunction_call * function_call;
        tMethod_call * method_call;
        tTokenNode *  varname;
        tArray_desreferencing * array_desreferencing;
        union subInteger{
            tTokenNode * sub;
            tTokenNode * integer;
        } ;
        tTokenNode * integer;
    };
} tFactor;

/**
 * Value
 * var
 *      INT
 *      CHAR
 * integer_expression
 * Object attribute desreferencing + Object attribute of the Object attribute desreferenced
 */
typedef struct tValue{
    union {
        tTokenNode * var;
        tIntegerExpression * integerExpression;
        tValueAuxObjectAttributeDesreferencing * value_object_attribute_desreferencing;
    };
}tValue;

/**
 * Value Auxiliar Struct
 * Object attribute desreferencing + Object attribute of the Object attribute desreferenced
 *
 * Object.attribute[ index ]
 * Object.attribute[ index ].attribute1
 */
typedef struct tValueAuxObjectAttributeDesreferencing{
    tObjectAttribute * objectAttribute;
    tTokenNode * openSquareBracket;
    tIntegerExpression * index;
    tTokenNode * closeSquareBracket;
    tTokenNode * point;     //// Nullable
    tTokenNode * varname;   //// Nullable
    // TODO Ver último caso del bison.
}tValueAux;

/**
 * Argument Values
 *
 * Value, NextArgument
 */
typedef struct tArgumentValues{
    tValue * value;
    tTokenNode * comma;
    struct tArgument * nextArgument;
}tArgumentValues;

/**
 * Function Call
 *
 * functionName( tArgument )
 * functionName( )
 */
typedef struct tFunctionCall{
    tTokenNode * functionName;
    tTokenNode * openP;
    tArgumentValues * firstArgument; //// Nullable
    tTokenNode * closeP;
}tFunctionCall;

typedef struct tObjectAttribute{
        union {
            tTokenNode *varname;
            tObjectAttribute *objectAttribute;
            tArrayDesreferencing *arrayDesreferencing;
        }
        tTokenNode * point ;
        tTokenNode * varname;
}tObjectAttribute;

typedef struct tReturn{
    tTokenNode * returnToken ;
    union {
       tValue * value;
       tCondition_unit * conditionUnit;
    } returnValue;
    tTokenNode *  semicolon;
}tReturn;


typedef struct tArrayDesreferencing{
    tTokenNode * varname ;
    tTokenNode * openSquareBracket;
    tIntegerExpression * integerExpression;
    tTokenNode * closeSquareBracket ;
} tArrayDesreferencing;

typedef struct commonIntegerExpression{
    struct tIntegerExpression * leftIntegerExpression;
    tTokenNode * operator;
    struct tIntegerExpression * rightIntegerExpression;
} commonIntegerExpression;

typedef  struct enclosedCommonIntegerExpression{
    tTokenNode * openParenthesis;
    struct tIntegerExpression * integerExpression;
    tTokenNode * closeParenthesis;

} enclosedCommonIntegerExpression;



typedef  struct tIntegerExpression{
    union {
        commonIntegerExpression * commonIntegerExpression;
        tFactor * factor;
        enclosedCommonIntegerExpression * enclosedCommonIntegerExpression;
    };
}tIntegerExpression;

typedef struct tProgramStatements{
    tProgramUnitStatements * programUnitStatements;
    struct tProgramStatements* ProgramStatements;
};


typedef struct IntegerExpressionSemicolon{
    tIntegerExpression * integerExpression;
    tTokenNode * semicolon;
} IntegerExpressionSemicolon;

typedef struct tProgramUnitStatements{
    union {
        tWhileLoop * whileLoop;
        tIf * ifCondition;
        tAssignation * assignation;
        tInstantiation * instantiation;
        IntegerExpressionSemicolon * integerExpressionSemicolon;
    };
};


typedef struct tCharValue{
    union {
        tTokenNode * character;
        tObjectAttribute* objectAttribute;
        tFunctionCall* functionCall;
        tMethodCall* methodCall;
        tTokenNode * varname;
        tArrayDesreferencing* arrayDesreferencing;
    };
}tCharValue;

typedef struct ifStatement{
    tTokenNode * ifReserved;
    tConditionClause * condition;
    tClause * clause ;
} ifStatement;

typedef struct ifElseStatement{
    ifStatement * ifStatement;
    tTokenNode * elseReserved;
    tClause * clause;
}ifElseStatement;

typedef struct tIf{
    union {
        ifStatement * ifStatement;
        ifElseStatement * ifElseStatement;
    };
}tIf;


typedef tWhile{
    tTokenNode * whileReserved;
    tCondition * conditionClause ;
    tClause * clause;
}tWhile;


typedef struct tArrayAssignation{
    
}tArrayAssignation;

#endif

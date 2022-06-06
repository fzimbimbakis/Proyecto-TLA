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

typedef struct tProgram{
    union {
        tMainFunction* mainFunction;
        tClassAux* class;
    };
};

typedef struct tClassAux{
    tClass* class;
    tProgram program;
};

typedef struct tClass{
    tTokenNode* class;
    tTokenNode* varname;
    tTokenNode* openBrace;
    tClassIn* classIn;
    tTokenNode* closeBrace;
};

typedef struct tClassIn{
    tAttributes* attributes;
    tConstructor* constructor;
    tMethods* methods;
};

typedef struct tCharacterArray{
    tCharValue* charValue;
    tTokenNode* comma;      ////los hacemos nullable estos 2
    tCharacterArray* next;  ////los hacemos nullable estos 2
};

typedef struct tIntegerArray{
    tIntegerExpression* integerExpression;
    tTokenNode* comma;      ////los hacemos nullable estos 2
    tIntegerArrat* next;  ////los hacemos nullable estos 2
};


typedef struct tCharDeclaration{
    tTokenNode* charType;
    tTokenNode* varname;
    tTokenNode* semicolon;
};

typedef struct tIntDeclaration{
    tTokenNode* intType;
    tTokenNode* varname;
    tTokenNode* semicolon;
};

typedef struct tIntegerArrayDeclaration{
    tTokenNode* intType;
    tTokenNode* varname;
    tTokenNode* openSquareBracket;
    tIntegerExpression* integerExpression;  //// Nullable
    tTokenNode* closeSquareBracket;
    tTokenNode* semicolon;

};


typedef struct tCharArrayDeclaration{
    tTokenNode* charType;
    tTokenNode* varname;
    tTokenNode* openSquareBracket;
    tIntegerExpression* integerExpression;  //// Nullable
    tTokenNode* closeSquareBracket;
    tTokenNode* semicolon;

};

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
        tTokenNode * varname;
        tObjectAttribute * objectAttribute;
    };
    tTokenNode * openSquareBracket;
    tIntegerExpression * index;
    tTokenNode * closeSquareBracket;
    tTokenNode * assignation;
    union {
        tArrayValueSemicolon * valueSemicolon;
        tInstantiation * instantiation;
    };
}tArrayAssignation;
/**
 * @Subnode
 * value;
 * Subnode used in tArrayAssignation.
 */
typedef struct tArrayValueSemicolon{
    tValue * value;
    tTokenNode * semicolon;
}tArrayValueSemicolon;

typedef struct tClause{
    tTokenNode* openBrace;
    tProgramStatements* programStatements;
    tTokenNode* closeBrace;
};

typedef struct tComparation{
    tValue* lValue;
    tComparisonOperator* comparisonOperator;
    tValue* rValue;
};

typedef struct tLogicalOperator{
    union {
        tTokenNode* andToken;
        tTokenNode* orToken;
    };
};

typedef struct tComparisonOperator{
    union {
        tTokenNode* equalOp;
        tTokenNode* notEqualOp;
        tTokenNode* lowerOp;
        tTokenNode* lowerEqOp;
        tTokenNode* greaterOp;
        tTokenNode* greaterEqOp;
    };
};

typedef struct tAttributes{
    tTokenNode* attributes;
    tTokenNode* operBrace;
    tDeclarations* declarations;
    tTokenNode* closeBrace;
};

typedef struct tDeclarations{
    tDeclaration * declaration;
    tDeclarations * declarations; //// Nullable
}; ////TODO checkear empty

typedef struct tConstructor{
    tTokenNode* constructor;
    tFunction* function;
};

typedef struct tConditionUnit{
    union {
        tComparation* comparation;
        tValueComparatorValue* valueComparatorValue;
        tLogicalComparationUnit* logicalComparationUnit
        tCondition* condition;
    };
};

typedef struct tvalueComparatorValue{
    tValue* lValue;
    tLogicalOperator logicalOperator;
    tValue* rValue;
};

typedef struct tLogicalComparationUnit{
    tComparation* comparation;
    tLogicalOperator* logicalOperator;
    tConditionUnit* conditionUnit;
};

typedef struct tCondition{
    tTokenNode * openP;
    tConditionUnit * conditionUnit;
    tTokenNode * closeP;
}tCondition;


typedef struct tMethods{
    tFunction * function;
    tMethods * methods; //// Nullable
}tMethods;

typedef tMethodCall{
    tTokenNode * varname;
    tTokenNode * point;
    tFunctionCall * functionCall;
}tMethodCall;

typedef tDataType{
    union {
        tTokenNode * integerType;
        tTokenNode * characterType;
    };
}tDataType;

typedef tMainFunction{
    tTokenNode* integerType;
    tTokenNode* main;
    tTokenNode* openParenthesis;
    tParameters* parameters;
    tTokenNode* closeParenthesis;
    tTokenNode* openBrace;
    tProgramStatements* programStatements;
    tTokenNode* closeBrace;
}tMainFunction;

typedef tInstantiation{
    tTokenNode* new;
    tFunctionCall* functionCall;
    tTokenNode* semicolon;
}tInstantiation;

typedef tIntegerAssignationDeclaration{
    tTokenNode* integer;
    tTokenNode* varname;
    tTokenNode* assignation;
    tIntegerExpression* integerExpression;
    tTokenNode* semicolon;
}tIntegerAssignationDeclaration;

typedef tCharAssignationDeclaration{
    tTokenNode* character;
    tTokenNode* varname;
    tTokenNode* assignation;
    tCharValue* charValue;
    tTokenNode* semicolon;
}tCharAssignationDeclaration;

typedef tIntegerArrayAssignationDeclaration{
    tTokenNode* integer;
    tTokenNode* varname;
    tTokenNode* openSquareBracket;
    tTokenNode* closeSquareBracket;
    tTokenNode* assignation;
    tTokenNode* openBrace;
    tIntegerArray* integerArray;
    tTokenNode* closeBrace;
    tTokenNode* semicolon;
}tIntegerArrayAssignationDeclaration;

/**
 *  Assignation
 *
 *  arrayAssignation
 *  varname assignation instantiation
 *  objectAttribute assignation value ;
 *  varname assignation value ;
 *  varname [ ] assignation { integerArray } ;
 *  varname [ ] assignation characterArray ;
 *  varname [ ] assignation string ;
 *  objectAttribute [ ] assignation { integerArray } ;
 *  objectAttribute [ ] assignation characterArray ;
 *  objectAttribute [ ] assignation string ;
 *
 * @note Node uses sub-node tSquareBrackets for "[]".
 */

typedef tAssignation{
    union{
        tTokenNode* varname;
        tArrayAssignation* arrayAssignation;
        tObjectAttribute* objectAttribute;
    };
    tSquareBrackets* squareBrackets; //// Nullable
    tAssignation* assignation; //// Nullable
//TODO: seguir

}tAssignation;

/**
 *  Function
 *
 *  datatype functionName( parameters ){ programStatements }
 *  void functionName( parameters ){ programStatements }
 *  functionName( parameters ){ programStatements }
 */
typedef struct tFunction{
    union {     //// Nullable
        tDataType * datatype;
        tTokenNode * void;
        //// Nothing
    };
    tTokenNode * varname;
    tTokenNode * openP;
    tParameters * parameters;
    tTokenNode * closeP;
    tTokenNode * openBrace;
    tProgramStatements * programStatements;
    tTokenNode * closeBrace;
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
        tDatatype * datatype;
        tTokenNode * objectTypeName;
    };
    tTokenNode * paramName;
    tSquareBrackets * squareBrackets;       //// Nullable
    tCommaNextParameters * nextParameters;  //// Nullable
}tParameters;
/**
 * @Subnode
 * []
 * Used in tParameters.
 */
typedef struct tSquareBrackets{
    tTokenNode * openSquareBracket;
    tTokenNode * closeSquareBracket;
};
/**
 * @Subnode
 * , parameters
 * Used in tParameters.
 */
typedef struct tCommaNextParameters{
    tTokenNode * comma;
    tParameters * nextParameters;
}tCommaNextParameters;
#endif

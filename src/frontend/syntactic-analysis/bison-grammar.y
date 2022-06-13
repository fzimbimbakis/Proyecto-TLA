%{

#include "bison-actions.h"
#include "../../backend/support/shared.h"


%}

%union{
	tTokenNode* TokenNode;
	tDataType* DataType;
	tFactor* Factor;
	tValue* Value;
	tArgumentValues* ArgumentValues;
	tFunctionCall* FunctionCall;
	tProgram* Program;
	tClass* Class;
	tClassIn* ClassIn;
	tCharacterArray* CharacterArray;
	tIntegerArray* IntegerArray;
	tCharDeclaration* CharDeclaration;
	tIntDeclaration* IntDeclaration;
	tIntegerArrayDeclaration* IntegerArrayDeclaration;
	tCharArrayDeclaration* CharArrayDeclaration;
	tGenericValueArray* GenericValueArray;
	tGenericValue* GenericValue;
	tObjectAttribute* ObjectAttribute;
	tReturn* Return;
	tArrayDesreferencing* ArrayDesreferencing;
	tProgramStatements* ProgramStatements;
    tProgramUnitStatements* ProgramUnitStatements;
    tCharValue* CharValue;
    tIf* If;
    tWhileLoop* WhileLoop;
    tArrayAssignation* ArrayAssignation;
    tClause* Clause;
    tComparation* Comparation;
    tLogicalOperator* LogicalOperator;
    tComparisonOperator* ComparisonOperator;
    tAttributes* Attributes;
    tDeclarations* Declarations;
    tConstructor* Constructor;
    tConditionUnit* ConditionUnit;
    tValueComparatorValue* ValueComparatorValue;
    tLogicalComparationUnit* LogicalComparationUnit;
    tCondition* Condition;
    tMethods* Methods;
    tMethodCall* MethodCall;
    tMainFunction* MainFunction;
    tInstantiation* Instantiation;
    tIntegerAssignationDeclaration* IntegerAssignationDeclaration;
    tCharAssignationDeclaration* CharAssignationDeclaration;
    tIntegerArrayAssignationDeclaration* IntegerArrayAssignationDeclaration;
    tAssignation* Assignation;
    tSuperSubnode* SuperSubnode;
    tArrayAssignationSubnode* ArrayAssignationSubnode;
    tSimpleAssignationSubnode* SimpleAssignationSubnode;
    tFunction* Function;
    tParameters* Parameters;
    tDeclaration* Declaration;
    tIntegerExpression* IntegerExpression;
    tCharArrayAssignationDeclaration* CharArrayAssignationDeclaration;
    int integer;
    int token;
    char * string;
    char character;
;}

%type <DataType> datatype
%type <Factor> factor
%type <Value> value
%type <ArgumentValues> argument_values
%type <FunctionCall> function_call
%type <Program> program
%type <Class> class
%type <ClassIn> class_in
%type <CharacterArray>character_array
%type <IntegerArray> integer_array
%type <CharDeclaration> char_declaration
%type <IntDeclaration> integer_declaration
%type <IntegerArrayDeclaration> integer_array_declaration
%type <CharArrayDeclaration> char_array_declaration
%type <GenericValueArray> generic_value_array
%type <GenericValue> generic_value
%type <ObjectAttribute> object_attribute
%type <Return> return
%type <ArrayDesreferencing> array_desreferencing
%type <ProgramStatements> program_statements
%type <ProgramUnitStatements> program_unit_statements
%type <CharValue> char_value
%type <If> if
%type <WhileLoop> while_loop
%type <ArrayAssignation> array_assignation
%type <Clause> clause
%type <Comparation> comparation
%type <LogicalOperator> logical_operator
%type <ComparisonOperator> comparison_operator
%type <Attributes> attributes
%type <Declarations> declarations
%type <Constructor> constructor
%type <ConditionUnit> condition_unit
%type <Condition> condition
%type <Methods> methods
%type <MethodCall> method_call
%type <MainFunction> main_function
%type <Instantiation> instantiation
%type <IntegerAssignationDeclaration> integer_assignation_declaration
%type <CharAssignationDeclaration> char_assignation_declaration
%type <IntegerArrayAssignationDeclaration> integer_array_assignation_declaration
%type <Assignation> assignation
%type <Function> function
%type <Function> constructor_function
%type <Parameters> parameters
%type <Declaration> declaration
%type <IntegerExpression> integer_expression
%type <CharArrayAssignationDeclaration> char_array_assignation_declaration
// IDs de los tokens generados desde Flex:
%token <token> MODULO
%token <token> INCREMENT
%token <token> DECREMENT
%token <token> ADD
%token <token> SUB
%token <token> MUL
%token <token> DIV
%token <token> COMMA
%token <token> SEMICOLON
%token <token> OPEN_BRACE
%token <token> CLOSE_BRACE
%token <token> OPEN_SQUARE_BRACKET
%token <token> CLOSE_SQUARE_BRACKET

%token <token> ASSIGNATION
%token <token> IF
%token <token> ELSE
%token <token> WHILE
%token <token> CLASS
%token <token> EXTENDS
%token <token> ATTRIBUTES
%token <token> CONSTRUCTOR
%token <token> RETURN
%token <token> NEW
%token <token> VOID
%token <token> INT
%token <token> CHAR
%token <character> CHARACTER
%token <string> STRING

%token <string> VARNAME
%token <token> EQUAL_OP
%token <token> NOT_EQUAL_OP
%token <token> LOWER_OP
%token <token> LOWEREQ_OP
%token <token> GREATER_OP
%token <token> GREATEREQ_OP
%token <token> AND
%token <token> OR

%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS

%token <integer> INTEGER
%token <token> POINT
%token <token> MAIN

// Reglas de asociatividad y precedencia (de menor a mayor):
%left ADD SUB
%left MUL DIV MODULO INCREMENT DECREMENT

%%

//
program: main_function { state.succeed = true;  state.result = 1; state.root = ProgramGrammarActionWithMain($1); $$ = state.root; }
 | class program {state.succeed = true ;  state.result = 1; state.root = ProgramGrammarActionWithClassAndProg($1,$2); $$ = state.root; };

//
class: CLASS VARNAME OPEN_BRACE  class_in CLOSE_BRACE  {$$ = ClassGrammarAction($1, $2, $3 ,$4 ,$5);}
| CLASS VARNAME EXTENDS VARNAME OPEN_BRACE class_in CLOSE_BRACE {$$ = ClassGrammarActionWithHerency($1, $2, $3 ,$4 ,$5,$6,$7);}
;



class_in: attributes constructor methods  {$$ = classInGrammarAction($1,$2,$3);}
;

instantiation: NEW function_call SEMICOLON {$$ = instantiationGrammarAction($1,$2,$3);}
;


declaration: char_declaration	{ $$ = charDeclarationGrammarAction($1);}
| integer_declaration	{ $$ = integerDeclarationGrammarAction($1);}
| integer_array_declaration	{ $$ = integerArrayDeclarationGrammarAction($1);}
| char_array_declaration	{ $$ = charArrayDeclarationGrammarAction($1);}
| integer_assignation_declaration	{ $$ = integerAssignationDeclarationGrammarAction($1);}
| char_assignation_declaration	{ $$ = charAssignationDeclarationGrammarAction($1);}
| integer_array_assignation_declaration	{ $$ = integerArrayAssignationDeclaration($1);}
| char_array_assignation_declaration	{ $$ = charArrayAssignationDeclarationGrammarAction($1);}
| VARNAME VARNAME SEMICOLON	{ $$ = declarationWithObjectDataTypeGrammarActionBasic($1, $2, $3);}
| VARNAME VARNAME ASSIGNATION method_call SEMICOLON	{ $$ = declarationWithObjectDataTypeGrammarActionMethodFunction($1, $2, $3, $4, $5);}
| VARNAME VARNAME ASSIGNATION function_call SEMICOLON	{ $$ = declarationWithObjectDataTypeGrammarActionMethodFunction($1, $2, $3, $4, $5);}
| VARNAME VARNAME ASSIGNATION instantiation	{ $$ = declarationWithObjectDataTypeGrammarActionInstantiation($1, $2, $3, $4);}
| VARNAME VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET SEMICOLON	{ $$ = declarationWithObjectDataTypeGrammarActionArrayNoSize($1, $2, $3, $4, $5);}
| VARNAME VARNAME OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET SEMICOLON	{ $$ = declarationWithObjectDataTypeGrammarActionArrayWithSize($1, $2, $3, $4, $5, $6);}

;




/************************
*DECLARATION ASSIGNATION*
************************/


integer_assignation_declaration: INT VARNAME ASSIGNATION integer_expression SEMICOLON	{$$ = integerAssignationDeclarationRuleGrammarAction($1,$2,$3,$4,$5);}
;


char_assignation_declaration: CHAR VARNAME ASSIGNATION char_value SEMICOLON  {$$ = charAssignationDeclarationRuleGrammarAction($1,$2,$3,$4,$5);}
;


integer_array_assignation_declaration: INT VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION OPEN_BRACE integer_array CLOSE_BRACE SEMICOLON {$$ = integerArrayAssignationDeclarationGrammarAction($1,$2,$3,$4,$5,$6,$7,$8,$9);};


char_array_assignation_declaration: CHAR VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION OPEN_BRACE character_array CLOSE_BRACE SEMICOLON {$$ = charArrayAssignationDeclarationRuleGrammarAction($1,$2,$3,$4,$5,$6,$7,$8,$9);}
| CHAR VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION STRING SEMICOLON {$$ = charArrayAssignationDeclarationRule2GrammarAction($1,$2,$3,$4,$5,$6,$7);}
;


integer_array: integer_expression {$$ =tIntegerArrayGrammarAction($1);}
| integer_expression COMMA integer_array {$$ = tIntegerArrayWithCommaGrammarAction($1,$2,$3);}
;


character_array: char_value {$$ = characterArrayGrammarAction($1);}
| char_value COMMA character_array {$$ = characterArrayRule2GrammarAction($1,$2,$3 );}
;


/************
*DECLARATION*
************/

integer_declaration: INT VARNAME SEMICOLON	{$$ = integerDeclarationRuleGrammarAction($1,$2,$3);}
;


char_declaration: CHAR VARNAME SEMICOLON  {$$ = charDeclarationRuleGrammarAction($1,$2,$3);}
;


integer_array_declaration: INT VARNAME OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET SEMICOLON {$$ = integerArrayDeclarationRuleGrammarAction($1,$2,$3,$4,$5,$6);}
;


char_array_declaration: CHAR VARNAME OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET SEMICOLON {$$ = charArrayDeclarationRuleGrammarAction($1,$2,$3,$4,$5,$6);}
| CHAR VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET SEMICOLON {$$ = charArrayDeclarationRule2GrammarAction($1,$2,$3,$4,$5);}
 ;

/*************
* ASSIGNATION*
**************/


assignation: VARNAME ASSIGNATION value SEMICOLON {$$ = assignationGrammarAction($1,$2,$3,$4);}
| VARNAME ASSIGNATION instantiation  {$$ = assignationRule2GrammarAction($1,$2,$3);}
| VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION OPEN_BRACE generic_value_array CLOSE_BRACE SEMICOLON {$$ = assignationRule3GrammarAction($1,$2,$3,$4,$5,$6,$7,$8);}
| VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION STRING SEMICOLON {$$ = assignationRule4GrammarAction( $1,$2,$3,$4,$5,$6);}
| array_assignation {$$ = assignationRule5GrammarAction($1);}
| object_attribute ASSIGNATION value SEMICOLON {$$ = assignationRule6GrammarAction($1,$2,$3,$4);}
| object_attribute ASSIGNATION instantiation {$$ = assignationRule7GrammarAction($1,$2,$3);}
| object_attribute OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION OPEN_BRACE generic_value_array CLOSE_BRACE SEMICOLON { $$ =  assignationRule8GrammarAction($1,$2,$3,$4,$5,$6,$7,$8);}
| object_attribute OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION STRING SEMICOLON { $$ =  assignationRule9GrammarAction($1,$2,$3,$4,$5,$6);}
;


value: integer_expression { $$ =  valueSingle($1);}
| CHARACTER { $$ =  valueSingleCharacter($1);}
| STRING { $$ =  valueSingleString($1);}
| object_attribute OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET { $$ =  valueObjectAttributeDesreferencing($1,$2,$3,$4);};
| object_attribute OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET POINT VARNAME { $$ =  valueObjectAttributeDesreferencingAttribute($1,$2,$3,$4,$5,$6);}
;

generic_value_array:
generic_value { $$ =  genericValueArraySingle($1);}
| generic_value COMMA generic_value_array { $$ =  genericValueArrayPlural($1,$2,$3);};

generic_value:
CHARACTER { $$ =  genericValueCharacter($1);}
|INTEGER { $$ =  genericValueInteger($1);}
| object_attribute { $$ =  genericValue($1);}
| function_call { $$ =  genericValue($1);}
| method_call { $$ =  genericValue($1);}
| VARNAME { $$ =  genericValueVarname($1);}
| array_desreferencing { $$ =  genericValue($1);}
;



char_value: CHARACTER { $$ =  charValueCharacter($1);}
| object_attribute  { $$ =  charValue($1,1);}
| function_call { $$ =  charValue($1,2);}
| method_call { $$ =  charValue($1,3);}
| VARNAME { $$ =  charValueVarname($1);}
| array_desreferencing { $$ =  charValue($1,5);}
;


array_assignation: VARNAME OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET ASSIGNATION value SEMICOLON { $$ = arrayAssignationValueA($1, $2, $3, $4, $5, $6, $7);}
| object_attribute OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET ASSIGNATION value SEMICOLON { $$ = arrayAssignationValueB($1, $2, $3, $4, $5, $6, $7);}
| object_attribute OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET ASSIGNATION instantiation { $$ = arrayAssignationSemicolonB($1, $2, $3, $4, $5, $6);}
| VARNAME OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET ASSIGNATION instantiation { $$ = arrayAssignationSemicolonA($1, $2, $3, $4, $5, $6);}
;


methods: function  methods { $$ = methods($1,$2);}
| /*empty*/ { $$ = NULL;}
;


method_call: VARNAME POINT function_call { $$ =  methodCall($1,$2,$3);};


datatype: INT { $$ =  dataType($1);}
| CHAR { $$ =  dataType($1);}
;


parameters: datatype VARNAME { $$ = basicParameters($1, $2);}
| datatype VARNAME  COMMA parameters { $$ = multiBasicParameters($1, $2, $3, $4);}
| VARNAME VARNAME { $$ = objectParameters($1, $2);}
| VARNAME VARNAME COMMA parameters { $$ = multiObjectParameters($1, $2, $3, $4);}
| datatype VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET { $$ = arrayParameters($1, $2, $3, $4);}
| datatype VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET COMMA parameters { $$ = multiArrayParameters($1, $2, $3, $4, $5, $6);}
| VARNAME VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET { $$ = objectArrayParameters($1, $2, $3, $4);}
| VARNAME VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET COMMA parameters { $$ = multiObjectArrayParameters($1, $2, $3, $4, $5, $6);}
| /* empty */ { $$ = NULL;}
;


main_function: INT MAIN OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE { $$ = mainFunctionRule($1, $2, $3, $4, $5, $6, $7, $8);}
;


function: datatype VARNAME OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE { $$ = functionRuleWithType($1, $2, $3, $4, $5, $6, $7, $8);}
| VOID VARNAME OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE { $$ = functionRuleNoType($1, $2, $3, $4, $5, $6, $7, $8);}
//| VARNAME OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE { $$ = functionRule3GrammarAction($1, $2, $3, $4, $5, $6, $7);}
;

//
constructor: CONSTRUCTOR constructor_function { $$ = constructor($1, $2); };

constructor_function: VARNAME OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE { $$ = functionRule3GrammarAction($1, $2, $3, $4, $5, $6, $7); };

declarations: declaration declarations { $$ = declarations($1, $2);}
| /* empty */ { $$ = NULL;}
;


attributes: ATTRIBUTES OPEN_BRACE declarations CLOSE_BRACE { $$ = attributes($1, $2, $3, $4);}
|  /*empty*/ { $$ = NULL;}
;


comparison_operator: EQUAL_OP { $$ = comparisonOperator($1);}
| NOT_EQUAL_OP { $$ = comparisonOperator($1);}
| LOWER_OP { $$ = comparisonOperator($1);}
| LOWEREQ_OP { $$ = comparisonOperator($1);}
| GREATER_OP { $$ = comparisonOperator($1);}
| GREATEREQ_OP  { $$ = comparisonOperator($1);};


logical_operator: AND { $$ = logicalOperator($1);}
| OR { $$ = logicalOperator($1);}
;


comparation: value comparison_operator value { $$ = comparation($1, $2, $3);}
;


condition_unit: comparation { $$ = conditionUnitComparation($1);}
| value logical_operator value { $$ = conditionUnitValOpVal($1,$2,$3);}
| comparation logical_operator condition_unit { $$ = conditionUnitCompOpCond($1, $2, $3);}
| condition { $$ = simpleConditionUnit($1);}
;


condition: OPEN_PARENTHESIS condition_unit CLOSE_PARENTHESIS { $$ = condition($1,$2,$3);}
;


clause: OPEN_BRACE program_statements CLOSE_BRACE { $$ = clause($1,$2,$3);}
;



while_loop: WHILE condition clause { $$ = whileLoop($1,$2,$3);}
;


if: IF condition clause { $$ = If($1,$2,$3);}
| IF condition clause ELSE clause { $$ = IfElse($1,$2,$3,$4,$5);}
;



argument_values: value {$$ = argumentValuesSingle($1);}
| value COMMA argument_values {$$ = argumentValuesPlural($1, $2, $3);}
| /* empty */ {$$ = NULL ;}
;


program_unit_statements: declaration {$$ = programUnitStatements($1, 0);}
| while_loop {$$ = programUnitStatements($1, 1);}
| if {$$ = programUnitStatements($1, 2);}
| assignation {$$ = programUnitStatements($1, 3);}
| return {$$ = programUnitStatements($1, 4);}
| instantiation {$$ = programUnitStatements($1, 5);}
| integer_expression SEMICOLON {$$ = programUnitStatementsIntegerExpression($1, $2);}
;


program_statements: program_unit_statements program_statements {$$ = programStatementsRule($1, $2);}
| /* empty */ {$$ = NULL ;}
;


array_desreferencing: VARNAME OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET {$$ = arrayDesreferencing($1, $2, $3, $4);}
;


return: RETURN value SEMICOLON {$$ = returnRuleValue($1, $2, 0, $3);}
| RETURN condition_unit SEMICOLON {$$ = returnRuleValue($1, $2, 1, $3);}
| RETURN SEMICOLON {$$ = returnRuleNoValue($1, $2);}
;


integer_expression: integer_expression ADD integer_expression {$$ = integerExpressionCommon($1, $2, $3);}
| integer_expression SUB integer_expression {$$ = integerExpressionCommon($1, $2, $3);}
| integer_expression MUL integer_expression {$$ = integerExpressionCommon($1, $2, $3);}
| integer_expression DIV integer_expression {$$ = integerExpressionCommon($1, $2, $3);}
| integer_expression MODULO integer_expression {$$ = integerExpressionCommon($1, $2, $3);}
| integer_expression DECREMENT {$$ = integerExpressionIncrementDecrement($1, $2);}
| integer_expression INCREMENT {$$ = integerExpressionIncrementDecrement($1, $2);}
| OPEN_PARENTHESIS integer_expression CLOSE_PARENTHESIS {$$ = integerExpressionEnclosed($1, $2, $3);}
| factor {$$ = integerExpressionFactor($1);}
;


factor: object_attribute {$$ = factorObjectAttribute($1);}
| function_call {$$ = factorFunctionCall($1);}
| method_call {$$ = factorMethodCall($1);}
| VARNAME {$$ = factorVarname($1);}
| array_desreferencing {$$ = factorArrayDesreferencing($1);}
| SUB INTEGER {$$ = factorSubInteger($1, $2);}
| INTEGER  {$$ = factorInteger($1);}
;


object_attribute: VARNAME POINT VARNAME	{$$ = objectAttributeFromVarname($1, $2, $3);}
| object_attribute POINT VARNAME		{$$ = objectAttributeFromObjectAttribute($1, $2, $3);}
| array_desreferencing POINT VARNAME 	{$$ = objectAttributeFromArrayDesreferencing($1, $2, $3);}
;


function_call: VARNAME OPEN_PARENTHESIS argument_values CLOSE_PARENTHESIS {$$ = functionCall($1, $2, $3, $4);};


%%

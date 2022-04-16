%{

#include "bison-actions.h"

%}

// IDs de los tokens generados desde Flex:
%token MODULO 
%token INCREMENT
%token DECREMENT
%token ADD
%token SUB
%token MUL
%token DIV
%token COMMA
%token SEMICOLON
%token OPEN_BRACE
%token CLOSE_BRACE
%token OPEN_SQUARE_BRACKET
%token CLOSE_SQUARE_BRACKET

%token ASSIGNATION
%token IF
%token ELSE
%token WHILE
%token CLASS
%token EXTENDS
%token ATTRIBUTES
%token CONSTRUCTOR
%token RETURN
%token NEW
%token VOID
%token INT
%token CHAR
%token CHARACTER
%token STRING

%token VARNAME
%token EQUAL_OP
%token NOT_EQUAL_OP
%token LOWER_OP
%token LOWEREQ_OP
%token GREATER_OP
%token GREATEREQ_OP
%token AND
%token OR

%token OPEN_PARENTHESIS
%token CLOSE_PARENTHESIS

%token INTEGER
%token POINT
%token MAIN

// Reglas de asociatividad y precedencia (de menor a mayor):
%left ADD SUB
%left MUL DIV

%%

program : main_function { $$ = ProgramGrammarAction($1); } | class program { $$ = ProgramGrammarAction($1); };


class: CLASS VARNAME OPEN_BRACE  class_in CLOSE_BRACE
| CLASS VARNAME EXTENDS VARNAME OPEN_BRACE class_in CLOSE_BRACE
{ debug("class"); }
;

class_in: attributes constructor methods { debug("class_in"); }
| constructor methods
| constructor
| attributes constructor;

instantiation: NEW function_call SEMICOLON { debug("instantiation"); };

declaration: char_declaration
| integer_declaration
| integer_array_declaration
| char_array_declaration
| integer_assignation_declaration
| char_assignation_declaration
| integer_array_assignation_declaration
| char_array_assignation_declaration
| VARNAME VARNAME SEMICOLON
| VARNAME VARNAME ASSIGNATION method_call SEMICOLON
| VARNAME VARNAME ASSIGNATION function_call SEMICOLON
| VARNAME VARNAME SEMICOLON
| VARNAME VARNAME ASSIGNATION instantiation { debug("declaration"); }
| VARNAME VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET SEMICOLON
| VARNAME VARNAME OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET SEMICOLON
{ debug("declaration"); }
;


/************************
*DECLARATION ASSIGNATION*
************************/

integer_assignation_declaration: INT VARNAME ASSIGNATION int_value SEMICOLON { debug("integer_assignation_declaration"); }
;

char_assignation_declaration: CHAR VARNAME ASSIGNATION char_value SEMICOLON { debug("char_assignation_declaration"); }
;

integer_array_assignation_declaration: INT VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION OPEN_BRACE integer_array CLOSE_BRACE SEMICOLON { debug("integer_array_assignation_declaration"); };

char_array_assignation_declaration: CHAR VARNAME OPEN_SQUARE_BRACKET  CLOSE_SQUARE_BRACKET ASSIGNATION character_array SEMICOLON 
| CHAR VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION STRING SEMICOLON
{ debug("char_array_assignation_declaration"); }
;


integer_array: int_value
| int_value COMMA integer_array
{ debug("integer_array"); }
;

character_array: char_value
| char_value COMMA character_array
{ debug("character_array"); }
;


/************
*DECLARATION*
************/
integer_declaration: INT VARNAME SEMICOLON
{ debug("integer_declaration"); }
;

char_declaration: CHAR VARNAME SEMICOLON
{ debug("char_declaration"); }
;

integer_array_declaration: INT VARNAME OPEN_SQUARE_BRACKET int_value CLOSE_SQUARE_BRACKET SEMICOLON
{ debug("integer_array_declaration"); }
;

char_array_declaration: CHAR VARNAME OPEN_SQUARE_BRACKET int_value CLOSE_SQUARE_BRACKET SEMICOLON
| CHAR VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET SEMICOLON
{ debug("char_array_declaration"); }
 ;

/*************
* ASSIGNATION*
**************/

assignation: VARNAME ASSIGNATION value SEMICOLON
| VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION OPEN_BRACE integer_array CLOSE_BRACE SEMICOLON ;
| VARNAME OPEN_SQUARE_BRACKET  CLOSE_SQUARE_BRACKET ASSIGNATION character_array SEMICOLON
| VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION STRING SEMICOLON
| array_assignation { debug("assignation"); }
| VARNAME ASSIGNATION instantiation
| object_attribute ASSIGNATION value SEMICOLON
| object_attribute OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION OPEN_BRACE integer_array CLOSE_BRACE SEMICOLON ;
| object_attribute OPEN_SQUARE_BRACKET  CLOSE_SQUARE_BRACKET ASSIGNATION character_array SEMICOLON
| object_attribute OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION STRING SEMICOLON
| object_attribute ASSIGNATION instantiation
{ debug("assignation"); }
;

value: integer_expression | CHARACTER | object_attribute  | function_call | method_call | VARNAME | array_desreferencing { debug("value"); };
int_value: integer_expression | object_attribute  | function_call | method_call | VARNAME | array_desreferencing { debug("int_value"); };
char_value: CHARACTER | object_attribute  | function_call | method_call | VARNAME | array_desreferencing { debug("char_value"); };
index: INTEGER | VARNAME | object_attribute { debug("index"); };

array_assignation: VARNAME OPEN_SQUARE_BRACKET index CLOSE_SQUARE_BRACKET ASSIGNATION value SEMICOLON
| object_attribute OPEN_SQUARE_BRACKET index CLOSE_SQUARE_BRACKET ASSIGNATION value SEMICOLON
{ debug("array_assignation"); }
;


methods : function
| function  methods { debug("methods"); };

method_call: VARNAME POINT function_call { debug("method_call"); };

datatype: INT
| CHAR
{ debug("datatype"); };

parameters: datatype VARNAME
| datatype VARNAME  COMMA parameters
| VARNAME VARNAME
| VARNAME VARNAME COMMA parameters
| datatype VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET
| datatype VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET COMMA parameters
| VARNAME VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET
| VARNAME VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET COMMA parameters
;

main_function: datatype MAIN OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| datatype MAIN OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| datatype MAIN OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE  CLOSE_BRACE
| VOID MAIN OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| VOID MAIN OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| VOID MAIN OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE  CLOSE_BRACE
| MAIN OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| MAIN OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| MAIN MAIN OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE  CLOSE_BRACE
{ debug("main_function"); };

function: datatype VARNAME OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| datatype VARNAME OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| VOID VARNAME OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| VOID VARNAME OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| VARNAME OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| VARNAME OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| VARNAME OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE CLOSE_BRACE
{ debug("function"); };

constructor : CONSTRUCTOR function { debug("contructor"); };

declarations: declaration
| declaration declarations { debug("declarations"); };

attributes: ATTRIBUTES OPEN_BRACE declarations CLOSE_BRACE | ATTRIBUTES OPEN_BRACE CLOSE_BRACE { debug("attributes"); };

comparison_operator: EQUAL_OP
| NOT_EQUAL_OP
| LOWER_OP
| LOWEREQ_OP
| GREATER_OP
| GREATEREQ_OP { debug("comparison_operator"); };

logical_operator : AND
| OR { debug("logical_operator"); };

comparation: value comparison_operator value { debug("comparation"); }
;

condition_unit: comparation
| value logical_operator value
| comparation logical_operator condition_unit
| OPEN_PARENTHESIS condition_unit CLOSE_PARENTHESIS
;

condition: OPEN_PARENTHESIS condition_unit CLOSE_PARENTHESIS { debug("condition"); };

clause: program_unit_statements
| OPEN_BRACE program_statements CLOSE_BRACE
{ debug("clause"); }
;

while_loop : WHILE condition clause { debug("while_loop"); };

if_clause: IF condition clause { debug("if_clause"); };

if : if_clause
| if_clause ELSE clause { debug("if"); };

function_call: VARNAME OPEN_PARENTHESIS argument_values CLOSE_PARENTHESIS
| VARNAME OPEN_PARENTHESIS CLOSE_PARENTHESIS
{ debug("function_call"); };

argument_values_unit: integer_expression
| CHARACTER
| STRING
| VARNAME
{ debug("argument_values_unit"); }
;

argument_values : argument_values_unit
| argument_values_unit COMMA argument_values { debug("argument_values"); };

program_unit_statements: declaration { debug("program_unit_statements"); }
| while_loop
| if
| function_call SEMICOLON
| assignation { debug("program_unit_statements"); }
| return
| method_call SEMICOLON
| instantiation { debug("program_unit_statements"); }
//| int_variable DECREMENT SEMICOLON
//| int_variable INCREMENT SEMICOLON
{ debug("program_unit_statements"); };
int_variable: VARNAME | object_attribute | array_desreferencing { debug("int_variable"); };

program_statements : program_unit_statements
| program_unit_statements program_statements
{ debug("program_statements"); }
;

array_desreferencing: VARNAME OPEN_SQUARE_BRACKET int_value CLOSE_SQUARE_BRACKET
{ debug("array_desreferencing"); }
;

return: RETURN value SEMICOLON
| RETURN condition_unit SEMICOLON
| RETURN SEMICOLON
{ debug("return"); }
;


integer_expression: integer_expression ADD integer_expression
| integer_expression SUB integer_expression
| integer_expression MUL integer_expression
| integer_expression DIV integer_expression
| integer_expression MODULO integer_expression
| integer_expression DECREMENT
| integer_expression INCREMENT
| OPEN_PARENTHESIS integer_expression CLOSE_PARENTHESIS
| factor
{ debug("integer_expression"); }
;

factor: INTEGER | object_attribute  | function_call | method_call | VARNAME | array_desreferencing | SUB INTEGER
{ debug("factor"); }
;

object_attribute: VARNAME POINT VARNAME
| object_attribute POINT VARNAME
| VARNAME POINT VARNAME OPEN_SQUARE_BRACKET int_value CLOSE_SQUARE_BRACKET
| object_attribute POINT VARNAME OPEN_SQUARE_BRACKET int_value CLOSE_SQUARE_BRACKET
{ debug("object_attributes"); }
;



%%

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
%left MUL DIV MODULO INCREMENT DECREMENT

%%

program : main_function { $$ = ProgramGrammarAction($1); } | class program { $$ = ProgramGrammarAction($1); };


class: CLASS VARNAME OPEN_BRACE  class_in CLOSE_BRACE
| CLASS VARNAME EXTENDS VARNAME OPEN_BRACE class_in CLOSE_BRACE
;

class_in: attributes constructor methods
| constructor methods
| constructor
| attributes constructor;

instantiation: NEW function_call SEMICOLON ;

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
| VARNAME VARNAME ASSIGNATION instantiation
| VARNAME VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET SEMICOLON
| VARNAME VARNAME OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET SEMICOLON

;


/************************
*DECLARATION ASSIGNATION*
************************/

integer_assignation_declaration: INT VARNAME ASSIGNATION integer_expression SEMICOLON
;


char_assignation_declaration: CHAR VARNAME ASSIGNATION char_value SEMICOLON
;

integer_array_assignation_declaration: INT VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION OPEN_BRACE integer_array CLOSE_BRACE SEMICOLON ;

char_array_assignation_declaration: CHAR VARNAME OPEN_SQUARE_BRACKET  CLOSE_SQUARE_BRACKET ASSIGNATION character_array SEMICOLON 
| CHAR VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION STRING SEMICOLON
;


integer_array: integer_expression
| integer_expression COMMA integer_array
;

character_array: char_value
| char_value COMMA character_array
;


/************
*DECLARATION*
************/
integer_declaration: INT VARNAME SEMICOLON
;

char_declaration: CHAR VARNAME SEMICOLON
;

integer_array_declaration: INT VARNAME OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET SEMICOLON
;

char_array_declaration: CHAR VARNAME OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET SEMICOLON
| CHAR VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET SEMICOLON
 ;

/*************
* ASSIGNATION*
**************/

assignation: VARNAME ASSIGNATION value SEMICOLON
| VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION OPEN_BRACE integer_array CLOSE_BRACE SEMICOLON 
| VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION character_array SEMICOLON
| VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION STRING SEMICOLON
| array_assignation
| VARNAME ASSIGNATION instantiation
| object_attribute ASSIGNATION value SEMICOLON
| object_attribute OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION OPEN_BRACE integer_array CLOSE_BRACE SEMICOLON 
| object_attribute OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION character_array SEMICOLON
| object_attribute OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION STRING SEMICOLON
| object_attribute ASSIGNATION instantiation
;

value: integer_expression 
| CHARACTER 
| STRING 
| object_attribute OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET 
| object_attribute OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET POINT VARNAME 
| object_attribute OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET POINT VARNAME object_attribute
;

char_value: CHARACTER 
| object_attribute  
| function_call 
| method_call 
| VARNAME 
| array_desreferencing 
;


array_assignation: VARNAME OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET ASSIGNATION value SEMICOLON
| object_attribute OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET ASSIGNATION value SEMICOLON
| object_attribute OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET ASSIGNATION instantiation
| VARNAME OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET ASSIGNATION instantiation
;


methods : function
| function  methods ;

method_call: VARNAME POINT function_call ;

datatype: INT
| CHAR
;

parameters: datatype VARNAME
| datatype VARNAME  COMMA parameters
| VARNAME VARNAME
| VARNAME VARNAME COMMA parameters
| datatype VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET
| datatype VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET COMMA parameters
| VARNAME VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET
| VARNAME VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET COMMA parameters
;

main_function: INT MAIN OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| INT MAIN OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| INT MAIN OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE CLOSE_BRACE ; 

function: datatype VARNAME OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| datatype VARNAME OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| VOID VARNAME OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| VOID VARNAME OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| VARNAME OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| VARNAME OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| VARNAME OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE CLOSE_BRACE
;

constructor : CONSTRUCTOR function ;

declarations: declaration
| declaration declarations 
;

attributes: ATTRIBUTES OPEN_BRACE declarations CLOSE_BRACE 
| ATTRIBUTES OPEN_BRACE CLOSE_BRACE 
;

comparison_operator: EQUAL_OP
| NOT_EQUAL_OP
| LOWER_OP
| LOWEREQ_OP
| GREATER_OP
| GREATEREQ_OP ;

logical_operator : AND
| OR 
;

comparation: value comparison_operator value
;

condition_unit: comparation
| value logical_operator value
| comparation logical_operator condition_unit
| OPEN_PARENTHESIS condition_unit CLOSE_PARENTHESIS
;

condition: OPEN_PARENTHESIS condition_unit CLOSE_PARENTHESIS 
;

clause: OPEN_BRACE program_statements CLOSE_BRACE
;

while_loop : WHILE condition clause 
;


if : IF condition clause
| IF condition clause ELSE clause
;



argument_values : value
| value COMMA argument_values 
;

program_unit_statements: declaration
| while_loop
| if
| assignation
| return
| instantiation
| integer_expression SEMICOLON
;

program_statements : program_unit_statements
| program_unit_statements program_statements
;

array_desreferencing: VARNAME OPEN_SQUARE_BRACKET integer_expression CLOSE_SQUARE_BRACKET
;

return: RETURN value SEMICOLON
| RETURN condition_unit SEMICOLON
| RETURN SEMICOLON
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
;

factor: object_attribute  
| function_call 
| method_call 
| VARNAME
| array_desreferencing 
| SUB INTEGER 
| INTEGER
;

object_attribute: VARNAME POINT VARNAME
| object_attribute POINT VARNAME
| array_desreferencing POINT VARNAME
;

function_call: VARNAME OPEN_PARENTHESIS argument_values CLOSE_PARENTHESIS 
| VARNAME OPEN_PARENTHESIS CLOSE_PARENTHESIS
;


%%

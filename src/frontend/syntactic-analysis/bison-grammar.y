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

// Reglas de asociatividad y precedencia (de menor a mayor):
%left ADD SUB
%left MUL DIV

%%

program : class function { $$ = ProgramGrammarAction($1); };


class: CLASS VARNAME OPEN_BRACE  class_in CLOSE_BRACE
| CLASS VARNAME EXTENDS VARNAME OPEN_BRACE class_in CLOSE_BRACE
;

class_in: attributes constructor methods ;

instantiation: NEW function_call;

declaration: char_declaration
| integer_declaration
| integer_array_declaration
| char_array_declaration
| integer_assignation_declaration
| char_assignation_declaration
| integer_array_assignation_declaration
| char_array_assignation_declaration
| VARNAME VARNAME ASSIGNATION instantiation
;


/************************
*DECLARATION ASSIGNATION*
************************/

integer_assignation_declaration: INT VARNAME ASSIGNATION integer_expression SEMICOLON
| INT VARNAME ASSIGNATION function_call 
| INT VARNAME ASSIGNATION method_call 
| INT VARNAME ASSIGNATION array_desreferencing SEMICOLON 
| INT VARNAME ASSIGNATION VARNAME SEMICOLON 
;

char_assignation_declaration: CHAR VARNAME ASSIGNATION CHARACTER SEMICOLON
| CHAR VARNAME ASSIGNATION function_call 
| CHAR VARNAME ASSIGNATION method_call
| CHAR VARNAME ASSIGNATION array_desreferencing SEMICOLON
| CHAR VARNAME ASSIGNATION VARNAME SEMICOLON
;

integer_array_assignation_declaration: INT VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION OPEN_BRACE integer_array CLOSE_BRACE SEMICOLON ;

char_array_assignation_declaration: CHAR VARNAME OPEN_SQUARE_BRACKET  CLOSE_SQUARE_BRACKET ASSIGNATION character_array SEMICOLON 
| CHAR VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION STRING SEMICOLON
;


integer_array: INTEGER
| INTEGER COMMA integer_array ;

character_array: CHARACTER
| CHARACTER COMMA character_array ;


/************
*DECLARATION*
************/
integer_declaration: INT VARNAME SEMICOLON ;

char_declaration: CHAR VARNAME SEMICOLON ;

integer_array_declaration: INT VARNAME OPEN_SQUARE_BRACKET INTEGER CLOSE_SQUARE_BRACKET SEMICOLON
| INT VARNAME OPEN_SQUARE_BRACKET VARNAME CLOSE_SQUARE_BRACKET SEMICOLON
;

char_array_declaration: CHAR VARNAME OPEN_SQUARE_BRACKET INTEGER CLOSE_SQUARE_BRACKET SEMICOLON
| CHAR VARNAME OPEN_SQUARE_BRACKET VARNAME CLOSE_SQUARE_BRACKET SEMICOLON
 ;

/*************
* ASSIGNATION*
**************/

assignation: VARNAME ASSIGNATION integer_expression SEMICOLON
| VARNAME ASSIGNATION CHARACTER SEMICOLON
| VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION integer_array SEMICOLON
| VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION character_array SEMICOLON
| VARNAME ASSIGNATION VARNAME SEMICOLON
| VARNAME ASSIGNATION array_desreferencing SEMICOLON
| VARNAME ASSIGNATION function_call  
| VARNAME ASSIGNATION method_call
| array_assignation
| VARNAME ASSIGNATION instantiation 
;

value: integer_expression | CHARACTER  
index: INTEGER | VARNAME ; 

array_assignation: VARNAME OPEN_SQUARE_BRACKET index CLOSE_SQUARE_BRACKET ASSIGNATION value SEMICOLON
| VARNAME OPEN_SQUARE_BRACKET index CLOSE_SQUARE_BRACKET ASSIGNATION function_call
| VARNAME OPEN_SQUARE_BRACKET index CLOSE_SQUARE_BRACKET ASSIGNATION method_call 
| VARNAME OPEN_SQUARE_BRACKET index CLOSE_SQUARE_BRACKET ASSIGNATION VARNAME SEMICOLON
| VARNAME OPEN_SQUARE_BRACKET index CLOSE_SQUARE_BRACKET ASSIGNATION array_desreferencing SEMICOLON;
;


methods : function
| function  methods;

method_call: VARNAME POINT function_call ; 

datatype: INT
| CHAR
;

parameters: datatype VARNAME
| datatype VARNAME  COMMA parameters 
| VARNAME VARNAME 
| VARNAME VARNAME COMMA parameters
;

function: datatype VARNAME OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| datatype VARNAME OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| VOID VARNAME OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
| VOID VARNAME OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE
;

constructor : CONSTRUCTOR function;

declarations: declaration 
| declaration declarations; 

attributes: ATTRIBUTES OPEN_BRACE declarations CLOSE_BRACE ;

comparison_operator: EQUAL_OP
| LOWER_OP
| LOWEREQ_OP
| GREATER_OP
| GREATEREQ_OP;

logical_operator : AND
| OR ;

comparation: VARNAME comparison_operator integer_expression 
| VARNAME comparison_operator VARNAME 
| VARNAME comparison_operator CHARACTER
;

condition_unit: comparation
| comparation logical_operator condition_unit
;

condition: OPEN_PARENTHESIS condition_unit CLOSE_PARENTHESIS ;

clause: program_unit_statements
| OPEN_BRACE program_statements CLOSE_BRACE
; 

while_loop : WHILE condition clause;

if_clause: IF condition clause ;

if : if_clause
| if_clause ELSE clause;

function_call: VARNAME OPEN_PARENTHESIS argument_values CLOSE_PARENTHESIS SEMICOLON
| VARNAME OPEN_PARENTHESIS CLOSE_PARENTHESIS SEMICOLON
;

argument_values_unit: INTEGER 
| CHAR
| STRING
| VARNAME
;

argument_values : argument_values_unit
| argument_values_unit COMMA argument_values ;

program_unit_statements: declaration
| while_loop
| if
| function_call
| assignation
| return
| method_call
| instantiation
| constant DECREMENT SEMICOLON
| constant INCREMENT SEMICOLON
;

program_statements : program_unit_statements
| program_unit_statements program_statements
;

array_desreferencing: VARNAME OPEN_SQUARE_BRACKET INTEGER CLOSE_SQUARE_BRACKET 
| VARNAME OPEN_SQUARE_BRACKET VARNAME CLOSE_SQUARE_BRACKET 
;

return: RETURN VARNAME SEMICOLON
| RETURN array_desreferencing SEMICOLON
| RETURN integer_expression SEMICOLON
| RETURN CHARACTER SEMICOLON
| RETURN SEMICOLON
;


integer_expression: integer_expression ADD integer_expression
| integer_expression SUB integer_expression
| integer_expression MUL integer_expression
| integer_expression DIV integer_expression
| integer_expression MODULO integer_expression 
| integer_expression DECREMENT
| integer_expression INCREMENT
| factor
;

factor: OPEN_PARENTHESIS integer_expression CLOSE_PARENTHESIS
| constant
;

constant: INTEGER | VARNAME; 


%%

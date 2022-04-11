%{

#include "bison-actions.h"

%}

// IDs de los tokens generados desde Flex:
/* Palabras reservadas*/
	%token IF
	%token ELSE
	%token WHILE
	%token CLASS
	%token EXTENDS
	%token ATTRIBUTES
	%token CONSTRUCTOR
	%token RETURN
	%token NEW
	%token INT
	%token CHARACTER
	%token CHAR
	%token STRING
	%token INTEGER
	
	/*Nombres de variables*/
	%token VARNAME

	/* Asignacion*/
	%token ASSIGNATION
	
	//Operaciones de comparacion
	%token EQUAL_OP
	%token LOWER_OP
	%token LOWEREQ_OP
	%token GREATER_OP
	%token GREATEREQ_OP

	
	// Operadores aritméticos.
	%token ADD
	%token SUB
	%token MUL
	%token DIV

	// Operadores logicos
	%token AND
	%token OR


	// Paréntesis y llaves.
	%token OPEN_PARENTHESIS
	%token CLOSE_PARENTHESIS
	%token OPEN_BRACE
	%token CLOSE_BRACE
	%token OPEN_SQUARE_BRACKET
	%token CLOSE_SQUARE_BRACKET

	
	// Punto y coma 
	%token SEMICOLON
	%token COMMA 

// Reglas de asociatividad y precedencia (de menor a mayor):
%left ADD SUB
%left MUL DIV

%%

program : class function


class: CLASS VARNAME OPEN_BRACE  class_in CLOSE_BRACE 
| CLASS VARNAME EXTENDS VARNAME OPEN_BRACE class_in CLOSE_BRACE 	
;

class_in: attributes constructor methods ;



declaration: char_declaration 
| integer_declaration
| integer_array_declaration
| char_array_declaration
| integer_assignation_declaration
| char_assignation_declaration
| integer_array_assignation_declaration
| char_array_assignation_declaration 
;

 
/************************
*DECLARATION ASSIGNATION*
************************/

integer_assignation_declaration: INT VARNAME ASSIGNATION INTEGER SEMICOLON 
	| INT VARNAME ASSIGNATION function_call SEMICOLON;

char_assignation_declaration: CHAR VARNAME ASSIGNATION CHARACTER SEMICOLON
	| CHAR VARNAME ASSIGNATION function_call SEMICOLON;

integer_array_assignation_declaration: INT VARNAME OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET ASSIGNATION OPEN_BRACE integer_array CLOSE_BRACE SEMICOLON ; 

char_array_assignation_declaration: CHAR VARNAME OPEN_SQUARE_BRACKET INTEGER CLOSE_SQUARE_BRACKET ASSIGNATION character_array SEMICOLON ; 


integer_array: INTEGER 
| INTEGER COMMA integer_array ; 

character_array: CHARACTER 
| CHARACTER COMMA character_array ; 




/************
*DECLARATION*
************/
integer_declaration: INT VARNAME SEMICOLON ;

char_declaration: CHAR VARNAME SEMICOLON ;

array_declaration: VARNAME OPEN_SQUARE_BRACKET INTEGER CLOSE_SQUARE_BRACKET  SEMICOLON

integer_array_declaration: INT array_declaration ;

char_array_declaration: CHAR array_declaration ;

/*************
* ASSIGNATION*
**************/

assignation: VARNAME ASSIGNATION INTEGER SEMICOLON
| VARNAME ASSIGNATION CHARACTER SEMICOLON
|  VARNAME OPEN_SQUARE_BRACKET INTEGER CLOSE_SQUARE_BRACKET ASSIGNATION integer_array SEMICOLON 
| VARNAME OPEN_SQUARE_BRACKET INTEGER CLOSE_SQUARE_BRACKET ASSIGNATION character_array SEMICOLON
;

methods : function 
| function  methods; 

declarations : declaration 
| declaration COMMA declarations; 

datatype: INT 
| CHAR 
;

parameters: datatype VARNAME 
| datatype VARNAME  COMMA parameters ; 

function: datatype VARNAME OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE 
| datatype VARNAME OPEN_PARENTHESIS CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE 
;  

constructor : CONSTRUCTOR function;

attributes: ATTRIBUTES OPEN_BRACE declarations CLOSE_BRACE 

comparison_operator: EQUAL_OP 
| LOWER_OP 
| LOWEREQ_OP 
| GREATER_OP 
| GREATEREQ_OP; 

logical_operator : AND 
| OR ; 

comparation: VARNAME comparison_operator datatype ;

condition_unit: comparation
| comparation logical_operator condition_unit
;

condition: OPEN_PARENTHESIS condition_unit CLOSE_PARENTHESIS ;

while_loop : WHILE condition OPEN_BRACE program_statements CLOSE_BRACE; 

if_clause: IF condition OPEN_BRACE program_statements CLOSE_BRACE ;

if : if_clause
| if_clause ELSE OPEN_BRACE program_statements CLOSE_BRACE; 

function_call: VARNAME OPEN_PARENTHESIS argument_values CLOSE_PARENTHESIS SEMICOLON;

argument_values : VARNAME 
| VARNAME COMMA argument_values ; 

program_unit_statements: declarations
| while_loop 
| if 
| function_call
| assignation
; 

program_statements : program_unit_statements 
| program_unit_statements program_statements 
;

%%

%{

#include "bison-actions.h"

%}

// IDs de los tokens generados desde Flex:
/* Palabras reservadas*/
	%token IF
	%token ELSE
%token	WHILE,
	%token CLASS
	%token EXTENDS
	%token ATTRIBUTES
	%token CONSTRUCTOR
	%token DATATYPE
	%token RETURN
	%token NEW
	%token INTEGER
	%token CHARACTER
	
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
	
	// Punto y coma 
	%token SEMICOLON
	%token COMMA 

// Reglas de asociatividad y precedencia (de menor a mayor):
%left ADD SUB
%left MUL DIV

%%

class: CLASS VARNAME OPEN_BRACE  class_in CLOSE_BRACE 
	   | CLASS VARNAME EXTENDS VARNAME OPEN_BRACE class_in CLOSE_BRACE 	
;

class_in: attributes constructor methods ;


varname : VARNAME 
| VARNAME ASSIGNACION INTEGER 
| VARNAME ASSIGNACION function_call
| //falta string  
| VARNAME COMMA varname  ; 

declaration: DATATYPE varname SEMICOLON 
; 

methods : functions*; 

declarations : declaration*; 

parameters: DATATYPE VARNAME | DATATYPE VARNAME COMMA parameters ; 

function: DATATYPE VARNAME OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS OPEN_BRACE program_statements CLOSE_BRACE ;  

constructor : CONSTRUCTOR OPEN_BRACE function CLOSE_BRACE

attributes: ATTRIBUTES OPEN_BRACE declarations CLOSE_BRACE 

comparison_operator: EQUAL_OP | LOWER_OP | LOWEREQ_OP | GREATER_OP | GREATEREQ_OP; 

logical_operator : AND | OR ; 

condition: OPEN_PARENTHESIS VARNAME comparison_operator INTEGER CLOSE_PARENTHESIS | OPEN_PARENTHESIS VARNAME comparison_operator INTEGER logical_operator condition CLOSE_PARENTHESIS;   

while_loop : WHILE condition OPEN_BRACE program_statements CLOSE_BRACE; 

if : IF condition OPEN_BRACE program_statements CLOSE_BRACE | IF condition OPEN_BRACE program_statements CLOSE_BRACE ELSE program_statements ; 

function_call: VARNAME OPEN_PARENTHESIS argument_values CLOSE_PARENTHESIS ;

argument_values : VARNAME | VARNAME COMMA argument_values ; 

program_unit_statements: declarations
| while_loop 
| if 
| function_call
; 

program_statements : program_unit_statements*
;

%%

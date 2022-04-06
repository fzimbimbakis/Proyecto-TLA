%{

#include "flex-actions.h"

%}

/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Patrones reutilizables. */
crlf			\r\n
digit			[0-9]
endline			\n
whitespace		[ \f\n\r\t\v]
ascii           [A-Za-z]





%%

/* Palabras reservadas*/
"if"                                        {return IF;}
"else"                                      {return ELSE;}
"while"                                     {return WHILE;}
"class"                                     {return CLASS;}
"extends"                                   {return EXTENDS;}
"constructor"                               {return CONSTRUCTOR;}
"return"                                    {return RETURN; }
"new"                                       {return NEW; }
"int"                                       {return INTEGER;}
"char"                                      {return CHARACTER;}


/* Nombres de variables*/
{ascii}+{digit}*                            {return VARNAME;}

/* Asignacion */
"="                                         {return ASSIGNACION;}

/* Operaciones de comparacion */
"=="                                        {return EQUAL_OP;}
"<"                                        {return LOWER_OP;}
"<="                                        {return LOWEREQ_OP;}
">"                                        {return GREATER_OP;}
">="                                        {return GREATEREQ_OP;}


/*Operadores aritmeticos*/
"+"											{ return ADD; }
"-"											{ return SUB; }
"*"											{ return MUL; }
"/"											{ return DIV; }

/* Operadores logicos */
"&&"                                        {return AND;}
"||"                                        {return OR;}


/* Parentesis y llaves*/
"("											{ return OPEN_PARENTHESIS; }
")"											{ return CLOSE_PARENTHESIS; }
"{"											{ return OPEN_BRACE; }
"}"											{ return CLOSE_BRACE; }

/* Punto y coma*/
";"                                         {return SEMICOLON;}
","                                         {return COMMA; }



{whitespace}								{ IgnoredPatternAction(yytext); }

.											{ return UnknownPatternAction(yytext); }

%%

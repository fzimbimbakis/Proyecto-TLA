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

"if"                                        {return IF;}
"else"                                      {return ELSE;}
"while"                                     {return WHILE;}
"class"                                     {return CLASS;}
"extends"                                   {return EXTENDS;}
"constructor"                               {return CONSTRUCTOR;}
"attributes"                                {return ATTRIBUTES; }
"return"                                    {return RETURN; }
"new"                                       {return NEW; }
"int"                                       {return INT;}
"char"                                      {return CHAR;}
{digit}+                                    {return INTEGER;}

{ascii}+{digit}*                            {return VARNAME;}

"="                                         {return ASSIGNATION;}

"=="                                        {return EQUAL_OP;}
"<"                                        {return LOWER_OP;}
"<="                                        {return LOWEREQ_OP;}
">"                                        {return GREATER_OP;}
">="                                        {return GREATEREQ_OP;}


"+"											{ return ADD; }
"-"											{ return SUB; }
"*"											{ return MUL; }
"/"											{ return DIV; }

"&&"                                        {return AND;}
"||"                                        {return OR;}


"("											{ return OPEN_PARENTHESIS; }
")"											{ return CLOSE_PARENTHESIS; }
"{"											{ return OPEN_BRACE; }
"}"											{ return CLOSE_BRACE; }
"["                                         { return OPEN_SQUARE_BRACKET; }
"]"                                         { return CLOSE_SQUARE_BRACKET; }



";"                                         {return SEMICOLON;}
","                                         {return COMMA; }



{whitespace}								{ IgnoredPatternAction(yytext); }


"\'.\'"                                     {return CHARACTER; }
"\".\""                                     {return STRING;}
.											{ return UnknownPatternAction(yytext); }

%%

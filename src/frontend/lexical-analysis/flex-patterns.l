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
letra           [A-Za-z]

%%

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

{digit}+									{ return IntegerPatternAction(yytext); }

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


{letra}+                            {return VARNAME;}


";"                                         {return SEMICOLON;}
","                                         {return COMMA; }

"\'.\'"                                     {return CHARACTER; }
"\".\""                                     {return STRING;}


{whitespace}								{ IgnoredPatternAction(yytext); }
{crlf}                                      {IgnoredPatternAction(yytext);}
.											{ return UnknownPatternAction(yytext); }

%%

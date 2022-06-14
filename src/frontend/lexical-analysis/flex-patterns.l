%{

#include "flex-actions.h"
#include <stdlib.h>

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
simpleQuote     "\'"
Quote            "\""
NotQuote         [^\"]+

%%
"%"                                          {yylval.token = MODULO; return MODULO;}
"++"                                         {yylval.token = INCREMENT; return INCREMENT;}
"--"                                            {yylval.token = DECREMENT; return DECREMENT;}


"="                                            {yylval.token = ASSIGNATION; return ASSIGNATION;}

"=="                                          {yylval.token = EQUAL_OP; return EQUAL_OP;}
"!="                                           {yylval.token = NOT_EQUAL_OP; return NOT_EQUAL_OP;}
"<"                                            {yylval.token = LOWER_OP; return LOWER_OP;}
"<="                                          {yylval.token = LOWEREQ_OP; return LOWEREQ_OP;}
">"                                            {yylval.token = GREATER_OP; return GREATER_OP;}
">="                                          {yylval.token = GREATEREQ_OP; return GREATEREQ_OP;}

"+"											  { yylval.token = ADD; return ADD; }
"-"											  { yylval.token = SUB; return SUB; }
"*"											  { yylval.token = MUL; return MUL; }
"/"											  { yylval.token = DIV; return DIV; }

"&&"                                         {yylval.token = AND; return AND;}
"||"                                            {yylval.token = OR; return OR;}

"("											 { yylval.token = OPEN_PARENTHESIS; return OPEN_PARENTHESIS; }
")"											 { yylval.token = CLOSE_PARENTHESIS; return CLOSE_PARENTHESIS; }
"{"											 { yylval.token = OPEN_BRACE; return OPEN_BRACE; }
"}"											 { yylval.token = CLOSE_BRACE; return CLOSE_BRACE; }
"["                                            { yylval.token = OPEN_SQUARE_BRACKET; return OPEN_SQUARE_BRACKET; }
"]"                                            { yylval.token = CLOSE_SQUARE_BRACKET; return CLOSE_SQUARE_BRACKET; }

{digit}+									 { yylval.integer=atoi(yytext);return IntegerPatternAction(yytext); }


"if"                                          {yylval.token = IF; return IF;}
"else"                                     {yylval.token = ELSE; return ELSE;}
"while"                                   {yylval.token = WHILE; return WHILE;}
"Class"                                   {yylval.token = CLASS; return CLASS;}
"extends"                              {yylval.token = EXTENDS; return EXTENDS;}
"Constructor"                       {yylval.token =CONSTRUCTOR;return CONSTRUCTOR;}
"Attributes"                          {yylval.token =ATTRIBUTES;return ATTRIBUTES; }
"return"                                 {yylval.token =RETURN; return RETURN; }
"new"                                     {yylval.token = NEW; return NEW; }
"main"                                    {yylval.token =MAIN;return MAIN;}

"void"                                       {yylval.token = VOID; return VOID;}
"int"                                          {yylval.token = INT; return INT;}
"char"                                       {yylval.token = CHAR; return CHAR;}
"\."                                            {yylval.token =POINT; return POINT;}


{letra}+                                     {yylval.string=yytext; return VARNAME;}


";"                                          {yylval.token =SEMICOLON; return SEMICOLON;}
","                                          {yylval.token = COMMA; return COMMA; }

{simpleQuote}.{simpleQuote}                  { yylval.character = yytext[1]; printf("%c",yylval.character);return CHARACTER; }
{Quote}{NotQuote}{Quote}                      {yylval.string=yytext; return STRING;}


{whitespace}								    {IgnoredPatternAction(yytext); }
{crlf}                                                {IgnoredPatternAction(yytext);}
.										                {return UnknownPatternAction(yytext); }
%%

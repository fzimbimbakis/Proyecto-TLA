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
simpleQuote     "\'"
Quote            "\""
NotQuote         [^\"]+

%%
"%"                                          {debug(yytext);return MODULO;}
"++"                                         {debug(yytext);return INCREMENT;}
"--"                                         {debug(yytext);return DECREMENT;}


"="                                          {debug(yytext);return ASSIGNATION;}

"=="                                         {debug(yytext);return EQUAL_OP;}
"!="                                         {debug(yytext);return NOT_EQUAL_OP;}
"<"                                          {debug(yytext);return LOWER_OP;}
"<="                                         {debug(yytext);return LOWEREQ_OP;}
">"                                          {debug(yytext);return GREATER_OP;}
">="                                         {debug(yytext);return GREATEREQ_OP;}

"+"											 {debug(yytext); return ADD; }
"-"											 {debug(yytext); return SUB; }
"*"											 {debug(yytext); return MUL; }
"/"											 {debug(yytext); return DIV; }

"&&"                                         {debug(yytext);return AND;}
"||"                                         {debug(yytext);return OR;}

"("											 {debug(yytext); return OPEN_PARENTHESIS; }
")"											 {debug(yytext); return CLOSE_PARENTHESIS; }
"{"											 {debug(yytext); return OPEN_BRACE; }
"}"											 {debug(yytext); return CLOSE_BRACE; }
"["                                          {debug(yytext); return OPEN_SQUARE_BRACKET; }
"]"                                          {debug(yytext); return CLOSE_SQUARE_BRACKET; }

{digit}+									 {debug(yytext); yylval.integer=yytext;return IntegerPatternAction(yytext); }


"if"                                         {debug(yytext);return IF;}
"else"                                       {debug(yytext);return ELSE;}
"while"                                      {debug(yytext);return WHILE;}
"Class"                                      {debug(yytext);return CLASS;}
"extends"                                    {debug(yytext);return EXTENDS;}
"Constructor"                                {debug(yytext);return CONSTRUCTOR;}
"Attributes"                                 {debug(yytext);return ATTRIBUTES; }
"return"                                     {debug(yytext);return RETURN; }
"new"                                        {debug(yytext);return NEW; }
"main"                                       {debug(yytext);return MAIN;}

"void"                                       {debug(yytext);return VOID;}
"int"                                        {debug(yytext);return INT;}
"char"                                       {debug(yytext);return CHAR;}
"\."                                         {debug(yytext);return POINT;}


{letra}+                                     {debug(yytext);yylval.string=yytext;return VARNAME;}


";"                                          {debug(yytext);return SEMICOLON;}
","                                          {debug(yytext);return COMMA; }

{simpleQuote}.{simpleQuote}                  {debug(yytext); yylval.character = yytext;return CHARACTER; }
{Quote}{NotQuote}{Quote}                     {debug(yytext);yylval.string=yytext; return STRING;}


{whitespace}								{IgnoredPatternAction(yytext); }
{crlf}                                      {IgnoredPatternAction(yytext);}
.										    {return UnknownPatternAction(yytext); }
%%

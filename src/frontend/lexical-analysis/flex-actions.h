#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../syntactic-analysis/bison-parser.h"
/**
 * Se definen los diferentes IDs de cada token disponible para el scanner Flex.
 */
//typedef enum TokenID {
//
//	// Por defecto, el valor "0" hace fallar el analizador sintáctico.
//	UNKNOWN = 0,
//
//	// Código de error de Bison, que permite abortar el escaneo de lexemas cuando
//	// se presente un patrón desconocido. El número "257" coincide con el valor
//	// que Bison le otorga por defecto, pero además permite que el resto de
//	// tokens continúen desde el valor "258" lo que permite proteger los IDs
//	// internos que Bison reserva para crear "tokens literales":
//	YYUNDEF = 257,
//    MODULO,
//    INCREMENT,
//    DECREMENT,
//	ADD,
//	SUB,
//	MUL,
//	DIV,
//    COMMA,
//    SEMICOLON,
//    OPEN_BRACE,
//    CLOSE_BRACE,
//    OPEN_SQUARE_BRACKET,
//    CLOSE_SQUARE_BRACKET,
//    ASSIGNATION,
//    IF,
//    ELSE,
//    WHILE,
//    CLASS,
//    EXTENDS,
//    ATTRIBUTES,
//    CONSTRUCTOR,
//    RETURN,
//    NEW,
//    VOID,
//    INT,
//    CHAR,
//    CHARACTER,
//    STRING,
//    VARNAME,
//    EQUAL_OP,
//    NOT_EQUAL_OP,
//    LOWER_OP,
//    LOWEREQ_OP,
//    GREATER_OP,
//    GREATEREQ_OP,
//    AND,
//    OR,
//     OPEN_PARENTHESIS,
//     CLOSE_PARENTHESIS,
//     INTEGER,
//     POINT,
//     MAIN
//} TokenID;

/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 */

unsigned IntegerPatternAction(const char * lexeme);

void IgnoredPatternAction(const char * lexeme);

unsigned UnknownPatternAction(const char * lexeme);

void debug(const char * lexeme);

#define YYUNDEF 257
#define UNKNOWN 0

#endif

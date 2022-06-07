#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>

/**
 * Implementación de "flex-rules.h".
 */

unsigned IntegerPatternAction(const char * lexeme) {
	LogDebug("IntegerPatternAction: '%s'.", lexeme);
//	yylval = atoi(lexeme);
	return INTEGER;
}
//TokenID NegativeIntegerPatternAction(const char * lexeme) {
//    LogDebug("IntegerPatternAction: '%s'.", lexeme);
//    yylval = atoi(lexeme);
//    return NEGATIVE;
//}


void IgnoredPatternAction(const char * lexeme) {
	LogDebug("IgnoredPatternAction: '%s'.", lexeme);
}

unsigned UnknownPatternAction(const char * lexeme) {
	LogDebug("UnknownPatternAction: '%s'.", lexeme);
	return YYUNDEF;
}
void debug(const char * lexeme){
    LogDebug("Pattern: '%s'.", lexeme);
}

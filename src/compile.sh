cd frontend/lexical-analysis
rm lex.yy.c
flex flex-patterns.l
cd ../../frontend/syntactic-analysis/
rm bison-grammar.tab.c
bison bison-grammar.y
cd ../..
gcc main.c frontend/lexical-analysis/lex.yy.c backend/support/logger.c backend/domain-specific/calculator.c frontend/syntactic-analysis/bison-grammar.tab.c frontend/lexical-analysis/flex-actions.c frontend/syntactic-analysis/bison-actions.c

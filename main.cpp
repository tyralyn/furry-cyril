#include "ast.hpp"
#include "symbol.hpp"
#include "codegeneration.hpp"
#include "parser.hpp"

extern int yydebug;
extern int yyparse();

ASTNode* astRoot;

int main(void) {
    yydebug = 0; // Set this to 1 if you want the parser to output debug information and parse processe
    astRoot = NULL;
    //std::cout<<"1\n";
    yyparse();
    //std::cout<<"2\n";
    if (astRoot) {
        Symbol* symbol = new Symbol();
        astRoot->accept(symbol);
        ClassTable* classTable = symbol->classTable;
        if (classTable) {
            // Uncomment the following line to print the class table after it is generated
            //print(*classTable);
            CodeGenerator* codegen = new CodeGenerator();
            codegen->classTable = classTable;
            astRoot->accept(codegen);
        }
    }

    return 0;
}

#include "CompilerParser.h"
#include "ParseTree.h"
#include <string>

using namespace std;

bool str_contains(const string& a, const char& b) {
	if (a.find(b) == string::npos)
		return false;
	return true;
}
bool str_contains(const string& a, const string& b) {
	if (a.find(b) == string::npos)
		return false;
	return true;
}

ParseTree* CompilerParser::process_token(Token* t) {
    
}

/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::vector<Token*> tokens) {

    this->_tks = tokens;

}

/**
 * Generates a parse tree for a single program
 */
ParseTree* CompilerParser::compileProgram() {
    // the top root of a Jack program must be a class - everything is in a class
    if (str_contains(_tks[0]->getValue(),"class") ) {
        if ( str_contains(_tks[1]->getValue(),"Main") )
        return compileClass();
    } else {
        throw ParseException();
    }
    return NULL;
}

/**
 * Generates a parse tree for a single class
 */
ParseTree* CompilerParser::compileClass() {
    
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 */
ParseTree* CompilerParser::compileClassVarDec() {
    return NULL;
}

/**
 * Generates a parse tree for a method, function, or constructor
 */
ParseTree* CompilerParser::compileSubroutine() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine's parameters
 */
ParseTree* CompilerParser::compileParameterList() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine's body
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    return NULL;
}

/**
 * Generates a parse tree for a variable declaration
 */
ParseTree* CompilerParser::compileVarDec() {
    return NULL;
}

/**
 * Generates a parse tree for a series of statements
 */
ParseTree* CompilerParser::compileStatements() {
    return NULL;
}

/**
 * Generates a parse tree for a let statement
 */
ParseTree* CompilerParser::compileLet() {
    return NULL;
}

/**
 * Generates a parse tree for an if statement
 */
ParseTree* CompilerParser::compileIf() {
    return NULL;
}

/**
 * Generates a parse tree for a while statement
 */
ParseTree* CompilerParser::compileWhile() {
    return NULL;
}

/**
 * Generates a parse tree for a do statement
 */
ParseTree* CompilerParser::compileDo() {
    return NULL;
}

/**
 * Generates a parse tree for a return statement
 */
ParseTree* CompilerParser::compileReturn() {
    return NULL;
}

/**
 * Generates a parse tree for an expression
 */
ParseTree* CompilerParser::compileExpression() {


    return NULL;
}

/**
 * Generates a parse tree for an expression term
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for an expression list
 */
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}


const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}

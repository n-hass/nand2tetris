#include "CompilerParser.h"
#include "ParseTree.h"
#include <cstring>
#include <string>

using namespace std;

bool str_contains(const string &a, const char &b) {
  if (a.find(b) == string::npos)
    return false;
  return true;
}
bool str_contains(const string &a, const string &b) {
  if (a.find(b) == string::npos)
    return false;
  return true;
}

ParseTree *CompilerParser::process_token(Token *t) {

	
}

/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::vector<Token *> tokens) {

  this->_tks = tokens;
}

/**
 * Generates a parse tree for a single program
 */
ParseTree *CompilerParser::compileProgram() {
  // the top root of a Jack program must be a class - everything is in a class
  if ( _tks[0]->getValue().compare("class") == 0) { // validation
    if (_tks[1]->getValue().compare("Main") == 0)
      return compileClass();
  } else {
    throw ParseException();
  }
  return NULL;
}

/**
 * Generates a parse tree for a single class
 */
ParseTree *CompilerParser::compileClass() {

	// lambda for testing if its a classVarDec
	auto var_test = [](ParseTree* a) {
		if (a->getType().compare("keyword") == 0){
			if (a->getValue().compare("static"))
				return true;
			if (a->getValue().compare("field"))
				return true;
		}
		return false;
	};
	
	// lambda for testing subroutine
	auto subrt_test = [](ParseTree* a) {
		if (a->getType().compare("keyword") == 0){
			if (a->getValue().compare("function"))
				return true;
			if (a->getValue().compare("method"))
				return true;
		}
		return false;
	};

  ParseTree *cl = new ParseTree("class", "");

  if (_tks[0]->getValue().compare("class") == 0) {
    _tks.erase(_tks.begin());
    if (_tks[0]->getType().compare("identifier") == 0) {
      _tks.erase(_tks.begin());

			if (_tks[0]->getValue().compare("{") == 0) {
				_tks.erase(_tks.begin());
			} else throw ParseException();
			
    } else throw ParseException();


  } else throw ParseException();

	// int blocks = 1; // code blocks nested within the class
	while ( _tks[0]->getValue().compare("}") != 0) { // while the current token is not 
		if (var_test(_tks[0])) {
			_tks[0]->addChild( compileClassVarDec() );
		}
		if (subrt_test(_tks[0])) {
			_tks[0]->addChild( compileSubroutine() );
		}
	}
	
	// remove the closing '}' from the token list
	_tks.erase(_tks.begin());

  validateClass(cl);

  return cl;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 */
ParseTree *CompilerParser::compileClassVarDec() { return NULL; }

/**
 * Generates a parse tree for a method, function, or constructor
 */
ParseTree *CompilerParser::compileSubroutine() { return NULL; }

/**
 * Generates a parse tree for a subroutine's parameters
 */
ParseTree *CompilerParser::compileParameterList() { return NULL; }

/**
 * Generates a parse tree for a subroutine's body
 */
ParseTree *CompilerParser::compileSubroutineBody() { return NULL; }

/**
 * Generates a parse tree for a variable declaration
 */
ParseTree *CompilerParser::compileVarDec() { return NULL; }

/**
 * Generates a parse tree for a series of statements
 */
ParseTree *CompilerParser::compileStatements() { return NULL; }

/**
 * Generates a parse tree for a let statement
 */
ParseTree *CompilerParser::compileLet() { return NULL; }

/**
 * Generates a parse tree for an if statement
 */
ParseTree *CompilerParser::compileIf() { return NULL; }

/**
 * Generates a parse tree for a while statement
 */
ParseTree *CompilerParser::compileWhile() { return NULL; }

/**
 * Generates a parse tree for a do statement
 */
ParseTree *CompilerParser::compileDo() { return NULL; }

/**
 * Generates a parse tree for a return statement
 */
ParseTree *CompilerParser::compileReturn() { return NULL; }

/**
 * Generates a parse tree for an expression
 */
ParseTree *CompilerParser::compileExpression() { return NULL; }

/**
 * Generates a parse tree for an expression term
 */
ParseTree *CompilerParser::compileTerm() { return NULL; }

/**
 * Generates a parse tree for an expression list
 */
ParseTree *CompilerParser::compileExpressionList() { return NULL; }

const char *ParseException::what() {
  return "An Exception occurred while parsing!";
}

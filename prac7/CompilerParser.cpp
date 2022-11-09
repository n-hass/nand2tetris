#include "CompilerParser.h"
#include "ParseTree.h"
#include "Token.h"
#include <cstddef>
#include <cstring>
#include <string>
#include <unordered_set>
#include <vector>

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

TokenList::TokenList() {}

TokenList::TokenList(std::vector<Token*> tks) {
	this->_tks = std::list<Token*> (tks.begin(), tks.end()); // capture the tokens on construction
}

string TokenList::peek_type(int i) {
	std::list<Token*>::iterator it;
	it = _tks.begin();
	advance(it,i);
	
	return (*it)->getType();
}
string TokenList::peek_val(int i) {
	std::list<Token*>::iterator it;
	it = _tks.begin();
	advance(it,i);

	return (*it)->getValue();
}
Token* TokenList::peek(){
	return _tks.front();
}

// consumes a token from the list
Token* TokenList::process_token() {

	Token* t = _tks.front();

	if (t->getType().compare("keyword") == 0) {
		if (gdef::keywords.find(t->getValue()) == gdef::keywords.end())
			throw ParseException();
		
	} else if (t->getType().compare("symbol") == 0) {
		if (gdef::symbols.find(t->getValue()) == gdef::keywords.end())
			throw ParseException();
		
	} else if (t->getType().compare("integerConstant") == 0) {
		int x = stoi(t->getType());
		if ( x < 0 || x > 32767)
			throw ParseException();

	} else if (t->getType().compare("stringConstant") == 0) {
		if (t->getValue().front() != '\"' || t->getValue().back() != '\"')
			throw ParseException();
		
		string v = t->getValue().substr(1,t->getValue().size()-2);
		if (v.compare("\"") == 0 || v.compare("\n") == 0)
			throw ParseException();
		

	} else if (t->getType().compare("identifier") == 0) {

		// checks if a string consists of only digits, upper/lower case letters and underscore
		auto validstring = [](const string& a) {
			if(a.find_first_not_of("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_") == string::npos)
				return true;
			return false;
		};

		if (t->getValue().front() >= '0' && t->getValue().front() <= '9') // if front character is a number
			throw ParseException();
		
		if (validstring(t->getValue()) == false)
			throw ParseException();

	}
	_tks.pop_front();

	return t;
}

/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::vector<Token *> tokens) {
  tlist = TokenList(tokens);
}

/**
 * Generates a parse tree for a single program
 */
ParseTree *CompilerParser::compileProgram() {
  // the top root of a Jack program must be a class - everything is in a class
  if ( tlist.peek_val(0).compare("class") == 0) { // validation
    if (tlist.peek_val(1).compare("Main") == 0)
      return compileClass();
  } else {
    throw ParseException();
  }
  return nullptr;
}

/**
 * Generates a parse tree for a single class
 */
ParseTree *CompilerParser::compileClass() {
	// for testing if token is a classVarDec
	auto is_vardec = [](ParseTree* a) {
		if (a->getType().compare("keyword") == 0){
			if (a->getValue().compare("static"))
				return true;
			if (a->getValue().compare("field"))
				return true;
		}
		return false;
	};
	
	// for testing if token is subroutine
	auto is_subrt = [](ParseTree* a) {
		if (a->getType().compare("keyword") == 0){
			if (a->getValue().compare("function"))
				return true;
			if (a->getValue().compare("method"))
				return true;
		}
		return false;
	};

	auto is_end = [](ParseTree* a) {
		if(a->getType() == "symbol")
			if (a->getValue() == "}")
				return true;
		return false;
	};

  ParseTree *tree = new ParseTree("class", "");
	tree->addChild(tlist.process_token()); // token: keyword class
	tree->addChild(tlist.process_token()); // token: identifier
	tree->addChild(tlist.process_token()); // token: symbol {
	
	do {
		Token* x = tlist.peek();
		if (is_vardec(x)) {
			tree->addChild(compileClassVarDec());
		}
		else if (is_subrt(x)) {
			tree->addChild(compileSubroutine());
		}
		else tree->addChild(tlist.process_token());
	} while ( is_end( tree->getChildren().back() ) == false ); // test if the token just added is the end of the 

  if (validateClass(tree) == false){
		throw ParseException();
	}
  return tree;
}

bool CompilerParser::validateClass(ParseTree* x) {
	vector<ParseTree *> c = x->getChildren();

	// the class structure ParseTree
	if (x->getType() != "class" || x->getValue() != "") 
		return false;
	
	// the first token, keyword class
	if (c[0]->getType() != "keyword" || c[0]->getValue() != "class")
		return false;
	
	// an identifier (which has already been validated by process_token)
	if (c[1]->getType() != "identifier")
		return false;
	
	// the open '{'
	if (c[2]->getType() != "symbol" || c[2]->getValue() != "{")
		return false;
	
	// class decleration body
	auto is_end = [](ParseTree* a) {
		if(a->getType() == "symbol")
			if (a->getValue() == "}")
				return true;
		return false;
	};
	int i=3;
	while ( is_end(c[i]) == false ) {
		if (c[i]->getType() != "classVarDec") {
			if (c[i]->getType() != "subroutine")
				return false;
		}
		
		i++;
	}

	if (i != c.size()-1 || c[i]->getType() != "symbol" || c[i]->getValue() != "}")
		return false;

	return true;
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

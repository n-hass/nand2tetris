#include "CompilerParser.h"
#include "ParseTree.h"
#include "Token.h"
#include <cstddef>
#include <cstring>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

inline bool token_is(ParseTree* a, const string& type, const string& val) {
	if (a==nullptr) return false;
	if (a->getType() == type && a->getValue() == val)
		return true;
	return false;
}
inline bool token_not(ParseTree* a, const string& type, const string& val) {
	if (a==nullptr) return false;
	if (a->getType() != type || a->getValue() != val)
		return true;
	return false;
}

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

	if (t == nullptr)
		throw ParseException();

	if (t->getType() == "keyword") {
		if (gdef::keywords.find(t->getValue()) == gdef::keywords.end())
			throw ParseException();
		
	} else if (t->getType()=="symbol") {
		if (gdef::symbols.find(t->getValue()) == gdef::keywords.end())
			throw ParseException();
		
	} else if (t->getType()=="integerConstant") {
		int x = stoi(t->getType());
		if ( x < 0 || x > 32767)
			throw ParseException();

	} else if (t->getType()=="stringConstant") {
		if (t->getValue().front() != '\"' || t->getValue().back() != '\"')
			throw ParseException();
		
		string v = t->getValue().substr(1,t->getValue().size()-2);
		if (v == "\"" || v == "\n")
			throw ParseException();
		

	} else if (t->getType()=="identifier") {

		// checks if a string consists of only digits, upper/lower case letters and underscore
		auto validstring = [](const string& a) {
			// NOTE THE ADDED PARENTHESIS
			if(a.find_first_not_of("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_()") == string::npos)
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
  if ( tlist.peek_val(0) == "class") { // validation
    if (tlist.peek_val(1) == "Main" || tlist.peek_val(1) == "main")
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
		if(a == nullptr) return false;
		if (a->getType() == "keyword") {
			if (a->getValue() == "static")
				return true;
			if (a->getValue() == "field")
				return true;
		}
		return false;
	};
	
	// for testing if token is subroutine
	auto is_subrt = [](ParseTree* a) {
		if(a == nullptr) return false;
		if (a->getType() == "keyword") {
			if (a->getValue() == "function")
				return true;
			if (a->getValue() == "method")
				return true;
			if (a->getValue() == "constructor")
				return true;
		}
		return false;
	};

	auto is_end = [](ParseTree* a) {
		if(a == nullptr) return true;
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

	if (validateClass(tree) == false) throw ParseException();
	
  return tree;
}

bool CompilerParser::validateClass(ParseTree* tree) {
	vector<ParseTree *> c = tree->getChildren();

	// the class structure ParseTree
	if (tree->getType() != "class" || tree->getValue() != "") 
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
		if (a==nullptr) return true;
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
ParseTree *CompilerParser::compileClassVarDec() { 
	ParseTree *tree = new ParseTree("classVarDec", "");
	tree->addChild(tlist.process_token()); // the field / static decleration
	tree->addChild(tlist.process_token()); // keyword 'type'
	tree->addChild(tlist.process_token()); // an identifier

	auto is_comma = [](ParseTree* a) {
		if (a==nullptr) return true; // break the loop
		if (a->getType() == "symbol"){
			if (a->getValue() == ",")
				return true;
		}
		return false;
	};

	ParseTree *x = tlist.peek();
	while(is_comma(x)) {
		tree->addChild(tlist.process_token()); // add the comma
		tree->addChild(tlist.process_token()); // add the next identifier
		x = tlist.peek();
	}

	tree->addChild(tlist.process_token()); // the semicolon

	if (validateClassVarDec(tree) == false) throw ParseException();
	
	return tree; 
}

bool CompilerParser::validateClassVarDec(ParseTree *tree) {
	vector<ParseTree*> c = tree->getChildren();
	
	if (tree->getType() != "classVarDec" || tree->getValue() != "")
		throw ParseException();
	
	if (c[0]->getType() != "keyword" || (c[0]->getValue() != "static" && c[0]->getValue() != "field"))
		throw ParseException();
	
	
	if (c[1]->getType() != "keyword" || gdef::vartypes.find(c[1]->getValue()) == gdef::vartypes.end())
		throw ParseException();
	
	// identifier list
	for (int i=2; i<c.size()-1; i++) {
		if (i%2 == 0) {
			if (c[i]->getType() != "identifier")
				return false;
		} else {
			if (c[i]->getType() != "symbol" || c[i]->getValue() != ",")
				return false;
		}
	}

	if (c.back()->getType() != "symbol" || c.back()->getValue() != ";")
		return false;
	
	return true;
}

/**
 * Generates a parse tree for a method, function, or constructor
 */
ParseTree *CompilerParser::compileSubroutine() {
	ParseTree *tree = new ParseTree("subroutine", "");

	tree->addChild(tlist.process_token()); // keyword: the subroutine type: function, method or constructor
	tree->addChild(tlist.process_token()); // keyword: the return type
	tree->addChild(tlist.process_token()); // identifier: subroutine name
	tree->addChild(tlist.process_token()); // symbol: '(' opening the parameter list

	tree->addChild(compileParameterList()); // build the parameter list

	tree->addChild(tlist.process_token()); // symbol: ')' ending the parameter list

	tree->addChild(compileSubroutineBody());

	if (validateSubroutine(tree) == false) throw ParseException();
	
	return tree; 
}

bool CompilerParser::validateSubroutine(ParseTree *tree) {
	if (tree->getType() != "subroutine" || tree->getValue() != "")
		return false;
	
	vector<ParseTree*> c = tree->getChildren();

	if (c[0]->getType()!="keyword" || ( // subroutine type definition
		c[0]->getValue()!="method" &&
		c[0]->getValue()!="constructor" &&
		c[0]->getValue()!="function"
	)) return false;

	if (c[1]->getType() == "identifier"){ // subroutine return type
		// do nothing
	} else if (c[1]->getType() != "keyword" || (
		gdef::vartypes.find(c[1]->getValue()) == gdef::vartypes.end() &&
		c[1]->getValue() != "void"
	)) return false;

	if (c[2]->getType() != "identifier")
		return false;
	
	if (c[3]->getType() != "symbol" || c[3]->getValue() != "(")
		return false;
	
	if (c[4]->getType() != "parameterList" || c[4]->getValue() != "")
		return false;
	
	if (c[5]->getType() != "symbol" || c[5]->getValue() != ")")
		return false;
	
	if (c[6]->getType() != "subroutineBody" || c[6]->getValue() != "")
		return false;

	return true;
}

/**
 * Generates a parse tree for a subroutine's parameters
 */
ParseTree *CompilerParser::compileParameterList() {
	ParseTree *tree = new ParseTree("parameterList","");

	auto is_parenthesis = [](ParseTree* a) {
		if (a==nullptr) return true; // break the loop
		if (a->getType() == "symbol"){
			if (a->getValue() == ")")
				return true;
		}
		return false;
	};
	Token* x = tlist.peek();
	while (is_parenthesis(x) == false) {

		tree->addChild(tlist.process_token()); // add the commas, types and identifiers 

		x = tlist.peek();
	}
	
	if(validateParameterList(tree) == false) throw ParseException();

	return tree;
}

bool CompilerParser::validateParameterList(ParseTree *tree) {
	if (tree->getType() != "parameterList" || tree->getValue() != "")
		return false;
	
	vector<ParseTree*> c = tree->getChildren();

	// function is valid if it has no parameters
	if (c.size() == 0)
		return true;
	
	// parameter list is either of length 2 when one parameter, or when length n, n+1 is divisble by 3
	if (c.size() < 2 || (c.size() != 2 && (c.size()+1)%3 != 0))
		return false;

	for (int i=0; i<c.size(); i+=3) {
		if (c[i]->getType() != "keyword" || gdef::vartypes.find(c[i]->getValue()) == gdef::vartypes.end())
			return false;
		if (c[i+1]->getType() != "identifier") // will be last token in param list in the last loop iteration
			return false;
		
		if (i+2 < c.size()) { // skip on last loop iteration as there will be no trailing comma
			if (c[i+2]->getType() != "symbol" || c[i+2]->getValue() != ",")
				return false;
		}
	}

	return true;
}

/**
 * Generates a parse tree for a subroutine's body
 */
ParseTree *CompilerParser::compileSubroutineBody() {
	ParseTree *tree = new ParseTree("subroutineBody", "");

	tree->addChild(tlist.process_token()); // symbol: '{'

	auto is_end = [](ParseTree* a) {
		if(a == nullptr) return true;
		return token_is(a, "symbol", "}");
	};
	ParseTree *x = tlist.peek();
	while(is_end(x) == false) {
		if (x->getType() == "keyword" && x->getValue() == "var") // if is a varDec
			tree->addChild(compileVarDec());
		else
		 tree->addChild(compileStatements());
		x = tlist.peek();
	}
	tree->addChild(tlist.process_token()); // symbol: '}'

	if (validateSubroutineBody(tree) == false) throw ParseException();

	return tree;
}
bool CompilerParser::validateSubroutineBody(ParseTree *tree) {
	vector<ParseTree*> c = tree->getChildren();

	if (c[0]->getType() != "symbol" || c[0]->getValue() != "{")
		return false;
	
	int i=1;
	while(c[i]->getType() != "symbol" && c[i]->getValue() != "}") {
		// these should all only be statements and varDecs which, by this time, are already validated
		if (c[i]->getType() != "varDec" && c[i]->getType() != "statements")
			return false;

		i++;
	}

	if (c[i] != c.back())
		return false;

	return true;
}

/**
 * Generates a parse tree for a variable declaration
 */
ParseTree *CompilerParser::compileVarDec() {
	ParseTree *tree = new ParseTree("varDec","");

	tree->addChild(tlist.process_token()); // keyword: var
	tree->addChild(tlist.process_token()); // keyword: type

	tree->addChild(tlist.process_token()); // the first identifier

	auto is_comma = [](ParseTree* a) {
		if (a==nullptr) return true; // break the loop
		if (a->getType() == "symbol"){
			if (a->getValue() == ",")
				return true;
		}
		return false;
	};
	ParseTree *x = tlist.peek();
	while(is_comma(x)) {
		tree->addChild(tlist.process_token()); // add the comma
		tree->addChild(tlist.process_token()); // add the next identifier
		x = tlist.peek();
	}

	tree->addChild(tlist.process_token()); // the semicolon

	if (validateVarDec(tree) == false) throw ParseException();
	
	return tree; 
}

bool CompilerParser::validateVarDec(ParseTree* tree) {
	vector<ParseTree*> c = tree->getChildren();
	
	if (tree->getType() != "varDec" || tree->getValue() != "")
		throw ParseException();
	
	if (c[0]->getType() != "keyword" || (c[0]->getValue() != "var"))
		throw ParseException();
	
	if (c[1]->getType() != "identifier") { // if the type is not an ADT 
		if (c[1]->getType() != "keyword" || gdef::vartypes.find(c[1]->getValue()) == gdef::vartypes.end())
			throw ParseException();
	}
	
	// identifier list
	for (int i=2; i<c.size()-1; i++) {
		if (i%2 == 0) {
			if (c[i]->getType() != "identifier")
				return false;
		} else {
			if (c[i]->getType() != "symbol" || c[i]->getValue() != ",")
				return false;
		}
	}

	if (c.back()->getType() != "symbol" || c.back()->getValue() != ";")
		return false;
	
	return true;
}

/**
 * Generates a parse tree for a series of statements
 */
ParseTree *CompilerParser::compileStatements() {
	ParseTree *tree = new ParseTree ("statements", "");

	// end of statements block = return statement;
	ParseTree *x = tlist.peek();
	while (token_is(x, "keyword", "return") || token_is(x, "keyword", "let") || token_is(x, "keyword", "do")) {
		if (x->getValue() == "do")
			tree->addChild(compileDo());
		else if (x->getValue() == "let")
			tree->addChild(compileLet());
		else if (x->getValue() == "return")
			tree->addChild(compileReturn());

		x = tlist.peek(); // for next iteration
	}
	// do something here. Check the loop exited for the right reason, ie, why should a block of statements end? next thing is varDec or }?

	return tree;
}

/**
 * Generates a parse tree for a let statement
 */
ParseTree *CompilerParser::compileLet() {
	ParseTree *tree = new ParseTree ("letStatement", "");

	tree->addChild(tlist.process_token()); // keyword: let
	tree->addChild(tlist.process_token()); // an identifier
	tree->addChild(tlist.process_token()); // symbol: =

	tree->addChild(compileExpression()); // the expression to evaluate

	tree->addChild(tlist.process_token()); // symbol: ;

	if (validateLet(tree) == false) throw ParseException();

	return tree;
}

bool CompilerParser::validateLet(ParseTree *tree) {
	if (token_not(tree, "letStatement", ""))
		return false;

	vector<ParseTree*> c = tree->getChildren();

	if (c.size() != 5)
		return false;
	
	
	if (token_not(c[0],"keyword","let"))
		return false; 

	if (c[1]->getType() != "identifier")
		return false;
	
	if (token_not(c[2],"symbol","="))
		return false; 

	if (c[3]->getType() != "expression")
		return false;

	if (token_not(c[4],"symbol",";"))
		return false; 

	return true;
}

/**
 * Generates a parse tree for an if statement
 */
ParseTree *CompilerParser::compileIf() {
	ParseTree *tree = new ParseTree ("ifStatement", "");

	tree->addChild(tlist.process_token()); // keyword: if
	tree->addChild(tlist.process_token()); // symbol: (
	tree->addChild(compileExpression()); // the expression to evaluate
	tree->addChild(tlist.process_token()); // symbol: )
	tree->addChild(tlist.process_token()); // symbol: {
	
	// code block of the if statement. can contain statements and/or varDecs
	auto is_end = [](ParseTree* a) {
		if(a == nullptr) return true;
		return token_is(a, "symbol", "}");
	};
	ParseTree *x = tlist.peek();
	while(is_end(x) == false) {
		if (x->getType() == "keyword" && x->getValue() == "var") // if is a varDec
			tree->addChild(compileVarDec());
		else
		 tree->addChild(compileStatements());
		x = tlist.peek();
	}
	tree->addChild(tlist.process_token()); // symbol: }

	// may be the end, but need to check if there is an else block

	x = tlist.peek();
	if (token_is(x, "keyword", "else")) {
		tree->addChild(tlist.process_token()); // keyword: else
		tree->addChild(tlist.process_token()); // symbol: {
		x = tlist.peek();
		while(is_end(x) == false) {
			if (x->getType() == "keyword" && x->getValue() == "var") // if is a varDec
				tree->addChild(compileVarDec());
			else
				tree->addChild(compileStatements());

			x = tlist.peek();
		}
		if (token_not(tlist.peek(),"symbol","}")) throw ParseException();
		tree->addChild(tlist.process_token()); // symbol: }
	}

	if (token_is(x, "symbol", "{")) throw ParseException(); // an open brace after the if. probably missing an 'else' keyword
	if (validateIf(tree) == false) throw ParseException();

	return tree;
}

bool CompilerParser::validateIf(ParseTree *tree) {
	if (token_not(tree, "ifStatement", ""))
		return false;

	vector<ParseTree*> c = tree->getChildren();

	/*
		6 = if with no statement body, 
		7 = if with no else, 
		9 = if with else but no bodies in either
		10 = if with else but statement body in only one
		11 = if with else and body in both
	*/
	if ( (c.size() == 6) ) {
		if (token_not(c[0],"keyword","if"))
			return false; 

		if (token_not(c[1],"symbol","("))
			return false; 

		if (c[2]->getType() != "expression")
			return false;
		
		if (token_not(c[3],"symbol",")"))
			return false; 

		if (token_not(c[4],"symbol","{"))
			return false;

		if (token_not(c[5],"symbol","}"))
			return false;
	}
	else if ( (c.size() == 7) ) {
		if (token_not(c[0],"keyword","if"))
		return false; 

		if (token_not(c[1],"symbol","("))
			return false; 

		if (c[2]->getType() != "expression")
			return false;
		
		if (token_not(c[3],"symbol",")"))
			return false; 

		if (token_not(c[4],"symbol","{"))
			return false;

		if (c[5]->getType() != "statements" && c[5]->getType() != "varDec")
			return false;

		if (token_not(c[6],"symbol","}"))
			return false;
	}
	else if (c.size() == 9) {
		if (token_not(c[0],"keyword","if"))
			return false; 

		if (token_not(c[1],"symbol","("))
			return false; 

		if (c[2]->getType() != "expression")
			return false;
		
		if (token_not(c[3],"symbol",")"))
			return false; 

		if (token_not(c[4],"symbol","{"))
			return false;

		if (token_not(c[5],"symbol","}"))
			return false;

		if (token_not(c[6],"keyword","else"))
			return false;

		if (token_not(c[7],"symbol","{"))
			return false;

		if (token_not(c[8],"symbol","}"))
			return false;
	}
	else if (c.size() == 10) { // either if or else doesnt contain an expression body, must determine
		if (token_not(c[0],"keyword","if"))
			return false; 

		if (token_not(c[1],"symbol","("))
			return false; 

		if (c[2]->getType() != "expression")
			return false;
		
		if (token_not(c[3],"symbol",")"))
			return false; 

		if (token_not(c[4],"symbol","{"))
			return false;

		if ( token_is(c[5],"symbol", "}") ) {
			if (token_not(c[6],"keyword","else"))
				return false;
			if (token_not(c[7],"symbol","{"))
				return false;
			if (c[8]->getType() != "statements" && c[8]->getType() != "varDec")
				return false;
			if (token_not(c[9],"symbol","}"))
				return false;

		} else if (c[5]->getType() == "statements" || c[5]->getType() == "varDec"){
			if (token_not(c[6],"symbol","}"))
				return false;

			if (token_not(c[7],"keyword","else"))
				return false;

			if (token_not(c[8],"symbol","{"))
				return false;

			if (token_not(c[9],"symbol","}"))
				return false;
		} else return false;

	} else if (c.size() == 11) {
		if (token_not(c[0],"keyword","if"))
			return false; 

		if (token_not(c[1],"symbol","("))
			return false; 

		if (c[2]->getType() != "expression")
			return false;
		
		if (token_not(c[3],"symbol",")"))
			return false; 

		if (token_not(c[4],"symbol","{"))
			return false;

		if (c[5]->getType() != "statements" && c[5]->getType() != "varDec")
			return false;

		if (token_not(c[6],"symbol","}"))
			return false;

		if (token_not(c[7],"keyword","else"))
			return false;

		if (token_not(c[8],"symbol","{"))
			return false;

		if (c[9]->getType() != "statements" && c[9]->getType() != "varDec")
			return false;

		if (token_not(c[10],"symbol","}"))
			return false;

	} else return false;
	
	return true;
}

/**
 * Generates a parse tree for a while statement
 */
ParseTree *CompilerParser::compileWhile() {
	ParseTree *tree = new ParseTree ("whileStatement", "");

	tree->addChild(tlist.process_token()); // keyword: while
	tree->addChild(tlist.process_token()); // symbol: (
	tree->addChild(compileExpression()); // the expression to evaluate
	tree->addChild(tlist.process_token()); // symbol: )
	tree->addChild(tlist.process_token()); // symbol: {
	
	// code block of the if statement. can contain statements and/or varDecs
	auto is_end = [](ParseTree* a) {
		if(a == nullptr) return true;
		return token_is(a, "symbol", "}");
	};
	ParseTree *x = tlist.peek();
	while(is_end(x) == false) {
		if (x->getType() == "keyword" && x->getValue() == "var") // if is a varDec
			tree->addChild(compileVarDec());
		else
		 tree->addChild(compileStatements());
		x = tlist.peek();
	}
	tree->addChild(tlist.process_token()); // symbol: }

	if (validateWhile(tree) == false) throw ParseException();

	return tree;
}
bool CompilerParser::validateWhile(ParseTree *tree) {
	if (token_not(tree, "whileStatement", ""))
		return false;

	vector<ParseTree*> c = tree->getChildren();

	if (c.size() != 7)
		return false;
	
	if (token_not(c[0],"keyword","while"))
		return false; 

	if (token_not(c[1],"symbol","("))
		return false; 

	if (c[2]->getType() != "expression")
		return false;
	
	if (token_not(c[3],"symbol",")"))
		return false; 

	if (token_not(c[4],"symbol","{"))
		return false;

	if (c[5]->getType() != "statements" && c[5]->getType() != "varDec")
		return false;

	if (token_not(c[6],"symbol","}"))
		return false;

	return true;
}

/**
 * Generates a parse tree for a do statement
 */
ParseTree *CompilerParser::compileDo() {
	ParseTree *tree = new ParseTree ("doStatement", "");

	tree->addChild(tlist.process_token()); // keyword: do
	tree->addChild(compileExpression()); // the expression to do
	tree->addChild(tlist.process_token()); // symbol: ;

	if (validateDo(tree) == false) throw ParseException();

	return tree;
}
bool CompilerParser::validateDo(ParseTree *tree) {
	if (token_not(tree, "doStatement", ""))
		return false;

	vector<ParseTree*> c = tree->getChildren();

	if (c.size() != 3)
		return false;
	
	if (token_not(c[0],"keyword","do"))
		return false; 

	if (c[1]->getType() != "expression")
		return false;

	if (token_not(c[2],"symbol",";"))
		return false;

	return true;
}

/**
 * Generates a parse tree for a return statement
 */
ParseTree *CompilerParser::compileReturn() {
	ParseTree *tree = new ParseTree ("returnStatement", "");

	tree->addChild(tlist.process_token()); // keyword: return

	if (token_not(tlist.peek(), "symbol", ";")) { // if this is an expression to evaluate
		tree->addChild(compileExpression()); // the expression to evaluate
	}

	tree->addChild(tlist.process_token()); // symbol: ;

	if (token_not(tlist.peek(),"symbol", "}")) // the next token after a return should always be a }
		throw ParseException();

	if (validateReturn(tree) == false) throw ParseException();

	return tree;
}
bool CompilerParser::validateReturn(ParseTree *tree) {
	if (token_not(tree, "returnStatement", ""))
		return false;

	vector<ParseTree*> c = tree->getChildren();

	if (c.size() == 2){
		if (token_not(c[0],"keyword","return"))
		return false; 

	if (token_not(c[1],"symbol",";"))
		return false;

	} else if (c.size() == 3) {
		if (token_not(c[0],"keyword","return"))
			return false; 

		if (c[1]->getType() != "expression")
			return false;

		if (token_not(c[2],"symbol",";"))
			return false;
	} else return false;
	
	return true;
}

/**
 * Generates a parse tree for an expression
 */
ParseTree *CompilerParser::compileExpression() {
	ParseTree *tree = new ParseTree("expression", "skip"); // TEMPORARY SKIP
	tlist.process_token(); // consume a token
	return tree;
}

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

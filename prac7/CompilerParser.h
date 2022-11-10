#ifndef COMPILERPARSER_H
#define COMPILERPARSER_H

#include <exception>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>

#include "ParseTree.h"
#include "Token.h"

// an abstraction interface for managing the tokens. for scaling later
struct TokenList {
  public:
  TokenList();
  TokenList(std::vector<Token*>);

  Token* process_token(); // used when you want to return the token and consume it
  Token* peek(); // used when you only want to see the next token, there is no processing or deletion from the list
  std::string peek_val(int i);
  std::string peek_type(int i);
  std::string tostring();


  private:
  std::list<Token*> _tks;
};

class CompilerParser {
public:
  CompilerParser(std::vector<Token *> tokens);

  ParseTree *compileProgram();
  ParseTree *compileClass();
  ParseTree *compileClassVarDec();
  ParseTree *compileSubroutine();
  ParseTree *compileParameterList();
  ParseTree *compileSubroutineBody();
  ParseTree *compileVarDec();

  ParseTree *compileStatements();
  ParseTree *compileLet();
  ParseTree *compileIf();
  ParseTree *compileWhile();
  ParseTree *compileDo();
  ParseTree *compileReturn();

  ParseTree *compileExpression();
  ParseTree *compileTerm();
  ParseTree *compileExpressionList();

private:
	bool validateClass(ParseTree*);
  bool validateClassVarDec(ParseTree*);
  bool validateSubroutine(ParseTree*);
  bool validateParameterList(ParseTree*);
  bool validateSubroutineBody(ParseTree*);
  bool validateVarDec(ParseTree*);

  bool validateLet(ParseTree*);
  bool validateIf(ParseTree*);
  bool validateWhile(ParseTree*);
  bool validateDo(ParseTree*);
  bool validateReturn(ParseTree*);

  bool validateExpression(ParseTree*);
  bool validateTerm(ParseTree*);
  bool validateExpressionList(ParseTree*);



  TokenList tlist;
};

class ParseException : public std::exception {
public:
  const char *what();
};

// grammar definition maps
namespace gdef {
	const std::unordered_set<std::string> keywords {
		"class", "constructor", "function", "method", "field", "static", "var",
		"int", "char", "boolean", "void", "true", "false", "null", "this",
		"let","do","if","else","while","return","skip"
	};

	const std::unordered_set<std::string> symbols {
		"{", "}", "(", ")", "[", "]", ".", ",", ";",
		"+", "-", "*", "/",
		"&", "|", "<", ">", "=", "~"
	};

  const std::unordered_set<std::string> vartypes {
    "int", "char", "boolean"
  };

  /*
	  directly maps a keyword token to a ParseTree type (if such a mapping exists)
  */
  const std::unordered_map<std::string, std::string> kw_tk {
    {"class", "class"},
    {"constructor","subroutine"},
    {"function","subroutine"},
    {"method","subroutine"},

    {"field","classVarDec"},
    {"static", "classVarDec"},

    {"var","varDec"},
    {"let","varDec"},

    {"let","letStatement"},
    {"if","ifStatement"},
    {"while","whileStatement"},
    {"do","doStatement"},
    {"return","returnStatement"},
    
    {"skip","expression"},

  };
}

#endif /*COMPILERPARSER_H*/
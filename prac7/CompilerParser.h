#ifndef COMPILERPARSER_H
#define COMPILERPARSER_H

#include <exception>
#include <map>
#include <unordered_set>
#include <vector>

#include "ParseTree.h"
#include "Token.h"

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

  ParseTree *process_token(Token*);

private:
	std::vector<Token*> _tks;

	ParseTree *validateClass(ParseTree*);
  ParseTree *validateClassVarDec(ParseTree*);
  ParseTree *validateSubroutine(ParseTree*);
  ParseTree *validateParameterList(ParseTree*);
  ParseTree *validateSubroutineBody(ParseTree*);
  ParseTree *validatecompileVarDec(ParseTree*);

  ParseTree *validateStatements(ParseTree*);
  ParseTree *validateLet(ParseTree*);
  ParseTree *validateIf(ParseTree*);
  ParseTree *validateWhile(ParseTree*);
  ParseTree *validateDo(ParseTree*);
  ParseTree *validateReturn(ParseTree*);

  ParseTree *validateExpression(ParseTree*);
  ParseTree *validateTerm(ParseTree*);
  ParseTree *validateExpressionList(ParseTree*);

	void rmtk();
};

class ParseException : public std::exception {
public:
  const char *what();
};

namespace mappings {
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
}
/*
	directly maps a token type to a ParseTree type (if such a mapping exists)
*/
const std::map<std::string, std::string> token_tksrees {
  {"class", "class"},

	{"static", "classVarDec"},
	{"field","classVarDec"},

	{"constructor","subroutine"},
	{"function","subroutine"},
	{"method","subroutine"},

	{"var","varDec"},
	{"let","varDec"},

	{"let","letStatement"},
	{"if","ifStatement"},
	{"while","whileStatement"},
	{"do","doStatement"},
	{"return","returnStatement"},
	
	{"skip","expression"},

};

#endif /*COMPILERPARSER_H*/
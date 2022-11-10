#include <iostream>
#include <string>
#include<vector>

#include "CompilerParser.h"
#include "ParseTree.h"
#include "Token.h"

/*
TEMPLATE
bool test() {
	std::vector<Token*> tokens;
	///////////////////////////////////////////////////////////////
	bool validcase = true;
	std::string caseName = "test";
	std::string s = "let a [ skip ] = skip;";
	tokens.push_back(new Token("keyword", "let"));
	tokens.push_back(new Token("identifier", "a"));
	tokens.push_back(new Token("symbol", "["));
	tokens.push_back(new Token("keyword", "skip"));
	tokens.push_back(new Token("symbol", "]"));
	tokens.push_back(new Token("symbol", "="));
	tokens.push_back(new Token("keyword", "skip"));
	tokens.push_back(new Token("symbol", ";"));
	///////////////////////////////////////////////////////////////

	std::cout << "Testing code - Expecting: "<<(validcase?"Valid tree":"error")<<"\n" << s << std::endl<< std::endl;
	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileStatements();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error != validcase){
		return true;
	}

	failedTestCases.push_back(caseName);
	totalFailedCases++;
	return false;
}

*/

int totalFailedCases = 0;
std::vector<std::string> failedTestCases;
const std::string red("\033[0;31m");
const std::string green("\033[0;32m");
const std::string reset("\033[0m");

bool varDecTest1(){

	std::string s = "var int temp;";
	std::cout << "Testing code - Expecting: Valid Tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "var"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "temp"));
    tokens.push_back(new Token("symbol", ";"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileVarDec();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("Var Dec Test 1");
	totalFailedCases++;
	return false;

}

bool varDecTest2(){

	std::string s = "var int a, b;";
	std::cout << "Testing code - Expecting: Valid Tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "var"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ","));
    tokens.push_back(new Token("identifier", "b"));
    tokens.push_back(new Token("symbol", ";"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileVarDec();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("Var Dec Test 2");
	totalFailedCases++;
	return false;

}

bool varDecTest3(){

	std::string s = "static int a, ! b;";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "static"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ","));
    tokens.push_back(new Token("symbol", "!"));
    tokens.push_back(new Token("identifier", "b"));
    tokens.push_back(new Token("symbol", ";"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileVarDec();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	failedTestCases.push_back("Var Dec Test 3");
	totalFailedCases++;
	return false;

}

bool varDecTest4(){

	std::string s = "int var a;";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("keyword", "var"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ";"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileVarDec();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	failedTestCases.push_back("Var Dec Test 4");
	totalFailedCases++;
	return false;

}

bool varDecTest5(){

	std::string s = "var int a";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl << std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "var"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileVarDec();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	failedTestCases.push_back("Var Dec Test 5");
	totalFailedCases++;
	return false;
}

bool varDecTest6(){

	std::string s = "var int a,";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl << std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "var"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ","));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileVarDec();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	totalFailedCases++;
	failedTestCases.push_back("Var Dec Test 6");

	return false;
}

bool varDecTest7(){

	std::string s = "var Test a;";
	std::cout << "Testing code - Expecting: valid tree \n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "var"));
    tokens.push_back(new Token("identifier", "Test"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ";"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileVarDec();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("Var Dec Test 7");
	totalFailedCases++;
	return false;

}


bool classVarDecTest1(){

	std::string s = "static int temp;";
	std::cout << "Testing code - Expecting: Valid Tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "static"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "temp"));
    tokens.push_back(new Token("symbol", ";"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileClassVarDec();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("Class Var Dec Test 1");
	totalFailedCases++;
	return false;

}

bool classVarDecTest2(){

	std::string s = "field int a, b;";
	std::cout << "Testing code - Expecting: Valid Tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "field"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ","));
    tokens.push_back(new Token("identifier", "b"));
    tokens.push_back(new Token("symbol", ";"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileClassVarDec();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("Class Var Dec Test 2");
	totalFailedCases++;
	return false;

}

bool classVarDecTest3(){

	std::string s = "var int a, b;";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "var"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ","));
    tokens.push_back(new Token("identifier", "b"));
    tokens.push_back(new Token("symbol", ";"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileClassVarDec();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}


	failedTestCases.push_back("Class Var Dec Test 3");
	totalFailedCases++;
return false;

}


bool classTest1(){

	std::string s = "class main {}";
	std::cout << "Testing code - Expecting: Valid Tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "class"));
    tokens.push_back(new Token("identifier", "main"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("symbol", "}"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileClass();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("Class Test 1");
	totalFailedCases++;
return false;

}

bool classTest2(){

	std::string s = "class main {field int a, b;}";
	std::cout << "Testing code - Expecting: Valid Tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "class"));
    tokens.push_back(new Token("identifier", "main"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("keyword", "field"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ","));
    tokens.push_back(new Token("identifier", "b"));
    tokens.push_back(new Token("symbol", ";"));
    tokens.push_back(new Token("symbol", "}"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileClass();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("Class Test 2");
	totalFailedCases++;
return false;

}

bool classTest3(){

	std::string s = "class main {field int a, b;";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "class"));
    tokens.push_back(new Token("keyword", "main"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("keyword", "field"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ","));
    tokens.push_back(new Token("identifier", "b"));
    tokens.push_back(new Token("symbol", ";"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileClass();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	failedTestCases.push_back("Class Test 3");
	totalFailedCases++;
return false;

}

bool classTest4(){

	std::string s = "class main {function void test(){}}";
	std::cout << "Testing code - Expecting: Valid Tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "class"));
    tokens.push_back(new Token("identifier", "main"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("keyword", "function"));
    tokens.push_back(new Token("keyword", "void"));
    tokens.push_back(new Token("identifier", "test"));
    tokens.push_back(new Token("symbol", "("));
    tokens.push_back(new Token("symbol", ")"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("symbol", "}"));
    tokens.push_back(new Token("symbol", "}"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileClass();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	totalFailedCases++;
	failedTestCases.push_back("Class Test 4");
return false;

}

bool programTest1(){

	std::string s = "class main {}";
	std::cout << "Testing code - Expecting: Valid Tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "class"));
    tokens.push_back(new Token("identifier", "main"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("symbol", "}"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileProgram();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("Program Test 1");
	totalFailedCases++;
return false;

}


bool programTest2(){

	std::string s = "static int a;";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "static"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ";"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileProgram();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	failedTestCases.push_back("Program Test 2");
	totalFailedCases++;
return false;

}

bool programTest3(){

	std::string s = "class main {}";
	std::cout << "Testing code - Expecting: Valid Tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "class"));
    tokens.push_back(new Token("identifier", "main"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("symbol", "}"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileProgram();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("Program Test 3");
	totalFailedCases++;
return false;

}

bool subroutineTest1(){

	std::string s = "function void myFunc ( int a ) {var int a ;}";
	std::cout << "Testing code - Expecting: Valid Tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "function"));
    tokens.push_back(new Token("keyword", "void"));
    tokens.push_back(new Token("identifier", "myFunc"));
    tokens.push_back(new Token("symbol", "("));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ")"));
    tokens.push_back(new Token("symbol", "{"));
	tokens.push_back(new Token("keyword", "var"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ";"));
    tokens.push_back(new Token("symbol", "}"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileSubroutine();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("Subroutine Test 1");
	totalFailedCases++;
return false;

}

bool subroutineTest2(){

	std::string s = "function void myFunc () {}";
	std::cout << "Testing code - Expecting: Valid Tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "function"));
    tokens.push_back(new Token("keyword", "void"));
    tokens.push_back(new Token("identifier", "myFunc"));
    tokens.push_back(new Token("symbol", "("));
    tokens.push_back(new Token("symbol", ")"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("symbol", "}"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileSubroutine();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("Subroutine Test 2");
	totalFailedCases++;
return false;

}

bool subroutineTest3(){

	std::string s = "function void myFunc () {";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "function"));
    tokens.push_back(new Token("keyword", "void"));
    tokens.push_back(new Token("identifier", "myFunc"));
    tokens.push_back(new Token("symbol", "("));
    tokens.push_back(new Token("symbol", ")"));
    tokens.push_back(new Token("symbol", "{"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileSubroutine();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	failedTestCases.push_back("Subroutine Test 3");
	totalFailedCases++;
return false;

}

bool subroutineTest4() {

	std::string s = "function void myFunc ) {}";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "function"));
    tokens.push_back(new Token("keyword", "void"));
    tokens.push_back(new Token("identifier", "myFunc"));
    tokens.push_back(new Token("symbol", ")"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("symbol", "}"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileSubroutine();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	failedTestCases.push_back("Subroutine Test 4");
	totalFailedCases++;
	return false;

}

bool subroutineTest5(){

	std::string s = "function int test () {}";
	std::cout << "Testing code - Expecting: Valid tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "function"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "test"));
    tokens.push_back(new Token("symbol", "("));
    tokens.push_back(new Token("symbol", ")"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("symbol", "}"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileSubroutine();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("Subroutine Test 5");
	totalFailedCases++;
	return false;

}


bool statementsTest1(){

	std::string s = "let a = skip ; do skip ; return ;";
	std::cout << "Testing code - Expecting: Valid Tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "let"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", "="));
    tokens.push_back(new Token("keyword", "skip"));
    tokens.push_back(new Token("symbol", ";"));
    tokens.push_back(new Token("keyword", "do"));
    tokens.push_back(new Token("keyword", "skip"));
    tokens.push_back(new Token("symbol", ";"));
    tokens.push_back(new Token("keyword", "return"));
    tokens.push_back(new Token("symbol", ";"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileStatements();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("Statements Test 1");
	totalFailedCases++;
return false;

}


bool statementsTest2(){

	std::string s = "let a = skip ; do skip ; return ; var int a;";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "let"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", "="));
    tokens.push_back(new Token("keyword", "skip"));
    tokens.push_back(new Token("symbol", ";"));
    tokens.push_back(new Token("keyword", "do"));
    tokens.push_back(new Token("keyword", "skip"));
    tokens.push_back(new Token("symbol", ";"));
    tokens.push_back(new Token("keyword", "return"));
    tokens.push_back(new Token("symbol", ";"));
	tokens.push_back(new Token("keyword", "var"));
	tokens.push_back(new Token("keyword", "int"));
	tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ";"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileStatements();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	failedTestCases.push_back("Statements Test 2");
	totalFailedCases++;
return false;

}

bool statementsTest3(){

	std::string s = "let a = skip";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "let"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", "="));
    tokens.push_back(new Token("keyword", "skip"));

	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileStatements();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	totalFailedCases++;
	failedTestCases.push_back("Statements Test 3");

return false;

}

bool statementsTest4(){

	std::string s = "do skip";
	std::cout << "Testing code - Expecting: error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "do"));
    tokens.push_back(new Token("keyword", "skip"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileStatements();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	failedTestCases.push_back("Statements Test 4");
	totalFailedCases++;
return false;
}

bool statementsTest5(){

	std::string s = "let a = skip;";
	std::cout << "Testing code - Expecting: Valid Tree\n" << s << std::endl<< std::endl;
  std::vector<Token*> tokens;
	tokens.push_back(new Token("keyword", "let"));
	tokens.push_back(new Token("identifier", "a"));
	tokens.push_back(new Token("symbol", "="));
	tokens.push_back(new Token("keyword", "skip"));
	tokens.push_back(new Token("symbol", ";"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileStatements();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("Statements Test 5");
	totalFailedCases++;
return false;

}
bool statementsTest6(){

	std::string s = "do skip ;";
	std::cout << "Testing code - Expecting: Valid tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "do"));
    tokens.push_back(new Token("keyword", "skip"));
    tokens.push_back(new Token("symbol", ";"));
	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileStatements();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("Statements Test 4");
	totalFailedCases++;
	return false;
}
bool statementsTest7() {
	std::vector<Token*> tokens;
	///////////////////////////////////////////////////////////////
	bool validcase = true;
	std::string s = "let a [ skip ] = skip;";
	tokens.push_back(new Token("keyword", "let"));
	tokens.push_back(new Token("identifier", "a"));
	tokens.push_back(new Token("symbol", "["));
	tokens.push_back(new Token("keyword", "skip"));
	tokens.push_back(new Token("symbol", "]"));
	tokens.push_back(new Token("symbol", "="));
	tokens.push_back(new Token("keyword", "skip"));
	tokens.push_back(new Token("symbol", ";"));
	///////////////////////////////////////////////////////////////

	std::cout << "Testing code - Expecting: "<<(validcase?"Valid tree":"error")<<"\n" << s << std::endl<< std::endl;
	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileStatements();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error != validcase){
		return true;
	}

	failedTestCases.push_back("Statements Test 7");
	totalFailedCases++;
	return false;
}

bool ifTest1(){

	std::string s = "if (skip) {let a = skip; do skip; } else {do skip;}";
	std::cout << "Testing code - Expecting: Valid Tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
  tokens.push_back(new Token("keyword", "if"));
	tokens.push_back(new Token("symbol", "("));
		tokens.push_back(new Token("keyword", "skip"));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", "{"));

    tokens.push_back(new Token("keyword", "let"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", "="));
    tokens.push_back(new Token("keyword", "skip"));
		tokens.push_back(new Token("symbol", ";"));

		tokens.push_back(new Token("keyword", "do"));
    tokens.push_back(new Token("identifier", "skip")); // check this
		tokens.push_back(new Token("symbol", ";"));

	tokens.push_back(new Token("symbol", "}"));
	tokens.push_back(new Token("keyword", "else"));
	tokens.push_back(new Token("symbol", "{"));
		tokens.push_back(new Token("keyword", "do"));
		tokens.push_back(new Token("identifier", "skip")); // check this
		tokens.push_back(new Token("symbol", ";"));
	tokens.push_back(new Token("symbol", "}"));


	bool error = false;


	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileIf();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("if-statement Test 1");
	totalFailedCases++;
	return false;

}

bool ifTest2(){

	std::string s = "if (skip) {} else {}";
	std::cout << "Testing code - Expecting: Valid tree (not really)\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
  tokens.push_back(new Token("keyword", "if"));
	tokens.push_back(new Token("symbol", "("));
		tokens.push_back(new Token("keyword", "skip"));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", "{"));
	tokens.push_back(new Token("symbol", "}"));
	tokens.push_back(new Token("keyword", "else"));
	tokens.push_back(new Token("symbol", "{"));
	tokens.push_back(new Token("symbol", "}"));


	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileIf();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("if-statement Test 2");
	totalFailedCases++;
	return false;
}

bool ifTest3(){

	std::string s = "if (skip) {} {}";
	std::cout << "Testing code - Expecting: error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
  tokens.push_back(new Token("keyword", "if"));
	tokens.push_back(new Token("symbol", "("));
		tokens.push_back(new Token("keyword", "skip"));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", "{"));
	tokens.push_back(new Token("symbol", "}"));
	tokens.push_back(new Token("symbol", "{"));
	tokens.push_back(new Token("symbol", "}"));


	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileIf();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	failedTestCases.push_back("if-statement Test 3");
	totalFailedCases++;
	return false;
}

bool ifTest4(){

	std::string s = "if () {}";
	std::cout << "Testing code - Expecting: valid tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
  tokens.push_back(new Token("keyword", "if"));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", "{"));
	tokens.push_back(new Token("symbol", "}"));


	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileIf();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("if-statement Test 4");
	totalFailedCases++;
	return false;
}

bool ifTest5(){

	std::string s = "if () {";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
  tokens.push_back(new Token("keyword", "if"));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", "{"));


	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileIf();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	failedTestCases.push_back("if-statement Test 5");
	totalFailedCases++;
	return false;
}

bool ifTest6(){

	std::string s = "if () {} else";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
  tokens.push_back(new Token("keyword", "if"));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", "{"));
	tokens.push_back(new Token("symbol", "}"));
	tokens.push_back(new Token("keyword", "else"));


	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileIf();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	failedTestCases.push_back("if-statement Test 6");
	totalFailedCases++;
	return false;
}
bool ifTest7() {
	std::vector<Token*> tokens;
	///////////////////////////////////////////////////////////////
	bool validcase = true;
	std::string caseName = "if test 7";
	std::string s = "if ( skip ) { }";
	tokens.push_back(new Token("keyword", "if"));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("keyword", "skip"));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", "{"));
	tokens.push_back(new Token("symbol", "}"));
	///////////////////////////////////////////////////////////////

	std::cout << "Testing code - Expecting: "<<(validcase?"Valid tree":"error")<<"\n" << s << std::endl<< std::endl;
	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileIf();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error != validcase){
		return true;
	}

	failedTestCases.push_back(caseName);
	totalFailedCases++;
	return false;
}
bool ifTest8() {
	std::vector<Token*> tokens;
	///////////////////////////////////////////////////////////////
	bool validcase = true;
	std::string caseName = "if test 8 (the long nested one)";
	std::string s = "if ( skip ) { if ( skip ) { } else { } } else { if ( skip ) { } else { } }";
	tokens.push_back(new Token("keyword", "if")); 			// if (skip)
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("keyword", "skip"));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", "{"));					// {
		tokens.push_back(new Token("keyword", "if"));			// 		if (skip)
		tokens.push_back(new Token("symbol", "("));
		tokens.push_back(new Token("keyword", "skip"));
		tokens.push_back(new Token("symbol", ")"));
		tokens.push_back(new Token("symbol", "{"));				// 		{
		tokens.push_back(new Token("symbol", "}"));				// 		}
		tokens.push_back(new Token("keyword", "else"));		// 		else
		tokens.push_back(new Token("symbol", "{"));				//		{
		tokens.push_back(new Token("symbol", "}"));				// 		}
		tokens.push_back(new Token("symbol", "}"));				// }
	
	tokens.push_back(new Token("keyword", "else"));			// else
	tokens.push_back(new Token("symbol", "{"));					// {
		tokens.push_back(new Token("keyword", "if"));			//		if (skip)
		tokens.push_back(new Token("symbol", "("));			
		tokens.push_back(new Token("keyword", "skip"));
		tokens.push_back(new Token("symbol", ")"));
		tokens.push_back(new Token("symbol", "{"));				//		{
		tokens.push_back(new Token("symbol", "}"));				// 		}
		tokens.push_back(new Token("keyword", "else"));		// 		else
		tokens.push_back(new Token("symbol", "{"));				//		{
		tokens.push_back(new Token("symbol", "}"));				// 		}

	tokens.push_back(new Token("symbol", "}"));					// }
	///////////////////////////////////////////////////////////////

	std::cout << "Testing code - Expecting: "<<(validcase?"Valid tree":"error")<<"\n" << s << std::endl<< std::endl;
	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileIf();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error != validcase){
		return true;
	}

	failedTestCases.push_back(caseName);
	totalFailedCases++;
	return false;
}

bool whileTest1(){

	std::string s = "while () {";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
  tokens.push_back(new Token("keyword", "while"));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", "{"));


	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileWhile();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	failedTestCases.push_back("while-statement Test 1");
	totalFailedCases++;
	return false;
}
bool whileTest2(){

	std::string s = "while {}";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
  tokens.push_back(new Token("keyword", "while"));
	tokens.push_back(new Token("symbol", "{"));
	tokens.push_back(new Token("symbol", "}"));


	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileWhile();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	failedTestCases.push_back("while-statement Test 2");
	totalFailedCases++;
	return false;
}
bool whileTest3(){

	std::string s = "while (x = 3) }";
	std::cout << "Testing code - Expecting: Error\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
  tokens.push_back(new Token("keyword", "while"));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("identifier", "x"));
	tokens.push_back(new Token("symbol", "="));
	tokens.push_back(new Token("integerConstant", "3"));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", "}"));


	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileWhile();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error){

		return true;
	}

	failedTestCases.push_back("while-statement Test 3");
	totalFailedCases++;
	return false;
}
bool whileTest4(){

	std::string s = "while (x = 3) {let x = y; do y();}";
	std::cout << "Testing code - Expecting: Valid tree\n" << s << std::endl<< std::endl;
    std::vector<Token*> tokens;
  tokens.push_back(new Token("keyword", "while"));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("identifier", "x"));
	tokens.push_back(new Token("symbol", "="));
	tokens.push_back(new Token("integerConstant", "3"));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", "{"));
	tokens.push_back(new Token("keyword", "let"));
	tokens.push_back(new Token("identifier", "x"));
	tokens.push_back(new Token("symbol", "="));
	tokens.push_back(new Token("identifier", "y"));
	tokens.push_back(new Token("symbol", ";"));
	tokens.push_back(new Token("keyword", "do"));
	tokens.push_back(new Token("identifier", "y"));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", ";"));
	tokens.push_back(new Token("symbol", "}"));


	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileWhile();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(!error){

		return true;
	}

	failedTestCases.push_back("while-statement Test 4");
	totalFailedCases++;
	return false;
}

bool whileTest5() {
	std::vector<Token*> tokens;
	///////////////////////////////////////////////////////////////
	bool validcase = true;
	std::string caseName = "while test 5";
	std::string s = "while ( skip ) {}";
	tokens.push_back(new Token("keyword", "while"));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("keyword", "skip"));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", "{"));
	tokens.push_back(new Token("symbol", "}"));
	///////////////////////////////////////////////////////////////

	std::cout << "Testing code - Expecting: "<<(validcase?"Valid tree":"error")<<"\n" << s << std::endl<< std::endl;
	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileWhile();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error != validcase){
		return true;
	}

	failedTestCases.push_back(caseName);
	totalFailedCases++;
	return false;
}


bool expressionTest1() {
	std::vector<Token*> tokens;
	///////////////////////////////////////////////////////////////
	bool validcase = true;
	std::string caseName = "expression test 1";
	std::string s = "1 + ( a + b )";
	tokens.push_back(new Token("integerConstant", "1"));
	tokens.push_back(new Token("symbol", "+"));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("identifier", "a"));
	tokens.push_back(new Token("symbol", "+"));
	tokens.push_back(new Token("identifier", "b"));
	tokens.push_back(new Token("symbol", ")"));
	///////////////////////////////////////////////////////////////

	std::cout << "Testing code - Expecting: "<<(validcase?"Valid tree":"error")<<"\n" << s << std::endl<< std::endl;
	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileExpression();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error != validcase){
		return true;
	}

	failedTestCases.push_back(caseName);
	totalFailedCases++;
	return false;
}
bool expressionTest2() {
	std::vector<Token*> tokens;
	///////////////////////////////////////////////////////////////
	bool validcase = true;
	std::string caseName = "expression test 2";
	std::string s = "Main . myFunc ( 1 , Hello )";
	tokens.push_back(new Token("identifier", "Main"));
	tokens.push_back(new Token("symbol", "."));
	tokens.push_back(new Token("identifier", "myFunc"));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("integerConstant", "1"));
	tokens.push_back(new Token("symbol", ","));
	tokens.push_back(new Token("identifier", "Hello"));
	tokens.push_back(new Token("symbol", ")"));
	///////////////////////////////////////////////////////////////

	std::cout << "Testing code - Expecting: "<<(validcase?"Valid tree":"error")<<"\n" << s << std::endl<< std::endl;
	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileTerm();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error != validcase){
		return true;
	}

	failedTestCases.push_back(caseName);
	totalFailedCases++;
	return false;
}
bool expressionTest3() {
	std::vector<Token*> tokens;
	///////////////////////////////////////////////////////////////
	bool validcase = true;
	std::string caseName = "expression test 3";
	std::string s = "( ( a + ( 1 - c ) ) > 5 ) = true";
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("identifier", "a"));
	tokens.push_back(new Token("symbol", "+"));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("integerConstant", "1"));
	tokens.push_back(new Token("symbol", "-"));
	tokens.push_back(new Token("identifier", "c"));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", ">"));
	tokens.push_back(new Token("integerConstant", "5"));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", "="));
	tokens.push_back(new Token("keyword", "true"));
	///////////////////////////////////////////////////////////////

	std::cout << "Testing code - Expecting: "<<(validcase?"Valid tree":"error")<<"\n" << s << std::endl<< std::endl;
	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileExpression();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error != validcase){
		return true;
	}

	failedTestCases.push_back(caseName);
	totalFailedCases++;
	return false;
}
bool expressionTest4() {
	std::vector<Token*> tokens;
	///////////////////////////////////////////////////////////////
	bool validcase = true;
	std::string caseName = "expression test 4";
	std::string s = "myFunc ( 1 , Hello , \"hi\" )";
	tokens.push_back(new Token("identifier", "myFunc"));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("integerConstant", "1"));
	tokens.push_back(new Token("symbol", ","));
	tokens.push_back(new Token("identifier", "Hello"));
	tokens.push_back(new Token("symbol", ","));
	tokens.push_back(new Token("stringConstant", "\"hi\""));
	tokens.push_back(new Token("symbol", ")"));
	///////////////////////////////////////////////////////////////

	std::cout << "Testing code - Expecting: "<<(validcase?"Valid tree":"error")<<"\n" << s << std::endl<< std::endl;
	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileTerm();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error != validcase){
		return true;
	}

	failedTestCases.push_back(caseName);
	totalFailedCases++;
	return false;
}


bool expressionListTest1() {
	std::vector<Token*> tokens;
	///////////////////////////////////////////////////////////////
	bool validcase = true;
	std::string caseName = "expression list test 1";
	std::string s = "1 + ( a + b ) , ( 3 - x ) + b";
	tokens.push_back(new Token("integerConstant", "1"));
	tokens.push_back(new Token("symbol", "+"));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("identifier", "a"));
	tokens.push_back(new Token("symbol", "+"));
	tokens.push_back(new Token("identifier", "b"));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", ","));
	tokens.push_back(new Token("symbol", "("));
	tokens.push_back(new Token("integerConstant", "3"));
	tokens.push_back(new Token("symbol", "-"));
	tokens.push_back(new Token("identifier", "x"));
	tokens.push_back(new Token("symbol", ")"));
	tokens.push_back(new Token("symbol", "+"));
	tokens.push_back(new Token("identifier", "b"));
	///////////////////////////////////////////////////////////////

	std::cout << "Testing code - Expecting: "<<(validcase?"Valid tree":"error")<<"\n" << s << std::endl<< std::endl;
	bool error = false;

	CompilerParser parser = CompilerParser(tokens);
	try {

		ParseTree* tree = parser.compileExpressionList();
		std::cout << tree->tostring();
	} catch (ParseException e) {
		error = true;
		std::cout << "Error while parsing!\n";
	}

	if(error != validcase){
		return true;
	}

	failedTestCases.push_back(caseName);
	totalFailedCases++;
	return false;
}

void printResult(bool result, int testNum){

	if(result){
		std::cout << green << std::endl;
	}else{
		std::cout << red << std::endl;
	}

	(result) ? std::cout << "Test " << testNum << " passed!\n\n" : std::cout << "Test " << testNum << " failed!!!!!\n\n";

	std::cout << reset << std::endl;

}

int main(int argc, const char *argv[]){
	int i = 1;

	std::cout << "=========================\n";
	std::cout << "STARTING VARDEC TESTS\n";
	std::cout << "=========================\n";
	printResult(varDecTest1(), i++);
	printResult(varDecTest2(), i++);
	printResult(varDecTest3(), i++);
	printResult(varDecTest4(), i++);
	printResult(varDecTest5(), i++);
	printResult(varDecTest6(), i++);
	printResult(varDecTest7(), i++);

	std::cout << "=========================\n";
	std::cout << "STARTING CLASSVARDEC TESTS\n";
	std::cout << "=========================\n";
	i = 1;
	printResult(classVarDecTest1(), i++);
	printResult(classVarDecTest2(), i++);
	printResult(classVarDecTest3(), i++);

	std::cout << "=========================\n";
	std::cout << "STARTING CLASS TESTS\n";
	std::cout << "=========================\n";
	i = 1;
	printResult(classTest1(), i++);
	printResult(classTest2(), i++);
	printResult(classTest3(), i++);
	printResult(classTest4(), i++);

	std::cout << "=========================\n";
	std::cout << "STARTING PROGRAM TESTS\n";
	std::cout << "=========================\n";
	i = 1;
	printResult(programTest1(), i++);
	printResult(programTest2(), i++);

	std::cout << "=========================\n";
	std::cout << "STARTING SUBROUTINE TESTS\n";
	std::cout << "=========================\n";
	i = 1;
	printResult(subroutineTest1(), i++);
	printResult(subroutineTest2(), i++);
	printResult(subroutineTest3(), i++);
	printResult(subroutineTest4(), i++);
	printResult(subroutineTest5(), i++);

	std::cout << "=========================\n";
	std::cout << "STARTING STATEMENTS TESTS\n";
	std::cout << "=========================\n";
	i = 1;
	printResult(statementsTest1(), i++);
	printResult(statementsTest2(), i++);
	printResult(statementsTest3(), i++);
	printResult(statementsTest4(), i++);
	printResult(statementsTest5(), i++);
	printResult(statementsTest6(), i++);
	printResult(statementsTest7(), i++);
	

	std::cout << "=========================\n";
	std::cout << "STARTING IF-STATEMENT TESTS\n";
	std::cout << "=========================\n";
	i = 1;
	printResult(ifTest1(), i++);
	printResult(ifTest2(), i++);
	printResult(ifTest3(), i++);
	printResult(ifTest4(), i++);
	printResult(ifTest5(), i++);
	printResult(ifTest6(), i++);
	printResult(ifTest7(), i++);
	printResult(ifTest8(), i++);

	std::cout << "=========================\n";
	std::cout << "STARTING WHILE-STATEMENT TESTS\n";
	std::cout << "=========================\n";
	i = 1;
	printResult(whileTest1(), i++);
	printResult(whileTest2(), i++);
	printResult(whileTest3(), i++);
	printResult(whileTest4(), i++);
	printResult(whileTest5(), i++);

	std::cout << "=========================\n";
	std::cout << "STARTING EXPRESSION TESTS\n";
	std::cout << "=========================\n";
	i = 1;
	printResult(expressionTest1(), i++);
	printResult(expressionTest2(), i++);
	printResult(expressionTest3(), i++);
	printResult(expressionTest4(), i++);

	std::cout << "=========================\n";
	std::cout << "STARTING EXPRESSION LIST TESTS\n";
	std::cout << "=========================\n";
	i = 1;
	printResult(expressionListTest1(), i++);

	std::cout << "=========================\n";
	std::cout << "TEST SUMMARY\n";
	std::cout << "=========================\n";
	if(totalFailedCases > 0){
		std::cout << red << std::endl;
	}else {
		std::cout << green << std::endl;
	}
	std::cout << "TEST CASES FAILED: " << totalFailedCases << std::endl;
	for (auto &&fail : failedTestCases){
		std::cout << fail << std::endl;

	}

	std::cout << reset << std::endl;

	return 0;
}
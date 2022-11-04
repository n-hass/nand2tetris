#include <iostream>
#include <string>
#include <vector>

#include "../../CompilerParser.h"
#include "../../ParseTree.h"
#include "../../Token.h"


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

	return false;

}

void printResult(bool result, int testNum){

	(result) ? std::cout << "Test " << testNum << " passed!\n\n" : std::cout << "Test " << testNum << " failed!!!!!\n\n";

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


	return 0;
}


#include <iostream>
#include <vector>

#include "CompilerParser.h"
#include "Token.h"

using namespace std;

int main(int argc, char *argv[]) {
    /* Tokens for:
     *     class MyClass {
     *
     *     }
     */
    vector<Token*> tokens;
    tokens.push_back(new Token("keyword", "class"));
    tokens.push_back(new Token("identifier", "Main"));
    tokens.push_back(new Token("symbol", "{"));

    // tokens.push_back(new Token("keyword", "field"));
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "test"));
    // tokens.push_back(new Token("symbol", ";"));

    // tokens.push_back(new Token("keyword", "method"));
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "foo"));
    // tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "x"));
    // tokens.push_back(new Token("symbol", ","));
    // tokens.push_back(new Token("keyword", "char"));
    // tokens.push_back(new Token("identifier", "y"));
    // tokens.push_back(new Token("symbol", ")"));

    tokens.push_back(new Token("keyword", "function"));
    tokens.push_back(new Token("keyword", "void"));
    tokens.push_back(new Token("identifier", "test"));
    tokens.push_back(new Token("symbol", "("));
    // tokens.push_back(new Token("keyword", "int"));
    // tokens.push_back(new Token("identifier", "x"));
    tokens.push_back(new Token("symbol", ")"));
    tokens.push_back(new Token("symbol", "{"));

        // tokens.push_back(new Token("keyword", "var"));
        // tokens.push_back(new Token("keyword", "int"));
        // tokens.push_back(new Token("identifier", "x"));
        // tokens.push_back(new Token("symbol", ";"));

        // tokens.push_back(new Token("keyword", "let"));
        // tokens.push_back(new Token("identifier", "x"));
        // tokens.push_back(new Token("symbol", "="));
        // tokens.push_back(new Token("integerConstant", "3"));
        // tokens.push_back(new Token("symbol", ";"));

        // tokens.push_back(new Token("keyword", "return"));
        // tokens.push_back(new Token("identifier", "x"));
        // tokens.push_back(new Token("symbol", ";"));

    tokens.push_back(new Token("symbol", "}"));

    tokens.push_back(new Token("symbol", "}"));

    try {
        CompilerParser parser(tokens);
        ParseTree* result = parser.compileProgram();
        if (result != NULL){
            cout << result->tostring() << endl;
        }
    } catch (ParseException e) {
        cout << "Error Parsing!" << endl;
    }
}
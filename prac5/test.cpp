#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "Assembler.h"
#include "SymbolTable.h"

using namespace std;

/** 
 * A quick-and-dirty driver. 
 * When testing your code, we encourage you to also write code to cheeck individual functions
 * as the autograder will do
 */
int main(int argc, char** argv) {

    SymbolTable symbolTable;
    Assembler assembler;
    vector<string> instructionList;

    // Open file
    fstream file;
    file.open("/Users/nh/My Drive (nickhassan01@gmail.com)/Uni/programs/2022/s2/cs/prac5/tests/Mult.asm", ios::in);
    
    // Read line-by-line
    string line;
    while (getline(file, line)) {
        /* remove comments */
        string::size_type idx = line.find("//");  // find start of "//"
        string lineRmComm = line.substr(0, idx);
        if (lineRmComm.size() == 0) continue;  // skip empty line
        /* remove spaces */
        string::iterator str_iter = remove(lineRmComm.begin(), lineRmComm.end(), ' ');
        lineRmComm.erase(str_iter, lineRmComm.end());
        instructionList.push_back(lineRmComm);
    }
    file.close();
    

    // Get array of instructions
    string instructions[instructionList.size()];
    copy(instructionList.begin(), instructionList.end(), instructions);

    // First pass
    assembler.doFirstPass(&symbolTable, instructions, instructionList.size());
    // Second pass
    string code = assembler.doSecondPass(&symbolTable, instructions, instructionList.size());
    // Print output
    cout << code << endl;
    
}
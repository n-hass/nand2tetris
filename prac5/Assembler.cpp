#include "Assembler.h"
#include "SymbolTable.h"

#include <cctype>
#include <string>
#include <bitset>

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

void eraseSubStr(string& a, const string& b) {
	size_t pos = a.find(b);

	if (pos != string::npos)
		a.erase(pos, b.length());
	
}

/**
 * Assembler constructor
 */
Assembler::Assembler() {
    // Your code here
}

/**
 * Assembler destructor
 */
Assembler::~Assembler() {
    // Your code here
}

/**
 * Assembler first pass; populates symbol table with label locations.
 * DOES NOT substitute 
 * @param symbolTable The symbol table to populate.
 * @param instructions An array of the assembly language instructions.
 * @param numOfInst number of inststructions
 */
void Assembler::doFirstPass(SymbolTable* symbolTable, string instructions[], int numOfInst) {
    int j=0;
    for (int i=0; i<numOfInst; i++) {

				if(str_contains(instructions[i],'\r') && instructions[i].length() == 1)
					continue;

        if ( parseInstructionType(instructions[i]) == L_INSTRUCTION ) {
						string l = instructions[i];
            symbolTable->addSymbol (
                instructions[i].substr(l.find_first_of('(')+1, l.find_last_of(')') - l.find_first_of('(') - 1) , j
            );
        } 
        else j++;
    }
}

/**
 * Translates a set of instructions to machine code.
 *
 * @param instructions An array of the assembly language instructions to be converted to machine code.
 * @param symbolTable The symbol table to reference/update.
 * @return A string containing the generated machine code as lines of 16-bit binary instructions.
 */
string Assembler::doSecondPass(SymbolTable* symbolTable, string instructions[], int numOfInst) {
		this->ST = symbolTable;
    string code = "";
		string comp,dest,jump, original;

    for (int i=0; i<numOfInst; i++) {
        string ln = instructions[i];
				original = ln;

        switch (parseInstructionType(ln)){
          case A_INSTRUCTION:
            ln = parseAInst(ln);
						code = code+"\n"+ln;
          break;
            
          case C_INSTRUCTION:
          	ln = parseCInst(ln);
						comp = ln.substr(3,7);
						dest = ln.substr(10,3);
						jump = ln.substr(13,3);

						code = code+"\n"+ln;
          break;
            
          default: break; // do nothing
        }

        
    }

		code.erase(0,1); // consume the leading newline
    return code;
}

/**
 * Parses the type of the provided instruction
 * @param instruction The assembly language representation of an instruction.
 * @return The type of the instruction (A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION, NULL)
 */
Assembler::InstructionType Assembler::parseInstructionType(string inst) {
    if (inst[0] == '(') 
        return L_INSTRUCTION;
    
    if (inst[0] == '@') 
        return A_INSTRUCTION;
    
    if ( (inst.find("=") != string::npos) || (inst.find(";") != string::npos) ) // contains = or contains ;
        return C_INSTRUCTION;

    return NULL_INSTRUCTION;
}

/**
 * Parses the destination of the provided C-instruction
 * @param instruction The assembly language representation of a C-instruction.
 * @return The destination of the instruction (A, D, M, AM, AD, MD, AMD, NULL)
 */
Assembler::InstructionDest Assembler::parseInstructionDest(string inst) {
    
    int mask = 0; // a bitmask for the dest enum

    if (inst.find("=") != string::npos) {
        string t = inst.substr(0,inst.find("="));

        if (t.find("M") != string::npos)
            mask = 1;
        if (t.find("D") != string::npos)
            mask += 2;
        if (t.find("A") != string::npos)
            mask += 4;
    }

    return static_cast<InstructionDest>(mask);
}

/**
 * Parses the jump condition of the provided C-instruction
 * @param instruction The assembly language representation of a C-instruction.
 * @return The jump condition for the instruction (JLT, JGT, JEQ, JLE, JGE, JNE, JMP, NULL)
 */
Assembler::InstructionJump Assembler::parseInstructionJump(string inst) {
    // Your code here:
    // for example if "JLT" appear at the comp field return enum label JLT
   if (str_contains(inst, "JLT"))
      return JLT;
   if (str_contains(inst, "JGT"))
      return JGT;
   if (str_contains(inst, "JEQ"))
      return JEQ;
   if (str_contains(inst, "JLE"))
      return JLE;
   if (str_contains(inst, "JGE"))
      return JGE;
   if (str_contains(inst, "JNE"))
      return JNE;
   if (str_contains(inst, "JMP"))
      return JMP;

   return NULL_JUMP;
}

/**
 * Parses the computation/op-code of the provided C-instruction
 * @param instruction The assembly language representation of a C-instruction.
 * @return The computation/op-code of the instruction (CONST_0, ... ,D_ADD_A , ... , NULL)
 */
Assembler::InstructionComp Assembler::parseInstructionComp(string inst) {
    string comp = inst.substr(
        inst.find('=') + 1,
        inst.find(';') - inst.find('=') - 1
    );

    auto i = compStrEnum.find(comp);

    if (i==compStrEnum.end())
        return NULL_COMP;
    
    return compStrEnum.at(comp);
}

/**
 * Parses the symbol of the provided A/L-instruction
 * @param instruction The assembly language representation of a A/L-instruction.
 * @return A string containing either a label name (L-instruction),
 *         a variable name (A-instruction), or a constant integer value (A-instruction)
 */
string Assembler::parseSymbol(string inst) {
	auto type = parseInstructionType(inst);
	eraseSubStr(inst, "\r");
	

	inst.erase(0,1);
	if (type == L_INSTRUCTION) {
		inst.pop_back();
		return inst;
	}
	if (type == A_INSTRUCTION) {
		return inst;
	}

	return "";
}

/**
 * Generates the binary bits of the dest part of a C-instruction
 * @param dest The destination of the instruction
 * @return A string containing the 3 binary dest bits that correspond to the given dest value.
 */
string Assembler::translateDest(InstructionDest dest) {
	return destMach.at(dest);
}

/**
 * Generates the binary bits of the jump part of a C-instruction
 * @param jump The jump condition for the instruction
 * @return A string containing the 3 binary jump bits that correspond to the given jump value.
 */
string Assembler::translateJump(InstructionJump jump) {
  return jumpMach.at(jump);
}

/**
 * Generates the binary bits of the computation/op-code part of a C-instruction
 * @param comp The computation/op-code for the instruction
 * @return A string containing the 7 binary computation/op-code bits that correspond to the given comp value.
 */
string Assembler::translateComp(InstructionComp comp) {	
	return compEnumMach.at(comp);
}

bool isNum(const string& s) {
    for (int i=0; i<s.length(); i++){
        if (isdigit(s[i]) == 0) return false;
    }
    return true;
}

/**
 * Generates the binary bits for an A-instruction, parsing the value, or looking up the symbol name.
 * @param symbol A string containing either a label name, a variable name, or a constant integer value
 * @param symbolTable The symbol table for looking up label/variable names
 * @return A string containing the 15 binary bits that correspond to the given sybmol.
 */
string Assembler::translateSymbol(string symbol, SymbolTable* symbolTable) {
  
	string AVal = parseSymbol(symbol);

	if (isNum(AVal)) { // is a constant num
		return bitset<15>( stoi(AVal) ).to_string();
	}
	else { // is a symbol
		int symcode = ST->getSymbol(AVal);
		if (parseInstructionType(symbol) == A_INSTRUCTION && symcode == -1) { // is an a instruction and symbol not in table
			ST->newVar(AVal);
			symcode = ST->getSymbol(AVal);
		}
		return bitset<15>(symcode).to_string();
	}

}

string Assembler::parseAInst(string inst) {
	return "0" + translateSymbol(inst, this->ST);
}

string Assembler::parseCInst(string inst) {

  auto comp = parseInstructionComp(inst);
  auto dest = parseInstructionDest(inst);
  auto jump = parseInstructionJump(inst);
  

	return ("111" + translateComp(comp) + translateDest(dest) + translateJump(jump));
}
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>

#include "SymbolTable.h"

using namespace std;

class Assembler {
    private:
        SymbolTable* ST;

   public:
    /** Instruction types */
    enum InstructionType {
        A_INSTRUCTION,
        C_INSTRUCTION,
        L_INSTRUCTION,
        NULL_INSTRUCTION
    };

    /** C-instruction destinations */
    enum InstructionDest {
        NULL_DEST,
        M,
        D,
        MD,
        A,
        AM,
        AD,
        AMD
    };

    /** C-instruction jump conditions */
    enum InstructionJump {
        JLT,
        JGT,
        JEQ,
        JLE,
        JGE,
        JNE,
        JMP,
        NULL_JUMP
    };

    /** C-instruction computations/op-codes */
    enum InstructionComp {
        CONST_0,
        CONST_1,
        CONST_NEG_1,
        VAL_A,
        VAL_M,
        VAL_D,
        NOT_A,
        NOT_M,
        NOT_D,
        NEG_A,
        NEG_M,
        NEG_D,
        A_ADD_1,
        M_ADD_1,
        D_ADD_1,
        A_SUB_1,
        M_SUB_1,
        D_SUB_1,
        D_ADD_A,
        D_ADD_M,
        D_SUB_A,
        D_SUB_M,
        A_SUB_D,
        M_SUB_D,
        D_AND_A,
        D_AND_M,
        D_OR_A,
        D_OR_M,
        NULL_COMP
    };
    
    // two maps for parsing the computation. this could be better optimised, but at least all the computation opcodes are abstracted from the parsing functions
    const map<InstructionComp, string> compEnumMach = {
        {CONST_0, "0101010"},
        {CONST_1, "0111111"},
        {CONST_NEG_1, "0111010"},
        {VAL_D, "0001100"},
        {VAL_A, "0110000"},
        {NOT_D, "0001101"},
        {NOT_A, "0110001"},
        {NEG_D, "0001111"},
        {NEG_A, "0110011"},
        {D_ADD_1, "0011111"},
        {A_ADD_1, "0110111"},
        {D_SUB_1, "0001110"},
        {A_SUB_1, "0110010"},
        {D_ADD_A, "0000010"},
        {D_SUB_A, "0010011"},
        {A_SUB_D, "0000111"},
        {D_AND_A, "0000000"},
        {D_OR_A, "0010101"},
        {VAL_M, "1110000"},
        {NOT_M, "1110001"},
        {NEG_M, "1110011"},
        {M_ADD_1, "1110111"},
        {M_SUB_1, "1110010"},
        {D_ADD_M, "1000010"},
        {D_SUB_M, "1010011"},
        {M_SUB_D, "1000111"},
        {D_AND_M, "1000000"},
        {D_AND_M, "1000000"},  
        {D_OR_M, "1010101"},
    };
    const map<string, InstructionComp> compStrEnum = {
        {"0", CONST_0},
        {"1", CONST_1},
        {"-1", CONST_NEG_1},
        {"D", VAL_D},
        {"A", VAL_A},
        {"!D", NOT_D},
        {"!A", NOT_A},
        {"-D", NEG_D},
        {"-A", NEG_A},
        {"D+1", D_ADD_1},
        {"1+D", D_ADD_1},
        {"A+1", A_ADD_1},
        {"1+A", A_ADD_1},
        {"D-1", D_SUB_1},
        {"A-1", A_SUB_1},
        {"D+A", D_ADD_A},
        {"A+D", D_ADD_A},
        {"D-A", D_SUB_A},
        {"A-D", A_SUB_D},
        {"D&A", D_AND_A},
        {"A&D", D_AND_A},  // commutative
        {"D|A", D_OR_A},
        {"A|D", D_OR_A},  // commutative
        {"M", VAL_M},
        {"!M", NOT_M},
        {"-M", NEG_M},
        {"M+1", M_ADD_1},
        {"1+M", M_ADD_1},
        {"M-1", M_SUB_1},
        {"D+M", D_ADD_M},
        {"M+D", D_ADD_M},  // commutative
        {"D-M", D_SUB_M},
        {"M-D", M_SUB_D},
        {"D&M", D_AND_M},
        {"M&D", D_AND_M},  // commutative
        {"D|M", D_OR_M},
        {"M|D", D_OR_M},
    };

    // dest to machine code definitions
    const map<InstructionDest, string> destMach {
        {NULL_DEST, "000"},
        {M, "001"},
        {D, "010"},
        {MD, "011"},
        {A, "100"},
        {AM, "101"},
        {AD, "110"},
        {AMD, "111"}
    };

    // jump to machine code definitions
    const map<InstructionJump, string> jumpMach {
        {NULL_JUMP, "000"},
        {JGT, "001"},
        {JEQ, "010"},
        {JGE, "011"},
        {JLT, "100"},
        {JNE, "101"},
        {JLE, "110"},
        {JMP, "111"}
    };

    /** Practical Assignment 5 methods */
    Assembler();
    Assembler(SymbolTable*);
    ~Assembler();
    
    void doFirstPass(SymbolTable* symbolTable, string instructions[], int numOfInst);
    string doSecondPass(SymbolTable* symbolTable, string instructions[], int numOfInst);

    string parseAInst(string inst);
    string parseCInst(string inst);

    InstructionType parseInstructionType(string instruction);
    InstructionDest parseInstructionDest(string instruction);
    InstructionJump parseInstructionJump(string instruction);
    InstructionComp parseInstructionComp(string instruction);
    string parseSymbol(string instruction);

    string translateDest(InstructionDest dest);
    string translateJump(InstructionJump jump);
    string translateComp(InstructionComp comp);
    string translateSymbol(string symbol, SymbolTable* symbolTable);
};

#endif /* ASSEMBLER_H */
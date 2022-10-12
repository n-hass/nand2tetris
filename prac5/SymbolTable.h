#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "types.h"
#include <map>      // indexable dictionary
#include <string>   // process c++ string

using namespace std;

class SymbolTable {
   public:
    SymbolTable();
    ~SymbolTable();

    bool newVar(string symbol);
    void addSymbol(string symbol, u16 value);
    int getSymbol(string symbol);

    private:
    map<string, u16> t; // the symbol table
    u32 tN;
};

#endif /* SYMBOL_TABLE_H */
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

class SymbolTable {
public:
	SymbolTable();
	// Constructor, creates a new empty symbol table, and pre-populate it

	void addEntry(string symbol, int address);
	// Add the pair (symbol, address) to the table

	bool contains(string symbol);
	// Does the symbol table contain the given symbol?

	int getAddress(string symbol);
	// Returns the address associated with the symbol

private:
	map <string, int> symbolTable;
};

#endif // SYMBOLTABLE_H

#include "SymbolTable.h"

using namespace std;

SymbolTable::SymbolTable() {
	// Pre-populate the symbol table
	symbolTable["SP"] = 0;
	symbolTable["LCL"] = 1;
	symbolTable["ARG"] = 2;
	symbolTable["THIS"] = 3;
	symbolTable["THAT"] = 4;

	symbolTable["R0"] = 0;
	symbolTable["R1"] = 1;
	symbolTable["R2"] = 2;
	symbolTable["R3"] = 3;
	symbolTable["R4"] = 4;
	symbolTable["R5"] = 5;
	symbolTable["R6"] = 6;
	symbolTable["R7"] = 7;
	symbolTable["R8"] = 8;
	symbolTable["R9"] = 9;
	symbolTable["R10"] = 10;
	symbolTable["R11"] = 11;
	symbolTable["R12"] = 12;
	symbolTable["R13"] = 13;
	symbolTable["R14"] = 14;
	symbolTable["R15"] = 15;

	symbolTable["SCREEN"] = 16384;
	symbolTable["KBD"] = 24576;
}

void SymbolTable::addEntry(string symbol, int address) {
	// Add the pair (symbol, address) to the table
	symbolTable[symbol] = address;
}

bool SymbolTable::contains(string symbol) {
	// Does the symbol table contain the given symbol?
	return (symbolTable.find(symbol) != symbolTable.end());
}

int SymbolTable::getAddress(string symbol) {
	// Returns the address associated with the symbol
	if (symbolTable.find(symbol) == symbolTable.end()) {
		throw runtime_error("Error: '" + symbol + "' " + " is not found.");
	}
	else {
		return symbolTable[symbol];
	}
}
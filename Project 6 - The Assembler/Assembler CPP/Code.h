#ifndef CODE_H
#define CODE_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Code {
public:
	Code();		// Constructor

	string destBinary(string destMnemonic);
	// Returns the 3-bit binary code of the dest mnemonic

	string compBinary(string compMnemonic);
	// Returns the 7-bit binary code of the comp mnemonic

	string jumpBinary(string jumpMnemonic);
	// Returns the 3-bit binary code of the jump mnemonic

private:
	map <string, string> destTable;
	map <string, string> compTable;
	map <string, string> jumpTable;
};

#endif // CODE_H

#include "Code.h"

using namespace std;

Code::Code() {
	// Populate the translation map tables
	destTable[""]	 = "000";
	destTable["M"]	 = "001";
	destTable["D"]	 = "010";
	destTable["MD"]	 = "011";
	destTable["A"]	 = "100";
	destTable["AM"]	 = "101";
	destTable["AD"]	 = "110";
	destTable["AMD"] = "111";

	compTable["0"]	 = "0101010";
	compTable["1"]	 = "0111111";
	compTable["-1"]	 = "0111010";
	compTable["D"]	 = "0001100";
	compTable["A"]	 = "0110000";
	compTable["!D"]	 = "0001101";
	compTable["!A"]	 = "0110001";
	compTable["-D"]	 = "0001111";
	compTable["-A"]	 = "0110011";
	compTable["D+1"] = "0011111";
	compTable["A+1"] = "0110111";
	compTable["D-1"] = "0001110";
	compTable["A-1"] = "0110010";
	compTable["D+A"] = "0000010";
	compTable["D-A"] = "0010011";
	compTable["A-D"] = "0000111";
	compTable["D&A"] = "0000000";
	compTable["D|A"] = "0010101";
	compTable["M"]	 = "1110000";
	compTable["!M"]	 = "1110001";
	compTable["-M"]	 = "1110011";
	compTable["M+1"] = "1110111";
	compTable["M-1"] = "1110010";
	compTable["D+M"] = "1000010";
	compTable["D-M"] = "1010011";
	compTable["M-D"] = "1000111";
	compTable["D&M"] = "1000000";
	compTable["D|M"] = "1010101";

	jumpTable[""]	 = "000";
	jumpTable["JGT"] = "001";
	jumpTable["JEQ"] = "010";
	jumpTable["JGE"] = "011";
	jumpTable["JLT"] = "100";
	jumpTable["JNE"] = "101";
	jumpTable["JLE"] = "110";
	jumpTable["JMP"] = "111";
}

string Code::destBinary(string destMnemonic) {
	// Returns the 3-bit binary code of the dest mnemonic
	return destTable[destMnemonic];
}

string Code::compBinary(string compMnemonic) {
	// Returns the 7-bit binary code of the comp mnemonic
	return compTable[compMnemonic];
}

string Code::jumpBinary(string jumpMnemonic) {
	// Returns the 3-bit binary code of the jump mnemonic
	return jumpTable[jumpMnemonic];
}

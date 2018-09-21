#pragma once
#ifndef CODEWRITER_H
#define CODEWRITER_H

#include <iostream>
#include <string>
#include "Parser.h"

using namespace std;

class CodeWriter {
public:
	// Constructor
	CodeWriter(ofstream& fileName) {
		out = &fileName;
		label = 0;
		file = "";
	}
	// Opens the input file/stream and gets ready to write into it
	
	// Destructor
	// ~CodeWriter();

	void setFileName(string fileName);
	// Informs the code writer that the translation of a new VM file is started

	void writeArithmetic(string command);
	// Writes the assembly code that is the translation of the given arithmetic command
	
	void WritePushPop(VMcommand pushpop, string segment, int index);
	// Writes the assembly code that is the translation of the given command, where 'command' is either "C_PUSH" or "C_POP"

	void push(string segment, int index);
	void pop(string segment, int index);
	string memorySegment(string segment, int index);

	void Close() {
		out->close();	// Closes the output file (destructor)
	}

private:
	ofstream* out;
	string file;
	int label;
	bool started;
};

#endif // PARSER_H
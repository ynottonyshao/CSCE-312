#pragma once
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum VMcommand {
	C_ARITHMETIC,
	C_PUSH, C_POP,
	COMMENT
};

class Parser {
public:
	// Constructor
	Parser(ifstream& fileName) {
		source = &fileName;
		command = "";
	}
	// Opens the input file/stream and gets ready to parse it

	// Destructor
	~Parser() {
		source->close();
	}

	bool hasMoreCommands();
	// Are there more commands in the input?

	void advance();
	// Reads the next command from the input and makes it the current command
	// Should be called only if hasMoreCommands() is true
	// Initially, there is no current command

	VMcommand commandType();
	// Returns the type of the current VM command:
	// "C_ARITHMETIC"
	// "C_PUSH", "C_POP"
	// "COMMENT"

	string arg1();
	// Returns the first argument of the current command
	// In the case of "C_ARITHMETIC", the command itself ('add', 'sub', etc.) is returned

	int arg2();
	// Returns the second argument of the current command
	// Should be called only if the current command is "C_PUSH" or "C_POP"

private:
	ifstream* source;
	string command;
};

#endif // PARSER_H
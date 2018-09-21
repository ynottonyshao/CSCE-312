#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Parser {
public:
	// Constructor
	Parser(ifstream& fileName) {
		source = &fileName;
		command = "";
	}
	// opens the input file/stream and gets ready to parse it

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

	string commandType();
	// Returns the type of the current command:
	// "A_COMMAND" for @XXX were XXX is either a symbol or a number
	// "C_COMMAND" for dest=comp;jump
	// "L_COMMAND" (pseudocommand) for (XXX) where XXX is a symbol

	string symbol();
	// Returns the symbol or decimal XXX of the current command @XXX or (XXX)
	// Should be called only when commandType() is "A_COMMAND" or "L_COMMAND"

	string dest();
	// Returns the dest mnemonic in the current C-command (8 possibilities)
	// Should be called only when commandType() is "C_COMMAND"

	string comp();
	// Returns the comp mnemonic in the current C-command (28 possibilities)
	// Should be called only when commandType() is "C_COMMAND"

	string jump();
	// Returns the jump mnemonic in the current C-command (8 possibilities)
	// Should be called only when commandType() is "C_COMMAND"

private:
	ifstream* source;
	string command;
};

#endif // PARSER_H
#include <iostream>
#include <string>
#include <fstream>
#include "Parser.h"

using namespace std;

bool Parser::hasMoreCommands() {
	return !(source->eof());	// end of file? Are there more commands in the input?
}

void Parser::advance() {
	getline(*source, command);
}

VMcommand Parser::commandType() {
	if ((command.substr(0, 2) == "//") || (command.find_first_not_of(" ") == string::npos)) {
		return COMMENT;
	}
	string tempCommand = command;
	if (tempCommand.find(" ") == 0) {
		tempCommand = tempCommand.substr(tempCommand.find_first_not_of(" "));
	}
	if (tempCommand.find("add") == 0 || tempCommand.find("sub") == 0 || tempCommand.find("neg") == 0 || tempCommand.find("eq") == 0 || tempCommand.find("gt") == 0 || tempCommand.find("lt") == 0 || tempCommand.find("and") == 0 || tempCommand.find("or") == 0 || tempCommand.find("not") == 0) {
		return C_ARITHMETIC;
	}

	if (command.find("push") == 0) {
		return C_PUSH;
	}
	if (command.find("pop") == 0) {
		return C_POP;
	}
	else {
		throw runtime_error("Could not do current command.");
	}
}

string Parser::arg1() {
	string pushpop;
	string arg = command;

	if (commandType() == C_ARITHMETIC) {
		int space1 = command.find(" ", 0);
		int space2 = command.find(" ", space1 + 1);
		return command.substr(space1 + 1, space2 - space1 - 1);	// Returns the first argument of the current command
	}
	else if (commandType() == C_PUSH) {
		pushpop = "push";
	}
	else if (commandType() == C_POP) {
		pushpop = "pop";
	}
	arg = arg.substr((arg.find(pushpop) + pushpop.length()));
	arg = arg.substr(arg.find_first_not_of(" "));
	// delete everything after arg1 using substr
	arg = arg.substr(0, arg.find(" "));
	return arg;	// Returns the first argument of the current command
}

int Parser::arg2() {
	if (commandType() == C_PUSH || commandType() == C_POP) {
		int firstSpace = command.find(" ", 0);
		int secondSpace = command.find(" ", firstSpace + 1);
		int thirdSpace = command.find(" ", secondSpace + 1);
		string indexStr = command.substr(secondSpace + 1, thirdSpace - secondSpace - 1);
		int index = stoi(indexStr);
		return index;	// Returns the second argument of the current command
	}
}
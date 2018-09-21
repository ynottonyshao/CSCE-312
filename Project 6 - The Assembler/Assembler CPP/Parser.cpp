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

string Parser::commandType() {
	// Return "COMMENT" if the line has "//" or " "
	if ((command.substr(0, 2) == "//") || (command.find_first_not_of(" ") == string::npos)) {
		return "COMMENT";
	}

	// Return "A_COMMAND" if command has "@"
	if (command.find("@") != string::npos) {
		return "A_COMMAND";
	}

	// Return "L_COMMAND" if command begins with "("
	if (command.at(0) == '(') {
		return "L_COMMAND";
	}
	else {
		return "C_COMMAND";		// return "C_COMMAND" for none of the above
	}
}

string Parser::symbol() {
	// skip and trim to the first non-whitespace character
	string ccommand = command.substr(command.find_first_not_of(" "));

	// stop at the space (at the end of the line)
	if (ccommand.find(" ") != string::npos) {
		// the command is everything on the line
		ccommand = ccommand.substr(0, ccommand.find(" "));
	}

	ccommand.erase(0, 1);	// erase "@" or "("
	if (ccommand.find(")") != string::npos) {
		// erase everything after ")"
		ccommand.erase(ccommand.find(")"), string::npos);
	}

	return ccommand;
}

string Parser::dest() {
	// skip and trim to the first non-whitespace character
	string ccommand = command.substr(command.find_first_not_of(" "));

	// stop at the space (at the end of the line)
	if (ccommand.find(" ") != string::npos) {
		// the command is everything on the line
		ccommand = ccommand.substr(0, ccommand.find(" "));
	}

	if (ccommand.find("=") == string::npos) {
		ccommand = "";	// dest = null
	}
	else {
		// erase everything after "="
		ccommand.erase(ccommand.find("="), string::npos);
	}

	return ccommand;		
}

string Parser::comp() {
	// skip and trim to the first non-whitespace character
	string ccommand = command.substr(command.find_first_not_of(" "));

	// stop at the space (at the end of the line)
	if (ccommand.find(" ") != string::npos) {
		// the command is everything on the line
		ccommand = ccommand.substr(0, ccommand.find(" "));
	}

	if (ccommand.find(";") != string::npos) {
		// the command is everything before ";"
		ccommand = ccommand.substr(0, ccommand.find(";"));
	}
	
	if (ccommand.find("=") != string::npos) {
		// erase "=" and everything before "="
		ccommand.erase(0, (ccommand.find("=") + 1));
	}
	int end = ccommand.find_last_not_of(";");
	return ccommand.substr(0, end + 1);
}

string Parser::jump() {
	// skip and trim to the first non-whitespace character
	string ccommand = command.substr(command.find_first_not_of(" "));

	// stop at the space (at the end of the line)
	if (ccommand.find(" ") != string::npos) {
		// the command is everything on the line
		ccommand = ccommand.substr(0, ccommand.find(" "));
	}

	if (ccommand.find(";") != string::npos) {
		// erase ";" and everything before ";"
		ccommand.erase(0, (ccommand.find(";") + 1));
		return ccommand;
	}
	return "";		// no jump mnemonic
}

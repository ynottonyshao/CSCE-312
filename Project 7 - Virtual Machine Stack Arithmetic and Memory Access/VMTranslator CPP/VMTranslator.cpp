#include <iostream>
#include <fstream>
#include <string>

#include "Parser.h"
#include "CodeWriter.h"

using namespace std;

int main(int argc, char *argv[]) {
	try {
		// Get the input and output file names, and provide usage instructions
		if (argc != 2) {
			cout << "Arguments are incorrect." << endl;
			cout << "Try this syntax: " << argv[0] << "<inputfilename.vm>" << endl;
			exit(1);
		}

		string inputFileName = argv[1];	// read input file name
		ifstream in;
		ofstream out;

		// Create the output file
		in.open(inputFileName);
		if (in.fail()) {
			throw runtime_error("Failed to create output file for " + inputFileName);
		}

		// Construct a Parser to parse the VM input file and
		// a CodeWriter to generate code into the corresponding output file
		Parser parse = Parser(in);
		inputFileName = inputFileName.substr(0, inputFileName.find(".", 0));	// takes away string ".vm"

		CodeWriter code = CodeWriter(out);
		code.setFileName(inputFileName);

		while (parse.hasMoreCommands()) {
			parse.advance();	// Reads the next command from the input and makes it the current command
			VMcommand commandtype = parse.commandType();
			if (commandtype != COMMENT) {
				if (commandtype == C_ARITHMETIC) {
					code.writeArithmetic(parse.arg1());
				}
				else if (commandtype == C_PUSH || commandtype == C_POP) {
					code.WritePushPop(commandtype, parse.arg1(), parse.arg2());
				}
				else {
					throw runtime_error("Unknown command type...");
				}
			}
		}
		in.close();		// close input file
		code.Close();	// close output file
		cout << "Successfully created " << inputFileName << ".asm file from " << inputFileName << ".vm!" << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "Oops... unknown error :(" << endl;
	}

	// system("pause");
}
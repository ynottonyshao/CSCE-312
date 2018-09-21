#include <iostream>
#include <fstream>
#include <bitset>
#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"

using namespace std;

int main(int argc, char *argv[]) {
	try {
		string inputFileName, outputFileName;
		int lineNumberROM = 0;	// line number of ROM (instructions)
		int addressRAM = 16;	// RAM address
		ifstream in;
		ofstream out;

		// Get the input and output file names, and provide usage instructions
		if (argc != 2) {
			cout << "Arguments are incorrect." << endl;
			cout << "Try this syntax: " << argv[0] << " <inputfilename.asm>" << endl;
			exit(1);
		}
		inputFileName = argv[1];	// read inputfile name
		
		// Create the output file
		in.open(inputFileName);
		if (in.fail()) {
			cout << "Failed to create output file for " << inputFileName << endl;
			exit(1);
		}

		/* First Pass */
		Parser parse = Parser(in);
		SymbolTable symbolTable;	// pre-populate symbolTable
		
		while (parse.hasMoreCommands()) {
			parse.advance();

			if (parse.commandType() == "L_COMMAND") {
				// if (LABEL), create LABEL entry in symbolTable
				symbolTable.addEntry(parse.symbol(), lineNumberROM);
			}
			else if (parse.commandType() != "COMMENT") {
				// skip to next line
				lineNumberROM++;
			}
		}
		in.close();
		in.open(inputFileName);
		
		outputFileName = inputFileName.substr(0, inputFileName.length() - 4) + ".hack";
		out.open(outputFileName);

		Code translate;

		/* Second Pass */
		while (parse.hasMoreCommands()) {
			parse.advance();
			if (parse.commandType() != "COMMENT") {
				if (parse.commandType() == "A_COMMAND") {
					out << "0";		// the first value of A-instruction
					if (isdigit(parse.symbol()[0])) {
						// if @<#>, then convert to equivalent binary code
						out << bitset<15>(stoi(parse.symbol(), nullptr)).to_string() << endl;
						// addressRAM++;	// go to next line
					}
					else {
						if (symbolTable.contains(parse.symbol())) {
							// if @<LABEL>, then convert <LABEL>'s address to binary code
							out << bitset<15>(symbolTable.getAddress(parse.symbol())).to_string() << endl;
							// addressRAM++;	// go to next line
						}
						else {
							// create symbolTable entry for variable <LABEL>
							symbolTable.addEntry(parse.symbol(), addressRAM);
							// convert the new address to binary code
							out << bitset<15>(addressRAM).to_string() << endl;
							addressRAM++;	// go to next line
						}
					}
				}
				else if (parse.commandType() == "C_COMMAND") {
					out << "111";	// the first three values of C-instruction
					out << translate.compBinary(parse.comp());	// print out translated comp bits
					out << translate.destBinary(parse.dest());	// print out translated dest bits
					out << translate.jumpBinary(parse.jump());	// print out translated jump bits
					out << endl;	// next line (so that code isn't a continuous single line of binary code)!
				}
			}
		}
		in.close();		// close input file
		out.close();	// close output file
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	
	catch (...) {
		cerr << "Oops... unknown error :(" << endl;
	}

	// system("pause");
}
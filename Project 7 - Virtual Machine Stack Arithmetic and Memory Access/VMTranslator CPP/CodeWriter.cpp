#include <iostream>
#include <string>
#include <fstream>
#include "CodeWriter.h"
using namespace std;

void CodeWriter::setFileName(string fileName) {
	out->open((fileName + ".asm"));
	if (out->fail()) {
		throw runtime_error("Failed to open output file for " + fileName);
	}
	file = fileName;
	cout << "The translation of " << fileName << ".vm began" << endl;
}

void CodeWriter::writeArithmetic(string command) {
	*out << "@SP" << endl << "A=M-1" << endl;
	if (command == "neg") {
		*out << "M=-M" << endl;
	}
	else if (command == "not") {
		*out << "M=!M" << endl;
	}
	else {
		*out << "D=M" << endl;
		*out << "@SP" << endl << "AM=M-1" << endl << "M=0" << endl << "A=A-1" << endl;
		if (command == "add") {
			*out << "M=M+D" << endl;
		}
		else if (command == "sub") {
			*out << "M=M-D" << endl;
		}
		else if (command == "and") {
			*out << "M=M&D" << endl;
		}
		else if (command == "or") {
			*out << "M=M|D" << endl;
		}
		else {
			*out << "D=M-D" << endl;
			*out << "@TRUE" << label << endl;
			*out << "D;J";
			if (command == "eq") {
				*out << "EQ";
			}
			else if (command == "lt") {
				*out << "LT";
			}
			else if (command == "gt") {
				*out << "GT";
			}
			*out << endl << "@SP" << endl << "A=M-1" << endl << "M=0" << endl;
			*out << "@FALSE" << label << endl;
			*out << "0;JEQ" << endl;
			*out << "(TRUE" << label << ")" << endl;
			*out << "@SP" << endl << "A=M-1" << endl << "M=-1" << endl;
			*out << "(FALSE" << label << ")" << endl;
			label++;
		}
	}
}

void CodeWriter::WritePushPop(VMcommand pushpop, string segment, int index) {
	if (pushpop == C_PUSH) {
		push(segment, index);
	}
	else if (pushpop == C_POP) {
		pop(segment, index);
	}
	else {
		throw runtime_error("PUSH or POP not found...");
	}
}

void CodeWriter::push(string segment, int index) {
	string memorySegmentStr = memorySegment(segment, index);

	if (segment == "constant") {
		*out << "@" << index << endl;
		*out << "D=A" << endl;
	}
	else if ((segment == "static") || (segment == "temp") || (segment == "pointer")) {
		*out << "@" << memorySegmentStr << endl;
		*out << "D=M" << endl;
	}
	else {
		*out << "@" << memorySegmentStr << endl;
		*out << "D=M" << endl;
		*out << "@" << index << endl << "A=D+A" << endl << "D=M" << endl;
	}
	*out << "@SP" << endl << "A=M" << endl << "M=D" << endl;
	*out << "@SP" << endl << "M=M+1" << endl;
}

void CodeWriter::pop(string segment, int index) {
	string memorySegmentStr = memorySegment(segment, index);

	if ((segment == "static") || (segment == "temp") || (segment == "pointer")) {
		*out << "@SP" << endl << "AM=M-1" << endl << "D=M" << endl;
		*out << "@" << memorySegmentStr << endl;
		*out << "M=D" << endl;
	}
	else {
		*out << "@" << memorySegmentStr << endl;
		*out << "D=M" << endl;
		*out << "@" << index << endl << "D=D+A" << endl;
		*out << "@R13" << endl << "M=D" << endl;
		*out << "@SP" << endl << "AM=M-1" << endl << "D=M" << endl;
		*out << "@R13" << endl << "A=M" << endl << "M=D" << endl;
	}
}

string CodeWriter::memorySegment(string segment, int index) {
	if (segment == "argument") {
		return "ARG";
	}
	if (segment == "local") {
		return "LCL";
	}
	if (segment == "this") {
		return "THIS";
	}
	if (segment == "that") {
		return "THAT";
	}
	if (segment == "pointer") {
		return "R" + to_string(3 + index);
	}
	if (segment == "temp") {
		return "R" + to_string(5 + index);
	}
	return file + "." + to_string(index);	// else "static"
}
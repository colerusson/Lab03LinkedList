#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "LinkedList.h"
#include "LinkedListInterface.h"	

using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif		

int main(int argc, char* argv[]) {
	VS_MEM_CHECK	//implementing memory check

		if (argc < 3) {
			cerr << "Please provide name of input and output files";
			return 1;
		}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in) {
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out) {
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}


	LinkedList<string> myList;		//instantiation of templated linked list
	LinkedList<string> copyList;

	for (string line; getline(in, line);) {		//iterate through the file line by line
		string item1, item2;
		if (line.size() == 0) continue;
		out << endl << line;
		istringstream iss(line);
		iss >> item1;
		if (item1 == "Insert") {		//check for instances of "insert and perform insertion function
			while (iss >> item2) {
				myList.push_front(item2);
			}
		}
		else if (item1 == "PrintList") {	//check for instances of "printlist" and perform toString function
			out << myList.toString();
		}
		else if (item1 == "Clear") {	//check for instances of "clear" and clear the linked list
			myList.clear();
			out << " OK";
		}
		else if (item1 == "Empty") {
			if (!myList.empty()) {
				out << " false";
			}
			else {
				out << " true";
			}
		}
		else if (item1 == "Size") {
			out << " " << myList.size();
		}
		else if (item1 == "Delete") {
			if (myList.size() != 0) {
				myList.pop_front();
				out << " OK";
			}
			else {
				out << " Empty!";
			}
		}
		else if (item1 == "First") {
			if (myList.size() != 0) {
				out << " " << myList.front();
			}
			else {
				out << " Empty!";
			}
		}
		else if (item1 == "Remove") {
			while (iss >> item2) {
				if (myList.size() != 0) {
					myList.remove(item2);
				}
			}
		}
		else if (item1 == "Reverse") {
			if (myList.size() != 0) {
				myList.reverse();
				out << " OK";
			}
			else {
				out << " Empty!";
			}
		}
		else if (item1 == "Copy") {
			copyList = myList;
			out << " OK";
		}
		else if (item1 == "PrintCopy") {
			if (copyList.size() != 0) {
				out << copyList.toString();
			}
			else {
				out << " Empty!";
			}
		}
	}
	in.close();

	return 0;
}

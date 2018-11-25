#ifndef _read_
#define _read_
#include<iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
class code_num {		//I create a class to keep two variables in a vector.
public:
	int burst;
	string inst_name;
	code_num()
	{ }
	//constructor of the code_num class
	code_num(string _inst_name, int _burst) {
		burst = _burst;
		inst_name = _inst_name;
	}
};
class read {

public:
	vector<code_num> read_all(string TxT_File);
};
vector<code_num> read::read_all(string TxT_File)	//txt files variables are kept as a code_num class's object and they are keep in vector.
{
	TxT_File+=".txt";
	ifstream file(TxT_File.c_str());
	string instruction_name;
	int burst;
	vector<code_num> codeVector;
	while (file >> instruction_name >> burst) {
		code_num newCodeLine(instruction_name, burst);
		codeVector.push_back(newCodeLine);
	}
	return codeVector;
}
#endif

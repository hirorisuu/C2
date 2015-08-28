#include "Main.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <string>
#include "Class.h"
#include "Parser.h"
using namespace std;

int main(){
	while (1){
		string s;
		cout << "> ";
		getline(cin, s);
		if (!s.empty()) cout << program(s) << endl;
	}
	return 0;
}

string program(string prog){
	state option = { 0, 0 };
	int ret = equa_1(prog, &option);
	ostringstream stream;
	stream << ret << "(" << (option.error ? "Error, " : "") << "position: " << option.posi << ")";
	return stream.str();
}

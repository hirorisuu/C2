#include "Main.h"
using namespace std;

int main(){
	while (1){
		string s;
		cout << "> ";
		cin >> s;
		if (!s.empty()) cout << program(s) << endl;
	}
	return 0;
}

string program(string prog){
	state option = { 0, 0 };
	int ret = parse(prog, &option);
	ostringstream stream;
	stream << ret << "(" << (option.error ? "Error, " : "") << "index: " << option.position << ")";
	return stream.str();
}

int parse(string s, state* option){
	for (int i = 0; i < s.size(); i++){
		if ()
	}
	return 1;
}
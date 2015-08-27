#include "Class.h"
#include "Parser.h"
#include <string>
using namespace std;

void space(string s, state *option){
	while (s[option->posi] == ' ') option->posi++;
}

int equa_1(string s, state *option){
	int ret = equa_2(s, option);
	while (1){
		if (s[option->posi] == '+'){
			option->posi++;
			ret += equa_2(s, option);
		}
		else if (s[option->posi] == '-'){
			option->posi++;
			ret -= equa_2(s, option);
		}
		else {
			return ret;
		}
	}
}

int equa_2(string s, state *option){
	int ret = equa_3(s, option);
	while(1){
		if (s[option->posi] == '*'){
			option->posi++;
			ret *= equa_2(s, option);
		}
		else if (s[option->posi] == '/'){
			option->posi++;
			ret /= equa_2(s, option);
		}
		else {
			return ret;
		}
	}
}

int equa_3(string s, state *option){
	int ret = 0;
	int old_posi = option->posi;
	space(s, option);
	if (s[option->posi] == '('){
		option->posi++;
		ret = equa_1(s, option);
		if (s[option->posi] != ')'){
			option->posi = old_posi;
			option->error = 1;
			return 0;
		}
		option->posi++;
	}
	else if (isdigit(s[option->posi])){
		string num;
		while (isdigit(s[option->posi])){
			num = num + s[option->posi];
			option->posi++;
		}
		int i = stoi(num);
		return i;
	}
	else{
		function(s, option);
		ret = -1;
	}
	space(s, option);
	return ret;
}

int function(string s,state *option){
	return 0;
}
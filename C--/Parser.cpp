#include "Class.h"
#include "Parser.h"
#include <string>
#include <map>
using namespace std;

map<string, int> var_int;

void space(string s, state *option){
	while (s[option->posi] == ' ') option->posi++;
}

int equa_1(string s, state *option){
	int ret = equa_2(s, option);
	space(s,option);
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
	space(s, option);
	while(1){
		if (s[option->posi] == '*'){
			option->posi++;
			ret *= equa_3(s, option);
		}
		else if (s[option->posi] == '/'){
			option->posi++;
			ret /= equa_3(s, option);
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
		return num(s,option);
	}
	else{
		ret = function(s, option);
	}
	space(s, option);
	return ret;
}

int function(string s,state *option){
	if (s.substr(option->posi,2) == "if") return if_cmm(s,option);
	else if (s.substr(option->posi, 3) == "for") return for_cmm(s,option);
	else if (s.substr(option->posi, 5) == "while") return while_cmm(s,option);
	else if (s.substr(option->posi, 3) == "int") return vardef(s,option);
	else return assign(s,option);
	return 0;
}

int if_cmm(string s, state *option){
	option->posi += 2;
	space(s, option);
	if (s[option->posi] != '('){
		option->error = 1;
		return -1;
	}
	option->posi++;
	if (equa_1(s, option) != 0){
		if (s[option->posi] != ')') {
			option->error = 1;
			return -1;
		}
		option->posi++;
		return equa_1(s, option);
	}
	return 0;
}

int while_cmm(string s, state *option){
	option->posi += 5;
	space(s, option);
	if (s[option->posi] != '('){
		option->error = 1;
		return -1;
	}
	option->posi++;
	if (equa_1(s, option) != 0){
		if (s[option->posi] != ')') {
			option->error = 1;
			return -1;
		}
		option->posi++;
		return equa_1(s, option);
	}
	return 0;
}

int for_cmm(string s, state *option){
	option->posi += 3;
	space(s, option);
	if (s[option->posi] != '('){
		option->error = 1;
		return -1;
	}
	option->posi++;
	int i = equa_1(s,option);
	return 0;
}

int vardef(string s,state *option){
	space(s, option);
	if (s.substr(option->posi, 3) == "int"){
		option->posi += 3;
		space(s, option);
		var_int[str(s, option)] = 0;
	}
	return 0;
}

int assign(string s, state *option){
	int old_posi = option->posi;
	space(s, option);
	string name = str(s, option);
	if (var_int[name] != -1) {
		space(s, option);
		if (s[option->posi] != '='){
			option->posi = old_posi;
			return var(s,option);
		}
		option->posi++;
		space(s, option);
		var_int[name] = num(s,option);
		return var_int[name];
	}
	else{
		option->error = 1;
		return -1;
	}
}

int var(string s, state *option){
	space(s, option);
	string name = str(s, option);
	if (var_int[name] != -1) return var_int[name];
	else{
		option->error = 1;
		return -1;
	}
}

int num(string s,state *option){
	string n;
	while (isdigit(s[option->posi])){
		n = n + s[option->posi];
		option->posi++;
	}
	return stoi(n);
}

string str(string s,state *option){
	string ss;
	while (isalpha(s[option->posi])){
		ss = ss + s[option->posi];
		option->posi++;
	}
	return ss;
}
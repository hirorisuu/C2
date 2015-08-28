#pragma once
#include <string>
using namespace std;

int equa_1(string, state*);
int equa_2(string, state*);
int equa_3(string, state*);
void space(string, state*);
int function(string, state*);
int if_cmm(string, state*);
int for_cmm(string, state*);
int while_cmm(string, state*);
int num(string, state*);
string str(string, state*);
int var(string, state*);
int vardef(string, state*);
int assign(string, state*);
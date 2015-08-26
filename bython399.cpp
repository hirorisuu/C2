/*                    *
 *  Bython ver.0.0.0  *
 *   made by:         *
 *          akouryy   *
 *        hirorisuu   *
 *         satouuta   *
 *                    */
#include <stdlib.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class bython_type{
	char t;
	bool b;
	int i;
	string s;
	vector<bython_type> v;
public:
	bython_type():i(0), t('i'){};
	bython_type(bool b):b(b), t('b'){};
	bython_type(int i):i(i), t('i'){};
	bython_type(string s):s(s), t('s'){};
	bython_type(vector<bython_type> v):v(v), t('v'){};
	char type() const{return t;}
	bool getb() const{
		if(t != 'b')
			throw this;
		return b;
	}
	int geti() const{
		if(t != 'i')
			throw this;
		return i;
	}
	string gets() const{
		if(t != 's')
			throw this;
		return s;
	}
	vector<bython_type> getv() const{
		if(t != 'v')
			throw this;
		return v;
	}
	string to_str() const{
		ostringstream str;
		switch(t){
		case 'b':
			str << b;
		case 'i':
			str << i;
		case 's':
			str << s;
		case 'v':
			if(v.empty()) return "[]";
			vector<bython_type>::const_iterator it = v.begin();
			str << "[" << (*it).to_str();
			++it;
			while(it != v.end()){
				str << "," << (*it).to_str();
				++it;
			}
			str << "]";
		}
		return str.str();
	}
	bool no_empty(){
		switch(t){
		case 'b':
			return b;
		case 'i':
			return i != 0;
		case 's':
			return !s.empty();
		case 'v':
			return !v.empty();
		}
	}
};
ostream& operator<< (ostream& os, const bython_type& p){
	os << p.to_str() << '(' << p.type() << ')';
	return os;
}
class tree{
public:
	virtual bython_type evalute()=0;
};
class op2_tree : tree{
	tree *left, *right;
	string op;
public:
	op2_tree(tree *left, string op, tree *right):left(left), op(op), right(right){}
	virtual bython_type evalute(){
		bython_type l = left->evalute();
		bython_type r = left->evalute();
		if(op == "+"){
			switch(l.type()){
				case 'i':
					return l.geti() + r.geti();
				case 's':
					return l.gets() + r.gets();
			}
		}else if(op == "-"){
			switch(l.type()){
				case 'i':
					return l.geti() - r.geti();
			}
		}else if(op == "*"){
			switch(l.type()){
				case 'i':
					return l.geti() * r.geti();
				case 's':
					string s = "", ls = l.gets();
					int ri = r.geti();
					for(int i = 0; i < ri; i++)
						s += ls;
					return s;
			}
		}else if(op == "/"){
			switch(l.type()){
				case 'i':
					return l.geti() / r.geti();
			}
		}else if(op == "%"){
			switch(l.type()){
				case 'i':
					return l.geti() % r.geti();
				case 's':
					return l.geti() % r.geti();
			}
		}else if(op == "in"){
			return find(r.begin(), r.end(), l) != r.end();
		}
	}
};
class num_tree : tree{
	int num;
public:
	num_tree(int num):num(num){}
	virtual bython_type evalute(){
		return num;
	}
};
class name_tree : tree{
	string name;
public:
	name_tree(string name):name(name){}
	virtual bython_type evalute(){
		return name;
	}
};
class block_tree : tree{
	vector<tree> exprs;
public:
	block_tree(vector<tree> exprs) : exprs(exprs){}
	virtual bython_type evalute(){
		vector<tree>::iterator it = exprs.begin();
		bython_type result;
		while(it != exprs.end()){
			result = (*it).evalute();
			++it;
		}
		return result;
	}
};
class if_tree : tree{
	tree *cond;
	block_tree *if_block, *else_block;
public:
	if_tree(tree* cond, block_tree* if_block, block_tree* else_block):cond(cond), if_block(if_block), else_block(else_block){}
	virtual bython_type evalute(){
		if(!(cond->evalute().no_empty()))
			return if_block->evalute();
		else
			return else_block->evalute();
	}
};
class while_tree : tree{
	tree *cond;
	block_tree *block;
public:
	while_tree(tree* cond, block_tree* block):cond(cond), block(block){}
	virtual bython_type evalute(){
		bython_type result;
		while(!(cond->evalute().no_empty()))
			result = block->evalute();
		return result;
	}
};
class for_tree : tree{
	string name;
	tree *expr;
	block_tree *block;
public:
	for_tree(string name, tree* expr, block_tree* block):name(name), cond(cond), block(block){}
	virtual bython_type evalute(){
		bython_type result;
		vector<bython_type> v = expr->evalute().getv();
		vector<bython_type>::iterator vi = v.begin();
		while(vi != v.end()){
			result = block->evalute();
		}
		return result;
	}
};
class a{};

struct parse{
	int index;
	int error;
};

int expr1(string const, parse*);
int expr2(string const, parse*);
int expr3(string const, parse*);
vector<int> block(string const, parse*);

/*
	{0 to 9}                                ... number   o
	S {a to z | A to Z | _} S               ... name     o
	[expr1 {, expr1}]                       ... funarg   x
	name \( funarg \)                       ... function x
	expr2 {(+ | -) expr2}                   ... expr1    o
	expr3 {(* | /) expr3}                   ... expr2    o
	S (\( expr1 \) | number | function) S   ... expr3    o
*/
string bython(string program){
	parse option = {0, 0};
	int ret = expr1(program, &option);
	ostringstream stream;
	stream << ret << "(" << (option.error?"Error, ":"") << "index: " << option.index << ")";
	return stream.str();
}
void skips(string const program, parse* option){
	while(program[option->index] == ' '){
		option->index++;
	}
}

int number(string program, parse* option){
	int result = 0;
	if(program[option->index] < '0' || '9' < program[option->index]){
		option->error = 1;
		return 0;
	}
	while('0' <= program[option->index] && program[option->index] <= '9'){
		result = result * 10 + program[option->index] - '0';
		option->index++;
	}
	return result;
}

string name(string program, parse* option){
	if(!(  'a' <= program[option->index] && program[option->index] <= 'z'
		|| 'A' <= program[option->index] && program[option->index] <= 'Z'
		|| '_' == program[option->index])){
		option->error = 1;
		return "";
	}
	int old_index = option->index;
	string result;
	while( 'a' <= program[option->index] && program[option->index] <= 'z'
		|| 'A' <= program[option->index] && program[option->index] <= 'Z'
		|| '0' <= program[option->index] && program[option->index] <= '9'
		|| '_' == program[option->index]){
		result += program[option->index];
		option->index++;
	}
	return result;
}

vector<int> funarg(string program, parse* option){
	vector<int> args;
	args.push_back(expr1(program, option));
	if(option->error){
		return args;
	}
	while(1){
		int val = expr1(program, option);
		if(option->error){
			return args;
		}
		args.push_back(val);
	}
}
int function(string program, parse* option){
	int old_index = option->index;
	vector<int> args;
	string fname = name(program, option);
	if(program[option->index] == '('){
		option->index++;
		args = funarg(program, option);
		if(program[option->index] != ')'){
			option->index = old_index;
			option->error = 1;
			return 0;
		}
		option->index++;
	}else{
		option->error = 1;
		return 0;
	}
	if(fname == "exit" && args.empty()){
		exit(0);
	}else if(fname == "exit" && args.size() == 1){
		exit(args[0]);
	}
	return 0; //TODO: 後で変える
}

int expr1(string program, parse* option){
	int result = expr2(program, option);
	while(1){
		switch(program[option->index]){
		case '+':
			option->index++;
			result += expr2(program, option);
			break;
		case '-':
			option->index++;
			result -= expr2(program, option);
			break;
		default:
			return result;
		}
		if(option->error){
			option->index--;
			option->error=0;
			return result;
		}
	}
}
int expr2(string program, parse* option){
	int result = expr3(program, option);
	while(1){
		switch(program[option->index]){
		case '*':
			option->index++;
			result *= expr3(program, option);
			break;
		case '/':
			option->index++;
			result /= expr3(program, option);
			break;
		default:
			return result;
		}
		if(option->error){
			option->index--;
			option->error=0;
			return result;
		}
	}
}
int expr3(string program, parse* option){
	int result = 0;
	int old_index = option->index;
	skips(program, option);
	if(program[option->index] == '('){
		option->index++;
		result = expr1(program, option);
		if(program[option->index] != ')'){
			option->index = old_index;
			option->error = 1;
			return 0;
		}
		option->index++;
	}else{
		result = number(program, option);
		if(option->error){
			option->error = 0;
			function(program, option);
		}
	}
	skips(program, option);
	return result;
}
vector<int> block(string program, parse* option){
	vector<int> result;
	int tabnum = 0, old_index = option->index;
	while(program[option->index] == '\t'){
		tabnum++;
	}
	while(1){
		int tabnuml = 0;
		while(program[option->index] == '\t'){
			tabnuml++;
		}
		if(tabnum != tabnuml)
			return result;
		int val = expr1(program, option);
		if(option->error){
			option->index = old_index;
			return result;
		}
		result.push_back(val);
	}

}
int while_stmt(string program, parse *option){
	int old_index = option->index;
	if(program.substr(option->index, 5) != "while"){
		option->error = 1;
		return 0;
	}
	option->index += 5;
	int cond = expr1(program, option);
	if(program[option->index] != ':'){
		option->error = 1;
		option->index = old_index;
		return 0;
	}
	skips(program, option);
	int stmt = block(program, option);
	if(program.substr(option->index, 3) != "end"){
		option->error = 1;
		option->index = old_index;
		return 0;
	}
	return 0;//TODO
}
int for_stmt(string program, parse* option){
    int old_index = option->index;
    if(program.substr(option->index, 3) != "for"){
        option->error = 1;
        return 0;
	}
    option->index +=  3;
	name(program, option);
	if(program.substr(option->index, 2) != "in"){
		option->error = 1;
		option->index = old_index;
		return 0;
	}
	option->index += 2;
	int cond = expr1(program, option);
    if(program[option->index] != ':'){
        option->error = 1;
        option->index = old_index;
        return 0;
    }
    skips(program, option);
    int stmt1 = block(program, option);
    if(program.substr(option->index, 3) != "end"){
        option->error = 1;
        option->index = old_index;
        return 0;
    }
    return 0;//TODO
}
/*
match [expr]:
	if [expr1]:
		[shori...]
	if [expr2]:
		[shori...]
	else:
		[shori...]
end
*/
int match_stmt(string program, parse* option){
    int old_index = option->index;
    if(program.substr(option->index, 5) != "match"){
        option->error = 1;
        return 0;
    }
	option->index += 5;
	int expr;
	if(program[2])
		; //TODO
}

int main(){
	while(1){
		cout << "> ";
		string s;
		getline(cin, s);
		if(!s.empty()){
			cout << bython(s) << endl;
		}
	}
}


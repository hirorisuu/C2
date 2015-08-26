#include <iostream>
#include <string>
using namespace std;

int main(){
	string s;
	while (1){
		cout << ">";
		cin >> s;
		if (s == "Hello") cout << "Hello!" << endl;
		else if (s == "exit") {
			cout << "See You" << endl;
			break;
		}
		else cout << "Please input Hello" << endl;
	}
	return 0;
}
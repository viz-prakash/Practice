#include <iostream>
#include <string>

/**
* Prints permutation of all strings lexicographically 
*/

using namespace std;

void permutate_string(string str, int pos) {
	if (pos == str.length() -1) {
		cout << str << endl;
	}
	char ch = str[pos];
	for (int i = pos; i < str.length(); i++) {
		str[pos] = str[i];
		str[i] = ch;
		permutate_string(str, pos + 1);
		str[i] = str[pos];
		str[pos] = ch;
	}
}

int main() {
	string str("abcd");
	permutate_string(str, 0);
	return 0;
}

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


int main() {
	string input;

	//cin >> input;
	getline(cin, input);
	const char *ch_input = input.c_str();
	for (int i = 0; i < input.length(); i++) {
		int val = ch_input[i] - 'a';
		if (ch_input[i] == '.' || ch_input[i] == ' ') {
			cout << ch_input[i];
		}
		else {
			if (val / 10 > 0) {
				cout << val << "#";
			}
			else {
				cout << val;
			}

		}
	}
	return 0;
}

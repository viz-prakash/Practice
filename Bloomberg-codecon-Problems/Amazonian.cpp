//Problem        : Amazonian Languages
//Language       : C++
//Compiled Using : g++
//Version        : GCC 4.9.1
//Input for your program will be provided from STDIN
//Print out all output from your program to STDOUT

#include <iostream>
#include <string>
#include <algorithm>
#include <climits> 
#include <vector>

using namespace std;

int prefix_matcher(const char* str1, int len1, const char* str2, int len2) {
	int i = len2;
	if (len1 < len2) {
		i = len1;
	}
	for (int j = 0; j < i; j++) {
		if (str1[j] != str2[j]) {
			return j;
		}
	}
	return i;
}

int main() {
	int J, K, N, M;
	vector<string> base_lang;
	vector<string> target_lang;
	cin >> J >> K >> N >> M;
	int i = N;
	string word;
	while (i--) {
		cin >> word;
		base_lang.push_back(word);
	}
	i = M;
	while (i--) {
		cin >> word;
		target_lang.push_back(word);
	}

	int count = 0;

	for (i = 0; i < target_lang.size(); i++) {
		for (int j = 0; j < base_lang.size(); j++) {
			int prefix_matched = prefix_matcher(target_lang[i].c_str(), target_lang[i].size(), base_lang[j].c_str(), base_lang[j].size());
			//cout << target_lang[i].size() << endl;
			//cout << prefix_matched / target_lang[i].size();
			if ((prefix_matched * 100/ target_lang[i].size()) >= J) {
				count++;
			}
		}
	}

	if (count * 100 / M >= K) {
		cout << count * 100 / M;
	}
	else {
		cout << 0;
	}
	return 0;
}

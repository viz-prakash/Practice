/*
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

class word_weight {
public :
	string kh_word;
	int weight;
	word_weight(string kh_word, int weight) {
		this->kh_word = kh_word;
		this->weight = weight;
	}

};

int main() {
	int N, M;
	cin >> N;
	
	map<string, word_weight> dict;
	map<int, string> trans;

	string en_word;
	string kh_word;
	while (N--) {
		int weight;
		//getline(cin, en_word);
		cin >> en_word;
		cin >> kh_word;
		cin >> weight;
		dict.insert(make_pair(en_word, word_weight(kh_word, weight)));

	}
	cin >> M;

	while (M--) {
		cin >> en_word;
		//pair<string, word_weight> pa = dict.find(;
		map<string, word_weight>::iterator it = dict.find(en_word);
		if (it != dict.end()) {
			trans.insert(make_pair(it->second.weight, it->second.kh_word));
		}
	}
	int first = 0;
	for (map<int, string>::reverse_iterator it = trans.rbegin(); it != trans.rend(); it++) {
		if (first != 0) {
			cout << " ";
		}
		cout << it->second;
		first = 1;
	}

	return 0;
}
*/
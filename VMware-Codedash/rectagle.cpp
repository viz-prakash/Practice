
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;


int main() {

	int t, N;
	list <int> sizes;
	cin >> t;
	while (t--) {
		cin >> N;
		while (N--) {
			int temp;
			cin >> temp;
			sizes.push_back(temp);
		}
		sizes.sort();
		int rec_count = 0;
		int eq_size = 0;
		int prev = -1;
		for (list<int>::iterator it = sizes.begin(); it != sizes.end(); it++) {
			if (prev == *it) {
				eq_size++;
				prev = -1;
			}
			else {
				prev = *it;
			}
			if (eq_size == 2) {
				rec_count++;
				eq_size = 0;
			}
		}
		cout << rec_count << endl;
		sizes.clear();
	}
	return 0;
}

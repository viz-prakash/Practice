/*
* Problem URL
* https://www.hackerrank.com/challenges/richie-rich
*/

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#define MAX_N 100002

using namespace std;

int main() {
	int n;
	int k;
	cin >> n >> k;
	int K = k;
	string number;
	cin >> number;
	int mid = (n - 1) / 2;
	int diff_count = 0;
	vector<int> mid_dist(MAX_N / 2, 0);
	int str_last_index = number.length() - 1;
	for (int i = mid; i >= 0; i--) {
		if (number[i] != number[str_last_index - i]) {
			diff_count++;
			mid_dist[i] = 1;
			if (number[0 + i] > number[str_last_index - i]) {
				number[str_last_index - i] = number[0 + i];
			}
			else {
				number[0 + i] = number[str_last_index - i];
			}
			k--;
		}
	}
	if (diff_count > K) {
		cout << -1;
		return 0;
	}
	for (int i = 0; k > 0 && i <= mid; i++) {
		if (number[i] != '9') {
			if (mid_dist[i] == 1) {
				k--;
			}
			else {
				k = k - 2;
			}
			number[i] = number[str_last_index - i] = '9';
		}
	}
	cout << number;
	return 0;
}
//Problem        : Grasshopper
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
#include <list>

using namespace std;

int D, N, K;

int longest_increasing_series(vector<int> &arr) {
	vector<int> dp(K, 1);
	dp[0] = 1;
	for (int i = 1; i < K; i++) {
		for (int j = i; j >= 0; j--) {
			if (arr[j] < arr[i]) {
				dp[i] = dp[j] + 1;
				break;
			}
		}
	}
	int max = 0;
	for (int i = 0; i < K; i++) {
		if (dp[i] > max) {
			max = dp[i];
		}
	}
	return max;
}

int main() {
	K = 4;
	//vector<int> arr = { 1, 2, 3, 4};
	//cout << longest_increasing_series(arr);
	cin >> D >> N >> K;
	vector< vector<int> > field(N, vector<int>(K, 0));
	for(int n = 0; n < N; n++) {
		for (int k = 0; k < K; k++) {
			cin >> field[n][k];
		}
	}
	
	list<int> max_possible_hops;
	char turn = 'R';
	int r_gold_count, g_gold_count;
	r_gold_count = g_gold_count = 0;
	while (D--) {
		for (int i = 0; i < N; i++) {
			max_possible_hops.push_back( longest_increasing_series(field[i]));
		}
		max_possible_hops.sort();
		for (int n = 0; n < N; n++) {
			if (turn == 'R') {
				if (n % 2 == 0) {
					r_gold_count += max_possible_hops.back();
					max_possible_hops.pop_back();
				}
				else {
					g_gold_count += max_possible_hops.back();
					max_possible_hops.pop_back();
				}
			}
			else {
				if (n % 2 == 0) {
					g_gold_count += max_possible_hops.back();
					max_possible_hops.pop_back();
				}
				else {
					r_gold_count += max_possible_hops.back();
					max_possible_hops.pop_back();
				}
			}			
		}

		for (int col = 0; col < K; col++) {
			if (col % 2 == 0) {
				int temp = field[0][col];
				for (int row = 1; row < N; row++) {
					field[row - 1][col] = field[row][col];
				}
				field[N - 1][col] = temp;
			}
			else {
				int temp = field[N - 1][col];
				for (int row = N - 2; row >= 0; row--) {
					field[row + 1][col] = field[row][col];
				}
				field[0][col] = temp;
			}
		}
		turn = 'G';
	}
	if (g_gold_count > r_gold_count) {
		cout << 1;
	}
	else {
		cout << 0;
	}
	cout << " " << g_gold_count;
	return 0;
}

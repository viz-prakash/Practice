//Problem        : Binary Ouroboros
//Language       : C++
//Compiled Using : g++
//Version        : GCC 4.9.1
//Input for your program will be provided from STDIN
//Print out all output from your program to STDOUT
#include <iostream>
#include <string>
#include <algorithm>
#include <climits> 
#include <cmath>


using namespace std;

void irregularity(int bit, int K, int N, int val, int target_level) {
	if (N > target_level) {
		return;
	}
	if (target_level == N ) {
		int level_begin = pow(2, N);
		if (K - 1== val % level_begin) {
			cout << bit;
		}
		return;
	}
	
	if (bit == 0) {
		irregularity(0, K, N + 1, (val * 2) , target_level);
		irregularity(1, K, N + 1, (val * 2) + 1, target_level);
	}
	else {
		irregularity(1, K, N + 1, (val * 2), target_level);
		irregularity(0, K, N + 1, (val * 2)  + 1, target_level);
	}
}

int main() {

	int N, K;
	cin >> N >> K;
	if (pow(2, N) < K) {
		cout << -1;
		return 0;
	}
	irregularity(0, K, 0, 1, N);

	return 0;
}

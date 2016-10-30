#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXX 10

int dp_pascal_triangle_left_upper_half(int n) {
	int memo[MAXX + 1][MAXX + 1];
	int i, j;
	memo[0][0] = 1;
	//base case
	memo[1][0] = 1;
	memo[0][1] = 1;

	for (i = 2; i <= n; i++) {
		memo[i][0] = 1;
		memo[0][i] = 1;
	}

	for (i = 2; i <= n; i++) {
		for (j = 1; j < i; j++) {
			memo[i - j][j] = memo[i - j][j - 1] + memo[i - j - 1][j];
		}
	}

	int sum_of_binomial_coefs = 0;
	for (j = 0; j <= n; j++) {
		sum_of_binomial_coefs += memo[n - j][j];
	}
	return sum_of_binomial_coefs;
}

//Lower left half
int dp_pascal_triangle(int n) {
	int memo[11][11];
	int i,j;
	for (i = 1; i <= n; i++) {
		memo[i][0] = 1;
		memo[i][i] = 1;
	}
	for (i = 2; i <= n; i++) {
		for (j = 1; j < i; j++) {
			memo[i][j] = memo[i - 1][j - 1] + memo[i - 1][j];
		}
	}

	int sum_of_coefs = 0;
	for (j = 0; j <= n; j++) {
		sum_of_coefs += memo[n][j];
	}
	return sum_of_coefs;
}

int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	int N, X;

	cin >> N;
	cin >> X;
	int all_possible_combinations = dp_pascal_triangle_left_upper_half(N) -1;
	if (X < all_possible_combinations) {
		cout << all_possible_combinations - X << endl;
	}
	else {
		cout << X - all_possible_combinations << endl;
	}
	//dp_pascal_triangle(N);

	return 0;
}

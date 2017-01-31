//Problem        : Chocolate Fix
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

int calculate_chocolates(int N, int M, int amount) {
	int num_of_chocolates = 0;
	int temp;
	num_of_chocolates = amount / N;
	int additional = 0;
	temp = num_of_chocolates;
	int rem;
	while (1) {
		if (temp / M == 0) {
			if ((additional + rem) == M)
				num_of_chocolates++;
			break;
		}
		additional = temp / M;
		rem = temp % M;
		num_of_chocolates += additional;
		temp = additional;
	}
		return (num_of_chocolates);
}

int main() {
	int N, M, P;
	//vector<int> amounts;

	cin >> N >> M >> P;
	while (P--) {
		int am;
		cin >> am;
		//amounts.push_back(am);
		cout << calculate_chocolates(N, M, am) << endl;
	}
	return 0;
}

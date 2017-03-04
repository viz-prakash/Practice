#include <iostream>
#include <string>

using namespace std;

// https://leetcode.com/problems/largest-palindrome-product/?tab=Description 
// Problem number 479

class Solution {
public:
	bool is_palindrome(string product_str) {
		int product_len = product_str.size() - 1;
		int mid = (product_len) / 2;
		for (int i = mid; i >= 0; i--) {
			if (product_str[i] != product_str[product_len - i]) {
				return false;
			}
		}
		return true;
	}
	// This is inefficient
	int largestPalindrome1(int n) {
		int MOD = 1337;
		long long largest_num = 0;
		long long product = 0;
		switch (n) {
		case 1:
			largest_num = 9;
			break;
		case 2:
			largest_num = 99;
			break;
		case 3:
			largest_num = 999;
			break;
		case 4:
			largest_num = 9999;
			break;
		case 5:
			largest_num = 99999;
			break;
		case 6:
			largest_num = 999999;
			break;
		case 7:
			largest_num = 9999999;
			break;
		case 8:
			largest_num = 99999999;
			break;
		}
		long long largest_palindrome = -1;

		product = largest_num * largest_num;
		int sum_largest = 2 * largest_num;
		for (int sum = sum_largest; sum >largest_num; sum--) {
			int mid = (sum + 1) / 2;
			long long i, j;
			if (sum % 2 == 0) {
				j = mid;
			}
			else {
				j = mid - 1;
			}
			for (i = mid; i <= largest_num; i++, j--) {
				product = i*j;
				string product_str = to_string(product);
				if (is_palindrome(product_str)) {
					cout << product;
					return product % 1337;
				}
			}
		}
	}

	int largestPalindrome(int n) {
		long long largest_num = pow(10, n)-1;
		long long largest_prod = largest_num * largest_num;
		int left_half = largest_prod / pow(10, n);
		while ( true) {
			long long cur_palindrome = make_palindrome(left_half);
			for ( long long i = largest_num; cur_palindrome / i <= largest_num && (i * i) >= cur_palindrome; i-- ) {
				if (cur_palindrome % i == 0) {
					cout << cur_palindrome << endl;
					return cur_palindrome % 1337;
				}
			}
			left_half--;
		}
	}

	long long make_palindrome(long long n) {
		string num = to_string(n);
		string temp = num;
		for (int i = temp.length() - 1; i >= 0; i--) {
			num.append(temp, i, 1);
		}
		return stoll(num);
	}
};

int main() {

	Solution solution;

	cout << solution.largestPalindrome(5);

	return 0;
}
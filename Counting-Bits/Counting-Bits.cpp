#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int>dp(num + 1);
        dp[0] = 0;
        for(int i = 1 ; i <= num ; i++) {
            if( i%2 == 0 ) {
                dp[i] = dp[i/2];
            }
            else {
                dp[i] = dp[i/2] + 1;
            }
        }
        return dp;
    }
    
};

int main() {
    Solution sol;
    int n = 11;
    vector<int> num_of_bits = sol.countBits(n);
    for ( int i = 0 ; i <= n ; i++  ) {
        cout << num_of_bits[i] << ", ";
    }
    return 0;
}
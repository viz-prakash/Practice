#include <iostream>
#include <vector>

using namespace std;



class node {
    public:
        long long int diff;
        int inc_start_ind;
        int dec_start_ind;
        node() {
            inc_start_ind = -1 ;
            dec_start_ind = -1 ;
            diff = 0;
        }
};

void upvotes_inc_dec_diff_count(vector<int> &input, int N, int K) {
    //long long int inc_dec_diff;
    vector<vector<node>> dp(K + 1 , vector<node>(N - K + 1, node())); 
    //base case window size 1 
    for( int i = 0 ;i <= N - K ; i++ ) {
        dp[1][i].diff = 0;
    }
    //start from window size 2
    for (int k = 2; k <= K; k++ ) {
        for( int i = 0 ;i <= N - K ; i++ ) {
            if ( input[i + k - 1] > input[i + k - 2]) {
                if ( dp[k-1][i].inc_start_ind == -1 ) {
                    dp[k][i].diff = dp[k-1][i].diff + 1;
                    dp[k][i].inc_start_ind = i -1 + k -1;
                }
                else {
                    dp[k][i].diff = dp[k-1][i].diff + (i - 1 + k - dp[k - 1][i].inc_start_ind);
                    dp[k][i].inc_start_ind = dp[k - 1][i].inc_start_ind; 
                }                
                dp[k][i].dec_start_ind = -1;
            }
            else if ( input[i + k - 1] < input[i + k -2] ) {
                if ( dp[k -1 ][i].dec_start_ind == -1) {
                    dp[k][i].diff = dp[k-1][i].diff - 1;
                    dp[k][i].dec_start_ind = i - 1 + k - 1;
                }
                else {
                    dp[k][i].diff = dp[k - 1][i].diff - (i - 1 + k - dp[ k - 1][i].dec_start_ind);
                    dp[k][i].dec_start_ind = dp[k - 1][i].dec_start_ind;
                }
                dp[k][i].inc_start_ind = -1;
            }
            else {
                if ( dp[k-1][i].inc_start_ind != -1 && dp[k-1][i].dec_start_ind == -1) {
                    dp[k][i].diff = dp[k-1][i].diff + ( i - 1 + k - dp[k - 1][i].inc_start_ind) - 1;
                    dp[k][i].dec_start_ind = i - 1 + k - 1;
                    dp[k][i].inc_start_ind = dp[k-1][i].inc_start_ind;
                }
                else if (dp[k - 1][i].dec_start_ind != -1 && dp[k-1][i].inc_start_ind == -1) {
                    dp[k][i].diff = dp[k-1][i].diff - (i - 1 + k - dp[k - 1][i].dec_start_ind) + 1;
                    dp[k][i].inc_start_ind =  i - 1 + k - 1;
                    dp[k][i].dec_start_ind = dp[k-1][i].dec_start_ind;
                }
                else if (dp[k-1][i].inc_start_ind != -1 && dp[k-1][i].dec_start_ind != -1) {
                    dp[k][i].diff = dp[k-1][i].diff + ( i - 1 + k - dp[k - 1][i].inc_start_ind) - (i - 1 + k - dp[k - 1][i].dec_start_ind); 
                    dp[k][i].dec_start_ind = dp[k-1][i].dec_start_ind;
                    dp[k][i].inc_start_ind = dp[k-1][i].inc_start_ind;
                }
                else {
                    dp[k][i].inc_start_ind =  i - 1 + k - 1;
                    dp[k][i].dec_start_ind = i - 1 + k - 1;
                }
            }
        }
    }
    //print the diff in last row
    for ( int i = 0 ; i <= N - K ; i++ ) {
        cout << dp[K][i].diff << endl;
    }
}

void brute_force_upvote_diff(vector<int> input, int N, int K) {
    int i,j;
    int diff, num_of_elements, non_dec = 0, sec_num_of_elements;
    for( i = 1; i <= N - K + 1 ; i++) {
        diff =0;
        num_of_elements = 1;
        non_dec = 0;
        sec_num_of_elements = 1;
        for ( j = 1 ; j < K ; j++) {
            if (input[i + j] > input[i + j - 1]) {
                if ( non_dec <= 0 ) {
                    diff += sec_num_of_elements;
                    num_of_elements = sec_num_of_elements + 1;
                    sec_num_of_elements = 1;
                    non_dec = 1;
                }
                else {
                    diff += num_of_elements;
                    num_of_elements++;
                }
            }
            else if ( input [i + j] < input [ i + j - 1]) {
                if( non_dec >= 0) {
                    diff -= sec_num_of_elements;
                    num_of_elements = sec_num_of_elements + 1;
                    sec_num_of_elements = 1;
                    non_dec = -1;
                }
                else {
                    diff -= num_of_elements;
                    num_of_elements++;
                }
            }
            else {
                if ( non_dec == 1) {
                    diff = diff + num_of_elements - sec_num_of_elements;
                }
                else {
                    diff = diff - num_of_elements + sec_num_of_elements;
                }
                num_of_elements++;
                sec_num_of_elements++;
            }
        }
        cout << diff << endl;
    }
}

class series_stat{
    public:
        int stat;
        int element_count_inc;
        int element_count_dec;

        series_stat() {
            stat = 0;
            element_count_dec = 0;
            element_count_inc = 0;
        }
};

void upvote_diff(vector<long long int> input, int N, int  K) {
    int i, j;
    vector<series_stat> rem_series_info(N, series_stat());
    vector<series_stat> pres_series_info(N, series_stat());
    //create rem_series_info stat
    j = N - 1;
    for ( i = N - 2; i >= 0 ; i--) {
        // for number of element remaining in series
        if ( input[i] < input[i+1]) {
            rem_series_info[i].stat = 1;
            rem_series_info[i].element_count_inc = rem_series_info[i + 1].element_count_inc + 1;
        }
        else if ( input[i] > input[i+1]) {
            rem_series_info[i].stat = -1;
            rem_series_info[i].element_count_dec = rem_series_info[i + 1].element_count_dec + 1;
        }
        else {
            // no need to set stat to 0 as already initialized to 0
            if ( rem_series_info[i+1].stat == 1) {
                rem_series_info[i].element_count_inc = rem_series_info[i+1].element_count_inc + 1;
                rem_series_info[i].element_count_dec = 1;
            }
            else if (rem_series_info[i+1].stat == -1) {
                rem_series_info[i].element_count_dec = rem_series_info[i+1].element_count_dec + 1;
                rem_series_info[i].element_count_inc = 1;
            }
            else {
                rem_series_info[i].element_count_inc = rem_series_info[i+1].element_count_inc + 1;
                rem_series_info[i].element_count_dec = rem_series_info[i+1].element_count_dec + 1;
            }
        }
        if (rem_series_info[i].element_count_dec == K) {
            rem_series_info[i].element_count_dec = K - 1;
        }
        if (rem_series_info[i].element_count_inc == K) {
            rem_series_info[i].element_count_inc = K - 1;
        }
        // For number of element in series
        if ( input[j - i] > input[j - i -1]) {
            pres_series_info[j - i].stat = 1;
            pres_series_info[j - i].element_count_inc = pres_series_info[j - i - 1].element_count_inc + 1;
        }
        else if ( input[j - i] < input[j - i -1]) {
            pres_series_info[j - i].stat = -1;
            pres_series_info[j - i].element_count_dec = pres_series_info[j - i - 1].element_count_dec + 1;
        }
        else {
            if ( pres_series_info[j - i -1].stat == 1) {
                pres_series_info[j - i].element_count_inc = pres_series_info[j - i - 1].element_count_inc + 1;
                pres_series_info[j - i].element_count_dec = 1;
            }
            else if ( pres_series_info[j - i - 1].stat == -1){
                pres_series_info[j - i].element_count_dec = pres_series_info[j - i - 1].element_count_dec + 1;
                pres_series_info[j - i].element_count_inc = 1;
            }
            else {
                pres_series_info[j - i].element_count_inc = pres_series_info[j - i - 1].element_count_inc + 1;
                pres_series_info[j - i].element_count_dec = pres_series_info[j - i - 1].element_count_dec + 1;
            }
        }
        if (pres_series_info[j - i].element_count_inc == K) {
            pres_series_info[j - i].element_count_inc = K - 1;
        }
        if (pres_series_info[j - i].element_count_dec == K ) {
            pres_series_info[j - i].element_count_dec = K - 1;
        }
    }

    //calculate diff in first window
    i = 0;
    int  num_of_elements, non_dec = 0, sec_num_of_elements, prev_diff;
    long long int diff =0;
    num_of_elements = 1;
    non_dec = 0;
    sec_num_of_elements = 1;
    for ( j = 1 ; j < K ; j++) {
        if (input[i + j] > input[i + j - 1]) {
            if ( non_dec <= 0 ) {
                diff += sec_num_of_elements;
                num_of_elements = sec_num_of_elements + 1;
                non_dec = 1;
            }
            else {
                diff += num_of_elements;
                num_of_elements++;
            }
            sec_num_of_elements = 1;
        }
        else if ( input [i + j] < input [ i + j - 1]) {
            if( non_dec >= 0) {
                diff -= sec_num_of_elements;
                num_of_elements = sec_num_of_elements + 1;
                non_dec = -1;
            }
            else {
                diff -= num_of_elements;
                num_of_elements++;
            }
			sec_num_of_elements = 1;
        }
        else {
            if ( non_dec == 1) {
                diff = diff + num_of_elements - sec_num_of_elements;
            }
            else {
                diff = diff - num_of_elements + sec_num_of_elements;
            }
            num_of_elements++;
            sec_num_of_elements++;
        }
    }
    cout << diff << endl;
    //slide the widow till the end
    for ( i = 1; i <= N - K; i++) {
        //prev_diff = diff;
        // remove contribution of element just got out of window
        if ( rem_series_info[i-1].stat == 1 ) {
            diff -= rem_series_info[i-1].element_count_inc;
        }
        else if ( rem_series_info[i-1].stat == -1) {
            diff += rem_series_info[i-1].element_count_dec;
        }
        else {
            diff -= rem_series_info[i-1].element_count_inc;
            diff += rem_series_info[i-1].element_count_dec;
        }

        // add contribution of element just got into window
        if ( pres_series_info[ i + K -1 ].stat == 1) {
            diff += pres_series_info[i + K - 1].element_count_inc;
        }
        else if ( pres_series_info[ i + K - 1].stat == -1) {
            diff -= pres_series_info[i + K - 1].element_count_dec;
        }
        else {
            diff += pres_series_info[i + K - 1].element_count_inc;
            diff -= pres_series_info[i + K - 1].element_count_dec;
        }
        cout << diff << endl;
    }
    
}

int main() {
    int N, K;
    cin >> N >> K;
    //long int val = -2033832544;
    //cout << val << endl;
    vector<long long int> input(N + 1);
    for ( int i = 0 ; i < N ; i++ ) {
        cin >> input[i];
    }    
    //upvotes_inc_dec_diff_count(input, N, K);
    //brute_force_upvote_diff(input, N, K);
    upvote_diff(input, N, K);
    return 0;
}
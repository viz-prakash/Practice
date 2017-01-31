#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <map>
using namespace std;


class mem_alloc {
public:
	int finish_time;
	int mem_allocated;
	mem_alloc(int finish_time, int mem_alloc) {
		this->finish_time = finish_time;
		this->mem_allocated = mem_alloc;
	}
};

int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	int N, M;
	cin >> N >> M;
	int temp = N;
	int dur, mem;
	long long int time = 0;
	// <mem_alloc> finish_time;
	multimap< long long int, int> finish_time;
	while (temp--) {
		cin >> dur >> mem;
		if (mem <= M) {
			finish_time.insert(make_pair(time + dur, mem));
			M -= mem;
		}
		else {
			while (M < mem) {

				time = finish_time.begin()->first;
				for (multimap<long long int, int>::iterator it = finish_time.begin(); it != finish_time.end() && it->first == time; it++) {
					M += it->second;
				}
				finish_time.erase(time);
			}
			finish_time.insert(make_pair(time + dur, mem));
			M -= mem;
		}
	}
	
	cout << (finish_time.end()--)->first;
	return 0;
}
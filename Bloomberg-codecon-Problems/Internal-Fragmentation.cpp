//Problem        : long long internal Fragmentation
//Language       : C++
//Compiled Using : g++
//Version        : GCC 4.9.1
//Input for your program will be provided from STDIN
//Prlong long int out all output from your program to STDOUT


#include <iostream>
#include <string>
#include <algorithm>
#include <climits> 
#include <vector>

using namespace std;
 int main() {
	unsigned long long int N;
	vector< unsigned long long int> file_sizes;
	long int sector_size;
	cin >> N;
	long int temp = N;
	long int filesize;
	while (temp--) {
		cin >> filesize;
		file_sizes.push_back(filesize);
	}
	cin >> sector_size;
	long long int i = 0;
	long long int total_consumed_sectors = 0;

	while(i < N) {
		if (file_sizes[i] % sector_size == 0) {
			total_consumed_sectors += file_sizes[i] / sector_size;
		}
		else {
			total_consumed_sectors += ((file_sizes[i] / sector_size) + 1);
		}
		i++;
	}
	cout << total_consumed_sectors * sector_size;
	return 0;
}


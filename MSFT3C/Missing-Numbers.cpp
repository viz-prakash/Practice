#include <iostream>
#include <list>
#include <sstream>
using namespace std;


void missing_numbers(std::list<int> input) {
	input.sort();
	int first = input.front();
	int last = input.back();
	int totalnums = last - first + 1;
	int * array = new int[totalnums];
	for (int num = 0; num < totalnums; num++) {
		array[num] = 0;
	}
	//bool array[ totalnums] = { 0 };
	for (int num : input) {
		array[num - first] = 1;
	}
	for (int num = 0; num < totalnums; num++) {
		if (array[num] == 0) {
			cout << num + first << " ";
		}
	}
	cout << std::endl;
	delete[] array;
}

int main() {
	int m = 0;
	//std::vector<int> line = {};
	string line;
	std::list<int> list;
	int num;
	cin >> m;
	std::cin.ignore(1, '\n');
	while (m--) {
		std::getline(cin, line);
		//cin >> line;
		std::istringstream iss(line);
		//int c;
		while (iss >> num) {
			list.push_back(num);
		}
		//cin >> num;
		//line.push_back(num);
		missing_numbers(list);
		list.clear();
	}
	return 0;
}
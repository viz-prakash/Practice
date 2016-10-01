#include <iostream>
#include <list>

using namespace std;

int main() {
	int buffer1[3];
	int buffer2[3];

	while (1) {
		fscanf(stdin, "%d%d%d", &buffer1[0], &buffer1[1], &buffer1[2]);
		if (feof(stdin)) {
			return 0;
		}
		fscanf(stdin, "%d%d%d", &buffer2[0], &buffer2[1], &buffer2[2]);
		/*
		if ((buffer1[0] * buffer1[0] + buffer1[1] * buffer1[1] + buffer1[2] * buffer1[2]) !=
		(buffer2[0] * buffer2[0] + buffer2[1] * buffer2[1] + buffer2[2] * buffer2[2])) {
		cout << "NO" << endl;
		}
		*/
		std::list<int> first(buffer1, buffer1 + sizeof(buffer1) / sizeof(int));
		std::list<int> sec(buffer2, buffer2 + sizeof(buffer2) / sizeof(int));
		first.sort();
		sec.sort();
		std::list<int>::iterator it = first.begin();
		std::list<int>::iterator it1 = sec.begin();
		int f1 = *it;
		//first.pop_front();
		it++;
		int f2 = *it;
		//first.pop_front();
		it++;
		int f3 = *it;
		it++;
		//first.pop_front();

		int g1 = *it1;
		//sec.pop_front();
		*it1++;
		int g2 = *it1;
		//sec.pop_front();
		*it1++;
		int g3 = *it1;
		//sec.pop_front();
		*it1++;
		int small = sec.front();
		if ((f1*f1 + f2*f2 == f3*f3) && (g1*g1 + g2*g2 == g3*g3) && f3 == g3 && f1 == g1) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
		first.clear();
		sec.clear();
		if (feof(stdin)) {
			return 0;
		}

	}

	return 0;
}
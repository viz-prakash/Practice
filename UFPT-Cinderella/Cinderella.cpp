#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	long bc;
	cin >> bc;
	double * bv = new double[bc];
	int temp = 0;
	double totalwater = 0;
	double biggest = -1;
	long bi;
	double eq_amount;
	while (temp < bc) {
		cin >> bv[temp];
		if (bv[temp] > biggest) {
			biggest = bv[temp];
			bi = temp;
		}
		totalwater += bv[temp];
		temp++;
	}
	//std::list<int> li(bv, bv + bc * sizeof(long));
	//li.sort();
	eq_amount = totalwater / bc;
	long move = 0;
	/*
	for (std::list<int>::iterator it = li.begin; it < li.end; it++) {
	if (*it > eq_amount) {
	move++;
	}
	}*/
	//vector<int> myvector(bv, bv + bc);
	//sort(myvector.begin(), myvector.end());
	int dt = 0;
	for (int i = 0; i < bc; i++) {
		if (bv[i] > eq_amount) {
			//move++;
			bool dtflat = false;
			for (int j = 0; j < bc; j++) {
				if (i == bi && dt != 0)
					continue;
				if (eq_amount - bv[j] == bv[i] - eq_amount) {
					dt++;
					dtflat = true;
				}
			}
			if (!dtflat || i == bi) {
				move++;
			}
		}
	}
	if (move == 0)
		cout << dt << endl;
	else
		cout << dt + move << endl;
	return 0;
}
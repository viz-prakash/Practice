#include <iostream>

//using namespace std;
#define num_of_days 1826

bool is_visa_valid(int *visits) {
	for (int i = 1; i < num_of_days - 178; i++) {
		int total_days_of_visit_180 = 0;
		int start_day_of_visit = 0;
		if (visits[i] == 1) {
			start_day_of_visit = i;
			int j;
			for (j = 1; j < 180 && i + j < num_of_days + 1; j++) {
				if (visits[i + j] == 0) {
					continue;
				}
				else if (visits[i + j] == -1) {
					total_days_of_visit_180 += i + j - start_day_of_visit + 1;
					start_day_of_visit = -1;
				}
				else {
					start_day_of_visit = i + j;
				}
			}
			if (j < 180 || start_day_of_visit != -1) {
				total_days_of_visit_180 += i + j - start_day_of_visit;
			}
			if (total_days_of_visit_180 > 90) {
				return false;
			}
		}
	}
	return true;
}



int main() {
	int num_of_visits;
	int visits[num_of_days + 1] = { 0 };
	std::cin >> num_of_visits;
	int start_day_of_visit, end_day_of_visit;
	int i;
	while (num_of_visits--) {
		std::cin >> start_day_of_visit >> end_day_of_visit;
		for (i = start_day_of_visit; i <= end_day_of_visit; i++) {
			visits[i] = 1;
		}
		//visits[start_day_of_visit ] = 1;
		//visits[end_day_of_visit ] = -1;
	}
	int day_count = 0;
	for (i = 1; i <= 180; i++) {
		if (visits[i] == 1) {
			day_count++;
			if (day_count > 90) {
				std::cout << "No" << std::endl;
				return 0;
			}
		}
	}

	for (i = 181; i <= 1826; i++) {
		if (visits[i - 180] == 1) {
			day_count--;
		}
		if (visits[i] == 1) {
			day_count++;
		}
		if (day_count > 90) {
			std::cout << "No" << std::endl;
			return 0;
		}
	}
	std::cout << "Yes" << std::endl;

	/*
	bool visa_validity = is_visa_valid(visits);
	if (visa_validity)
	std::cout << "Yes";
	else
	std::cout << "No";
	std::cout << std::endl;*/
	/*char c;
	std::cin >> c;
	*/
	return 0;
}
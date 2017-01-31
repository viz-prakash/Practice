//Problem        : Diamonds in the Rough
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
#include <map>
#include <math.h>

using namespace std;

float x1, y11, x2, y2, x3, y3;
multimap<float, float> cordinates;

float ccw(float x1, float y1, float x2, float y2, float xp , float yp) {
	return ((x2 - x1)*(yp - y1) - (y2 - y1)*(xp - x1));
}

bool point_in_triangle(float x, float y) {
	if (ccw(x1, y11, x2, y2, x, y) < 0.0) {
		return false;
	}
	if (ccw(x2, y2, x3, y3,  x, y) < 0.0) {
		return false;
	}
	if (ccw( x3, y3, x1, y11, x, y) < 0.0) {
		return false;
	}
	return true;
}


int main() {
	float x, y;
	float min_x, min_y, max_x, max_y;
	cin >> x >> y;
	cordinates.insert(make_pair(x, y));
	cin >> x >> y;
	cordinates.insert(make_pair(x, y));
	cin >> x >> y;
	cordinates.insert(make_pair(x, y));
	if (cordinates.begin()->first == (++cordinates.begin())->first) {
		if (cordinates.begin()->second > (++cordinates.begin())->second) {
			x1 = cordinates.begin()->first;
			y11 = (++cordinates.begin())->second;
			x2 = x1;
			y2 = cordinates.begin()->first;
			x3 = cordinates.rbegin()->first;
			y3 = cordinates.rbegin()->second;
		}
		else {
			x1 = cordinates.begin()->first;
			y11 = cordinates.begin()->second;
			x2 = x1;
			y2 = (++cordinates.begin())->second;
			x3 = cordinates.rbegin()->first;
			y3 = cordinates.rbegin()->second;
		}
	}
	else if ((++cordinates.begin())->first == cordinates.rbegin()->first) {
		if ((++cordinates.begin())->second > cordinates.rbegin()->second) {
			x1 = cordinates.begin()->first;
			y11 = cordinates.begin()->second;
			x2 = cordinates.rbegin()->first;
			y2 = cordinates.rbegin()->second;
			x3 = x2;
			y3 = (++cordinates.begin())->second;
		}
		else {
			x1 = cordinates.begin()->first;
			y11 = cordinates.begin()->second;
			x2 = cordinates.rbegin()->first;
			y2 = (++cordinates.begin())->second;
			x3 = x2;
			y3 = cordinates.rbegin()->second;
		}
	}
	else {
		x1 = cordinates.begin()->first;
		y11 = cordinates.begin()->second;
		x2 = (++cordinates.begin())->first;
		y2 = (++cordinates.begin())->second;
		x3 = cordinates.rbegin()->first;
		y3 = cordinates.rbegin()->second;
	}

	if (y2 > y3) {
		x2 = x2 + x3;
		x3 = x2 - x3;
		x2 = x2 - x3;
		y2 = y2 + y3;
		y3 = y2 - y3;
		y2 = y2 - y3;
	}
	else if (y2 == y3) {
		if (x2 > x3) {
			x2 = x2 + x3;
			x3 = x2 - x3;
			x2 = x2 - x3;
			y2 = y2 + y3;
			y3 = y2 - y3;
			y2 = y2 - y3;
		}
	}

	min_x = ceil(min(min(x1, x2), x3));
	min_y = ceil(min(min(y11, y2), y3));
	max_x = floor(max(max(x1, x2), x3));
	max_y = floor(max(max(y11, y2), y3));
	long long int count = 0;

	for ( float x = min_x; x <= max_x; x++) {
		for (float y = min_y; y <= max_y; y++) {
			if (point_in_triangle(x, y)) {
				count++;
			}
		}
	}

	cout << count;
	return 0;
}

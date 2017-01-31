//Problem        : Truths of Predatation
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
using namespace std;

//unordered_map<int, int> eaters;
//unordered_map<int, int> eatables;
//unordered_map<int, int> same_type;

int main() {
	int N, K, C, X, Y;
	cin >> N >> K;
	//graph of eaters
	vector< vector<int> > eaters(N + 1, vector<int>(N + 1, 0));
	//graph of sametype
	vector< vector<int> > same_type(N + 1, vector<int>(N + 1,0));

	int false_clues = 0;
	bool cur_clue;
	for (int k = 0; k < K; k++) {
		cin >> C >> X >> Y;
		cur_clue = true;
		if (X > N || Y > N) {
			cur_clue = false;
			false_clues++;
			continue;
		}
		/*
		//check if X has any type
		bool x_has_category = false;
		for (int i = 1; i <= N; i++) {
			if (same_type[X][i] == 1) {
				x_has_category = true;
				break;
			}
		}
		//check if X's eater has a type
		bool x_eater_has_category = false;
		for (int i = 1; i <= N; i++) {
			if(eaters[i][X] == 1) {
				for (int j = 1; j <= N; j++) {
					if (same_type[i][j] == 1) {
						x_eater_has_category = true;
						break;
					}
				}
				break;
			}
		}
		//check if Y's eater has a type
		bool y_eater_has_category = false;
		for (int j = 1; j <= N; j++) {
			if (eaters[j][Y] == 1) {
				for (k = 1; k <= N; k++) {
					if (same_type[j][k] == 1) {
						y_eater_has_category = true;
						break;
					}
				}
				break;
			}
		}
		//check if Y has a category
		bool y_has_catagory = false;
		for (int i = 1; i <= N; i++) {
			if (same_type[Y][i] == 1) {
				y_eater_has_category = true;
				break;
			}
		}
		*/
		if (C == 1) {
			int i, j;
			if (same_type[X][Y] == 1) {
				continue;
			}

			if (eaters[X][Y] == 1 || eaters[Y][X] == 1) {
				cur_clue = false;
			}

			if (cur_clue) {
				//eaters of X and Y are not of same type
				for (i = 1; i <= N; i++) {
					if (eaters[i][X] == 1 && same_type[i][Y] == 1) {
						cur_clue = false;
						break;
					}
				}
				//eaters of X are not eaten by any Ys types
				if (cur_clue) {
					for (i = 1; i <= N; i++) {
						if (eaters[i][X] == 1 && eaters[Y][i] == 1) {
							cur_clue = false;
							break;
						}
					}
				}
			}
			
			if (cur_clue) {
				//eaters of Y are not same type of Xs
				for (i = 1; i <= N; i++) {
					if (eaters[i][Y] == 1 && same_type[i][X] == 1) {
						cur_clue = false;
						break;
					}
				}
				//eaters of Y are not eaten by Xs
				for (i = 1; i <= N; i++) {
					if (eaters[i][Y] == 1 && eaters[X][i] == 1) {
						cur_clue = false;
						break;
					}
				}
			}

			if (cur_clue) {
				//update all same type of X and Y to each other
				same_type[X][Y] = 1;
				same_type[Y][X] = 1;
				for (i = 1; i <= N; i++) {
					if (same_type[X][i] == 1) {
						same_type[i][Y] = 1;
						same_type[Y][i] = 1;
						for (j = 1; j <= N; j++) {
							if (same_type[Y][j] == 1) {
								same_type[i][j] = 1;
								same_type[j][i] = 1;
							}
						}
					}
				}

				//TODO update eaters too from both sides X and Y for each other
				for (i = 1; i <= N; i++) {
					if (eaters[Y][i] == 1 || eaters[X][i] == 1) {
						eaters[X][i] = 1;
						eaters[Y][i] = 1;
						for (j = 1; j <= N; j++) {
							if (same_type[X][j] == 1) {
								eaters[j][i] = 1;
							}
							if (same_type[Y][j] == 1) {
								eaters[j][i] = 1;
							}
						}
					}							
				}

				// update if X and Y are eaten by too
				for (i = 1; i <= N; i++) {
					if (eaters[i][X] == 1 || eaters[i][Y] == 1) {
						eaters[i][X] = 1;
						eaters[i][Y] = 1;
						for (j = 1; j <= N; j++) {
							if (same_type[X][j] == 1) {
								eaters[i][j] = 1;
							}
							if (same_type[Y][j] == 1) {
								eaters[i][j] == 1;
							}
						}
					}
				}
			}
		}
		else {
			if (eaters[X][Y] == 1) {
				continue;
			}
			else if (X == Y) {
				cur_clue = false;
			}
			else if (same_type[X][Y] == 1) {
				cur_clue = false;
			}
			else {
				int i, j;
				//type of Xs are not eaten by type of Ys
				for (i = 1; i <= N; i++) {
					if (eaters[Y][i] == 1 && same_type[X][i] == 1) {
						cur_clue = false;
						break;
					}
				}
				if (cur_clue) {
						//any other type other than X already eating Ys type
					for (i = 1; i <= N; i++) {
						if (eaters[i][Y] == 1 && eaters[X][i] == 1) {
							cur_clue = false;
							break;
						}
					}
				}
				if (cur_clue) {
					//update same types of all Ys eaten by X
					for (i = 1; i <= N; i++) {
						if (eaters[X][i] == 1) {
							same_type[i][Y] = 1;
							same_type[Y][i] = 1;
							for (j = 1; j <= N; j++) {
								if (same_type[Y][j] == 1) {
									same_type[j][i] = 1;
									same_type[i][j] = 1;
								}
							}
						}
					}
				
					//update same type of all eaters of same type(of Y)
					for (i = 1; i <= N; i++) {
						if (eaters[i][Y] == 1 && same_type[i][X] == 0 && i != X) {
							same_type[X][i] = 1;
							same_type[i][X] = 1;
							for (j = 1; j <= N; j++) {
								if (same_type[i][j] == 1) {
									same_type[X][j] = 1;
									same_type[j][X] = 1;
									for (int k = 1; k <= N; k++) {
										if (same_type[X][k] == 1) {
											same_type[j][k] = 1;
											same_type[k][j] = 1;
										}
									}
								}
							}
							break;
						}
					}

					//updates eaters
					eaters[X][Y] = 1;
					for ( i = 1; i <= N; i++) {
						if (same_type[Y][i] == 1) {
							eaters[X][i] = 1;
							for (j = 1; j <= N; j++) {
								if (same_type[X][j] == 1) {
									eaters[j][i] = 1;
								}
							}
						}
					}
					//

				}
			}
		}
		if (!cur_clue) {
			false_clues++;
		}
	}
	cout << false_clues;
	return 0;
}

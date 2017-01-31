//Problem        : Bishop
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

vector<vector<int>> chess_board(8, vector<int>(8, -1));

void bishop_moves_tl_br(int row, int col) {
	int i, j;
	for (i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++) {
		if (chess_board[i][j] == -1) {
			chess_board[i][j] = chess_board[row][col] + 1;
		}
	}
	for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
		if (chess_board[i][j] == -1) {
			chess_board[i][j] = chess_board[row][col] + 1;
		}
	}

	
}

void bishop_moves_bl_tr(int row, int col) {
	int i, j;
	for (i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--) {
		if (chess_board[i][j] == -1) {
			chess_board[i][j] = chess_board[row][col] + 1;
		}
	}
	for (i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++) {
		if (chess_board[i][j] == -1) {
			chess_board[i][j] = chess_board[row][col] + 1;
		}
	}
}


int main() {
	int pos, target;
	cin >> pos >> target;

	int row = (pos - 1) / 8;
	int col = (pos - 1) % 8;
	int target_row = (target - 1) / 8;
	int target_col = (target - 1) % 8;
	chess_board[row][col] = 0;
	int i, j;
	bishop_moves_tl_br(row, col);
	bishop_moves_bl_tr(row, col);
	
	for (i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--) {
		bishop_moves_tl_br(i, j);
	}
	

	for (i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++) {
		bishop_moves_tl_br(i, j);
	}
	
	for (i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++) {
		bishop_moves_bl_tr(i, j);
	}

	for (i = row - 1, j = col - 1; i >= 0 && j >= 0; j--, i--) {
		bishop_moves_bl_tr(i, j);
	}

	cout << chess_board[target_row][target_col];
	return 0;
}

#include <iostream>
#include "check.h"

using namespace std;

bool check(int* board, int n_row, int n_col, int player) {

	// for each cell, check if there is a line of 5 consecutive pieces of the same color
	for (int i = 0; i < n_row; i++) 
		for (int j = 0; j < n_col; j++) {
			// check column
			if(j + 5 <= n_col) {
				bool check = true;
				for(int k = 0; k < 5; k++) 
					if(board[i*n_col + j + k] != player) check = false;
				if(check) return true;
			}
			// check row
			if(i + 5 <= n_row) {
				bool check = true;
				for(int k = 0; k < 5; k++) 
					if(board[(i + k)*n_col + j] != player) check = false;
				if(check) return true;
			}
			// check diagonal
			if(i + 5 <= n_row && j + 5 <= n_col) {
				bool check = true;
				for(int k = 0; k < 5; k++) 
					if(board[(i + k)*n_col + j + k] != player) check = false;
				if(check) return true;
			}
			// check anti-diagonal
			if(i - 5 >= 0 && j + 5 <= n_col) {
				bool check = true;
				for(int k = 0; k < 5; k++) 
					if(board[(i - k)*n_col + j + k] != player) check = false;
				if(check) return true;
			}
		}
	return false;
}
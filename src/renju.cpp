#include <iostream>
#include "board.h"
#include "draw.h"
#include "banhand.h"

using namespace std;

#include <termios.h>
#include <getch.h>
#include <vars.h>
#include <check.h>

void run() {
	int n_rows, n_cols;
	printf("Please input the size of the board(row cols): ");
	scanf("%d%d", &n_rows, &n_cols);

	while(n_rows < 5 || n_cols < 5){	//判断棋盘大小是否合规
	if(n_rows < 5 || n_cols < 5) printf("Bad board size! Please input again(row cols):");
	scanf("%d%d", &n_rows, &n_cols);
	}

	int *board = new int[n_rows * n_cols];

	int n_blocks = n_rows * n_cols;

	for(int i = 0; i < n_blocks; i++) board[i] = STATUS_BLANK;

	int current_row = 0;
	int current_col = 0;
	int current_player = PLAYER_ONE;

	board[current_row * n_cols + current_col] = STATUS_CHOICE;
	int pre_status = STATUS_BLANK;

	while(true) {
		draw_board(board, n_rows, n_cols, current_player);
		char op;
		op = getch();
		op = toupper(op);
		
		int next_row = current_row;
		int next_col = current_col;

		if(op == 'Q') break;
		if(op == 'W') next_row--;
		if(op == 'S') next_row++;
		if(op == 'A') next_col--;
		if(op == 'D') next_col++;

		next_row = max(0, min(n_rows - 1, next_row));
		next_col = max(0, min(n_cols - 1, next_col));

		if(op == ' ') {
			int &status = board[current_row * n_cols + current_col];
			if(pre_status > STATUS_BLANK) continue;
			status = current_player;
			pre_status = current_player;
			
			if(banhand(board, n_rows, n_cols,current_row, current_col)){	//判断禁手
				printf("Player used banned chess! Player 2 wins!\n");
				break;
			}

			if(check(board, n_rows, n_cols, current_player)) {	//判断胜利
				printf("Player %d wins!\n", current_player);
				break;
			}

			if(draw_check(board,n_blocks)) {	//判断是否平局
				printf("Game Draw!\n");
				break;
			}

			current_player = current_player ^ 1;
			continue;
		}
		
		board[current_row * n_cols + current_col] = pre_status;
		pre_status = board[next_row * n_cols + next_col];
		board[next_row * n_cols + next_col] = STATUS_CHOICE;

		swap(current_row, next_row);
		swap(current_col, next_col);

	}
}

int main() {

	run();
	return 0;
}

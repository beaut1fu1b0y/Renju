//草他奶的最烦这种一堆逻辑要判断的代码了，每次都忘记几个



#include <iostream>
#include "banhand.h"
#include "vars.h"
#include "check.h"
using namespace std;

bool banhand(int* board, int n_row, int n_col, int current_row, int current_col) {

    if(check(board,n_row,n_col,PLAYER_ONE) == true){    //黑方胜利情况下，判断长连
		for (int i = 0; i < n_row; i++) {
			for (int j = 0; j < n_col; j++) {
				// check column
				if(j + 6 <= n_col) {
					bool check = true;
					for(int k = 0; k < 6; k++) 
						if(board[i*n_col + j + k] != PLAYER_ONE) check = false;
						if(check) return true;
				}
				// check row
				if(i + 6 <= n_row) {
						bool check = true;
						for(int k = 0; k < 6; k++) 
							if(board[(i + k)*n_col + j] != PLAYER_ONE) check = false;
						if(check) return true;
				}
				// check diagonal
				if(i + 6 <= n_row && j + 6 <= n_col) {
						bool check = true;
						for(int k = 0; k < 6; k++) 
							if(board[(i + k)*n_col + j + k] != PLAYER_ONE) check = false;
						if(check) return true;
				}
				// check anti-diagonal
				if(i - 6 >= 0 && j + 6 <= n_col) {
						bool check = true;
						for(int k = 0; k < 6; k++) 
							if(board[(i - k)*n_col + j + k] != PLAYER_ONE) check = false;
						if(check) return true;
				}
			}
        }
    }

    if(check(board,n_row,n_col,PLAYER_ONE) == false){   //黑方未胜利情况下，判断三三禁手
		int sum = 0;
		for (int i = 0; i < n_row; i++) {
			for (int j = 0; j < n_col; j++) {
				//check column
				if(j + 4 <= n_col){
					bool check = true, included_current = false;
					for(int k = 0; k < 3; k++){
						if(board[i*n_col + j + k] != PLAYER_ONE) check = false;
						if(i == current_row && j + k == current_col) included_current = true;	//必须包含最后落子
					}
					if(check && included_current && (board[i*n_col + j + 3] == STATUS_BLANK && board[i*n_col + j - 1] == STATUS_BLANK) && (board[i*n_col + j + 4] == STATUS_BLANK || (board[i*n_col + j - 2] == STATUS_BLANK && j - 2 >= 0)) && (board[i*n_col + j + 3] != PLAYER_ONE && board[i*n_col + j - 1] != PLAYER_ONE)) sum++;	//须判断是否为活四 //活三须满足加一子可形成活四，因此一边不为空的三连不属于活三	//须判断左右的空是否跨行
				}
				//check row
				if(i + 4 <= n_row){
					bool check = true, included_current = false;
					for(int k = 0; k < 3; k++){
						if(board[(i + k)*n_col + j] != PLAYER_ONE) check = false;
						if((i + k) == current_row && j == current_col) included_current = true;
					}
					if(check && included_current && (board[(i + 3)*n_col + j] == STATUS_BLANK && board[(i - 1)*n_col + j] == STATUS_BLANK) && (board[(i + 4)*n_col + j] == STATUS_BLANK || (board[(i - 2)*n_col + j] == STATUS_BLANK && i - 2 >= 0)) && (board[(i + 3)*n_col + j] != PLAYER_ONE && board[(i - 1)*n_col + j] != PLAYER_ONE)) sum++;
				}
				//check diagonal
				if(i + 4 <= n_row && j + 4 <= n_col){
					bool check = true, included_current = false;
					for(int k = 0; k < 3; k++){
						if(board[(i + k)*n_col + j + k] != PLAYER_ONE) check = false;
						if((i + k) == current_row && (j + k) == current_col) included_current = true;
					}
					if(check && included_current && (board[(i - 1)*n_col + j - 1] == STATUS_BLANK && board[(i + 3)*n_col + j + 3] == STATUS_BLANK) && ((board[(i - 2)*n_col + j - 2] == STATUS_BLANK && i - 2 >= 0 && j - 2 >= 0) || board[(i + 4)*n_col + j + 4] == STATUS_BLANK) && (board[(i - 1)*n_col + j - 1] != PLAYER_ONE && board[(i + 3)*n_col + j + 3] != PLAYER_ONE)) sum++;
				}
				//check anti-diagonal
				if(i - 4 >= 0 && j + 4 <= n_col){
					bool check = true, included_current = false;
					for(int k = 0; k < 3; k++){
						if(board[(i - k)*n_col + j + k] != PLAYER_ONE) check = false;
						if((i - k) == current_row && (j + k) == current_col) included_current = true;
					}
					if(check && included_current && (board[(i + 1)*n_col + j - 1] == STATUS_BLANK && board[(i - 3)*n_col + j + 3] == STATUS_BLANK) && ((board[(i + 2)*n_col + j - 2] == STATUS_BLANK || board[(i - 4)*n_col + j + 4] == STATUS_BLANK && i + 2 <= n_row && j - 2 >= 0)) && (board[(i + 1)*n_col + j - 1] != PLAYER_ONE && board[(i - 3)*n_col + j + 3] != PLAYER_ONE)) sum++;
				}
			}
		}
		if(sum == 2) return true;
	}

    if(check(board,n_row,n_col,PLAYER_ONE) == false){   //黑方未胜利情况下，判断四四禁手	//总觉得有一些我尚未发现的bug
		int count = 0;
		for (int i = 0; i < n_row; i++) {
			for (int j = 0; j < n_col; j++) {
				//check column
				if(j + 4 <= n_col) {
					bool check = true;
					for(int k = 0; k < 4; k++) 
						if(board[i*n_col + j + k] != PLAYER_ONE) check = false;
					if(check && (board[i*n_col + j + 4] == STATUS_BLANK || (board[i*n_col + j - 1] == STATUS_BLANK && j - 1 >= 0))) count++;	//同样须判断左右的空是否跨行
				}
				//check row
				if(i + 4 <= n_row) {
					bool check = true;
					for(int k = 0; k < 4; k++) 
						if(board[(i + k)*n_col + j] != PLAYER_ONE) check = false;
					if(check && (board[(i + 4)*n_col + j] == STATUS_BLANK || (board[(i - 1)*n_col + j] == STATUS_BLANK && i - 1 >= 0))) count++;
				}
				//check diagonal
				if(i + 4 <= n_row && j + 4 <= n_col){
					bool check = true;
					for(int k = 0; k < 4; k++)
						if(board[(i + k)*n_col + j + k] != PLAYER_ONE) check = false;
					if(check && ((board[(i - 1)*n_col + j - 1] == STATUS_BLANK && i - 1 >= 0 && j - 1 >= 0) || board[(i + 4)*n_col + j + 4] == STATUS_BLANK)) count++;
				}
				//check anti-diagonal
				if(i - 4 >= 0 && j + 4 <= n_col){
					bool check = true;
					for(int k = 0; k < 4; k++)
						if(board[(i - k)*n_col + j + k] != PLAYER_ONE) check = false;
					if(check && ((board[(i + 1)*n_col + j - 1] == STATUS_BLANK && i + 1 <= n_row && j - 1 >= 0) || board[(i - 4)*n_col + j + 4] == STATUS_BLANK)) count++;
				}
			}
		}
		if(count == 2) return true;
	}

    return false;
}
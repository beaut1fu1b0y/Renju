#include<draw.h>
#include<vars.h>
#include<iostream>

using namespace std;

bool draw_check(int* board,int n_blocks) {
    for(int i = 0; i < n_blocks; i++) {
        if(board[i] == STATUS_BLANK) return false;
    }
    return true;
}
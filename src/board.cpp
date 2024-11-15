#include <iostream>
#include <vars.h>

int draw_board(int* board, int n_rows, int n_cols, int player) {

    system("clear");

	printf("    ");
	for (int i = 0; i < n_cols; i++) printf("%c", 'A' + i);

	printf("\n");

	for(int i = 0; i < n_rows; i++) {
		printf("%03d ", i);

		for (int j = 0; j < n_cols; j++) {
            int status = board[i * n_cols + j];
			if (status == STATUS_BLANK) printf(CHESS_BLANK);
			else if(status == STATUS_BLACK) printf(CHESS_BLACK);
			else if (status == STATUS_CHOICE) printf(CHESS_CHOICE);
			else printf(CHESS_WHITE);
		}
		printf("\n");
    }
    printf("Current Player: %s\n", !player ? "○" : "●");
	return 0;
}

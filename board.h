#define N_BOARD	20
#define BOARDSTATUS_OK	1
#define BOARDSTATUS_NOK	0

int board_initBoard(void);
int board_getBoardStatus(int pos);

int board_getBoardCoin(int pos);
void board_printBoardStatus(void);


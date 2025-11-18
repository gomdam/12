#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "board.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define MAX_DIE 
int rolldie(void)
{
	return rand()%MAX_DIE + 1;
}
int main(int argc, char *argv[]) 
{
	int cnt;
	int pos;
	srand( (unsigned) (time(NULL)) );
	
	//opening
	printf("=====================================\n");
	printf("               SHARKGAME             \n");
	printf("=====================================\n");
	
	//step 1 . initialization(player name, variables)
	board_initBoard();
	
	//step 2 . turn play(do while)
	cnt = 0;
	pos = 0;
	do
	{
		int die_result;
		int coinResult;
		//2-1. status printing
		board_printBoardStatus();
		//2-2. roll die
		die_result = rolldie();
		//2-3. move(result)
		pos += die_result;
		
		printf("pos : %i (die :%i)\n", pos, die_result);
		coinResult = board_getBoardCoin(pos);
		
		printf("coin : %i\n", coinResult);
	//2-4. change turn, shark move
	cnt++;
	}
	while(cnt<5);
	
	
	//step 3 . game end (winner)
	
	//ending
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("=====================================\n");
	printf("                THE END              \n");
	printf("=====================================\n"); 
	
	return 0;
}

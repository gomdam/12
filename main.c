#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "board.h"


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define MAX_DIE	6

#define N_PLAYER	3
#define MAXLENGTH	30
#define MAX_DIE	6

#define PLAYERSTATUS_LIVE	0
#define PLAYERSTATUS_DIE	1
#define PLAYERSTATUS_END	2

char player_name[N_PLAYER] [MAXLENGTH];
int player_position[N_PLAYER];
int player_coin[N_PLAYER];
int player_status[N_PLAYER];
char player_statusString[3] [MAXLENGTH] = {"LIVE", "DIE", "END"};

void printPlayerPosition(int player)
{
	int i;
	
	for(i=0;i<N_BOARD;i++)
	{
		printf("|");
		if (i == player_position[player])
		{
			printf("%c", player_name[player] [0]);
		}
		else
		{
			if(board_getBoardStatus(i) == BOARDSTATUS_OK)
				printf(" ");
			else
				printf("X");
		}
		
	}
	printf("|\n");
}

void printPlayerStatus(void)
{
	int i;
	for(i=0;i<N_PLAYER;i++)
	{
		printf("%s : pos %i, coin : %i, status %s\n", 
			player_name[i], player_position[i], player_coin[i], player_statusString[player_status[i]]);
		printPlayerPosition(i);
	}
}

void initPlayer(void)
{
	int i;
	for(i=0;i<N_PLAYER;i++)
	{
		player_position[i] = 0;
		player_coin[i] = 0;
		player_status[i] = PLAYERSTATUS_LIVE;
		
		printf("player %i's name : ", i);
		scanf("%s", player_name[i]);
		fflush(stdin);
	}
}

int gameEnd(void)
{
	int i;
	int flag_end = 1;
	
	for(i=0;i<N_PLAYER;i++)
	{
		if(player_status[i] == PLAYERSTATUS_LIVE)
			flag_end = 0;
	}
	return flag_end;
}

void checkDie(void)
{
	int i;
	for(i=0;i<N_PLAYER;i++)
	{
		if(board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK)
		{
			player_status[i] = PLAYERSTATUS_DIE;
			printf("so sad %s died at position %i\n", player_name[i], player_position[i]);
		}
	}
}

int rolldie(void)
{
	return rand()%MAX_DIE + 1;
}

int main(int argc, char *argv[]) 
{

	int turn;
	
	int dum;
	
	srand( (unsigned) (time(NULL)) );
	
	//opening
	printf("=====================================\n");
	printf("               SHARKGAME             \n");
	printf("=====================================\n");
	
	//step 1 . initialization(player name, variables)
	board_initBoard();
	initPlayer();
	//player init
	
	//step 2 . turn play(do while)
	
	turn = 0;
	
	do
	{
		int die_result;
		
		
		
		if(player_status[turn] != PLAYERSTATUS_LIVE)
		{
			turn = (turn + 1)%N_PLAYER;
			continue;
		}
		
		//2-1. status printing
		board_printBoardStatus();
	
		//player status (each)
		printPlayerStatus();
		
		//2-2. roll die
		printf("%s turn!\n", player_name[turn]);
		printf("press end key to roll a die\n");
		scanf("%d", &dum);
		fflush(stdin);	
		die_result = rolldie();
		//each playerturn
		
		//2-3. move(result)
		player_position[turn] += die_result;
		if(player_position[turn] >= N_BOARD-1)
		{
			player_position[turn] = N_BOARD-1;
			player_status[turn] = PLAYERSTATUS_END;
		}
		printf("die result : %i, %s moved to %i\n", die_result, player_name[turn], player_position[turn]);
		//each player turn
		
			
		player_coin[turn] += board_getBoardCoin(player_position[turn]);
		printf("lucky! %s got %i coins\n", player_name[turn], player_coin[turn]);
		
		
		//2-4. change turn, shark move
		//change turn
		turn = (turn + 1)%N_PLAYER;
		
		//shark move
		if (turn == 0)
		{
			int shark_pos = board_stepShark();
			printf("shark moved to %i\n", shark_pos);
			
			//check die
			checkDie();
		}
		
		
		
		
	}
	while(gameEnd() == 0); // game end condition
	
	
	//step 3 . game end (winner)
	
	
	//ending
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("=====================================\n");
	printf("                THE END              \n");
	printf("=====================================\n"); 
	
	return 0;
}

//cnt da ji woo gi

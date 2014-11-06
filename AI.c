#include "Globals.h"
#include "AI.h"
#include "Moves.h"  
#include<stdio.h>


int AiPlay(int board[][8],int turn, int undoboards[][8][8], int whitedifficulty, int blackdifficulty) 
{ // the AI moves, calculates the move with the greatest value, then plays there. Board state is then changed.
	int otherturn = turn == 1?2:1;
	int highestweight = -100;
	int ivalue = -1;
	int jvalue = -1;
	int tempweight = 0;
	srand(time(NULL));
	int r;
	int i,j;
	for (i=0; i<8; i++)
		for (j=0; j<8; j++)	
		{
			if(board[i][j]==green) 
			{
				tempweight=getWeight(board,i,j,turn,otherturn,undoboards, whitedifficulty, blackdifficulty);
				if (tempweight>highestweight) 
				{	
					highestweight = tempweight;
					ivalue = i;
					jvalue = j;
				}
				if (tempweight==highestweight) 
				{
					r = rand() % 20;;
					if (r<10) 
					{
						highestweight = tempweight;
						ivalue = i;
						jvalue = j;
					}
				}	
			}
		}
	//System.out.println(turn == black ? "highest weight for black was "+highestweight+" from "+ivalue+" "+jvalue : "highest weight for white was "+highestweight+" from "+ivalue+" "+jvalue);
	if (ivalue>=0&&jvalue>=0) 
	{
	
	//important to note, x and y axis are flipped. although it doesnt matter when calculations are performed, printing needs to be done in reverse
	//displayBoard(board);
	printf(" %d AI moved at %d,%d\n",turn,jvalue,ivalue);
		board[ivalue][jvalue]=turn;
		ChangePieces(board, ivalue,jvalue, turn, otherturn);
		
	}
	return highestweight;
}
void displayBoard(int board[][8])
{ // draw all the pieces on the board (GRAPHICS)
	int i,j,k;
	printf("AI- X AXIS\n");
	printf(" 0 1 2 3 4 5 6 7\n");
	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			if(board[i][j]==white) {
				printf("|W");
			}
			else if(board[i][j]==black) {
				printf("|B");
			}
			else if(board[i][j]==green) {
				printf("|G");
			}
			else
				printf("|_");
		}
		if(i == 3)
			printf("| %d  Y AXIS\n",i);
		else
			printf("| %d\n",i);
	}
}
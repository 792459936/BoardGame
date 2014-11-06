#include "Globals.h"
#include "Undo.h"  
#include<stdio.h>



/*most of this we shouldnt need to touch so I wont go into much detail on commenting it*/


void ResetMoveList(int board[][8]) 
{ // changes all green to blank
int i,j,k;
for (i=0; i<8; i++)
	for (j=0; j<8; j++) {
		if(board[i][j]==green) {
			board[i][j]=blank;
		}
	}
}
void UndoMove(int board[][8], int undoboards[][8][8], int *pturn, int *potherturn) {
	bool difference = false;
	printf("undo");
	ResetMoveList(board);
	int i,j,k;
	for(j=0;j<8;j++)
		for(k=0;k<8;k++) {
			if (board[j][k]!=undoboards[0][j][k])
				difference=true;
			board[j][k]=undoboards[0][j][k];
		}
	if (difference) {
		*potherturn = *potherturn == white ? black : white;
		*pturn = *pturn == white ? black : white;
	}
	for(i=0;i<9;i++)
		for(j=0;j<8;j++)
			for(k=0;k<8;k++) {
				undoboards[i][j][k]=undoboards[i+1][j][k];
			}
	ResetMoveList(board);
}

void UndoButton(int board[][8], int x,int y, int undoboards[][8][8], int *pturn, int *potherturn, bool *pMouseClicked, bool *AIPresent) 
{ // undo (GRAPHICS)
	int iterator=1;
	
	int it;
	if (*pMouseClicked == true&&x==10&&y==10) { // undo x=y=10
		*pMouseClicked=false;
		if(*AIPresent==true) {
			iterator=2;
			//System.out.println("doubles");
		}
		for(it=0;it<iterator;it++) {
			UndoMove(board,undoboards,pturn,potherturn);
		}
	}
}


#include "Globals.h"
#include "Moves.h" 
#include "AI.h" 
#include "Undo.h"
#include <stdio.h>
#include <math.h>


void findMoves(int board[][8], int turn, int otherturn) 
{ // find green pieces for every piece you own
int i,j,k;
for (i=0; i<8; i++)
	for (j=0; j<8; j++) {
		if(board[i][j]==turn) {
			setMoves(board, i,j, turn, otherturn);
		}
	}
}

void ChangePieces(int board[][8], int i,int j, int turn, int otherturn) 
{ // applies transformation after move is played, check every direction around the piece and apply the correct color to it
	//left
	int resetj=j;
	int reseti=i;
	int counter = 0;
	int stop= 0;
	int x,y,k;
	
	/*
		\|/ the two for loops iterate through all possible directions from a piece x
		-X-	this vector is then subjected to a test to see if any pieces can be changed in that
		/|\	direction.
	*/
	for(x = -1; x <= 1; x++)
	{
		for(y = -1; y <=1; y++)
		{
			
			if( (i+x>0) && (i+x<7) && (j+y>0) && (j+y<7) && board[i+x][j+y]==otherturn)
			{
			counter++;
			//printf("here%d, %d looking at CurrentBlock = %d , AfterBlock = %d\n",i,j,board[i][j], board[i+x][j+y]);
			i+=x;
			j+=y;
				//count how many pieces in a row there are of the other color (ones to be changed) 
				while(j>=0&&j<=7&&i>=0&&i<=7&&board[i][j]==otherturn) 
				{
					counter++;
					i+=x;
					j+=y;
					
				}
				if (j<0||board[i][j]!=turn)
					counter=0;
				i=reseti;
				j=resetj;
				i+=x;
				j+=y;
				//go through and change up until the counter hits 0
				while(j>=0&&j<=7&&i>=0&&i<=7&&counter > 0&& board[i][j]==otherturn) 
				{
					counter--;
					board[i][j]=turn;
					i+=x;
					j+=y;
				}
			i=reseti;
			j=resetj;
			counter=0;
			}
		}
	}
}

void setMoves(int board[][8], int i,int j, int turn, int otherturn) { // just like change pieces, finds all directions around a piece and finds possible moves
	//left
	int resetj=j;
	int reseti=i;
	int x,y,k;
	
	/*
		\|/ the two for loops iterate through all possible directions from a piece x
		-X-	this vector is then subjected to a test to see if any moves can be set in that
		/|\	direction.
	*/
	for(x = -1; x <= 1; x++)
	{
		for(y = -1; y <=1; y++)
		{
			if( (i+x>0) && (i+x<7) && (j+y>0) && (j+y<7) && board[i+x][j+y]==otherturn )
			{
			i+=x;
			j+=y;
				//find the end of a run of opponents colors
				while(j>=0&&j<=7&&i>=0&&i<=7 && board[i][j]==otherturn) 
				{
					i+=x;
					j+=y;
					
				}
				//if at the end there is a blank then it is a valid move.
				if(j>=0&&j<=7&&i>=0&&i<=7&&board[i][j]==blank)
				{
					board[i][j]=green;
				}
				i=reseti;
				j=resetj;
			}
		}
	}
}

int getWeight(int board[][8], int i, int j, int turn, int otherturn, int undoboards[][8][8], int whitedifficulty, int blackdifficulty) 
{ // finds the wieght of any move by the number of pieces it will take in every direction and the other alogrithms
	//left
	
	int resetj=j;
	int reseti=i;
	int counter = 0;
	int x,y,k;
	/*
		\|/ the two for loops iterate through all possible directions from a piece x
		-X-	this vector is then subjected to a test to see the weight of a moves influence in that
		/|\	direction.
	*/
	for(x = -1; x <= 1; x++)
	{
		for(y = -1; y <=1; y++)
		{
			if( (i+x>0) && (i+x<7) && (j+y>0) && (j+y<7) && board[i+x][j+y]==otherturn )
			{
			i+=x;
			j+=y;
				while(j>=0&&j<=7&&i>=0&&i<=7&&board[i][j]==otherturn) 
				{
					if (board[i][j]!=turn)
						counter++;
					i+=x;
					j+=y;
					
				}
				i=reseti;
				j=resetj;
			}
		}
	}
	
	//after, more heuristics are run on the calculation depending on the difficulty level
	if ((turn==black&&blackdifficulty==medium)||(turn==white&&whitedifficulty==medium)) {
		if (isCorner(i,j))
			counter+=10;
		if (isSubCorner(i,j))
			counter-=3;
	}
	//hard is the only difficulty level with a minmax tree
	if ((turn==black&&blackdifficulty==hard)||(turn==white&&whitedifficulty==hard)) {
		counter+=applyHard(i,j,turn,otherturn,board,undoboards, whitedifficulty, blackdifficulty);
	}
	
	
	return counter;
}


int applyHard(int ival, int jval, int turn, int otherturn, int board[][8], int undoboards[][8][8], int whitedifficulty, int blackdifficulty) 
{ // applies the weights of the board to a move
	//printf("Assuming move at %d %d\n",ival,jval);
	int i,j,k;
	int itemp = ival;
	int jtemp = jval;
	double calculation=0;
	
	
	int saveddifficulty=otherturn == white ? whitedifficulty : blackdifficulty; // save both current difficulties
	int currentdifficulty = turn == white ? whitedifficulty : blackdifficulty; 
	whitedifficulty=currentdifficulty; // for calculating, assume the other AI thinks like you, both AI are set to the current thinkers level
	blackdifficulty = currentdifficulty;
	
	
	if (forwardturns==0)//while you are not already looking ahead
	{
		while(forwardturns < 3)//look ahead this many
		{
			forwardturns++;
			//printf("fturns = %d turn = %d\n",forwardturns, turn);
			board[itemp][jtemp]=turn;// apply the current move
			ChangePieces(board, ival,jval, turn, otherturn);//show changes
			
			otherturn = otherturn == white ? black : white; //change to opponents turn
			turn = turn == white ? black : white;
			
			ResetMoveList(board); //find that turns moves.
			findMoves(board, turn, otherturn);
			
				//this is a recursive call to the AiPlay -> AI takes the next turn acting as if 
				//its opponent thinks just as well as it does. debugging this is hell on earth.
			calculation += pow(-1.0,forwardturns)*AiPlay(board, turn, undoboards, whitedifficulty, blackdifficulty)/2; //calculate the highest possible score they have
			
			
			otherturn = otherturn == white ? black : white; //set move back to you
			turn = turn == white ? black : white;
			//printf("fturns = %d turn = %d\n",forwardturns, turn);
		}
	
		for(j=0;j<8;j++)
			for(k=0;k<8;k++) 
			{
				board[j][k]=undoboards[0][j][k];
			}
		forwardturns=0;
	}
	
	ResetMoveList(board);
	findMoves(board, turn, otherturn);
	
	//return the other players to their original AI difficulty settings
	if(otherturn == white) 
		whitedifficulty=saveddifficulty; 
	else 
		blackdifficulty=saveddifficulty;
	
	//add the weights matrix heuristic, however for reversi, if the corner is already taken dont worry about moving in a subcorner
	if(isSubCorner(ival,jval) && ClosestCornerFilled(board, ival,jval))
		calculation +=1;
	else
		calculation +=weights[ival][jval];
	
	return (int)calculation;	
}



bool isCorner(int i, int j) 
{ // returns if the tile is a corner (good)
	if((i==0&&j==0)||(i==0&&j==7)||(i==7&&j==0)||(i==7&&j==7))
		return true;
	return false;
}
	
bool isSubCorner(int i, int j) 
{ // returns if the tile touches a corner (bad)
	if((i==1&&j==0)||(i==1&&j==7)||(i==7&&j==1)||(i==7&&j==6)||(i==1&&j==1)||(i==1&&j==6)||(i==6&&j==0)||(i==6&&j==7)||(i==0&&j==1)||(i==0&&j==6)||(i==6&&j==1)||(i==6&&j==6))
		return true;
	return false;
}


bool ClosestCornerFilled(int board [][8], int i, int j) 
{ 
	//get nearest corner
	i = i <=3?0:7;
	j = j <=3?0:7;
	// if it is occupied by a piece
	if(board[i][j] == 1 || board[i][j] == 2)
		return true;
	return false;
}
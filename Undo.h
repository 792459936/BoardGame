#ifndef UNDO_H_   /* Include guard */
#define UNDO_H_  
#pragma once


//changes all possible moves to blanks
void ResetMoveList(int board[][8]); 
//reverts the board to the last matrix of the undo stack
void UndoMove(int board[][8], int undoboards[][8][8], int *pturn, int *potherturn);
//sets up the undo parameters
void UndoButton(int board[][8], int x,int y, int undoboards[][8][8], int *pturn, int *potherturn, bool *pMouseClicked, bool *AIPresent); 


#endif /* UNDO_H_ */ 
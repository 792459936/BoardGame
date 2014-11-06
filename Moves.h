#ifndef MOVES_H_   /* Include guard */
#define MOVES_H_  
#pragma once

//sets up the function call for setMoves
void findMoves(int board[][8], int turn, int otherturn);
//change the board state to react to a piece being played
void ChangePieces(int board[][8], int i,int j, int turn, int otherturn);
//find possible moves based on the board state and current turn, label them Green
void setMoves(int board[][8], int i,int j, int turn, int otherturn);
//get the weight of a particular move (AI)
int getWeight(int board[][8], int i, int j, int turn, int otherturn, int undoboards[][8][8], int whitedifficulty, int blackdifficulty);

//AI HELPERS
//apply hard heuristics and depth tree.
int applyHard(int ival, int jval, int turn, int otherturn, int board[][8], int undoboards[][8][8], int whitedifficulty, int blackdifficulty);
//check if the position is a corner
bool isCorner(int i, int j);
//check if the position is next to a corner
bool isSubCorner(int i, int j) ;


#endif /* MOVES_H_ */
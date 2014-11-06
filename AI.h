#ifndef AI_H_   /* Include guard */
#define AI_H_  
#pragma once


int AiPlay(int board[][8], int turn, int undoboards[][8][8], int whitedifficulty, int blackdifficulty);
void displayBoard(int board[][8]);

#endif /* AI_H_ */
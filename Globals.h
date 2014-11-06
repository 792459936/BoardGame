#ifndef GLOB_H_   /* Include guard */
#define GLOB_H_  
#pragma once


typedef int bool;
#define true 1
#define false 0




    

    //pieces
    static int blank = 0; 
    static int black = 1;  
    static int white = 2; 
    static int green = 3;
    //players
    static int whiteplayer=0;
    static int blackplayer=0;
    static int human = 0;
    static int Ai = 1;
    static int ServerID = 1;
    static int ClientID = 2;
    static int TypeClient = 0;
	
    //difficulties
    static int blackdifficulty = 0;
    static int whitedifficulty = 0;
    static int easy = 0;
    static int medium = 1;
    static int hard = 2;
    static int forwardturns = 0;
	
	//static bool AiPresent=false; // self explanitory booleans
    //
    static int mX = 0;//clicked
    static int mY = 0;
    static int weights[8][8] =
		{
		{99, -8, 8, 6, 6, 8, -8, 99},
		{-8, -24, -4, -3, -3, -4, -24, -8},
		{8, -4, 7, 4, 4, 7, -4, 8},
		{6, -3, 4, 0, 0, 4, -3, 6},
		{6, -3, 4, 0, 0, 4, -3, 6},
		{8, -4, 7, 4, 4, 7, -4, 8},
		{-8, -24, -4, -3, -3, -4, -24, -8},
		{99, -8, 8, 6, 6, 8, -8, 99},
		}; // for Hard mode
		
		



#endif /* GLOB_H_ */
/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
//#include <device.h>
#include <stdio.h>
#include <time.h>
#include "Globals.h"
#include "Undo.h"
#include "Moves.h"
#include "AI.h"

    int board[8][8];
	int weight[8][8];
    int undoboards[10][8][8];
	static int turnchecker = 0;
	
	static int turn = 1;
    static int otherturn = 2;	
	static bool mouse_clicked=false;
	
	static int clicks = 0;
    static bool AiPresent=false; // self explanitory booleans
    static bool BothAi = false;
    static int nomoves = 0;
	
    static int p=-1;// this changes the state of the game: -1 = load all values, 0 = reset, 1 = main menu, 2= game.


		
void initialize()
{
    //addMouseListener(this); 
    //addKeyListener(this); 

    p=0;

}

void fillundoboards() 
{ // preload undo boards with the beginnning state
int i,j,k;
for(i=0;i<10;i++)
	for(j=0;j<7;j++)
		for(k=0;k<7;k++) {
			undoboards[i][j][k]=board[j][k];
		}
}

void drawMenu() 
{ // draw main menu GRAPHICS
       
}
	
void selectMenu(int x, int y) 
{ 	// this will be where most of the interrupts are called.
	whiteplayer = Ai;
	whitedifficulty=medium;
	blackplayer = Ai;
	blackdifficulty=hard;
	AiPresent=true;
	BothAi=true;
	p=2;
}
void drawBoard() 
{ // draw the game board (GRAPHICS)	
	//this function is replaced by draw pieces. it was used with graphics in java, but in comand line
	//there is no need to draw the board then the pieces, since both need to be drawn at the same time.
}



void drawPieces() 
{ // draw all the pieces on the board (GRAPHICS)
	int i,j,k;
	printf("     X AXIS\n");
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


	

void SetupBoard()
{	//reversi setup, 4 pieces in the middle
    printf("Welcome");
	int i,j,k;
    for (i=0; i < 8; i++)
        for (j=0; j < 8; j++)
            board[i][j] = blank;

    board[3][3] = white;
    board[4][4] = white;
    board[3][4] = black;
    board[4][3] = black;
    p=1;//advance to next piece of the program
    fillundoboards();
}
void MainHandle()
{
    printf("Main Menu\n"); // no idea what this might be used for yet

    //if (mouse_clicked) {
        selectMenu(mX,mY);
        mouse_clicked=false;
    //}
    //drawMenu();
}
void NewGame ( int x, int y) 
{ // if the new game numbers are called, refresh the game state, this will call the function to check on any updated switches for game control

    if (mouse_clicked == true&&x<10&&y>10) { // new game == 11,11
        mouse_clicked=false;
        p=0;
        ResetMoveList(board);
        //refreshed = false;
       /* AiPresent=false;
        BothAi=false;
		whiteplayer = Ai;
		whitedifficulty=easy;
		AiPresent=true;*/
        //repaint();
    }
}
	
bool gameover () 
{ // boolean for game over possibility
    int spaces=0;
    int movepossibilities = 0;
	int i,j,k;
    for (i=0; i<8; i++)
        for (j=0; j<8; j++) {
            if(board[i][j]==blank)
                    spaces++;
            if(board[i][j]==green)
                    movepossibilities++;
        }

    if (spaces == 0 && movepossibilities == 0)
        return true;
    else if (movepossibilities == 0&&nomoves==otherturn) {
        return true;
    } 
    else if (movepossibilities == 0) {
        nomoves=turn;
        return false;
    }
    else {
        nomoves=0;
        return false;
    }
}

void getWinner () 
{ 
    int spaces=0;
    int movepossibilities = 0;
    int blackpieces = 0;
    int whitepieces = 0;
	int i,j,k;//count the scores
    for (i=0; i<8; i++)
        for (j=0; j<8; j++) 
        {
            if(board[i][j]==blank)
                    spaces++;
            else if(board[i][j]==black)
                    blackpieces++;
            else if(board[i][j]==white)
                    whitepieces++;
            else if(board[i][j]==green)
                    movepossibilities++;
        }
		//display the scores and the winner
    printf("blank = %d black = %d white = %d green = %d\n",blank,blackpieces,whitepieces,movepossibilities);
    if (blackpieces != whitepieces) 
    {
        printf(blackpieces > whitepieces ? "Black Wins! win by number\n" : "White Wins! win by number\n");
    }
    else 
    {
        printf("tie game");
    }
}

bool isPlayable (int x, int y) { //if a location is playable (green)
    if (x>=0&&x<=7&&y>=0&&y<=7) {
        if (board[x][y]==green)
            return true;
    }
    return false;
}

bool isTurn (int turn) { // if it is a humans turn
    if (turn==black&&blackplayer==0) // blackplayer == 0 -> human : 1 -> AI
        return true;
    else if(turn==white&&whiteplayer==0)
        return true;
    else
        return false;

}



void play(int x, int y) { // the basic play. change a piece then call the ChangePieces function to apply the move to the board
    board[x][y]=turn;
	//the board is flipped on the x and y axis, works fine in all calculations, but printing is off
    printf("player moved - %d %d\n",y,x);
    ChangePieces(board, x, y, turn, otherturn);
}


/*START PILE OF NOPE FUNCTION*/
void ProgressGame()
{
	
	/*
	THIS IS A HUGE PILE OF NOPE AT THE MOMENT, IGNORE WHILE I LOOK INTO CLEANING UP LATER.
	HANDLES BOTH HUMAN AND AI MOVES IN ONE FUNCTION AS WELL AS PROGRESSING THE MOVES IN THE GAME
	*/
	
	
	int i,j,k;
    if(gameover() == false && mouse_clicked == true &&isPlayable(mX,mY)&&isTurn(turn)) 
    { //player move
        ResetMoveList(board);
		
            for(i=8;i>=0;i--)
                for(j=0;j<8;j++)
                    for(k=0;k<8;k++) {
                        undoboards[i+1][j][k]=undoboards[i][j][k];// this loads the state of the board before the move into the undo slot.
                            }
            for(j=0;j<8;j++)
                for(k=0;k<8;k++) {
                    undoboards[0][j][k]=board[j][k];
                }
            printf("X = %d, Y = %d\n",mX,mY);
            play(mX,mY);
            //System.out.print("clicked");
			printf("clicked\n");
			
			printf("turn = %d \n",turn);
            otherturn = otherturn == white ? black : white;
            turn = turn == white ? black : white;
			printf("turn = %d \n",turn);
			
            ResetMoveList(board);
            mouse_clicked=false;
			printf("check1\n");
    }				// re-evaluate after player moves.
	printf("check2\n");
	//refresh
    drawBoard();
    UndoButton(board,mX,mY,undoboards, &turn, &otherturn, &mouse_clicked, &AiPresent);
    NewGame(mX,mY);
	drawPieces();	
    findMoves(board, turn, otherturn);
    drawPieces();	


    
    if(!isTurn(turn)&&!gameover()) 
    { // if there is an AI present AI goes.
        for(i=8;i>=0;i--)
            for(j=0;j<8;j++)
                for(k=0;k<8;k++)
                {
                    undoboards[i+1][j][k]=undoboards[i][j][k]; // this loads the state of the board before the move into the undo slot.
                }
        for(j=0;j<8;j++)
            for(k=0;k<8;k++) 
            {
                undoboards[0][j][k]=board[j][k];
            }
        AiPlay(board, turn, undoboards, whitedifficulty, blackdifficulty);
        otherturn = otherturn == white ? black : white;
        turn = turn == white ? black : white;
        ResetMoveList(board);
		
		//refresh
        drawBoard();
        UndoButton(board,mX,mY,undoboards, &turn, &otherturn, &mouse_clicked, &AiPresent);
        findMoves(board, turn, otherturn);
        drawPieces();	
        NewGame(mX,mY);
    } // re-evaluate after AI moves.    
	
	
	
        if (gameover() == true) 
		{
            printf("game over\n");
            getWinner();
			printf("done. press a key\n");
			scanf("%d", &mX);
        }
        if (gameover() == false) 
		{
            //if(BothAi)
            //repaint();
        }
        if(nomoves == turn) 
		{
            otherturn = otherturn == white ? black : white;
            turn = turn == white ? black : white;
            //repaint();
        }
}

/*END PILE OF NOPE FUNCTION*/



void GameLoop()
{
	if(p==-1) 
    { // start up the Listeners (happens once)
        initialize();
		printf("done init\n");
    }
    if(p==0) 
    {
        SetupBoard();
		printf("done setup\n");
    }

    if(p==1) 
    { // main menu (redrawn every time you click or //repaint)
        MainHandle();
		printf("done handle\n");
    }

    if (p==2) 
    { //game
        ProgressGame();
		printf("done board\n");
    }
}

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	printf("here!");
    

    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
		GameLoop();
		if(!BothAi)
		{
			printf("enter x value\n");
			scanf("%d", &mY);
			printf("%d\n",mY);
			printf("enter y value\n");
			scanf("%d", &mX);
			printf("%d\n",mX);
			mouse_clicked=true;
		}
		//for testing when both AI are on
		//delay(1000);
    }
	return 0;
}


void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}




/* [] END OF FILE */

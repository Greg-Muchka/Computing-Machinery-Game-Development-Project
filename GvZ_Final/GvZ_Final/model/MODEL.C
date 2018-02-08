/* ================================================
- Module Name: model
- Purpose: model for the game and all its elements
================================================ */
#include "MODEL.H"
/* ================================================
- Name: initializeWall
- Purpose: initializes walls and its elements
================================================ */
void initializeWall(struct Model* gamePtr,int wallNum, int Xpos1,int Ypos1,int Xpos2,int Ypos2, int Height,int Width, int isHorizontal)
{
	gamePtr->walls[wallNum].Xpos1 = Xpos1;
	gamePtr->walls[wallNum].Ypos1 = Ypos1;
	gamePtr->walls[wallNum].Xpos2 = Xpos2;
	gamePtr->walls[wallNum].Ypos2 = Ypos2;
	gamePtr->walls[wallNum].Height = Height;
	gamePtr->walls[wallNum].Width = Width;
	gamePtr->walls[wallNum].isHorizontal = isHorizontal;
	gamePtr->walls[wallNum].Active = TRUE;
}
/* ================================================
- Name: initializePlayer
- Purpose: initializes player and its elements
================================================ */
void initializePlayer(struct Model* gamePtr, int Xpos,int Ypos,int Speed, bool Active,bool Move,int XDirection,int YDirection,int Height,int Width)
{
	/*Add variable for player number if 2 player is implemented*/
	gamePtr->players[0].Xpos = Xpos;
	gamePtr->players[0].Ypos = Ypos;
	gamePtr->players[0].Xold = Xpos;
	gamePtr->players[0].Yold = Ypos;
	gamePtr->players[0].Speed = Speed;
	gamePtr->players[0].Active = Active;
	gamePtr->players[0].XDirection = XDirection;
	gamePtr->players[0].YDirection = YDirection;
	gamePtr->players[0].Move = Move;
	gamePtr->players[0].Height = Height;
	gamePtr->players[0].Width = Width;
}
/* ================================================
- Name: initializeZombie
- Purpose: initializes zombie and its elements
================================================ */
void initializeZombie(struct Model* gamePtr,int ZNum,int Xpos,int Ypos,int Speed,bool Active, int XDirection,int YDirection,int Height,int Width)
{
	gamePtr->zombies[ZNum].Xpos = Xpos;
	gamePtr->zombies[ZNum].Ypos = Ypos;
	gamePtr->zombies[ZNum].Speed = Speed;
	gamePtr->zombies[ZNum].XDirection = XDirection;
	gamePtr->zombies[ZNum].YDirection = YDirection;
	gamePtr->zombies[ZNum].Active = Active;
	gamePtr->zombies[ZNum].Height = Height;
	gamePtr->zombies[ZNum].Width = Width;
	gamePtr->zombies[ZNum].Xold = Xpos;
	gamePtr->zombies[ZNum].Yold = Ypos;
}
/* ================================================
- Name: initializeBullet
- Purpose: initializes bullets and its elements
Returns true if a bullet was initialized 
================================================ */
bool initializeBullet(struct Model* gamePtr)
{
	int i;
	int BulletFound = FALSE;
	for(i = 0; i < NUMBULLET && !BulletFound; i++)
	{
		if(!gamePtr->bullets[i].Active)
		{
			switch(gamePtr->players[0].XDirection)
			{
				case 1:
				gamePtr->bullets[i].Xpos = gamePtr->players[0].Xpos + 16;
				gamePtr->bullets[i].Ypos = gamePtr->players[0].Ypos + 12;
				break;
				case -1:
				gamePtr->bullets[i].Xpos = gamePtr->players[0].Xpos +6;
				gamePtr->bullets[i].Ypos = gamePtr->players[0].Ypos + 12;
			}
			switch(gamePtr->players[0].YDirection)
			{
				case 1:
				gamePtr->bullets[i].Xpos = gamePtr->players[0].Xpos + 14;
				gamePtr->bullets[i].Ypos = gamePtr->players[0].Ypos + 20;
				break;
				case -1:
				gamePtr->bullets[i].Xpos = gamePtr->players[0].Xpos +14;
				gamePtr->bullets[i].Ypos = gamePtr->players[0].Ypos;
			}
			gamePtr->bullets[i].Speed = 15;
			gamePtr->bullets[i].XDirection = gamePtr->players[0].XDirection;
			gamePtr->bullets[i].YDirection = gamePtr->players[0].YDirection;
			gamePtr->bullets[i].Active = TRUE;
			gamePtr->bullets[i].Height = 8;
			gamePtr->bullets[i].Width = 8;
			gamePtr->bullets[i].newBullet = TRUE;
			
			gamePtr->bullets[i].Xold = gamePtr->bullets[i].Xpos;
			gamePtr->bullets[i].Yold = gamePtr->bullets[i].Ypos;
			BulletFound = TRUE;
		}
	}
	return BulletFound;
}
/* ================================================
- Name: setPoint
- Purpose: sets point objects
================================================ */
void setPoint(struct Model *gamePtr, int prevPointPos)
{
	int randNum;
	bool set = FALSE;
	
	while(!set)
	{
		randNum = rand() % NUMPOINT;
		if(randNum != prevPointPos){
			set = TRUE;
			gamePtr->point[randNum].Active = TRUE;
			gamePtr->point[randNum].Clear = FALSE;
		}
	}
}
/* ================================================
- Name: initializePoint
- Purpose: initializes points and its elements
================================================ */
void initializePoint(struct Model *gamePtr, int Xpos, int Ypos, bool Clear, bool Active, int count)
{
	gamePtr->point[count].Xpos = Xpos;
	gamePtr->point[count].Ypos = Ypos;
	gamePtr->point[count].Xpos2 = gamePtr->point[count].Xpos + 8;
	gamePtr->point[count].Ypos2 = gamePtr->point[count].Ypos + 8;
	gamePtr->point[count].Clear = Clear;
	gamePtr->point[count].Active = Active;
	
}
/* ================================================
- Name: initialize
- Purpose: initializes game model and its elements
================================================ */
void initialize(struct Model* gamePtr)
{	
	gamePtr->gameOver = FALSE;
	gamePtr->Restart = FALSE;
	gamePtr->Lives = 3;
	gamePtr->Level = 1;
	gamePtr->Selection = 0;
	gamePtr->enteredSelection = 0;
	gamePtr->Score = 0;
}
/* ================================================
- Name: initializeLevelOne
- Purpose: initializes level at reset point and its
elements
================================================ */
void initializeLevelOne(struct Model *gamePtr)
{
	initializeZero(gamePtr);
	/*gamePtr,wallNum, Xpos1,Ypos1,Xpos2,Ypos2, Height,Width, isHorizontal*/
	
	initializeWall(gamePtr,0,0,0,639,8,8,639,1);
	initializeWall(gamePtr,1,0,360,639,368,8,639,1);
	initializeWall(gamePtr,2,635,0,639,359,360,8,0);
	initializeWall(gamePtr,3,0,0,7,359,360,8,0);
	
	initializePlayer(gamePtr,300,150,3,TRUE,FALSE,0,1,32,32);

	initializeZombie(gamePtr,0,10,10,4,TRUE,1,0,32,32);
	initializeZombie(gamePtr,1,600,10,4,TRUE,-1,0,32,32);
	initializeZombie(gamePtr,2,10,300,4,TRUE,1,0,32,32);
	initializeZombie(gamePtr,3,600,300,4,TRUE,-1,0,32,32);

	initializePoint(gamePtr, 310,  50, FALSE, TRUE, 0);
	initializePoint(gamePtr, 150, 200, FALSE, FALSE, 1);
	initializePoint(gamePtr, 250, 300, FALSE, FALSE, 2);
	initializePoint(gamePtr, 350, 100, FALSE, FALSE, 3);
	initializePoint(gamePtr, 450, 200, FALSE, FALSE, 4);
	initializePoint(gamePtr, 550, 300, FALSE, FALSE, 5);
	initializePoint(gamePtr, 200, 350, FALSE, FALSE, 6);
	initializePoint(gamePtr, 300, 200, FALSE, FALSE, 7);
	initializePoint(gamePtr, 400, 300, FALSE, FALSE, 8);
	initializePoint(gamePtr, 500, 350, FALSE, FALSE, 9);
}
/* ================================================
- Name: remakeZombies
- Purpose: remakes zombies and elements
================================================ */
void remakeZombies(struct Model* gamePtr){
	int count;
	for(count = 0; count < NUMZOMBIE; count++){
		if(gamePtr->zombies[count].Active == 0){
			if(count == 0)
				initializeZombie(gamePtr,0,10,10,4,TRUE,1,0,32,32);
			else if(count == 1)
				initializeZombie(gamePtr,1,600,10,4,TRUE,-1,0,32,32);
			else if(count == 2)
				initializeZombie(gamePtr,2,10,300,4,TRUE,1,0,32,32);
			else if(count == 3)
				initializeZombie(gamePtr,3,600,300,4,TRUE,-1,0,32,32);
		}
	}
}
/* ================================================
- Name: initializeZero
- Purpose: initializes arrays elements to zero
(so no accidental garbage values set at creation)
================================================ */
void initializeZero(struct Model* gamePtr){
	int count;
	for(count = 0; count < NUMBULLET; count++){
		gamePtr->bullets[count].Active = 0;	
	}
	for(count = 0; count < NUMZOMBIE; count++){
		gamePtr->zombies[count].Active = 0;	
	}
	for(count = 0; count < NUMPLAYER; count++){
		gamePtr->players[count].Active = 0;	
	}
	for(count = 0; count < NUMWALLS; count++){
		gamePtr->walls[count].Active = 0;
	}
}
/* ================================================
- Name: requestMovePlayer
- Purpose: handles the requests for player movement
================================================ */
void requestMovePlayer(struct Model* gamePtr, long Action)
{
	switch(Action){
	case UP:
		gamePtr->players[0].Move = TRUE;
		gamePtr->players[0].XDirection = 0;
		gamePtr->players[0].YDirection = -1;
		
	break;
	case DOWN:
		gamePtr->players[0].Move = TRUE;
		gamePtr->players[0].XDirection = 0;
		gamePtr->players[0].YDirection = 1;
	break;
	case LEFT:
		gamePtr->players[0].Move = TRUE;
		gamePtr->players[0].XDirection = -1;		
		gamePtr->players[0].YDirection = 0;	
	break;
	case RIGHT:
		gamePtr->players[0].Move = TRUE;
		gamePtr->players[0].XDirection = 1;
		gamePtr->players[0].YDirection = 0;
	
	}
}
/* ================================================
- Name: requestMoveZombie
- Purpose: handles the requests for zombie movement
================================================ */
void requestMoveZombie(struct Model* gamePtr)
{
	int randNum;
	int i;
	for(i = 0; i < NUMZOMBIE; i++)
	{	
		if(gamePtr->zombies[i].Active)
		{
			if(gamePtr->zombies[i].Xpos <= gamePtr->players[0].Xpos){
				if(gamePtr->zombies[i].Ypos <= gamePtr->players[0].Ypos){
					randNum = rand() % 2;
					switch(randNum){
						case 0: /*DOWN*/
						gamePtr->zombies[i].XDirection = 0;
						gamePtr->zombies[i].YDirection = 1;
						break;
						case 1: /*RIGHT*/
						gamePtr->zombies[i].XDirection = 1;
						gamePtr->zombies[i].YDirection = 0;
						break;
					}
				}
				else if(gamePtr->zombies[i].Ypos >= gamePtr->players[0].Ypos){
					randNum = rand() % 2;
					switch(randNum){
						case 0: /*UP*/
						gamePtr->zombies[i].XDirection = 0;
						gamePtr->zombies[i].YDirection = -1;
						break;
						case 1: /*RIGHT*/
						gamePtr->zombies[i].XDirection = 1;
						gamePtr->zombies[i].YDirection = 0;
						break;
					}
				}
			}
			else if(gamePtr->zombies[i].Xpos >= gamePtr->players[0].Xpos){
				if(gamePtr->zombies[i].Ypos <= gamePtr->players[0].Ypos){
					randNum = rand() % 2;
					switch(randNum){
						case 0: /*DOWN*/
						gamePtr->zombies[i].XDirection = 0;
						gamePtr->zombies[i].YDirection = 1;
						break;
						case 1: /*LEFT*/
						gamePtr->zombies[i].XDirection = -1;
						gamePtr->zombies[i].YDirection = 0;	
						break;
					}
				}
				else if(gamePtr->zombies[i].Ypos >= gamePtr->players[0].Ypos){
					randNum = rand() % 2;
					switch(randNum){
						case 0: /*UP*/
						gamePtr->zombies[i].XDirection = 0;
						gamePtr->zombies[i].YDirection = -1;
						break;
						case 1: /*LEFT*/
						gamePtr->zombies[i].XDirection = -1;
						gamePtr->zombies[i].YDirection = 0;	
						break;
					}
				}
			}
		}
	}	
}
/* ================================================
- Module Name: model
- Purpose: header file for model.c
================================================ */
#ifndef MODEL_H
#define MODEL_H

#include <osbind.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMWALLS 4
#define NUMPLAYER 2
#define NUMZOMBIE 4
#define NUMBULLET 3
#define FALSE 0
#define TRUE 1
#define NUMPOINT 10

#define UP 0x480000
#define DOWN 0x500000
#define LEFT 0x4B0000
#define RIGHT 0x4D0000
#define SPACEBAR 0x390020
#define ESC  0x01001B

typedef int bool;

struct Point{
	int Xpos;
	int Ypos;
	int Xpos2;
	int Ypos2;
	bool Active;
	bool Clear;
};

struct Player{
	int Xpos;
	int Ypos;
	int Xold;
	int Yold;
	int Speed;
	bool Active;
	bool Move;
	int XDirection;
	int YDirection;
	int Height;
	int Width;
};

struct Zombie{
	int Xpos;
	int Ypos;
	int Xold;
	int Yold;
	int Speed;
	bool Active;	
	int XDirection;
	int YDirection;
	int Height;
	int Width;
	bool Clear;
};

struct Wall{
	int Xpos1;
	int Ypos1;
	int Xpos2;
	int Ypos2;
	int Height;
	int Width;
	int isHorizontal;
	bool Active;
};

struct Bullet{
	int Xpos;
	int Ypos;
	int Xold;
	int Yold;
	int Speed;
	bool Active;
	int XDirection;
	int YDirection;
	int Height;
	int Width;
	bool newBullet;
	bool Clear;
};

struct Model{
	struct Wall walls[NUMWALLS];
	struct Player players[NUMPLAYER];
	struct Zombie zombies[NUMZOMBIE];
	struct Bullet bullets[NUMBULLET];
	struct Point point[NUMPOINT];
	bool gameOver;
	bool Restart;
	int Lives;
	int Level;
	int Selection;
	int enteredSelection;
	int Score;
};

void initializeWall(struct Model* gamePtr,int wallNum, int Xpos1,int Ypos1,int Xpos2,int Ypos2, int Height,int Width,int isHorizontal);
void initializePlayer(struct Model* gamePtr, int Xpos,int Ypos,int Speed, bool Active,bool Move,int XDirection,int YDirection,int Height,int Width);
void initializeZombie(struct Model* gamePtr,int ZNum,int Xpos,int Ypos,int Speed,bool Active, int XDirection,int YDirection,int Height,int Width);
bool initializeBullet(struct Model* gamePtr);
void initialize(struct Model* gamePtr);
void initializeZero(struct Model* gamePtr);
void initializeLevelOne(struct Model *gamePtr);
void initializePoint(struct Model *gamePtr, int Xpos, int Ypos, bool Clear, bool Active, int count);

void setPoint(struct Model *gamePtr, int prevPointPos);

void remakeZombies(struct Model* gamePtr);
void requestMovePlayer(struct Model* gamePtr, long Action);
void requestMoveZombie(struct Model* gamePtr);
#endif
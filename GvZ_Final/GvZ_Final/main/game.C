/* ================================================
- Name: Jaedwin Montal and Greg Muchka
- Email: jmont467@mtroyal.ca, gmuch146@hmtroyal.ca
- Course: COMP2659 - 001
- Stage: 8 
- Due Date: 4/15/2016 
- Instructor: Paul Pospisil
================================================ */
/* ================================================
- Name:  main
- Purpose: main program for our game
================================================ */
#include "game.H"
#include <stdio.h>

typedef void (*Vector)();  /* a Vector is a function start addr. */ 
typedef unsigned char UBYTE;
typedef UBYTE SCANCODE;

#define BUFFER_SIZE 256
volatile UBYTE 			*const MFP_IS 		= 0xFFFA11;
volatile UBYTE 			*const MFP_IE 		= 0xFFFA09;
volatile const SCANCODE *const IKBD_RDR 	= 0xFFFC02; 
char 					*const ASCII_TABLE  = 0xFE829C;

UINT32 backBuffer[32256];

Vector install_vector(int num, Vector vector);

UBYTE buffer[BUFFER_SIZE], head = 0, tail = 0;
int playerOneXpos1 = 150;
int playerOneXpos2 = 250;
int playerOneYpos1 = 274;
int playerOneYpos2 = 306;

int playerTwoXpos1 = 326;
int playerTwoXpos2 = 426;
int playerTwoYpos1 = 274;
int playerTwoYpos2 = 306;

int exitXpos1 = 270;
int exitXpos2 = 320;
int exitYpos1 = 336;
int exitYpos2 = 368;

char deltaX = 0x00;
char deltaY = 0x00;
int mouseX = 320;
int mouseY = 200;
unsigned int currX = 0;
unsigned int currY = 0;

int render_request = FALSE;
int music_notes = 0;
int oldScore = 0;
int make = FALSE;

bool mouseClick = FALSE;
bool mouseEnable = TRUE;

int Mouse_count = 0;

long Action = 0x00;

bool gun_effect = FALSE;
bool point_effect = FALSE;
UINT32 *base2 = backBuffer;
UINT32 *base32;
bool start = FALSE;
UINT32 BKGarray[2048];
UINT32 *background = &BKGarray;

int main()
{
	/* Game Model */
	struct Model gameModel; 
	struct Model* gamePtr;	
	
	int count, i, toggle = 1;
	bool found = FALSE;

	Vector orig_VBL_vector = install_vector(VBL, VBL_ISR); 
	Vector orig_IKBD_vector = install_vector(IKBD, IKBD_ISR); 
	/* Time Functions*/ 
	ULONG32 timeNow = 0;
	ULONG32 timeThen = 0;
	ULONG32 timeElapsed = 0;
	ULONG32 startNoteTime = 0;
	ULONG32 elapsedNoteTime = 0;
	ULONG32 finishNoteTime = 0;
	/* Bases */
	base32 = Physbase();
	
	base2 = (UINT32*)((UINT32)base2 + (256 - ((UINT32)base2) & 255));
	
	disable_cursor(); 
	
	/* Initialize Game */
	gamePtr = &gameModel;
	initialize(gamePtr);
	initializeLevelOne(gamePtr);

	/* Game Selection Screen */
	fill_screen((UINT8*)base32,splash_welcome);
	
	saveBKGD(base32, mouseX, mouseY, background);
	printMouse(base32, mouseX, mouseY);
	
	/**********************************************************************************/
	reset_sound();
	while(!start)
		updateMouse(gamePtr);
	/* 1-Player Selected */
	if(gamePtr->enteredSelection == 0)
	{
		clear_screen(base32);
		clear_screen(base2);
		render(gamePtr, base32, base2);
		drawStatic(gamePtr, base32);
		drawStatic(gamePtr, base2); 
		
		while(gamePtr->gameOver != TRUE && gamePtr->Lives!= 0)
		{
			if(isWaiting())
				Action = read_from_buffer();
			
			if(Action == ESC)
				gamePtr->gameOver = TRUE;
			
			if(gamePtr->Restart)
			{
				reset_sound();
				switch(gamePtr->Level)
				{
					case 1:
					initializeLevelOne(gamePtr);
					clear_screen(base32);
					clear_screen(base2);
					render(gamePtr, base32, base2);
					drawStatic(gamePtr,base32);
					drawStatic(gamePtr,base2);
				}
				gamePtr->Restart = FALSE;
			}
			if(Action == SPACEBAR && gamePtr->Score != 0)
			{
				if(initializeBullet(gamePtr))
				{	
					gun_effect = TRUE;
					gamePtr->Score--;
					oldScore--;
				}
				Action = 0x00;
			}
			else
				requestMovePlayer(gamePtr, Action);
		 	if(gamePtr->Score > oldScore)
			{
				oldScore = gamePtr->Score;
				point_effect = TRUE;
			}
			if(render_request)
			{
				requestMoveZombie(gamePtr);
				move(gamePtr);
				if(toggle == 1)
				{
					render(gamePtr, base32, base2);
					remakeZombies(gamePtr);
					Setscreen(-1, base32, -1);
					
					toggle = 2;
				}
				else if(toggle == 2)
				{
					render(gamePtr, base2, base32);				
					Setscreen(-1, base2, -1);
					
					toggle = 1;
				}
				render_request = FALSE;
			}
			
		}
		Setscreen(-1, base32, -1);
		clear_screen(base32);
		Action = 0x00;
		
		/* Print End Game Splash with Score */
		if(gamePtr->Score != 0){
			fill_screen((UINT8*)base32,splash_endGameScore0);
			renderFinalScore(gamePtr,base32);		
		}
		/* Print End Game Splash without Score*/
		else
			fill_screen((UINT8*)base32,splash_endGame);
		
		while(Action != SPACEBAR)
		{
			if(isWaiting())
				Action = read_from_buffer();
		}
	}
	/* 2 Player Selected */
	else if(gamePtr->enteredSelection == 1){
		clear_screen(base32);
	}
	else if(gamePtr->enteredSelection == 2){
		clear_screen(base32);
	}
	/***********************************************************************************************/
	stop_sound();
	install_vector(VBL, orig_VBL_vector);
	install_vector(IKBD, orig_IKBD_vector);
	clear_screen(base32);
	return 0;
}

/* ================================================
- Name: disable_cursor
- Purpose: disables flashing cursor
================================================ */
void disable_cursor()
{
	printf("\033f");
	fflush(stdout);
}
/* ================================================
- Name: install_vector
- Purpose: injstall custom vector 
================================================ */
Vector install_vector(int num, Vector vector) 
{ 
	 Vector orig; 
	 Vector *vectp = (Vector *)((long)num << 2);  
	 long old_ssp = Super(0); 
	 orig = *vectp;  
	 *vectp = vector; 
	 Super(old_ssp);  
	 return orig; 
} 
/*===================== ================================================
- Name: do_VBL_ISR
- Purpose: incremeants global variables in background 70 times a second 
====================================================================== */
void do_VBL_ISR()
{
	render_request = TRUE;
	if(update_music(music_notes))
		music_notes = 0;
	else
		music_notes++;
	
	if(gun_effect){
		gun_shot();
		gun_effect = FALSE;
	}
	if(point_effect){
		point_increment_sound();
		point_effect = FALSE;
	}
	if(mouseEnable)
	{
		clearMouse(base32, mouseX, mouseY);
		restoreBKGD(base32, mouseX, mouseY, background);
		mouseX += currX;
		currX = 0;
		mouseY += currY;
		currY = 0;
		if(mouseX < 0)
			mouseX = 0;
		if(mouseX > 608)
			mouseX = 608;
		if(mouseY < 0)
			mouseY = 0;
		if(mouseY > 367)
			mouseY = 367;
		saveBKGD(base32, mouseX, mouseY, background);
		printMouse(base32, mouseX, mouseY);
		mouseEnable = FALSE;
	}
}
/*===================== ================================================
- Name: do_VBL_ISR
- Purpose: incremeants global variables in background 70 times a second 
====================================================================== */
void do_IKBD_ISR()
{
	SCANCODE code = *IKBD_RDR;
	
	if(Mouse_count == 0)
	{
		if(code >= 0xF8)
		{
			if(code > 0xF8)
				mouseClick = TRUE;
			Mouse_count++; 
		}
		else
		{
			if((code & 0x80) != 0x80)
				write_to_buffer(code);
		}
	}
	else
	{
		if(Mouse_count == 1)
		{
			deltaX = (char)code;
			currX += deltaX;
			Mouse_count++;
		}
		else
		{
			deltaY = (char)code;
			currY += deltaY;
			Mouse_count = 0;
			if(!start)
				mouseEnable = TRUE;
		}
	}
	
	*MFP_IS &= 0xBF;
}
/*===================== ================================================
- Name: write_to_buffer
- Purpose: increments the tail position of the buffer and adds an element to the buffer 
====================================================================== */
void write_to_buffer(SCANCODE code)
{
	buffer[tail] = code;
	tail++;
}
/*===================== ================================================
- Name:read_from_buffer
- Purpose: gets the head of the buffer and returns long version of the scancode 
			concatinated with the asccii value of the key
====================================================================== */
long read_from_buffer()
{
	long old_ssp = Super(0);
	
	char ascii_val;
	long return_val;
	SCANCODE scan_val;
	
	*MFP_IE &= 0xBF;

	scan_val = buffer[head++];
	ascii_val = *(ASCII_TABLE + scan_val);
	return_val = (((long)scan_val) << 16) | ascii_val;
	/*printf("0x00%x00%x\n", (char)(return_val >> 16), (char)(return_val));*/
	*MFP_IE |= 0x40;
	
	Super(old_ssp);
	
	return return_val;
}
/*===================== ================================================
- Name: isWaiting
- Purpose: returns true if the buffer is not empty
====================================================================== */
bool isWaiting()
{
	return head != tail;
}
/*===================== ================================================
- Name: updateMouse
- Purpose: chacks to see if the  ouse has been clicked and 
			appropriatly updates the state of the game
====================================================================== */
void updateMouse(struct Model *gamePtr)
{
	if(mouseClick)
		{
			if(mouseX < playerOneXpos2 && 
				mouseX + 16 >= playerOneXpos1 &&
				mouseY < playerOneYpos2 &&
				mouseY +16 >= playerOneYpos1)
				{
					gamePtr->enteredSelection = 0;
					start = TRUE;
					Action = 0x00;
				}
				else
					if(mouseX < playerTwoXpos2 && 
					mouseX + 16 >= playerTwoXpos1 &&
					mouseY < playerTwoYpos2 &&
					mouseY + 16 >= playerTwoYpos1)
					{
						gamePtr->enteredSelection = 1;
						start = TRUE;
						Action = 0x00;
					}
					else
						if(mouseX < exitXpos2 && 
						mouseX + 16 >= exitXpos1 &&
						mouseY < exitYpos2 &&
						mouseY + 16 >= exitYpos1)
						{
							gamePtr->enteredSelection = 2;
							start = TRUE;
							Action = 0x00;
						}
						else
						{
							mouseClick = FALSE;
						}
		}
}
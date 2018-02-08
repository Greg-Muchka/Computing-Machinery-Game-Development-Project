/* ================================================
- Module Name: render
- Purpose: handle all rendering calls for game
================================================ */
#include "RENDER.H"

/* ================================================
- Name: drawStatic
- Purpose: handles the rendering for all static 
(non-moving) objects, such as the walls and the 
SCORE/LIVES bitmaps
================================================ */
void drawStatic(struct Model *gamePtr, UINT32 *base32)
{	
	/* draw walls */
	int i;
	for(i = 0; i < NUMWALLS; i++)
	{
		if(gamePtr->walls[i].isHorizontal)
			plot_Horizontal_Line((UINT8*)base32, (gamePtr->walls[i].Xpos1), (gamePtr->walls[i].Ypos1), (gamePtr->walls[i].Width));
		else
			plot_Vertical_Line((UINT8*)base32, gamePtr->walls[i].Xpos1, gamePtr->walls[i].Ypos1, gamePtr->walls[i].Height);
	}

	/* draw "SCORE" */	
	plot_bitmap_32(base32, 0, 368, font_ch_S);
    plot_bitmap_32(base32, 24, 368, font_ch_C);
    plot_bitmap_32(base32, 52, 368, font_ch_O);
    plot_bitmap_32(base32, 80, 368, font_ch_R);
    plot_bitmap_32(base32, 102, 368, font_ch_E);

	/* draw "LIVES" */	
	plot_bitmap_32(base32, 456, 368, font_ch_L);
    plot_bitmap_32(base32, 480, 368, font_ch_I);
    plot_bitmap_32(base32, 504, 368, font_ch_V);
    plot_bitmap_32(base32, 536, 368, font_ch_E);
    plot_bitmap_32(base32, 568, 368, font_ch_S);	
}
/* ================================================
- Name: render
- Purpose: handle the rendering for all dynamic
objects that may occur in the game
================================================ */
void render(struct Model *gamePtr, UINT32 *base1, UINT32 *base2)
{	
    clearLives(gamePtr, base1);
	clearPlayers(gamePtr, base1);
	clearBullets(gamePtr, base1, base2);
	clearZombies(gamePtr, base1, base2);
	clearPoint(gamePtr, base1, base2);
 
 	drawBullets(gamePtr, base1, base2);
	drawLives(gamePtr,base1);
	drawScore(gamePtr,base1);
	drawZombies(gamePtr, base1);
	drawPlayers(gamePtr, base1, base2);
	drawPoint(gamePtr, base1, base2);

}
void restoreBKGD(UINT32 *base, int x, int y, UINT32 *background)
{
	int i, j = 0;
	if(x >= 0 && x+ 31 < SCREEN_WIDTH && y >= 0 && y + 32 < SCREEN_HEIGHT)
	{
		for(i = 0; i < BITMAP_MAX; i++){
			*(base + (y+i) * 20 + (x >> 5)) 	  = *(background + (j++));
			*(base + (y+i) * 20 + ((x >> 5) + 1)) = *(background + (j++));
			
			/* NOTE: Changed |= to = (before the bitmap[i])*/
		}
	}
}
void saveBKGD(UINT32 *base, int x, int y, UINT32 *background)
{
	int i, j = 0;
	if(x >= 0 && x+ 31 < SCREEN_WIDTH && y >= 0 && y + 32 < SCREEN_HEIGHT)
	{
		for(i = 0; i < BITMAP_MAX; i++){
			*(background + (j++)) = *(base + (y+i) * 20 + (x >> 5));
			*(background + (j++)) = *(base + (y+i) * 20 + ((x >> 5) + 1));
			
			/* NOTE: Changed |= to = (before the bitmap[i])*/
		}
	}
}
void printMouse(UINT32 *base, int x, int y)
{
	int i;
	if(x >= 0 && x+ 31 < SCREEN_WIDTH && y >= 0 && y + BITMAP_MAX -1 < SCREEN_HEIGHT)
	{
		for(i = 0; i < BITMAP_MAX; i++){
			*(base + (y+i) * 20 + (x >> 5)) ^= selection_bitmap[i] >> (x & 31);
			*(base + (y+i) * 20 + (x >> 5) + 1) ^= selection_bitmap[i] << (32 - (x & 31));
			/* NOTE: Changed |= to = (before the bitmap[i])*/
		}
	}
}
void clearMouse(UINT32 *base, int mouseX, int mouseY)
{
	clear_bitmap_32(base, mouseX, mouseY);
}
/* ================================================
- Name: renderFinalScore
- Purpose: handle the rendering for the final score
used at the end of the game
================================================ */
void renderFinalScore(struct Model *gamePtr, UINT32 *base32){
	int pos1 = 0, pos2 = 0, pos3 = 0;	

	pos1 = (gamePtr->Score % 10);
	pos2 = (gamePtr->Score % 100)/10;
	pos3 = gamePtr->Score/100;
	
	/* 3rd Position _ _ x */
	plotScore(base32,pos3,271,300);
	
	/* 2nd Position _ x _ */
	plotScore(base32,pos2,303,300);
	
	/* 1st Position _ x _ */
	plotScore(base32,pos1,335,300);
}
/* ================================================
- Name: clearPoint
- Purpose: handles the render clearing for the
points
================================================ */
void clearPoint(struct Model *gamePtr, UINT32 *base1, UINT32 *base2){
	int i;
	bool found = FALSE;
	
	for(i = 0; i < NUMPOINT && !found; i++){
		if(gamePtr->point[i].Clear){
			clear_bitmap_8((UINT8*)base1, gamePtr->point[i].Xpos, gamePtr->point[i].Ypos);
			clear_bitmap_8((UINT8*)base2, gamePtr->point[i].Xpos, gamePtr->point[i].Ypos);
			found = TRUE;
			gamePtr->point[i].Clear = FALSE;
		}
	}
}
/* ================================================
- Name: clearLives
- Purpose: handles the render clearing for the
lives
================================================ */
void clearLives(struct Model *gamePtr, UINT32 *base32){
    clear_bitmap_32(base32, 600, 368);
}
/* ================================================
- Name: clearZombies
- Purpose: handles the render clearing for the
zombies
================================================ */
void clearZombies(struct Model *gamePtr, UINT32 *base32, UINT32 *base2){
	int i;
	for(i = 0; i < NUMZOMBIE; i++){
		if(gamePtr->zombies[i].Active){
			clear_bitmap_32(base32, gamePtr->zombies[i].Xold, gamePtr->zombies[i].Yold);			
		}
        if(gamePtr->zombies[i].Clear){
			clear_bitmap_32(base32, gamePtr->zombies[i].Xpos, gamePtr->zombies[i].Ypos);
			clear_bitmap_32(base2, gamePtr->zombies[i].Xpos, gamePtr->zombies[i].Ypos);
			
			clear_bitmap_32(base32, gamePtr->zombies[i].Xold, gamePtr->zombies[i].Yold);
			clear_bitmap_32(base2, gamePtr->zombies[i].Xold, gamePtr->zombies[i].Yold);
			
			gamePtr->zombies[i].Clear = FALSE;
		}
	}
}
/* ================================================
- Name: clearPlayers
- Purpose: handles the render clearing for the
players
================================================ */
void clearPlayers(struct Model *gamePtr, UINT32 *base32){
	int i;
	for(i = 0; i < NUMPLAYER; i++){
		if(gamePtr->players[i].Active){
			clear_bitmap_32(base32, gamePtr->players[i].Xold, gamePtr->players[i].Yold);		
		}
	}
}
/* ================================================
- Name: clearBullets
- Purpose: handles the render clearing for the
bullets
================================================ */
void clearBullets(struct Model *gamePtr, UINT32 *base32, UINT32 *base2){
	int i;
    for(i = 0; i < NUMBULLET; i++){
		if(!gamePtr->bullets[i].newBullet && gamePtr->bullets[i].Active){
			clear_bitmap_8((UINT8*)base32, gamePtr->bullets[i].Xold, gamePtr->bullets[i].Yold);
			clear_bitmap_8((UINT8*)base2, gamePtr->bullets[i].Xold, gamePtr->bullets[i].Yold);
		}
		
		if(gamePtr->bullets[i].Clear){
			gamePtr->bullets[i].Clear = FALSE;
			clear_bitmap_8((UINT8*)base32, gamePtr->bullets[i].Xpos, gamePtr->bullets[i].Ypos);
			clear_bitmap_8((UINT8*)base2, gamePtr->bullets[i].Xpos, gamePtr->bullets[i].Ypos);		
		}
	}
}
/* ================================================
- Name: drawPoint
- Purpose: handles the rendering for the points
================================================ */
void drawPoint(struct Model *gamePtr, UINT32 *base1, UINT32 *base2)
{
	int i;
	bool found = FALSE;
	for(i = 0; i < NUMPOINT && !found; i++){
		if(gamePtr->point[i].Active){
			plot_bitmap_8((UINT8*)base1, gamePtr->point[i].Xpos, gamePtr->point[i].Ypos, point_bitmap);
			plot_bitmap_8((UINT8*)base2, gamePtr->point[i].Xpos, gamePtr->point[i].Ypos, point_bitmap);
			found = TRUE;
		}
	}
}
/* ================================================
- Name: drawScore
- Purpose: handles the calculations for plotScore
================================================ */
void drawScore(struct Model *gamePtr, UINT32 *base32){
	int pos1 = 0, pos2 = 0, pos3 = 0;
	pos1 = (gamePtr->Score % 10);
	pos2 = (gamePtr->Score % 100)/10;
	pos3 = gamePtr->Score/100;
	
	/* 3rd Position _ _ x */
	plotScore(base32,pos3,134,368);
	
	/* 2nd Position _ x _ */
	plotScore(base32,pos2,166,368);
	
	/* 1st Position _ x _ */
	plotScore(base32,pos1,198,368);
}
/* ================================================
- Name: plotScore
- Purpose: handles the rendering for the score
================================================ */
void plotScore(UINT32 *base32, int posNum, int xPos, int yPos){
	clear_bitmap_32(base32, xPos,yPos);
	
	switch(posNum){
		case 0: 
			plot_bitmap_32(base32, xPos, yPos, font_ch_0);
		break;
		case 1:
			plot_bitmap_32(base32, xPos, yPos, font_ch_1);	
		break;
		case 2:
			plot_bitmap_32(base32, xPos, yPos, font_ch_2);		
		break;
		case 3: 
			plot_bitmap_32(base32, xPos, yPos, font_ch_3);
		break;
		case 4:
			plot_bitmap_32(base32, xPos, yPos, font_ch_4);	
		break;
		case 5:
			plot_bitmap_32(base32, xPos, yPos, font_ch_5);		
		break;		
		case 6: 
			plot_bitmap_32(base32, xPos, yPos, font_ch_6);
		break;
		case 7:
			plot_bitmap_32(base32, xPos, yPos, font_ch_7);	
		break;
		case 8:
			plot_bitmap_32(base32, xPos, yPos, font_ch_8);		
		break;
		case 9:
			plot_bitmap_32(base32, xPos, yPos, font_ch_9);		
		break;
	}	
}
/* ================================================
- Name: drawLives
- Purpose: handles the rendering for lives
================================================ */
void drawLives(struct Model *gamePtr, UINT32 *base32){
    int numLives = gamePtr->Lives;

    switch(numLives){
        case 1:
			plot_bitmap_32(base32, 600, 368, font_ch_1);
		break;
        case 2:
			plot_bitmap_32(base32, 600, 368, font_ch_2);		
        break;
		case 3:
			plot_bitmap_32(base32, 600, 368, font_ch_3);
        break;
    }
}
/* ================================================
- Name: drawZombies
- Purpose: handles the rendering for zombies
================================================ */
void drawZombies(struct Model *gamePtr, UINT32 *base32){
	int i;
	for(i = 0; i < NUMZOMBIE; i++)
	{
		if(gamePtr->zombies[i].Active)
		{
			switch(gamePtr->zombies[i].XDirection){
			case 1:
			plot_bitmap_32(base32, gamePtr->zombies[i].Xpos, gamePtr->zombies[i].Ypos, zombie_bitmap_right);
			break;
			case -1:
			plot_bitmap_32(base32, gamePtr->zombies[i].Xpos, gamePtr->zombies[i].Ypos, zombie_bitmap_left);
			}
			switch(gamePtr->zombies[i].YDirection){
			case 1:
			plot_bitmap_32(base32, gamePtr->zombies[i].Xpos, gamePtr->zombies[i].Ypos, zombie_bitmap_down);
			break;
			case -1:
			plot_bitmap_32(base32, gamePtr->zombies[i].Xpos, gamePtr->zombies[i].Ypos, zombie_bitmap_up);
			}
		}
	}
}
/* ================================================
- Name: drawPlayers
- Purpose: handles the rendering for players
================================================ */
void drawPlayers(struct Model *gamePtr, UINT32 *base32, UINT32 *base2){
	int i;
	for(i = 0; i < NUMPLAYER; i++)
	{
		if(gamePtr->players[i].Active)
		{
			switch(gamePtr->players[i].XDirection){
			case 1:
			plot_bitmap_32(base32, gamePtr->players[i].Xpos, gamePtr->players[i].Ypos, gangster_bitmap_right);
			plot_bitmap_32(base2, gamePtr->players[i].Xpos, gamePtr->players[i].Ypos, gangster_bitmap_right);			
			break;
			case -1:
			plot_bitmap_32(base32, gamePtr->players[i].Xpos, gamePtr->players[i].Ypos, gangster_bitmap_left);
			plot_bitmap_32(base2, gamePtr->players[i].Xpos, gamePtr->players[i].Ypos, gangster_bitmap_left);
			}
			switch(gamePtr->players[i].YDirection){
			case 1:
			plot_bitmap_32(base32, gamePtr->players[i].Xpos, gamePtr->players[i].Ypos, gangster_bitmap_down);			
			plot_bitmap_32(base2, gamePtr->players[i].Xpos, gamePtr->players[i].Ypos, gangster_bitmap_down);	
			break;
			case -1:
			plot_bitmap_32(base32, gamePtr->players[i].Xpos, gamePtr->players[i].Ypos, gangster_bitmap_up);
			plot_bitmap_32(base2, gamePtr->players[i].Xpos, gamePtr->players[i].Ypos, gangster_bitmap_up);
			}
		}
			
	}
}
/* ================================================
- Name: drawBullets
- Purpose: handles the rendering for bullets
================================================ */
void drawBullets(struct Model *gamePtr, UINT32 *base32, UINT32 *base2){
	int i;
	for(i = 0; i < NUMBULLET; i++)
	{
		if(gamePtr->bullets[i].Active)
		{
			if(gamePtr->bullets[i].newBullet)
				gamePtr->bullets[i].newBullet = FALSE;
			
			gamePtr->bullets[i].Clear = FALSE;
			switch(gamePtr->bullets[i].XDirection){
			case 1:
			plot_bitmap_8((UINT8*)base32, gamePtr->bullets[i].Xpos, gamePtr->bullets[i].Ypos, bullet_bitmapRight);	
			plot_bitmap_8((UINT8*)base2, gamePtr->bullets[i].Xpos, gamePtr->bullets[i].Ypos, bullet_bitmapRight);	
			break;
			case -1:
			plot_bitmap_8((UINT8*)base32, gamePtr->bullets[i].Xpos, gamePtr->bullets[i].Ypos, bullet_bitmapLeft);			
			plot_bitmap_8((UINT8*)base2, gamePtr->bullets[i].Xpos, gamePtr->bullets[i].Ypos, bullet_bitmapLeft);	
			}
			switch(gamePtr->bullets[i].YDirection){
			case 1:
			plot_bitmap_8((UINT8*)base32, gamePtr->bullets[i].Xpos, gamePtr->bullets[i].Ypos, bullet_bitmapDown);				
			plot_bitmap_8((UINT8*)base2, gamePtr->bullets[i].Xpos, gamePtr->bullets[i].Ypos, bullet_bitmapDown);
			break;
			case -1:
			plot_bitmap_8((UINT8*)base32, gamePtr->bullets[i].Xpos, gamePtr->bullets[i].Ypos, bullet_bitmapUp);
			plot_bitmap_8((UINT8*)base2, gamePtr->bullets[i].Xpos, gamePtr->bullets[i].Ypos, bullet_bitmapUp);
			}
		}
	}
}
/* ================================================
- Module Name: render
- Purpose: header file for render.c
================================================ */
#ifndef RENDER_H
#define RENDER_H
#include "../global/TYPES.H"
#include "../model/MODEL.H"
#include "RASTER.H"
#include "../images/BITMAPS.H"
#include "../clearqk/CLEAR_QK.H"

void plotScore(UINT32 *base32, int posNum, int xPos, int yPos);

void render(struct Model *gamePtr, UINT32 *base1, UINT32 *base2);
void renderFinalScore(struct Model *gamePtr, UINT32 *base32);
void clear(struct Model *gamePtr, UINT32 *base32);

void clearLives(struct Model *gamePtr, UINT32 *base32);
void clearScore(struct Model *gamePtr, UINT32 *base32);
void clearZombies(struct Model *gamePtr, UINT32 *base32, UINT32 *base2);
void clearBullets(struct Model *gamePtr, UINT32 *base32, UINT32 *base2);
void clearPlayers(struct Model *gamePtr, UINT32 *base32);
void clearPoint(struct Model *gamePtr, UINT32 *base1, UINT32 *base2);

void drawLives(struct Model *gamePtr, UINT32 *base32);
void drawScore(struct Model *gamePtr, UINT32 *base32);
void drawZombies(struct Model *gamePtr, UINT32 *base32);
void drawPlayers(struct Model *gamePtr, UINT32 *base32, UINT32 *base2);
void drawBullets(struct Model *gamePtr, UINT32 *base32, UINT32 *base2);
void drawPoint(struct Model *gamePtr, UINT32 *base1, UINT32 *base2);
void drawStatic(struct Model *gamePtr, UINT32 *base32);

void printMouse(UINT32 *base, int mouseX, int mouseY);
void clearMouse(UINT32 *base, int mouseX, int mouseY);
void saveBKGD(UINT32 *base32, int x, int y, UINT32 *background);
void restoreBKGD(UINT32 *base32, int mouseX, int mouseY, UINT32 *background);


#endif
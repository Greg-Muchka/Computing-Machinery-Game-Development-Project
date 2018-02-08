/* ================================================
- Name: game
- Purpose: header file for game.c
================================================ */
#ifndef GAME_H
#define GAME_H

#include <osbind.h>
#include "../events/Event.H"
#include "../drawing/Render.H"
#include "../global/TYPES.H"
#include "../audio/PSG.H"
#include "../clearqk/CLEAR_QK.H"
#include "../steem/STEEM.H"

#define VBL 28
#define IKBD 70

void disable_cursor();
void do_VBL_ISR();
void do_IKBD_ISR();
void write_to_buffer(unsigned char);
long read_from_buffer();
bool isWaiting();
void updateMouse(struct Model *gamePtr);
#endif
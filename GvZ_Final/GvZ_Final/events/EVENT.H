/* ================================================
- Module Name: event
- Purpose: header file for event.c
================================================ */
#ifndef EVENT_H
#define EVENT_H
#include "../drawing/RENDER.H"
#include "../model/Model.H"

void move(struct Model *gamePtr);
void moveBullet(struct Model *gamePtr);
void moveZombie(struct Model *gamePtr);
void movePlayer(struct Model *gamePtr);
#endif
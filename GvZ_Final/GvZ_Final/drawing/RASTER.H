/* ================================================
- Module Name: raster
- Purpose: header for raster.c
================================================ */
#ifndef RASTER_H
#define RASTER_H

#include <osbind.h>
#include <unistd.h>
#include "../global/TYPES.H"
#include "../images/BITMAPS.H"

void fill_screen(UINT8 *base, const UINT8  *pattern); 


void plot_pixel(UINT8 *base, int x, int y);
void plot_Horizontal_Line(UINT8 *base, int x, int y, int z);
void plot_Vertical_Line(UINT8 *base, int x, int y, int z);
void plot_Line(UINT8 *base, int x, int y, int a, int b);

void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap);
void clear_bitmap_32(UINT32 *base, int x, int y);
void clear_bitmap_32_mouse(UINT32 *base, int x, int y);

void plot_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap);
void clear_bitmap_8(UINT8 *base, int x, int y);

#endif
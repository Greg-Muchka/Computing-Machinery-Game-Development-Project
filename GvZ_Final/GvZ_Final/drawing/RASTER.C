/* ================================================
- Module Name: raster
- Purpose: handles raster graphics creation
================================================ */
#include "RASTER.H"
#include <string.h>
/* ================================================
- Name: 
- Purpose:
================================================ */
void fill_screen(UINT8 *base, const UINT8  *pattern)
{
	memcpy(base,pattern,(long)32000);
}
/* ================================================
- Name: 
- Purpose:
================================================ */
void plot_pixel(UINT8 *base, int x, int y)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		*(base + y * 80 + (x >> 3)) |= 1 << 7 - (x & 7);
}
/* ================================================
- Name: 
- Purpose:
================================================ */
void plot_Horizontal_Line(UINT8 *base, int x, int y, int z)
{
	int i = 0;
	int j = 0;
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT && 
		z >= 0 && z < SCREEN_WIDTH)
	{
		for(j = 0; j < 8; j++){
			for(i = 0; i <= (z-x); i++){
				*(base + (y+j) * 80 + ((x + i) >> 3)) = 0xFF;
			}
	}
	}
}
/* ================================================
- Name: 
- Purpose:
================================================ */
void plot_Vertical_Line(UINT8 *base, int x, int y, int z)
{
	int i = 0;
	if (x >= 0 && x <= SCREEN_WIDTH && y >= 0 && y <= SCREEN_HEIGHT && 
		z >= 0 && z <= SCREEN_HEIGHT)
	{
		for(i = 0; i < (z-y); i++){
			*(base + (y+i) * 80 + (x >> 3)) = 0xFF;
		}
	}
} 
/* ================================================
- Name: 
- Purpose:
================================================ */
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap)
{
	int i;
	if(x >= 0 && x+ 31 < SCREEN_WIDTH && y >= 0 && y + BITMAP_MAX -1 < SCREEN_HEIGHT)
	{
		for(i = 0; i < BITMAP_MAX; i++){
			*(base + (y+i) * 20 + (x >> 5)) |= bitmap[i] >> (x & 31);
			*(base + (y+i) * 20 + (x >> 5) + 1) |= bitmap[i] << (32 - (x & 31));
			/* NOTE: Changed |= to = (before the bitmap[i])*/
		}
	}
}
/* ================================================
- Name: 
- Purpose:
================================================ */
void clear_bitmap_32(UINT32 *base, int x, int y)
{
	int i;
	if(x >= 0 && x+ 31 < SCREEN_WIDTH && y >= 0 && y + BITMAP_MAX -1 < SCREEN_HEIGHT)
	{
		for(i = 0; i < BITMAP_MAX; i++){
			*(base + (y+i) * 20 + (x >> 5)) &= 0xFFFFFFFF << (32 - (x & 31));
			*(base + (y+i) * 20 + (x >> 5) + 1) &= 0xFFFFFFFF >> (x & 31);;
			/* NOTE: Changed |= to = (before the bitmap[i])*/
		}
	}
}
/* ================================================
- Name: 
- Purpose:
================================================ */
void clear_bitmap_32_mouse(UINT32 *base, int x, int y)
{
	int i;
	if(x >= 0 && x+ 31 < SCREEN_WIDTH && y >= 0 && y + BITMAP_MAX -1 < SCREEN_HEIGHT)
	{
		for(i = 0; i < BITMAP_MAX; i++){
			*(base + (y+i) * 20 + (x >> 5)) |= 0xFFFFFFFF << (32 - (x & 31));
			*(base + (y+i) * 20 + (x >> 5) + 1) |= 0xFFFFFFFF >> (x & 31);;
			/* NOTE: Changed |= to = (before the bitmap[i])*/
		}
	}
}
/* ================================================
- Name: 
- Purpose:
================================================ */
void plot_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap)
{
	int i;
	if(x >= 0 && x+ 7 < SCREEN_WIDTH && y >= 0 && y + BITMAP_MIN -1 < SCREEN_HEIGHT)
	{
		for(i = 0; i < BITMAP_MIN; i++){
			*(base + (y+i) * 80 + (x >> 3)) |= bitmap[i] >> (x & 7);
			*(base + (y+i) * 80 + (x >> 3) + 1) |= bitmap[i] << (8 - (x & 7)) ;
			/* NOTE: Changed |= to = (before the bitmap[i])*/
		}
	}
}
/* ================================================
- Name: 
- Purpose:
================================================ */
void clear_bitmap_8(UINT8 *base, int x, int y)
{
	int i;
	if(x >= 0 && x+ 7 < SCREEN_WIDTH && y >= 0 && y + BITMAP_MIN -1 < SCREEN_HEIGHT)
	{
		for(i = 0; i < BITMAP_MIN; i++){
			
			*(base + (y+i) * 80 + (x >> 3)) = 0x0 >> (x & 7);
			*(base + (y+i) * 80 + (x >> 3) + 1) = 0x0 << (8 - (x & 7)) ;
			/* NOTE: Changed |= to = (before the bitmap[i])*/
		}
	}
}
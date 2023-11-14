/**
 * @file render.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../../hal/hal.h"
#include <cstdint>


/* Visible (NTSC) screen height */
#ifndef NES_VISIBLE_HEIGHT
#define  NES_VISIBLE_HEIGHT   224
#endif /* !NES_VISIBLE_HEIGHT */
#define  NES_SCREEN_WIDTH     256
#define  NES_SCREEN_HEIGHT    240


extern uint16_t myPalette[];


extern "C" void render_frame(const uint8_t* data[])
{
    // for (int32_t i = 0; i < NES_SCREEN_HEIGHT; i++)
    // {
    //     HAL::GetCanvas()->writeIndexedPixels((uint8_t *)(data[i]), myPalette, NES_SCREEN_WIDTH);
    // }

    for (int y = 0; y < NES_SCREEN_HEIGHT; y++)
	{
		// HAL::GetCanvas()->writeIndexedPixels((const uint8_t*)(bmp->line), myPalette, NES_SCREEN_WIDTH);
		// gfx->writeIndexedPixels((uint8_t *)(data[i] + frame_x_offset), myPalette, frame_line_pixels);
		for (int x = 0; x < NES_SCREEN_WIDTH; x++)
		{
			HAL::GetCanvas()->drawPixel(x, y, myPalette[data[y][x]]);
		}
	}
	HAL::CanvasUpdate();
	printf("???\n");
}

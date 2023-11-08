/**
 * @file main.cpp
 * @author Forairaaaaa
 * @brief
 * https://github.com/lovyan03/LovyanGFX/tree/fa1e250bff49e933a5d2eeccd15dab0b8f5dfb02/examples_for_PC
 * @version 0.1
 * @date 2023-11-04
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "lgfx/v1/lgfx_fonts.hpp"
#include "lgfx/v1/misc/enum.hpp"
#include "lgfx/v1/platforms/sdl/common.hpp"
#include "rachel/rachel.h"
#define LGFX_USE_V1
#include <LGFX_AUTODETECT.hpp>
#include <LovyanGFX.hpp>
#include <random>
#include "performance_window.hpp"



// static LGFX _lcd(240, 240);
// static LGFX _lcd(480, 320);

// static LGFX_Sprite *_canvas;
// #define _canvas_update() _canvas->pushSprite(0, 0)

#define PIN_LEFT 39
#define PIN_DOWN 38
#define PIN_RIGHT 37
#define PIN_UP 36

std::random_device rd;
std::mt19937 gen(rd());
int Game_random(int low, int high) 
{
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

// static PerformanceWindow _pw;


void setup() 
{
    RACHEL::Setup();
}

void loop()
{
    RACHEL::Loop();

    // lgfx::delay(16);
    // _pw.update();
}

/**
 * @file hal_sim.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "lgfx/v1/LGFX_Sprite.hpp"
#include "lgfx/v1/platforms/sdl/common.hpp"
#define LGFX_USE_V1
#include <LGFX_AUTODETECT.hpp>
#include <LovyanGFX.hpp>
#include "lgfx/v1/lgfx_fonts.hpp"
#include "hal.h"



class HAL_Simulator : public HAL
{
    std::string type() override { return "Simulator"; }

    void init() override
    {
        // Display 
        _display = new LGFX(240, 240);
        _display->init();

        // Canvas
        _canvas = new LGFX_Sprite(_display);
        _canvas->createSprite(_display->width(), _display->height());
    }

    void delay(unsigned long milliseconds) override
    {
        lgfx::delay(milliseconds);
    }

    unsigned long millis() override
    {
        return lgfx::millis();
    }

    void loadSystemFont24() override
    {
        // https://github.com/Bodmer/TFT_eSPI/tree/master/Tools/Create_Smooth_Font/Create_font
        // http://lvgl.100ask.net/8.1/tools/fonts-zh-source.html#id7
        // https://r12a.github.io/app-conversion/
        _canvas->loadFont("../rachel/apps/assets/fonts/zpix_cn_24.vlw");
    }
};

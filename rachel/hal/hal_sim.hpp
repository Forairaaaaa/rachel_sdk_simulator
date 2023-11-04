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
};

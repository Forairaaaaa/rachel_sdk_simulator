/**
 * @file hal.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include "hal.h"


HAL* HAL::_hal = nullptr;


HAL* HAL::Get()
{
    return _hal;
}


bool HAL::Check()
{
    return _hal != nullptr;
}


bool HAL::Inject(HAL* hal)
{
    if (_hal != nullptr)
    {
        spdlog::error("HAL already exist");
        return false;
    }

    if (hal == nullptr)
    {
        spdlog::error("invalid HAL ptr");
        return false;
    }

    hal->init();
    spdlog::info("HAL injected, type: {}", hal->type());

    _hal = hal;

    return true;
}


void HAL::Destroy()
{   
    if (_hal == nullptr)
    {
        spdlog::error("HAL not exist");
        return;
    }

    delete _hal;
    _hal = nullptr;
}


void HAL::renderFpsPanel()
{
    static unsigned long time_count = 0;

    _canvas->setTextColor(TFT_WHITE, TFT_BLACK);
    _canvas->setTextSize(2);
    _canvas->drawNumber(1000 / (millis() - time_count), 0, 0, &fonts::Font0);

    time_count = millis();
}


static const uint32_t _blue_screen_bg_color = 0x003c94;

void HAL::popFatalError(std::string msg)
{
    loadTextFont24();
    _canvas->setTextColor(TFT_WHITE, _blue_screen_bg_color);
    _canvas->fillScreen(_blue_screen_bg_color);
    
    _canvas->setCursor(8, 15);
    _canvas->setTextSize(5);
    _canvas->printf(":(");

    _canvas->setCursor(0, 155);
    _canvas->setTextSize(1);
    _canvas->printf("   Fatal Error\n   %s", msg.c_str());

    _canvas->pushSprite(0, 0);


    // Wait reboot or power off 
    while (1)
    {
        delay(100);
        if (getButton(GAMEPAD::BTN_A))
            reboot();
        if (getButton(GAMEPAD::BTN_B))
            powerOff();
    }
}


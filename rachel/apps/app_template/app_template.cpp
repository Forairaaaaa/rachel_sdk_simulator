/**
 * @file app_template.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_template.h"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include "../assets/theme/theme.h"


using namespace MOONCAKE::APPS;


void AppTemplate::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppTemplate::onResume()
{
    spdlog::info("{} onResume", getAppName());

    HAL::GetCanvas()->setTextScroll(true);
    HAL::GetCanvas()->setCursor(0, 0);
}


void AppTemplate::onRunning()
{
    // Every seconds 
    if ((HAL::Millis() - _data.count) > 1000)
    {
        spdlog::info("{}: Hi", getAppName());

        HAL::GetCanvas()->printf("[%ld] %s: Hi\n", _data.count, getAppName().c_str());
        HAL::CanvasUpdate();

        _data.count = HAL::Millis();
    }

    // Press Select to quit  
    if (HAL::GetButton(GAMEPAD::BTN_SELECT))
        destroyApp();
}


void AppTemplate::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}

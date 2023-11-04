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


using namespace MOONCAKE::APPS;


void AppTemplate::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppTemplate::onRunning()
{
    if ((HAL::Millis() - _data.count) > 1000)
    {
        spdlog::info("{}: Hi", getAppName());
        _data.count = HAL::Millis();
    }
}


void AppTemplate::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}

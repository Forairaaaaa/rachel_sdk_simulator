/**
 * @file app_nofrendo.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_nofrendo.h"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include "../assets/theme/theme.h"

extern "C" {
    #include "nofrendo/nofrendo.h"
}


using namespace MOONCAKE::APPS;


void AppNofrendo::onCreate()
{
    spdlog::info("{} onCreate", getAppName());
}


void AppNofrendo::onResume()
{
    spdlog::info("{} onResume", getAppName());
}


void AppNofrendo::onRunning()
{
    nofrendo_main(0, NULL);
}


void AppNofrendo::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}

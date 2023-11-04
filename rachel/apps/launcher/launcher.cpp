/**
 * @file launcher.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "launcher.h"
#include "lgfx/v1/lgfx_fonts.hpp"
#include "spdlog/spdlog.h"
#include "../../hal/hal.h"
#include <LovyanGFX.hpp>
#include "../assets/theme/theme.h"
#include "assets/launcher_bottom_panel.h"


using namespace MOONCAKE::APPS;


void Launcher::onCreate()
{
    spdlog::info("{} onCreate", getAppName());

    // Enable bg running 
    setAllowBgRunning(true);
    // Auto start 
    startApp();







    HAL::GetCanvas()->fillScreen(THEME_COLOR_DARK);


    HAL::GetCanvas()->pushImage(0, 158, 240, 82, image_data_launcher_bottom_panel);



    HAL::GetCanvas()->setTextColor(THEME_COLOR_DARK, THEME_COLOR_LIGHT);

    HAL::GetCanvas()->setFont(&fonts::efontCN_24_b);


    // HAL::GetCanvas()->drawCenterString("Genshing Import", 120, 174);
    // HAL::GetCanvas()->drawCenterString("_ _,_ _!", 120, 174);

    HAL::GetCanvas()->drawCenterString("原坤", 120, 174);



    HAL::CanvasUpdate();
}


void Launcher::onRunning()
{

}


void Launcher::onRunningBG()
{

}


void Launcher::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}


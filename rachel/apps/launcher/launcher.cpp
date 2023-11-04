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
#include "../assets/icons/icons.h"
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

    HAL::GetCanvas()->setFont(&fonts::efontCN_24);


    // HAL::GetCanvas()->drawCenterString("Genshing Import", 120, 174);
    HAL::GetCanvas()->drawCenterString("SETTINGS", 120, 174);
    // HAL::GetCanvas()->drawCenterString("_ _,_ _!", 120, 174);

    // HAL::GetCanvas()->drawCenterString("原坤", 120, 174);
    // HAL::GetCanvas()->drawCenterString("设置", 120, 174);
    // HAL::GetCanvas()->drawCenterString("起飞", 120, 174);



    HAL::GetCanvas()->pushImage(89, 46, 62, 62, image_data_icon_app_default);

    HAL::GetCanvas()->pushImage(14, 76, 62, 62, image_data_icon_app_default);

    HAL::GetCanvas()->pushImage(164, 76, 62, 62, image_data_icon_app_default);


    
    HAL::GetCanvas()->fillRect(0, 0, 240, 24, THEME_COLOR_LIGHT);


    HAL::GetCanvas()->setFont(&fonts::efontCN_16_b);
    HAL::GetCanvas()->drawCenterString("22:33", 120, 3);


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


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
#include "../utils/system/ui/ui.h"


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
    HAL::GetCanvas()->clear(THEME_COLOR_LIGHT);
    HAL::LoadTextFont24();
    HAL::GetCanvas()->setTextColor(THEME_COLOR_DARK, THEME_COLOR_LIGHT);
}


void AppTemplate::onRunning()
{
    // // Every seconds 
    // if ((HAL::Millis() - _data.count) > 1000)
    // {
    //     spdlog::info("{}: Hi", getAppName());

        
    //     HAL::GetCanvas()->printf(" Hi!");
    //     HAL::CanvasUpdate();


    //     _data.count = HAL::Millis();
    // }


    // // Press Select to quit  
    // if (HAL::GetButton(GAMEPAD::BTN_SELECT))
    //     destroyApp();


    std::vector<std::string> test = {
        "Select Shit:",
        "asdad",
        "sa????",
        "465476756",
        "asd asid afhi",
        "???s333***",
        "77713jdfobih fsd"
        "sdsdjiji s",
        "yyrt rtg",
        "asdad",
        "sa????",
        "465476756",
        "asd asid afhi",
        "???s333***",
        "77713jdfobih fsd"
        "sdsdjiji s",
        "yyrt rtg"
    };
    auto sm = SYSTEM::UI::SelectMenu(test);
    auto index = sm.waitResult();
    spdlog::info("select: {}", test[index]);
    destroyApp();
}


void AppTemplate::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}

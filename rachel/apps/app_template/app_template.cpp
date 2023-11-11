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


using namespace SYSTEM::UI;


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


    




    auto select_menu = SelectMenu();

    std::vector<std::string> test = {
        "[Menu Type]",
        "Left",
        "Center",
        "Right",
        "Quit"
    };

    auto alignment = SelectMenu::ALIGN_LEFT;
    while (1)
    {
        auto result = select_menu.waitResult(test, alignment);
        if (result == 1)
            alignment = SelectMenu::ALIGN_LEFT;
        else if (result == 2)
            alignment = SelectMenu::ALIGN_CENTER;
        else if (result == 3)
            alignment = SelectMenu::ALIGN_RIGHT;
        else
            break;
    }


    destroyApp();
}


void AppTemplate::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());
}

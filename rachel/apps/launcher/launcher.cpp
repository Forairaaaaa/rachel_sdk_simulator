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



void Launcher::_update_clock()
{
    
}


void Launcher::onCreate()
{
    spdlog::info("{} onCreate", getAppName());

    // Enable bg running 
    setAllowBgRunning(true);
    // Auto start 
    startApp();

    _create_menu();
}


void Launcher::onResume()
{
    // Load resources 
    HAL::LoadSystemFont24();
}


void Launcher::onRunning()
{
    _update_clock();
    _update_menu();
}


void Launcher::onRunningBG()
{
    // If only launcher running still 
    if (mcAppGetFramework()->getAppManager().getCreatedAppNum() == 1)
    {
        spdlog::info("back to launcher");

        // Close anim 
        // TODO 
        
        // Back to business
        mcAppGetFramework()->startApp(this);
    }
}


void Launcher::onDestroy()
{
    spdlog::info("{} onDestroy", getAppName());

    _destroy_menu();
}


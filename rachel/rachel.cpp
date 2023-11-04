/**
 * @file rachel.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "rachel.h"
#include "hal/hal.h"
#include "spdlog/spdlog.h"
#include <mooncake.h>
#include "hal/hal_sim.hpp"
#include "apps/apps.h"


using namespace MOONCAKE;
static Mooncake* _mooncake = nullptr;


int Game_random(int low, int high);


void RACHEL::Setup()
{
    spdlog::info("Rachel Setup");

    // HAL injection 
    HAL::Inject(new HAL_Simulator);

    // Mooncake framework 
    _mooncake = new Mooncake;
    _mooncake->init();

    // Install launcher 
    auto launcher = new APPS::Launcher_Packer;

    // Install apps 
    _mooncake->installApp(new APPS::AppTemplate_Packer);

    // Create launcher 
    _mooncake->createApp(launcher);
}


void RACHEL::Loop()
{
    _mooncake->update();
}


void RACHEL::Destroy()
{
    // Free 
    delete _mooncake;
    HAL::Destroy();

    spdlog::warn("Rachel destroy");
}


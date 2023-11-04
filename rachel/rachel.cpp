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


static MOONCAKE::Mooncake* _mooncake = nullptr;


int Game_random(int low, int high);


void RACHEL::Setup()
{
    spdlog::info("Rachel Setup");

    // HAL 
    HAL::Inject(new HAL_Simulator);

    // Mooncake framework 
    _mooncake = new MOONCAKE::Mooncake;
    _mooncake->init();
}


void RACHEL::Loop()
{
    _mooncake->update();

    HAL::GetCanvas()->fillSmoothCircle(
        Game_random(0, HAL::GetCanvas()->width()), Game_random(0, HAL::GetCanvas()->height()),
        Game_random(1, 24), Game_random(TFT_BLACK, TFT_WHITE));
    HAL::CanvasUpdate();
}


void RACHEL::Destroy()
{
    // Free 
    delete _mooncake;
    HAL::Destroy();

    spdlog::warn("Rachel-Main destroy");
}


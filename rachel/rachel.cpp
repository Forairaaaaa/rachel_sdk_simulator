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


using namespace MOONCAKE;


void RACHEL::Main()
{
    spdlog::info("Rachel-Main");

    // HAL 
    HAL::Inject(new HAL);

    // Mooncake framework 
    auto mc = new Mooncake;
    mc->init();


    // Main loop 
    while (1)
    {
        mc->update();
    }


    // Free 
    delete mc;
    HAL::Destroy();

    spdlog::warn("Rachel-Main quit");
}

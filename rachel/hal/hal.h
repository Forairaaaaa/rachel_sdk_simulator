/**
 * @file hal.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <iostream>
#include <string>
#include "lgfx/v1/platforms/sdl/common.hpp"
#define LGFX_USE_V1
#include <LGFX_AUTODETECT.hpp>
#include <LovyanGFX.hpp>

/**
 * @brief Singleton like pattern to simplify hal's getter 
 * 1) Inherit and override methods to create a specific hal 
 * 2) Use HAL::Inject() to inject your hal
 * 3) Use HAL:Get() to get this hal wherever you want 
 */
class HAL 
{
private:
    static HAL* _hal;

public:
    /**
     * @brief Get HAL pointer 
     * 
     * @return HAL* 
     */
    static HAL* Get();

    /**
     * @brief Check if HAL is valid 
     * 
     * @return true 
     * @return false 
     */
    static bool Check();

    /**
     * @brief HAL injection, init() will be called here  
     * 
     * @param hal 
     * @return true 
     * @return false 
     */
    static bool Inject(HAL* hal);

    /**
     * @brief Destroy HAL and free memory 
     * 
     */
    static void Destroy();


    virtual ~HAL() {}
    virtual void init() {}
    virtual std::string type() { return "Base"; }

};

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
#include <LovyanGFX.hpp>
#include "lgfx/v1/LGFXBase.hpp"
#include "lgfx/v1/LGFX_Sprite.hpp"
#include "lgfx/v1_autodetect/LGFX_AutoDetect_sdl.hpp"
#include <iostream>
#include <string>


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

    

    /**
     * @brief Base class 
     * 
     */
public:
    HAL() :
        _display(nullptr)
        {}
    virtual ~HAL() {}
    virtual std::string type() { return "Base"; }
    virtual void init() {}
    
    /**
     * @brief Components 
     * 
     */
protected:
    LGFX_Device* _display;
    LGFX_Sprite* _canvas;


    /**
     * @brief Getters 
     * 
     */
public:
    /**
     * @brief Display device 
     * 
     * @return LGFX_Device* 
     */
    static LGFX_Device* GetDisplay() { return Get()->_display; }

    /**
     * @brief Full screen canvas (sprite)
     * 
     * @return LGFX_Sprite* 
     */
    static LGFX_Sprite* GetCanvas() { return Get()->_canvas; }


    /**
     * @brief APIs
     * 
     */
public:
    static void CanvasUpdate() { GetCanvas()->pushSprite(0, 0); }

};

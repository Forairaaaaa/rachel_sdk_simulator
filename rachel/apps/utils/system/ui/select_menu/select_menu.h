/**
 * @file select_menu.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../../smooth_menu/simple_menu/simple_menu.h"


namespace SYSTEM::UI
{
    class SelectMenu
    {
    public:
        struct Config_t
        {
            
        };
        
    private:
        SMOOTH_MENU::Simple_Menu* _menu;

    public:
        SelectMenu();
        ~SelectMenu();
    };
}

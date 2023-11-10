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
#include <iostream>
#include <string>
#include <vector>


namespace SYSTEM::UI
{
    class SelectMenu
    {
    public:
        struct Config_t
        {
            int first_item = 1;
            uint32_t menu_update_interval = 10;
        };
        
    private:
        struct Data_t
        {
            SMOOTH_MENU::Simple_Menu* menu = nullptr;
            SMOOTH_MENU::SimpleMenuCallback_t* render_cb = nullptr;
            uint32_t menu_update_count = 0;
            bool menu_wait_button_released = false;
        };
        Data_t _data;
        Config_t _config;
        

    public:
        SelectMenu(std::vector<std::string>& itemList);
        ~SelectMenu();

        inline Config_t getConfig() { return _config; }
        inline void setConfig(Config_t cfg) { _config = cfg; }

        /**
         * @brief Render the menu and blocked untill item selected 
         * 
         * @return int Selected item index 
         */
        int waitResult();
    };
}

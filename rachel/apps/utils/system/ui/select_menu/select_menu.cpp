/**
 * @file select_menu.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "select_menu.h"
#include "../../../../../hal/hal.h"
#include "components/render_callbacks.h"


using namespace SYSTEM::UI;


SelectMenu::SelectMenu(std::vector<std::string>& itemList)
{
    // Create menu 
    _data.menu = new SMOOTH_MENU::Simple_Menu(HAL::GetCanvas()->width(), HAL::GetCanvas()->height());

    // Load font 
    HAL::LoadLauncherFont24();

    // Push items into menu 
    int text_width = 12;
    int text_height = 24;
    for (int i = 0; i < itemList.size(); i++) 
    {
        _data.menu->getMenu()->addItem(
            itemList[i].c_str(),
            10,
            10 + (text_height + 5) * i,
            text_width * itemList[i].size(),
            text_height
        );
    }

    // Configs 
    _data.menu->setFirstItem(_config.first_item);

    // Set render callback 
    _data.render_cb = new SelectMenuRenderCb_AlignLeft;
    _data.menu->setRenderCallback(_data.render_cb);
}


SelectMenu::~SelectMenu()
{
    delete _data.menu;
    delete _data.render_cb;
}


int SelectMenu::waitResult()
{
    while (1)
    {
        if ((HAL::Millis() - _data.menu_update_count) > _config.menu_update_interval)
        {
            // Update navigation 
            if (HAL::GetButton(GAMEPAD::BTN_UP))
            {
                if (!_data.menu_wait_button_released)
                {
                    _data.menu->goLast();
                    _data.menu_wait_button_released = true;
                }
            }
            else if (HAL::GetButton(GAMEPAD::BTN_DOWN))
            {
                if (!_data.menu_wait_button_released)
                {
                    _data.menu->goNext();
                    _data.menu_wait_button_released = true;
                }
            }

            // If select 
            else if (HAL::GetButton(GAMEPAD::BTN_A))
            {
                _data.menu->getSelector()->pressed();
                // Wait release 
                while (HAL::GetButton(GAMEPAD::BTN_A))
                {
                    _data.menu->update(HAL::Millis());
                    HAL::CanvasUpdate();
                }
                _data.menu->getSelector()->released();

                // Wait anim finish 
                while (!_data.menu->getSelector()->isAnimFinished())
                {
                    _data.menu->update(HAL::Millis());
                    HAL::CanvasUpdate();
                }

                // If not title 
                if (_data.menu->getSelector()->getTargetItem() != 0)
                    return _data.menu->getSelector()->getTargetItem() + 1;
            }

            // Unlock if no button is pressing 
            else
            {
                _data.menu_wait_button_released = false;
            }

            // Render and push frame  
            _data.menu->update(HAL::Millis());
            HAL::CanvasUpdate();

            _data.menu_update_count = HAL::Millis();
        }
        else 
        {
            HAL::Delay(5);
        }
    }
}


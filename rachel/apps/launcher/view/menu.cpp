/**
 * @file menu.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../launcher.h"
#include "lgfx/v1/lgfx_fonts.hpp"
#include "menu_render_callback.hpp"
#include "spdlog/spdlog.h"


using namespace MOONCAKE::APPS;


void Launcher::_create_menu()
{
    spdlog::info("create menu");

    // Create menu and render callback 
    _data.menu = new SMOOTH_MENU::Simple_Menu;
    _data.menu_render_cb = new LauncherRenderCallBack;

    // Init and set render callback 
    _data.menu->init(HAL::GetCanvas()->width(), HAL::GetCanvas()->height());
    _data.menu->setRenderCallback(_data.menu_render_cb);


    // Set selector anim, in this launcher case, is the icon's moving anim (fixed selector)
    auto cfg_selector = _data.menu->getSelector()->config();
    cfg_selector.animPath_x = LVGL::ease_out;
    cfg_selector.animPath_y = LVGL::ease_out;
    cfg_selector.animTime_x = 400;
    cfg_selector.animTime_y = 400;
    _data.menu->getSelector()->config(cfg_selector);

    // Allow selector go loop 
    _data.menu->setMenuLoopMode(true);


    // Get installed app list
    spdlog::info("installed apps num: {}", mcAppGetFramework()->getAppRegister().getInstalledAppNum());
    int i = 0;
    for (const auto& app : mcAppGetFramework()->getAppRegister().getInstalledAppList())
    {
        // Pass the launcher 
        if (app->getAddr() == getAppPacker())
            continue;

        // spdlog::info("app: {} icon: {}", app->getAppName(), app->getAppIcon());
        spdlog::info("push app: {} into menu", app->getAppName());
        
        // Push items into menu, use icon pointer as the item user data
        _data.menu->getMenu()->addItem(
            app->getAppName(),
            THEME_APP_ICON_GAP + i * (THEME_APP_ICON_WIDTH + THEME_APP_ICON_GAP),
            THEME_APP_ICON_MARGIN_TOP,
            THEME_APP_ICON_WIDTH,
            THEME_APP_ICON_HEIGHT,
            app->getAppIcon()
        );
        i++;
    }


    // Setup some widget shit 
    // Pass clock string pointer for redner 
    ((LauncherRenderCallBack*)_data.menu_render_cb)->setClock(&_data.clock);

    // Setup anims
    ((LauncherRenderCallBack*)_data.menu_render_cb)->statusBarAnim.setAnim(LVGL::ease_out, 0, 24, 400);
    ((LauncherRenderCallBack*)_data.menu_render_cb)->statusBarAnim.resetTime(HAL::Millis() + 200);

    ((LauncherRenderCallBack*)_data.menu_render_cb)->bottomPanelAnim.resetTime(HAL::Millis() + 300);
    ((LauncherRenderCallBack*)_data.menu_render_cb)->bottomPanelAnim.setAnim(LVGL::ease_out, 240, 158, 400);
}


void Launcher::_update_menu()
{
    if ((HAL::Millis() - _data.menu_update_count) > _data.menu_update_interval)
    {
        // Update navigation 
        // TODO

        // Update menu
        _data.menu->update(HAL::Millis());

        // Push frame buffer 
        HAL::CanvasUpdate();

        _data.menu_update_count = HAL::Millis();
    }
}


void Launcher::_destroy_menu()
{
    spdlog::info("destroy menu");
    delete _data.menu;
    delete _data.menu_render_cb;
}




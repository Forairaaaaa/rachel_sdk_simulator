/**
 * @file apps.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "launcher/launcher.h"
#include "app_template/app_template.h"
#include "app_settings/app_settings.h"
#include "app_emulator/app_emulator.h"
#include "app_blegamepad/app_blegamepad.h"
/* Header files locator(Don't remove) */


void rachel_app_install_callback(MOONCAKE::Mooncake* mooncake)
{
    mooncake->installApp(new MOONCAKE::APPS::AppSettings_Packer);
    mooncake->installApp(new MOONCAKE::APPS::AppEmulator_Packer);
    mooncake->installApp(new MOONCAKE::APPS::AppBlegamepad_Packer);
    /* Install app locator(Don't remove) */
}

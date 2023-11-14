/**
 * @file app_gbemulator.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include "../assets/icons/icons.h"


namespace MOONCAKE::APPS
{
    /**
    * @brief Gbemulator 
    *
    */
    class AppGb_emulator : public APP_BASE
    {
    public:
        void onCreate() override;
        void onResume() override;
        void onRunning() override;
        void onDestroy() override;
    };

    class AppGb_emulator_Packer : public APP_PACKER_BASE
    {
        std::string getAppName() override { return "GB Emulator"; }
        void* getAppIcon() override { return (void*)image_data_icon_app_default; }
        void* newApp() override { return new AppGb_emulator; }
        void deleteApp(void *app) override { delete (AppGb_emulator*)app; }
    };
}
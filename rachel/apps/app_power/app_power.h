/**
 * @file app_power.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include "assets/icon_app_power.h"


namespace MOONCAKE::APPS
{
    /**
    * @brief Power 
    *
    */
    class AppPower : public APP_BASE
    {
    private:
        struct Data_t
        {
            unsigned long count = 0;
        };
        Data_t _data;

    public:
        void onCreate() override;
        void onResume() override;
        void onRunning() override;
        void onDestroy() override;
    };

    class AppPower_Packer : public APP_PACKER_BASE
    {
        std::string getAppName() override { return "电源"; }
        void * getAppIcon() override { return (void*)image_data_icon_app_power; }
        void *newApp() override { return new AppPower; }
        void deleteApp(void *app) override { delete (AppPower*)app; }
    };
}
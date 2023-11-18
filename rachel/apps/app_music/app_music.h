/**
 * @file app_music.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <mooncake.h>
#include "assets/icon_app_music.hpp"


namespace MOONCAKE::APPS
{
    /**
    * @brief Music 
    *
    */
    class AppMusic : public APP_BASE
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

    class AppMusic_Packer : public APP_PACKER_BASE
    {
        std::string getAppName() override { return "Music"; }
        void* getAppIcon() override { return (void*)image_data_icon_app_music; }
        void* newApp() override { return new AppMusic; }
        void deleteApp(void *app) override { delete (AppMusic*)app; }
    };
}
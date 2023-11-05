/**
 * @file launcher.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <mooncake.h>
#include <string>


namespace MOONCAKE
{
    namespace APPS
    {
        /**
        * @brief Launcher
        *
        */
        class Launcher : public APP_BASE
        {
        private:
            struct Data_t
            {
                std::string clock;
            };
            Data_t _data;
            void _update_clock();
            void _create_menu();
            void _update_menu();
            void _destroy_menu();

        public:
            void onCreate() override;
            void onResume() override;
            void onRunning() override;
            void onRunningBG() override;
            void onDestroy() override;
        };

        class Launcher_Packer : public APP_PACKER_BASE
        {
            std::string getAppName() override { return "Launcher"; }
            void *newApp() override { return new Launcher; }
            void deleteApp(void *app) override { delete (Launcher*)app; }
        };
    }
}

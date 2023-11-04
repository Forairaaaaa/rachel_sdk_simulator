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
                
            };
            Data_t _data;

        public:
            void onCreate() override;
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

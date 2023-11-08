/**
 * @file simple_menu.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-06-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../camera/camera.h"


namespace SMOOTH_MENU {


    class SimpleMenuCallback_t {
        public:
            virtual void renderCallback(
                const std::vector<Item_t*>& menuItemList,
                const RenderAttribute_t& selector,
                const RenderAttribute_t& camera
            ) { }
    };


    class Simple_Menu {
        private:
            Menu_t* _menu;
            Selector_t* _selector;
            Camrea_t* _camera;
            SimpleMenuCallback_t* _render_callback;
            bool _first_open;

        
        public:
            Simple_Menu() :
                _menu(nullptr),
                _selector(nullptr),
                _camera(nullptr),
                _render_callback(nullptr),
                _first_open(true)
                { }
            ~Simple_Menu() = default;


            inline Menu_t* getMenu() { return _menu; }
            inline Selector_t* getSelector() { return _selector; }
            inline Camrea_t* getCamera() { return _camera; }


            /**
             * @brief Set menu go back when hit limit
             * 
             * @param loopMode 
             */
            void setMenuLoopMode(bool loopMode);


            /**
             * @brief Init menu
             * 
             * @param cameraWidth 
             * @param cameraHeight 
             */
            inline void init(int cameraWidth, int cameraHeight)
            {
                init();
                getCamera()->setSize(cameraWidth, cameraHeight);
            }
            
            void init(Menu_t* menu = nullptr, Selector_t* selector = nullptr, Camrea_t* camera = nullptr);
            

            /**
             * @brief Set the Render Callback function, for your graphics lib
             * 
             * @param callback 
             */
            inline void setRenderCallback(SimpleMenuCallback_t* callback) { _render_callback = callback; }


            /**
             * @brief Uptate menu
             * 
             * @param currentTime 
             * @param renderAtOnce 
             */
            void update(uint32_t currentTime, bool renderAtOnce = true);


            /**
             * @brief Go to last item
             * 
             */
            void goLast();


            /**
             * @brief Go to next item
             * 
             */
            void goNext();


            /**
             * @brief Render at once
             * 
             */
            void render();

    };


}


# See how to install sdl2: https://wiki.libsdl.org/SDL2/Installation
cmake_minimum_required (VERSION 3.8)
project(LGFX_SDL)

add_definitions(-DLGFX_SDL)

# ビルド対象にするファイルを指定する;
# LovyanGFXのあるパスと位置関係を変えた場合は相対パス記述を環境に合わせて調整すること;
file(GLOB Target_Files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS 
    *.cpp
    Lib/LovyanGFX/src/lgfx/Fonts/efont/*.c
    Lib/LovyanGFX/src/lgfx/Fonts/IPA/*.c
    Lib/LovyanGFX/src/lgfx/utility/*.c
    Lib/LovyanGFX/src/lgfx/v1/*.cpp
    Lib/LovyanGFX/src/lgfx/v1/misc/*.cpp
    Lib/LovyanGFX/src/lgfx/v1/panel/Panel_Device.cpp
    Lib/LovyanGFX/src/lgfx/v1/panel/Panel_FrameBufferBase.cpp
    Lib/LovyanGFX/src/lgfx/v1/platforms/sdl/*.cpp
)

# Rachel
file(GLOB_RECURSE RACHELE_SRCS
    rachel/apps/*.c
    rachel/apps/*.cpp
    rachel/hal/hal_simulator/*.c
    rachel/hal/hal_simulator/*.cpp
)
set(RACHELE_SRCS_EXTRA
    rachel/rachel.cpp
    rachel/hal/hal.cpp
    rachel/hal/lgfx_fx/lgfx_fx.cpp
)
# Nofrendo
set(NOFRENDO_INCS
    rachel/apps/app_nofrendo/nofrendo
    rachel/apps/app_nofrendo/nofrendo/cpu
    rachel/apps/app_nofrendo/nofrendo/libsnss
    rachel/apps/app_nofrendo/nofrendo/mappers
    rachel/apps/app_nofrendo/nofrendo/nes
    rachel/apps/app_nofrendo/nofrendo/sndhrdw
)

add_executable (LGFX_SDL ${Target_Files} ${RACHELE_SRCS} ${RACHELE_SRCS_EXTRA})

# includeするファイルのパスを指定する;
# LovyanGFXのあるパスと位置関係を変えた場合は相対パス記述を環境に合わせて調整すること;
target_include_directories(LGFX_SDL PUBLIC "Lib/LovyanGFX/src/" ${NOFRENDO_INCS})


# Mooncake 
add_subdirectory("Lib/mooncake")


IF (CMAKE_SYSTEM_NAME MATCHES "Linux")

# Linux環境の場合;
# SDL2_INCLUDE_DIRS と SDL2_LIBRARIES を事前に設定しておく;
    find_package(SDL2 REQUIRED SDL2)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(LGFX_SDL -lpthread ${SDL2_LIBRARIES} mooncake)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")

# Windows環境の場合;
# SDL2を配置したパス内のincludeのパスを指定する;
    target_include_directories(LGFX_SDL PUBLIC "C:/SDL2/include")

# SDL2を配置したパス内の.libファイルのパスを指定する;
    target_link_libraries(LGFX_SDL PUBLIC "C:/SDL2/lib/x64/SDL2.lib" mooncake)


    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>")

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")

# MacOS(Darwin)環境の場合;
    find_package(SDL2 REQUIRED COMPONENTS SDL2)
    target_link_libraries(LGFX_SDL PRIVATE SDL2::SDL2)

ENDIF ()

target_compile_features(LGFX_SDL PUBLIC cxx_std_17)

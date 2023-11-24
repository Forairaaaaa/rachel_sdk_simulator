# Rachel SDK simulator
SDk simulator of project Rachel
## Usage

### Get submodules

```
./fetch_submodules.sh
```

### Install SDL
You can download SDL from https://www.libsdl.org/

On on Linux you can install it via terminal:
```
sudo apt-get update && sudo apt-get install -y build-essential libsdl2-dev
```

### Build and run 

```
mkdir build && cd build
```

```
cmake .. && make
```

```
./LGFX_SDL
```



# 编译

`RachelSDK` 为 `PIO` 工程， `VS Code` 下载 `PlatformIO` 插件，用 `VS Code` 打开文件夹即可



# SDK 目录树

```shell
.
├── apps
│   ├── app_ble_gamepad               BLE 手柄
│   ├── app_music                     音乐播放器
│   ├── app_nofrendo                  NES 模拟器
│   ├── app_raylib_games              Raylib 游戏
│   ├── app_screencast                WiFi 投屏
│   ├── app_settings                  设置
│   ├── app_genshin                   __,__!
│   ├── app_template                  App 模板
│   ├── launcher                      启动器
│   ├── utils                         通用组件库
│   ├── assets                        公共资源
│   ├── tools                         App 相关工具(脚本)
│   └── apps.h                        App 安装回调
├── hal
│   ├── hal.cpp                       HAL 基类
│   ├── hal.h                         HAL 基类
│   ├── hal_rachel                    HAL Rachel 派生类
│   ├── hal_simulator                 HAL PC 模拟器派生类
│   └── lgfx_fx                       lgfx 派生类(拓展图形API)
├── rachel.cpp
└── rachel.h                          RachelSDK 入口
```



# SD 卡目录树

NES 模拟器、音乐播放器等会尝试加载SD卡里指定目录的资源文件

```
.
├── buzz_music                        蜂鸣器音乐
│   ├── harrypotter.json
│   ├── nokia.json
│   ...
├── fonts                             字体
│   └── font_text_24.vlw
└── nes_roms                          NES ROM 文件
    ├── Kirby's Adventure (E).nes
    ├── Snow Bros (U).nes
	...
```

`font_text_24.vlw` 这个字体我用的是 [Zpix](https://github.com/SolidZORO/zpix-pixel-font)很嗨好看，可以替换任何自己喜欢的

`NES ROM` 直接丢进去就行，不是很大的应该都能玩



# SDK 结构

![](https://github.com/Forairaaaaa/rachel_sdk_simulator/blob/main/pics/sdk_layers.jpg)



# 创建 App

##### 写了个 `python` 脚本用来简化 App 创建：

```shell
python3 ./src/rachel/apps/tools/app_generator.py
```

​	$ Rachel app generator > <

​	$ app name:

```
hello_world
```

​	$ file names:

​	$ - ../app_hello_world/app_hello_world.cpp

​	$ - ../app_hello_world/app_hello_world.h

​	$ app class name: AppHello_world

​	$ install app hello_world

​	$ done

##### App 就创建好了, 重新编译上传：

![](https://github.com/Forairaaaaa/rachel_sdk_simulator/blob/main/pics/create_app.jpg)

##### 新创建的 App 基本模板如下，详细的生命周期和API可以参考 [Mooncake](https://github.com/Forairaaaaa/mooncake) 项目

```cpp
// Like setup()...
void AppTemplate::onResume()
{
    spdlog::info("{} 启动", getAppName());
}


// Like loop()...
void AppTemplate::onRunning()
{    
    spdlog::info("咩啊");
    HAL::Delay(1000);

    _data.count++;
    if (_data.count > 5)
        destroyApp();
}
```

`Mooncake` 框架内部集成了 [spdlog](https://github.com/gabime/spdlog) 日志库，当然你也可以继续用 `cout`, `printf`, `Serial`...

##### 手动创建

- 复制 `src/rachel/apps/app_template` 到同一目录并重命名： `src/rachel/apps/app_hello_world`
- 将里面的 `app_template.cpp` 和 `app_template.h` 重命名为 `app_hello_world.cpp` 和 `app_hello_world.h` 
- 打开  `app_hello_world.cpp` 和 `app_hello_world.h` ，将里面的所有 `AppTemplate` 替换成 `AppHello_world`
- 打开 `src/rachel/apps/apps.h`
- 添加 `#include "app_hello_world/app_hello_world.h"` 
- 添加 `mooncake->installApp(new MOONCAKE::APPS::AppHello_world_Packer);`
- 编译上传

### 常用的  App  API

##### destroyApp()

关闭 App，调用后会告诉框架你不玩了，框架会把你的 App 销毁释放，所以在 `onRunning()` 被阻塞的情况下是无效的

```cpp
// 有效
void AppTemplate::onRunning()
{
    destroyApp();
}

// 无效
void AppTemplate::onRunning()
{    
    destroyApp();
    HAL::Delay(66666666666);
}
```

##### getAppName()

获取 App 名字，会返回你设置的 App 名字

```cpp
// 你的 App 头文件里:
class AppHello_world_Packer : public APP_PACKER_BASE
{
    // 这里修改你的 App 名字:
    std::string getAppName() override { return "文明讲礼外乡人"; }
    ...
}
```

##### getAppIcon()

获取 App 图标，启动器在渲染画面时会调用

```cpp
// 你的 App 头文件里:
class AppHello_world_Packer : public APP_PACKER_BASE
{
    ...
    // 这里修改你的 App 图标(有默认图标)
    void* getAppIcon() override { return (void*)image_data_icon_app_default; }
    ...
}
```

##### mcAppGetDatabase()

获取数据库实例，是一个简单的 `RAM` 上 `KV` 数据库，可以用于 App 退出数据保存、多 App 间的数据共享(当然断电没)，详细用法参考[这里](https://github.com/Forairaaaaa/mooncake/blob/main/example/framework/simplekv_test.cpp)

```cpp
void AppTemplate::onResume()
{
    // 看看数据库里有没有这个 key
    if (mcAppGetDatabase()->Exist("开了?"))
    {
        // 数据库里拿出来, 看看开了几次
        int how_many = mcAppGetDatabase()->Get("开了?")->value<int>();
        spdlog::info("开了 {} 次", how_many);
		
        // 加上这一次, 写进数据库
        how_many++;
        mcAppGetDatabase()->Put<int>("开了?", how_many);
    }
    // 没有就创建一个
    else
        mcAppGetDatabase()->Add<int>("开了?", 1);
}
```

##### mcAppGetFramework()

获取 `Mooncake` 框架实例，一般用来写启动器.. 比如[这里](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/apps/launcher/view/menu.cpp#L57).

```cpp
// 看看安装了几个 App
auto installed_app_num = mcAppGetFramework()->getAppRegister().getInstalledAppNum();
spdlog::info("安装了 {} 个 App", installed_app_num);

// 看看他们都叫什么
for (const auto& app_packer : mcAppGetFramework()->getAppRegister().getInstalledAppList())
{
    spdlog::info("{}", app_packer->getAppName());
}
```



# HAL 硬件抽象层

![](https://github.com/Forairaaaaa/rachel_sdk_simulator/blob/main/pics/hal_uml.jpg)

HAL为**单例**模式，SDK初始化时会[注入](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/rachel.cpp#L34)一个HAL实例. 

- 对于 `HAL Rachel` ，按住 `按键A` 开机，会暂停在初始化界面，可以查看详细的HAL初始化log
- 如果有不同底层硬件需求，只需派生新的[HAL](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/hal/hal.h#L84)对象，重写 API 方法 (override) 并在初始化时注入即可

### Include

```cpp
#include "{path to}/hal/hal.h"
```

### 显示 API

```cpp
// 获取屏幕驱动实例
HAL::GetDisplay();

// 获取全屏Buffer实例
HAL::GetCanvas();

// 推送全屏buffer到显示屏
HAL::CanvasUpdate();

// 渲染FPS面板
HA::RenderFpsPanel();
```

显示驱动使用 [LovyanGFX](https://github.com/lovyan03/LovyanGFX)，详细的图形API可以参考原项目[示例](https://github.com/lovyan03/LovyanGFX/tree/master/examples/HowToUse)

### 系统 API

```cpp
// 延时(毫秒)
HAL::Delay(unsigned long milliseconds);

// 获取系统运行毫秒数
HAL::Millis();

// 关机
HAL::PowerOff();

// 重启
HAL::Reboot();

// 设置RTC时间
HAL::SetSystemTime(tm dateTime);

// 获取当前时间
HAL::GetLocalTime();

// 优雅地抛个蓝屏
HAL::PopFatalError(std::string msg);
```

`HAL Rachel` 在初始化时会以RTC时间[调整系统时间](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/hal/hal_rachel/components/hal_rtc.cpp#L70)，所以时间相关的`POSIX标准`API都可以正常使用

### 外设 API

```cpp
// 刷新IMU数据
HAL::UpdateImuData();

// 获取IMU数据
HAL::GetImuData();

// 蜂鸣器开始哔哔
HAL::Beep(float frequency, uint32_t duration);

// 蜂鸣器别叫了
HAL::BeepStop();

// 检查SD卡是否可用
HAL::CheckSdCard();

// 获取按键状态
HAL::GetButton(GAMEPAD::GamePadButton_t button);

// 获取任意按键状态
HAL::GetAnyButton();
```

### 系统配置 API

```cpp
// 从内部FS导入系统配置
HAL::LoadSystemConfig();

// 保存系统配置到内部FS
HAL::SaveSystemConfig();

// 获取系统配置
HAL::GetSystemConfig();

// 设置系统配置
HAL::SetSystemConfig(CONFIG::SystemConfig_t cfg);

// 以系统配置刷新设备
HAL::UpdateSystemFromConfig();
```





# 通用组件库

一些比较有用的通用封装库放在了这里  `rachel/apps/utils/system`

## 选择菜单

![](https://github.com/Forairaaaaa/rachel_sdk_simulator/blob/main/pics/select_menu.jpg)

创建一个选择菜单

#### Include

```cpp
#include "{path to}/utils/system/ui/ui.h"
```

#### Example

```cpp
using namespace SYSTEM::UI;

// 创建选择菜单
auto select_menu = SelectMenu();

// 创建选项列表
std::vector<std::string> items = {
    "[WHAT 7 TO PLAY]",
    "Jenshin Import",
    "Light Soul",
    "Grand Cop Manual",
    "Super Maliao",
    "Quit"
};

// 等待选择
auto selected_index = select_menu.waitResult(items);
spdlog::info("selected: {}", items[selected_index]);
```



## 进度条窗口

![](https://github.com/Forairaaaaa/rachel_sdk_simulator/blob/main/pics/progress_window.jpg)

创建一个带有进度条的窗口（u1s1, 现在应该算是页面）

#### Include

```cpp
#include "{path to}/utils/system/ui/ui.h"
```

#### Example

```cpp
using namespace SYSTEM::UI;

for (int i = 0; i < 100; i++)
{
    ProgressWindow("正在检测智商..", i);
    HAL::CanvasUpdate();
    HAL::Delay(20);
}
```



## 蜂鸣器音乐播放器

参考 [arduino-songs](https://github.com/robsoncouto/arduino-songs) 的 json 格式蜂鸣器音乐播放器，[json 格式音乐示例](https://github.com/Forairaaaaa/rachel_sdk_simulator/blob/main/rachel/apps/app_music/assets/buzz_music/nokia.json)

#### Include

```cpp
#include "{path to}/utils/system/audio/audio.h"
```

#### Example

```cpp
using namespace SYSTEM::AUDIO;

// 播放SD路径上的json音乐文件
BuzzMusicPlayer::playFromSdCard("/buzz_music/nokia.json");
```



## 按钮

参考 [Button](https://github.com/madleech/Button) 的按键库

#### Include

```cpp
#include "{path to}/utils/system/inputs/inputs.h"
```

#### Example

```cpp
using namespace SYSTEM::INPUTS;

auto button_a = Button(GAMEPAD::BTN_A);

while (1)
{
    if (button_a.pressed())
        spdlog::info("button a was pressed");
    if (button_a.released())
        spdlog::info("button a was released");
    if (button_a.toggled())
        spdlog::info("button a was toggled");
    HAL::Delay(20);
}
```



# 深入

更深入些的具体框架和实现，睡不着可以看看

## HAL Rachel

`HAL Rachel` 派生自 `HAL`，提供了 `HAL` 中的 `API` 在 `arduino-esp32` 上的具体实现

#### 目录树

```shell
.
├── components                        各外设的初始化和 API 实现
│   ├── hal_display.cpp
│   ├── hal_fs.cpp
│   ├── hal_gamepad.cpp
│   ├── hal_i2c.cpp
│   ├── hal_imu.cpp
│   ├── hal_power.cpp
│   ├── hal_rtc.cpp
│   ├── hal_sdcard.cpp
│   └── hal_speaker.cpp
├── hal_config.h                      引脚定义, 内部 log 定义等
├── hal_rachel.h                      类声明
└── utils
    └── m5unified                     非常好用的一些 ESP32 外设抽象
```

#### 初始化流程

`HAL` 在被[注入](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/hal/hal.cpp#L44)时会调用 `init()` ，`HAL Rachel` 重写的 [init()](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/hal/hal_rachel/hal_rachel.h#L61) 即为初始化流程：

```cpp
inline void init() override
{
    _power_init();                    电源管理初始化
    _disp_init();                     显示屏初始化
    _gamepad_init();                  手柄按键初始化
    _spk_init();                      扬声器(蜂鸣器)初始化
    _i2c_init();                      I2C 初始化
    _rtc_init();                      RTC 初始化
    _imu_init();                      IMU 初始化
    _fs_init();                       内部 Flash 文件系统初始化
    _sdcard_init();                   SD 卡文件系统初始化
    _system_config_init();            系统配置初始化
    _sum_up();                        总结
}
```

- 内部 Flash 文件系统使用 `LittleFS` ，目前只是用于系统设置的保存, 所以[分区](https://github.com/Forairaaaaa/RachelSDK/blob/main/custom.csv#L7C27-L7C34)只给了 256 kB
- `loadTextFont24()` 这个 API 的设计目的是用于更好看的(支持中文)文本显示需求，[实现方式](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/hal/hal_rachel/components/hal_sdcard.cpp#L40)是从SD卡读取 `vlw` 字体，所以使用这个字体后，渲染画面耗时会变长
- 当然有很多方法可以让上面这个API也适用于快速刷新的画面，不过对我来说这个[自带字体](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/hal/hal_rachel/components/hal_sdcard.cpp#L63)够用了，启动器和选择菜单都是用的这个
- RTC 和 IMU 这两个外设都可以在 [M5Unified](https://github.com/m5stack/M5Unified) 这个库中找到现成好用的驱动和抽象，我只是从其中抽离出来根据需求做对接

## HAL Simulator

因为 [LovyanGFX](https://github.com/lovyan03/LovyanGFX/tree/master/examples_for_PC/CMake_SDL) 支持 SDL 作显示后端，因此要实现一个 PC 上的 HAL 实现基本什么都不用做（确信），一个[头文件](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/hal/hal_simulator/hal_simulator.hpp)搞定。RachelSDK 的模拟器工程在[这里](https://github.com/Forairaaaaa/rachel_sdk_simulator)

## RachelSDK 初始化流程

有 HAL 把底层抽象架空，剩下的都是 C++ 自由发挥了（当然有些 App 还是直接用了平台特定 API, 比如 NES 模拟器用了 ESP32 的分区读写 API, 如果这些都给做上抽象就太浪费时间了~, 条件编译隔开就好, 不妨碍整体框架的通用性）

RachelSDK 的初始化在[这里](https://github.com/Forairaaaaa/rachel_sdk_simulator/blob/main/rachel/rachel.cpp#L26)，具体如下：

```cpp
...

// 根据平台注入具体 HAL 实现
#ifndef ESP_PLATFORM
HAL::Inject(new HAL_Simulator);
#else
HAL::Inject(new HAL_Rachel);
#endif

// 初始化 Mooncake 调度框架
_mooncake = new Mooncake;
_mooncake->init();

// 安装启动器 (嗯，启动器也是 App )
auto launcher = new APPS::Launcher_Packer;
_mooncake->installApp(launcher);

// 安装其他 App (设置、模拟器...)
rachel_app_install_callback(_mooncake);

// 启动启动器
_mooncake->createApp(launcher);

...
```

初始化完后, 由 [Mooncake](https://github.com/Forairaaaaa/mooncake) 框架接管，完成各个 App 的各个生命周期的调度

## App Launcher

启动器，由 SDK 启动的第一个 App，用来启动别的 App（？）

#### 目录树

```shell
.
├── assets                            静态资源
│   └── launcher_bottom_panel.hpp
├── launcher.cpp                      App Launcher 实现
├── launcher.h                        App Launcher 声明
└── view
    ├── app_anim.cpp                  App 打开关闭动画
    ├── menu.cpp                      启动器菜单
    └── menu_render_callback.hpp      启动器菜单渲染回调
```

打开 [launcher.cpp](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/apps/launcher/launcher.cpp)，从各个生命周期看起：

`onCreate` ，这个地方只会在启动器被[创建](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/rachel.cpp#L49)时调用一次，所以负责自己属性的配置和资源申请等：

```cpp
void Launcher::onCreate()
{
    ...
        
    // 允许后台运行
    setAllowBgRunning(true);
    // 使能在创建后自动启动
    startApp();
    
    // 创建菜单(这个菜单就是安装了的 App 的列表的抽象, 后面渲染部分会详细讲)
    _create_menu();
}
```
`onResume` 会在启动器刚创建，或者从后台切到前台时被调用，所以放一些渲染前的准备，控件信息刷新..

```cpp
void Launcher::onResume()
{
    ...

    // 切字体..
    HAL::LoadLauncherFont24();
    HAL::GetCanvas()->setTextScroll(false);
    
    // 更新状态栏的时间文本
    _update_clock(true);
}
```


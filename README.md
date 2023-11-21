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





## SDK目录树

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



## SD卡目录树

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

`font_text_24.vlw` 这个字体我用的是 [Zpix](https://github.com/SolidZORO/zpix-pixel-font) , 很嗨好看, 可以替换任何自己喜欢的.

`NES ROM` 直接丢进去就行, 不是很大的应该都能玩.





## 创建App

##### 写了个 python 脚本用来简化 App 创建: 

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

##### App 就创建好了, 重新编译上传:

![](https://github.com/Forairaaaaa/rachel_sdk_simulator/blob/main/pics/create_app.jpg)

##### 新创建的 App 基本模板如下, 详细的生命周期和API可以参考 [Mooncake](https://github.com/Forairaaaaa/mooncake) 项目

```cpp
// Like setup()...
void AppTemplate::onResume()
{
    spdlog::info("{} onResume", getAppName());

    _quit_count = 0;
}


// Like loop()...
void AppTemplate::onRunning()
{    
    spdlog::info("咩啊");
    HAL::Delay(1000);

    _quit_count++;
    if (_quit_count > 5)
        destroyApp();
}
```

Mooncake 框架内部集成了 [spdlog](https://github.com/gabime/spdlog) 日志库, 当然你也可以继续用 std::cout, printf, Serial...





## HAL硬件抽象层

![](https://github.com/Forairaaaaa/rachel_sdk_simulator/blob/main/pics/hal_uml.jpg)

HAL为**单例**模式，SDK初始化时会[注入](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/rachel.cpp#L34)一个HAL实例. 

- 对于 `HAL Rachel` , 按住按键A开机, 会暂停在初始化界面, 可以查看详细HAL初始化log.
- 如果有不同底层硬件需求, 只需派生新的[HAL](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/hal/hal.h#L84)对象, override 虚函数并在初始化时注入即可.

### Include

```cpp
#include "{path to}/hal/hal.h"
```

### 显示API

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

显示驱动使用 [LovyanGFX](https://github.com/lovyan03/LovyanGFX), 详细的图形API可以参考原项目[示例](https://github.com/lovyan03/LovyanGFX/tree/master/examples/HowToUse)

### 系统API

```cpp
// 延时(毫秒)
HAL::Delay(unsigned long milliseconds);

// 获取系统运行毫秒数
HAL::Millis();

// 关机
HAL::PowerOff();

// 重启
HAL::Reboot();

// 获取当前时间
HAL::SetSystemTime(tm dateTime);

// 获取当前时间
HAL::GetLocalTime();

// 优雅地抛个蓝屏
HAL::PopFatalError(std::string msg);
```

HAL_Rachel 在初始化时会以RTC时间[调整系统时间](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/hal/hal_rachel/components/hal_rtc.cpp#L70), 所以关于时间的POSIX标准API都可以正常使用

### 外设API

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

### 系统配置API

```cpp
// 从内部FS导入系统配置
HAL::LoadSystemConfig();

// 保存系统配置到内部FS
HAL::SaveSystemConfig();

// 获取系统配置, Get the System Config 
HAL::GetSystemConfig();

// 设置系统配置, Set the System Config 
HAL::SetSystemConfig(CONFIG::SystemConfig_t cfg);

// 以系统配置刷新设备, Update device to the system config 
HAL::UpdateSystemFromConfig();
```





## 通用组件库

一些比较有用的通用封装库放在了这里  `rachel/apps/utils/system`

### 选择菜单

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



### 进度条窗口

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



### 蜂鸣器音乐播放器

参考 [arduino-songs](https://github.com/robsoncouto/arduino-songs) 的 **json** 格式蜂鸣器音乐播放器, [json 格式音乐示例](https://github.com/Forairaaaaa/rachel_sdk_simulator/blob/main/rachel/apps/app_music/assets/buzz_music/nokia.json).

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



### 按钮

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




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



## 创建App, Create an App

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



## 硬件抽象层API, HAL API

HAL为**单例**模式，[当SDK初始化时被注入](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/rachel.cpp#L34). 

如有不同底层硬件需求, 只需派生新的[HAL](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/hal/hal.h#L84)对象, 改写虚函数并在初始化时注入即可.

HAL is a **singleton**, [injected during SDK's init](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/rachel.cpp#L34). 

### Include

```cpp
#include "{path to}/hal/hal.h"
```

### 显示API, Display API

```cpp
// 获取屏幕驱动实例, Get display device
HAL::GetDisplay();

// 获取全屏Buffer实例, Get full screen canvas (sprite)
HAL::GetCanvas();

// 推送全屏buffer到显示屏, Push framebuffer
HAL::CanvasUpdate();

// 渲染FPS面板, Render fps panel
HA::RenderFpsPanel();
```

显示驱动使用 [LovyanGFX](https://github.com/lovyan03/LovyanGFX), 详细的图形API可以参考原项目[示例](https://github.com/lovyan03/LovyanGFX/tree/master/examples/HowToUse)

### 系统API, System API

```cpp
// 延时(毫秒), Delay(ms)
HAL::Delay(unsigned long milliseconds);

// 获取系统运行毫秒数, Get the number of milliseconds passed since boot 
HAL::Millis();

// 关机, Power off
HAL::PowerOff();

// 重启, Reboot
HAL::Reboot();

// 获取当前时间, Get local time(wrap of localtime())
HAL::SetSystemTime(tm dateTime);

// 获取当前时间, Get local time(wrap of localtime())
HAL::GetLocalTime();

// 优雅地抛个蓝屏, Pop error message and wait reboot
HAL::PopFatalError(std::string msg);
```

HAL_Rachel 在初始化时会以RTC时间[调整系统时间](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/hal/hal_rachel/components/hal_rtc.cpp#L70), 所以关于时间的POSIX标准API都可以正常使用

### 外设API, Peripheral API

```cpp
// 刷新IMU数据, Update IMU data
HAL::UpdateImuData();

// 获取IMU数据, Get the Imu Data
HAL::GetImuData();

// 蜂鸣器开始哔哔, Buzzer beep
HAL::Beep(float frequency, uint32_t duration);

// 蜂鸣器别叫了, Stop buzzer beep
HAL::BeepStop();

// 检查SD卡是否可用, Check if sd card is valid
HAL::CheckSdCard();

// 获取按键状态, Get button state 
HAL::GetButton(GAMEPAD::GamePadButton_t button);

// 获取任意按键状态, Get any button state
HAL::GetAnyButton();
```

### 系统配置API, System config API

```cpp
// 从内部FS导入系统配置, Load system config from FS 
HAL::LoadSystemConfig();

// 保存系统配置到内部FS, Save system config to FS 
HAL::SaveSystemConfig();

// 获取系统配置, Get the System Config 
HAL::GetSystemConfig();

// 设置系统配置, Set the System Config 
HAL::SetSystemConfig(CONFIG::SystemConfig_t cfg);

// 以系统配置刷新设备, Update device to the system config 
HAL::UpdateSystemFromConfig();
```



## 通用组件库, System utils

一些比较有用的通用封装库放在了这里  `rachel/apps/utils/system`

Useful utilities (hal api based) are integrated in `rachel/apps/utils/system`



### 选择菜单, Select menu

创建一个[选择菜单](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/apps/utils/system/ui/select_menu/select_menu.h).

Create a [select menu](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/apps/utils/system/ui/select_menu/select_menu.h).

#### Include

```cpp
#include "{path to}/utils/system/ui/ui.h"
```

#### Example

```cpp
using namespace SYSTEM::UI;

// 创建选择菜单, Create a select menu 
auto select_menu = SelectMenu();

// 创建选项列表, Create item list 
std::vector<std::string> items = {
    "[WHAT 7 TO PLAY]",
    "Jenshin Import",
    "Light Soul",
    "Grand Cop Manual",
    "Super Maliao",
    "Quit"
};

// 等待选择, Wait select result  
auto selected_index = select_menu.waitResult(items);
spdlog::info("selected: {}", items[selected_index]);
```

![](https://github.com/Forairaaaaa/rachel_sdk_simulator/blob/main/pics/select_menu.jpg)



### 进度条窗口, Progress  window

创建一个带有[进度条的窗口](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/apps/utils/system/ui/select_menu/select_menu.h).（u1s1, 现在应该算是页面）

Create [window with progress bar](https://github.com/Forairaaaaa/RachelSDK/blob/main/src/rachel/apps/utils/system/ui/select_menu/select_menu.h).

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

![](https://github.com/Forairaaaaa/rachel_sdk_simulator/blob/main/pics/progress_window.jpg)



### 蜂鸣器音乐播放器, Buzz music player

参考 [arduino-songs](https://github.com/robsoncouto/arduino-songs) 的 **json** 格式蜂鸣器音乐播放器, [json 格式音乐示例](https://github.com/Forairaaaaa/rachel_sdk_simulator/blob/main/rachel/apps/app_music/assets/buzz_music/nokia.json).

A **json** buzz music file player refs to [arduino-songs](https://github.com/robsoncouto/arduino-songs), [json music file example](https://github.com/Forairaaaaa/rachel_sdk_simulator/blob/main/rachel/apps/app_music/assets/buzz_music/nokia.json).

#### Include

```cpp
#include "{path to}/utils/system/audio/audio.h"
```

#### Example

```cpp
using namespace SYSTEM::AUDIO;

// 播放SD路径上的json音乐文件, Play the music json file store in SD card 
BuzzMusicPlayer::playFromSdCard("/buzz_music/nokia.json");
```



### 按钮, Button

参考 [Button](https://github.com/madleech/Button) 的按键库

Button lib refs to  [Button](https://github.com/madleech/Button)

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




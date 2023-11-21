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



## Create an App





## HAL APIs

HAL is a singleton, injected during SDK's init.

HAL为单例模式, SDK初始化时注入.

### Include

```cpp
#include "{path to}/hal/hal.h"
```

### Display APIs

```cpp
HAL::GetDisplay()		// Get display device, 获取屏幕驱动实例
HAL::GetCanvas()		// Get full screen canvas (sprite), 获取全屏Buffer实例
HAL::CanvasUpdate()		// Push framebuffer, 推送全屏buffer到显示屏 
HA::RenderFpsPanel()	// Render fps panel, 渲染FPS面板 
```

### System APIs

```cpp
HAL::Delay(unsigned long milliseconds)	// Delay(ms), 延时(毫秒)
HAL::Millis() 			// Get the number of milliseconds passed since boot, 获取系统运行毫秒数
HAL::PowerOff()			// Power off, 关机
HAL::Reboot()			// Reboot, 重启 
HAL::SetSystemTime(tm dateTime)	// Get local time(wrap of localtime()), 获取当前时间
HAL::GetLocalTime()		// Get local time(wrap of localtime()), 获取当前时间
HAL::PopFatalError(std::string msg)	// Pop error message and wait reboot, 优雅地抛个蓝屏 
```

### Peripheral APIs

```cpp
HAL::UpdateImuData()	// Update IMU data, 刷新IMU数据
HAL::GetImuData()		// Get the Imu Data, 获取IMU数据
HAL::Beep(float frequency, uint32_t duration)	// Buzzer beep, 蜂鸣器开始哔哔
HAL::BeepStop()			// Stop buzzer beep, 蜂鸣器别叫了 
HAL::CheckSdCard()		// Check if sd card is valid, 检查SD卡是否可用
HAL::GetButton(GAMEPAD::GamePadButton_t button)	// Get button state, 获取按键状态 
HAL::GetAnyButton()		// Get any button state, 获取任意按键状态 
```

### System config APIs

```cpp
HAL::LoadSystemConfig()	// Load system config from FS, 从内部FS导入系统配置 
HAL::SaveSystemConfig()	// Save system config to FS, 保存系统配置到内部FS
HAL::GetSystemConfig()	// Get the System Config, 获取系统配置 
HAL::SetSystemConfig(CONFIG::SystemConfig_t cfg)	// Set the System Config, 设置系统配置 
HAL::UpdateSystemFromConfig()	// Update device to the system config, 以系统配置刷新设备
```



## System utils

Useful utilities (hal api based) are integrated in `rachel/apps/utils/system`

一些比较有用的HAL封装放在了这里  `rachel/apps/utils/system`



### Select menu

Create a menu for selecting.

创建一个选择菜单.

### Include

```cpp
#include "{path to}/utils/system/ui/ui.h"
```

### Example

```cpp
using namespace SYSTEM::UI;

// Create a select menu, 创建选择菜单 
auto select_menu = SelectMenu();

// Create item list, 创建选项列表 
std::vector<std::string> items = {
    "[WHAT 7 TO PLAY]",
    "Jenshin Import",
    "Light Soul",
    "Grand Cop Manual",
    "Super Maliao",
    "Quit"
};

// Wait select result, 等待选择 
auto selected_index = select_menu.waitResult(items);
spdlog::info("selected: {}", items[selected_index]);
```



### Progress  window

Create window with progress bar.

创建一个带有进度条的窗口.

### Include

```cpp
#include "{path to}/utils/system/ui/ui.h"
```

### Example

```cpp
using namespace SYSTEM::UI;

for (int i = 0; i < 100; i++)
{
    ProgressWindow("正在检测智商..", i);
    HAL::CanvasUpdate();
    HAL::Delay(20);
}
```



### Buzz music player

A json buzz music file player refs to *https://github.com/robsoncouto/arduino-songs*

参考 *https://github.com/robsoncouto/arduino-songs* 的蜂鸣器音乐播放器

### Include

```cpp
#include "{path to}/utils/system/audio/audio.h"
```

### Example

[json music example](https://github.com/Forairaaaaa/rachel_sdk_simulator/blob/main/rachel/apps/app_music/assets/buzz_music/nokia.json)

```cpp
using namespace SYSTEM::AUDIO;

// Play the music json file store in SD card, 播放SD路径上的json音乐文件 
BuzzMusicPlayer::playFromSdCard("/buzz_music/nokia.json");
```



### Button

Button lib refs to *https://github.com/madleech/Button*

参考 *https://github.com/madleech/Button* 的按键库


# OfflineBurner 离线编程器

[![Version](https://img.shields.io/badge/version-0.12-yellow.svg)](https://github.com/Sun2773/OfflineBurner)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-STM32F103-orange.svg)](https://www.st.com/en/microcontrollers-microprocessors/stm32f103.html)
[![Hardware](https://img.shields.io/badge/hardware-立创-blue.svg)](https://oshwhub.com/xiaoxunweixun/burner)

## 项目简介

Burner 是一款基于**STM32F103**的离线编程器，支持对各种 STM32 系列微控制器进行离线烧录。该编程器操作简单，免驱动，具有**U盘**拖拽式固件传输功能，可脱离**PC**独立完成目标芯片的程序烧录工作。不需要上位机，支持 Windows、macOS、Android 等所有能够挂载 U盘 的设备，只要支持 FAT 文件系统即可使用。

### 核心优势

- 🚀 **即插即用**: 免驱动，插入即可使用
- 📂 **拖拽式操作**: 如同普通 U盘，直接拖拽 .bin 文件
- 🔌 **离线工作**: 无需 PC 连接，独立完成烧录任务
- 💡 **智能提示**: LED 和声音状态反馈
- 📱 **跨平台可用**: 支持 Windows、macOS、Android 端

## 主要特性

- 🔥 **离线烧录**: 支持脱离 PC 独立完成 STM32 芯片烧录
- 💾 **U盘模式**: 拖拽式固件文件传输，无需专用软件
- 🎯 **多芯片支持**: 支持 STM32F0/F1/F2/F3/F4 系列芯片，可自行增加烧录算法支持更多芯片
- ⚡ **SWD 接口**: 通过 SWD 协议进行目标芯片编程
- 🔧 **智能识别**: 自动检测目标板连接并触发烧录
- 🔊 **状态指示**: LED 和蜂鸣器丰富的状态提示
- 🛡️ **IAP 升级**: 支持通过 U盘 进行固件升级
- 🎮 **按键操作**: 支持手动触发烧录和 U盘 挂载

## 硬件架构

### 主控芯片

- **MCU**: STM32F103 系列
- **存储**: 外部 SPI Flash (16MB)
- **接口**: USB 2.0 Full Speed
- **调试**: SWD 接口

## 开发环境

### 必需工具

- **IDE**: IAR Embedded Workbench for ARM
- **调试器**: J-Link 或 ST-Link
- **Python**: Python 3.x (项目依赖 Python 脚本生成文件)

### 依赖库

- STM32F10x Standard Peripheral Library
- CMSIS Core
- CMSIS-DAP
- FatFS 文件系统
- cJSON 解析库
- USB FS Device Driver

## 快速开始

### 1. 获取项目

```bash
git clone https://github.com/Sun2773/OfflineBurner.git
cd OfflineBurner
```

### 2. 开发环境配置

1. 安装 IAR Embedded Workbench
2. 连接 J-Link 调试器
3. 打开 `Project.eww` 工作空间文件

### 3. 编译项目

**首次编译需先执行初始化脚本**：

```bash
./Script/init.bat  # 安装 Python 依赖
```
**说明**：

> **注意**：Python 脚本并非必须依赖。
> 
> **脚本作用**：
> - 自动提取 `Version.h` 中的版本号
> - 生成对应版本号命名的 `.bin` 文件
> - 合并 Bootloader，生成完整固件并输出到 `Output` 文件夹
> 
> **无 Python 环境的替代方案**：
> 1. 修改 IAR 项目配置，关闭 Post-build 命令
> 2. 如需输出 `.bin` 文件，请在 Output Converter 中手动配置
> 3. 重新编译项目即可


**使用 VS Code 任务**：

- 按 `Ctrl+Shift+P` 打开命令面板
- 运行 "Tasks: Run Task"
- 选择 "iar: Build Project"

**使用 IAR IDE**：

- 打开项目后选择对应配置 (Debug/Release/Bootloader)
- 点击编译按钮或按 F7

**注意**：

> 使用 Python 脚本编译时，**必须先编译 Bootloader**，再编译主程序 (Debug/Release)。
> 
> 因为 Python 脚本会在编译主程序时自动合并 Bootloader 和主程序固件。

### 4. 烧录固件到编程器

**方式一：使用 IAR 直接下载**

- 需要先下载 Bootloader 配置
- 然后下载主程序

**方式二：使用脱机烧录器**

- 通过 J-Flash 或其他脱机烧录器
- 下载与 Bootloader 合并后的 .bin 文件

### 5. 设备固件升级

如需升级编程器固件：

1. 在编程器 U 盘中创建一个名为 `firmware` 的文件夹
2. 将新的固件文件放入 `firmware` 文件夹下
3. 重新为编程器上电，等待绿色指示灯 500ms 周期闪烁即升级完成
4. **注意**: 升级过程中红灯闪烁属正常现象，不要断电

### 6. 添加算法

如需添加自己的算法：

1. 参考[编程算法项目](https://github.com/Sun2773/OfflineBurnerAlgo.git)
2. 编译后将生成的\*.c 文件添加到工程
3. 修改 Arithmetic\algo\flash_blob.c，添加自己的目标板
4. 编译下载

### 7. 配置文件 (可选)

系统会在编程器 U盘 中自动生成配置文件 `config.json`：

```json
{
  "file": "",
  "version": "0.11",
  "autoBurn": 1,
  "chipErase": 0,
  "readProtection": 0,
  "autoRun": 1,
  "verify": 0,
  "flashAddr": "0x08000000"
}
```

**说明**：

- 可修改此文件进行功能配置
- 删除文件后重新上电会生成默认配置

## 自动识别芯片原理

离线编程器通过 SWD (Serial Wire Debug) 接口实现对目标 STM32 芯片的自动识别，整个识别过程分为以下几个关键步骤：

### 1. 读取 DBGMCU_IDCODE 寄存器

- 参考芯片手册，编程器通过读取**DBGMCU_IDCODE**，来识别目标芯片
- 构建一个芯片列表，每次检测到芯片后读取**DBGMCU_IDCODE**，匹配列表获取编程算法

| 芯片                              | DBGMCU_IDCODE DEV_ID |
| --------------------------------- | -------------------- |
| STM32F03x                         | 0x444                |
| STM32F04x                         | 0x445                |
| STM32F05x                         | 0x440                |
| STM32F07x                         | 0x448                |
| STM32F09x                         | 0x442                |
| STM32F10x_LD                      | 0x412                |
| STM32F10x_MD                      | 0x410                |
| STM32F10x_HD                      | 0x414                |
| STM32F10x_XL                      | 0x418                |
| STM32F2xx                         | 0x411                |
| STM32F3xx                         | 0x432                |
| STM32F405xx/07xx STM32F415xx/17xx | 0x413                |

### 2. 读取 Flash 大小

- 同系列的芯片可能集成不同的 Flash，编程算法可能不同
- 通过读取 Flash 大小寄存器来匹配具体的算法
- **注意**：若芯片设置了读保护会读取不到 Flash 大小，需要先解锁再读取
- 不同的芯片 Flash 大小寄存器地址也不一样，需要参考芯片手册，添加到算法列表中

| 芯片       | 地址       |
| ---------- | ---------- |
| STM32F0/F3 | 0x1FFFF7CC |
| STM32F1    | 0x1FFFF7E0 |
| STM32F2/F4 | 0x1FFF7A22 |

### 3. 制作如下算法列表

```c
const FlashBlobList_t FlashBlobList[] = {
    {
        .DevId         = 0x444,              // STM32F03x 设备ID
        .Name          = "STM32F03x",        // 产品名称
        .FlashSizeAddr = 0x1FFFF7CC,         // Flash大小寄存器地址
        .FlashSize     = {16, 64},           // Flash容量范围 (KB)
        .prog_flash    = &_stm32f0xx_64_,    // 对应的编程算法
        .prog_opt      = &_stm32f0xx_opt_,   // 选项字节算法
    },
    // ... 更多芯片定义
};
```
- 每个芯片都需要两套算法
- 一个是处理选项字节的，对芯片加锁解锁
- 另一个是处理 Flash 的，对芯片进行写入操作

## 使用方法

### 快速使用步骤

1. **连接电脑**：将编程器插入电脑 USB 口
2. **挂载 U盘**：长按按键直至蜂鸣器长鸣，U盘挂载成功
3. **拖入固件**：将目标程序 (.bin 文件) 直接拖入 U盘 (可修改配置文件)
4. **加载程序**：再次单击按键或重新为编程器上电，红绿指示灯交替闪烁，正在加载固件，等待绿灯 500ms 周期闪烁 (处理完成)
5. **连接目标**：通过 SWD 接口连接目标 STM32 单片机
6. **自动烧录**：连接目标板后自动触发烧录 (autoBurn=1)
7. **手动烧录**：未烧录状态下，单击功能键主动触发烧录

### 烧录速度

- 📊 **下载速度**: 约 50KB/s (不含擦除时间)
- ⏱️ **速度差异**: 不同芯片的下载速度和擦除时间略有差异
- 🧪 **实测数据**: STM32F407 烧录 800KB 左右大小的程序
  - 芯片擦除：约 15 秒
  - 程序下载：约 15 秒
  - 总计用时：约 30 秒

### 设备固件升级

如需升级编程器固件：

1. 在编程器 U盘 中创建一个名为 `firmware` 的文件夹
2. 将新的固件文件放入 `firmware` 文件夹下
3. 重新为编程器上电，等待绿色指示灯 500ms 周期闪烁即升级完成
4. **注意**: 升级过程中红灯闪烁属正常现象，不要断电

### 重要注意事项

- ⚠️ **文件限制**: 只能放入一个 `*.bin` 文件
- ⚠️ **命名规范**: 文件名不可使用中文字符
- ⚠️ **升级安全**: 设备升级过程中严禁断电，否则设备变砖
- ⚠️ **烧录流程**: 拖入固件后单击按键或需重新上电，等待文件处理完成
  - 编程器会自动将 U盘 中的程序文件复制到内部 Flash 存储
  - 复制过程中红绿灯交替闪烁，完成后会自动删除 U盘 中的文件(防止固件泄露)
  - 烧录时从内部 Flash 读取程序并下载到目标板
  - 等待绿灯 500ms 周期闪烁后即可开始烧录操作

### LED 和蜂鸣器状态指示

#### 蜂鸣器提示

- 🔊 **短鸣一声**: 开始烧录
- 🔊 **再次短鸣**: 烧录完成
- 🔊 **长鸣**: 编程失败 (同时红灯常亮)
- 🔊 **超短鸣**: 识别到目标板 (非自动烧录模式)

#### LED 状态指示

- 🟢 **绿灯闪烁**: 正在烧录
- 🟢 **绿灯 500ms 周期闪烁**: 设备空闲/处理完成
- 🔴 **红灯闪烁**: 正在处理文件
- 🔴 **红灯常亮**: 编程失败 (同时蜂鸣器长鸣)
- 🟢 **绿灯呼吸**: U盘模式

## 开源平台

- 📋 **软件开源**: [GitHub](https://github.com/Sun2773/OfflineBurner)
- 📋 **软件开源**: [Gitee](https://gitee.com/SUN2773/OfflineBurner)
- 🔧 **硬件开源**: [立创开源硬件平台](https://oshwhub.com/xiaoxunweixun/burner)

---

**注意**: 本项目仅供学习和开发使用，请遵守相关法律法规和开源协议。

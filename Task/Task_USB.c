#include "Task_USB.h"
#include "buzzer.h"
#include "hw_config.h"
#include "usb_pwr.h"

static uint16_t USB_Reset_Timer = 0;

/**
 * @brief  USB任务处理函数
 * @note   100ms执行一次
 * @retval None
 */
void USB_Task(void) {
    static uint16_t usb_timeout = 0;
    if (USB_StateGet()) {
        if (usb_timeout < 20) {
            usb_timeout++;
        } else if (bDeviceState != CONFIGURED) {
            USB_Unload();
            Beep(300);
        }
    } else {
        usb_timeout = 0;
    }
    if (USB_Reset_Timer > 0) {
        if (--USB_Reset_Timer == 0) {
            NVIC_SystemReset();
        }
    }
}

/**
 * @brief  USB重置函数
 * @note   延时1秒后重置USB
 * @retval None
 */
void USB_Reset(void) {
    USB_Reset_Timer = 10;   // 1秒后重置USB
    USB_Unload();
    Beep(500);
}
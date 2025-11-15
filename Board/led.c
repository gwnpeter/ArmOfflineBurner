#include "led.h"

/**
 * @brief  LED IO初始化
 * @note
 * @retval None
 */
void LED_Init(void) {
    GPIO_InitTypeDef        GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef       TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   // 使能PC端口时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);    //

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_2;   // LED0端口配置
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   // IO口速度为2MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);              // 根据设定参数初始化GPIO

    TIM_TimeBaseStructure.TIM_Period        = 1000 - 1;             // 设置自动重装载值
    TIM_TimeBaseStructure.TIM_Prescaler     = 72 - 1;               // 设置分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;                    // 设置时钟分割
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;   // 设置计数模式
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);                 // 初始化定时器

    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM2;          // 设置比较模式
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   // 设置比较输出状态
    TIM_OCInitStructure.TIM_Pulse       = 0;                        // 设置比较值
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;      // 设置输出极性
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);                        // 初始化通道
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);                        // 初始化通道

    TIM_CtrlPWMOutputs(TIM2, ENABLE);                   // 主输出使能
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);   // 预装载使能
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);   // 预装载使能
    TIM_ARRPreloadConfig(TIM2, ENABLE);                 // ARR预装载使能
    TIM_Cmd(TIM2, ENABLE);                              // 使能定时器
}

#include "buzzer.h"

static uint16_t Beep_Timer = 0;

// BUZZER IO初始化
void Buzzer_Init(void) {
    GPIO_InitTypeDef        GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef       TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;         // 端口配置
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;    //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   // IO口速度为2MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);              // 根据设定参数初始化GPIO

    TIM_TimeBaseStructure.TIM_Period        = 200 - 1;              // 设置自动重装载值
    TIM_TimeBaseStructure.TIM_Prescaler     = 72 - 1;               // 设置分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;                    // 设置时钟分割
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;   // 设置计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                 // 初始化定时器

    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;                   // 设置比较模式
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;           // 设置比较输出状态
    TIM_OCInitStructure.TIM_Pulse       = (uint16_t) ((TIM3->ARR) * 0.5f);   // 设置比较值
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;               // 设置输出极性
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);                                 // 初始化通道

    TIM_CtrlPWMOutputs(TIM3, ENABLE);                   // 主输出使能
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);   // 通道预装载使能
    TIM_ARRPreloadConfig(TIM3, ENABLE);                 // ARR预装载使能
    TIM_Cmd(TIM3, ENABLE);                              // 使能定时器
}

/**
 * @brief  蜂鸣器任务
 * @note   10ms周期执行
 * @retval None
 */
void Beep_Task(void) {
    if (Beep_Timer > 0) {
        Beep_On();
        Beep_Timer--;
    } else {
        Beep_Off();
    }
}

void Beep(uint16_t delay) {
    Beep_Timer = delay;
}
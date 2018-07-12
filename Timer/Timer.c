/**
  ******************************************************************************
  * 文件名程: Timer.c
  * 作    者: By Sw Young
  * 版    本: V1.0
  * 功    能:
  * 编写日期: 2018.3.29
  ******************************************************************************
  * 说明：
  * 硬件平台：
  *   MCUc:TM4C123
  * 软件设计说明：
  *
  * Github：
  ******************************************************************************
**/
#include "timer.h"


char Time_Flag = 0;
uint32_t Counter = 0;
uint8_t Beep_Flag = 0;
uint32_t Beep_Counter = 0;
uint32_t Beep_Fre = 40;

/**
  * 函 数 名:MotorContolTimer.c
  * 函数功能:
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明:
  *   By Sw Young
  *   2018.03.29
  */
void Timer0_Config(void)
{
       //
       // Enable the peripherals used by this example.
       //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
       //
       // Enable processor interrupts.
       //
       //不分频
       //设置为向上计数模式
        TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC_UP);
       //
       //把计数值装满
       TimerLoadSet(TIMER0_BASE, TIMER_A,0xFFFFFFFF);//2
       //
       //***************************中断使能*******************************************
       //默认不中断
       //使能TIME0B在基数结束时中断
       //TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
       //使能TIMER0B中断
       //IntEnable(INT_TIMER0A);
       IntDisable(INT_TIMER0A);//2
       //动态注册
       //TimerIntRegister(ui32Base, ui32Timer, pfnHandler)
       //使能TIMER0B,开始计数
       //TimerEnable(TIMER0_BASE, TIMER_B);
       TimerEnable(TIMER0_BASE, TIMER_A);//2
       //使能处理器中断
       IntMasterEnable();
}
/**
  * 函 数 名:Timer0IntHandler.c
  * 函数功能:
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明:
  *   By Sw Young
  *   2018.03.29
  */
uint8_t k=0;
void Timer0IntHandler(void)
{
    uint32_t ui32IntStatus;
    ui32IntStatus = TimerIntStatus(TIMER0_BASE, true);
    TimerIntClear(TIMER0_BASE, ui32IntStatus);//清除中断标志位
    if((GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0) & GPIO_PIN_0)  != GPIO_PIN_0)
    {
    KeyPress0=(1+KeyPress0)%2;
    }

    if(k)
        {k=0;GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, GPIO_PIN_2);}
    else
        {k=1;GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, 0);}
}
void Timer1_Config(void)
{
       //
       // Enable the peripherals used by this example.
       //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
       //
       // Enable processor interrupts.
       //
        IntMasterEnable();

       //
       // Configure the two 32-bit periodic timers.
       //
        TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);

        TimerLoadSet(TIMER1_BASE, TIMER_A,  800000); //Fre = 主频/800000 = 100HZ

       //
       // Setup the interrupts for the timer timeouts.
       //
        IntEnable(INT_TIMER1A);

        TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
       //
       // Enable the timers.
       //
        TimerEnable(TIMER1_BASE, TIMER_A);
}
/**
  * 函 数 名:Timer1IntHandler.c
  * 函数功能:
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明:
  *   By Sw Young
  *   2018.03.29
  */
/*
 * 定时器1的中断服务函数在PID.C中
 */


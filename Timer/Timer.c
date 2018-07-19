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
#include "MavLink_Receive/mavlink_recieve.h"
#include "Control/Control.h"
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
    // The Timer0 peripheral must be enabled for use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    //
    // Configure Timer0A and Timer0B connect as a 32-bit periodic timer.
    //
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC_UP);

    //
    // Set the load value to max value.
    //
    TimerLoadSet(TIMER0_BASE, TIMER_A, 0xFFFFFFFF);

    // Disable the timer0 interrupt.
    IntDisable(INT_TIMER0A);

    // Enable the timer.
    TimerEnable(TIMER0_BASE, TIMER_A);

    //
    // Enable processor interrupts.
    //
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

        TimerLoadSet(TIMER1_BASE, TIMER_A,  1600000); //Fre = 主频/1600000 = 50HZ

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
void Timer2_Config(void)
{
       //
       // Enable the peripherals used by this example.
       //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
       //
       // Enable processor interrupts.
       //
        IntMasterEnable();

       //
       // Configure the two 32-bit periodic timers.
       //
        TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);

        TimerLoadSet(TIMER2_BASE, TIMER_A,  800000); //Fre = 主频/800000 = 100HZ

       //
       // Setup the interrupts for the timer timeouts.
       //
        IntEnable(INT_TIMER2A);

        TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
       //
       // Enable the timers.
       //
        TimerEnable(TIMER2_BASE, TIMER_A);
}
uint8_t i=0;
void Timer2IntHandler(void)
{
    uint32_t ui32IntStatus;
    ui32IntStatus = TimerIntStatus(TIMER2_BASE, true);
    TimerIntClear(TIMER2_BASE, ui32IntStatus);//清除中断标志位

//    Get_Distance();//获取高度
//    Get_Attitude();//获取姿态

//    i=~i;
//    if(i)
//        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
//    else
//        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
}

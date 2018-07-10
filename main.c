/*******************************************
开发坏境:CCSv7.0
开发板:TIVA C Launchpad(TM4C123GH6PM)
程序功能:16位定时器，单次定时模式和周期性定时模式
程序说明:
编程者: Young sw
********************************************/
#include <stdint.h>
#include <stdbool.h>

/**
  ******************************************************************************
  * 文件名程: main.c
  * 作    者: By Sw Young
  * 版    本: V1.0
  * 功    能:
  * 编写日期: 2018.3.29
  ******************************************************************************
  * 说明：
  * 硬件平台：
  *   MCUc:TM4C123、2相四线步进电机、DRV8825电机驱动、WiFi
  * 软件设计说明：
  *   通过无线精确控制小车的前进、后退距离；左转右转角度。
  * Github：https://github.com/youngsw/Remote_Control_Car_PointRace_3_Car
  ******************************************************************************
**/
#include <stdint.h>
#include <stdbool.h>
#include "stdio.h"

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"
#include "driverlib/pwm.h"
#include "colorful_LED/colorful_LED.h"
#include "Pwm/pwm.h"
#include "Timer/Timer.h"
#include "oled.h"
#include "bmp.h"
#include "delay/delay.h"
#include "utils/uartstdio.h"
#include "driverlib/uart.h"
#include "uart/uart.h"
#include "uart/uartstdio.h"
#include "Beep/Beep.h"
#include "9.6'OLED/OLED.h"
#include "head.h"
#include "Control/Control.h"
#include "sonar.h"


void HardwareConfig(void)
{
    Uart0Iint();        //串口0初始化
    Uart1Iint();        //串口1初始化

    PwmConfig();            //初始化PWM

    LED_ColorInit();    //LED初始化
    LED_Color(160, 0, 2);

    OLED_Init();            //初始化OLED
    OLED_Clear();
    OLED_DrawBMP(0,0,128,8,BMP3);

    Sonar_Configure();
    Sonar_GPIOA_Configure();
    Sonar_GPIOA_Interrupt();

    Timer0_Config();

}

uint16_t Disetence ;
int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //主频设置80M
    HardwareConfig();
    LED_Color(255,0,0);
    UnlockPixhawk();

    while(1)
    {
        //UARTprintf("Hello");
        Disetence = GetAverageDistance();
        UARTprintf("Distance: %d\n",Disetence);
        Delay_ms(1000);
    }
}

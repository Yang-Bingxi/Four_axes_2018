/*
 * Control.c
 *
 *  Created on: 2018年7月10日
 *      Author: Sw Young
 */
#include "head.h"
#include "colorful_LED/colorful_LED.h"
#include "Pwm/pwm.h"
#include "Timer/Timer.h"
#include "oled.h"
#include "delay/delay.h"
#include "uart/uart.h"
#include "Beep/Beep.h"
#include "9.6'OLED/OLED.h"
#include "Control.h"

/*
 * 参数初始化
 */
//高度:单位 MM
uint16_t Goal_Distance = 800;//默认定高值800mm
uint16_t Real_Distance = 0;
uint16_t Error_Distance = 0;

uint16_t Goal_XCoordinate,Goal_YCoordinate;
uint16_t Real_XCoordinate,Real_YCoordinate;
extern volatile uint8_t get_x, get_y;

uint8_t Control_Open = 0;

/*遥控器校准值
 *CH1 1100-1950
 *CH2 1100-1950
 *CH3 1100-1950
 *CH4 1100-1950
 *CH5 1100(自稳)-1520(定高)-1950(降落)
 */
void UnlockPixhawk(void)
{
    PwmControl_1(1520);
    PwmControl_2(1520);
    PwmControl_3(1100);
    PwmControl_4(1520);
    PwmControl_5(1100); //自稳模式
    Delay_ms(1000);//延时等待
    PwmControl_3(1100);
    PwmControl_4(1950);//解锁
    Delay_ms(1000);
    Delay_ms(1000);
    Delay_ms(1000);
    PwmControl_4(1520);

    PwmControl_1(1520);
    PwmControl_2(1520);
    PwmControl_3(1100);
    PwmControl_4(1520);

    PwmControl_5(1520); //定高模式

}
void LockPixhawk(void)
{
    PwmControl_3(1100);
    PwmControl_4(1950);//上锁
    Delay_ms(1000);
    Delay_ms(1000);
    Delay_ms(1000);
    PwmControl_4(1520);
}
void LandMode(void)
{
    PwmControl_5(1950); //降落模式
    PwmControl_1(1520);
    PwmControl_2(1520);
    PwmControl_3(1100);
    PwmControl_4(1520);
}
void Get_Coordinate(void)
{
    get_x = Real_XCoordinate;
    get_y = Real_YCoordinate;
}
void Get_Distance(void)
{
    Real_Distance = GetAverageDistance();
}
void AltitudeHold(void)
{
    Real_Distance = GetAverageDistance();
    if(Real_Distance>Goal_Distance)
        Error_Distance = Real_Distance-Goal_Distance;
    else if(Goal_Distance>Real_Distance)
        Error_Distance = Goal_Distance-Real_Distance;


}

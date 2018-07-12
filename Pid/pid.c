/*
 * pid.c
 *
 *  Created on: 2018年7月10日
 *      Author: Sw Young
 */

#include "pid.h"
#include "timer.h"
#include "Control/Control.h"
#include "Pwm/pwm.h"

extern uint8_t Control_Open;

PID_K PID_X;
PID_K PID_Y;
PID_K PID_H;
PID_Data PID_Data_X;
PID_Data PID_Data_Y;
PID_Data PID_Data_H;

bool start_PID_X = false;
bool start_PID_Y = false;
bool start_PID_H = false;

volatile int err_x = 0;
volatile int err_y = 0;
volatile int err_h = 0;

volatile uint8_t get_x = CAMERA_MID_X, get_y = CAMERA_MID_Y;

void PID_Init(void)
{
    get_x = CAMERA_MID_X;
    get_y = CAMERA_MID_Y;
    PID_X.Kp           = DEFAULT_KP_X;
    PID_X.Ki           = DEFAULT_KI_X;
    PID_X.Kd           = DEFAULT_KD_X;
    PID_X.dt           = (float)(1.0/DEFAULT_PID_FREQ);
    PID_X.d_LPF        = DEFAULT_LPFITER;
    PID_X.I_MAX        = DEFAULT_I_MAX;
    PID_X.OUT_MAX      = DEFAULT_OUT_MAX;

    PID_Data_X.LastError        = 0.0;
    PID_Data_X.Error            = 0.0;
    PID_Data_X.Proportion       = 0.0;
    PID_Data_X.Integrator       = 0.0;
    PID_Data_X.Last_Derivative  = 0.0;
    PID_Data_X.Derivative       = 0.0;
    PID_Data_X.PID_OUT          = 0.0;

    PID_Y.Kp           = DEFAULT_KP_Y;
    PID_Y.Ki           = DEFAULT_KI_Y;
    PID_Y.Kd           = DEFAULT_KD_Y;
    PID_Y.dt           = (float)(1.0/DEFAULT_PID_FREQ);
    PID_Y.d_LPF        = DEFAULT_LPFITER;
    PID_Y.I_MAX        = DEFAULT_I_MAX;
    PID_Y.OUT_MAX      = DEFAULT_OUT_MAX;

    PID_Data_Y.LastError      = 0.0;
    PID_Data_Y.Error           = 0.0;
    PID_Data_Y.Proportion      = 0.0;
    PID_Data_Y.Integrator      = 0.0;
    PID_Data_Y.Last_Derivative = 0.0;
    PID_Data_Y.Derivative      = 0.0;
    PID_Data_Y.PID_OUT         = 0.0;

    PID_H.Kp           = DEFAULT_KP_H;
    PID_H.Ki           = 0;
    PID_H.Kd           = 0;
    PID_H.dt           = 0;
    PID_H.d_LPF        = 0;
    PID_H.I_MAX        = 0;
    PID_H.OUT_MAX      = 0;

    PID_Data_H.LastError       = 0.0;
    PID_Data_H.Error           = 0.0;
    PID_Data_H.Proportion      = 0.0;
    PID_Data_H.Integrator      = 0.0;
    PID_Data_H.Last_Derivative = 0.0;
    PID_Data_H.Derivative      = 0.0;
    PID_Data_H.PID_OUT         = 0.0;
}

void Position_PID(void)
{
    PID_Data_X.Proportion = PID_X.Kp * PID_Data_X.Error;

    // calculate integrator constrain in i_max.
    if((PID_X.Ki != 0) && (PID_X.dt != 0))
    {
        PID_Data_X.Integrator += PID_X.Ki * PID_Data_X.Error * PID_X.dt;
        if (PID_Data_X.Integrator < -(PID_X.I_MAX))
        {
            PID_Data_X.Integrator = -(PID_X.I_MAX);
        }
        else if (PID_Data_X.Integrator > PID_X.I_MAX)
        {
            PID_Data_X.Integrator = PID_X.I_MAX;
        }
    }
    else
    {
        PID_Data_X.Integrator = 0;
    }

    // calculate instantaneous Derivative.
    if((PID_X.Kd != 0) && (PID_X.dt != 0))
    {
        PID_Data_X.Derivative = PID_X.Kd * (PID_Data_X.Error - PID_Data_X.LastError) / PID_X.dt;
        // discrete low pass filter, cuts out the
        // high frequency noise that can drive the controller crazy.
        PID_Data_X.Derivative = PID_Data_X.Last_Derivative + (PID_X.dt / ( PID_X.d_LPF + PID_X.dt)) * (PID_Data_X.Derivative - PID_Data_X.Last_Derivative);
        // update state
        PID_Data_X.LastError = PID_Data_X.Error;
        PID_Data_X.Last_Derivative = PID_Data_X.Derivative;
    }

    PID_Data_X.PID_OUT = PID_Data_X.Proportion + PID_Data_X.Integrator + PID_Data_X.Derivative;
    if (PID_Data_X.PID_OUT > PID_X.OUT_MAX)
    {
        PID_Data_X.PID_OUT = PID_X.OUT_MAX;
    }
    else if (PID_Data_X.PID_OUT < -(PID_X.OUT_MAX))
    {
        PID_Data_X.PID_OUT = -(PID_X.OUT_MAX);
    }

    PID_Data_Y.Proportion = PID_Y.Kp * PID_Data_Y.Error;

    // calculate integrator constrain in i_max.
    if((PID_Y.Ki != 0) && (PID_Y.dt != 0))
    {
        PID_Data_Y.Integrator += PID_Y.Ki * PID_Data_Y.Error * PID_Y.dt;
        if (PID_Data_Y.Integrator < -(PID_Y.I_MAX))
        {
            PID_Data_Y.Integrator = -(PID_Y.I_MAX);
        }
        else if (PID_Data_Y.Integrator > PID_Y.I_MAX)
        {
            PID_Data_Y.Integrator = PID_Y.I_MAX;
        }
    }
    else
    {
        PID_Data_Y.Integrator = 0;
    }

    // calculate instantaneous Derivative.
    if((PID_Y.Kd != 0) && (PID_Y.dt != 0))
    {
        PID_Data_Y.Derivative = PID_Y.Kd * (PID_Data_Y.Error - PID_Data_Y.LastError) / PID_Y.dt;
        // discrete low pass filter, cuts out the
        // high frequency noise that can drive the controller crazy.
        PID_Data_Y.Derivative = PID_Data_Y.Last_Derivative + (PID_Y.dt / ( PID_Y.d_LPF + PID_Y.dt)) * (PID_Data_Y.Derivative - PID_Data_Y.Last_Derivative);
        // update state
        PID_Data_Y.LastError = PID_Data_Y.Error;
        PID_Data_Y.Last_Derivative = PID_Data_Y.Derivative;
    }

    PID_Data_Y.PID_OUT = PID_Data_Y.Proportion + PID_Data_Y.Integrator + PID_Data_Y.Derivative;
    if (PID_Data_Y.PID_OUT > PID_Y.OUT_MAX)
    {
        PID_Data_Y.PID_OUT = PID_Y.OUT_MAX;
    }
    else if (PID_Data_Y.PID_OUT < -(PID_Y.OUT_MAX))
    {
        PID_Data_Y.PID_OUT = -(PID_Y.OUT_MAX);
    }
}
uint8_t t;
void Timer1IntHandler(void)
{
    //
    // Clear the timer interrupt.
    //
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Update the interrupt status on the display.
    //
    TimerIntDisable(TIMER1_BASE, TIMER_A);
    if(Control_Open)
    /*
     * test
     */
//        t =~ t;
//        if(t)
//            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, GPIO_PIN_1);
//        else
//            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, 0);

    Get_Coordinate();//获取坐标值
    Get_Distance();//获取高度
    err_x = (int)(Real_Distance * (get_x - CAMERA_MID_X));
    err_y = (int)(Real_Distance * (get_y - CAMERA_MID_Y));
    PID_Data_X.Error = err_x;
    PID_Data_Y.Error = err_y;
    Position_PID();
    if(start_PID_X)
        PwmControl_1(channel_val_MID+PID_Data_X.PID_OUT);
    if(start_PID_Y)
        PwmControl_2(channel_val_MID+PID_Data_Y.PID_OUT);
    if(start_PID_H)
    {
        if(Real_Distance < (Goal_Distance - 10))
        {
            err_h = Goal_Distance-Real_Distance;
            //PwmControl_3(1600);//油门量60%//无pid调节
            PwmControl_3(channel_val_MID+PID_H.Kp*err_h);
        }

        if(Real_Distance > (Goal_Distance + 10))
        {
            err_h = Real_Distance-Goal_Distance;
            //PwmControl_3(1435);//油门量39%//无pid调节
            PwmControl_3(channel_val_MID-PID_H.Kp*err_h);

        }
        else if((Real_Distance-Goal_Distance<10)||(Goal_Distance-Real_Distance>10))//调节死区 -10 ~ +10
        {
            //set_ppm(0,0,channel_percent(50),0,0,0);
            PwmControl_3(channel_val_MID-PID_H.Kp*0);
        }
    }
    TimerIntEnable(TIMER1_BASE, TIMER_A);

}

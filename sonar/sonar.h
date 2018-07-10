#ifndef _SONAR_H
#define _SONAR_H

#include "head.h"
#include "delay/delay.h"
//V=331×根号(1+T/273)(m/S)

extern uint8_t temperature;

#define T  temperature       //在这里填温度O(∩_∩)O
#define SoundVelocity  (331*sqrt(1+T/273))

extern volatile bool DataIsReady;

void ShellSort(double A[], int n); //希尔排序
double GetAverageDistance();
void Sonar_Configure(void);
void SonarTrig(void);
void Sonar_GPIOA_Configure(void);
void Sonar_GPIOA_Interrupt(void);



#endif

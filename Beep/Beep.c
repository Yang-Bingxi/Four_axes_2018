#include "beep.h"
#include "head.h"

//默认蜂鸣器低电平有效
void Beep_Configure()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    //输出GPIO配置
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_7);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);//关蜂鸣器
}

void BeepSet(uint8_t status)
{
    if(status)
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);//开蜂鸣器
    if(status==0)
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);//关蜂鸣器

}

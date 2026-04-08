//<<AICUBE_USER_HEADER_REMARK_BEGIN>>
////////////////////////////////////////
// 在此添加用户文件头说明信息
// 文件名称: main.c
// 文件描述:
// 文件版本: V1.0
// 修改记录:
//   1. (2026-04-07) 创建文件
////////////////////////////////////////
//<<AICUBE_USER_HEADER_REMARK_END>>


#include "config.h"                     //默认已包含stdio.h、intrins.h等头文件


//<<AICUBE_USER_INCLUDE_BEGIN>>
// 在此添加用户头文件包含
//<<AICUBE_USER_INCLUDE_END>>


//<<AICUBE_USER_GLOBAL_DEFINE_BEGIN>>
// 在此添加用户全局变量定义、用户宏定义以及函数声明
uint16_t adc_value = 0;
uint16_t pwm_duty = 0;
uint16_t pwm_max = 0;
//<<AICUBE_USER_GLOBAL_DEFINE_END>>



////////////////////////////////////////
// 项目主函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void main(void)
{
    //<<AICUBE_USER_MAIN_INITIAL_BEGIN>>
    // 在此添加用户主函数初始化代码
    //<<AICUBE_USER_MAIN_INITIAL_END>>

    SYS_Init();

    //<<AICUBE_USER_MAIN_CODE_BEGIN>>
    // 在此添加主函数中运行一次的用户代码
    pwm_max = (uint16_t)41536;
    //<<AICUBE_USER_MAIN_CODE_END>>

    while (1)
    {
        USBLIB_OUT_Done();              //查询方式处理USB接收的数据

        //<<AICUBE_USER_MAIN_LOOP_BEGIN>>
        // 在此添加主函数中用户主循环代码
        adc_value = ADC_Convert(1);
        pwm_duty = (uint32_t)adc_value * pwm_max / 4095;
        PWM_UpdateDuty(PWMB_CH6, pwm_duty);
        printf("ADC1 = %d, PWM = %d\n", adc_value, pwm_duty);
        delay_ms(1);
        //<<AICUBE_USER_MAIN_LOOP_END>>
    }
}

////////////////////////////////////////
// 系统初始化函数
// 入口参数: 无
// 函数返回: 无
////////////////////////////////////////
void SYS_Init(void)
{
    EnableAccessXFR();                  //使能访问扩展XFR
    IAP_SetTimeBase();                  //设置IAP等待参数,产生1us时基

    //<<AICUBE_USER_PREINITIAL_CODE_BEGIN>>
    // 在此添加用户预初始化代码
    //<<AICUBE_USER_PREINITIAL_CODE_END>>

    PORT0_Init();                       //P0口初始化
    PORT1_Init();                       //P1口初始化
    PORT3_Init();                       //P3口初始化
    PORT5_Init();                       //P5口初始化
    CLK_Init();                         //时钟模块初始化
    ADC_Init();                         //ADC初始化
    PWMB_Init();                        //高级PWMB初始化
    delay_ms(1);
    USBLIB_Init();                      //USB库初始化
    delay_ms(1);

    //<<AICUBE_USER_INITIAL_CODE_BEGIN>>
    // 在此添加用户初始化代码
    //<<AICUBE_USER_INITIAL_CODE_END>>

    EnableGlobalInt();                  //使能全局中断
}

////////////////////////////////////////
// 微秒延时函数
// 入口参数: us (设置延时的微秒值)
// 函数返回: 无
////////////////////////////////////////
void delay_us(uint16_t us)
{
    do
    {
        NOP(14);                        //(MAIN_Fosc + 500000) / 1000000 - 10
    } while (--us);
}


////////////////////////////////////////
// 毫秒延时函数
// 入口参数: ms (设置延时的毫秒值)
// 函数返回: 无
////////////////////////////////////////
void delay_ms(uint16_t ms)
{
    uint16_t i;

    do
    {
        i = MAIN_Fosc / 10000;
        while (--i);
    } while (--ms);
}


//<<AICUBE_USER_FUNCTION_IMPLEMENT_BEGIN>>
// 在此添加用户函数实现代码
//<<AICUBE_USER_FUNCTION_IMPLEMENT_END>>



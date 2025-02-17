#include "pwm.h"



/**************************************************************************
函数功能：pwm初始化
入口参数：arr：设为一个时钟频率的最大值  psc： 预分频值
返回  值：无
**************************************************************************/
void PWM_Int(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;                //定义结构体GPIO_InitStructure
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;      //定义结构体TIM_TimeBaseStructure   
	TIM_OCInitTypeDef TIM_OCInitStructure;              //定义结构体TIM_OCInitStructure
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PB端口时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能定时器3
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //复用模式输出
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1; //PB0 、PB1
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;        //IO口速度
	GPIO_Init(GPIOB,&GPIO_InitStructure);                   //GPIO初始化
	
	TIM_TimeBaseStructure.TIM_Period = arr;                //设置下一个更新活动的自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;             //预分配值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;           //时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode= TIM_OCMode_PWM1;             //PWM脉冲宽度调制1
	TIM_OCInitStructure.TIM_Pulse = 0;                           //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //设置TIM输出极性为高
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	
	TIM_CtrlPWMOutputs(TIM3,ENABLE);//主输出使能
	
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能预装载寄存器
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);              //使能自动装载允许位
	TIM_Cmd(TIM3,ENABLE);//启动定时器3
	
	
}

void Set_PWM(int PWM1,int PWM2)
{
	if(PWM1>0){
		GPIO_SetBits(GPIOB, GPIO_Pin_14);	 // 高电平       PB14 --- AIN1     1
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);	 // 低电平	    PB15 --- AIN2     0
	}else{
		 GPIO_SetBits(GPIOB, GPIO_Pin_15);	 // 高电平      PB15 --- AIN2      1   
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);	 // 低电平}   PB14 --- AIN1      0
		PWM1=-PWM1;
	}
	if(PWM2>0){
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);     //高电平   PB13 --- BIN2     0
		GPIO_SetBits(GPIOB, GPIO_Pin_12);  // 低电平   PB12 --- BIN1         1
	}else{
		GPIO_SetBits(GPIOB, GPIO_Pin_13);     //高电平   PB13 --- BIN2       1
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);  // 低电平   PB12 --- BIN1       0
		PWM2=-PWM2;
	}
    TIM_SetCompare3(TIM3,PWM1);//设置TIM3通道3的占空比  3000/7200
	TIM_SetCompare4(TIM3,PWM2);
}


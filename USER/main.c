#include "stm32f10x.h"

#include "delay.h"
#include "gpio.h"
#include "moto.h"
#include "pwm.h"
#include "adc.h"
#include "usart.h"
#include "encoder.h"
#include "key.h"
#include "buzzer.h"
#include "lightsensor.h"

 /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/

int TargetVelocity=500;
float Velcity_Kp=1,  Velcity_Ki=3,  Velcity_Kd; //����ٶ�PID����
uint8_t Key_Value;

int main(void)
 {	 
	 int encoder_A,encoder_B;
	 int Velocity_PWM1=0,Velocity_PWM2=0;
	 u16 adcx;
	 float vcc;                                         
   SystemInit(); //����ϵͳʱ��Ϊ72M   
   delay_init();    //��ʱ������ʼ��
   Gpio_Init();    //��ʼ��gpio��B pin_12/pin_13/14/15
   uart_init(9600);		//���ڳ�ʼ��
   adc_Init();				//ADC1�ĳ�ʼ��   ֻ��TB6612����ѹģ�����л�ȡ��ص�ѹ�Ĺ��ܣ�ֻ��TB6612FNGû���������
   PWM_Int(7199,0);      //��ʼ��pwm��� 72000 000 /7199+1=10000 
   Encoder_Init_Tim2();
   Encoder_Init_Tim4();
	 Key_Init();
	 Buzzer_Init();
	 LightSensor_Init();
	 
	 
	 
	 
  while(1)
	{
		adcx=Get_adc_Average(ADC_Channel_6,10);  //��ȡadc��ֵ
		vcc=(float)adcx*(3.3*11/4096);     				//��ǰ��ѹ
		
		
		Key_Value = Key_GetNum();
		if(Key_Value == 1)
		{
		
		
		}
		
		if(Key_Value == 2)
		{
		
		
		
		}
		
		
		/*
		�������ƣ���ʹ�ñ���������ֵ�������������롣���������ǻ����趨ֱֵ���趨�ģ�������ϵͳ�ĵ�ǰ״̬�������
		�ص㣺�������ĸ���ͻȻ���ӣ��ⲿ���ţ�����Ч�ʷ����仯����ص�ѹ������¶ȵȸ��ţ����������ƿ����޷���ʱ����������ʵ��ת�����趨ֵ����ƫ�
		tips��ʹ��ʱ������ע�ʹ򿪼���
		*/
		printf("��ǰΪ�������ƽ̳�:\r\n");

		Velocity_PWM1=3000;						//��������-ֱ���趨PWMֵ
		Velocity_PWM2=3000;						//��������-ֱ���趨PWMֵ
		Set_PWM(Velocity_PWM1,Velocity_PWM2);	//��������-����PWMֵ�������
		
		/*
		��ȡ���������ݷ�����ͨ����ȡ��Ӧ��ʱ���ļ���ֵ����ȡ�����������ݡ���ѧϰ�ջ�����ǰ��Ҫѧϰ���ʹ��
		*/
		encoder_A=Read_Encoder(2);								//��ȡ������1��ֵ��  ����ʱ������⵱ǰ����ٶ� �ջ�ʱ����⵱ǰ����ٶȣ�����PID�������ջ����� 
		encoder_B=Read_Encoder(4);              				//��ȡ������2��ֵ��  ����ʱ������⵱ǰ����ٶ� �ջ�ʱ����⵱ǰ����ٶȣ�����PID�������ջ����� 
		
        /*
		�ջ����ƣ����������ı�������ֵ����PID�������γɱջ��������ٸ���PID�������ջ����ƺ������PWMֵ�Ե�����п���
		�ص㣺ͨ��ʵʱ�������������Ը���ȷ�ؿ��Ƶ���ٶȣ�������ͬʱ�ܹ���Ӧϵͳ�����ı仯����ص�ѹ�����Ч�ʵȣ����ⲿ���ţ����أ�Ħ��ϵ���ȣ�������ϵͳ���ȶ���
		tips��ʹ��ʱ������ע�ʹ򿪼���
		*/
//		printf("��ǰΪ�ջ����ƽ̳�:\r\n");
//		Velocity_PWM1=Velocity_A(TargetVelocity,encoder_A);		//PID�ջ�����-���PWMֵ
//		Velocity_PWM2=Velocity_B(TargetVelocity,encoder_B);		//PID�ջ�����-���PWMֵ
//		Set_PWM(Velocity_PWM1,Velocity_PWM2);			//�ջ�����-����PWMֵ�������
		printf("��ǰ��ѹ=%6.2f V  Encoder_A = %d  Encoder_B=%d\r\n",vcc,encoder_A,encoder_B);				//��ӡ��ǰ��ѹ������С�������λ	
	 }
 }
   

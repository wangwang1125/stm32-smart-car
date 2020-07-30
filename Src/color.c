#include "color.h"
int R=0,G=0,B=0;

int flag=0;
int Gray;//代表灰度值
//int g_SF[3];//从TCS3200输出信号的脉冲数转换为RGB标准值的RGB因子
float g_SF[3];//从TCS3200输出信号的脉冲数转换为RGB标准值的RGB因子
int g_count = 0;//计算与反射光强相对应TCS3200颜色传感器输出信号的脉冲数

//数组用于存储在1S内TCS3200输出信号的脉冲数，它乘以RGB比例因子就是RGB标准值
int g_array[3];
int g_flag =0;//滤波器模式选择顺序标志

//设置三个标志位，用于定值获取比例因子
int getrate1=0;  
int getrate2=0;  
int getrate3=0;  


//初始化TSC3200个控制引脚的输入输出模式
//设置TCS3200D的内置振荡器方波频率与其输出信号频率的比例因子为2%
void TSC_Init()
{
	TCS32_S0(0);TCS32_S1(1);
}



//选择滤波器模式，决定让红、绿、蓝，哪种光线通过滤波器
void TSC_FilterColor(int Level01,int Level02)
{
	if(Level01 !=0)
		Level01 = 1 ;
	
	if(Level02 !=0)
		Level02 = 1 ;
	
	TCS32_S2(Level01);
	TCS32_S3(Level02);
}


//中断函数，计算TCS3200输出信号的脉冲数
void TSC_Count()
{
	g_count ++;
}

//设置反射光中红、绿、蓝三色光分别通过滤波器时如何处理数据的标志
//该函数被 TSC——Callback（）调用
void TSC_WB(int Level0,int Level1)
{
	g_count = 0; //计数值清零
	g_flag ++; //输出信号技术标志
	TSC_FilterColor(Level0,Level1);//滤波器模式

}



//定时器中断函数，每1S中断后，把该时间内的红、绿、蓝三种光线通过滤波器时，
//TCS3200输出信号脉冲个数分别存储到数组g_array[3]的相应元素变量中
void TSC_Call()
{
	switch (g_flag)
	
	{
		case 0:
			TSC_WB(0,0); //选择让红色光线通过滤波器模式
		  break;
		case 1:
			
			flag=1;
		  g_array[0] = g_count;//存储1S内的红光通过滤波器时，TCS3200输出的脉冲个数 备用
		  TSC_WB(1,1);//选择让绿光线通过滤波器的模式
		  break;
		case 2:
			
			flag=2;
		  g_array[1] = g_count;//存储1S内的绿光通过滤波器时，TCS3200输出的脉冲个数
		  TSC_WB(0,1);//选择让蓝光线通过滤波器的模式
		  break;
		case 3:
			
			flag=3;
		  g_array[2] = g_count;//存储1S内的蓝光通过滤波器时，TCS3200输出的脉冲个数
		  TSC_WB(1,0);//选择让无滤波器的模式
		  
		  break;
		
		default:
			flag=4;
			g_count = 0;//计数值清零

		  break;
		
	}
}




float Rrate=0,Grate=0,Brate=0; //得到的比例因子定值，用于后续颜色检测时使用

//识别颜色函数，实时检测，请把  STOP_TIME;   注释掉，即打开定时器
int TCS3200_Distinguish(void)
{
	
	
	int Blue1=1,Green1=2,Red1=3;
	
    switch(flag)
	{
		case 1:
			 g_SF[0] =255.0/g_array[0]; //红色光比例因子
		   //在串口中打印出红光比例因子
		
		   getrate1++;//让标志位getrate1=1，而不清零从而达到保存某一时刻比例因子
		   if(getrate1==1)
			 {
				 Rrate=g_SF[0];
			 }
			 
		   flag=0;
		   break;
		
		case 2:
			 g_SF[1] =255.0/g_array[1]; //绿色光比例因子
		
		   getrate2++;
		   if(getrate2==1)
				Grate=g_SF[1];
		   flag=0;
		   break;
		
		case 3:
			 g_SF[2] =255.0/g_array[2]; //蓝色光比例因子
		
		   getrate3++;
		   if(getrate3==1)
			 {
				 Brate=g_SF[2];
			 }
			 
		   flag=0;
		   break;
	}

	

	if(flag==4)
	{
		float Max=0,Min=0;
        float Rhsv=0,Ghsv=0,Bhsv=0;
        float H=0,S=0,V=0;
		
		R = (int)(g_array[0]*Rrate);
		G = (int)(g_array[1]*Grate);
		B = (int)(g_array[2]*Brate);
		flag=0;//选择输出颜色的比例因子和RGB标志位清零
		g_flag =0;//滤波器模式选择顺序标志位清零
		

		
		if((B>=150)&&(R<=150)&&(G<=150)) //绿
			return Blue1;
		if((G>=150)&&(R<=150)&&(B<=150)) //绿
			return Green1;
		if((R>=150)&&(B<=150)&&(G<=150)) //绿
			return Red1;
		

		
	}
	return 0;
}




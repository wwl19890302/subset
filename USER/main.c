#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "24l01.h" 	 
//ALIENTEK战舰STM32开发板实验32
//无线通信 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司  
 int main(void)
 {	 
	u8 key,mode;
	u16 t=0;			 
	u8 tmp_buf[30];		    
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
	LCD_Init();	//初始化LCD
	KEY_Init();	 //按键初始化	
 
 	NRF24L01_Init();    	//初始化NRF24L01 

	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(60,70,200,16,16,"NRF24L01 TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2012/9/13");		  
 	while(NRF24L01_Check())	//检查NRF24L01是否在位.	
	{
		LCD_ShowString(60,130,200,16,16,"NRF24L01 Error");
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}								   
	LCD_ShowString(60,130,200,16,16,"NRF24L01 OK");
			LCD_ShowString(60,150,200,16,16,"NRF24L01 TX_Mode");	
		NRF24L01_TX_Mode();
	
	NRF24L01_RX_Mode();
 	while(1)//在该部分确定进入哪个模式!
	{
		key=KEY_Scan(1);
//		mode=1;
		
 			while(1)
			{	  		    		    				 
				if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
				{
//					tmp_buf[32]=0;//加入字符串结束符
					printf("%d %d\r\n",tmp_buf[0],tmp_buf[29]); 
					LCD_ShowString(0,190,239,32,16,tmp_buf); 	
					NRF24L01_TX_Mode();
					NRF24L01_TxPacket(tmp_buf);
				}else delay_us(100);	   
				t++;
				if(t==10000)//大约1s钟改变一次状态
				{
					t=0;
					LED0=!LED0;
				} 				    
			};

// 	  	switch (key)
// 		{
// 			case KEY_UP:
// 				tmp_buf[0] = 1;
// 				tmp_buf[1] = 200;
// 				break;
// 			case KEY_LEFT:
// 				tmp_buf[0] = 2;
// 				tmp_buf[1] = 160;
// 				break;
// 			case KEY_DOWN:
// 				tmp_buf[0] = 3;
// 				tmp_buf[1] = 100;
// 				break;
// 			case KEY_RIGHT:
// 				tmp_buf[0] = 4;
// 				tmp_buf[1] = 40;
// 				break;
// //			case KEY_UP:
// //				NRF24L01_TxPacket(tmp_buf);
// //				break;
// //			case KEY_UP:
// //				NRF24L01_TxPacket(tmp_buf);
// //				break;
// 			
// 		}
// 	//	mode = NRF24L01_TxPacket(tmp_buf);	
// 		if(key>=1 && key <= 6)  
// 		{ 				 
// 			if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
// 			{
// 				//			tmp_buf[2]=0;//加入结束符	
// 				LCD_ShowString(60,170,239,32,16,"Sended DATA:");	
// 				LCD_ShowString(0,190,239,32,16,tmp_buf); 
//   	  
// 	   
// 			}else
// 			{										   	
//  				LCD_ShowString(60,170,239,32,16,"Send Failed "); 
// 				LCD_Fill(0,188,240,218,WHITE);//清空上面的显示			   
// 			};
// 		}
// 			if(t % 100 == 0)
// 				LED0=!LED0;
// 			delay_ms(10);
// 			t++;				    
	}
    
}



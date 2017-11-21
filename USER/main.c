#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "24l01.h" 	 
//ALIENTEKս��STM32������ʵ��32
//����ͨ�� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  
 int main(void)
 {	 
	u8 key,mode;
	u16 t=0;			 
	u8 tmp_buf[30];		    
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();	//��ʼ��LCD
	KEY_Init();	 //������ʼ��	
 
 	NRF24L01_Init();    	//��ʼ��NRF24L01 

	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(60,70,200,16,16,"NRF24L01 TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2012/9/13");		  
 	while(NRF24L01_Check())	//���NRF24L01�Ƿ���λ.	
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
 	while(1)//�ڸò���ȷ�������ĸ�ģʽ!
	{
		key=KEY_Scan(1);
//		mode=1;
		
 			while(1)
			{	  		    		    				 
				if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
				{
//					tmp_buf[32]=0;//�����ַ���������
					printf("%d %d\r\n",tmp_buf[0],tmp_buf[28]); 
					LCD_ShowString(0,190,239,32,16,tmp_buf); 	
					NRF24L01_TX_Mode();
					NRF24L01_TxPacket(tmp_buf);
					NRF24L01_RX_Mode();
				}else delay_us(100);	   
				t++;
				if(t==10000)//��Լ1s�Ӹı�һ��״̬
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
// 				//			tmp_buf[2]=0;//���������	
// 				LCD_ShowString(60,170,239,32,16,"Sended DATA:");	
// 				LCD_ShowString(0,190,239,32,16,tmp_buf); 
//   	  
// 	   
// 			}else
// 			{										   	
//  				LCD_ShowString(60,170,239,32,16,"Send Failed "); 
// 				LCD_Fill(0,188,240,218,WHITE);//����������ʾ			   
// 			};
// 		}
// 			if(t % 100 == 0)
// 				LED0=!LED0;
// 			delay_ms(10);
// 			t++;				    
	}
    
}



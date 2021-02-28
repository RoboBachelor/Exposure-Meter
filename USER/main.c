//******************************************************************************/	 
// Exposure Meter on STM32 Pocket 
// Auther: Jiingyi Wang
// Date: Feb. 28, 2021
//******************************************************************************/
#include "delay.h"
#include "sys.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"
#include "bh1750.h"
#include "key.h"
#include <stdio.h>
#include <math.h>
	
typedef enum{
	WAITING = 0,
	MEASURE_ONCE,
	MEASURE_CONTINUNE,
}Meter_Mode_e;
	
Meter_Mode_e meter_mode;

char* exposure_table[] = {
	"2' f1.4 *",	//0EV
	"1' f1.4 *",
	"2 f1.4 *",
	"4 f1.4 *",
	"8 f1.4 *",
	"15 f1.4 *",
	"30 f1.4",
	"60 f1.4",
	"60 f2.0",	//8EV
	"60 f2.8",
	"60 f4.0",
	"125 f4.0",
	"250 f4.0",
	"500 f4.0",
	"1000 f4.0",
	"1000 f5.6",
	"1000 f8.0"	//16EV
};
	
int main(void)
{
	delay_init();
	LCD_Init();//LCD³õÊ¼»¯
	Key_GPIO_Init();
	LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
	BH1750_Init();
	while(1)
	{
		delay_ms(10);

		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0){
			float lux = BH1750_ReadLux();
			float EV = log(lux / 2.5);
			char display_buf[20];
			sprintf(display_buf, "Lux: %.1f", lux);
			LCD_ShowString(0,40, (u8*)display_buf, WHITE, GRAY,16,0);
			sprintf(display_buf, "EV: %.1f", EV);
			LCD_ShowString(0,56, (u8*)display_buf, WHITE, GRAY,16,0);
			int8_t EV_index = (int8_t)round(EV);
			if(EV_index >= 0 && EV_index <= 16){
				LCD_ShowString(0,72, (u8*)exposure_table[EV_index], WHITE, GRAY,16,0);
			}
			meter_mode = WAITING;		
			delay_ms(150);
		}
		
	}
}


#include "stm32f10x_i2c.h"
#include "app_i2c.h"

void I2C2_config (void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef I2C_InitStructure;
	
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	I2C_InitStructure.I2C_Ack = I2C_Ack_Disable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 200000;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = 0x0B;
	
	I2C_Init(I2C2,&I2C_InitStructure);
	I2C_Cmd(I2C2,ENABLE);
}



void I2C2_write(unsigned char HW_address, unsigned char sub, unsigned char data)
{
	int ticks = I2C_TIMEOUT;			// number of flag checks before stop i2c transmition 
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)&&ticks) {ticks--;}
	if (ticks == 0) return;
	ticks = I2C_TIMEOUT;
	
	I2C_Send7bitAddress(I2C2, HW_address, I2C_Direction_Transmitter);
	while((!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) && ticks) {ticks--;}
	if (ticks == 0) return;
	ticks = I2C_TIMEOUT;
	
	if (sub != 0xFF)
	{
		I2C_SendData(I2C2, sub);
		while((!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))&&ticks) {ticks--;}
		if (ticks == 0) return;
		ticks = I2C_TIMEOUT;
	}
	
	I2C_SendData(I2C2, data);
	while((!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))&&ticks) {ticks--;}
	if (ticks == 0) return;
	ticks = I2C_TIMEOUT;
	
	I2C_GenerateSTOP(I2C2, ENABLE);
	while((I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY)) && ticks) {ticks--;}
	if (ticks == 0) return;
}

char I2C2_read (unsigned char HW_address, unsigned char sub)
{
	char data;
	int ticks = I2C_TIMEOUT;			// number of flag checks before stop i2c transmition 
	

		I2C_GenerateSTART(I2C2, ENABLE);
		while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)&&ticks) {ticks--;}
		if (ticks == 0) return 0;
		ticks = I2C_TIMEOUT;
		
		I2C_Send7bitAddress(I2C2, HW_address, I2C_Direction_Transmitter);
		while((!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))&&ticks) {ticks--;}
		if (ticks == 0) return 0;
		ticks = I2C_TIMEOUT;
		
	if (sub != 0xFF)
	{	
		I2C_SendData(I2C2, sub);
		while((!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))&&ticks) {ticks--;}
		if (ticks == 0) return 0;
		ticks = I2C_TIMEOUT;
	}
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while((!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))&&ticks) {ticks--;}
	if (ticks == 0) return 0;
	ticks = I2C_TIMEOUT;
	
	I2C_Send7bitAddress(I2C2, HW_address, I2C_Direction_Receiver);
	while((!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))&&ticks) {ticks--;}
	if (ticks == 0) return 0;
	ticks = I2C_TIMEOUT;
	
	
	while((!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED))&&ticks) {ticks--;}
	if (ticks == 0) return 0;
	ticks = I2C_TIMEOUT;
	
	data = I2C2->DR;
	
	
	I2C_NACKPositionConfig(I2C2,I2C_NACKPosition_Current);
	
	I2C_GenerateSTOP(I2C2, ENABLE);
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY)&&ticks) {ticks--;}	
	if (ticks == 0) return 0;
	return data;
}

void I2C2_read_buf (unsigned char HW_address, unsigned char sub, unsigned char * p_buf, unsigned char buf_size)
{
	int ticks = I2C_TIMEOUT;			// number of flag checks before stop i2c transmition 
	

		I2C_GenerateSTART(I2C2, ENABLE);
		while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)&&ticks) {ticks--;}
		if (ticks == 0) 
		{
			return;
		}
		ticks = I2C_TIMEOUT;
		
		I2C_Send7bitAddress(I2C2, HW_address, I2C_Direction_Transmitter);
		while((!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))&&ticks) {ticks--;}
		if (ticks == 0) 
		{
			return;
		}
		ticks = I2C_TIMEOUT;
		
	if (sub != 0xFF)
	{	
		I2C_SendData(I2C2, sub);
		while((!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED))&&ticks) {ticks--;}
		if (ticks == 0) 
		{
			return;
		}
		ticks = I2C_TIMEOUT;
	}
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while((!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))&&ticks) {ticks--;}
	if (ticks == 0) 
	{
		return;
	}
	ticks = I2C_TIMEOUT;
	
	I2C_AcknowledgeConfig(I2C2,ENABLE);

	I2C_Send7bitAddress(I2C2, HW_address, I2C_Direction_Receiver);
	while((!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))&&ticks) {ticks--;}
	if (ticks == 0) 
	{
		return;
	}
	ticks = I2C_TIMEOUT;
		
	for (uint8_t i=0; i<buf_size; i++)
	{		
		while((!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED))&&ticks) {ticks--;}
		if (ticks == 0) 
		{
			return;
		}
		ticks = I2C_TIMEOUT;
		
		p_buf[i] = I2C2->DR;
	}
	
	I2C_AcknowledgeConfig(I2C2,DISABLE);
	
	I2C_NACKPositionConfig(I2C2,I2C_NACKPosition_Current);
	
	I2C_GenerateSTOP(I2C2, ENABLE);
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY)&&ticks) {ticks--;}	
	if (ticks == 0) return;
}


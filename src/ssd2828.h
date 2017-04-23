/*
 * ssd2828.h
 *
 *  Created on: May 4, 2016
 *      Author: metalheart
 */

#ifndef SSD2828_H_
#define SSD2828_H_

#include "common/hal_common.h"

enum ssd2828_pin
{
	SSD2828_RST = 0,
	SSD2828_CS,
	SSD2828_CLK,
	SSD2828_SDI,
	SSD2828_SDO
};

const gpio_pin_t ssd2828_pin_cfg[] =
{
		{GPIOA, GPIO_Pin_2, MODE_OUT},
		{GPIOA, GPIO_Pin_1, MODE_OUT},
		{GPIOA, GPIO_Pin_0, MODE_OUT},
		{GPIOA, GPIO_Pin_4, MODE_OUT},
		{GPIOA, GPIO_Pin_3, MODE_IN},
};

inline void ssd2828_pulse_clk()
{
	gpio_set(ssd2828_pin_cfg + SSD2828_CLK, 0);
	gpio_set(ssd2828_pin_cfg + SSD2828_CLK, 1);
	gpio_set(ssd2828_pin_cfg + SSD2828_CLK, 0);
}

inline void ssd2828_pulse_clk_hl()
{
	gpio_set(ssd2828_pin_cfg + SSD2828_CLK, 1);
	gpio_set(ssd2828_pin_cfg + SSD2828_CLK, 0);
}

void Set_RST(uint32_t index)
{
	gpio_set(ssd2828_pin_cfg + SSD2828_RST, index);
}

void Set_2805_CS(uint32_t index)
{
	gpio_set(ssd2828_pin_cfg + SSD2828_CS, index);
}

void Set_SCL(uint32_t index)
{
	gpio_set(ssd2828_pin_cfg + SSD2828_CLK, index);
}

void Set_SDI(uint32_t index)
{
	gpio_set(ssd2828_pin_cfg + SSD2828_SDI, index);
}

void SPI_3W_SET_Cmd(uint8_t cmd)
{
	gpio_set(ssd2828_pin_cfg + SSD2828_SDI, 0);	//Set DC=0, for writing to Command register
	ssd2828_pulse_clk();
	for(uint8_t i = 0; i < 8; ++i)
	{
		gpio_set(ssd2828_pin_cfg + SSD2828_SDI, cmd & 0x80);
		ssd2828_pulse_clk_hl();
		cmd = cmd << 1;
	}
}

void SPI_3W_SET_PAs(uint8_t value)
{
	uint32_t kk;

	gpio_set(ssd2828_pin_cfg + SSD2828_SDI, 1);
	ssd2828_pulse_clk();
	for(kk=0;kk<8;kk++)
	{
		gpio_set(ssd2828_pin_cfg + SSD2828_SDI, value & 0x80);
		ssd2828_pulse_clk_hl();
		value = value << 1;
	}
}
//-----------------------------------------------------
void Write_com(uint16_t vv)
{
	gpio_set(ssd2828_pin_cfg + SSD2828_CS, 0);
	SPI_3W_SET_Cmd(vv & 0xff);
}

void Write_register(uint16_t vv)
{
	SPI_3W_SET_PAs(vv & 0xff);
	SPI_3W_SET_PAs((vv >> 8) & 0xff);
}
//-----------------------------------------------------

void writec(uint8_t cmd)
{
	uint32_t kk;

	gpio_set(ssd2828_pin_cfg + SSD2828_CS, 0);

	gpio_set(ssd2828_pin_cfg + SSD2828_SDI, 0);			//Set DC=0, for writing to Command register
	ssd2828_pulse_clk();
	for(uint8_t i = 0; i < 8; ++i)
	{
		gpio_set(ssd2828_pin_cfg + SSD2828_SDI, cmd & 0x80);
		ssd2828_pulse_clk_hl();
		cmd = cmd << 1;
	}

	gpio_set(ssd2828_pin_cfg + SSD2828_CS, 1);
}

void writed(uint8_t cmd)
{
	uint32_t kk;

	gpio_set(ssd2828_pin_cfg + SSD2828_CS, 0);

	Set_SDI(1);			//Set DC=0, for writing to Command register
	Set_SCL(0);
	Set_SCL(1);


	Set_SCL(0);
	for(uint8_t i = 0; i < 8; ++i)
	{
		gpio_set(ssd2828_pin_cfg + SSD2828_SDI, cmd & 0x80);
		ssd2828_pulse_clk_hl();
		cmd = cmd << 1;
	}

	gpio_set(ssd2828_pin_cfg + SSD2828_CS, 1);
}

void SPI_2825_WrCmd(uint8_t cmd)
{
	uint32_t kk;

	Set_2805_CS(0);

	Set_SDI(0);			//Set DC=0, for writing to Command register
	Set_SCL(0);
	Set_SCL(1);


	Set_SCL(0);
	for(kk=0;kk<8;kk++)
	{
		if((cmd&0x80)==0x80) Set_SDI(1);
		else         Set_SDI(0);
		Set_SCL(1);
		Set_SCL(0);
		cmd = cmd<<1;
	}

	Set_2805_CS(1);
}

//void SPI_2825_WrCmd(uint8_t)
void SPI_2825_WrReg(uint8_t c,uint16_t value)
{
	Set_2805_CS(0);
	SPI_3W_SET_Cmd(c);
	SPI_3W_SET_PAs(value&0xff);
	SPI_3W_SET_PAs((value>>8)&0xff);
	Set_2805_CS(1);
}



uint8_t Read_PAs(void)
{
	uint32_t kk;
	uint8_t  rdValue;

//	Set_SCL(0);
	rdValue = 0;
	for(kk=0;kk<8;kk++)
	{
		rdValue = rdValue<<1;

		Set_SCL(1);
		if(gpio_read(ssd2828_pin_cfg + SSD2828_SDO))  rdValue |= 0x01;
		Set_SCL(0);
	}
//	Set_CSX(0);

	return rdValue;
}

uint16_t   SPI_READ(void)
{
	uint8_t  cmd,rdT;
	uint16_t reValue;
	uint32_t kk;

	Set_2805_CS(0);

	Set_SDI(0);			//Set DC=0, for writing to Command register
	Set_SCL(0);
	Set_SCL(1);


	cmd = 0xB0;
	Set_SCL(0);
	for(kk=0;kk<8;kk++)
	{
		if((cmd&0x80)==0x80) Set_SDI(1);
		else         Set_SDI(0);
		Set_SCL(1);
		Set_SCL(0);
		cmd = cmd<<1;
	}

	Set_SDI(0);			//Set DC=0, for writing to Command register
	Set_SCL(0);
	Set_SCL(1);


	cmd = 0xFA;
	Set_SCL(0);
	for(kk=0;kk<8;kk++)
	{
		if((cmd&0x80)==0x80) Set_SDI(1);
		else         Set_SDI(0);
		Set_SCL(1);
		Set_SCL(0);
		cmd = cmd<<1;
	}

	rdT=0;
	for(kk=0;kk<8;kk++)
	{
		rdT = rdT<<1;
		Set_SCL(1);
		if(gpio_read(ssd2828_pin_cfg + SSD2828_SDO)) rdT |= 0x01;
		Set_SCL(0);
	}

	reValue = rdT;
	//reValue = (reValue<<8)&0xFF00;

	rdT=0;
	for(kk=0;kk<8;kk++)
	{
		rdT = rdT<<1;
		Set_SCL(1);
		if(gpio_read(ssd2828_pin_cfg + SSD2828_SDO)) rdT |= 0x01;
		Set_SCL(0);
	}

	reValue += (rdT<<8);

	Set_2805_CS(1);

	return reValue;
}


void ssd2828_init()
{
	gpio_init(ssd2828_pin_cfg, 5);

	Set_RST(0);

	delay_ms(50);

	Set_2805_CS(1);
	Set_SCL(0);
	Set_SDI(0);
	Set_RST(1);

	delay_ms(50);
}

uint16_t   SPI_READ_ID(void)
{
	SPI_2825_WrReg(0xd4, 0x00FA);
	uint16_t id = SPI_READ();
	return id;
}

#endif /* SSD2828_H_ */

/*
 * Copyright 2017 Tommi Airikka <tommi@airikka.net>
 */

#include "yacrc16.h"


static uint16_t onebyte(uint8_t byte, uint16_t crc)
{
	int i,with_poly = 0;

	for(i=0; i<8; i++)
	{
		with_poly = crc & 0x8000;
		crc = crc << 1;
		if(byte & 0x80)
			crc = crc | 0x01;
		byte = byte << 1;
		if(with_poly)
			crc = crc ^ POLY;
	}

	return crc;
}

static uint16_t crc16(char* data, int length, uint16_t checkcrc)
{
	uint16_t crc = -1;
	int i = 0;
	uint8_t byte = 0;

	for(i=0; i < length; i++)
	{
		byte = (uint8_t)*data++;
		crc = onebyte(byte, crc);
	}

	if(checkcrc)
	{
		crc = onebyte((uint8_t)((checkcrc & 0xFF00)>>8),crc);
		crc = onebyte((uint8_t)(checkcrc & 0x00FF),crc);
	}
	else
	{
		for(i=0; i<2; i++)
			crc = onebyte(0, crc);
	}

	return crc;
	
}

uint16_t gen_crc16(char* data, int length)
{
	return crc16(data, length, 0);
}

int check_crc16(char* data, int length, uint16_t crc)
{
	return !crc16(data, length, crc);
}

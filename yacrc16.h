/*
 * Copyright 2017 Tommi Airikka <tommi@airikka.net>
 */

#ifndef YACRC16_H
#define YACRC16_H

#define POLY 0xA823

#include <stdint.h>

uint16_t gen_crc16(char* data, int length);

/* 1 if OK, 0 if NOK */
int check_crc16(char* data, int length, uint16_t crc);

#endif

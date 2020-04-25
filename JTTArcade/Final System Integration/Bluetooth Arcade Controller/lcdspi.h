/*
 * lcdspi.h
 *
 *  Created on: Dec 14, 2017
 *      Author: Tanner
 */

#ifndef LCDSPI_H_
#define LCDSPI_H_

#define LCD P3OUT
#define A0BIT  BIT2

void LCDSPI_Init(int command);
void LCDSPI_Transmit(unsigned char d);

#endif /* LCDSPI_H_ */

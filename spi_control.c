/*
 * spi_control.c
 *
 *  Created on: Jan 18, 2014
 *      Author: atching
 */

#include "altera_avalon_pio_regs.h"
#include "system.h"

void delay(int delay_time){
	int i = 0;
	int j = 0;
	for(i = 0; i < delay_time; i++){
		j++;
	}
}

void spi_send(unsigned int address, unsigned int data){
	int i = 0;

	IOWR_ALTERA_AVALON_PIO_DATA(CS_BASE, 0); // Begin
	delay(10);
	for(i = 0; i < 7; i++){
		if(address & 0x8000){
			IOWR_ALTERA_AVALON_PIO_DATA(SDIN_BASE, 1);
			//printf("1");
		}else{
			IOWR_ALTERA_AVALON_PIO_DATA(SDIN_BASE, 0);
			//printf("0");
		}
		delay(10);
		IOWR_ALTERA_AVALON_PIO_DATA(SCLK_BASE, 1);
		delay(10);
		IOWR_ALTERA_AVALON_PIO_DATA(SCLK_BASE, 0);
		delay(10);

		address <<= 1;
	}

	for(i = 0; i < 9; i++){
		if(data & 0x8000){
			IOWR_ALTERA_AVALON_PIO_DATA(SDIN_BASE, 1);
			//printf("1");
		}else{
			IOWR_ALTERA_AVALON_PIO_DATA(SDIN_BASE, 0);
			//printf("0");
		}
		IOWR_ALTERA_AVALON_PIO_DATA(SCLK_BASE, 1);
		delay(10);
		IOWR_ALTERA_AVALON_PIO_DATA(SCLK_BASE, 0);
		delay(10);

		data <<= 1;
	}

	IOWR_ALTERA_AVALON_PIO_DATA(CS_BASE, 1); // Latches word to AIC
}

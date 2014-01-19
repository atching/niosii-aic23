/*
 * spi_control.h
 *
 *  Created on: Jan 18, 2014
 *      Author: atching
 *      Organization: University of Washington Electrical Engineering
 *		Notes: Intended for use by EE443 students
 *
 *		SPI control for bit banging
 */


void delay(int delay_time);
void spi_send(unsigned int address, unsigned int data);

/*
 * aic23.c
 *
 *  Created on: Jan 18, 2014
 *      Author: atching
 *      Organization: University of Washington Electrical Engineering
 *		Notes: Intended for use by EE443 students
 *
 *  This library is used to control an TI AIC23 audio codec on an Altera AD/DA
 *  Data Conversion Card via bit banging from an Altera Cyclone IV running NIOS II.
 *  Addresses are hard coded to the locations of the control registers as stated
 *  within the datasheet.
 *
 *  Some code and constants were adapted from the datasheet and the libraries from
 *  the TI DSK6713 development board.
 *
 *  Please note that this library is not meant to be elegantly written and was written
 *  for ease of use and functionality for students not familiar with embedded systems
 *  or software coding practices.
 *
 *  Please refer to the data sheet for more info.
 *  http://www.ti.com/lit/ds/symlink/tlv320aic23b.pdf
 */

#include "aic23.h"
#include "spi_control.h"

unsigned int aic23_config[10] = {0x0017, 0x0017, 0x01f9, 0x01f9, 0x0011, 0x0000, 0x0000, 0x0043, 0x0081, 0x0001};

static int aic23_default_config[10] = {0x0017, 0x0017, 0x01f9, 0x01f9, 0x0011, 0x0000, 0x0000, 0x0043, 0x0081, 0x0001};
unsigned int aic23_demo[10] = {0x0017, 0x0217, 0x05f9, 0x07f9, 0x0839, 0x0A00, 0x0C00, 0x0E01, 0x1081, 0x1201};

// Initializes AIC to default
void AIC23_init(){
	int i = 0;
	for(i = 0; i < 10; i++){
		spi_send(i, aic23_default_config[i]);
		aic23_config[i] = aic23_default_config[i];
	}
}


/* Returns register values
   Valid Inputs:
	LEFT_LINE_VOLUME
	RIGHT_LINE_VOLUME
	LEFT_HEAD_VOLUME
	RIGHT_HEAD_VOLUME
	ANALOG_AUDIO_PATH
	DIGITAL_AUDIO_PATH
	POWER_DOWN
	DIGITAL_AUDIO_INTERFACE
	SAMPLE_RATE
	DIGITAL_INTERFACE_ACTIVATION
 */
unsigned int AIC23_read(unsigned char address){
	return aic23_config[address];
}



/////////////////////////////////////////////////////////////////
//
// 				Line Input Left Channel Volume
//
/////////////////////////////////////////////////////////////////

/* Left/right line simultaneous volume/mute update
   Valid inputs:
		ENABLED
		DISABLED
*/
void AIC23_line_lrs(unsigned int simultaneous_update){
	aic23_config[0] = (aic23_config[0] & 0x00FF) | (simultaneous_update << 8);
	spi_send(0x00, aic23_config[0]);
}

/* Left line input mute
   Valid inputs:
		NORMAL
		MUTED
*/
void AIC23_line_lim(unsigned int mute){
	aic23_config[0] = (aic23_config[0] & 0x017F) | (mute << 7);
	spi_send(0x00, aic23_config[0]);
}

/* Left line input volume control
   Valid inputs:
		0b10111 = 0dB default
		0b11111 = +12 dB down to 0b00000 = -34.5dB in 1.5dB steps
*/
void AIC23_line_liv(unsigned int volume){
	aic23_config[0] = (aic23_config[0] & 0x01E0) | (volume);
	spi_send(0x00, aic23_config[0]);
}

/////////////////////////////////////////////////////////////////
//
// 				Line Input Right Channel Volume Control
//
/////////////////////////////////////////////////////////////////

/* Right/left line simultaneous volume/mute update
   Valid inputs:
		ENABLED
		DISABLED
*/
void AIC23_line_rls(unsigned int simultaneous_update){
	aic23_config[1] = (aic23_config[1] & 0x00FF) | (simultaneous_update << 8);
	spi_send(0x01, aic23_config[1]);
}

/* Right line input mute
   Valid inputs:
		NORMAL
		MUTED
*/
void AIC23_line_rim(unsigned int mute){
	aic23_config[1] = (aic23_config[1] & 0x017F) | (mute << 7);
	spi_send(0x01, aic23_config[1]);
}

/* Right line input volume control
   Valid inputs:
		0b10111 = 0dB default
		0b11111 = +12 dB down to 0b00000 = -34.5dB in 1.5dB steps
*/
void AIC23_line_riv(unsigned int volume){
	aic23_config[1] = (aic23_config[1] & 0x01E0) | (volume);
	spi_send(0x01, aic23_config[1]);
}

/////////////////////////////////////////////////////////////////
//
// 				Headphone Left Channel Volume Control
//
/////////////////////////////////////////////////////////////////

/* Left/right headphone simultaneous volume/mute update
   Valid inputs:
		ENABLED
		DISABLED
*/
void AIC23_head_lrs(unsigned int simultaneous_update){
	aic23_config[2] = (aic23_config[2] & 0x00FF) | (simultaneous_update << 8);
	spi_send(0x02, aic23_config[2]);
}

/* Left Channel Zero-Cross Detect
   Valid inputs:
		ON
		OFF
*/
void AIC23_head_lzc(unsigned int zero){
	aic23_config[2] = (aic23_config[2] & 0x017F) | (zero << 7);
	spi_send(0x02, aic23_config[2]);
}

/* Left Headphone Volume Control
   Valid Inputs:
   	   0b1111001 = 0dB default
   	   0b1111111 = +6dB down to 0b0110000 = -73dB mute in 1dB increments
   	   Anything lower than -73dB is still mute. 79 steps in between max/min.
 */
void AIC23_head_lhv(unsigned int volume){
	aic23_config[2] = (aic23_config[2] & 0x0180) | volume;
	spi_send(0x02, aic23_config[2]);
}

/////////////////////////////////////////////////////////////////
//
// 				Headphone Right Channel Volume Control
//
/////////////////////////////////////////////////////////////////

/* Right/left headphone simultaneous volume/mute update
   Valid inputs:
		ENABLED
		DISABLED
*/
void AIC23_head_rls(unsigned int simultaneous_update){
	aic23_config[3] = (aic23_config[3] & 0x00FF) | (simultaneous_update << 8);
	spi_send(0x03, aic23_config[3]);
}

/* Right Channel Zero-Cross Detect
   Valid inputs:
		ON
		OFF
*/
void AIC23_head_rzc(unsigned int zero){
	aic23_config[3] = (aic23_config[3] & 0x017F) | ((zero & 0x01) << 7);
	spi_send(0x03, aic23_config[3]);
}

/* Right Headphone Volume Control
   Valid Inputs:
   	   0b1111001 = 0dB default
   	   0b1111111 = +6dB down to 0b0110000 = -73dB mute in 1dB increments
   	   Anything lower than -73dB is still mute. 79 steps in between max/min.
 */
void AIC23_head_rhv(unsigned int volume){
	aic23_config[3] = (aic23_config[3] & 0x0180) | volume;
	spi_send(0x03, aic23_config[3]);
}

/////////////////////////////////////////////////////////////////
//
// 					Analog Audio Path Control
//
/////////////////////////////////////////////////////////////////

void AIC23_sidetone_disable(unsigned int sidetone){
	aic23_config[4] = aic23_config[4] & 0x01DF;
	spi_send(0x04, aic23_config[4]);
}

void AIC23_sidetone_add(unsigned int add){
	aic23_config[4] = (aic23_config[4] & 0x1F) | ((add & 0x0F) << 5);
	spi_send(0x04, aic23_config[4]);
}

void AIC23_dac_select(unsigned int dac){
	aic23_config[4] = (aic23_config[4] & 0x1EF) | ((dac & 0x01) << 4);
	spi_send(0x04, aic23_config[4]);
}

/* Bypass
   Valid Inputs:
   	   ENABLED
   	   DISABLED
 */
void AIC23_bypass(unsigned int bypass){
	aic23_config[4] = (aic23_config[4] & 0x1F7) | ((bypass & 0x01) << 3);
	spi_send(0x04, aic23_config[4]);
}

void AIC23_input(unsigned int input){
	aic23_config[4] = (aic23_config[4] & 0x1FB) | ((input & 0x01) << 2);
	spi_send(0x04, aic23_config[4]);
}

void AIC23_mic_mute(unsigned int mute){
	aic23_config[4] = (aic23_config[4] & 0x1FD) | ((mute & 0x01) << 2);
	spi_send(0x04, aic23_config[4]);
}

void AIC23_mic_boost(unsigned int boost){
	aic23_config[4] = (aic23_config[4] & 0x1FE) | (boost & 0x01);
	spi_send(0x04, aic23_config[4]);
}

/////////////////////////////////////////////////////////////////
//
// 					Digital Audio Path Control
//
/////////////////////////////////////////////////////////////////

void AIC23_dac_mute(unsigned int mute){
	aic23_config[5] = (aic23_config[5] & 0x1F7) | ((mute & 0x01) << 3);
	spi_send(0x05, aic23_config[5]);
}

void AIC23_deemp(unsigned int deemphasis){
	aic23_config[5] = (aic23_config[5] & 0x01F9) | ((deemphasis & 0x03) << 1);
	spi_send(0x05, aic23_config[5]);
}

void AIC23_adc_highpass(unsigned int highpass){
	aic23_config[5] = (aic23_config[5] & 0x01FE) | (highpass & 0x01);
	spi_send(0x05, aic23_config[5]);
}

/////////////////////////////////////////////////////////////////
//
// 						Power Down Control
//
/////////////////////////////////////////////////////////////////

void AIC23_power_on(){
	aic23_config[6] = 0xFF;
	spi_send(0x06, aic23_config[6]);
}

void AIC23_power_off(){
	aic23_config[6] = 0x00;
	spi_send(0x06, aic23_config[6]);
}

/////////////////////////////////////////////////////////////////
//
// 				Digital Audio Interface Format
//
/////////////////////////////////////////////////////////////////

void AIC23_mode(unsigned int mode){
	aic23_config[7] = (aic23_config[7] & 0x01BF) | ((mode & 0x01) << 6);
	spi_send(0x07, aic23_config[7]);
}

void AIC23_lr_swap(unsigned int swap){
	aic23_config[7] = (aic23_config[7] & 0x01DF) | ((swap & 0x01) << 5);
	spi_send(0x07, aic23_config[7]);

}

void AIC23_lr_phase(unsigned int phase){
	aic23_config[7] = (aic23_config[7] & 0x01EF) | ((phase & 0x01) << 4);
	spi_send(0x07, aic23_config[7]);
}

void AIC23_input_len(unsigned int length){
	aic23_config[7] = (aic23_config[7] & 0x01F3) | ((length & 0x03) << 2);
	spi_send(0x07, aic23_config[7]);
}

void AIC23_format(unsigned int format){
	aic23_config[7] = (aic23_config[7] & 0x01FC) | (format & 0x02);
	spi_send(0x07, aic23_config[7]);
}


/////////////////////////////////////////////////////////////////
//
// 						Sample Rate Control
//
/////////////////////////////////////////////////////////////////

void AIC23_clkin(unsigned int clock){
	aic23_config[8] = (aic23_config[8] & 0x01BF) | ((clock & 0x01) << 6);
	spi_send(0x08, aic23_config[8]);
}

void AIC23_clkout(unsigned int clock){
	aic23_config[8] = (aic23_config[8] & 0x017F) | ((clock & 0x01) << 7);
	spi_send(0x08, aic23_config[8]);
}

/* Sets sample frequency
   Valid input frequencies include:
	 AIC23_FREQ_8KHZ 0x06	// 8000 Hz
	 AIC23_FREQ_16KHZ 0x2c	// 16000 Hz
	 AIC23_FREQ_24KHZ 0x20	// 24000 Hz
	 AIC23_FREQ_32KHZ 0x0c	// 32000 Hz
	 AIC23_FREQ_44KHZ 0x11	// 44100 Hz
	 AIC23_FREQ_48KHZ 0x00	// 48000 Hz
	 AIC23_FREQ_96KHZ 0x0e	// 96000 Hz
 */
void AIC23_setFreq(unsigned int frequency){
	aic23_config[8] = (aic23_config[8] & 0x1C3) | ((frequency & 0x0F) << 2);
	spi_send(0x08, aic23_config[8]);
}

void AIC23_bosr(unsigned int frequency){
	aic23_config[8] = (aic23_config[8] & 0x1FD) | ((frequency & 0x01) << 1);
	spi_send(0x08, aic23_config[8]);
}

void AIC23_clk_mode(unsigned int mode){
	aic23_config[8] = (aic23_config[8] & 0x1FE) | (mode & 0x01);
	spi_send(0x08, aic23_config[8]);
}

/////////////////////////////////////////////////////////////////
//
// 					Digital Interface Activation
//
/////////////////////////////////////////////////////////////////

// Turns the AIC23 on
void AIC23_on(){
	spi_send(0x06, 0x00);
}

// Turns the AIC23 off
void AIC23_off(){
	spi_send(0x06, 0x80);
}












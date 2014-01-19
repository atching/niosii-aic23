/*
 * aic23.c
 *
 *  Created on: Jan 18, 2014
 *      Author: atching
 *
 *  Header for the control of the AIC23 audio codec on the Altera AD/DA Daughter
 *  Card.
 *
 *  Certain code and settings taken/adapted from TI DSK6713 source libraries.
 */

#define AIC23_DEFAULT_CONFIG ;0x0017, 0x0017, 0x01f9, 0x01f9, 0x0011, 0x0000, 0x0000, 0x0043, 0x0081, 0x0001}

#define MUTE 0x01
#define NORMAL 0x00
#define ENABLED 0x01
#define DISABLED 0x00
#define ON 0x01
#define OFF 0x00
#define USB 0x01

// Look up register values
#define LEFT_LINE_VOLUME 0
#define RIGHT_LINE_VOLUME 1
#define LEFT_HEAD_VOLUME 2
#define RIGHT_HEAD_VOLUME 3
#define ANALOG_AUDIO_PATH 4
#define DIGITAL_AUDIO_PATH 5
#define POWER_DOWN 6
#define DIGITAL_AUDIO_INTERFACE 7
#define SAMPLE_RATE 8
#define DIGITAL_INTERFACE_ACTIVATION 9

// Sample Rate Control
#define AIC23_FREQ_8KHZ 0x06	// 8000 Hz
#define AIC23_FREQ_16KHZ 0x2c	// 16000 Hz
#define AIC23_FREQ_24KHZ 0x20	// 24000 Hz
#define AIC23_FREQ_32KHZ 0x0c	// 32000 Hz
#define AIC23_FREQ_44KHZ 0x11	// 44100 Hz
#define AIC23_FREQ_48KHZ 0x00	// 48000 Hz
#define AIC23_FREQ_96KHZ 0x0e	// 96000 Hz

#define DEEMPHASIS_CONTROL_OFF 0x00
#define DEEMPHASIS_CONTROL_32KHZ 0x01
#define DEEMPHASIS_CONTROL_44KHZ 0x02 // 44.1khz
#define DEEMPHASIS_CONTROL_48KHZ 0x03


// Prototypes
void AIC23_init();
unsigned int AIC23_read(unsigned char address);

void AIC23_line_lrs(unsigned int simultaneous_update);
void AIC23_line_lim(unsigned int mute);
void AIC23_line_liv(unsigned int volume);

void AIC23_line_rls(unsigned int simultaneous_update);
void AIC23_line_rim(unsigned int mute);
void AIC23_line_riv(unsigned int volume);

void AIC23_head_lrs(unsigned int simultaneous_update);
void AIC23_head_lzc(unsigned int zero);
void AIC23_head_lhv(unsigned int volume);

void AIC23_head_rls(unsigned int simultaneous_update);
void AIC23_head_rzc(unsigned int zero);
void AIC23_head_rhv(unsigned int volume);

void AIC23_sidetone_disable(unsigned int sidetone);
void AIC23_sidetone_add(unsigned int add);
void AIC23_dac_select(unsigned int dac);
void AIC23_bypass(unsigned int bypass);
void AIC23_input(unsigned int input);
void AIC23_mic_mute(unsigned int mute);
void AIC23_mic_boost(unsigned int boost);

void AIC23_dac_mute(unsigned int mute);
void AIC23_deemp(unsigned int deemphasis);
void AIC23_adc_highpass(unsigned int highpass);

void AIC23_power_on();
void AIC23_power_off();

void AIC23_mode(unsigned int mode);
void AIC23_lr_swap(unsigned int swap);
void AIC23_lr_phase(unsigned int phase);
void AIC23_input_len(unsigned int length);
void AIC23_format(unsigned int format);

void AIC23_clkin(unsigned int clock);
void AIC23_clkout(unsigned int clock);
void AIC23_setFreq(unsigned int frequency);
void AIC23_bosr(unsigned int frequency);
void AIC23_clk_mode(unsigned int mode);

void AIC23_on();
void AIC23_off();


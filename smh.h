#pragma once

#include "stdafx.h"

#ifndef EMS_TEST_H_INCLUDED
#define EMS_TEST_H_INCLUDED
#include "EMS Test.h"
#endif // !EMS_TEST_H_INCLUDED

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED
#include "display.h"
#endif // !DISPLAY_H_INCLUDED


int board_index = 0;
int smh;
void smh_initialization();
void GpibError(char *msg);
void smh_unitialization();
void smh_generate(unsigned long long freq, std::string modulation_type, int modulation_depth, int mod_freq, double voltage);
int print_digit(int digits, unsigned long long val, int n, int z);
void smh_change_level_no_modulation(double level);

void smh_initialization() {
	smh = ibdev(						 /* Create a unit descriptor handle         */
		0,								/* Board Index (GPIB0 = 0, GPIB1 = 1, ...) */
		smh_primary_address,             /* Device primary address                  */
		0,								/* Device secondary address                */
		T10s,                            /* Timeout setting (T10s = 10 seconds)     */
		1,                               /* Assert EOI line at end of write         */
		0);                              /* EOS termination mode                    */
	if (ibsta & ERR) {                   /* Check for GPIB Error                    */
		exit_error("Connection with SMH: Failure\nPlease make sure there is a GPIB connection and the device is switched on.");
		Sleep(4000);
		GpibError("ibdev Error");
	}
	Sleep(250);
	ibclr(smh);						     /* Clear the device                        */
	if (ibsta & ERR) {
		GpibError("ibclr Error");
	}
	Sleep(250);
	ibwrt(smh, "*RST", 3);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
	Sleep(50);
}
void smh_unitialization() {
	ibonl(smh, 0);						 /* Take the device offline                 */
	if (ibsta & ERR) {
		GpibError("ibonl Error");
	}
}
void smh_generate(unsigned long long freq, std::string modulation_type, int modulation_depth, int mod_freq, double voltage) {
	if (modulation_type == "AM" || modulation_type == "am") {
		int digits = mod_freq > 0 ? (int) log10 ((double) mod_freq) + 1 : 1;
		char input[30] = { 'A','F',':' };
		unsigned long long remain = 0;
		for (int i = 3; i < (digits + 3); i++) {
			unsigned long long val = (mod_freq - remain) / (int)(pow(10, digits - i + 2));
			input[i] = (int)val + 48;
			remain += (val * (int)pow(10, digits - i + 2));
		}
		ibwrt(smh, input, digits+3);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		memset(input, '\0', sizeof(input));
		input[0] = 'A';
		input[1] = 'M';
		input[2] = ':';
		input[3] = (modulation_depth & 0xf8)/10 + 48;
		input[4] = (modulation_depth & 0x07) == 0 ? 48 : (modulation_depth & 0x07) + 48;
		ibwrt(smh, input, 5);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		memset(input, '\0', sizeof(input));
		digits = freq > 0 ? (int)log10((double)freq) + 1 : 1;
		input[0] = 'R';
		input[1] = 'F';
		input[2] = ':';
		input[3] = print_digit(digits, freq, digits, 1) + 48;
		input[4] = print_digit(digits, freq, digits - 1, 1) + 48;
		if (digits == 6) {
			input[3] = '.';
			input[4] = print_digit(digits, freq, digits, 1) + 48;
			input[5] = print_digit(digits, freq, digits - 1, 1) + 48;
			input[6] = print_digit(digits, freq, digits - 2, 1) + 48;
			input[7] = print_digit(digits, freq, digits - 3, 1) + 48;
			input[8] = print_digit(digits, freq, digits - 4, 1) + 48;
			input[9] = print_digit(digits, freq, digits - 5, 1) + 48;
		}
		if (digits == 7) {
			input[4] = '.';
			input[5] = print_digit(digits, freq, digits - 1, 1) + 48;
			input[6] = print_digit(digits, freq, digits - 2, 1) + 48;
			input[7] = print_digit(digits, freq, digits - 3, 1) + 48;
			input[8] = print_digit(digits, freq, digits - 4, 1) + 48;
			input[9] = print_digit(digits, freq, digits - 5, 1) + 48;
		}
		if (digits == 8) {
			input[5] = '.';
			input[6] = print_digit(digits, freq, digits - 2, 1) + 48;
			input[7] = print_digit(digits, freq, digits - 3, 1) + 48;
			input[8] = print_digit(digits, freq, digits - 4, 1) + 48;
			input[9] = print_digit(digits, freq, digits - 5, 1) + 48;
		}
		else if (digits == 9) {
			input[5] = print_digit(digits, freq, digits - 2, 1) + 48;
			input[6] = '.';
			input[7] = print_digit(digits, freq, digits - 3, 1) + 48;
			input[8] = print_digit(digits, freq, digits - 4, 1) + 48;
			input[9] = print_digit(digits, freq, digits - 5, 1) + 48;
		}
		else if (digits == 10) {
			input[5] = print_digit(digits, freq, digits - 2, 1) + 48;
			input[6] = print_digit(digits, freq, digits - 3, 1) + 48;
			input[7] = '.';
			input[8] = print_digit(digits, freq, digits - 4, 1) + 48;
			input[9] = print_digit(digits, freq, digits - 5, 1) + 48;
		}
		else if (digits == 11) {
			input[5] = print_digit(digits, freq, digits - 2, 1) + 48;
			input[6] = print_digit(digits, freq, digits - 3, 1) + 48;
			input[7] = print_digit(digits, freq, digits - 4, 1) + 48;
			input[8] = '.';
			input[9] = print_digit(digits, freq, digits - 5, 1) + 48;
		}
		
		input[10] = 'M';
		input[11] = 'H';
		input[12] = 'z';
		ibwrt(smh, input, 13);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		memset(input, '\0', sizeof(input));
		input[0] = 'L';
		input[1] = 'E';
		input[2] = 'V';
		input[3] = 'E';
		input[4] = 'L';
		input[5] = ':';
		input[6] = 'R';
		input[7] = 'F';
		digits = voltage > 0 ? (int)log10((double)voltage) + 1 : 1;
		remain = 0;
		if (voltage >= 0) {
			input[8] = (int)abs(voltage) / 10 - ((int)abs(voltage) % 10) / 10 + 48;
			input[9] = ((int)abs(voltage) % 10) + 48;
			input[10] = '.';
			input[11] = (int)(((int)(abs(voltage*10)) % 10)) + 48;
			input[12] = (int)((((int)(abs(voltage*100)) % 10))) + 48;
			input[13] = 'd';
			input[14] = 'B';
			input[15] = 'm';
			ibwrt(smh, input, 16);
			if (ibsta & ERR) {
				GpibError("ibwrt Error");
			}
		}
		if (voltage < 0) {
			input[8] = '-';
			input[9] = (int)abs(voltage) / 10 - ((int)abs(voltage) % 10) / 10 + 48;
			input[10] = ((int)abs(voltage) % 10) + 48;
			input[11] = '.';
			input[12] = (int)(((int)(abs(voltage * 10)) % 10)) + 48;
			input[13] = (int)((((int)(abs(voltage * 100)) % 10))) + 48;
			input[14] = 'd';
			input[15] = 'B';
			input[16] = 'm';
			ibwrt(smh, input, 17);
			if (ibsta & ERR) {
				GpibError("ibwrt Error");
			}
		}
	}
	if (modulation_type == "NONE" || modulation_type == "none" || modulation_type == "NO" || modulation_type == "no") {
		ibwrt(smh, "AM:OFF", 6);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		int digits = freq > 0 ? (int)log10((double)freq) + 1 : 1;
		char input[30] = { 'R','F',':' };
		input[3] = print_digit(digits, freq, digits, 1) + 48;
		input[4] = print_digit(digits, freq, digits - 1, 1) + 48;
		if (digits == 6) {
			input[3] = '.';
			input[4] = print_digit(digits, freq, digits, 1) + 48;
			input[5] = print_digit(digits, freq, digits - 1, 1) + 48;
			input[6] = print_digit(digits, freq, digits - 2, 1) + 48;
			input[7] = print_digit(digits, freq, digits - 3, 1) + 48;
			input[8] = print_digit(digits, freq, digits - 4, 1) + 48;
			input[9] = print_digit(digits, freq, digits - 5, 1) + 48;
		}
		if (digits == 7) {
			input[4] = '.';
			input[5] = print_digit(digits, freq, digits - 1, 1) + 48;
			input[6] = print_digit(digits, freq, digits - 2, 1) + 48;
			input[7] = print_digit(digits, freq, digits - 3, 1) + 48;
			input[8] = print_digit(digits, freq, digits - 4, 1) + 48;
			input[9] = print_digit(digits, freq, digits - 5, 1) + 48;
		}
		if (digits == 8) {
			input[5] = '.';
			input[6] = print_digit(digits, freq, digits - 2, 1) + 48;
			input[7] = print_digit(digits, freq, digits - 3, 1) + 48;
			input[8] = print_digit(digits, freq, digits - 4, 1) + 48;
			input[9] = print_digit(digits, freq, digits - 5, 1) + 48;
		}
		else if (digits == 9) {
			input[5] = print_digit(digits, freq, digits - 2, 1) + 48;
			input[6] = '.';
			input[7] = print_digit(digits, freq, digits - 3, 1) + 48;
			input[8] = print_digit(digits, freq, digits - 4, 1) + 48;
			input[9] = print_digit(digits, freq, digits - 5, 1) + 48;
		}
		else if (digits == 10) {
			input[5] = print_digit(digits, freq, digits - 2, 1) + 48;
			input[6] = print_digit(digits, freq, digits - 3, 1) + 48;
			input[7] = '.';
			input[8] = print_digit(digits, freq, digits - 4, 1) + 48;
			input[9] = print_digit(digits, freq, digits - 5, 1) + 48;
		}
		else if (digits == 11) {
			input[5] = print_digit(digits, freq, digits - 2, 1) + 48;
			input[6] = print_digit(digits, freq, digits - 3, 1) + 48;
			input[7] = print_digit(digits, freq, digits - 4, 1) + 48;
			input[8] = '.';
			input[9] = print_digit(digits, freq, digits - 5, 1) + 48;
		}
		input[10] = 'M';
		input[11] = 'H';
		input[12] = 'z';
		ibwrt(smh, input, 13);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		memset(input, '\0', sizeof(input));
		input[0] = 'L';
		input[1] = 'E';
		input[2] = 'V';
		input[3] = 'E';
		input[4] = 'L';
		input[5] = ':';
		input[6] = 'R';
		input[7] = 'F';
		if (voltage >= 0) {
			input[8] = (int)abs(voltage) / 10 - ((int)abs(voltage) % 10) / 10 + 48;
			input[9] = ((int)abs(voltage) % 10) + 48;
			input[10] = '.';
			input[11] = (int)(((int)(abs(voltage * 10)) % 10)) + 48;
			input[12] = (int)((((int)(abs(voltage * 100)) % 10))) + 48;
			input[13] = 'd';
			input[14] = 'B';
			input[15] = 'm';
			ibwrt(smh, input, 16);
			if (ibsta & ERR) {
				GpibError("ibwrt Error");
			}
		}
		if (voltage < 0) {
			input[8] = '-';
			input[9] = (int)abs(voltage) / 10 - ((int)abs(voltage) % 10) / 10 + 48;
			input[10] = ((int)abs(voltage) % 10) + 48;
			input[11] = '.';
			input[12] = (int)(((int)(abs(voltage * 10)) % 10)) + 48;
			input[13] = (int)((((int)(abs(voltage * 100)) % 10))) + 48;
			input[14] = 'd';
			input[15] = 'B';
			input[16] = 'm';
			ibwrt(smh, input, 17);
			if (ibsta & ERR) {
				GpibError("ibwrt Error");
			}
		}
	}
}
int print_digit(int digits, unsigned long long val, int n, int z) {
	if (n == z) {
		return (int)(val % 10);
	}
	print_digit(digits, val / 10, n, z + 1);
}
void smh_change_level_no_modulation(double level) {
	char input[40];
	input[0] = 'L';
	input[1] = 'E';
	input[2] = 'V';
	input[3] = 'E';
	input[4] = 'L';
	input[5] = ':';
	input[6] = 'R';
	input[7] = 'F';
	int digits = level > 0 ? (int)log10((double)level) + 1 : 1;
	if (level >= 0) {
		input[8] = (int)abs(level) / 10 - ((int)abs(level) % 10) / 10 + 48;
		input[9] = ((int)abs(level) % 10) + 48;
		input[10] = '.';
		input[11] = (int)(((int)(abs(level * 10)) % 10)) + 48;
		input[12] = (int)((((int)(abs(level * 100)) % 10))) + 48;
		input[13] = 'd';
		input[14] = 'B';
		input[15] = 'm';
		ibwrt(smh, input, 16);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
	}
	if (level < 0) {
		input[8] = '-';
		input[9] = (int)abs(level) / 10 - ((int)abs(level) % 10) / 10 + 48;
		input[10] = ((int)abs(level) % 10) + 48;
		input[11] = '.';
		input[12] = (int)(((int)(abs(level * 10)) % 10)) + 48;
		input[13] = (int)((((int)(abs(level * 100)) % 10))) + 48;
		input[14] = 'd';
		input[15] = 'B';
		input[16] = 'm';
		ibwrt(smh, input, 17);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
	}
}
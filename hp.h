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



int hp;
void hp_initialization();
void hp_unitialization();
void hp_generate(unsigned long long freq, std::string modulation_type, int modulation_depth, int modulation_frequency, double voltage);
void hp_change_level_no_modulation(double voltage);

void hp_initialization() {

	hp = ibdev(						 /* Create a unit descriptor handle         */
		0,					 /* Board Index (GPIB0 = 0, GPIB1 = 1, ...) */
		hp_primary_address,             /* Device primary address                  */
		0,           /* Device secondary address                */
		T10s,                            /* Timeout setting (T10s = 10 seconds)     */
		1,                               /* Assert EOI line at end of write         */
		0);                              /* EOS termination mode                    */
	if (ibsta & ERR) {                   /* Check for GPIB Error                    */
		exit_error("Connection with HP-IB 8341B: Failure\nPlease make sure there is a GPIB connection and the device is switched on.");
		Sleep(4000);
		GpibError("ibdev Error");
	}
	Sleep(250);
	ibclr(hp);						     /* Clear the device                        */
	if (ibsta & ERR) {
		GpibError("ibclr Error");
	}
	Sleep(250);
}
void hp_unitialization() {
	ibonl(hp, 0);						 /* Take the device offline                 */
	if (ibsta & ERR) {
		GpibError("ibonl Error");
	}
}
void hp_generate(unsigned long long freq, std::string modulation_type, int modulation_depth, int modulation_frequency, double voltage) {
	if (modulation_type == "am" || modulation_type == "AM") {
		afg_generate(volts_to_dBm(dBm_to_volts(voltage)*modulation_depth/100));
		ibwrt(hp, "AM1", 3);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
	}
	else {
		ibwrt(hp, "AM0", 3);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
	}
	char input[30];
	ibwrt(hp, "RF1", 3);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
	input[0] = 'P';
	input[1] = 'L';
	input[2] = ' ';
	if (voltage >= 0) {
		input[3] = (int)abs(voltage) / 10 - ((int)abs(voltage) % 10) / 10 + 48;
		input[4] = ((int)abs(voltage) % 10) + 48;
		input[5] = '.';
		input[6] = (int)(((int)(abs(voltage * 10)) % 10)) + 48;
		input[7] = (int)((((int)(abs(voltage * 100)) % 10))) + 48;
		input[8] = ' ';
		input[9] = 'D';
		input[10] = 'B';
		ibwrt(smh, input, 11);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
	}
	if (voltage < 0) {
		input[3] = '-';
		input[4] = (int)abs(voltage) / 10 - ((int)abs(voltage) % 10) / 10 + 48;
		input[5] = ((int)abs(voltage) % 10) + 48;
		input[6] = '.';
		input[7] = (int)(((int)(abs(voltage * 10)) % 10)) + 48;
		input[8] = (int)((((int)(abs(voltage * 100)) % 10))) + 48;
		input[9] = ' ';
		input[10] = 'D';
		input[11] = 'B';
		ibwrt(smh, input, 12);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
	}
	memset(input, '\0', sizeof(input));
	int digits = freq > 0 ? (int)log10((double)freq) + 1 : 1;
	input[0] = 'C';
	input[1] = 'W';
	input[2] = ' ';
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
	input[10] = ' ';
	input[11] = 'M';
	input[12] = 'Z';
	ibwrt(smh, input, 13);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
}
void hp_change_level_no_modulation(double voltage) {
	ibwrt(hp, "AM0", 3);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
	char input[30];
	ibwrt(hp, "RF1", 3);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
	input[0] = 'P';
	input[1] = 'L';
	input[2] = ' ';
	if (voltage >= 0) {
		input[3] = (int)abs(voltage) / 10 - ((int)abs(voltage) % 10) / 10 + 48;
		input[4] = ((int)abs(voltage) % 10) + 48;
		input[5] = '.';
		input[6] = (int)(((int)(abs(voltage * 10)) % 10)) + 48;
		input[7] = (int)((((int)(abs(voltage * 100)) % 10))) + 48;
		input[8] = ' ';
		input[9] = 'D';
		input[10] = 'B';
		ibwrt(smh, input, 11);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
	}
	if (voltage < 0) {
		input[3] = '-';
		input[4] = (int)abs(voltage) / 10 - ((int)abs(voltage) % 10) / 10 + 48;
		input[5] = ((int)abs(voltage) % 10) + 48;
		input[6] = '.';
		input[7] = (int)(((int)(abs(voltage * 10)) % 10)) + 48;
		input[8] = (int)((((int)(abs(voltage * 100)) % 10))) + 48;
		input[9] = ' ';
		input[10] = 'D';
		input[11] = 'B';
		ibwrt(smh, input, 12);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
	}
}
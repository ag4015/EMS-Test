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





int afg;
void afg_initialization();
void afg_unitialization();
void afg_generate(double level);
double dBm_to_volts(double val);
double volts_to_dBm(double val);
void afg_change_frequency(int freq);


void afg_initialization() {

	afg = ibdev(						 /* Create a unit descriptor handle         */
		0,					 /* Board Index (GPIB0 = 0, GPIB1 = 1, ...) */
		afg_primary_address,             /* Device primary address                  */
		0,           /* Device secondary address                */
		T10s,                            /* Timeout setting (T10s = 10 seconds)     */
		1,                               /* Assert EOI line at end of write         */
		0);                              /* EOS termination mode                    */
	if (ibsta & ERR) {                   /* Check for GPIB Error                    */
		exit_error("Connection with AFG: Failure\nPlease make sure there is a GPIB connection and the device is switched on.");
		Sleep(4000);
		GpibError("ibdev Error");
	}
	Sleep(250);
	ibclr(afg);						     /* Clear the device                        */
	if (ibsta & ERR) {
		GpibError("ibclr Error");
	}
	Sleep(250);
}
void afg_unitialization() {
	ibonl(afg, 0);						 /* Take the device offline                 */
	if (ibsta & ERR) {
		GpibError("ibonl Error");
	}
}
void afg_generate(double level) {
	voltage_afg = dBm_to_volts(level);
	if (voltage_afg < 0.006) {
		return;
	}
	char input[50];
	input[0] = 'L';
	input[1] = 'E';
	input[2] = 'V';
	input[3] = 'E';
	input[4] = 'L';
	input[5] = '(';
	input[6] = 'P';
	input[7] = 'P';
	input[8] = ')';
	input[9] = ' ';
	if (voltage_afg == 10) {
		input[10] = '1';
		input[11] = '0';
		ibwrt(afg, input, 12);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
	}
	else {
		input[10] = (int)(((int)voltage_afg) % 10) + 48;
		input[11] = '.';
		input[12] = (int)(voltage_afg * 10) % 10 + 48;
		input[13] = (int)(voltage_afg * 100) % 10 + 48;
		input[14] = (int)(voltage_afg * 1000) % 10 + 48;
		input[15] = (int)(voltage_afg * 10000) % 10 + 48;
		ibwrt(afg, input, 16);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
	}
}
void afg_change_frequency(int freq) {
	char input[40];
	input[0] = 'F';
	input[1] = 'R';
	input[2] = 'E';
	input[3] = 'Q';
	input[4] = 'U';
	input[5] = 'E';
	input[6] = 'N';
	input[7] = 'C';
	input[8] = 'Y';
	input[9] = '(';
	input[10] = '1';
	input[11] = ')';
	input[12] = ' ';
	input[13] = (int)(freq / 1000) + 48;
	input[14] = (freq / 100) % 10 + 48;
	input[15] = (freq / 10) % 10 + 48;
	input[16] = freq % 10 + 48;
	input[17] = 'E';
	input[18] = '0';
  	ibwrt(afg, input, 19);
	if (ibsta & ERR) {
	GpibError("ibwrt Error");
	}
}
double dBm_to_volts(double val) {
	double value = sqrt(0.05*pow(10, val / 10));
	return value;
}
double volts_to_dBm(double val) {
	double value =  10 * log10(((val / 50) * (val / 50)) * 50 * 1000);
	return value;
}
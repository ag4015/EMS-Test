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


void urv5_initialization();
double urv5_measure_2(char sel);
void urv5_unitialization();


int urv5 = 0;



void urv5_initialization() {
	ibrsc(0, 1);
	ibsic(0);
	urv5 = ibdev(                /* Create a unit descriptor handle         */
		0,              /* Board Index (GPIB0 = 0, GPIB1 = 1, ...) */
		urv5_primary_address,          /* Device primary address                  */
		0,						/* Device secondary address                */
		T10s,                    /* Timeout setting (T10s = 10 seconds)     */
		1,                       /* Assert EOI line at end of write         */
		0);                      /* EOS termination mode                    */
	if (ibsta & ERR) {             /* Check for GPIB Error                    */
		exit_error("Connection with URV5: Failure\nPlease make sure there is a GPIB connection and the device is switched on.");
		Sleep(4000);
		GpibError("ibdev Error");
	}
	ibclr(urv5);                 /* Clear the device                        */
	if (ibsta & ERR) {
		GpibError("ibclr Error");
	}
	ibwrt(urv5, "C0", 2);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
	std::cout << "URV5 reset\n";
	ibwrt(urv5, "F3", 2);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
	ibwrt(urv5, "PB", 2);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
	ibwrt(urv5, "U1", 2);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
	ibwrt(urv5, "X4", 2);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
}
void urv5_unitialization() {
	ibonl(urv5, 0);              /* Take the device offline                 */
	if (ibsta & ERR) {
		GpibError("ibonl Error");
	}
}
double urv5_measure_2(char sel) {
	if (sel == 'b' || sel == 'B') {
		ibwrt(urv5, "PB", 2);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		ibwrt(urv5, "U1", 2);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		ibrd(urv5, Buffer, 20);
		if (ibsta & ERR) {
			GpibError("ibrd Error");
		}
		Buffer[19] = '\0';
		double a = (Buffer[10] - 48);
		if (a < 0) {
			a = 0;
		}
		double b = (Buffer[11] - 48);
		if (b < 0) {
			b = 0;
		}
		double v =  (a*10 + b + (Buffer[13] - 48) * 0.1 + (Buffer[14] - 48)*0.01);
		if (Buffer[9] = '-') {
			v *= -1;
		}
		return v;
	}
	if (sel == 'a' || sel == 'A') {
		ibwrt(urv5, "PA", 2);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		ibwrt(urv5, "U1", 2);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		ibrd(urv5, Buffer, 20);
		if (ibsta & ERR) {
			GpibError("ibrd Error");
		}
		Buffer[19] = '\0';
		double a = (Buffer[10] - 48);
		if (a < 0) {
			a = 0;
		}
		double b = (Buffer[11] - 48);
		if (b < 0) {
			b = 0;
		}
		double v = (a * 10 + b + (Buffer[13] - 48) * 0.1 + (Buffer[14] - 48)*0.01);
		if (Buffer[9] = '-') {
			v *= -1;
		}
		return attenuation + v;
	}
}
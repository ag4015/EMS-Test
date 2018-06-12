#pragma once
#include "stdafx.h"

#ifndef CMATH_INCLUDED
#define CMATH_INCLUDED
#include <cmath>
#endif // !CMATH_INCLUDED

#ifndef CTIME_INCLUDED
#define CTIME_INCLUDED
#include <ctime>
#endif // !CTIME_INCLUDED

#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED
#include "time.h"
#endif // !CTIME_INCLUDED

#ifndef STRING_INCLUDED
#define STRING_INCLUDED
#include <string>
#endif // !STRING_INCLUDED

#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED
#include <vector>
#endif // !VECTOR_INCLUDED

#ifndef FSTREAM_INCLUDED
#define FSTREAM_INCLUDED
#include <fstream>
#endif // !FSTREAM_INCLUDED

#ifndef IOSTREAM_INCLUDED
#define IOSTREAM_INCLUDED
#include <iostream>
#endif // !IOSTREAM_INCLUDED

#ifndef NI488_H_INCLUDED
#define NI488_H_INCLUDED
#include "ni488.h"
#endif // !NI_H_INCLUDED

#ifndef GNUPLOT_I_HPP_INCLUDED
#define GNUPLOT_I_HPP_INCLUDED
#include "gnuplot_i.hpp"
#endif	// !GNUPLOT_I_HPP_INCLUDED

#ifndef SSTREAM_INCLUDED
#define SSTREAM_INCLUDED
#include <sstream>
#endif // !SSTREAM_INCLUDED

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED
#include "display.h"
#endif // !DISPLAY_H_INCLUDED

#ifndef CSTDLIB_H_INCLUDED
#define CSTDLIB_H_INCLUDED
#include <cstdlib>
#endif // !CSTDLIB_H_INCLUDED







#define BOARD_INDEX 0;
#define GPIB0 0
#define INITIAL_VOLTAGE -20


// The number of clock ticks per second
#define CLOCKS_PER_SEC  ((clock_t)1000)
#define ERR     (1<<15) /* Error detected                   */

// Determine which amplifiers to use

bool amp_1 = true;
bool amp_2 = true;
bool amp_3 = true;
bool amp_4 = true;
bool amp_5 = true;
bool amp_6 = true;
bool amp_7 = true;
int current_amplifier;
bool want_to_measure = false;
bool want_to_plot = true;
bool want_to_test = false;
bool want_vout = false;
bool want_gain = false;
bool measurement_done = false;
std::string file_name = "Initial Test";
std::string current_path = "C:/Users/Admin/Documents/EMS/Projects/";


// Define minimum frequency for correct amplification for each amplifier

unsigned long long min_freq_amp_1 = 1000000;	    // 1000 KHz	ANP RES 100L
unsigned long long min_freq_amp_2 = 100000000;	// 100 MHz	EATON
unsigned long long min_freq_amp_3 = 500000000;	// 500 MHz	BONN
unsigned long long min_freq_amp_4 = 1000000000;	// 1 GHz	Hughes (1-2 GHz)
unsigned long long min_freq_amp_5 = 2000000000;	// 2 GHz	Hughes (2-4 GHz)
unsigned long long min_freq_amp_6 = 4000000000;	// 4 GHz	Hughes (4-8 GHz)
unsigned long long min_freq_amp_7 = 8000000000;	// 8 GHz	Hughes (8-18 GHz)

												// Define maximum frequency for correct amplification for each amplifier

unsigned long long max_freq_amp_1 = 200000000;   // 200 Mhz	ANP RES 100L
unsigned long long max_freq_amp_2 = 512000000;	// 512 MHz	EATON
unsigned long long max_freq_amp_3 = 1000000000;	// 1 GHz	BONN
unsigned long long max_freq_amp_4 = 2000000000;	// 2 GHz	Hughes (1-2 GHz)
unsigned long long max_freq_amp_5 = 4000000000;	// 4 GHz	Hughes (2-4 GHz)
unsigned long long max_freq_amp_6 = 8000000000;	// 8 GHz	Hughes (4-8 GHz)
unsigned long long max_freq_amp_7 = 18000000000;	// 18 GHz	Hughes (8-18 GHz)

													// Define maximum input voltage to amplifiers

int max_voltage_amp_1 = 0;
int max_voltage_amp_2 = -14;
int max_voltage_amp_3 = 0;
int max_voltage_amp_4 = 0;
int max_voltage_amp_5 = 0;
int max_voltage_amp_6 = 0;
int max_voltage_amp_7 = 0;



// Determine frequency range of measurement for the whole test and each amplifier

unsigned long long initial_frequency = 80 * (unsigned long long)pow(10, 6);	//Hz
unsigned long long final_frequency = 18 * (unsigned long long)pow(10, 9);			//Hz
unsigned long long initial_frequency_amp_1 = initial_frequency;
unsigned long long initial_frequency_amp_2 = max_freq_amp_1;
unsigned long long initial_frequency_amp_3 = max_freq_amp_2;
unsigned long long initial_frequency_amp_4 = max_freq_amp_3;
unsigned long long initial_frequency_amp_5 = max_freq_amp_4;
unsigned long long initial_frequency_amp_6 = max_freq_amp_5;
unsigned long long initial_frequency_amp_7 = max_freq_amp_6;
unsigned long long final_frequency_amp_1 = max_freq_amp_1;
unsigned long long final_frequency_amp_2 = max_freq_amp_2;
unsigned long long final_frequency_amp_3 = max_freq_amp_3;
unsigned long long final_frequency_amp_4 = max_freq_amp_4;
unsigned long long final_frequency_amp_5 = max_freq_amp_5;
unsigned long long final_frequency_amp_6 = max_freq_amp_6;
unsigned long long final_frequency_amp_7 = max_freq_amp_7;

// Define the names of the amplifiers

std::string amplifier_name_1 = "AMP RES 100L";
std::string amplifier_name_2 = "EATON";
std::string amplifier_name_3 = "BONN";
std::string amplifier_name_4 = "Hughes (1-2 GHz)";
std::string amplifier_name_5 = "Hughes (2-4 GHz)";
std::string amplifier_name_6 = "Hughes (4-8 GHz)";
std::string amplifier_name_7 = "Hughes (8-18 GHz)";


int urv5_primary_address = 1;
int hp_primary_address = 10;
int afg_primary_address = 3;
int smh_primary_address = 2;
int emco_primary_address = 15;
int urv5_2_primary_address = 6;

double field_at_eut = 10;					    // V/m
int modulation_depth = 80;						// %
int dwell_time = 2000;
int carrier_frequency = 1000;
double voltage_afg;

void exit_error(std::string some_error);
void exit_error(std::string some_error) {
	int smh = ibdev(0, smh_primary_address, 0, T10s, 1, 0);
	int hp = ibdev(0, smh_primary_address, 0, T10s, 1, 0);
	int afg = ibdev(0, afg_primary_address, 0, T10s, 1, 0);
	int urv5 = ibdev(0, urv5_primary_address, 0, T10s, 1, 0);
	int emco_unit = ibdev(0, emco_primary_address, 0, T10s, 1, 0);
	ibwrt(smh, "LEVEL:OFF", 9);
	ibwrt(hp, "RF0", 3);
	display_message(some_error, "Error");
	ibonl(hp, 0);
	ibonl(smh, 0);
	ibonl(afg, 0);
	ibonl(urv5, 0);
	ibonl(emco_unit, 0);
	exit(EXIT_FAILURE);
}
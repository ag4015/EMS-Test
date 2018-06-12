#pragma once

#include "stdafx.h"

#ifndef EMS_TEST_H_INCLUDED
#define EMS_TEST_H_INCLUDED
#include "EMS Test.h"
#endif // !EMS_TEST_H_INCLUDED

#ifndef SMH_H_INCLUDED
#define SMH_H_INCLUDED
#include "smh.h"
#endif	//!SMH_H_INCLUDED

#ifndef EMCO_H_INCLUDED
#define EMCO_H_INCLUDED
#include "emco.h"
#endif // !EMCO_H_INCLUDED

#ifndef URV5_H_INCLUDED
#define URV5_H_INCLUDED
#include "urv5.h"
#endif	// !URV5_H_INCLUDED

#ifndef AFG_H_INCLUDED
#define AFG_H_INCLUDED
#include "afg.h"
#endif	//	!AFG_H_INCLUDED

#ifndef HP_H_INCLUDED
#define HP_H_INCLUDED
#include "hp.h"
#endif	//	!HP_H_INCLUDED

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED
#include "display.h"
#endif // !DISPLAY_H_INCLUDED



// FUNCTION DEFINITION


void run_measurement();
void gpib_configuration();
std::string obtain_used_amplifiers();

// Determines in a log scale which are the measurement frequencies

void frequency_steps(int& number_steps, unsigned long long initial_frequency, unsigned long long final_frequency, std::vector<unsigned long long>& meas_freq);

// Use gnuplot to plot data and store it

void plot(std::string which_plot);

// Change output voltage of SMH to match required electric field strength

void correct_field_1(double field_at_eut, int i, double& ref_voltage, int modulation_depth, int carrier_frequency, double& vin, double& meas_field);
void correct_field_2(double field_at_eut, int i, double& ref_voltage, int modulation_depth, int carrier_frequency, double& meas_field);
// Determine with initial and final frequencies which amplifiers to use

void det_amp();


void run_measurement() {
	int number_steps;
	double total_time = 0;
	unsigned int i = 0;
	bool do_once = true;
	unsigned int index_of_vector = 0;
	std::string key;
	bool configure_amplifiers = true;
	double ref_voltage = INITIAL_VOLTAGE;						// dBm						//3 seconds of dwell time
	gpib_configuration();
	initial_configuration();
	display_message("Place required field sensor in the desired location and connect it to EMCO.");
	emco_initialization();
	emco_default_configuration();
	Sleep(2000);
	if (amp_1 || amp_2 || amp_3) {
		display_message("Switch on SMH and URV5.\nConnect Output of SMH to URV5 channel B (Right)\nConnect IEEE (GPIB) cables to the computer (but not the optical extension)");
		smh_initialization();
		urv5_initialization();
	}

	// AMPLIFIER 1

	if (amp_1 == true) {

		ref_voltage = INITIAL_VOLTAGE;
		display_message("\nInsert SMH output to " + amplifier_name_1 + ".");
		current_amplifier = 1;
		gpib_configuration();
		emco_initialization();
		smh_initialization();
		urv5_initialization();
		frequency_steps(number_steps, initial_frequency_amp_1, final_frequency_amp_1, meas.frequency);
		smh_generate(initial_frequency_amp_1, "NONE", modulation_depth, carrier_frequency, ref_voltage);
		total_time = 0;

		while (i < meas.frequency.size() && meas.frequency[i] < final_frequency_amp_1) {

			double meas_field, vin = 0;
			clock_t begin = std::clock();
			if (do_once) {
				do_once = false;
				correct_field_1(field_at_eut, i, ref_voltage, modulation_depth, carrier_frequency, vin, meas_field);
			}

			smh_generate(meas.frequency[i], "NONE", modulation_depth, carrier_frequency, ref_voltage);
			Sleep(100);
			correct_field_1(field_at_eut, i, ref_voltage, modulation_depth, carrier_frequency, vin, meas_field);
			if (want_vout) {
				double vout, gain;
				vout = urv5_measure_2('A');
				meas.voltage_output_amplifier.push_back(vout);
				if (want_gain) {
					gain = vout - vin;
					meas.gain.push_back(gain);
				}
			}
			clock_t end = std::clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			total_time += elapsed_secs;
			meas.field.push_back(meas_field);
			meas.voltage_smh.push_back(ref_voltage);
			meas.voltage_input_amplifier.push_back(vin);
			i++;
		}


		//****************************************************************************//
		//								SWITCH OFF									 //
		//****************************************************************************//


		ibwrt(smh, "LEVEL:OFF", 9);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		Sleep(100);
		index_of_vector = emco_print_measurements_amp_1(index_of_vector);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		std::ostringstream sstream1;
		sstream1 << total_time/60;
		std::string string1 = sstream1.str();
		display_message("Stage of measurement completed.\nInput to " + amplifier_name_1 + " is now OFF.\nSwitch off " + amplifier_name_1 + ".\nTotal time taken: " + string1 + " minutes.");
		do_once = true;
		/*smh_unitialization();*/
	}

	// AMPLIFIER 2

	if (amp_2 == true) {

		ref_voltage = INITIAL_VOLTAGE;
		display_message("\nInsert SMH output to " + amplifier_name_2 + ".");
		current_amplifier = 2;
		gpib_configuration();
		emco_initialization();
		smh_initialization();
		urv5_initialization();
		frequency_steps(number_steps, initial_frequency_amp_2, final_frequency_amp_2, meas.frequency);
		smh_generate(initial_frequency_amp_2, "NONE", modulation_depth, carrier_frequency, ref_voltage);
		total_time = 0;

		while (i < meas.frequency.size() && meas.frequency[i] < final_frequency_amp_2) {

			double meas_field, vin = 0;
			clock_t begin = std::clock();
			if (do_once) {
				do_once = false;
				correct_field_1(field_at_eut, i, ref_voltage, modulation_depth, carrier_frequency, vin, meas_field);
			}

			smh_generate(meas.frequency[i], "NONE", modulation_depth, carrier_frequency, ref_voltage);
			Sleep(100);
			correct_field_1(field_at_eut, i, ref_voltage, modulation_depth, carrier_frequency, vin, meas_field);
			if (want_vout) {
				double vout, gain;
				vout = urv5_measure_2('A');
				meas.voltage_output_amplifier.push_back(vout);
				gain = vout - vin;
				meas.gain.push_back(gain);
			}
			clock_t end = std::clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			total_time += elapsed_secs;
			meas.field.push_back(meas_field);
			meas.voltage_smh.push_back(ref_voltage);
			meas.voltage_input_amplifier.push_back(vin);
			i++;
		}
		//****************************************************************************//
		//								SWITCH OFF									  //
		//****************************************************************************//
		ibwrt(smh, "LEVEL:OFF", 9);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		Sleep(100);
		index_of_vector = emco_print_measurements_amp_2(index_of_vector);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		std::ostringstream sstream1;
		sstream1 << total_time / 60;
		std::string string1 = sstream1.str();
		display_message("Stage of measurement completed.\nInput to " + amplifier_name_2 + " is now OFF.\nSwitch off " + amplifier_name_2 + ".\nTotal time taken: " + string1 + " minutes.");
		do_once = true;
		/*smh_unitialization();*/
	}

	// AMPLIFIER 3

	if (amp_3 == true) {

		ref_voltage = INITIAL_VOLTAGE;
		display_message("\nInsert SMH output to " + amplifier_name_3 + ".");
		current_amplifier = 3;
		gpib_configuration();
		emco_initialization();
		smh_initialization();
		urv5_initialization();
		frequency_steps(number_steps, initial_frequency_amp_3, final_frequency_amp_3, meas.frequency);
		smh_generate(initial_frequency_amp_3, "NONE", modulation_depth, carrier_frequency, ref_voltage);
		total_time = 0;

		while (i < meas.frequency.size() && meas.frequency[i] < final_frequency_amp_3) {

			double meas_field, vin = 0;
			clock_t begin = std::clock();
			if (do_once) {
				do_once = false;
				correct_field_1(field_at_eut, i, ref_voltage, modulation_depth, carrier_frequency, vin, meas_field);
			}

			smh_generate(meas.frequency[i], "NONE", modulation_depth, carrier_frequency, ref_voltage);
			Sleep(100);
			correct_field_1(field_at_eut, i, ref_voltage, modulation_depth, carrier_frequency, vin, meas_field);
			if (want_vout) {
				double vout, gain;
				vout = urv5_measure_2('A');
				meas.voltage_output_amplifier.push_back(vout);
				if (want_gain) {
					gain = vout - vin;
					meas.gain.push_back(gain);
				}
			}
			clock_t end = std::clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			total_time += elapsed_secs;
			meas.field.push_back(meas_field);
			meas.voltage_smh.push_back(ref_voltage);
			meas.voltage_input_amplifier.push_back(vin);
			i++;
		}
		//****************************************************************************//
		//								SWITCH OFF									 //
		//****************************************************************************//
		ibwrt(smh, "LEVEL:OFF", 9);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		Sleep(100);
		index_of_vector = emco_print_measurements_amp_3(index_of_vector);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		std::ostringstream sstream1;
		sstream1 << total_time / 60;
		std::string string1 = sstream1.str();
		display_message("Stage of measurement completed.\nInput to " + amplifier_name_3 + " is now OFF.\nSwitch off " + amplifier_name_3 + ".\nTotal time taken: " + string1 + " minutes.");
		do_once = true;
		/*smh_unitialization();*/
	}

	if (amp_1 || amp_2 || amp_3) {
		urv5_unitialization();
		smh_unitialization();
	}
	if (amp_4 || amp_5 || amp_6 || amp_7) {
		display_message("Switch on HP-IB 8341B.\nConnect the IEEE (GPIB) cables to the computer (the optical extension too).\nConnect AFG output to AM input of HP-IB 8341B");
		if (double some_field = emco_measure() > field_at_eut) {
			std::ostringstream sstream1, sstream2;
			sstream1 << some_field;
			sstream2 << field_at_eut;
			std::string string1 = sstream1.str();
			std::string string2 = sstream2.str();
			display_message("Error, the minimum field read inside the chamber is " + string1 + " V/m.\nTherefore " + string2 + "V/m cannot be obtained.\nCheck any malfunction of the sensors or increase the electric field of the test.", "Error", MB_OK);
			exit(EXIT_FAILURE);
		}
	}

	// AMPLIFIER 4

	if (amp_4 == true) {

		ref_voltage = INITIAL_VOLTAGE;
		display_message("Insert HP output to " + amplifier_name_4 + ".");
		current_amplifier = 4;
		emco_initialization();
		hp_initialization();
		frequency_steps(number_steps, initial_frequency_amp_4, final_frequency_amp_4, meas.frequency);
		hp_generate(initial_frequency_amp_4, "NONE", modulation_depth, carrier_frequency, ref_voltage);
		total_time = 0;

		while (i < meas.frequency.size() && meas.frequency[i] < final_frequency_amp_4) {

			double meas_field = 0;
			clock_t begin = std::clock();
			if (do_once) {
				do_once = false;
				correct_field_2(field_at_eut, i, ref_voltage, modulation_depth, carrier_frequency, meas_field);
			}

			hp_generate(meas.frequency[i], "NONE", modulation_depth, carrier_frequency, ref_voltage);
			Sleep(100);
			correct_field_2(field_at_eut, i, ref_voltage, modulation_depth, carrier_frequency, meas_field);
			if (want_vout) {
				double vout, vin, gain;
				vin = urv5_measure_2('B');
				vout = urv5_measure_2('A');
				meas.voltage_output_amplifier.push_back(vout);
				if (want_gain) {
					gain = vout - vin;
					meas.gain.push_back(gain);
				}
			}
			clock_t end = std::clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			total_time += elapsed_secs;
			meas.field.push_back(meas_field);
			meas.voltage_smh.push_back(ref_voltage);
			i++;
		}
		//****************************************************************************//
		//								SWITCH OFF									 //
		//****************************************************************************//
		ibwrt(hp, "RF0", 3);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}

		Sleep(100);
		index_of_vector = emco_print_measurements_amp_4(index_of_vector);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		std::ostringstream sstream1;
		sstream1 << total_time / 60;
		std::string string1 = sstream1.str();
		display_message("Stage of measurement completed.\nInput to " + amplifier_name_4 + " is now OFF.\nSwitch off " + amplifier_name_4 + ".\nTotal time taken: " + string1 + " minutes.");
		do_once = true;
	}

	// AMPLIFIER 5													

	if (amp_5 == true) {

		ref_voltage = INITIAL_VOLTAGE;
		display_message("Insert HP output to " + amplifier_name_5 + ".");
		current_amplifier = 5;
		emco_initialization();
		hp_initialization();
		frequency_steps(number_steps, initial_frequency_amp_5, final_frequency_amp_5, meas.frequency);
		hp_generate(initial_frequency_amp_5, "NONE", modulation_depth, carrier_frequency, ref_voltage);

		while (i < meas.frequency.size() && meas.frequency[i] < final_frequency_amp_5) {

			double meas_field = 0;
			clock_t begin = std::clock();
			if (do_once) {
				do_once = false;
				correct_field_2(field_at_eut, i, ref_voltage, modulation_depth, carrier_frequency, meas_field);
			}

			hp_generate(meas.frequency[i], "NONE", modulation_depth, carrier_frequency, ref_voltage);
			Sleep(100);
			correct_field_2(field_at_eut, i, ref_voltage, modulation_depth, carrier_frequency, meas_field);
			if (want_vout) {
				double vout, vin, gain;
				vin = urv5_measure_2('B');
				vout = urv5_measure_2('A');
				meas.voltage_output_amplifier.push_back(vout);
				if (want_gain) {
					gain = vout - vin;
					meas.gain.push_back(gain);
				}
			}
			clock_t end = std::clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			total_time += elapsed_secs;
			meas.field.push_back(meas_field);
			meas.voltage_smh.push_back(ref_voltage);
			i++;
		}
		//****************************************************************************//
		//								SWITCH OFF									 //
		//****************************************************************************//
		ibwrt(hp, "RF0", 3);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		Sleep(100);
		index_of_vector = emco_print_measurements_amp_5(index_of_vector);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		std::ostringstream sstream1;
		sstream1 << total_time / 60;
		std::string string1 = sstream1.str();
		display_message("Stage of measurement completed.\nInput to " + amplifier_name_5 + " is now OFF.\nSwitch off " + amplifier_name_5 + ".\nTotal time taken: " + string1 + " minutes.");
		do_once = true;
	}

	// AMPLIFIER 6

	if (amp_6 == true) {

		ref_voltage = INITIAL_VOLTAGE;
		display_message("Insert HP output to " + amplifier_name_6 + ".");
		current_amplifier = 6;
		emco_initialization();
		hp_initialization();
		frequency_steps(number_steps, initial_frequency_amp_6, final_frequency_amp_6, meas.frequency);
		hp_generate(initial_frequency_amp_6, "NONE", modulation_depth, carrier_frequency, ref_voltage);

		while (i < meas.frequency.size() && meas.frequency[i] < final_frequency_amp_6) {

			double meas_field = 0;
			clock_t begin = std::clock();
			if (do_once) {
				do_once = false;
				correct_field_2(field_at_eut, i, ref_voltage, modulation_depth, carrier_frequency, meas_field);
			}

			hp_generate(meas.frequency[i], "NONE", modulation_depth, carrier_frequency, ref_voltage);
			Sleep(100);
			correct_field_2(field_at_eut, i, ref_voltage, modulation_depth, carrier_frequency, meas_field);
			if (want_vout) {
				double vout, vin, gain;
				vin = urv5_measure_2('B');
				vout = urv5_measure_2('A');
				meas.voltage_output_amplifier.push_back(vout);
				if (want_gain) {
					gain = vout - vin;
					meas.gain.push_back(gain);
				}
			}
			clock_t end = std::clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			total_time += elapsed_secs;
			meas.field.push_back(meas_field);
			meas.voltage_smh.push_back(ref_voltage);
			i++;
		}
		//****************************************************************************//
		//								SWITCH OFF									 //
		//****************************************************************************//
		ibwrt(hp, "RF0", 9);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		Sleep(100);
		index_of_vector = emco_print_measurements_amp_6(index_of_vector);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		std::ostringstream sstream1;
		sstream1 << total_time / 60;
		std::string string1 = sstream1.str();
		display_message("Stage of measurement completed.\nInput to " + amplifier_name_6 + " is now OFF.\nSwitch off " + amplifier_name_6 + ".\nTotal time taken: " + string1 + " minutes.");
		do_once = true;
	}

	// AMPLIFIER 7

	if (amp_7 == true) {

		ref_voltage = INITIAL_VOLTAGE;
		display_message("Insert HP output to " + amplifier_name_7 + ".");
		current_amplifier = 7;
		emco_initialization();
		hp_initialization();
		frequency_steps(number_steps, initial_frequency_amp_7, final_frequency_amp_7, meas.frequency);
		hp_generate(initial_frequency_amp_7, "NONE", modulation_depth, carrier_frequency, ref_voltage);

		while (i < meas.frequency.size() && meas.frequency[i] < final_frequency_amp_7) {

			double meas_field = 0;
			clock_t begin = std::clock();
			if (do_once) {
				do_once = false;
				correct_field_2(field_at_eut, i, ref_voltage, modulation_depth, carrier_frequency, meas_field);
			}

			hp_generate(meas.frequency[i], "NONE", modulation_depth, carrier_frequency, ref_voltage);
			Sleep(100);
			correct_field_2(field_at_eut, i, ref_voltage, modulation_depth, carrier_frequency, meas_field);
			if (want_vout) {
				double vout, vin, gain;
				vin = urv5_measure_2('B');
				vout = urv5_measure_2('A');
				meas.voltage_output_amplifier.push_back(vout);
				if (want_gain) {
					gain = vout - vin;
					meas.gain.push_back(gain);
				}
			}
			clock_t end = std::clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			total_time += elapsed_secs;
			meas.field.push_back(meas_field);
			meas.voltage_smh.push_back(ref_voltage);
			i++;
		}
		//****************************************************************************//
		//								SWITCH OFF									 //
		//****************************************************************************//
		ibwrt(hp, "RF0", 3);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		Sleep(100);
		index_of_vector = emco_print_measurements_amp_7(index_of_vector);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		std::ostringstream sstream1;
		sstream1 << total_time / 60;
		std::string string1 = sstream1.str();
		display_message("Stage of measurement completed.\nInput to " + amplifier_name_7 + " is now OFF.\nSwitch off " + amplifier_name_7 + ".\nTotal time taken: " + string1 + " minutes.");
		do_once = true;
	}

	if (amp_4 || amp_5 || amp_6 || amp_7) {
		hp_unitialization();
		if (want_vout) {
			urv5_unitialization();
		}
	}
	emco_unitialization();
	int size_of_vector = i;
	i = 0;
	meas.field.clear();
	meas.frequency.clear();
	meas.voltage_smh.clear();
}

void frequency_steps(int& number_steps, unsigned long long initial_frequency, unsigned long long final_frequency, std::vector<unsigned long long>& meas_freq) {
	unsigned long long actual_freq = initial_frequency;
	for (number_steps = 0; actual_freq < final_frequency; number_steps++) {
		meas.frequency.push_back(actual_freq);
		double convert = actual_freq*1.01;
		actual_freq = (unsigned long long)convert;
	}
}

void plot(std::string which_plot) {
	Sleep(2000);
	Gnuplot g1, g2, g3;
	std::vector<double> vall;

	if (amp_1 == true) {
		std::ifstream meas_amp_1_file;
		meas_amp_1_file.open("measurement_amp_1.txt");
		if (!meas_amp_1_file.is_open()) {
			std::cout << "Error, couldn't open measurement_amp_1.txt" << std::endl;
			exit(EXIT_FAILURE);
		}
		unsigned long long freq;
		double field, v_smh, vin, vout, gain;
		if (want_vout) {
			while (meas_amp_1_file >> field >> freq >> v_smh >> vin >> vout >> gain) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq / 1000000);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
				meas.voltage_output_amplifier.push_back(vout);
				meas.gain.push_back(gain);
			}
		}
		else {
			while (meas_amp_1_file >> field >> freq >> v_smh >> vin) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq / 1000000);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
			}
		}
		meas_amp_1_file.close();
	}
	if (amp_2 == true) {
		std::ifstream meas_amp_2_file;
		meas_amp_2_file.open("measurement_amp_2.txt");
		if (!meas_amp_2_file.is_open()) {
			std::cout << "Error, couldn't open measurement_amp_2.txt" << std::endl;
			exit(EXIT_FAILURE);
		}
		unsigned long long freq;
		double field, v_smh, vin, vout, gain;
		if (want_vout) {
			while (meas_amp_2_file >> field >> freq >> v_smh >> vin >> vout >> gain) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq / 1000000);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
				meas.voltage_output_amplifier.push_back(vout);
				meas.gain.push_back(gain);
			}
		}
		else {
			while (meas_amp_2_file >> field >> freq >> v_smh >> vin) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq / 1000000);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
			}
		}
		meas_amp_2_file.close();
	}
	if (amp_3 == true) {
		std::ifstream meas_amp_3_file;
		meas_amp_3_file.open("measurement_amp_3.txt");
		if (!meas_amp_3_file.is_open()) {
			std::cout << "Error, couldn't open measurement_amp_3.txt" << std::endl;
			exit(EXIT_FAILURE);
		}
		unsigned long long freq;
		double field, v_smh, vin, vout, gain;
		if (want_vout) {
			while (meas_amp_3_file >> field >> freq >> v_smh >> vin >> vout >> gain) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq / 1000000);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
				meas.voltage_output_amplifier.push_back(vout);
				meas.gain.push_back(gain);
			}
		}
		else {
			while (meas_amp_3_file >> field >> freq >> v_smh >> vin) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq / 1000000);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
			}
		}
		meas_amp_3_file.close();
	}

	int i = 0;
	if (amp_1 || amp_2 || amp_3) {
		while (i < meas.voltage_input_amplifier.size()) {
			vall.push_back(meas.voltage_input_amplifier[i]);
			i++;
		}
	}

	if (amp_4 == true) {
		std::ifstream meas_amp_4_file;
		meas_amp_4_file.open("measurement_amp_4.txt");
		if (!meas_amp_4_file.is_open()) {
			std::cout << "Error, couldn't open measurement_amp_4.txt" << std::endl;
			exit(EXIT_FAILURE);
		}
		unsigned long long freq;
		double field, v_smh, vin, vout, gain;
		if (want_vout) {
			while (meas_amp_4_file >> field >> freq >> v_smh >> vin >> vout >> gain) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq / 1000000);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
				meas.voltage_output_amplifier.push_back(vout);
				meas.gain.push_back(gain);
			}
		}
		else {
			while (meas_amp_4_file >> field >> freq >> v_smh) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq / 1000000);
				meas.voltage_smh.push_back(v_smh);
			}
		}
		meas_amp_4_file.close();
	}
	if (amp_5 == true) {
		std::ifstream meas_amp_5_file;
		meas_amp_5_file.open("measurement_amp_5.txt");
		if (!meas_amp_5_file.is_open()) {
			std::cout << "Error, couldn't open measurement_amp_5.txt" << std::endl;
			exit(EXIT_FAILURE);
		}
		unsigned long long freq;
		double field, v_smh, vin, vout, gain;
		if (want_vout) {
			while (meas_amp_5_file >> field >> freq >> v_smh >> vin >> vout >> gain) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq / 1000000);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
				meas.voltage_output_amplifier.push_back(vout);
				meas.gain.push_back(gain);
			}
		}
		else {
			while (meas_amp_5_file >> field >> freq >> v_smh) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq / 1000000);
				meas.voltage_smh.push_back(v_smh);
			}
		}
		meas_amp_5_file.close();
	}
	if (amp_6 == true) {
		std::ifstream meas_amp_6_file;
		meas_amp_6_file.open("measurement_amp_6.txt");
		if (!meas_amp_6_file.is_open()) {
			std::cout << "Error, couldn't open measurement_amp_6.txt" << std::endl;
			exit(EXIT_FAILURE);
		}
		unsigned long long freq;
		double field, v_smh, vin, vout, gain;
		if (want_vout) {
			while (meas_amp_6_file >> field >> freq >> v_smh >> vin >> vout >> gain) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq / 1000000);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
				meas.voltage_output_amplifier.push_back(vout);
				meas.gain.push_back(gain);
			}
		}
		else {
			while (meas_amp_6_file >> field >> freq >> v_smh) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq / 1000000);
				meas.voltage_smh.push_back(v_smh);
			}
		}
		meas_amp_6_file.close();
	}
	if (amp_7 == true) {
		std::ifstream meas_amp_7_file;
		meas_amp_7_file.open("measurement_amp_7.txt");
		if (!meas_amp_7_file.is_open()) {
			std::cout << "Error, couldn't open measurement_amp_7.txt" << std::endl;
			exit(EXIT_FAILURE);
		}
		unsigned long long freq;
		double field, v_smh, vin, vout, gain;
		if (want_vout) {
			while (meas_amp_7_file >> field >> freq >> v_smh >> vin >> vout >> gain) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq / 1000000);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
				meas.voltage_output_amplifier.push_back(vout);
				meas.gain.push_back(gain);
			}
		}
		else {
			while (meas_amp_7_file >> field >> freq >> v_smh) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq / 1000000);
				meas.voltage_smh.push_back(v_smh);
			}
		}
		meas_amp_7_file.close();
	}

	if (amp_4 || amp_5 || amp_6 || amp_7) {
		while (i < meas.voltage_smh.size()) {
			vall.push_back(meas.voltage_smh[i]);
			i++;
		}
	}

	g1.set_grid();
	g1.set_smooth("bezier");
	g1.set_xlogscale();
	g1.set_xlabel("Frequency (MHz)");
	g1.set_ylabel("Electric field (V/m)");
	g1.set_xrange((double)initial_frequency / 1000000, (double)final_frequency / 1000000);
	g1.set_style("points").plot_xy(meas.frequency, meas.field, "Electric field");
	g1.showonscreen();
	g1 << "set terminal jpeg \n";
	g1 << "set output 'Electric field measurements.jpeg' \n";
	g1 << "replot \n";

	g2.set_grid();
	g2.set_smooth("bezier");
	g2.set_xlogscale();
	g2.set_xlabel("Frequency (MHz)");
	g2.set_ylabel("Voltage (dBm)");
	g2.set_xrange((double)initial_frequency / 1000000, (double)final_frequency / 1000000);
	g2.set_style("points").plot_xy(meas.frequency, vall, "Output from signal generator");
	if (want_vout) {
		g2.set_style("points").plot_xy(meas.frequency, meas.voltage_output_amplifier, "Output from amplifier");
	}
	g2 << "set terminal jpeg \n";
	g2 << "set output 'Voltage measurements.jpeg' \n";
	g2 << "replot";
	g2 << "unset output";

	if (want_vout) {
		g3.set_grid();
		g3.set_smooth("bezier");
		g3.set_xlogscale();
		g3.set_xlabel("Frequency (MHz)");
		g3.set_ylabel("Gain (dB)");
		g3.set_xrange((double)initial_frequency / 1000000, (double)final_frequency / 1000000);
		g3.set_style("points").plot_xy(meas.frequency, meas.gain, "Amplifier gain");
		g3 << "set terminal jpeg \n";
		g3 << "set output 'Voltage measurements.jpeg' \n";
		g3 << "replot";
	}
}

void correct_field_1(double field_at_eut, int i, double& ref_voltage, int modulation_depth, int carrier_frequency, double& vin, double& meas_field) {
	meas_field = emco_measure();
	vin = urv5_measure_2('B');
	while (meas_field < 0.97 * field_at_eut || meas_field > 1.03 * field_at_eut) {
		while (meas_field > 1.03*field_at_eut) {
			ref_voltage -= 0.2;
			smh_change_level_no_modulation(ref_voltage);
			vin = urv5_measure_2('B');
			if ((current_amplifier == 1 && vin > max_voltage_amp_1) || (current_amplifier == 2 && vin > max_voltage_amp_2)
				|| (current_amplifier == 3 && vin > max_voltage_amp_3) || (current_amplifier == 4 && vin > max_voltage_amp_4)
				|| (current_amplifier == 5 && vin > max_voltage_amp_5) || (current_amplifier == 6 && vin > max_voltage_amp_6)
				|| (current_amplifier == 7 && vin > max_voltage_amp_7)) {
				if (current_amplifier == 1 || current_amplifier == 2 || current_amplifier == 3) {
					exit_error("Exceeded input voltage to amplifier.\nIncrease the gain of the amplifier, reduce the electric field of the test or increase the maximum input voltage of the amplifier.");
				}
			}
			meas_field = emco_measure();
		}
		while (meas_field < 0.97*field_at_eut) {
			ref_voltage += 0.2;
			smh_change_level_no_modulation(ref_voltage);
			vin = urv5_measure_2('B');
			if ((current_amplifier == 1 && vin > max_voltage_amp_1) || (current_amplifier == 2 && vin > max_voltage_amp_2)
				|| (current_amplifier == 3 && vin > max_voltage_amp_3) || (current_amplifier == 4 && vin > max_voltage_amp_4)
				|| (current_amplifier == 5 && vin > max_voltage_amp_5) || (current_amplifier == 6 && vin > max_voltage_amp_6)
				|| (current_amplifier == 7 && vin > max_voltage_amp_7)) {
				if (current_amplifier == 1 || current_amplifier == 2 || current_amplifier == 3) {
					exit_error("Exceeded input voltage to amplifier.\nIncrease the gain of the amplifier, reduce the electric field of the test or increase the maximum input voltage of the amplifier.");
				}
			}
			meas_field = emco_measure();
		}
	}
}
void correct_field_2(double field_at_eut, int i, double& ref_voltage, int modulation_depth, int carrier_frequency, double& meas_field) {
	meas_field = emco_measure();
	while (meas_field < 0.97 * field_at_eut || meas_field > 1.03 * field_at_eut) {
		while (meas_field > 1.03*field_at_eut) {
			ref_voltage -= 0.2;
			hp_change_level_no_modulation(ref_voltage);
			if ((current_amplifier == 1 && ref_voltage > max_voltage_amp_1) || (current_amplifier == 2 && ref_voltage > max_voltage_amp_2)
				|| (current_amplifier == 3 && ref_voltage > max_voltage_amp_3) || (current_amplifier == 4 && ref_voltage > max_voltage_amp_4)
				|| (current_amplifier == 5 && ref_voltage > max_voltage_amp_5) || (current_amplifier == 6 && ref_voltage > max_voltage_amp_6)
				|| (current_amplifier == 7 && ref_voltage > max_voltage_amp_7)) {
				exit_error("Exceeded input voltage to amplifier.\nIncrease the gain of the amplifier, reduce the electric field of the test or increase the maximum input voltage of the amplifier.");
			}
			Sleep(100);
			meas_field = emco_measure();
		}
		while (meas_field < 0.97*field_at_eut) {
			ref_voltage += 0.2;
			hp_change_level_no_modulation(ref_voltage);
			if ((current_amplifier == 1 && ref_voltage > max_voltage_amp_1) || (current_amplifier == 2 && ref_voltage > max_voltage_amp_2)
				|| (current_amplifier == 3 && ref_voltage > max_voltage_amp_3) || (current_amplifier == 4 && ref_voltage > max_voltage_amp_4)
				|| (current_amplifier == 5 && ref_voltage > max_voltage_amp_5) || (current_amplifier == 6 && ref_voltage > max_voltage_amp_6)
				|| (current_amplifier == 7 && ref_voltage > max_voltage_amp_7)) {
				exit_error("Exceeded input voltage to amplifier.\nIncrease the gain of the amplifier, reduce the electric field of the test or increase the maximum input voltage of the amplifier.");
			}
			Sleep(100);
			meas_field = emco_measure();
		}
	}
}
void det_amp() {
	if (initial_frequency >= min_freq_amp_1 && initial_frequency < max_freq_amp_1) {
		initial_frequency_amp_1 = initial_frequency;
		if (final_frequency < max_freq_amp_1) {
			final_frequency_amp_1 = final_frequency;
		}
		else {
			final_frequency_amp_1 = max_freq_amp_1;
		}
		amp_1 = true;
	}
	else {
		amp_1 = false;
	}
	if ((initial_frequency >= min_freq_amp_2 && initial_frequency < max_freq_amp_2) || (amp_1 == true && final_frequency > max_freq_amp_1)) {
		if (initial_frequency > min_freq_amp_2) {
			initial_frequency_amp_2 = initial_frequency;
		}
		else {
			initial_frequency_amp_2 = max_freq_amp_1;
		}
		if (final_frequency < max_freq_amp_2) {
			final_frequency_amp_2 = final_frequency;
		}
		else {
			final_frequency_amp_2 = max_freq_amp_2;
		}
		amp_2 = true;
	}
	else {
		amp_2 = false;
	}
	if ((initial_frequency >= min_freq_amp_3 && initial_frequency < max_freq_amp_3) || (amp_2 == true && final_frequency > max_freq_amp_2)) {
		if (initial_frequency > min_freq_amp_3) {
			initial_frequency_amp_3 = initial_frequency;
		}
		else {
			initial_frequency_amp_3 = max_freq_amp_2;
		}
		if (final_frequency < max_freq_amp_3) {
			final_frequency_amp_3 = final_frequency;
		}
		else {
			final_frequency_amp_3 = max_freq_amp_3;
		}
		amp_3 = true;
	}
	else {
		amp_3 = false;
	}
	if ((initial_frequency >= min_freq_amp_4 && initial_frequency < max_freq_amp_4) || (amp_3 == true && final_frequency > max_freq_amp_3)) {
		if (initial_frequency > min_freq_amp_4) {
			initial_frequency_amp_4 = initial_frequency;
		}
		else {
			initial_frequency_amp_4 = max_freq_amp_3;
		}
		if (final_frequency < max_freq_amp_4) {
			final_frequency_amp_4 = final_frequency;
		}
		else {
			final_frequency_amp_4 = max_freq_amp_4;
		}
		amp_4 = true;
	}
	else {
		amp_4 = false;
	}
	if ((initial_frequency >= min_freq_amp_5 && initial_frequency < max_freq_amp_5) || (amp_4 == true && final_frequency > max_freq_amp_4)) {
		if (initial_frequency > min_freq_amp_5) {
			initial_frequency_amp_5 = initial_frequency;
		}
		else {
			initial_frequency_amp_5 = max_freq_amp_4;
		}
		if (final_frequency < max_freq_amp_5) {
			final_frequency_amp_5 = final_frequency;
		}
		else {
			final_frequency_amp_5 = max_freq_amp_5;
		}
		amp_5 = true;
	}
	else {
		amp_5 = false;
	}
	if ((initial_frequency >= min_freq_amp_6 && initial_frequency < max_freq_amp_6) || (amp_5 == true && final_frequency > max_freq_amp_5)) {
		if (initial_frequency > min_freq_amp_6) {
			initial_frequency_amp_6 = initial_frequency;
		}
		else {
			initial_frequency_amp_6 = max_freq_amp_5;
		}
		if (final_frequency < max_freq_amp_6) {
			final_frequency_amp_6 = final_frequency;
		}
		else {
			final_frequency_amp_6 = max_freq_amp_6;
		}
		amp_6 = true;
	}
	else {
		amp_6 = false;
	}
	if ((initial_frequency >= min_freq_amp_7 && initial_frequency < max_freq_amp_7) || (amp_6 == true && final_frequency > max_freq_amp_6)) {
		if (initial_frequency > min_freq_amp_7) {
			initial_frequency_amp_7 = initial_frequency;
		}
		else {
			initial_frequency_amp_7 = max_freq_amp_6;
		}
		if (final_frequency < max_freq_amp_7) {
			final_frequency_amp_7 = final_frequency;
		}
		else {
			final_frequency_amp_7 = max_freq_amp_7;
		}
		amp_7 = true;
	}
	else {
		amp_7 = false;
	}
	if (initial_frequency < min_freq_amp_1) {
		amp_1 = false;
		amp_2 = false;
		amp_3 = false;
		amp_4 = false;
		amp_5 = false;
		amp_6 = false;
		amp_7 = false;
		std::ostringstream sstream1;
		sstream1 << min_freq_amp_1;
		std::string string1 = sstream1.str();
		exit_error("The initial frequency is bellow the minimum frequency range of the available amplifiers." + string1 + ". Enter a different initial frequency.");
	}
	if (final_frequency > max_freq_amp_7) {
		amp_1 = false;
		amp_2 = false;
		amp_3 = false;
		amp_4 = false;
		amp_5 = false;
		amp_6 = false;
		amp_7 = false;
		std::ostringstream sstream1;
		sstream1 << max_freq_amp_7;
		std::string string1 = sstream1.str();
		exit_error("The initial frequency is above the maximum frequency range of the available amplifiers." + string1 + " Hz.\nEnter a different final frequency.");
	}
}
void gpib_configuration() {
	//ibfind(GPIB0);
	ibconfig(GPIB0, IbcSC, 1);
	ibsic(GPIB0);
	ibconfig(GPIB0, IbcSRE, 1);
	ibconfig(GPIB0, IbcTIMING, 1);
}
std::string obtain_used_amplifiers() {
	std::string amplifiers;
	if (amp_1) {
		amplifiers = amplifier_name_1;
	}
	if (amp_2) {
		amplifiers += ("\n" + amplifier_name_2);
	}
	if (amp_3) {
		amplifiers += ("\n" + amplifier_name_3);
	}
	if (amp_4) {
		amplifiers += ("\n" + amplifier_name_4);
	}
	if (amp_5) {
		amplifiers += ("\n" + amplifier_name_5);
	}
	if (amp_6) {
		amplifiers += ("\n" + amplifier_name_6);
	}
	if (amp_7) {
		amplifiers += ("\n" + amplifier_name_7);
	}
	return amplifiers;
}

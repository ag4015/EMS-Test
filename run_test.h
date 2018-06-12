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



//FUNCTION DEFINITION

void run_test();



void run_test() {
	int number_steps;
	double total_time = 0;
	unsigned int i = 0;
	bool do_once = true;
	unsigned int index_of_vector = 0;
	std::string key;
	bool configure_amplifiers = true;
	double ref_voltage = INITIAL_VOLTAGE;						// dBm
	gpib_configuration();
	initial_configuration();
	display_message("Place EUT in the desired location.");

	if (amp_1 == true) {
		std::ifstream meas_amp_1_file;
		meas_amp_1_file.open("measurement_amp_1.txt");
		if (!meas_amp_1_file.is_open()) {
			exit_error("Couldn't open measurement_amp_1.txt");
		}
		unsigned long long freq;
		double field, v_smh, vin, vout, gain;
		if (want_vout) {
			while (meas_amp_1_file >> field >> freq >> v_smh >> vin >> vout >> gain) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
				meas.voltage_output_amplifier.push_back(vout);
				meas.gain.push_back(gain);
			}
		}
		else {
			while (meas_amp_1_file >> field >> freq >> v_smh >> vin) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq);
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
			exit_error("Couldn't open measurement_amp_2.txt");
		}
		unsigned long long freq;
		double field, v_smh, vin, vout, gain;
		if (want_vout) {
			while (meas_amp_2_file >> field >> freq >> v_smh >> vin >> vout >> gain) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
				meas.voltage_output_amplifier.push_back(vout);
				meas.gain.push_back(gain);
			}
		}
		else {
			while (meas_amp_2_file >> field >> freq >> v_smh >> vin) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq);
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
			exit_error("Couldn't open measurement_amp_3.txt");
		}
		unsigned long long freq;
		double field, v_smh, vin, vout, gain;
		if (want_vout) {
			while (meas_amp_3_file >> field >> freq >> v_smh >> vin >> vout >> gain) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
				meas.voltage_output_amplifier.push_back(vout);
				meas.gain.push_back(gain);
			}
		}
		else {
			while (meas_amp_3_file >> field >> freq >> v_smh >> vin) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
			}
		}
		meas_amp_3_file.close();
	}
	if (amp_4 == true) {
		std::ifstream meas_amp_4_file;
		meas_amp_4_file.open("measurement_amp_4.txt");
		if (!meas_amp_4_file.is_open()) {
			exit_error("Couldn't open measurement_amp_4.txt");
		}
		unsigned long long freq;
		double field, v_smh, vin, vout, gain;
		if (want_vout) {
			while (meas_amp_4_file >> field >> freq >> v_smh >> vin >> vout >> gain) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
				meas.voltage_output_amplifier.push_back(vout);
				meas.gain.push_back(gain);
			}
		}
		else {
			while (meas_amp_4_file >> field >> freq >> v_smh) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq);
				meas.voltage_smh.push_back(v_smh);
			}
		}
		meas_amp_4_file.close();
	}
	if (amp_5 == true) {
		std::ifstream meas_amp_5_file;
		meas_amp_5_file.open("measurement_amp_5.txt");
		if (!meas_amp_5_file.is_open()) {
			exit_error("Couldn't open measurement_amp_5.txt");
		}
		unsigned long long freq;
		double field, v_smh, vin, vout, gain;
		if (want_vout) {
			while (meas_amp_5_file >> field >> freq >> v_smh >> vin >> vout >> gain) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
				meas.voltage_output_amplifier.push_back(vout);
				meas.gain.push_back(gain);
			}
		}
		else {
			while (meas_amp_5_file >> field >> freq >> v_smh) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq);
				meas.voltage_smh.push_back(v_smh);
			}
		}
		meas_amp_5_file.close();
	}
	if (amp_6 == true) {
		std::ifstream meas_amp_6_file;
		meas_amp_6_file.open("measurement_amp_6.txt");
		if (!meas_amp_6_file.is_open()) {
			exit_error("Couldn't open measurement_amp_6.txt");
		}
		unsigned long long freq;
		double field, v_smh, vin, vout, gain;
		if (want_vout) {
			while (meas_amp_6_file >> field >> freq >> v_smh >> vin >> vout >> gain) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
				meas.voltage_output_amplifier.push_back(vout);
				meas.gain.push_back(gain);
			}
		}
		else {
			while (meas_amp_6_file >> field >> freq >> v_smh) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq);
				meas.voltage_smh.push_back(v_smh);
			}
		}
		meas_amp_6_file.close();
	}
	if (amp_7 == true) {
		std::ifstream meas_amp_7_file;
		meas_amp_7_file.open("measurement_amp_7.txt");
		if (!meas_amp_7_file.is_open()) {
			exit_error("Couldn't open measurement_amp_7.txt");
		}
		unsigned long long freq;
		double field, v_smh, vin, vout, gain;
		if (want_vout) {
			while (meas_amp_7_file >> field >> freq >> v_smh >> vin >> vout >> gain) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq);
				meas.voltage_smh.push_back(v_smh);
				meas.voltage_input_amplifier.push_back(vin);
				meas.voltage_output_amplifier.push_back(vout);
				meas.gain.push_back(gain);
			}
		}
		else {
			while (meas_amp_7_file >> field >> freq >> v_smh) {
				meas.field.push_back(field);
				meas.frequency.push_back(freq);
				meas.voltage_smh.push_back(v_smh);
			}
		}
		meas_amp_7_file.close();
	}

	if (amp_1 || amp_2 || amp_3) {
		display_message("Switch on SMH.\nConnect IEEE (GPIB) cables to the computer (but not the optical extension)");
		smh_initialization();
		urv5_initialization();
	}

	if (amp_1 == true) {

		display_message("Insert SMH output to " + amplifier_name_1 + ".");
		current_amplifier = 1;
		gpib_configuration();
		emco_initialization();
		smh_initialization();
		urv5_initialization();

		while (i < meas.frequency.size() && meas.frequency[i] < final_frequency_amp_1) {
			smh_generate(meas.frequency[i], "AM", modulation_depth, carrier_frequency, meas.voltage_smh[i]);
			Sleep(dwell_time);
			i++;
		}

		ibwrt(smh, "LEVEL:OFF", 9);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}

		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		display_message("Stage of testing completed.\nInput to " + amplifier_name_1 + " is now OFF.\n Switch off" + amplifier_name_1 + ".");
	}
	if (amp_2 == true) {

		display_message("Insert SMH output to " + amplifier_name_2 + ".");
		current_amplifier = 2;
		gpib_configuration();
		emco_initialization();
		smh_initialization();
		urv5_initialization();

		while (i < meas.frequency.size() && meas.frequency[i] < final_frequency_amp_2) {
			smh_generate(meas.frequency[i], "AM", modulation_depth, carrier_frequency, meas.voltage_smh[i]);
			Sleep(dwell_time);
			i++;
		}

		ibwrt(smh, "LEVEL:OFF", 9);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}

		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		display_message("Stage of testing completed.\nInput to " + amplifier_name_2 + " is now OFF.\n Switch off" + amplifier_name_2 + ".");
	}
	if (amp_3 == true) {

		display_message("Insert SMH output to " + amplifier_name_3 + ".");
		current_amplifier = 3;
		gpib_configuration();
		emco_initialization();
		smh_initialization();
		urv5_initialization();

		while (i < meas.frequency.size() && meas.frequency[i] < final_frequency_amp_3) {
			smh_generate(meas.frequency[i], "AM", modulation_depth, carrier_frequency, meas.voltage_smh[i]);
			Sleep(dwell_time);
			i++;
		}

		ibwrt(smh, "LEVEL:OFF", 9);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}

		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		display_message("Stage of testing completed.\nInput to " + amplifier_name_3 + " is now OFF.\n Switch off" + amplifier_name_3 + ".");
	}

	if (amp_1 || amp_2 || amp_3) {
		smh_unitialization();
		urv5_unitialization();
	}
	if (amp_4 || amp_5 || amp_6 || amp_7) {
		display_message("Switch on HP-IB 8341B and AFG.\nConnect the IEEE (GPIB) cables to the computer (including the optical extension).\nConnect AFG output to AM input of HP-IB 8341B.");
	}

	if (amp_4 == true) {

		display_message("Insert SMH output to " + amplifier_name_4 + ".");
		current_amplifier = 4;
		hp_initialization();
		afg_initialization();
		afg_change_frequency(carrier_frequency);

		while (i < meas.frequency.size() && meas.frequency[i] < final_frequency_amp_4) {
			Sleep(100);
			hp_generate(meas.frequency[i], "AM", modulation_depth, carrier_frequency, meas.voltage_smh[i]);
			Sleep(dwell_time);
			i++;
		}

		ibwrt(hp, "RF0", 3);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}

		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		display_message("Stage of testing completed.\nInput to " + amplifier_name_4 + " is now OFF.\n Switch off" + amplifier_name_4 + ".");
	}
	if (amp_5 == true) {

		display_message("Insert SMH output to " + amplifier_name_5 + ".");
		current_amplifier = 5;
		hp_initialization();
		afg_initialization();
		afg_change_frequency(carrier_frequency);

		while (i < meas.frequency.size() && meas.frequency[i] < final_frequency_amp_5) {
			hp_generate(meas.frequency[i], "AM", modulation_depth, carrier_frequency, meas.voltage_smh[i]);
			Sleep(dwell_time);
			i++;
		}

		ibwrt(hp, "RF0", 3);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		display_message("Stage of testing completed.\nInput to " + amplifier_name_5 + " is now OFF.\n Switch off" + amplifier_name_5 + ".");
		std::cin >> key;
	}
	if (amp_6 == true) {

		display_message("Insert SMH output to " + amplifier_name_6 + ".");
		current_amplifier = 6;
		hp_initialization();
		afg_initialization();
		afg_change_frequency(carrier_frequency);

		while (i < meas.frequency.size() && meas.frequency[i] < final_frequency_amp_6) {
			hp_generate(meas.frequency[i], "AM", modulation_depth, carrier_frequency, meas.voltage_smh[i]);
			Sleep(dwell_time);
			i++;
		}

		ibwrt(hp, "RF0", 3);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}

		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		display_message("Stage of testing completed.\nInput to " + amplifier_name_6 + " is now OFF.\n Switch off" + amplifier_name_6 + ".");
	}
	if (amp_7 == true) {

		display_message("Insert SMH output to " + amplifier_name_7 + ".");
		current_amplifier = 7;
		hp_initialization();
		afg_initialization();
		afg_change_frequency(carrier_frequency);

		while (i < meas.frequency.size() && meas.frequency[i] < final_frequency_amp_7) {
			hp_generate(meas.frequency[i], "AM", modulation_depth, carrier_frequency, meas.voltage_smh[i]);
			Sleep(dwell_time);
			i++;
		}

		ibwrt(hp, "RF0", 3);
		if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}

		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		Sleep(500);
		Beep(1046, 500);
		display_message("Stage of testing completed.\nInput to " + amplifier_name_7 + " is now OFF.\n Switch off" + amplifier_name_7 + ".");
	}

	if (amp_4 || amp_5 || amp_6 || amp_7) {
		afg_unitialization();
		hp_unitialization();
	}

	meas.field.clear();
	meas.frequency.clear();
	meas.voltage_smh.clear();
	meas.voltage_input_amplifier.clear();
}
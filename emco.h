/*****************************************************************************
* Refer to the language interface documentation for details on
* which header and .obj files to include in your project.
*****************************************************************************/
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



void initial_configuration();
void write_configuration_file();
void emco_initialization();
void emco_default_configuration();
double emco_measure();
void emco_unitialization();
int emco_print_measurements_amp_1(unsigned int index_of_vector);
int emco_print_measurements_amp_2(unsigned int index_of_vector);
int emco_print_measurements_amp_3(unsigned int index_of_vector);
int emco_print_measurements_amp_4(unsigned int index_of_vector);
int emco_print_measurements_amp_5(unsigned int index_of_vector);
int emco_print_measurements_amp_6(unsigned int index_of_vector);
int emco_print_measurements_amp_7(unsigned int index_of_vector);


void GpibError(char *msg);        /* Error function declaration              */

int emco_unit = 0;                   /* Device unit descriptor                  */
int BoardIndex = 0;               /* Interface Index (GPIB0=0,GPIB1=1,etc.)  */
std::ofstream measurements_file;
struct measurement {
	std::vector<double> field;
	std::vector<double> voltage_smh;
	std::vector<double> voltage_input_amplifier;
	std::vector<double> voltage_output_amplifier;
	std::vector<double> gain;
	std::vector<unsigned long long> frequency;
};
std::string available_probes;
char  Buffer[101];             /* Read buffer                             */
measurement meas;
std::string coordinate_representation;
int selected_probe;
std::string time_period;
std::string units;
double attenuation = 0;

void make_new_file();
void initial_configuration() {
	std::ifstream infile;
	std::string file = current_path + file_name + "/" + file_name + ".txt";
	infile.open(file.c_str());
	if (!infile.is_open()) {
		exit_error("Error, could not open the file");
		exit(EXIT_FAILURE);
	}
	std::string word;
	infile >> word >> emco_primary_address;
	infile >> word >> urv5_primary_address;
	infile >> word >> smh_primary_address;
	infile >> word >> hp_primary_address;
	infile >> word >> afg_primary_address;
	infile >> word >> urv5_2_primary_address;
	infile >> word >> initial_frequency;
	infile >> word >> final_frequency;
	infile >> word >> modulation_depth;
	infile >> word >> carrier_frequency;
	infile >> word >> dwell_time;
	infile >> word >> field_at_eut;
	infile >> word >> min_freq_amp_1;
	infile >> word >> min_freq_amp_2;
	infile >> word >> min_freq_amp_3;
	infile >> word >> min_freq_amp_4;
	infile >> word >> min_freq_amp_5;
	infile >> word >> min_freq_amp_6;
	infile >> word >> min_freq_amp_7;
	infile >> word >> max_freq_amp_1;
	infile >> word >> max_freq_amp_2;
	infile >> word >> max_freq_amp_3;
	infile >> word >> max_freq_amp_4;
	infile >> word >> max_freq_amp_5;
	infile >> word >> max_freq_amp_6;
	infile >> word >> max_freq_amp_7;
	infile >> word >> max_voltage_amp_1;
	infile >> word >> max_voltage_amp_2;
	infile >> word >> max_voltage_amp_3;
	infile >> word >> max_voltage_amp_4;
	infile >> word >> max_voltage_amp_5;
	infile >> word >> max_voltage_amp_6;
	infile >> word >> max_voltage_amp_7;
	infile >> word >> amplifier_name_1;
	infile >> word >> amplifier_name_2;
	infile >> word >> amplifier_name_3;
	infile >> word >> amplifier_name_4;
	infile >> word >> amplifier_name_5;
	infile >> word >> amplifier_name_6;
	infile >> word >> amplifier_name_7;
	infile >> word >> measurement_done;
	infile >> word >> amp_1;
	infile >> word >> amp_2;
	infile >> word >> amp_3;
	infile >> word >> amp_4;
	infile >> word >> amp_5;
	infile >> word >> amp_6;
	infile >> word >> amp_7;
	infile.close();
}
void write_configuration_file() {
	std::ofstream outfile;
	std::string file = current_path + file_name + ".txt";
	outfile.open(file.c_str());
	if (!outfile.is_open()) {
		exit_error("Error, could not open the file");
		exit(EXIT_FAILURE);
	}
	std::string word;
	outfile << "emco_primary_addres\t" << emco_primary_address << "\n";
	outfile << "urv5_primary_address\t" << urv5_primary_address << "\n";
	outfile << "smh_primary_address\t" << smh_primary_address << "\n";
	outfile << "hp_primary_address\t" << hp_primary_address << "\n";
	outfile << "afg_primary_address\t" << afg_primary_address << "\n";
	outfile << "urv5_2_primary_address\t" << urv5_2_primary_address << "\n";
	outfile << "initial_frequency\t" << initial_frequency << "\n";
	outfile << "final_frequency\t" << final_frequency << "\n";
	outfile << "modulation_depth\t" << modulation_depth << "\n";
	outfile << "carrier_frequency\t" << carrier_frequency << "\n";
	outfile << "dwell_time\t" << dwell_time << "\n";
	outfile << "field_at_eut\t" << field_at_eut << "\n";
	outfile << "min_freq_amp_1\t" << min_freq_amp_1 << "\n";
	outfile << "min_freq_amp_2\t" << min_freq_amp_2 << "\n";
	outfile << "min_freq_amp_3\t" << min_freq_amp_3 << "\n";
	outfile << "min_freq_amp_4\t" << min_freq_amp_4 << "\n";
	outfile << "min_freq_amp_5\t" << min_freq_amp_5 << "\n";
	outfile << "min_freq_amp_6\t" << min_freq_amp_6 << "\n";
	outfile << "min_freq_amp_7\t" << min_freq_amp_7 << "\n";
	outfile << "max_freq_amp_1\t" << max_freq_amp_1 << "\n";
	outfile << "max_freq_amp_2\t" << max_freq_amp_2 << "\n";
	outfile << "max_freq_amp_3\t" << max_freq_amp_3 << "\n";
	outfile << "max_freq_amp_4\t" << max_freq_amp_4 << "\n";
	outfile << "max_freq_amp_5\t" << max_freq_amp_5 << "\n";
	outfile << "max_freq_amp_6\t" << max_freq_amp_6 << "\n";
	outfile << "max_freq_amp_7\t" << max_freq_amp_7 << "\n";
	outfile << "max_voltage_amp_1\t" << max_voltage_amp_1 << "\n";
	outfile << "max_voltage_amp_2\t" << max_voltage_amp_2 << "\n";
	outfile << "max_voltage_amp_3\t" << max_voltage_amp_3 << "\n";
	outfile << "max_voltage_amp_4\t" << max_voltage_amp_4 << "\n";
	outfile << "max_voltage_amp_5\t" << max_voltage_amp_5 << "\n";
	outfile << "max_voltage_amp_6\t" << max_voltage_amp_6 << "\n";
	outfile << "max_voltage_amp_7\t" << max_voltage_amp_7 << "\n";
	outfile << "amplifier_name_1\t" << amplifier_name_1 << "\n";
	outfile << "amplifier_name_2\t" << amplifier_name_2 << "\n";
	outfile << "amplifier_name_3\t" << amplifier_name_3 << "\n";
	outfile << "amplifier_name_4\t" << amplifier_name_4 << "\n";
	outfile << "amplifier_name_5\t" << amplifier_name_5 << "\n";
	outfile << "amplifier_name_6\t" << amplifier_name_6 << "\n";
	outfile << "amplifier_name_7\t" << amplifier_name_7 << "\n";
	outfile << "measurement_done\t" << measurement_done << "\n";
	outfile << "amp_1\t" << amp_1 << "\n";
	outfile << "amp_2\t" << amp_2 << "\n";
	outfile << "amp_3\t" << amp_3 << "\n";
	outfile << "amp_4\t" << amp_4 << "\n";
	outfile << "amp_5\t" << amp_5 << "\n";
	outfile << "amp_6\t" << amp_6 << "\n";
	outfile << "amp_7\t" << amp_7 << "\n";
	outfile.close();
}
void GpibError(char *msg) {
	//printf("ibsta = &H%x  <", ibsta);
	//if (ibsta & ERR)  exit_error(" ERR");
	//if (ibsta & TIMO)  exit_error(" TIMO");
	//if (ibsta & END)  exit_error(" END");
	//if (ibsta & SRQI)  exit_error(" SRQI");
	//if (ibsta & RQS)  exit_error(" RQS");
	//if (ibsta & CMPL)  exit_error(" CMPL");
	//if (ibsta & LOK)  exit_error(" LOK");
	//if (ibsta & REM)  exit_error(" REM");
	//if (ibsta & CIC)  exit_error(" CIC");
	//if (ibsta & ATN)  exit_error(" ATN");
	//if (ibsta & TACS)  exit_error(" TACS");
	//if (ibsta & LACS)  exit_error(" LACS");
	//if (ibsta & DTAS)  exit_error(" DTAS");
	//if (ibsta & DCAS)  exit_error(" DCAS");
	//printf(" >\n");

	//printf("iberr = %d", iberr);
	if (iberr == EDVR) exit_error(" EDVR <DOS Error>\n");
	if (iberr == ECIC) exit_error(" ECIC <Not Controller-In-Charge>\n");
	if (iberr == ENOL) exit_error(" ENOL <No Listener>\n");
	if (iberr == EADR) exit_error(" EADR <Address error>\n");
	if (iberr == EARG) exit_error(" EARG <Invalid argument>\n");
	if (iberr == ESAC) exit_error(" ESAC <Not System Controller>\n");
	if (iberr == EABO) exit_error(" EABO <Operation aborted>\n");
	if (iberr == ENEB) exit_error(" ENEB <No GPIB board>\n");
	if (iberr == EOIP) exit_error(" EOIP <Async I/O in progress>\n");
	if (iberr == ECAP) exit_error(" ECAP <No capability>\n");
	if (iberr == EFSO) exit_error(" EFSO <File system error>\n");
	if (iberr == EBUS) exit_error(" EBUS <Command error>\n");
	if (iberr == ESTB) exit_error(" ESTB <Status byte lost>\n");
	if (iberr == ESRQ) exit_error(" ESRQ <SRQ stuck on>\n");
	if (iberr == ETAB) exit_error(" ETAB <Table Overflow>\n");

	//printf("ibcntl = %ld\n", ibcntl);
	//printf("\n");

	/* Call ibonl to take the device and interface offline */
	ibonl(15, 0);
	ibonl(2, 0);
	ibonl(1, 0);
	ibonl(10, 0);
	ibonl(3, 0);

 	exit(1);
}
void emco_initialization() {
	emco_unit = ibdev(				    /* Create a unit descriptor handle         */
		0,						/* Board Index (GPIB0 = 0, GPIB1 = 1, ...) */
		emco_primary_address,           /* Device primary address                  */
		0,						         /* Device secondary address                */
		T10s,							/* Timeout setting (T10s = 10 seconds)     */
		1,							    /* Assert EOI line at end of write         */
		0);							    /* EOS termination mode                    */
	if (ibsta & ERR) {				    /* Check for GPIB Error                    */
		exit_error("Connection with EMCO: Failure\nPlease make sure there is a GPIB connection and the device is switched on."); 
		Sleep(4000);
		GpibError("ibdev Error");
	}
	ibclr(emco_unit);                  /* Clear the device                        */
	if (ibsta & ERR) {
		GpibError("ibclr Error");
	}
}
void emco_unitialization() {
	ibonl(emco_unit, 0);              /* Take the device offline                 */
	if (ibsta & ERR) {
		GpibError("ibonl Error");
	}
	measurements_file.close();
}
void emco_default_configuration() {
	ibwrt(emco_unit, "PR1", 3);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
	int error = 0;
	selected_probe = Buffer[1] - 48;
	ibwrt(emco_unit, "U1", 2);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
	ibwrt(emco_unit, "C1", 2);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
	ibwrt(emco_unit, "T00,0,5", 8);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
	ibwrt(emco_unit, "IT", 2);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
}
int emco_print_measurements_amp_1(unsigned int index_of_vector) {
	std::ofstream measurement_amp_1;
	measurement_amp_1.open("measurement_amp_1.txt");
	if (!measurement_amp_1.is_open()) {
		exit_error("Error, could not ope measurement_amp_1.txt");
		exit(EXIT_FAILURE);
	}
	if (want_vout) {
		while (index_of_vector < meas.field.size()) {
			measurement_amp_1 << meas.field[index_of_vector] << "\t" << meas.frequency[index_of_vector] << "\t" << meas.voltage_smh[index_of_vector] << "\t"
				<< meas.voltage_input_amplifier[index_of_vector] << meas.voltage_output_amplifier[index_of_vector] << "\t" << meas.gain[index_of_vector] << "\n";
			index_of_vector++;
		}
	}
	else {
		while (index_of_vector < meas.field.size()) {
			measurement_amp_1 << meas.field[index_of_vector] << "\t" << meas.frequency[index_of_vector] << "\t" << meas.voltage_smh[index_of_vector] << "\t"
				<< meas.voltage_input_amplifier[index_of_vector] << "\n";
			index_of_vector++;
		}
	}
	measurement_amp_1.close();
	return index_of_vector;
}
int emco_print_measurements_amp_2(unsigned int index_of_vector) {
	std::ofstream measurement_amp_2;
	measurement_amp_2.open("measurement_amp_2.txt");
	if (!measurement_amp_2.is_open()) {
		exit_error("Error, could not ope measurement_amp_2.txt");
		exit(EXIT_FAILURE);
	}
	if (want_vout) {
		while (index_of_vector < meas.field.size()) {
			measurement_amp_2 << meas.field[index_of_vector] << "\t" << meas.frequency[index_of_vector] << "\t" << meas.voltage_smh[index_of_vector] << "\t"
				<< meas.voltage_input_amplifier[index_of_vector] << meas.voltage_output_amplifier[index_of_vector] << "\t" << meas.gain[index_of_vector] << "\n";
			index_of_vector++;
		}
	}
	else {
		while (index_of_vector < meas.field.size()) {
			measurement_amp_2 << meas.field[index_of_vector] << "\t" << meas.frequency[index_of_vector] << "\t" << meas.voltage_smh[index_of_vector] << "\t"
				<< meas.voltage_input_amplifier[index_of_vector] << "\n";
			index_of_vector++;
		}
	}
	measurement_amp_2.close();
	return index_of_vector;
}
int emco_print_measurements_amp_3(unsigned int index_of_vector) {
	std::ofstream measurement_amp_3;
	measurement_amp_3.open("measurement_amp_3.txt");
	if (!measurement_amp_3.is_open()) {
		exit_error("Error, could not ope measurement_amp_3.txt");
		exit(EXIT_FAILURE);
	}
	if (want_vout) {
		while (index_of_vector < meas.field.size()) {
			measurement_amp_3 << meas.field[index_of_vector] << "\t" << meas.frequency[index_of_vector] << "\t" << meas.voltage_smh[index_of_vector] << "\t"
				<< meas.voltage_input_amplifier[index_of_vector] << meas.voltage_output_amplifier[index_of_vector] << "\t" << meas.gain[index_of_vector] << "\n";
			index_of_vector++;
		}
	}
	else {
		while (index_of_vector < meas.field.size()) {
			measurement_amp_3 << meas.field[index_of_vector] << "\t" << meas.frequency[index_of_vector] << "\t" << meas.voltage_smh[index_of_vector] << "\t"
				<< meas.voltage_input_amplifier[index_of_vector] << "\n";
			index_of_vector++;
		}
	}
	measurement_amp_3.close();
	return index_of_vector;
}
int emco_print_measurements_amp_4(unsigned int index_of_vector) {
	std::ofstream measurement_amp_4;
	measurement_amp_4.open("measurement_amp_4.txt");
	if (!measurement_amp_4.is_open()) {
		exit_error("Error, could not ope measurement_amp_4.txt");
		exit(EXIT_FAILURE);
	}
	if (want_vout) {
		while (index_of_vector < meas.field.size()) {
			measurement_amp_4 << meas.field[index_of_vector] << "\t" << meas.frequency[index_of_vector] << "\t" << meas.voltage_smh[index_of_vector] << "\t"
				<< meas.voltage_input_amplifier[index_of_vector] << meas.voltage_output_amplifier[index_of_vector] << "\t" << meas.gain[index_of_vector] << "\n";
			index_of_vector++;
		}
	}
	else {
		while (index_of_vector < meas.field.size()) {
			measurement_amp_4 << meas.field[index_of_vector] << "\t" << meas.frequency[index_of_vector] << "\t" << meas.voltage_smh[index_of_vector] << "\n";
			index_of_vector++;
		}
	}
	measurement_amp_4.close();
	return index_of_vector;
}
int emco_print_measurements_amp_5(unsigned int index_of_vector) {
	std::ofstream measurement_amp_5;
	measurement_amp_5.open("measurement_amp_5.txt");
	if (!measurement_amp_5.is_open()) {
		exit_error("Error, could not ope measurement_amp_5.txt\n");
		exit(EXIT_FAILURE);
	}
	if (want_vout) {
		while (index_of_vector < meas.field.size()) {
			measurement_amp_5 << meas.field[index_of_vector] << "\t" << meas.frequency[index_of_vector] << "\t" << meas.voltage_smh[index_of_vector] << "\t"
				<< meas.voltage_input_amplifier[index_of_vector] << meas.voltage_output_amplifier[index_of_vector] << "\t" << meas.gain[index_of_vector] << "\n";
			index_of_vector++;
		}
	}
	else {
		while (index_of_vector < meas.field.size()) {
			measurement_amp_5 << meas.field[index_of_vector] << "\t" << meas.frequency[index_of_vector] << "\t" << meas.voltage_smh[index_of_vector] << "\n";
			index_of_vector++;
		}
	}
	measurement_amp_5.close();
	return index_of_vector;
}
int emco_print_measurements_amp_6(unsigned int index_of_vector) {
	std::ofstream measurement_amp_6;
	measurement_amp_6.open("measurement_amp_6.txt");
	if (!measurement_amp_6.is_open()) {
		exit_error("Error, could not ope measurement_amp_6.txt");
		exit(EXIT_FAILURE);
	}
	if (want_vout) {
		while (index_of_vector < meas.field.size()) {
			measurement_amp_6 << meas.field[index_of_vector] << "\t" << meas.frequency[index_of_vector] << "\t" << meas.voltage_smh[index_of_vector] << "\t"
				<< meas.voltage_input_amplifier[index_of_vector] << meas.voltage_output_amplifier[index_of_vector] << "\t" << meas.gain[index_of_vector] << "\n";
			index_of_vector++;
		}
	}
	else {
		while (index_of_vector < meas.field.size()) {
			measurement_amp_6 << meas.field[index_of_vector] << "\t" << meas.frequency[index_of_vector] << "\t" << meas.voltage_smh[index_of_vector] << "\n";
			index_of_vector++;
		}
	}
	measurement_amp_6.close();
	return index_of_vector;
}
int emco_print_measurements_amp_7(unsigned int index_of_vector) {
	std::ofstream measurement_amp_7;
	measurement_amp_7.open("measurement_amp_7.txt");
	if (!measurement_amp_7.is_open()) {
		exit_error("Error, could not ope measurement_amp_7.txt\n");
		exit(EXIT_FAILURE);
	}
	if (want_vout) {
		while (index_of_vector < meas.field.size()) {
			measurement_amp_7 << meas.field[index_of_vector] << "\t" << meas.frequency[index_of_vector] << "\t" << meas.voltage_smh[index_of_vector] << "\t"
				<< meas.voltage_input_amplifier[index_of_vector] << meas.voltage_output_amplifier[index_of_vector] << "\t" << meas.gain[index_of_vector] << "\n";
			index_of_vector++;
		}
	}
	else {
		while (index_of_vector < meas.field.size()) {
			measurement_amp_7 << meas.field[index_of_vector] << "\t" << meas.frequency[index_of_vector] << "\t" << meas.voltage_smh[index_of_vector] << "\n";
			index_of_vector++;
		}
	}
	measurement_amp_7.close();
	return index_of_vector;
}
double emco_measure(){
	ibwrt(emco_unit, "RA?", 3);
	if (ibsta & ERR) {
		GpibError("ibwrt Error");
	}
	ibrd(emco_unit, Buffer, 30);
	if (ibsta & ERR) {
		GpibError("ibrd Error");
	}
	Buffer[ibcntl] = '\0';
	return atof(Buffer);
}
void make_new_file() {
	std::ofstream outfile;
	std::string file = current_path + file_name + ".txt";
	outfile.open(file.c_str());
	if (!outfile.is_open()) {
		exit_error("Error, could not open the file");
		exit(EXIT_FAILURE);
	}
	std::string word;
	outfile << "emco_primary_addres\t" << emco_primary_address << "\n";
	outfile << "urv5_primary_address\t" << urv5_primary_address << "\n";
	outfile << "smh_primary_address\t" << smh_primary_address << "\n";
	outfile << "hp_primary_address\t" << hp_primary_address << "\n";
	outfile << "afg_primary_address\t" << afg_primary_address << "\n";
	outfile << "urv5_2_primary_address\t" << urv5_2_primary_address << "\n";
	outfile << "initial_frequency\t" << initial_frequency << "\n";
	outfile << "final_frequency\t" << final_frequency << "\n";
	outfile << "modulation_depth\t" << modulation_depth << "\n";
	outfile << "carrier_frequency\t" << carrier_frequency << "\n";
	outfile << "dwell_time\t" << dwell_time << "\n";
	outfile << "field_at_eut\t" << field_at_eut << "\n";
	outfile << "min_freq_amp_1\t" << min_freq_amp_1 << "\n";
	outfile << "min_freq_amp_2\t" << min_freq_amp_2 << "\n";
	outfile << "min_freq_amp_3\t" << min_freq_amp_3 << "\n";
	outfile << "min_freq_amp_4\t" << min_freq_amp_4 << "\n";
	outfile << "min_freq_amp_5\t" << min_freq_amp_5 << "\n";
	outfile << "min_freq_amp_6\t" << min_freq_amp_6 << "\n";
	outfile << "min_freq_amp_7\t" << min_freq_amp_7 << "\n";
	outfile << "max_freq_amp_1\t" << max_freq_amp_1 << "\n";
	outfile << "max_freq_amp_2\t" << max_freq_amp_2 << "\n";
	outfile << "max_freq_amp_3\t" << max_freq_amp_3 << "\n";
	outfile << "max_freq_amp_4\t" << max_freq_amp_4 << "\n";
	outfile << "max_freq_amp_5\t" << max_freq_amp_5 << "\n";
	outfile << "max_freq_amp_6\t" << max_freq_amp_6 << "\n";
	outfile << "max_freq_amp_7\t" << max_freq_amp_7 << "\n";
	outfile << "max_voltage_amp_1\t" << max_voltage_amp_1 << "\n";
	outfile << "max_voltage_amp_2\t" << max_voltage_amp_2 << "\n";
	outfile << "max_voltage_amp_3\t" << max_voltage_amp_3 << "\n";
	outfile << "max_voltage_amp_4\t" << max_voltage_amp_4 << "\n";
	outfile << "max_voltage_amp_5\t" << max_voltage_amp_5 << "\n";
	outfile << "max_voltage_amp_6\t" << max_voltage_amp_6 << "\n";
	outfile << "max_voltage_amp_7\t" << max_voltage_amp_7 << "\n";
	outfile << "amplifier_name_1\t" << amplifier_name_1 << "\n";
	outfile << "amplifier_name_2\t" << amplifier_name_2 << "\n";
	outfile << "amplifier_name_3\t" << amplifier_name_3 << "\n";
	outfile << "amplifier_name_4\t" << amplifier_name_4 << "\n";
	outfile << "amplifier_name_5\t" << amplifier_name_5 << "\n";
	outfile << "amplifier_name_6\t" << amplifier_name_6 << "\n";
	outfile << "amplifier_name_7\t" << amplifier_name_7 << "\n";
	outfile << "measurement_done\t" << 0 << "\n";
	outfile << "amp_1\t" << 0 << "\n";
	outfile << "amp_2\t" << 0 << "\n";
	outfile << "amp_3\t" << 0 << "\n";
	outfile << "amp_4\t" << 0 << "\n";
	outfile << "amp_5\t" << 0 << "\n";
	outfile << "amp_6\t" << 0 << "\n";
	outfile << "amp_7\t" << 0 << "\n";
	outfile.close();
}
/*
*=========================================================================================
 *  This class is a Mock for the eHealth sensor platform, which is described below:
 *
 *  The mock is produced for testing Arduino software without needing to set up the
 *  physical eHealth devices.
 *
 *  Written by:
 *  Edwin Brackenreg - University of Sydney - School of Electrical and Information Engineering
 *  October 2016
 *========================================================================================
 *  eHealth sensor platform for Arduino and Raspberry from Cooking-hacks.
 *
 *  Description: "The e-Health Sensor Shield allows Arduino and Raspberry Pi
 *  users to perform biometric and medical applications by using 9 different
 *  sensors: Pulse and Oxygen in Blood Sensor (SPO2), Airflow Sensor (Breathing),
 *  Body Temperature, Electrocardiogram Sensor (ECG), Glucometer, Galvanic Skin
 *  Response Sensor (GSR - Sweating), Blood Pressure (Sphygmomanometer) and
 *  Patient Position (Accelerometer)."
 *
 *  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version 2.0
 *  Author: Luis Martín & Ahmad Saad
 */


// include this library's description file
#include "eHealthMock.h"


//***************************************************************
// Accelerometer Variables and definitions						*
//***************************************************************

	//! not the wire library, can't use pull-ups
	#include "utils/i2c.h"

	//! Breakout board defaults to 1, set to 0 if SA0 jumper is set
	#define SA0 1
		#if SA0
			#define MMA8452_ADDRESS 0x1D  //! SA0 is high, 0x1C if low
		#else
			#define MMA8452_ADDRESS 0x1C
		#endif

	#define	int1Pin 2
	#define int2Pin 3

	//! Set the scale below either 2, 4 or 8.
	const byte scale = 2;

	//! Set the output data rate below. Value should be between 0 and 7.
	//! 0=800Hz, 1=400, 2=200, 3=100, 4=50, 5=12.5, 6=6.25, 7=1.56
	const byte dataRate = 0;


//***************************************************************
// Constructor of the class										*
//***************************************************************

	//! Function that handles the creation and setup of instances
	eHealthClassMock::eHealthClassMock(void) {

	    /*void constructor*/
        // Set up the random number seed. Used in various places
        randomSeed(micros());
    }


//***************************************************************
// Public Methods												*
//***************************************************************


	//!******************************************************************************
	//!	Name:	initPositionSensor()												*
	//!	Description: Initializes the position sensor and configure some values.		*
	//!	Param : void																*
	//!	Returns: void																*
	//!	Example: eHealth.initPositionSensor();										*
	//!******************************************************************************

	void eHealthClassMock::initPositionSensor(void)
	{
        // Nothing to do
	}


	//!******************************************************************************
	//!	Name:	readBloodPressureSensor()											*
	//!	Description: Initializes the BloodPressureSensor sensor.					*
	//!	Param : void																*
	//!	Returns: void																*
	//!	Example: eHealth.initBloodPressureSensor();									*
	//!******************************************************************************

	void eHealthClassMock::readBloodPressureSensor(void)
	{

        length = 5;// The protocol sends the number of measures

        for (int i = 0; i<length; i++) { // The protocol sends data in this order
            bloodPressureDataVector[i].year = 2016
            bloodPressureDataVector[i].month = 10
            bloodPressureDataVector[i].day = 10
            bloodPressureDataVector[i].hour = 10
            bloodPressureDataVector[i].minutes = 10
            bloodPressureDataVector[i].systolic = 120
            bloodPressureDataVector[i].diastolic = 80
            bloodPressureDataVector[i].pulse = 65
        }
	}



	//!******************************************************************************
	//!		Name:	initPulsioximeter()												*
	//!		Description: Initializes the pulsioximeter sensor.						*
	//!		Param : void															*
	//!		Returns: void															*
	//!		Example: eHealth.initPulsioximeter();									*
	//!******************************************************************************

	void eHealthClassMock::initPulsioximeter(void)
	{
		// Nothing to do
	}

	//!******************************************************************************
	//!		Name:	getTemperature()												*
	//!		Description: Returns the corporal temperature.							*
	//!		Param : void															*
	//!		Returns: float with the corporal temperature value.						*
	//!		Example: float temperature = eHealth.getTemperature();					*
	//!******************************************************************************

	float eHealthClassMock::getTemperature(void)
	{
		//Local variables
		float Temperature = 37.5; //Corporal Temperature

		return Temperature;
	}

	//!******************************************************************************
	//!		Name:	getOxygenSaturation()											*
	//!		Description: Returns the oxygen saturation in blood in percent.			*
	//!		Param : void															*
	//!		Returns: int with the oxygen saturation value							*
	//!		Example: int SPO2 = eHealth.getOxygenSaturation();						*
	//!******************************************************************************

	int eHealthClassMock::getOxygenSaturation(void)
	{
		return SPO2;
	}

	//!******************************************************************************
	//!		Name:	getBPM()														*
	//!		Description: Returns the heart beats per minute.						*
	//!		Param : void															*
	//!		Returns: int with the beats per minute									*
	//!		Example: int BPM = eHealth.getBPM();									*
	//!******************************************************************************

	int eHealthClassMock::getBPM(void)
	{
		return BPM;
	}


	//!******************************************************************************
	//!		Name:	getSkinConductance()											*
	//!		Description: Returns the value of skin conductance.						*
	//!		Param : void															*
	//!		Returns: float with the value of skin conductance						*
	//!		Example: float conductance = eHealth.getSkinConductance();				*
	//!******************************************************************************

	float eHealthClassMock::getSkinConductance(void)
	{
		// Local variable declaration.
		float conductance = -1.0;
		delay(1);

		float voltage = eHealthClassMock::getSkinConductanceVoltage(void)

        if(voltage > 0) {
            conductance = 20*((voltage - 0.5));
        }

		delay(1);

		return conductance;
	}


	//!******************************************************************************
	//!		Name:	getSkinResistance()												*
	//!		Description: Returns the value of skin resistance.						*
	//!		Param : void															*
	//!		Returns: float with the value of skin resistance						*
	//!		Example: float resistance = eHealth.getSkinResistance();				*
	//!******************************************************************************

	float eHealthClassMock::getSkinResistance(void)
	{
		// Local variable declaration.
		float resistance = -1;
		float conductance = eHealthClassMock::getSkinConductance(void);

		//Conductance calcultacion
		if(conductance > 0) {
            resistance = 1 / (conductance / 1000000);
        }

		delay(2);

		return resistance;
	}


	//!******************************************************************************
	//!		Name:	getSkinConductanceVoltage()										*
	//!		Description: Returns the skin conductance value in voltage .			*
	//!		Param : void															*
	//!		Returns: float with the skin conductance value in voltage 				*
	//!		Example: float volt = eHealth.getSkinConductanceVoltage();				*
	//!******************************************************************************

	float eHealthClassMock::getSkinConductanceVoltage(void)
	{
		delay(2);

		//Get a random number instead of analog pin value
		int sensorValue = random(1, 1024);

		//Convert the random value to voltage.
		float voltage = ( sensorValue * 5.0 ) / 1023;

		delay(2);
		return voltage;
	}


	//!******************************************************************************
	//!		Name:	getECG()														*
	//!		Description: Returns an analogic value to represent the ECG.			*
	//!		Param : void															*
	//!		Returns: float with the ECG value in voltage			 				*
	//!		Example: float volt = eHealth.getECG();									*
	//!******************************************************************************

	float eHealthClassMock::getECG(void)
	{
		float analog0;
		// Get random value
		int sensorValue = random(1, 1024);

		// Convert to voltage
		analog0 = (float)sensorValue * 5 / 1023.0;

		return analog0;
	}


	//!******************************************************************************
	//!		Name:	getEMG()														*
	//!		Description: Returns an analogic value to represent the EMG.			*
	//!		Param : void															*
	//!		Returns: float with the EMG value in voltage			 				*
	//!		Example: float volt = eHealth.getEMG();									*
	//!******************************************************************************

	int eHealthClassMock::getEMG(void)
	{
		float analog0;
		// Get random value
		int sensorValue = random(1, 1024);

		// Convert to voltage
		analog0 = (float)sensorValue * 5 / 1023.0;

		return analog0;
	}


	//!******************************************************************************
	//!		Name:	getBodyPosition()												*
	//!		Description: Returns the current body position.							*
	//!		Param : void															*
	//!		Returns: uint8_t with the the position of the pacient.	 				*
	//!		Example: uint8_t position = eHealth.getBodyPosition();					*
	//!******************************************************************************

	uint8_t eHealthClassMock::getBodyPosition(void)
	{

		return 125;
	}


	//!******************************************************************************
	//!		Name:	getSystolicPressure()											*
	//!		Description: Returns the  value of the systolic pressure.				*
	//!		Param : void															*
	//!		Returns: int with the systolic pressure.								*
	//!		Example: int systolic = eHealth.getSystolicPressure();					*
	//!******************************************************************************

	int eHealthClassMock::getSystolicPressure(int i)
	{
		return bloodPressureDataVector[i].systolic;
	}


	//!******************************************************************************
	//!		Name:	getDiastolicPressure()											*
	//!		Description: Returns the  value of the diastolic pressure.				*
	//!		Param : void															*
	//!		Returns: int with the diastolic pressure.								*
	//!		Example: int diastolic = eHealth.getDiastolicPressure();				*
	//!******************************************************************************

	int eHealthClassMock::getDiastolicPressure(int i)
	{
		return bloodPressureDataVector[i].diastolic;
	}


	//!******************************************************************************
	//!		Name:	getAirFlow()													*
	//!		Description: Returns an analogic value to represent the air flow.		*
	//!		Param : void															*
	//!		Returns: int with the airFlow value (0-1023).							*
	//!		Example: int airFlow = eHealth.getAirFlow();							*
	//!******************************************************************************

	int eHealthClassMock::getAirFlow(void)
	{
		return 50;
	}


	//!******************************************************************************
	//!		Name:	printPosition()													*
	//!		Description: Returns an analogic value to represent the air flow.		*
	//!		Param : uint8_t position : the current body position. 					*
	//!		Returns: void															*
	//!		Example: eHealth.printPosition(position);								*
	//!******************************************************************************

	void eHealthClassMock::printPosition( uint8_t position )
	{
		if (position == 1) {
			Serial.println("Prone position");
		} else if (position == 2) {
			Serial.println("Stand or sit position");
		} else if (position == 3) {
			Serial.println("Left lateral decubitus");
		} else if (position == 4) {
			Serial.println("Supine position");
		} else if (position == 5) {
			Serial.println("Rigth lateral decubitus");
		} else  {
			Serial.println("non-defined position");
		}
	}


	//!******************************************************************************
	//!		Name:	readPulsioximeter()												*
	//!		Description: It reads a value from pulsioximeter sensor.				*
	//!		Param : void										 					*
	//!		Returns: void															*
	//!		Example: readPulsioximeter();											*
	//!******************************************************************************

	void eHealthClassMock::readPulsioximeter(void)
	{
			SPO2 = 98;
			BPM  = 75;
	}


	//!******************************************************************************
	//!		Name: airflowWave()														*
	//!		Description: It prints air flow wave form in the serial monitor			*
	//!		Param : int air with the analogic value									*
	//!		Returns: void															*
	//!		Example: eHealth.airflowWave();											*
	//!******************************************************************************

	void eHealthClassMock::airFlowWave(int air)
	{
		for (int i=0; i < (air / 5) ; i ++) {
				Serial.print("..");
		}

		Serial.print("..");
		Serial.print("\n");
		delay(25);
	}


	//!******************************************************************************
	//!		Name: readGlucometer()													*
	//!		Description: It reads the data stored in the glucometer					*
	//!		Param : void															*
	//!		Returns: void															*
	//!		Example: eHealth.readGlucometer();										*
	//!******************************************************************************

	void eHealthClassMock::readGlucometer(void)
	{

        length = 5;// The protocol sends the number of measures

        for (int i = 0; i<length; i++) { // The protocol sends data in this order
            glucoseDataVector[i].year = 2016;
            glucoseDataVector[i].month = 10;
            glucoseDataVector[i].day = 10;
            glucoseDataVector[i].hour = 10;
            glucoseDataVector[i].minutes = 10;

            glucoseDataVector[i].glucose = 5;
            glucoseDataVector[i].meridian = 4;
        }
	}

	//!******************************************************************************
	//!		Name: getGlucometerLength()												*
	//!		Description: it returns the number of data stored in the glucometer		*
	//!		Param : void															*
	//!		Returns: uint8_t with length											*
	//!		Example: int length = eHealth.getGlucometerLength();					*
	//!******************************************************************************

	uint8_t eHealthClassMock::getGlucometerLength(void)
	{
		return length;
	}

	//!******************************************************************************
	//!		Name: getBloodPressureLength()											*
	//!		Description: it returns the number of data stored in					*
	//!		the blood pressure sensor												*
	//!		Param : void															*
	//!		Returns: uint8_t with length											*
	//!		Example: int length = eHealth.getBloodPressureLength();					*
	//!******************************************************************************

	uint8_t eHealthClassMock::getBloodPressureLength(void)
	{
		return length;
	}


	//!******************************************************************************
	//!		Name: numberToMonth()													*
	//!		Description: Convert month variable from numeric to character.			*
	//!		Param : int month in numerical format									*
	//!		Returns: String with the month characters (January, February...).		*
	//!		Example: Serial.print(eHealth.numberToMonth(month));					*
	//!******************************************************************************

	String eHealthClassMock::numberToMonth(int month)
	{
		if (month == 1)  return "January";
		else if (month == 2)  return "February";
		else if (month == 3)  return "March";
		else if (month == 4)  return "April";
		else if (month == 5)  return "May";
		else if (month == 6)  return "June";
		else if (month == 7)  return "July";
		else if (month == 8)  return "August";
		else if (month == 9)  return "September";
		else if (month == 10) return "October";
		else if (month == 11) return "November";
		else return "December";
	}


	//!******************************************************************************
	//!		Name:	version()														*
	//!		Description: It check the version of the library						*
	//!		Param : void															*
	//!		Returns: void															*
	//!		Example: eHealth.version();												*
	//!******************************************************************************

	int eHealthClassMock::version(void)
	{
		return 1.0;
	}


//***************************************************************
// Private Methods												*
//***************************************************************

	//! This function will read the p/l source register and
	//!	print what direction the sensor is now facing */

	void eHealthClassMock::portraitLandscapeHandler()
	{
        position[0] = 3;

        position[1] = 0;

        position[2] = 1;

		bodyPosition();
	}

/*******************************************************************************************************/

	//! Initialize the MMA8452 registers.

	void eHealthClassMock::initMMA8452(byte fsr, byte dataRate)
	{
		// Do nothing

	}

/*******************************************************************************************************/

	//! Sets the MMA8452 to standby mode. It must be in standby to change most register settings.

	void eHealthClassMock::MMA8452Standby()
	{
		// Do nothing
	}

/*******************************************************************************************************/

	//! Sets the MMA8452 to active mode. Needs to be in this mode to output data

	void eHealthClassMock::MMA8452Active()
	{
		// Do nothing
	}

/*******************************************************************************************************/

	//! Read i registers sequentially, starting at address into the dest byte array.
	void eHealthClassMock::readRegisters(byte address, int i, byte * dest)
	{
		// Do nothing
	}

/*******************************************************************************************************/

	//! Read a single byte from address and return it as a byte.

	byte eHealthClassMock::readRegister(uint8_t address)
	{
		// Do nothing

		return 1;
	}

/*******************************************************************************************************/

	//! Writes a single byte (data) into address
	void eHealthClassMock::writeRegister(unsigned char address, unsigned char data)
	{
		// Do nothing
	}

/*******************************************************************************************************/

	//! Assigns a value depending on body position.

	void eHealthClassMock::bodyPosition( void )
	{
        bodyPos = 6;
	}

/*******************************************************************************************************/

	//! Converts from 7 segments to number.

	uint8_t eHealthClassMock::segToNumber(uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F, uint8_t G )
	{
        return 0;
	}

/*******************************************************************************************************/

	//! Swap data for blood pressure mesure

	char eHealthClassMock::swap(char _data)
	{
		char highBits = (_data & 0xF0) / 16;
 		char lowBits =  (_data & 0x0F) * 16;
  		return ~(highBits + lowBits);
	}

/*******************************************************************************************************/

//***************************************************************
// Preinstantiate Objects										*
//***************************************************************

	eHealthClassMock eHealth = eHealthClassMock();






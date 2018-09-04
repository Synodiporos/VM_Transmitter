/*
 * Controller.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#include "Controller.h"

Controller::Controller(){

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

void Controller::activate(){
	if(batteryMonitor)
		batteryMonitor->setBatteryMonitorListener(this);
	if(probeA)
		probeA->setListener(this);
	if(transceiver)
		transceiver->setActionListener(this);
	if(notification){
		notification->setActiveEnabled(true);
		notification->setEnabled(true);
	}
	initialization();
}

void Controller::deactivate(){
	if(batteryMonitor)
		batteryMonitor->setBatteryMonitorListener(nullptr);
	if(probeA)
		probeA->setListener(nullptr);
	if(transceiver)
			transceiver->setActionListener(nullptr);
	//if(notification)
	//	notification->stopNotify();
}

void Controller::initialization(){
	bool batteryAlarm = this->batteryMonitor->isAlarmEnabled();
	this->notification->setBatteryLowEnabled(batteryAlarm);

	bool connState = transceiver->isConnected();
 	this->notification->setConnectionLostEnabled(!connState);

 	notification->setActiveEnabled(true);
 	notification->setEnabled(true);
 	//probeA->setEnabled(true);
 	/*unsigned int hvValue = this->probeA->getMeasurement();
 	if(	hvValue >= NOT_HVWARNING_TRIG ){
		notification->setHVWarningEnabled(true);
		batteryMonitor->pauseRecord();
	}else{
		notification->setHVWarningEnabled(false);
		batteryMonitor->startRecord();
	}*/
}

void Controller::setBatteryMonitor(BatteryMonitor* batteryMonitor){
	this->batteryMonitor = batteryMonitor;
}

void Controller::setProbeA(Probe* probe){
	if(this->probeA!=probe){
		if(this->probeA)
			this->probeA->setListener(nullptr);
		if(probe)
			probe->setListener(this);
		this->probeA = probe;
	}
}

/*void Controller::setProbeA(HVProbe* probe){
	if(this->probeA!=probe){
		if(this->probeA)
			this->probeA->setMeasurementListener(nullptr);
		if(probe)
			probe->setMeasurementListener(this);
		this->probeA = probe;
	}
}*/

void Controller::propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery){
	if(source==this->probeA){
		onProbeAMeasurementChanged(this->probeA->getMeasurement());
	}
}

void Controller::actionPerformed(Action action){
	void* source = action.getSource();
	if(source==transceiver){
		unsigned int id = action.getActionId();
		switch(id){
			case RFTransceiver::ON_MESSAGE_RECEIVED:{
				char* msg = (char*)action.getContainer();
				onMessageReceived(msg);
				break;
			}
			case RFTransceiver::ON_MESSAGE_SEND:{
				char* msg = (char*)action.getContainer();
				onMessageSend(msg);
				break;
			}
			case RFTransceiver::ON_CONNECTION_STATE:{
				bool* state = (bool*)action.getContainer();
				onConnectionStateChanged(*state);
				break;
			}
		}
	}
}

bool Controller::isSleep(){
	return this->sleep;
}

void Controller::onSystemStartUp(){
	Serial.println("System Start Up!");

	transceiver->powerUp();
	transceiver->startConnectivityCheck();
	batteryMonitor->measure();
	notification->startNotify();
}

void Controller::onSystemSleep(){
	Serial.println("System SLEEP!");
	//SPI.end();
	//pinMode(2, INPUT_PULLUP);
	transceiver->powerDown();

	//notification->notifyActive();

	unsigned long time = millis();
	while(millis()-time<60){
		notification->validate();
		resetSleepTimer();
	}
}

void Controller::onSystemWakeup(uint8_t source){
	Serial.println();
	if(source==SYSTEM_INTER){
		Serial.println("ON Wake Up by INTERRUPT");
	}
	else{
		Serial.println("ON Wake Up by TIMER");
	}

	transceiver->powerUp();
	transceiver->startConnectivityCheck();
	batteryMonitor->measure();
	notification->startNotify();

	sleep = false;
	resetSleepTimer();
}

void Controller::onIterrate(){

	probeA->validate();
	batteryMonitor->validate();
	transceiver->validate();
	notification->validate();

	unsigned long interval = millis()-sleepTimer;
	unsigned long interval2 = millis()-timer2;
	if(!hvWarning && interval>=WAKEUP_INTERVAL){
		sleep = true;
	}

	if(interval2>=100){
	//	Serial.println("ON Iterate");
		timer2 = millis();
	}
}

void Controller::resetSleepTimer(){
	sleepTimer = millis();
}

void Controller::onProbeAMeasurementChanged(unsigned short int value){
	if(	value >= SM_SURGE_MIN){
		hvWarning = true;
		notification->setHVWarningEnabled(true);
		//batteryMonitor->pauseRecord();
		transceiver->setAutoSleep(false);
	}else{
		hvWarning = false;
		notification->setHVWarningEnabled(false);
		//batteryMonitor->startRecord();
		transceiver->setAutoSleep(true);
		resetSleepTimer();
	}

	surgeMonitor.setDevice(1);
	surgeMonitor.setMeasurement(value);

	char at[RF_PAYLOAD_SIZE];
	char str[] = CMD_HV1;
	unsigned int hv = (AREF_VOLTAGE * value)/FACTOR_10350; //volts*100;
	/*unsigned int volts =
			(((AREF_VOLTAGE * value)/1023) + HVPROBE_VOLTS_OFFSET)
			*100;*/
	sprintf (at, "AT+%s=%d", str, hv);
	//7+5+1
	this->transceiver->write(at);
	//Serial.println(at);

	//delay(1);
	Serial.print(F("HVProbe Value: "));
	Serial.print(value);
	Serial.print(F(" Voltage: "));
	Serial.print(probeA->voltage(AREF_VOLTAGE, 0));
	Serial.print(F(" Measurement: "));
	Serial.print(hv);
	Serial.println( HVPROBE_UNITS );
}

void Controller::onBatteryValueChanged(
			BatteryMonitor* source, short int oldValue){
	float vin = source->getMeasurementValue();
	uint8_t perc = source->getPercentage();
	uint8_t alarm = source->isAlarmEnabled();

	/*Serial.print(F("Battery Volts: "));
	Serial.print(vin);
	Serial.print(F("V Percentage: "));
	Serial.print(perc);
	Serial.print( "%" );
	Serial.print(F(" Alarm: "));
	Serial.println(alarm);*/

	char at[RF_PAYLOAD_SIZE];
	char str[] = CMD_BAT;
	sprintf (at, "AT+%s=%d,%d", str, (int)vin*100, perc);
	//3+4+4+4+1+1
	this->transceiver->write(at);
	//Serial.println(at);
}

void Controller::onBatteryTriggerAlarmStateChanged(
			BatteryMonitor* source, bool alarm){
	Serial.print(F("Battery Alarm State: "));
	Serial.println(alarm);
	this->notification->setBatteryLowEnabled(alarm);
}

void Controller::onMessageReceived(char* msg){
	Serial.print(F("Slave RF Message Received: "));
	Serial.println(msg);

	std::string input = string(msg);
	std::string cmdN;
	vector<string> params;
	AT::parse(input, cmdN, params);

	if(cmdN.compare(ATCMDs::AT_ACK)==0){
		char at[RF_PAYLOAD_SIZE];
		char str[] = CMD_ACR;
		sprintf (at, "AT+%s", str);
		RFTransceiver::getInstance()->write(at);
	}



	//CMD* cmd = AT::toCMD(input);
	//cmd->execute();

	/*Serial.print(F("CMD: "));
	Serial.print(input.c_str());
	Serial.print(F(" at= "));
	Serial.println(cmdN.c_str());*/
	//delete cmd;
	resetSleepTimer();
}

void Controller::onMessageSend(char* msg){

}

void Controller::onConnectionStateChanged(bool state){
	Serial.print(F("# Connection State: "));
	Serial.println(state);
	this->notification->setConnectionLostEnabled(!state);
}

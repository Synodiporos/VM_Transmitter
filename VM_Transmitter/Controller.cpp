/*
 * Controller.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#include "Controller.h"

Controller::Controller(RF24& radio) :
	radio(radio){

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

void Controller::activate(){
	surgeMonitor.setActionListener(this);
	if(batteryMonitor)
		batteryMonitor->setBatteryMonitorListener(this);

	probeA.setListener(this);
	probeB.setListener(this);

	if(transceiver)
		transceiver->setActionListener(this);
	if(notification){
		notification->setActiveEnabled(true);
		notification->setEnabled(true);
	}


}

void Controller::deactivate(){
	surgeMonitor.setActionListener(nullptr);
	if(batteryMonitor)
		batteryMonitor->setBatteryMonitorListener(nullptr);

	probeA.setListener(nullptr);
	probeB.setListener(nullptr);

	if(transceiver)
			transceiver->setActionListener(nullptr);
	//if(notification)
	//	notification->stopNotify();
}

void Controller::initialization(){
	Serial.begin(SRL_BD);

	probeA.setFrequency(HVPROBE_FREQ);
	probeA.setEnabled(true);
	probeB.setFrequency(HVPROBE_FREQ);
	probeB.setEnabled(false);

	//Initialaze RF
	transceiver->initialize();

	bool batteryAlarm = this->batteryMonitor->isAlarmEnabled();
	this->notification->setBatteryLowEnabled(batteryAlarm);

	bool connState = transceiver->isConnected();
 	this->notification->setConnectionLostEnabled(!connState);

 	notification->setActiveEnabled(true);

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

void Controller::resetSleepTimer(){
	sleepTimer = millis();
}

void Controller::propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery){
	if(source == &probeA){
		onProbeAMeasurementChanged(this->probeA.getMeasurement());
	}
	else{
		onProbeBMeasurementChanged(this->probeB.getMeasurement());
	}
}

void Controller::actionPerformed(Action action){
	void* source = action.getSource();
	if(source==transceiver){
		unsigned int id = action.getActionId();
		switch(id){
			case RFTransceiver::ON_MESSAGE_RECEIVED:{
				char* msg = (char*)action.getContainer();
				onRFMessageReceived(msg);
				break;
			}
			case RFTransceiver::ON_RESPONSE_RECEIVED:{
				char* msg = (char*)action.getContainer();
				uint8_t id = 2;
				onRFResponseReceived(msg, id);
				break;
			}
			case RFTransceiver::ON_MESSAGE_SEND:{
				char* msg = (char*)action.getContainer();
				onRFMessageSend(msg);
				break;
			}
			case RFTransceiver::ON_MESSAGE_SEND_ERROR:{
				char* msg = (char*)action.getContainer();
				onRFMessageSendError(msg);
				break;
			}
			case RFTransceiver::ON_CONNECTION_STATE:{
				bool* state = (bool*)action.getContainer();
				onRFStateChanged(
						RFTransceiver::ON_CONNECTION_STATE ,
						*state);
				break;
			}
			case RFTransceiver::ON_ACTIVE_STATE:{
				bool* state = (bool*)action.getContainer();
				onRFStateChanged(
						RFTransceiver::ON_CONNECTION_STATE ,
						*state);
				break;
			}
		}
	}
	else if(source==&surgeMonitor){
		unsigned int id = action.getActionId();
		switch(id){
			case SurgeMonitor::ON_SURGE_APPLIED:{
				unsigned int * data =
						action.getContainer();
				unsigned int device = *data;
				unsigned int max = *(data + 1);
				unsigned int slope = *(data + 2);
				onSurgeApplied(device, max, slope);
				break;
			}
		}
	}
}

bool Controller::isSleep(){
	return this->sleep;
}

void Controller::onSystemStartUp(){
	initialization();
	Serial.println("System Start Up!");

	transceiver->setEnabled(true);
	transceiver->powerUp();
	//transceiver->startConnectivityCheck();
	char at[] = "AT+ACK+1";
	transceiver->send(at, 1);

	batteryMonitor->measure();
	notification->setEnabled(true);
	notification->startNotify();
}

void Controller::onSystemSleep(){
	Serial.println("System SLEEP!");
	//SPI.end();
	//pinMode(2, INPUT_PULLUP);
	transceiver->powerDown();

	unsigned long time = millis();
	while(millis()-time<60){
		notification->validate();
		resetSleepTimer();
	}

	notification->stopNotify();
	notification->setEnabled(false);
	delay(20);
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
	//transceiver->startConnectivityCheck();
	transceiver->send("AT+ACK+1", 1);
	batteryMonitor->measure();
	notification->startNotify();

	sleep = false;
	resetSleepTimer();
}

void Controller::onIterrate(){
	probeA.validate();
	probeB.validate();
	batteryMonitor->validate();
	transceiver->validate();
	notification->validate();

	unsigned long interval = millis()-sleepTimer;
	unsigned long interval2 = millis()-timer2;
	if(!hvWarning && interval>=WAKEUP_INTERVAL &&
			!transceiver->isConnecting()){
		sleep = true;
	}

	if(interval2>=100){
	//	Serial.println("ON Iterate");
		timer2 = millis();
	}
}

void Controller::onProbeAMeasurementChanged(unsigned short int value){
	if(	value >= SM_SURGE_MIN){
		hvWarning = true;
		notification->setHVWarningEnabled(true);
		//batteryMonitor->pauseRecord();
		//transceiver->setAutoSleep(false);
	}else{
		hvWarning = false;
		notification->setHVWarningEnabled(false);
		//batteryMonitor->startRecord();
		//transceiver->setAutoSleep(true);
		resetSleepTimer();
	}

	surgeMonitor.setDevice(1);
	surgeMonitor.setMeasurement(value);

	char at[RF_PAYLOAD_SIZE];
	unsigned int hv = (AREF_VOLTAGE * value)/FACTOR_10350; //volts*100;
	char params[3][8] = {'\0','\0','\0'};
	snprintf(params[0], 8, "%d", hv);
	CharUtil::compineAT(at, CMD_HV1, 0, params);
	this->transceiver->write(at);

	Serial.print(F("HVProbeA Value: "));
	Serial.print(value);
	Serial.print(F(" Voltage: "));
	Serial.print(probeA.voltage(AREF_VOLTAGE, 0));
	Serial.print(F(" Measurement: "));
	Serial.print(hv);
	Serial.println( HVPROBE_UNITS );
}

void Controller::onProbeBMeasurementChanged(unsigned short int value){
	if(	value >= SM_SURGE_MIN){
		hvWarning = true;
		notification->setHVWarningEnabled(true);
		//batteryMonitor->pauseRecord();
		//transceiver->setAutoSleep(false);
	}else{
		hvWarning = false;
		notification->setHVWarningEnabled(false);
		//batteryMonitor->startRecord();
		//transceiver->setAutoSleep(true);
		resetSleepTimer();
	}

	surgeMonitor.setDevice(2);
	surgeMonitor.setMeasurement(value);

	char at[RF_PAYLOAD_SIZE];
	unsigned int hv = (AREF_VOLTAGE * value)/FACTOR_820; //volts*100;
	char params[3][8] = {'\0','\0','\0'};
	snprintf(params[0], 8, "%d", hv);
	CharUtil::compineAT(at, CMD_HV2, 0, params);
	this->transceiver->write(at);

	Serial.print(F("HVProbeB Value: "));
	Serial.print(value);
	Serial.print(F(" Voltage: "));
	Serial.print(probeB.voltage(AREF_VOLTAGE, 0));
	Serial.print(F(" Measurement: "));
	Serial.print(hv);
	Serial.println( HVPROBE_UNITS );
}

void Controller::onSurgeApplied(uint8_t device,
		unsigned int charge, unsigned int slope){

	/*Serial.print("$$$ Surge Applied: ");
	Serial.print(" Device:");
	Serial.print( device);
	Serial.print(" Charge:");
	Serial.print( charge);
	Serial.print(" slope:");
	Serial.print( (float)slope/10);
	Serial.print(" aps");
	Serial.println();*/

	char at[RF_PAYLOAD_SIZE];
	char params[3][8] = {'\0', '\0', '\0'};
	snprintf(params[0], 8, "%d", charge);
	snprintf(params[1], 8, "%lu", slope);
	if(device==1){
		CharUtil::compineAT(at, CMD_SR1, 1, params);
	}
	else{
		CharUtil::compineAT(at, CMD_SR2, 1, params);
	}

	this->transceiver->write(at);
}

void Controller::onBatteryValueChanged(
			BatteryMonitor* source, short int oldValue){
	float vin = source->getMeasurementValue();
	uint8_t perc = source->getPercentage();
	uint8_t alarm = source->isAlarmEnabled();

	Serial.print(F("Battery Volts: "));
	Serial.print(vin);
	Serial.print(F("V Percentage: "));
	Serial.print(perc);
	Serial.print( "%" );
	Serial.print(F(" Alarm: "));
	Serial.println(alarm);

	char at[RF_PAYLOAD_SIZE];
	//char str[] = CMD_BAT;
	unsigned int vout = (float)vin*100;
	//sprintf (at, "AT+%s=%d,%d", str, vout, perc);
	//3+4+4+4+1+1

	char params[3][8];
	snprintf(params[0], 8, "%d", vout);
	snprintf(params[1], 8, "%d", perc);
	snprintf(params[2], 8, "%d", alarm);
	CharUtil::compineAT(at, CMD_BAT, 0, params);
	this->transceiver->write(at);
	//Serial.println(at);
}

void Controller::onBatteryTriggerAlarmStateChanged(
			BatteryMonitor* source, bool alarm){
	Serial.print(F("Battery Alarm State: "));
	Serial.println(alarm);
	this->notification->setBatteryLowEnabled(alarm);
}

void Controller::onRFStateChanged(uint8_t action, uint8_t state){
	if(action==RFTransceiver::ON_CONNECTION_STATE){
		switch(state){
			case RF_STATE_OFF:{
				Serial.println(F("RF OFF"));
				break;
			}
			case RF_STATE_INITIALIZE_ERROR:{
				Serial.println(F("RF INIT ERROR"));
				this->notification->setConnectionLostEnabled(true);
				break;
			}
			case RF_STATE_INITIALIZED:{
				Serial.println(F("RF INITIALIZED"));
				//transceiver->printDetails();
				break;
			}
			case RF_STATE_DISCONNECTED:{
				Serial.println(F("RF DISCONNECTED"));
				this->notification->setConnectionLostEnabled(true);
				break;
			}
			case RF_STATE_CONNECTING:{
				Serial.println(F("RF CONNECTING"));
				break;
			}
			case RF_STATE_CONNECTED:{
				Serial.println(F("RF CONNECTED"));
				this->notification->setConnectionLostEnabled(false);
				break;
			}
		}
	}
	else if(action==RFTransceiver::ON_ACTIVE_STATE){
		if(state){
			Serial.println(F("RF ACTIVE"));
		}
		else{
			Serial.println(F("RF INACTIVE"));
		}
	}
}

void Controller::onRFMessageReceived(char* msg){
	Serial.print(F("RF MESSAGE RECEIVED: "));
	Serial.println(msg);

	std::string input = string(msg);
	std::string cmdN;
	vector<string> params;
	//AT::parse(input, cmdN, params);

	/*String cmd = "AT_";
	cmd += CMD_ACR;
	if(cmdN.compare(cmd.c_str())==0){
		char at[RF_PAYLOAD_SIZE];
		char str[] = CMD_ACR;
		sprintf (at, "AT+%s", str);
		transceiver->write(at);
	}*/



	//CMD* cmd = AT::toCMD(input);
	//cmd->execute();

	/*Serial.print(F("CMD: "));
	Serial.print(input.c_str());
	Serial.print(F(" at= "));
	Serial.println(cmdN.c_str());*/
	//delete cmd;
	resetSleepTimer();
}

void Controller::onRFMessageSend(char* msg){
	Serial.print(F("RF MESSAGE SEND: "));
	Serial.println(msg);
}

void Controller::onRFResponseReceived(char* msg, uint8_t id){
	Serial.print(F("RF RESPONSE SEND: "));
	Serial.println(msg);
}

void Controller::onRFMessageSendError(char* msg){
	Serial.print(F("RF MESSAGE SEND ERROR: "));
	Serial.println(msg);
}

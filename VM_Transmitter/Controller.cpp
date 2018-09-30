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
	button.setButtonListener(this);
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
	button.setButtonListener(nullptr);
}

void Controller::initialization(){
	Serial.begin(SRL_BD);

	probeA.setFrequency(HVPROBE_FREQ);
	probeA.setEnabled(true);
	probeB.setFrequency(HVPROBE_FREQ);
	probeB.setEnabled(true);

	//Initialaze RF
	transceiver->initialize();

	bool batteryAlarm = this->batteryMonitor->isAlarmEnabled();
	this->notification->setBatteryLowEnabled(batteryAlarm);

	bool connState = transceiver->isConnected();
 	this->notification->setConnectionLostEnabled(!connState);

 	notification->setActiveEnabled(true);

 	buffer->initialize();

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

uint8_t Controller::getRequestId(){
	uint8_t id = requestId++;
	if(requestId>=254)
		requestId = 1;
	return id;
}

void Controller::resetSleepTimer(){
	sleepTimer = millis();
}

uint8_t Controller::sendSurgeRequest(
		Surge surge, uint8_t source){
	char * cmd;

	if(surge.device==1)
		cmd = CMD_SR1;
	else
		cmd = CMD_SR2;

	char at[RF_PAYLOAD_SIZE];
	char params[3][8] = {'\0', '\0', '\0'};
	snprintf(params[0], 8, "%lu", surge.charge);
	snprintf(params[1], 8, "%d", surge.slope);
	snprintf(params[2], 8, "%lu", surge.datetime);
	uint8_t id = getRequestId();


	CharUtil::compineAT(at, cmd, id, params);

	uint8_t sps;
	if(source==0)
		sps = this->transceiver->send(at, id) + 1;
	else
		sps = this->transceiver->send(at, id) + 11;

	onSurgeRequestStateChanged(sps);
	if(sps==1){
		//Live request not send
		Serial.println(F("PUSH"));
		buffer->push(surge);
	}
	else if(sps==11){
		//Buffer request not send
	}
	else{

	}

	return sps;
}

void Controller::onSurgeRequestStateChanged(uint8_t state){
	if(this->surgePostState!=state){
		Serial.print(F("SURGE POST STATE: "));
		Serial.println(state);
		this->surgePostState = state;
	}
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
				char c = action.getActionName()[0];
				uint8_t id = c;
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
			case RFTransceiver::ON_REQUEST_SEND_OK:{
				char* msg = (char*)action.getContainer();
				uint8_t rid = action.getActionName()[0];
				onRFRequestPostOK(msg, rid);
				break;
			}
			case RFTransceiver::ON_REQUEST_SEND_FAIL:{
				char* msg = (char*)action.getContainer();
				uint8_t rid = action.getActionName()[0];
				onRFRequestPostFail(msg, rid);
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
			case SurgeMonitor::ON_SM_STATE_CHANGED:{
				uint8_t state = surgeMonitor.getState();
				Surge surge = *(Surge*)action.getContainer();
				switch(state){
					case SM_STATE_CHARGING:{
						Serial.println(F("ON SURGE CHARGING"));
						break;
					}
					case SM_STATE_CHARGED:{
						Serial.println(F("ON SURGE CHARGED"));
						onSurgeApplied(surge);
						break;
					}
					case SM_STATE_DISCHARGED:{
						Serial.println(F("ON SURGE DISCHARGED"));
						break;
					}
				}
				break;
			}
		}
	}
}

void Controller::stateChanged(State state){
	ButtonState stateId = *(ButtonState*)state.getValue();
	onButtonStateChanged(stateId);
}

bool Controller::isSleep(){
	return this->SLEEP;
}

void Controller::onSystemStartUp(){
	initialization();
	Serial.println("System Start Up!");

	transceiver->setEnabled(true);
	transceiver->powerUp();
	//transceiver->startConnectivityCheck();

	char at[RF_PAYLOAD_SIZE];
	char params[3][8] = {'\0','\0','\0'};
	uint8_t id = getRequestId();
	CharUtil::compineAT(at, CMD_ACK, id, params);
	transceiver->send(at, id);

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
	SLEEP = false;
	Serial.println();
	if(source==SYSTEM_INTER){
		Serial.println("ON Wake Up by INTERRUPT");
		WAKEUP_DURATION = WAKEUP_WHEN_HV;
	}
	else{
		Serial.println("ON Wake Up by TIMER");
		WAKEUP_DURATION = WAKEUP_NORMAL;
	}

	transceiver->powerUp();

	char at[RF_PAYLOAD_SIZE];
	char params[3][8] = {'\0','\0','\0'};
	uint8_t id = getRequestId();
	CharUtil::compineAT(at, CMD_ACK, id, params);
	transceiver->send(at, id);

	batteryMonitor->measure();
	notification->startNotify();

	resetSleepTimer();
}

void Controller::onIterrate(){
	probeA.validate();
	probeB.validate();
	surgeMonitor.validate();
	batteryMonitor->validate();
	transceiver->validate();
	notification->validate();
	button.validate();

	unsigned long milliseconds = millis();
	unsigned long intervalSleep = milliseconds-sleepTimer;
	unsigned long intervalBuffer = milliseconds-bufferTimer;
	unsigned long interval2 = milliseconds-timer2;

	//Validate Request Buffer
	if(!buffer->isEmpty() &&
			transceiver->isConnected() &&
			(surgePostState!=2 & surgePostState!=12) &&
			intervalBuffer>256){
		Serial.println(F("There are requests to be send!"));
		buffer->top(surge);
		sendSurgeRequest(surge, 0);
		bufferTimer = millis();
	}

	//Validate un-send request
	/*if(surgePostState == 1 || surgePostState == 3){
		Serial.println(F("PUSH"));
		buffer->push(surge);
		onSurgeRequestStateChanged(0);
	}
	else if(surgePostState == 4){
		Serial.println(F("POP"));
		buffer->pop();
		onSurgeRequestStateChanged(0);
	}*/

	//Validate Sleep
	if(!HVWARNING && intervalSleep>=WAKEUP_DURATION &&
			!transceiver->isSending() &&
			button.getButtonState()==ButtonState::RELEASED){
		SLEEP = true;
	}

	if(interval2>=100){
	//	Serial.println("ON Iterate");
		timer2 = millis();
	}
}

void Controller::onProbeAMeasurementChanged(unsigned short int value){
	HV1 = (AREF_VOLTAGE * value)/FACTOR_10350; //volts*100;
	if(	value >= SM_SURGE_MIN){
		onHVWarningStateChanged(true);
		//notification->setHVWarningEnabled(true);
		//batteryMonitor->pauseRecord();
		//transceiver->setAutoSleep(false);
		probeB.setEnabled(false);
	}else{
		if(HV2<200){
			onHVWarningStateChanged(false);
		}
		//notification->setHVWarningEnabled(false);
		//batteryMonitor->startRecord();
		//transceiver->setAutoSleep(true);
		resetSleepTimer();
		probeB.setEnabled(true);
	}

	surgeMonitor.setDevice(1);
	surgeMonitor.setMeasurement(value);

	char at[RF_PAYLOAD_SIZE];
	char params[3][8] = {'\0','\0','\0'};
	snprintf(params[0], 8, "%ld", (long)HV1);
	CharUtil::compineAT(at, CMD_HV1, 0, params);
	this->transceiver->write(at);

	/*Serial.print(F("HVProbeA Value: "));
	Serial.print(value);
	Serial.print(F(" Voltage: "));
	Serial.print(probeA.voltage(AREF_VOLTAGE, 0));
	Serial.print(F(" Measurement: "));
	Serial.print(HV1);
	Serial.println( HVPROBE_UNITS );
	Serial.println(millis());*/
}

void Controller::onProbeBMeasurementChanged(unsigned short int value){
	HV2 = (long)(AREF_VOLTAGE * value)/FACTOR_820; //volts*100;
	if(	value >= SM_SURGE_MIN){
		onHVWarningStateChanged(true);
		notification->setHVWarningEnabled(true);
		//batteryMonitor->pauseRecord();
		//transceiver->setAutoSleep(false);
		probeA.setEnabled(false);
	}else{
		if(HV1<200){
			onHVWarningStateChanged(false);
		}
		notification->setHVWarningEnabled(false);
		//batteryMonitor->startRecord();
		//transceiver->setAutoSleep(true);
		resetSleepTimer();
		probeA.setEnabled(true);
	}

	surgeMonitor.setDevice(2);
	surgeMonitor.setMeasurement(value);

	char at[RF_PAYLOAD_SIZE];
	char params[3][8] = {'\0','\0','\0'};
	snprintf(params[0], 8, "%ld", HV2);
	CharUtil::compineAT(at, CMD_HV2, 0, params);
	this->transceiver->write(at);

	/*Serial.print(F("HVProbeB Value: "));
	Serial.print(value);
	Serial.print(F(" Voltage: "));
	Serial.print(probeB.voltage(AREF_VOLTAGE, 0));
	Serial.print(F(" Measurement: "));
	Serial.print(HV2);
	Serial.println( HVPROBE_UNITS );
	Serial.println(millis());*/
}

void Controller::onHVWarningStateChanged(bool state){
	if(this->HVWARNING!=state){
		this->HVWARNING = state;
		Serial.println(state);
	}
}

void Controller::onSurgeApplied(Surge surge){
	uint8_t device = surge.device;
	unsigned long chargeVolts;
	unsigned int slopeVolts;
	unsigned long datetime = surge.datetime;
	if(device==1){
		chargeVolts = (AREF_VOLTAGE * surge.charge)/FACTOR_10350;
		slopeVolts =
				(float)(AREF_VOLTAGE * surge.slope)/(FACTOR_10350*100);
	}
	else{
		chargeVolts = (AREF_VOLTAGE * surge.charge)/FACTOR_820;
		slopeVolts =
				(float)(AREF_VOLTAGE * surge.slope)/(FACTOR_820*100);
	}

	surge = {datetime,
			(uint8_t)device,
			(uint32_t)chargeVolts,
			(uint16_t)slopeVolts};

	Serial.print("$$$ Surge Applied: ");
	Serial.print(" Device:");
	Serial.print( device);
	Serial.print(" Charge:");
	Serial.print( chargeVolts);
	Serial.print(" slope:");
	Serial.print( surge.slope);
	Serial.print(" slopeVolts:");
	Serial.println( slopeVolts);

	sendSurgeRequest(surge, 1);
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
			case RF_STATE_REQUEST_ERROR:{
				//DISCONNECTED
				Serial.println(F("RF REQUEST ERROR"));
				//this->notification->setConnectionLostEnabled(true);
				break;
			}
			case RF_STATE_REQUEST_SENDING:{
				Serial.println(F("RF REQUEST SENDING"));
				break;
			}
			case RF_STATE_REQUEST_SEND:{
				//CONNECTED
				Serial.println(F("RF REQUEST SEND"));
				//this->notification->setConnectionLostEnabled(false);
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


void Controller::onRFResponseReceived(char* msg, uint8_t id){
	Serial.print(F("RF RESPONSE RECEIVED: "));
	Serial.println(id);
	resetSleepTimer();
}

void Controller::onRFMessageSend(char* msg){
	Serial.print(F("RF MESSAGE SEND: "));
	Serial.println(msg);
}

void Controller::onRFMessageSendError(char* msg){
	Serial.print(F("RF MESSAGE SEND: "));
	Serial.println(msg);
	resetSleepTimer();
}

void Controller::onRFRequestPostOK(char* msg, uint8_t id){
	Serial.print(F("RF REQUEST SEND OK: "));
	Serial.println(msg);
	resetSleepTimer();
	if(surgePostState == 2){
		onSurgeRequestStateChanged(4);
		//Buffer request POSTED
		Serial.println(F("POP Buffer Request"));
		buffer->pop();
		bufferTimer = millis();
	}
	else if(surgePostState == 12){
		onSurgeRequestStateChanged(14);
		bufferTimer = millis();
	}
}

void Controller::onRFRequestPostFail(char* msg, uint8_t id){
	Serial.print(F("RF REQUEST SEND FAIL: "));
	Serial.println(msg);
	resetSleepTimer();
	if(surgePostState == 2){
		onSurgeRequestStateChanged(3);
		//Buffer request NOT POSTED
		bufferTimer = millis();
	}else if(surgePostState == 12){
		onSurgeRequestStateChanged(13);
		//Live request NOT POSTED
		Serial.println(F("PUSH Live Request"));
		buffer->push(surge);
		bufferTimer = millis();
	}
}

void Controller::onButtonStateChanged(ButtonState state){
	unsigned long interval = millis()-sleepTimer;
	Serial.print(F("Button State: "));
	Serial.println((int)state);
	//Serial.println(interval);
	switch(state){
		case ButtonState::PRESSED:{
			Serial.print(F("&&&     Buffer Size: "));
			Serial.print((int)buffer->getSize());
			Serial.print(F(" index:"));
			Serial.println((int)0);
			break;
		}
		case ButtonState::RELEASED:{
			break;
		}
		case ButtonState::CLICKED:{

			break;
		}
		case ButtonState::HOLDED:{
			buffer->clear();
			Serial.print(F("Clear Buffer Size: "));
			Serial.print((int)buffer->getSize());
			Serial.print(F(" index:"));
			Serial.println((int)0);
			break;
		}
	}
}

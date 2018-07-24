/*
 * CMDBatteryReport.h
 *
 *  Created on: 23 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef CMD_CMDBATTERYREPORT_H_
#define CMD_CMDBATTERYREPORT_H_
#include "../CMD/CMD.h"

class CMDBatteryReport : public CMD{
public:
	CMDBatteryReport();
	CMDBatteryReport(std::vector<string>& params);
	virtual ~CMDBatteryReport();
	int execute();

};

#endif /* CMD_CMDBATTERYREPORT_H_ */

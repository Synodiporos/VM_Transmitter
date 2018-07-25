/*
 * CMDSettings.h
 *
 *  Created on: 24 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef CMD_CMDSETTINGS_H_
#define CMD_CMDSETTINGS_H_

#include "CMD.h"
#include <vector>

class CMDSettings: public CMD {
public:
	CMDSettings();
	CMDSettings(std::vector<string>& params);
	virtual ~CMDSettings();
	string getName();
	int execute();
};

#endif /* CMD_CMDSETTINGS_H_ */

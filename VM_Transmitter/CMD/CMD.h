/*
 * CMD.h
 *
 *  Created on: Jul 23, 2018
 *      Author: sgeorgiadis
 */

#ifndef CMD_CMD_H_
#define CMD_CMD_H_
#include <string>
#include <vector>
using namespace std;

class CMD {
public:

	static const uint8_t SYSTEM = 0;
	static const uint8_t SRL = 1;
	static const uint8_t RF = 2;
	static const uint8_t ESP = 3;

	CMD();
	CMD(std::vector<string>& params);
	virtual ~CMD();

	virtual std::string getName();
	virtual void setParams(std::vector<string>& params);
	virtual std::vector<string>& getParams();
	virtual void setSource(uint8_t source);
	virtual uint8_t getSource();

	virtual int execute() = 0;

	void print();

protected:
	std::vector<string> params;
	uint8_t source = 0;
};

#endif /* CMD_CMD_H_ */

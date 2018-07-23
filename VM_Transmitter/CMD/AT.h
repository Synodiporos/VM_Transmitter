/*
 * AT.h
 *
 *  Created on: Jul 23, 2018
 *      Author: sgeorgiadis
 */

#ifndef AT_AT_H_
#define AT_AT_H_

#include <vector>
#include <string>
#include "CMD.h"
using namespace std;

#define AT_PREF AT

class AT {
public:
	static const string PREF;
	static const char DELIM;

	virtual ~AT();


	static bool parse(string input, string& command, vector<string>& params);
	static int toCMD(const string& at, CMD& cmd);


private:
	static void split(const string& s, vector<string>& v);
	static long toLong(string str);
};

#endif /* AT_AT_H_ */

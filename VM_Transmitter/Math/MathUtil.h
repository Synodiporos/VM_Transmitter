/*
 * MathUtil.h
 *
 *  Created on: Jul 2, 2018
 *      Author: sgeorgiadis
 */

#ifndef MATH_MATHUTIL_H_
#define MATH_MATHUTIL_H_

class MathUtil {
public:

	static float map(long value, float in_min,
			float in_max, long out_min, long out_max)	{
	  return (float)(value - in_min) * (out_max - out_min) /
			  (in_max - in_min) + out_min;
	}

};

#endif /* MATH_MATHUTIL_H_ */

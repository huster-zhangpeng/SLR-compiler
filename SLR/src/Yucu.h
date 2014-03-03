/*
 * Yucu.h
 *
 *  Created on: 2012-11-6
 *      Author: zp
 */

#ifndef YUCU_H_
#define YUCU_H_

#include <vector>
#include <string>
#include "Exp.h"

class Element {
public:
	Element();
	virtual ~Element();

	int getBeginAddr();
	void setBeginAddr(int beginAddr);
	int getEndAddr();
	void setEndAddr(int endAddr);
	int getLength();
	void setLength(int length);
	//int getRepresent();
	//void setRepresent(int represent);
	std::vector<Exp> & getSegment();
	std::string getResult();
	void setResult(std::string result);

private:
	int beginAddr;
	int endAddr;
	//int represent;
	int length;
	std::string result;
	std::vector<Exp> segment;
};

#endif /* YUCU_H_ */

/*
 * Exp.h
 *
 *  Created on: 2012-11-6
 *      Author: zp
 */

#ifndef EXP_H_
#define EXP_H_

#include <string>

class Exp {
public:
	Exp();
	virtual ~Exp();

	std::string getOpcode();
	std::string getArg1();
	std::string getArg2();
	std::string getResult();
	void setOpcode(std::string opcode);
	void setArg1(std::string arg1);
	void setArg2(std::string arg2);
	void setResult(std::string result);

private:
	std::string _opcode;
	std::string _arg1;
	std::string _arg2;
	std::string _result;
};

#endif /* EXP_H_ */

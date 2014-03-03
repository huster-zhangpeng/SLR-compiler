/*
 * Exp.cpp
 *
 *  Created on: 2012-11-6
 *      Author: zp
 */

#include "Exp.h"

Exp::Exp() {
	// TODO Auto-generated constructor stub
	_opcode = "";
	_arg1 = "";
	_arg2 = "";
	_result = "";
}

std::string Exp::getOpcode(){
	return _opcode;
}

void Exp::setOpcode(std::string opcode){
	_opcode = opcode;
}

std::string Exp::getArg1(){
	return _arg1;
}

void Exp::setArg1(std::string arg1){
	_arg1 = arg1;
}

std::string Exp::getArg2(){
	return _arg2;
}

void Exp::setArg2(std::string arg2){
	_arg2 = arg2;
}

std::string Exp::getResult(){
	return _result;
}

void Exp::setResult(std::string result){
	_result = result;
}

Exp::~Exp() {
	// TODO Auto-generated destructor stub
}

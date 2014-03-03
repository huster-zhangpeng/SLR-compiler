/*
 * Yucu.cpp
 *
 *  Created on: 2012-11-6
 *      Author: zp
 */

#include "Yucu.h"

Element::Element() {
	// TODO Auto-generated constructor stub
	beginAddr = 0;
	endAddr = 0;
	//represent = 0;
	length = 0;
}

int Element::getBeginAddr(){
	return beginAddr;
}

void Element::setBeginAddr(int addr){
	beginAddr = addr;
	length = endAddr - beginAddr;
}

int Element::getEndAddr(){
	return endAddr;
}

void Element::setEndAddr(int addr){
	endAddr = addr;
	length = endAddr - beginAddr;
}

int Element::getLength(){
	return length;
}

void Element::setLength(int length){
	Element::length = length;
	endAddr = beginAddr + length;
}

/*
int Element::getRepresent(){
	return represent;
}

void Element::setRepresent(int represent){
	Element::represent = represent;
}
*/

std::vector<Exp> & Element::getSegment(){
	return segment;
}

std::string Element::getResult(){
	return result;
}

void Element::setResult(std::string result){
	Element::result = result;
}

Element::~Element() {
	// TODO Auto-generated destructor stub
}


/*
 * Cisu.cpp
 *
 *  Created on: 2012-11-6
 *      Author: zp
 */

#include "Cisu.h"

Cisu::Cisu() {
	// TODO Auto-generated constructor stub
	token = "";
	syn = -1;
	line = 0;
	pos = 0;
}

int Cisu::getSyn(){
	return syn;
}

std::string Cisu::getToken(){
	return token;
}

int Cisu::getLine(){
	return line;
}

int Cisu::getPos(){
	return pos;
}

std::istream& operator>>(std::istream& in, Cisu& cisu){
	std::string text;
	int i;
	getline(in, text);
	cisu.token.clear();
	for(i = 1; text[i] != ','; i++){
		cisu.token.push_back(text[i]);
	}
	text = text.substr(i + 2, text.size() - 1);
	sscanf(text.c_str(), "%d, %d, %d", &(cisu.syn), &(cisu.line), &(cisu.pos));
	return in;
}

Cisu::~Cisu() {
	// TODO Auto-generated destructor stub
}


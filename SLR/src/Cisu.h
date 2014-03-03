/*
 * Cisu.h
 *
 *  Created on: 2012-11-6
 *      Author: zp
 */

#ifndef CISU_H_
#define CISU_H_

#include <string>
#include <iostream>

class Cisu {
public:
	Cisu();
	virtual ~Cisu();

	int getSyn();
	std::string getToken();
	int getLine();
	int getPos();
	friend std::istream& operator>>(std::istream& out, Cisu& cisu);

private:
	std::string text;
	std::string token;
	int syn;
	int line;
	int pos;
};

#endif /* CISU_H_ */

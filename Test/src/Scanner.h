/*
 * Scanner.h
 *
 *  Created on: 2012-10-21
 *      Author: zp
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include <string>
#include <map>

class Scanner {

public:
	Scanner(std::string filename);
	virtual ~Scanner();

	void analysis();

protected:
	void scan();

private:
	void init();
	void readAll();
	bool isDigit(char ch);
	bool isLetter(char ch);
	bool isBlank(char ch);

private:
	std::string _in;
	std::string _out;
	std::string _prog;
	std::string _token;
	int _syn;
	int _pos;
	int _line;
	int _cpos;
	std::map<std::string,int> _rwtab;
};

#endif /* SCANNER_H_ */

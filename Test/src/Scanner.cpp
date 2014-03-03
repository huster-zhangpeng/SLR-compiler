/*
 * Scanner.cpp
 *
 *  Created on: 2012-10-21
 *      Author: zp
 */

#include <fstream>
#include <iostream>

#include "Scanner.h"

Scanner::Scanner(std::string filename) :
		_syn(0), _pos(0), _line(1), _cpos(0) {
	// TODO Auto-generated constructor stub
	init();

	if (filename.empty()) {
		std::cout << "Please input src filename!" << std::endl;
	}
	_in = filename;
	int dotPos = filename.find('.', 0);
	_out = filename.substr(0, dotPos) + ".cisu";

	readAll();
}

void Scanner::init() {
	_rwtab["begin"] = 1;
	_rwtab["if"] = 2;
	_rwtab["then"] = 3;
	_rwtab["else"] = 4;
	_rwtab["while"] = 5;
	_rwtab["do"] = 6;
	_rwtab["end"] = 7;
}

void Scanner::readAll() {
	std::ifstream fin(_in.c_str()); //fin(_in);
	if (!fin.is_open()) {
		std::cout << "File open error!" << std::endl;
		exit(-1);
	}
	fin >> std::noskipws;

	char ch;
	do {
		fin >> ch;
		_prog += ch;
	} while (ch != '#');
	fin.close();
}

void Scanner::analysis() {
	std::ofstream fout(_out.c_str());
	if (!fout.is_open()) {
		std::cout << "File open error!" << std::endl;
		exit(-1);
	}
	do {
		scan();
		if (_syn == -1) {
			std::cout << "Error: in row " << _line << " column " << _cpos << " find invalid charcter: " << _token
					<< std::endl;
		} else {
			fout << '(' << _token << ", " << _syn << ", " << _line << ", "
					<< _cpos << ')' << std::endl;
		}
	} while (_syn != 0);
	fout.close();
}

bool Scanner::isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

bool Scanner::isLetter(char ch) {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool Scanner::isBlank(char ch) {
	return (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n');
}

Scanner::~Scanner() {
	// TODO Auto-generated destructor stub
}

void Scanner::scan() {
	_token.clear();

	char ch = _prog[_pos++];
	_cpos++;
	while (isBlank(ch)) {
		if (ch == '\n') {
			_line++;
			_cpos = 0;
		}
		ch = _prog[_pos++];
		_cpos++;
	}
	if (isLetter(ch)) {
		do {
			_token += ch;
			ch = _prog[_pos++];
			_cpos++;
		} while (isLetter(ch) || isDigit(ch));
		_pos--;
		_cpos--;
		std::map<std::string, int>::iterator it = _rwtab.find(_token);
		if (it == _rwtab.end()) {
			//not found, token is not key word
			_syn = 10;
		} else {
			_syn = it->second;
		}
	} else if (isDigit(ch)) {
		do {
			_token += ch;
			ch = _prog[_pos++];
			_cpos++;
		} while (isDigit(ch));
		_syn = 11;
		_pos--;
		_cpos--;
	} else {
		switch (ch) {
		case '<':
			_token += ch;
			ch = _prog[_pos++];
			_cpos++;
			if (ch == '>') {
				_syn = 21;
				_token += ch;
			} else if (ch == '=') {
				_syn = 22;
				_token += ch;
			} else {
				_syn = 20;
				_pos--;
				_cpos--;
			}
			break;
		case '>':
			_token += ch;
			ch = _prog[_pos++];
			_cpos++;
			if (ch == '=') {
				_syn = 24;
				_token += ch;
			} else {
				_syn = 23;
				_pos--;
				_cpos--;
			}
			break;
		case ':':
			_token += ch;
			ch = _prog[_pos++];
			_cpos++;
			if (ch == '=') {
				_syn = 18;
				_token += ch;
			} else {
				_syn = 17;
				_pos--;
				_cpos--;
			}
			break;
		case '+':
			_syn = 13;
			_token += ch;
			break;
		case '-':
			_syn = 14;
			_token += ch;
			break;
		case '*':
			_syn = 15;
			_token += ch;
			break;
		case '/':
			_syn = 16;
			_token += ch;
			break;
		case ';':
			_syn = 26;
			_token += ch;
			break;
		case '(':
			_syn = 27;
			_token += ch;
			break;
		case ')':
			_syn = 28;
			_token += ch;
			break;
		case '=':
			_syn = 25;
			_token += ch;
			break;
		case '#':
			_syn = 0;
			_token += ch;
			break;
		default:
			_syn = -1;
			_token += ch;
			break;
		}
	}
}


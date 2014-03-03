//============================================================================
// Name        : Test.cpp
// Author      : zhangpeng
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Scanner.h"

using namespace std;

int main(int argc, char** argv) {
	if(argc < 2){
		cout<<"Error:Please input src filename!"<<endl;
		return 0;
	}
	Scanner scanner(argv[1]);
	scanner.analysis();
	return 0;
}

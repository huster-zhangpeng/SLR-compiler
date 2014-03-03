//============================================================================
// Name        : SLR.cpp
// Author      : zhangpeng
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include "Cisu.h"
#include "Yucu.h"

#define MAX_STATE 100
using namespace std;

struct _cell {
	char op;
	int state;
} ACTION[MAX_STATE][MAX_STATE];
int GOTO[MAX_STATE][MAX_STATE];
int totalState, totalVT, totalVN, totalRule;
vector<string> symbol;
int itemCountOfRule[MAX_STATE];
int headOfRule[MAX_STATE];
int category[MAX_STATE];
stack<int> stateStack;
stack<Element> resultStack;
string exp;
int tempVarCount = 0;

string getTempVar() {
	string var = "";
	char buf[20];
	sprintf(buf, "temp%d", tempVarCount);
	var.append(buf);
	tempVarCount++;
	return var;
}

void printElement(Element ret){
	vector<Exp> & exps = ret.getSegment();
	cout << "Length"<< ret.getLength()<< endl;
	for (unsigned i = 0; i < exps.size(); i++) {
		cout << '(' << exps[i].getOpcode();
		cout << ',' << exps[i].getArg1();
		cout << ',' << exps[i].getArg2();
		cout << ',' << exps[i].getResult() << ')' << endl;
	}
}

void guiyue1() {
	for (int i = 0; i < 3; i++) {
		stateStack.pop();
	}
	Element begin, Z, end;
	end = resultStack.top();
	resultStack.pop();
	Z = resultStack.top();
	resultStack.pop();
	begin = resultStack.top();
	resultStack.pop();
	printElement(Z);
	resultStack.push(Z);
}

void guiyue2() {
	for (int i = 0; i < 3; i++) {
		stateStack.pop();
	}
	Element ret, Z, e2, S;
	S = resultStack.top();
	resultStack.pop();
	e2 = resultStack.top();
	resultStack.pop();
	Z = resultStack.top();
	resultStack.pop();
	vector<Exp> & Z_exps = Z.getSegment();
	vector<Exp> & S_exps = S.getSegment();
	for (unsigned i = 0; i < S_exps.size(); i++) {
		Z_exps.push_back(S_exps[i]);
	}
	Z.setResult(S.getResult());
	Z.setLength(Z.getLength() + S.getLength());
	printElement(Z);
	resultStack.push(Z);
}

void guiyue3() {
	stateStack.pop();
	return;
}

void guiyue4() {
	for (int i = 0; i < 3; i++) {
		stateStack.pop();
	}
	Element ret, id, e2, E;
	E = resultStack.top();
	resultStack.pop();
	e2 = resultStack.top();
	resultStack.pop();
	id = resultStack.top();
	resultStack.pop();
	vector<Exp> & E_exps = E.getSegment();
	Exp exp;
	exp.setOpcode(":=");
	exp.setArg1(E.getResult());
	exp.setArg2("None");
	exp.setResult(id.getResult());
	E_exps.push_back(exp);
	E.setLength(E.getLength() + 1);
	printElement(E);
	resultStack.push(E);
}

void guiyue5() {
	for (int i = 0; i < 6; i++) {
		stateStack.pop();
	}
	Element B, S1, S2;
	S2 = resultStack.top(); resultStack.pop();
	resultStack.pop();
	S1 = resultStack.top(); resultStack.pop();
	resultStack.pop();
	B = resultStack.top(); resultStack.pop();
	resultStack.pop();
	printElement(B);
	cout<<endl;
	printElement(S1);
	cout<<endl;
	printElement(S2);
	cout<<endl;
	vector<Exp> & B_exps = B.getSegment();
	vector<Exp> & S1_exps = S1.getSegment();
	vector<Exp> & S2_exps = S2.getSegment();
	string destAddr = "";
	char buf[20] = "";
	sprintf(buf, "%d", S2.getLength()+2);
	destAddr.append(buf);
	B_exps[B_exps.size()-1].setResult(destAddr);
	for(unsigned i = 0; i < S2_exps.size(); i++){
		B_exps.push_back(S2_exps[i]);
	}
	Exp exp;
	exp.setOpcode("j");
	exp.setArg1("None");
	exp.setArg2("None");
	buf[0] = '\0';
	sprintf(buf, "%d", S1.getLength()+1);
	destAddr.clear();
	destAddr.append(buf);
	exp.setResult(destAddr);
	B_exps.push_back(exp);
	for(int i = 0; i < S1.getLength(); i++){
		B_exps.push_back(S1_exps[i]);
	}
	B.setLength(B.getLength()+S1.getLength()+S2.getLength()+1);
	printElement(B);
	resultStack.push(B);
}

void guiyue6() {
	for (int i = 0; i < 4; i++) {
		stateStack.pop();
	}
	Element B, S;
	S = resultStack.top(); resultStack.pop();
	resultStack.pop();
	B = resultStack.top(); resultStack.pop();
	resultStack.pop();
	vector<Exp> & B_exps = B.getSegment();
	vector<Exp> & S_exps = S.getSegment();
	B_exps[B_exps.size()-1].setResult("2");

	Exp exp;
	exp.setOpcode("j");
	exp.setArg1("None");
	exp.setArg2("None");
	string destAddr = "";
	char buf[20] = "";
	sprintf(buf, "%d", S.getLength()+2);
	destAddr.append(buf);
	exp.setResult(destAddr);
	B_exps.push_back(exp);

	for(int i = 0; i < S.getLength(); i++){
		B_exps.push_back(S_exps[i]);
	}

	destAddr.clear();
	buf[0] = '\0';
	sprintf(buf, "%d", -B.getLength() - S.getLength() - 1);
	destAddr.append(buf);
	exp.setOpcode("j");
	exp.setResult(destAddr);
	B_exps.push_back(exp);
	B.setLength(B.getLength() + S.getLength() + 2);
	printElement(B);
	resultStack.push(B);
}

void guiyue7(){
	for (int i = 0; i < 3; i++) {
		stateStack.pop();
	}
	Element E1, op, E2;
	E2 = resultStack.top(); resultStack.pop();
	op = resultStack.top(); resultStack.pop();
	E1 = resultStack.top(); resultStack.pop();
	vector<Exp> & E1_exps = E1.getSegment();
	vector<Exp> & E2_exps = E2.getSegment();
	for(int i = 0; i < E2.getLength(); i++){
		E1_exps.push_back(E2_exps[i]);
	}
	Exp exp;
	string tempVar = getTempVar();
	exp.setOpcode(op.getResult());
	exp.setArg1(E1.getResult());
	exp.setArg2(E2.getResult());
	exp.setResult(tempVar);
	E1_exps.push_back(exp);
	E1.setLength(E1.getLength() + E2.getLength() + 1);
	E1.setResult(tempVar);
	printElement(E1);
	resultStack.push(E1);
}

void guiyue8(){
	for (int i = 0; i < 3; i++) {
		stateStack.pop();
	}
	Element E;
	resultStack.pop();
	E = resultStack.top(); resultStack.pop();
	resultStack.pop();
	printElement(E);
	resultStack.push(E);
}

void guiyue9(){
	stateStack.pop();
}

void guiyue10(){
	stateStack.pop();
}

void guiyue11(){
	for (int i = 0; i < 3; i++) {
		stateStack.pop();
	}
	Element E1, rop, E2;
	E2 = resultStack.top(); resultStack.pop();
	rop = resultStack.top(); resultStack.pop();
	E1 = resultStack.top(); resultStack.pop();
	vector<Exp> & E1_exps = E1.getSegment();
	vector<Exp> & E2_exps = E2.getSegment();
	for(int i = 0; i < E2.getLength(); i++){
		E1_exps.push_back(E2_exps[i]);
	}
	Exp exp;
	exp.setOpcode("j" + rop.getResult());
	exp.setArg1(E1.getResult());
	exp.setArg2(E2.getResult());
	exp.setResult("1");
	E1_exps.push_back(exp);
	E1.setLength(E1.getLength() + E2.getLength() + 1);
	printElement(E1);
	resultStack.push(E1);
}

typedef void (*Fun)();
Fun guiyue[11] = { guiyue1, guiyue2, guiyue3, guiyue4, guiyue5, guiyue6, guiyue7,
					guiyue8, guiyue9, guiyue10, guiyue11};

void readActionAndGotoTable(char *filename) {
	ifstream fin(filename);
	if (!fin.is_open()) {
		cout << "Can't open file:" << filename << endl;
		exit(-1);
	}

	fin >> totalRule >> totalState >> totalVT >> totalVN;
	for (int i = 0; i < totalVT + totalVN; i++) {
		string str;
		fin >> str;
		symbol.push_back(str);
	}

	int temp;
	fin >> temp;
	for (int i = 0; i < temp; i++) {
		fin >> category[i];
	}

	for (int i = 1; i <= totalRule; i++) {
		fin >> headOfRule[i];
	}

	//读取ACTION表
	for (int i = 0; i < totalState; i++) {
		for (int j = 0; j < totalVT; j++) {
			fin >> ACTION[i][j].op;
			if (ACTION[i][j].op == 'a')
				continue;
			if (ACTION[i][j].op == 'w')
				continue;
			fin >> ACTION[i][j].state;
		}
	}

	//读取GOTO表
	for (int i = 0; i < totalState; i++) {
		for (int j = 0; j < totalVN; j++) {
			fin >> GOTO[i][j];
		}
	}
	fin.close();
}

void SLR(char *src) {
	ifstream fw(src);
	if (!fw.is_open()) {
		cout << "Source file not found:" << src << endl;
		exit(-1);
	}
	//int a;
	Cisu cisu;
	fw >> cisu;
	stateStack.push(0);
	while (true) {
		int id = stateStack.top();
		int syn = category[cisu.getSyn()];
		//stateStack.pop();
		if (ACTION[id][syn].op == 's') {
			cout << "Current state:"<<id<<" Move into state:"<<ACTION[id][syn].state<<endl;
			stateStack.push(ACTION[id][syn].state);
			Element e;
			cout << cisu.getToken() << endl;
			e.setResult(cisu.getToken());
			resultStack.push(e);
			fw >> cisu;
		} else if (ACTION[id][syn].op == 'r') {
			int ruleNo = ACTION[id][syn].state;
			cout << "Current state:"<<id<<" Apply to rule " << ruleNo << " interpret:" << endl;

			Fun fooGuiyue = guiyue[ruleNo - 1];
			(*fooGuiyue)();
			int t = stateStack.top();
			stateStack.push(GOTO[t][headOfRule[ruleNo]]);
		} else if (ACTION[id][syn].op == 'a') {
			cout << "Success!" << endl;
			break;
		} else {
			cout << "Current state:"<<id<<" Current word:"<<cisu.getToken()<<endl;
			cout << "Error: in Row " << cisu.getLine() <<" column " << cisu.getPos() << " find invalid action" << endl;
			cout << "Error to stop compile"<<endl;
			exit(-1);
		}
	}
}
//#define DEBUG
int main(int argc, char** argv) {
	readActionAndGotoTable("action.txt");
#ifdef DEBUG
	SLR("test.cisu");
#else
	if (argc < 2){
		cout<<"Error:Please input word file!"<<endl;
		return 0;
	}
	SLR(argv[1]);
#endif
	string filename(argv[1]);
	int dotPos = filename.find('.', 0);
	string out = filename.substr(0, dotPos) + ".exp";
	cout<<out<<endl;
	ofstream fout(out.c_str());
	Element ret = resultStack.top();
	vector<Exp> & exps = ret.getSegment();
	for (unsigned i = 0; i < exps.size(); i++) {
		fout << i <<"\t:(" << exps[i].getOpcode();
		fout << ',' << exps[i].getArg1();
		fout << ',' << exps[i].getArg2();
		fout << ',' << exps[i].getResult() << ')' << endl;
	}

	return 0;
}

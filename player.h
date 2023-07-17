#pragma once
#include<iostream>
#include<string>
#include"bscs22101_Header.h"

using namespace std;
class player{
	string name;
	color c;
	int t=60;
public:
	player(string n, color cl);
	string getName();
	color getColor();
	int GetTime()const {
		return t;
	}
	void SetTime(int ti) {
		this->t = ti;
	}
};

 
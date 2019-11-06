#pragma once
#include <iostream>

using namespace std;
class Date
{
	int d, m, y;
public:
	Date(int d=1, int m=1, int y=1);
	Date(const Date & dat) { d = dat.d; m = dat.m; y = dat.y; }
	Date(Date && dat) = default;
	~Date() = default;
	void setD(int i) { d = i; }
	void setM(int i) { m = i; }
	void setY(int i) { y = i; }
	int getD() const { return d; }
	int getM() const { return m; }
	int getY() const { return y; }
	Date & operator= (const Date & dat);
	friend istream & operator>>(istream & is, Date & date);
	friend ostream & operator<< (ostream & os, const Date & date);
	void writeDate() const;
	friend bool earlierReleased(const Date & a, const Date & b);
};


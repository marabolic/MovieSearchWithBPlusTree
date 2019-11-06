#pragma once
#include "Date.h"
#include <iostream>

using namespace std;

Date::Date(int d, int m, int y)
{
	this->d = d;
	this->m = m;
	this->y = y;
}


Date & Date::operator=(const Date & dat)
{
	d = dat.d; m = dat.m; y = dat.y;
	return *this;
}

void Date::writeDate() const
{
	cout << y << "-" << m << "-" <<  d;
}


istream& operator>>(istream& fs, Date& date)
{
	return fs;
}

ostream & operator<<(ostream & os, const Date & date)
{
	date.writeDate();
	return os;
}



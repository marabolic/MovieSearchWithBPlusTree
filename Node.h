#pragma once
#include "Date.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
class Node
{
	string title;
	string lang;
	long long revenue;
	int runtime;
	bool valid;
public:
	Date date;
	Node() { valid = true; }
	Node(const Node & a);
	Node(Node && a) { valid = true; }
	void setT(string t) { title = t; }
	void setL(string l) { lang = l; }
	void setRe(long long r) { revenue = r; }
	void setRu(int r) { runtime = r; }
	void setValid(bool flag) { valid = flag; }
	string getT()const { return title; }
	string getL()const { return lang; }
	long long getRe()const { return revenue; }
	int getRu()const { return runtime; }
	bool getValid() const { return valid; }
	Node & operator= (const Node & a);
	//friend ostream & operator<< (ostream & os, Node & a);
};

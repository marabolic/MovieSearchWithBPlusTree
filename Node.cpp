#pragma once
#include "Node.h"

Node::Node(const Node & a) {
	title = a.title; lang = a.lang; revenue = a.revenue; 
	runtime = a.runtime; date = a.date; valid = true;
}

Node & Node::operator=(const Node & a)
{
	title = a.title; 
	lang = a.lang; 
	revenue = a.revenue;
	runtime = a.runtime; date = a.date; valid = true;
	return *this;
}

//ostream & operator<<(ostream & os, const  Node & a)
//{
//	string s;
//	return os;
//}
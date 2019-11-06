#pragma once
#pragma once
#include "Date.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool earlierReleased(const Date & a, const Date & b)
{
	if (a.y < b.y) return true;
	else {
		if (a.y == b.y) {
			if (a.m < b.m) return true;
			else {
				if (a.m == b.m) {
					if (a.d < b.d) return true;
					else return false;
				}
				else return false;
			}
		}
		else return false;
	}
}


void writeDB(Node v[]) {
	for (int i = 0; i < 5000; i++)
		cout << v[i].date << " " << v[i].getT() << " " << endl;
}

void deleteDB(Node v[]) {
	for (int i = 0; i != sizeof(v); i++) {
		v[i].setValid(false);
	}
}

void sortDB(Node v[], int n, Node &x) {

	/*for (int i = 0; i < 23 - 1; i++) {
		for (int j = i + 1; j < 23; j++)
		{
			if (earlierReleased(v[i].date, v[j].date)) {
				Node temp = v[i];
				v[i] = v[j];
				v[j] = temp;
			}

			cout << "\nbroj sort koraka\t"<< cnt;
			cnt++;
		}
	}*/
	int i = 0;
	while (i < n && earlierReleased(v[i].date, x.date))
		i++;
	for (int j = n - 1; j >= i; j--)
		v[j + 1] = v[j];
	v[i] = x;
}

void deleteMovie(Node &a) {
	a.setValid(false);
}

void readDB(ifstream & db, Node database[], int num) {
	int i = 0;
	while (!db.eof()) {
		Node n = Node();
		char c; db.get(c);
		while (c != '\n') db.get(c);
		db.get(c); string b = "";
		while (c != ',') {
			//n->lang += c;
			b += c;
			db.get(c);
		}
		n.setL(b);
		db.get(c); b = "";
		while (c != ',') {
			//n->title += c;
			b += c;
			db.get(c);
		}
		n.setT(b);
		db.get(c); int a = 0;
		while (c != '/') {
			a *= 10;
			a += c - '0';
			db.get(c);
		}
		n.date.setM(a);
		db.get(c); a = 0;
		while (c != '/') {
			a *= 10;
			a += c - '0';
			db.get(c);
		}
		n.date.setD(a);
		db.get(c); a = 0;
		while (c != ',') {
			a *= 10;
			a += c - '0';
			db.get(c);
		}
		n.date.setY(a); long long rev;
		db >> rev;
		n.setRe(rev);
		db.get(c); int run;
		db >> run;
		n.setRu(run);
		//cout << n.date << " " << n.getT() << " " << n.getValid() << endl;
		sortDB(database, i, n);
		i++;
		//sortDB(database, i);
	}
	db.close();
}



void makeDatabase() {
	ifstream db;
	db.open("mali.txt", ios::in);
	if (!db.is_open())  cout << "error opening file" << endl;
	const int n = 23;
	Node database[n];
	readDB(db, database, n);
	writeDB(database);
	cout << '\n' << '\n';


}




#include "BPlusTree.h"
#include "Database.h"

Node * first(Node database[], int max, int key);
const int m = 5000;
Node database[m];
int main() {
	ifstream db;
	db.open("movies.txt", ios::in);
	if (!db.is_open())  cout << "error opening file" << endl;
	
	int order;
	cout << "unesi red stabla: ";
	cin >> order;
	
	readDB(db, database, m);
	//writeDB(database);
	cout << '\n' << '\n';
	BPlusTree bp = BPlusTree();
	bp.root = nullptr;
	int k;
	for (int i = 0; i < m; i++)
	{
		k = database[i].date.getY();
		k *= 100;
		k += database[i].date.getM();
		bp.root = bp.addNode(database, order-1, k, bp.getRoot());
		//cout << "\n\numece se:" << k << "\n";
		//bp.levelOrder(bp.root);
	}
	int key;
	/*cout << "unesi kljuc ";*/
	/*cin >> key;
	bp.root = bp.addNode(database, order - 1, key, bp.getRoot());*/
	bp.levelOrder(bp.root);
	cout << endl;
	cout << endl;
	int del;
	cout << "\nunesi kljuc ";
	cin >> del;
	bp.deleteNode(bp.root, order - 1, database, del);
	bp.levelOrder(bp.root);
	cout << "\nunesi kljuc ";
	cin >> del;
	bp.deleteNode(bp.root, order - 1, database, del);
	bp.levelOrder(bp.root);
	//bp.countYear(bp.root, bp.root, order - 1, 2012, database);
	//bp.interval(bp.root, bp.root, order - 1, 2008, 2012, database);

	system("PAUSE");
}
#pragma once
#include "BPlusTree.h"
#include <queue>


BPlusTree::BPlusTree(NodeB *root)
{
	root = new NodeB();
	root->leaf = true;
	root->m = 0;
	for (int i = 0; i < root->m; i++)
	{
		root->key[i] = 0;
	}
	for (int i = 0; i < root->m; i++)
	{
		root->ptr[i] = nullptr;
	}

}

Node * first(Node database[], int max, int key) {
	int i = 0;
	Node *ptr = nullptr;
	while (true) {
		int k = database[i].date.getY();
		k *= 100;
		k += database[i].date.getM();
		if (i == max) break;
		if (key == k && database[i].getValid()) {
			ptr = &database[i];
			break;
		}
		else i++;
	}
	//ptr->date.writeDate();
	return ptr;
}

BPlusTree::NodeB * BPlusTree::search(NodeB * temp, NodeB *&myKey, int max, int k) {
	while (temp != nullptr && !temp->leaf) {
		int i = 0;
		while (i < temp->capacity && temp->key[i] <= k) {
			if (temp->key[i] != k) {
				i++;
			}
			else {
				if (!temp->leaf) {
					myKey = temp;
					break;
					/*temp = static_cast<NodeB*>(temp->ptr[i]);
					i = 0;*/
				}
				else {
					//cout << temp->key[i];
					return temp;   
				}
			}
		}
		temp = static_cast<NodeB*>(temp->ptr[i]);
	}
	if (temp != nullptr) {
		if (temp->capacity < max) {
			return temp;
		}
	}
	return temp;
}

BPlusTree::NodeB * BPlusTree::searchYear(NodeB * temp, NodeB *myKey, int max, int year) {
	while (temp != nullptr && !temp->leaf) {
		int i = 0;
		while (i < temp->capacity && temp->key[i] / 100 <= year) {
			if (temp->key[i]/100 != year) {
				i++;
			}
			else {
				if (!temp->leaf) {
					myKey = temp;
					temp = static_cast<NodeB*>(temp->ptr[i]);
					i = 0;
				}
				else {
					//cout << temp->key[i];
					return temp;
				}
			}
		}
		temp = static_cast<NodeB*>(temp->ptr[i]);
	}
	if (temp != nullptr) {
		if (temp->capacity < max) {
			return temp;
		}
	}
	return temp;
}

void BPlusTree::countYear(NodeB * root, NodeB *mykey, int max, int year, Node database[]) {
	NodeB *temp = searchYear(root, mykey, max, year);
	int i = 0;
	while (i < temp->capacity && temp->key[i] /100 < year) {
		i++;
	}
	int cnt = 0;
	Node *first = static_cast<Node*>(temp->ptr[i]);
	while (first != nullptr && first->date.getY() == year && first->getValid() == true) { 
		cout << first->getT() << endl;
		first++; cnt++;
	}
	cout << "broj filmova u godini: " << cnt << endl;

}

void BPlusTree::interval(NodeB * root, NodeB *mykey, int max, int start, int stop, Node database[]) {
	NodeB *temp = searchYear(root, mykey, max, start);
	int i = 0;
	while (i < temp->capacity && temp->key[i] / 100 < start) {
		i++;
	}
	Node *first = static_cast<Node*>(temp->ptr[i]);
	while (first != nullptr && first->date.getY() >= start && first->date.getY() <= stop && first->getValid() == true) {
		cout << first->getT() << endl;
		first++; 
	}
}

BPlusTree::NodeB * BPlusTree::addNode(Node database[], int max, int k, NodeB *root) {
	NodeB *myKey = nullptr;
	NodeB * temp = root;
	temp = search(root, myKey, max, k);
	int i = 0;
	if (temp != nullptr) {
		while (i < temp->capacity && temp->key[i] < k) {
			i++;
		}
		
		if (temp->key[i] == k) {
			return root;
			//cout << "Neuspesno umetanje: kljuc postoji\n";
		}

		for (int j = max - 1; j >= i; j--)
		{
			temp->key[j + 1] = temp->key[j];
			temp->ptr[j + 2] = temp->ptr[j+1];
		}
		temp->key[i] = k;
		temp->capacity++;
		
		//cout << "dodati kljuc" << temp->key[i];
		void * data = static_cast<Node*>(first(database, 23, k));
		temp->ptr[i] = data;									//ovo mozda 
		if (temp->key[max] != 0) {
			//split lista
			NodeB * newNode = new NodeB();

			
			for (int i = 0; i <= max - 1 - max / 2; i++)
			{
				newNode->key[i] = temp->key[max / 2 + 1 + i];  //kopiranje kljuceva
				newNode->ptr[i] = temp->ptr[max / 2 + 1+i];  //kopiranje pointera
				temp->key[max / 2 + 1 + i] = 0;
				temp->ptr[max / 2 +1+ i] = nullptr;
				newNode->capacity++;
				temp->capacity--;
			}
			newNode->ptr[max] = temp->ptr[max];
			temp->ptr[max] = newNode;
			NodeB * par = temp->parent;
			newNode->parent = par;
			newNode->ptr[i] = data;
			if (par == nullptr) {				
				par = new NodeB();
				par->leaf = false;
				root = par;
			}
			newNode->parent = par;
			temp->parent = par;

			//parent split

			while (par->key[max - 1] != 0) {
				int iParent = 0;
				while (iParent < max && par->key[iParent] < k) {
					iParent++;
				}
				for (int jParent = max - 1; jParent >= i; jParent--)
				{
					par->key[jParent + 1] = par->key[jParent];
					par->ptr[jParent + 1] = par->ptr[jParent];
				}
				par->key[iParent] = temp->key[max / 2];
				par->capacity++;
				temp = par;//mozda
				if (par->key[max] != 0) {
					NodeB * newParent = new NodeB();
					newParent->leaf = false;
					int i = 0;
					for (i = 0; i <= max - 1 - max / 2; i++)
					{
						newParent->key[i] = par->key[max / 2 + 1 + i];		 //kopiranje kljuceva
						newParent->ptr[i] = par->ptr[max / 2 + 1 + i];		 //kopiranje pointera
						par->key[max / 2 + 1 + i] = 0;
						par->ptr[max / 2 + 1 + i] = nullptr;
						newParent->capacity++;
						par->capacity--;
					}
					par->key[max / 2 + 1 + i] = 0;
					par->ptr[max / 2 + 1 + i] = nullptr;
					par->capacity--;
					k = par->key[max / 2];
					newParent->ptr[i] = newNode; 
					newNode->parent = newParent;
					for (int i = 0; i < newParent->capacity; i++)
					{
						static_cast<NodeB*>(newParent->ptr[i])->parent = newParent;
					}
					newNode = newParent;
					NodeB * parN = temp->parent;
					newNode->parent = parN;
					if (temp->parent == nullptr) {		//temp->parent				
						parN = new NodeB();
						parN->leaf = false;
						temp->parent = parN;
						newNode->parent = parN;
						root = parN;
						parN->ptr[0] = par;				//par
						parN->ptr[1] = newParent;			//newPar
					}
					par = parN;
					//newNode->parent = par;
				}
			}

			if (par->key[max - 1] == 0) {
				int iParent = 0;
				while (iParent < par->capacity && par->key[iParent] < k) {
					iParent++;
				}
				//if (par->capacity != 0) {
					for (int jParent = max - 1; jParent >= iParent; jParent--)
					{
						par->key[jParent + 1] = par->key[jParent];
						par->ptr[jParent + 2] = par->ptr[jParent + 1];

					}
				//}
				par->key[iParent] = temp->key[max / 2];
				par->capacity++;
				par->ptr[iParent] = temp;
				par->ptr[iParent+1] = newNode;
			}
		}
		else {
		if (temp->key[temp->capacity] == k) {
			int i = 0;
			while (i < myKey->capacity && myKey->key[i] < k) {
				i++;
			}
			myKey->key[i] = k;
		}
}
	}
	else {
		temp = new NodeB();
		temp->key[i] = k;
		temp->capacity++;
		void * data = first(database, max, k);
		temp->ptr[i] = data;
		/*cout << "dodati kljuc\t" << temp->key[i] << '\n';
		cout << "dodati ptr\t" << temp->ptr[i] << "\n\n";*/
		root = temp;
	}
	return root;
}

void BPlusTree::levelOrder(NodeB * root) const
{
	NodeB* temp = root;
	queue<NodeB*> Q;
	Q.push(root);
	Q.push(nullptr);
	while (Q.size() > 1) {
		temp = Q.front();
		Q.pop();
		if (temp == nullptr) {
			Q.push(nullptr);
			cout << endl;
			//cout << "inf\n";
		}
		else {
			for (int i = 0; i < temp->capacity; i++)
			{
				cout << temp->key[i] << " ";
			}
			cout << "   "; 
			if (!temp->leaf) {
				NodeB* x = temp;
				for (int i = 0; i <= temp->capacity; i++)
				{
					Q.push(static_cast<NodeB*>(x->ptr[i]));
				}
			}
		}
	}
}


void BPlusTree::deleteMergeNodes(NodeB * temp, NodeB * myKey, int max, int key)
{
	//[move]
	int i = 0;
	while (i < temp->capacity && temp->key[i] < key) {
		i++;
	}
	Node *n = static_cast<Node*>(temp->ptr[i]);
	//deleteMovie(*n);
	for (int j = i; j < temp->capacity; j++)
	{
		temp->key[j] = temp->key[j + 1];
		temp->ptr[j] = temp->ptr[j + 1];
	}
	temp->capacity--;
	//[move]

	//[parent, sibling]
	int j = 0;
	while (j < temp->parent->capacity &&  temp->parent->key[j] < key) {
		j++;
	}


	NodeB *sibling = static_cast<NodeB*>(temp->parent->ptr[j + 1]);
	//[parent, sibling]

	//fali brisanje ovde 
	if (sibling != nullptr ) {
		for (int k = temp->capacity, l = 0; k < max && l < sibling->capacity; l++, k++)
		{
			temp->key[k] = sibling->key[l];
			temp->ptr[k] = sibling->ptr[l];
			temp->capacity++;
		}
		temp->ptr[temp->capacity - 1] = sibling->ptr[sibling->capacity - 1];
		sibling->capacity = 0;
		temp->parent->capacity--;
	}

	NodeB *mark = temp->parent;
	//mark->capacity = 0;


	while (mark != nullptr) {

		//[parent, sibling]
		int j = 0;
		while (j < mark->parent->capacity &&  mark->parent->key[j] < key) {
			j++;
		}
		NodeB *sibling = static_cast<NodeB*>(mark->parent->ptr[j + 1]);
		//[parent, sibling]

		if (sibling->capacity - 1 >= (max / 2)) {
			deleteWithBorrowInter(mark, myKey, max, mark->key[i]); //nem blage sta sam ovde uradila
			break;
		}
		else {
			if (temp->parent == root && root->capacity == 1) {
				deleteRootSpec(temp, max);
				break;
			}
			else {
				if (mark->parent->capacity >= (max / 2)-1) {
					mark->key[i] = mark->parent->key[j]; //brise se ne prepisuje se sad
					mark->capacity++;

					for (int j = i + 1; j < mark->parent->capacity; j++)
					{
						mark->parent->key[j] = mark->parent->key[j + 1];
						mark->parent->ptr[j + 1] = mark->parent->ptr[j + 2];
					}
					mark->parent->capacity--;
					for (int k = mark->capacity, l = 0; k < max && l <= sibling->capacity; l++, k++)
					{
						mark->key[k] = sibling->key[l];
						mark->ptr[k] = sibling->ptr[l];
						mark->capacity++;
						static_cast<NodeB*>(mark->ptr[k])->parent = mark;
					}
					mark->ptr[mark->capacity] = sibling->ptr[sibling->capacity];
					sibling->capacity = 0;
					//sibling->parent->ptr[j + 1] = nullptr;
					//sibling->parent = nullptr;
					break;
				}
				else {
					temp = mark;
					mark = mark->parent;
				}
			}
		}
	}
}

void BPlusTree::deleteWithoutBorrowLeaf(NodeB * temp, NodeB * myKey, int key)
{
	//[move]
	int i = 0;
	while (i < temp->capacity && temp->key[i] < key) {
		i++;
	}
	Node *n = static_cast<Node*>(temp->ptr[i]);
	//deleteMovie(*n);
	for (int j = i; j < temp->capacity; j++)
	{
		temp->key[j] = temp->key[j + 1];
		temp->ptr[j] = temp->ptr[j + 1];
	}
	temp->capacity--;
	//[move]

	int j = 0;
	if (myKey != nullptr) {
		while (j < myKey->capacity && myKey->key[j] < key) {
			j++;
		}
		myKey->key[j] = temp->key[temp->capacity-1];
	}
}

void BPlusTree::deleteWithBorrowLeaf(NodeB * temp, NodeB * myKey, int max, int key)
{
	//[move]
	int i = 0;
	while (i < temp->capacity && temp->key[i] < key) {
		i++;
	}
	Node *n = static_cast<Node*>(temp->ptr[i]);
	//deleteMovie(*n);
	for (int j = i; j < temp->capacity; j++)
	{
		temp->key[j] = temp->key[j + 1];
		temp->ptr[j + 1] = temp->ptr[j + 2];
	}
	//[move]

	//[parent, sibling]
	int j = 0;
	while (j < temp->parent->capacity &&  temp->parent->key[j] < key) {
		j++;
	}
	NodeB *sibling = static_cast<NodeB*>(temp->parent->ptr[j + 1]);
	//[parent, sibling]

	
	temp->parent->key[j] = sibling->key[0];
	if(i==0) temp->key[i+1] = temp->parent->key[j];
	else temp->key[i] = temp->parent->key[j];
	for (int j = i; j < sibling->capacity; j++)
	{
		sibling->key[j - 1] = sibling->key[j];
		sibling->ptr[j] = sibling->ptr[j + 1];
	}
	sibling->capacity--;
}

void BPlusTree::deleteWithBorrowInter(NodeB * temp, NodeB * myKey, int max, int key)
{
	//[move]
	int i = 0;
	while (i < temp->capacity && temp->key[i] < key) {
		i++;
	}
	Node *n = static_cast<Node*>(temp->ptr[i]);
	//deleteMovie(*n);
	for (int j = i; j < temp->capacity; j++)
	{
		temp->key[j] = temp->key[j + 1];
		temp->ptr[j + 1] = temp->ptr[j + 2];
	}
	//[move]

	//[parent, sibling]
	int j = 0;
	while (j < temp->parent->capacity &&  temp->parent->key[j] < key) {
		j++;
	}
	NodeB *sibling = static_cast<NodeB*>(temp->parent->ptr[j + 1]);
	//[parent, sibling]

	temp->parent->key[j] = sibling->key[0];
	temp->key[i] = temp->parent->key[j];
	for (int j = i-1; j < sibling->capacity; j++)
	{
		sibling->key[j - 1] = sibling->key[j];
		sibling->ptr[j] = sibling->ptr[j + 1];
	}
	sibling->capacity--;
}

void BPlusTree::deleteRootSpec(NodeB* temp, int max)
{
	root = static_cast<NodeB*>(root->ptr[0]);
	root->parent = nullptr;
	for (int k = root->capacity, l = 0; k < max && l <= temp->capacity; l++, k++)
	{
		root->key[k] = temp->key[l];
		root->ptr[k] = temp->ptr[l];
		root->capacity++;
		static_cast<NodeB*>(temp->ptr[k])->parent = temp;
	}
	root->ptr[root->capacity] = temp->ptr[temp->capacity];
	temp->capacity = 0;
}


void BPlusTree::deleteNode(NodeB * root, int max, Node database[], int key)
{
	BPlusTree::NodeB * myKey = nullptr;
	BPlusTree::NodeB * del = search(getRoot(), myKey, max, key);
	//deleteWithBorrowLeaf(del, myKey, max, key);

	int j = 0;
	while (j < del->parent->capacity &&  del->parent->key[j] < key) {
		j++;
	}
	
	NodeB *sibling = static_cast<NodeB*>(del->parent->ptr[j + 1]);

	if (del->capacity - 1 > max / 2 ) {
		deleteWithoutBorrowLeaf(del, myKey, key);
	}
	else {
		if (sibling != nullptr && sibling->capacity - 1> max / 2) {
			deleteWithBorrowLeaf(del, myKey, max, key);
		}
		else {
				deleteMergeNodes(del, myKey, max, key);
		}
	}
}




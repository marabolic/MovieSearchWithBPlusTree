#pragma once
#include "Node.h"

class BPlusTree
{

	struct NodeB {
		int key[10];
		void *ptr[11];
		NodeB * parent;
		int capacity = 0;
		int m;
		bool leaf;
		NodeB(){
			for (int i = 0; i < 10; i++)
			{ key[i] = 0; }
			for (int i = 0; i < 10; i++)
			{ ptr[i] = nullptr; }
			parent = nullptr;
		}
		NodeB(const NodeB & a) {
			for (int i = 0; i < 10; i++)
			{
				key[i] = a.key[i];
			}
			for (int i = 0; i < 10; i++)
			{
				ptr[i] = a.ptr[i];
			}
			parent = a.parent; 
		}
	};
	

public:
	NodeB *root;
	BPlusTree(NodeB *root = nullptr);
	~BPlusTree() = default;
	void setRoot(NodeB * r) { root = r; }
	NodeB * getRoot() { return root; }
	//void split(NodeB * node);
	void countYear(NodeB * root, NodeB* mykey, int max, int k, Node database[]);
	NodeB * search(NodeB *root, NodeB *&myKey, int max, int key);
	NodeB * searchYear(NodeB * temp, NodeB *myKey, int max, int year);
	void interval(NodeB * root, NodeB *mykey, int max, int start, int stop, Node database[]);
	NodeB * addNode(Node database[], int max, int k,NodeB *root= nullptr);
	void levelOrder(NodeB * root) const;
	void deleteWithoutBorrowLeaf(NodeB * temp, NodeB * myKey, int key);
	void deleteWithBorrowLeaf(NodeB * temp, NodeB * myKey,int max, int key);
	void deleteWithBorrowInter(NodeB * temp, NodeB * myKey, int max, int key);
	void deleteRootSpec(NodeB * temp, int max);
	void deleteMergeNodes(NodeB * temp, NodeB * myKey, int max, int key);
	void deleteNode(NodeB * root, int max, Node database[], int key);

};


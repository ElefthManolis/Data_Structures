#pragma once
#include <fstream>
#include <string>

struct Node
{
	Node() = delete;
	Node(int v, Node* l, Node* r);
	int value;
	Node* leftChild = nullptr;
	Node* rightChild = nullptr;
	int height();
};

class AVLTree
{
public:
	AVLTree();
	bool Build(std::string filename);
	void Insert(int number);
	bool Delete(int number);
	bool Search(int number) const;
	int GetSize() const;
	int GetMin() const;

private:
	Node* Insert(Node* n, int value);
	Node* Delete(Node* n, int value, bool& found);
	Node* BalanceNode(Node* n);
	Node* RightRotation(Node* n);
	Node* LeftRotation(Node* n);
	Node* MinNode(Node* n) const;
	int nodeBalanceFactor(Node* n);

private:
	Node* root;
	int elements;
};
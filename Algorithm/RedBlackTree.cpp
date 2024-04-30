#include "RedBlackTree.h"
#include <iostream>
#include <windows.h>
using namespace std;

enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

void SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<SHORT>(color));
}

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

RedBlackTree::RedBlackTree()
{
	_nil = new NodeTree();
	_root = _nil;
}

RedBlackTree::~RedBlackTree()
{
	Release(_root);
	if (_nil)
		delete _nil;
}

void RedBlackTree::Release(NodeTree* root)
{
	if (root == _nil)
	{
		return;
	}

	Release(root->left);
	Release(root->right);
	delete root;
}

void RedBlackTree::Print(NodeTree* nodeTree, int x, int y)
{
	if (nodeTree == _nil)
		return;

	SetCursorPosition(x, y);

	if (nodeTree->color == Color::Black)
		SetCursorColor(ConsoleColor::BLUE);
	else
		SetCursorColor(ConsoleColor::RED);

	cout << nodeTree->key;
	Print(nodeTree->left, x - (5 / (y + 1)), y + 1);
	Print(nodeTree->right, x + (5 / (y + 1)), y + 1);

	SetCursorColor(ConsoleColor::WHITE);
}

NodeTree* RedBlackTree::Search(NodeTree* nodeTree, int key)
{
	if (!nodeTree) return _nil;

	while (nodeTree)
	{
		if (key == nodeTree->key)
			return nodeTree;
		else if (key < nodeTree->key) {
			nodeTree = nodeTree->left;
		}
		else
			nodeTree = nodeTree->right;
	}

	return _nil;
}

NodeTree* RedBlackTree::Min(NodeTree* nodeTree)
{
	if (nodeTree == _nil) return _nil;

	while (nodeTree->left != _nil)
		nodeTree = nodeTree->left;

	return nodeTree;
}

NodeTree* RedBlackTree::Max(NodeTree* nodeTree)
{
	if (nodeTree == _nil) return _nil;

	while (nodeTree->right != _nil)
		nodeTree = nodeTree->right;

	return nodeTree;
}

NodeTree* RedBlackTree::Next(NodeTree* nodeTree)
{
	if (nodeTree == _nil) return _nil;

	if (nodeTree->right)
	{
		nodeTree = nodeTree->right;
		while (nodeTree->left != _nil)
			nodeTree = nodeTree->left;
	}
	else
	{
		while (nodeTree == nodeTree->parent->right)
			nodeTree = nodeTree->parent;

		nodeTree = nodeTree->parent;
	}

	return nodeTree;
}

void RedBlackTree::Insert(int key)
{
	NodeTree* newNode = new NodeTree();
	newNode->key = key;

	NodeTree* temp = _root;
	NodeTree* parent = _nil;

	while (temp != _nil)
	{
		parent = temp;
		if (key < temp->key)
			temp = temp->left;
		else
			temp = temp->right;
	}

	newNode->parent = parent;

	if (parent == _nil)
		_root = newNode;
	else if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;

	newNode->left = _nil;
	newNode->right = _nil;
}

void RedBlackTree::InsertFixup(NodeTree* nodeTree)
{
}

void RedBlackTree::Delete(int key)
{
	NodeTree* node = Search(_root, key);
	Delete(node);
}

void RedBlackTree::Delete(NodeTree* nodeTree)
{
	if (nodeTree == _nil) return;

	if (nodeTree->left == _nil)
		Replace(nodeTree, nodeTree->right);
	else if (nodeTree->right == _nil)
		Replace(nodeTree, nodeTree->left);
	else
	{
		NodeTree* next = Next(nodeTree);
		nodeTree->key = next->key;
		Delete(next);
	}
}

void RedBlackTree::Replace(NodeTree* u, NodeTree* v)
{
	NodeTree* parent = u->parent;

	if (parent == _nil) {
		_root = v;
	}
	else if (parent->left == u)
	{
		parent->left = v;
	}
	else
	{
		parent->right = v;
	}

	if (v)
		v->parent = parent;

	delete u;
}

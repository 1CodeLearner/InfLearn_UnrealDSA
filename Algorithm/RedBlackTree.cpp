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
	Delete(_root);
}

void RedBlackTree::Delete(NodeTree* nodeTree)
{
	if (nodeTree == _nil)
		return;
	Delete(nodeTree->left);
	Delete(nodeTree->right);
	delete nodeTree;
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
	return nullptr;
}

NodeTree* RedBlackTree::Min(NodeTree* nodeTree)
{
	return nullptr;
}

NodeTree* RedBlackTree::Max(NodeTree* nodeTree)
{
	return nullptr;
}

NodeTree* RedBlackTree::Next(NodeTree* nodeTree)
{
	return nullptr;
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

	if(parent == _nil)
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
}

//void RedBlackTree::Delete(NodeTree* nodeTree)
//{
//}

void RedBlackTree::Replace(NodeTree* u, NodeTree* v)
{
}

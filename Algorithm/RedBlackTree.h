#pragma once


enum class Color
{
	Red = 0,
	Black = 1,
};

struct NodeTree
{	
	NodeTree* parent = nullptr;
	NodeTree* left = nullptr;
	NodeTree* right = nullptr;
	int key = {};
	Color color = Color::Black;
};


class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

private:
	void Delete(NodeTree* NodeTree);
public:

	void	Print() { Print(_root, 10, 0); }
	void	Print(NodeTree* nodeTree, int x, int y);

	NodeTree* Search(NodeTree* NodeTree, int key);

	NodeTree* Min(NodeTree* nodeTree);
	NodeTree* Max(NodeTree* nodeTree);
	NodeTree* Next(NodeTree* nodeTree);

	void	Insert(int key);
	void	InsertFixup(NodeTree* nodeTree);

	void	Delete(int key);
	//void	Delete(NodeTree* nodeTree);
	void	Replace(NodeTree* u, NodeTree* v);

private:
	NodeTree* _root = nullptr;
	NodeTree* _nil = nullptr;
};


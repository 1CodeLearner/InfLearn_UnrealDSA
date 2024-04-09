#pragma once
#include <string>
#include <vector>
#include <memory>
namespace Tree
{
	using namespace std;

	struct Node
	{
		Node() = default;
		Node(const string& name)
			: name(name)
		{}
		string name;

		vector<shared_ptr<Node>> children;
	};

	shared_ptr<Node> CreateTree()
	{
		shared_ptr<Node> root = make_shared<Node>("R1 개발실");
		{
			shared_ptr<Node> node = make_shared<Node>("디자인팀");
			root->children.push_back(node);
			{
				shared_ptr<Node> leaf = make_shared<Node>("전투");
				node->children.push_back(leaf);
				//{
				//	shared_ptr<Node> subleaf = make_shared<Node>("케릭터");
				//	shared_ptr<Node> subleaf1 = make_shared<Node>("모브");
				//	shared_ptr<Node> subleaf2 = make_shared<Node>("보스");
				//	leaf->children.push_back(subleaf);
				//	leaf->children.push_back(subleaf1);
				//	leaf->children.push_back(subleaf2);
				//}
			}
			{
				shared_ptr<Node> leaf = make_shared<Node>("경제");
				node->children.push_back(leaf);
			}
			{
				shared_ptr<Node> leaf = make_shared<Node>("스토리");
				node->children.push_back(leaf);
			}
		}
		{
			shared_ptr<Node> node = make_shared<Node>("프로그래밍팀");
			root->children.push_back(node);
			{
				shared_ptr<Node> leaf = make_shared<Node>("서버");
				node->children.push_back(leaf);
			}
			{
				shared_ptr<Node> leaf = make_shared<Node>("클라");
				node->children.push_back(leaf);
			}
			{
				shared_ptr<Node> leaf = make_shared<Node>("엔진");
				node->children.push_back(leaf);
			}
		}
		{
			shared_ptr<Node> node = make_shared<Node>("아트팀");
			root->children.push_back(node);
			{
				shared_ptr<Node> leaf = make_shared<Node>("배경");
				node->children.push_back(leaf);
			}
			{
				shared_ptr<Node> leaf = make_shared<Node>("캐릭터");
				node->children.push_back(leaf);
			}
		}

		return root;
	}

	void PrintTree(shared_ptr<Node> root, int depth)
	{
		for (int i = 0; i < depth; ++i) {
			cout << "-";
		}

		cout << root->name << endl;

		for (auto child : root->children) {
			PrintTree(child, depth + 1);
		}
	}

	//finding number of nodes
	int FindHeight(shared_ptr<Node> root)
	{
		int height = 1;

		for (shared_ptr<Node>& child : root->children)
			height = max(height, FindHeight(child) + 1);

		return height;
	}

	//finding number of edges
	int FindHeightAlt(shared_ptr<Node> root)
	{
		if (root->children.empty()) return 0;

		int total = INT32_MIN;
		for (auto& child : root->children) {
			total = max(total, FindHeightAlt(child));
		}
		return total + 1;
	}
}
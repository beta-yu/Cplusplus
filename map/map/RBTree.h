#pragma once

enum Color{ RED, BLACK };
template<class K, class V>
struct RBTreeNode
{
	RBTreeNode* _parent;
	RBTreeNode* _left;
	RBTreeNode* _right;
	Color _col;
	pair<K, V> _kv;

	RBTreeNode(const pair<K, V>& kv)
		:_parent(nullptr)
		, _left(nullptr)
		, _right(nullptr)
		, _col(RED)
		, _kv(kv)
	{}
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(nullptr)
	{}

	pair<Node*, bool> Insert(const pair<K, V>& kv)
	{
		Node* newNode = new Node(kv);
		if (_root == nullptr)
		{
			_root = newNode;
			_root->_col = BLACK;
			return make_pair(_root, true);
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur != nullptr)
		{
			if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return make_pair(cur, false);
			}
		}
		cur = newNode;
		if (parent->_kv.first > cur->_kv.first)
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;
		//调整
		//parent->_col == RED, 不满足连续两个结点不能都为红色
		while (parent != nullptr && parent->_col == RED)
		{
			//parent = cur->_parent;
			Node* grandfather = parent->_parent;
			Node* uncle = nullptr;
			if (parent == grandfather->_left)
			{
				uncle = grandfather->_right;
				//uncle存在且为红色
				if (uncle != nullptr && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent; //继续向上
				}
				else //uncle不存在或存在为黑色
				{
					if (cur == parent->_right) //先旋转回cur == parent->_left的情况
					{
						RotateL(parent);
						swap(cur, parent); 
						//旋转导致cur和parent位置交换，应该交换回来，否则会导致下面着色错误
					}
					//处理cur == parent->_left的情况
					RotateR(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;
					//旋转结束后，grandfather已经是parent的右孩子
					//此时parent是该子树的根，旋转结束后，子树各路径中黑色节点的数量没有改变，
					//且子树根结点parent为黑色，无论子树上层是什么颜色结点都不必再向上调整
					break;
				}
			}
			else //parent == grandfather->_right
			{
				uncle = grandfather->_left;
				if (uncle != nullptr && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(cur, parent);
					}
					RotateL(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;
					break;
				}
			}
		}
		_root->_col = BLACK; //调整可能导致根结点变为红色
		return make_pair(newNode, true);
	}

	void InOrder()
	{
		_InOrder(_root);
	}

private:
	void RotateR(Node* root)
	{
		Node* subL = root->_left;
		Node* subLR = subL->_right;
		Node* ppNode = root->_parent;
		root->_left = subLR;
		if (subLR != nullptr) //subLR可能为nullptr
			subLR->_parent = root;
		subL->_right = root;
		root->_parent = subL;
		subL->_parent = ppNode;
		if (ppNode != nullptr)
		{ //root可能为ppNode的左节点，也可能为右节点
			if (ppNode->_left == root)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
		}
		else
		{
			_root = subL; //ppNode == nullptr,则subL为新的根结点
		}
	}

	void RotateL(Node* root)
	{
		Node* subR = root->_right;
		Node* subRL = subR->_left;
		Node* ppNode = root->_parent;
		root->_right = subRL;
		if (subRL != nullptr)
			subRL->_parent = root;
		subR->_left = root;
		root->_parent = subR;
		subR->_parent = ppNode;
		if (ppNode != nullptr)
		{
			if (ppNode->_left == root)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;
		}
		else
		{
			_root = subR;
		}
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}

private:
	Node* _root;
};

void Test()
{
	RBTree<int, int> t;
	//int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	//int arr[] = { 1, 2, 1, 2, 3, 4, 3, 4, 5, 6, 5, 6, 7 };
	for (auto it : arr)
	{
		pair<RBTreeNode<int, int>*, bool> result = t.Insert(make_pair(it, 1));
		if (result.second == false)
			++(((result.first)->_kv).second);
	}

	t.InOrder();
}
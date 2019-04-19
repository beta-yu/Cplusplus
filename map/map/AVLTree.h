#pragma once

using namespace std;
template <class K, class V>
struct TreeNode
{
	TreeNode* _left;
	TreeNode* _right;
	TreeNode* _parent;
	pair<K, V> _kv;
	int _bf; //balance factor

	TreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _bf(0)
	{}
};

template <class K, class V>
class AVLTree
{
	typedef TreeNode<K, V> Node;
	typedef pair<K, V> Pair;
public:
	AVLTree()
		:_root(nullptr)
	{}

	Node* Find(const K& key)
	{
		if (_root == nullptr)
			return nullptr;
		Node* cur = _root;
		while (cur != nullptr)
		{
			if (cur->_kv.first > key)
				cur = cur->_left;
			else if (cur->_kv.first < key)
				cur = cur->_right;
			else
				return cur;
		}
	}

	pair<Node*, bool> Insert(const Pair& kv)
	{
		Node* newNode = new Node(kv);
		if (_root == nullptr)
		{
			_root = newNode;
			return make_pair(_root, true);
		}
		Node* prev = nullptr;
		Node* cur = _root;
		while (cur != nullptr)
		{
			if (cur->_kv.first > kv.first)
			{
				prev = cur;
				cur = cur->_left;
			}
			else if (cur->_kv.first < kv.first)
			{
				prev = cur;
				cur = cur->_right;
			}
			else
				return make_pair(cur, false);
		}
		cur = newNode;
		if (prev->_kv.first > kv.first)
			prev->_left = cur;
		else
			prev->_right = cur;
		cur->_parent = prev;

		//更新节点平衡因子
		cur->_bf = 0;
		Node* parent = cur->_parent;
		while (parent != nullptr)
		{
			if (cur == parent->_left)
				(parent->_bf)--;
			else if (cur == parent->_right)
				(parent->_bf)++;
			if (abs(parent->_bf) == 1)
			{
				// 1/-1，因此该节点原bf == 0，以该节点为根的子树的高度变了(+1),
				// 对上层节点有影响，需要继续向上更新平衡因子
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 0) 
				// 该节点原来平衡因子为1/-1，插入节点，只是把原本最底层的叶子节点补齐,
				// 以该节点为根结点的子树的高度并没有改变，对上层节点没有影响
				break;
			else //bf == 2/-2，不再平衡，需要对以parent为根的树进行旋转
			{
				if (parent->_bf == -2)
				{
					if (parent->_left->_bf == -1)
					{
						//向右单旋
						RotateR(parent);
					}
					else
					{
						Node* subL = parent->_left;
						Node* subLR = subL->_right;
						int bf = subLR->_bf;
						//先把以parent->_left为根节点的树向左单旋；
						RotateL(parent->_left);
						//再把以parent为根节点的树向右单旋（左右双旋）
						RotateR(parent);
						if (bf == 1)
						{
							subL->_bf = -1;
							parent->_bf = 0;
						}
						else if (bf == -1)
						{
							subL->_bf = 0;
							parent->_bf = 1;
						}
					}
				}
				else
				{
					if (parent->_right->_bf == 1)
					{
						//左单旋
						RotateL(parent);
					}
					else
					{
						Node* subR = parent->_right;
						Node* subRL = subR->_left;
						int bf = subRL->_bf;
						//先把以parent->_right为根节点的树向右单旋；
						RotateR(parent->_right);
						//再把以parent为根节点的树向左单旋（右左双旋）
						RotateL(parent);
						//双旋转平衡因子修正
						if (bf == 1)
						//与新增节点处于subRL的左还是右有关
						//parent和subR分别占有了subRL的左和右
						{
							parent->_bf = -1;
							subR->_bf = 0;
						}
						else if (bf == -1)
						{
							subR->_bf = 1;
							parent->_bf = 0;
						}
					}
				}
				break; //在旋转时已更新平衡因子,旋转结束后，
					   //parent->_bf == 0, 以parent为根结点的子树已经平衡
			}
		}
		return make_pair(newNode, true);
	}

	void InOrder()
	{
		_InOrder(_root);
	}

	bool IsBalance()
	{
		return _IsBalance(_root);
	}

private:
	void Destory(Node*& root)
	{
		delete root;
		root = nullptr;
	}

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
		//更新相关节点的平衡因子(看起来像是这样，好像没错，其实有问题的)，
		//在双旋中不能直接赋值0，具体情况在双旋中处理
		subL->_bf = root->_bf = 0;
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

		root->_bf = subR->_bf = 0;
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		//cout << "isbalance: " << _IsBalance(root) << " bf: " << root->_bf << endl;

		_InOrder(root->_right);
	}

	int Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
			return true;

		int diff = Height(root->_right) - Height(root->_left);
		if (diff != root->_bf) //实际的平衡因子和旋转时调整的平衡因子不相等，说明调整方法有问题
			return false;

		return abs(diff) <= 1
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);
	}

private:
	Node* _root;
};

void Test()
{
	AVLTree<int, int> t;
	//int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	int arr[] = { 1, 2, 1, 2, 3, 4, 3, 4, 5, 6, 5, 6, 7 };
	for (auto it : arr)
	{
		pair<TreeNode<int, int>*, bool> result = t.Insert(make_pair(it, 1));
		if (result.second == false)
			++(((result.first)->_kv).second);
	}

	t.InOrder();
	//cout << t.IsBalance() << endl;
}
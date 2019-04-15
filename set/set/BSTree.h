#pragma once

template <class K>
struct TreeNode
{
	TreeNode* _left;
	TreeNode* _right;
	K _key;

	TreeNode(const K& key)
		:_left(nullptr)
		, _right(nullptr)
		, _key(key)
	{}
}; //typedef模板非法？

template<class K>
class BSTree  //binary search tree
{
public:
	BSTree()
		:_root(nullptr)
	{}

	~BSTree()
	{
		__Destory(_root);
	}

	BSTree(const BSTree& tree)
	{
		_root = copy(_root, tree._root);
	}

	BSTree<K> operator=(const BSTree& tree)
	{
		if (_root == tree._root)
			return *this;
		__Destory(_root);
		_root = copy(_root, tree._root);
		return *this;
	}

	bool Insert(const K& val)
	{
		if (_root == nullptr)
		{
			_root = new TreeNode<K>(val);
		}
		else
		{
			TreeNode<K>* parent = nullptr;
			TreeNode<K>* cur = _root;
			while (cur != nullptr)
			{
				if (cur->_key > val) //小于当前节点值，去它的左
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < val)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false; //key唯一，相等，插入失败
				}
			}
			cur = new TreeNode<K>(val);
			//判断cur应该是parent的左还是右
			if (parent->_key > val)
			{
				parent->_left = cur;
			}
			else
			{
				parent->_right = cur;
			}
		}
		return true;
	}

	TreeNode<K>* Find(const K& val)
	{
		TreeNode<K>* cur = _root;
		while (cur != nullptr)
		{
			if (cur->_key > val)
			{
				cur = cur->_left;
			}
			else if (cur->_key < val)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}

	bool Erase(const K& val)
	{
		//1.被删除节点无孩子，直接删，parent = nullptr;（可在2中同时处理）
		//2.被删除节点有一个孩子节点，判断当前节点是parent的right/left，
		//  连接parent与当前节点的子节点，删除当前节点
		//3.被删除节点的left/right都不为空，
		//  在左子树中找最大值结点或在右子树中找最小值节点,与当前节点进行值交换，删除交换后的节点
		if (_root == nullptr)
			return false;
		TreeNode<K>* parent = nullptr;
		TreeNode<K>* cur = _root;
		while (cur != nullptr)
		{
			if (cur->_key == val)
			{
				break;
			}
			else if (cur->_key > val)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				parent = cur;
				cur = cur->_right;
			}
		}
		if (cur == nullptr)
			return false;
		//1.2.
		if (cur->_left == nullptr) //左右都为空也在这处理
		{
			if (cur == _root) //当前删除节点为根结点，根节点下移
				_root = cur->_right;
			else //cur == _root时，parent == nullptr
			{
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else
					parent->_right = cur->_right;
			}
			Destory(cur);
		}
		else if (cur->_right == nullptr)
		{
			if (cur == _root)
				_root = cur->_left;
			else
			{
				if (parent->_left == cur)
					parent->_left = cur->_left;
				else
					parent->_right = cur->_left;
			}
			Destory(cur);
		}
		//3.
		else
		{
			//在左树中找最大值节点
			TreeNode<K>* curNode = cur->_left;
			TreeNode<K>* parentNode = cur; //关键
			while (true)
			{
				if (curNode->_right != nullptr)
				{
					parentNode = curNode;
					curNode = curNode->_right;
				}
				else
					break;
			}
			swap(cur->_key, curNode->_key);
			//curNode的右节点一定为空，判断左是否为空，若不为空，连接起来
			if (curNode->_left == nullptr)
			{
				//仍需判断curNode与parentNode的关系，
				//curNode不一定是parentNode的右节点
				//（例如：当cur的左子树只有一个节点，
				//那么左子树中最大节点(curNode)就是cur->_left）
				if (parentNode->_left == curNode)
					parentNode->_left = nullptr;
				else
					parentNode->_right = nullptr;
				Destory(curNode);
			}
			else
			{
				if (parentNode->_left == curNode)
					parentNode->_left = curNode->_left;
				else
					parentNode->_right = curNode->_left;
				Destory(curNode);
			}
		}
		return true;
	}


	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

private:
	void _Inorder(TreeNode<K>* _root)
	{
		if (_root == nullptr)
			return;
		_Inorder(_root->_left);
		cout << _root->_key << " ";
		_Inorder(_root->_right);
	}

	void Destory(TreeNode<K>*& ptr)
	{
		if (ptr != nullptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}

	void __Destory(TreeNode<K>*& ptr)
	{
		if (ptr == nullptr)
			return;
		__Destory(ptr->_left);
		__Destory(ptr->_right);
		Destory(ptr);
	}

	TreeNode<K>* copy(TreeNode<K>* root1, TreeNode<K>* root2)
	{
		if (root2 == nullptr)
			return nullptr;
		root1 = new TreeNode<K>(root2->_key);
		root1->_left = copy(root1->_left, root2->_left);
		root1->_right = copy(root1->_right, root2->_right);
		return root1;
	}

private:
	TreeNode<K>* _root;
};

void Test()
{
	BSTree<int> s;
	//s.Insert(2);
	//s.Insert(2);
	//s.Insert(1);
	//s.Insert(5);
	//s.Insert(4);
	//s.Insert(3);
	//s.Insert(4);
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	for (auto it : arr)
	{
		s.Insert(it);
	}
	s.Inorder();

	BSTree<int> copy(s);
	copy.Inorder();

	for (auto it : arr)
	{
		s.Erase(it);
		s.Inorder();
	}

	s = copy;
	s.Inorder();
}
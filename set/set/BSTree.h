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



	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}
private:
	TreeNode<K>* _root;

	void _Inorder(TreeNode<K>* _root)
	{
		if (_root == nullptr)
			return;
		_Inorder(_root->_left);
		cout << _root->_key << " ";
		_Inorder(_root->_right);
	}
};

void Test()
{
	BSTree<int> s;
	s.Insert(2);
	s.Insert(2);
	s.Insert(1);
	s.Insert(5);
	s.Insert(4);
	s.Insert(3);
	s.Insert(4);
	s.Inorder();
}
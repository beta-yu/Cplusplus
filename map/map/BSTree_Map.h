#pragma once
using namespace std;
template <class K, class V>
struct TreeNode
{
	TreeNode* _left;
	TreeNode* _right;
	pair<K, V> _kv;

	TreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _kv(kv)
	{}
}; 

template<class K, class V>
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

	BSTree<K, V> operator=(const BSTree& tree)
	{
		if (_root == tree._root)
			return *this;
		__Destory(_root);
		_root = copy(_root, tree._root);
		return *this;
	}

	pair<TreeNode<K, V>*, bool> Insert(const pair<K, V>& kv)
	{
		TreeNode<K, V>* result;
		if (_root == nullptr)
		{
			_root = new TreeNode<K, V>(kv);
			result = _root;
		}
		else
		{
			TreeNode<K, V>* parent = nullptr;
			TreeNode<K, V>* cur = _root;
			while (cur != nullptr)
			{
				if (cur->_kv.first > kv.first) //小于当前节点值，去它的左
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
					return make_pair(cur, false); //key唯一，相等，插入失败
				}
			}
			cur = new TreeNode<K, V>(kv);
			//判断cur应该是parent的左还是右
			if (parent->_kv.first > kv.first)
			{
				parent->_left = cur;
			}
			else
			{
				parent->_right = cur;
			}
			result = cur;
		}
		return make_pair(result, true);
	}

	TreeNode<K, V>* Find(const K& val)
	{
		TreeNode<K, V>* cur = _root;
		while (cur != nullptr)
		{
			if (cur->_kv.first > val)
			{
				cur = cur->_left;
			}
			else if (cur->_kv.first < val)
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

	//bool Erase(const K& val)
	//{
	//	//1.被删除节点无孩子，直接删，parent = nullptr;（可在2中同时处理）
	//	//2.被删除节点有一个孩子节点，判断当前节点是parent的right/left，
	//	//  连接parent与当前节点的子节点，删除当前节点
	//	//3.被删除节点的left/right都不为空，
	//	//  在左子树中找最大值结点或在右子树中找最小值节点,与当前节点进行值交换，删除交换后的节点
	//	if (_root == nullptr)
	//		return false;
	//	TreeNode<K, V>* parent = nullptr;
	//	TreeNode<K, V>* cur = _root;
	//	while (cur != nullptr)
	//	{
	//		if (cur->_key == val)
	//		{
	//			break;
	//		}
	//		else if (cur->_key > val)
	//		{
	//			parent = cur;
	//			cur = cur->_left;
	//		}
	//		else
	//		{
	//			parent = cur;
	//			cur = cur->_right;
	//		}
	//	}
	//	if (cur == nullptr)
	//		return false;
	//	//1.2.
	//	if (cur->_left == nullptr) //左右都为空也在这处理
	//	{
	//		if (cur == _root) //当前删除节点为根结点，根节点下移
	//			_root = cur->_right;
	//		else //cur == _root时，parent == nullptr
	//		{
	//			if (parent->_left == cur)
	//				parent->_left = cur->_right;
	//			else
	//				parent->_right = cur->_right;
	//		}
	//		Destory(cur);
	//	}
	//	else if (cur->_right == nullptr)
	//	{
	//		if (cur == _root)
	//			_root = cur->_left;
	//		else
	//		{
	//			if (parent->_left == cur)
	//				parent->_left = cur->_left;
	//			else
	//				parent->_right = cur->_left;
	//		}
	//		Destory(cur);
	//	}
	//	//3.
	//	else
	//	{
	//		//在左树中找最大值节点
	//		TreeNode<K, V>* curNode = cur->_left;
	//		TreeNode<K, V>* parentNode = cur; //关键
	//		while (true)
	//		{
	//			if (curNode->_right != nullptr)
	//			{
	//				parentNode = curNode;
	//				curNode = curNode->_right;
	//			}
	//			else
	//				break;
	//		}
	//		swap(cur->_key, curNode->_key);
	//		//curNode的右节点一定为空，判断左是否为空，若不为空，连接起来
	//		if (curNode->_left == nullptr)
	//		{
	//			//仍需判断curNode与parentNode的关系，
	//			//curNode不一定是parentNode的右节点
	//			//（例如：当cur的左子树只有一个节点，
	//			//那么左子树中最大节点(curNode)就是cur->_left）
	//			if (parentNode->_left == curNode)
	//				parentNode->_left = nullptr;
	//			else
	//				parentNode->_right = nullptr;
	//			Destory(curNode);
	//		}
	//		else
	//		{
	//			if (parentNode->_left == curNode)
	//				parentNode->_left = curNode->_left;
	//			else
	//				parentNode->_right = curNode->_left;
	//			Destory(curNode);
	//		}
	//	}
	//	return true;
	//}


	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

private:
	void _Inorder(TreeNode<K, V>* _root)
	{
		if (_root == nullptr)
			return;
		_Inorder(_root->_left);
		cout << _root->_kv.first << ":" << _root->_kv.second << " ";
		_Inorder(_root->_right);
	}

	void Destory(TreeNode<K, V>*& ptr)
	{
		if (ptr != nullptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}

	void __Destory(TreeNode<K, V>*& ptr)
	{
		if (ptr == nullptr)
			return;
		__Destory(ptr->_left);
		__Destory(ptr->_right);
		Destory(ptr);
	}

	TreeNode<K, V>* copy(TreeNode<K, V>* root1, TreeNode<K, V>* root2)
	{
		if (root2 == nullptr)
			return nullptr;
		root1 = new TreeNode<K, V>(root2->_kv);
		root1->_left = copy(root1->_left, root2->_left);
		root1->_right = copy(root1->_right, root2->_right);
		return root1;
	}

private:
	TreeNode<K, V>* _root;
};

void Test()
{
	BSTree<int, int> s;
	//s.Insert(2);
	//s.Insert(2);
	//s.Insert(1);
	//s.Insert(5);
	//s.Insert(4);
	//s.Insert(3);
	//s.Insert(4);
	//int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	int arr[] = { 1, 2, 1, 2, 3, 4, 3, 4, 5, 6, 5, 6, 7 };
	for (auto it : arr)
	{
		pair<TreeNode<int, int>*, bool> result;
		result = s.Insert(make_pair(it, int()));
		(((result.first)->_kv).second)++; //value表示key出现的次数
	}
	s.Inorder();




	//BSTree<int, int> copy(s);
	//copy.Inorder();

	////for (auto it : arr)
	////{
	////	s.Erase(it);
	////	s.Inorder();
	////}

	//s = copy;
	//s.Inorder();
}
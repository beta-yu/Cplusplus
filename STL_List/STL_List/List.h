#ifndef _List_H_
#define _List_H_

namespace qy
{
	template<class T>
	struct ListNode
	{
		T _val;
		ListNode<T>* _next;
		ListNode<T>* _prev;

		ListNode(T val = T())
			:_val(val)
			, _next(nullptr)
			, _prev(nullptr)
		{}

	};
	/*
		list不能像vector一样以普通指针作为迭代器，因为其节点不连续存储
		利用模板传参区别const和非const迭代器
	*/
	template<class T, class Ref, class Ptr>
	struct ListIterator
	{
		typedef ListNode<T> Node;
		typedef ListIterator<T, Ref, Ptr> Self; /*Ref和Ptr是否为const区别迭代器类型*/
		Node* _node; //迭代器内指向链表节点的指针
		ListIterator()
			:_node(nullptr)
		{}

		ListIterator(Node* node)
			:_node(node)
		{}
		//copy()
		ListIterator(const Self& it)
			:_node(it._node)
		{}

		//const迭代器只可读不可修改
		Ref operator*()
		{
			return _node->_val;
		}
		
		/*
			当链表中节点的值为自定义类型时，例如Date对象
			"迭代器->"可以取到对象的地址，对该 "地址->"可取的对象的数据成员（_year/_month/_day）
			此处存在两个"->",编译器优化只需写一个
			const迭代器只可读不可修改
		*/
		Ptr operator->()
		{
			return &(_node->_val);
		}

		Self operator++()
		{
			_node = _node->_next;
			return *this;
		}
		
		Self operator++(int)
		{
			Self temp(*this);
			_node = _node->_next;
			return temp;
		}

		Self operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		Self operator--(int)
		{
			Self temp(*this);
			_node = _node->_prev;
			return temp;
		}

		bool operator==(const Self& self) const
		{
			return _node == self._node;
		}

		bool operator!=(const Self& self) const
		{
			return _node != self._node;
		}
	};

	template<class T>
	class List  //带头双向循环链表
	{
		typedef ListNode<T> Node;
		typedef ListIterator<T, T&, T*> iterator;
		typedef ListIterator<T, const T&, const T*> const_iterator;

	public:
		List()
			:_head(new Node)
		{
			_head->_next = _head;
			_head->_prev = _head;
		}

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		const_iterator cbegin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator cend() const
		{
			return const_iterator(_head);
		}

		void PushBack(const T& val)
		{
			Insert(end(), val);
		}

		void PushFront(const T& val)
		{
			Insert(begin(), val);
		}

		void PopBack()
		{
			Erase(--end());
		}

		void PopFront()
		{
			Erase(begin());
		}

		iterator Insert(iterator pos, const T& val)
		{
			Node* newnode = new Node(val);
			Node* pCur = pos._node;
			Node* pPrev = pCur->_prev;
			pPrev->_next = newnode;
			newnode->_prev = pPrev;
			newnode->_next = pCur;
			pCur->_prev = newnode;
			return pos;
		}

		/*
			Erase会导致指向被删除元素的那个迭代器失效
			在这里返回指向被删除元素后一个元素的迭代器
		*/
		iterator Erase(iterator pos)
		{
			//不能删头节点
			assert(pos != end());
			Node* pCur = pos._node;
			Node* pPrev = pCur->_prev;
			Node* pNext = pCur->_next;
			pPrev->_next = pNext;
			pNext->_prev = pPrev;
			delete pCur;
			return iterator(pNext);
		}

		
	private:
		Node* _head;
	};

	void TestList()
	{
		List<int> l;
		l.PushBack(1);
		l.PushBack(2);
		l.PushBack(3);
		l.PushBack(4);
		auto it = l.begin();
		while (it != l.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;

		l.PopBack();
		l.PopFront();
		for (auto it : l)
		{
			cout << it << " ";
		}
		cout << endl;
		l.PushFront(1);
		l.PushBack(4);
		for (auto it : l)
		{
			cout << it << " ";
		}
		cout << endl;
	}
}


#endif //_List_H_
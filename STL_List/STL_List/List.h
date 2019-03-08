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
		list������vectorһ������ָͨ����Ϊ����������Ϊ��ڵ㲻�����洢
		����ģ�崫������const�ͷ�const������
	*/
	template<class T, class Ref, class Ptr>
	struct ListIterator
	{
		typedef ListNode<T> Node;
		typedef ListIterator<T, Ref, Ptr> Self; /*Ref��Ptr�Ƿ�Ϊconst�������������*/
		Node* _node; //��������ָ������ڵ��ָ��
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

		//const������ֻ�ɶ������޸�
		Ref operator*()
		{
			return _node->_val;
		}
		
		/*
			�������нڵ��ֵΪ�Զ�������ʱ������Date����
			"������->"����ȡ������ĵ�ַ���Ը� "��ַ->"��ȡ�Ķ�������ݳ�Ա��_year/_month/_day��
			�˴���������"->",�������Ż�ֻ��дһ��
			const������ֻ�ɶ������޸�
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
	class List  //��ͷ˫��ѭ������
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
			Erase�ᵼ��ָ��ɾ��Ԫ�ص��Ǹ�������ʧЧ
			�����ﷵ��ָ��ɾ��Ԫ�غ�һ��Ԫ�صĵ�����
		*/
		iterator Erase(iterator pos)
		{
			//����ɾͷ�ڵ�
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
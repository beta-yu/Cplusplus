#pragma once

template<class T>
struct HashNode
{
	T _val;
	HashNode *_next;

	HashNode(const T& val)
		:_val(val)
		, _next(nullptr)
	{}
};

template<class K, class T, class KeyOfValue>
class HashTable;

template<class K, class T, class KeyOfValue>
class HashTableIterator
{
public:
	typedef HashNode<T> Node;
	typedef HashTableIterator Self;
	HashTableIterator(Node* node, HashTable<K, T, KeyOfValue>* ht)
		:_node(node)
		, _ht(ht)
	{}

	Self& operator++()
	{
		if (_node->_next)
			_node = _node->_next;
		else
		{
			KeyOfValue kov;
			size_t htsize = _ht->_table.size();
			size_t index = kov(_node->_val) % htsize; //计算当前节点所在链在哈希表中的节点索引
			++index; //当前链访问完
			for (; index < htsize; ++index)
			{
				if (_ht->_table[index] != nullptr)
				{
					_node = _ht->_table[index];
					break;
				}
			}
			if (index == htsize) //访问完毕
				_node = nullptr;
		}	
		return *this;
	}

	//不支持operator--(),因为存在单链表

	bool operator!=(const Self& it)
	{
		return _node != it._node;
	}

	bool operator==(const Self& it)
	{
		return !(*this != it);
	}

	T& operator*()
	{
		return _node->_val;
	}

	T* operator->()
	{
		return &(operator*());
	}

private:
	Node* _node;
	HashTable<K, T, KeyOfValue>* _ht;
};

template<class K, class T, class KeyOfValue>
class HashTable
{
	template<class K, class T, class KeyOfValue>
	friend class HashTableIterator;
public:
	typedef HashNode<T> Node;
	typedef HashTableIterator<K, T, KeyOfValue> Iterator;
private:
	std::vector<Node*> _table;
	size_t _size;

	void CheckCapacity()
	{
		//负载因子为1时增容
		if (_size >= _table.size())
		{
			KeyOfValue kov;
			size_t newsize = (_table.size() == 0 ? 10 : _table.size() * 2);
			//对于新的size，需要重新分配各节点所在的位置
			std::vector<Node*> newtable;
			newtable.resize(newsize);
			for (const auto& it : _table)
			{
				Node* cur = it;
				while (cur)
				{
					Node* next = cur->_next;
					size_t index = kov(cur->_val) % newsize;
					cur->_next = newtable[index];
					newtable[index] = cur; //将_table下的节点挂到newtable上
					cur = next;
				}
			}
			swap(_table, newtable);
		}
	}

public:
	HashTable()
		:_size(0)
	{}

	std::pair<Iterator, bool> Insert(const T& t)
	{
		CheckCapacity();
		KeyOfValue kov;
		size_t index = kov(t) % _table.size();
		Node* cur = _table[index];
		while (cur)
		{
			if (kov(cur->_val) == kov(t))
				return make_pair(Iterator(cur, this), false);
			cur = cur->_next;
		}
		//头插
		Node* newnode = new Node(t);
		newnode->_next = _table[index];
		_table[index] = newnode;
		++_size;
		return make_pair(Iterator(newnode, this), true);
	}

	bool Erase(const K& key);
	bool Find(const K& key)
	{
		KeyOfValue kov;
		size_t index = 0;
		for (; index < _table.size(); ++index)
		{
			if (_table[index] != nullptr)
			{
				Node* cur = _table[index];
				while (cur)
				{
					if (kov(cur->_val) == key)
						return true;
					cur = cur->_next;
				}
			}
		}
		return false;
	}

	Iterator begin()
	{
		size_t index = 0;
		for (; index < _table.size(); ++index)
		{
			if (_table[index])
			{
				return Iterator(_table[index], this);
			}
		}
		return Iterator(nullptr, this);
	}

	Iterator end()
	{
		return Iterator(nullptr, this);
	}
};
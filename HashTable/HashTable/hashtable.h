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

template<class T, class KeyOfValue>
class HashTableIterator
{
public:
	typedef HashNode<T> Node;
	typedef HashTableIterator Self;
	HashTableIterator(Node* node, const std::vector<Node*>& v)
		:_node(node)
		, _v(v)
	{}

	Self& operator++()
	{
		if (_node->_next)
			_node = _node->_next;
		else
		{
			KeyOfValue kov;
			size_t index = kov(_node->_val) % _v.size();
			++index;
			for (; index < _v.size(); ++index)
			{
				if (_v[index] != nullptr)
				{
					_node = _v[index];
				}
			}
			if (index == _v.size())
				_node = nullptr;
		}
		
		return *this;
	}

	bool operator!=(const Self& it)
	{
		return _node != it._node;
	}

	T& operator*()
	{
		return _node->_val;
	}

	

private:
	Node* _node;
	const std::vector<Node*>& _v;
};

template<class K, class T, class KeyOfValue>
class HashTable
{
public:
	typedef HashNode<T> Node;
	typedef HashTableIterator<T, KeyOfValue> iterator;

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

	std::pair<Node*, bool> Insert(const T& t)
	{
		CheckCapacity();
		KeyOfValue kov;
		size_t index = kov(t) % _table.size();
		Node* cur = _table[index];
		while (cur)
		{
			if (kov(cur->_val) == kov(t))
				return make_pair(cur, false);
			cur = cur->_next;
		}
		//头插
		Node* newnode = new Node(t);
		newnode->_next = _table[index];
		_table[index] = newnode;
		++_size;
		return make_pair(newnode, true);
	}

	bool Erase(const K& key);
	bool Find(const K& key);

	iterator& begin()
	{
		size_t index = 0;
		for (; index < _table.size(); ++index)
		{
			if (_table[index])
			{
				return iterator(_table[index], _table);
			}
		}
		return iterator(nullptr, _table);
	}

	iterator& end()
	{
		return iterator(nullptr, _table);
	}
};
#ifndef __PRIORITY_QUEUE_
#define __PRIORITY_QUEUE_

template<class T, class Container = vector<T>, class Compare = less<T>>
class PriorityQueue
{
public:
	PriorityQueue()
	{}

	template<class Iterator>
	PriorityQueue(Iterator first, Iterator last)
		:_con(first, last)
	{
		MakeHeap();
	}

	/*less 默认大根堆*/
	void AdjustUp(size_t pos)
	{
		size_t child = pos;
		size_t parent = (child - 1) / 2;
		while (child > 0)
		{
			Compare com;
			if (com(_con[parent], _con[child]))
			{
				swap(_con[child], _con[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	void AdjustDown(size_t pos)
	{
		size_t parent = pos;
		size_t child = 2 * parent + 1;
		while (child < _con.size())
		{
			Compare com;
			if (child + 1 < _con.size() && com(_con[child], _con[child + 1]))
			{
				swap(_con[child + 1], _con[child]);
			}
			if (com(_con[parent], _con[child]))
			{
				swap(_con[child], _con[parent]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

	/*
		建堆
	*/
	void MakeHeap()
	{
		size_t parent = (_con.size() - 2) / 2;
		while (true)
		{
			AdjustDown(parent);
			if (parent == 0) return;
			--parent;
		}
	}

	void Push(const T& value)
	{
		_con.push_back(value);
		AdjustUp(_con.size() - 1);
	}

	void Pop()
	{
		swap(_con[0], _con[_con.size() - 1]);
		_con.pop_back();
		AdjustDown(0);
	}

	const T& Top() const
	{
		return _con[0];
	}

	size_t Size() const
	{
		return _con.size();
	}

	size_t Empty() const
	{
		return _con.empty();
	}
private:
	Container _con;
};


#endif //__PRIORITY_QUEUE_
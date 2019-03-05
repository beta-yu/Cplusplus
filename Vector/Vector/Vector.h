#ifndef VECTOR_H
#define VECTOR_H

namespace qy
{
	template<class T>
	class Vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		Vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorge(nullptr)
		{}

		/*copy()*/
		Vector(const Vector<T>& v)
			:_start(new T[v.Capacity()])
			, _finish(_start+v.Size())
			, _endofstorge(_start + v.Capacity())
		{
			/*不能用memcpy，因为memcpy会对vector中的自定义类型元素进行浅拷贝*/
			for (size_t i = 0; i < v.Size(); ++i)
			{
				_start[i] = v._start[i];
			}
		}

		/*赋值*/
		Vector<T>& operator=(Vector<T> v)
		{
			Swap(v);
			return *this;
		}

		void Swap(Vector<T>& v)
		{
			swap(_start, v._start);
			swap(_finish, v._finish);
			swap(_endofstorge, v._endofstorge);
		}

		~Vector()
		{
			if (_start != nullptr)
			{
				delete[] _start;
				_start = nullptr;
			}
			_finish = nullptr;
			_endofstorge = nullptr;
		}

		size_t Size() const
		{
			return (_finish - _start);
		}

		size_t Capacity() const
		{
			return (_endofstorge - _start);
		}

		void Reverse(size_t n)
		{
			if (n > Capacity())
			{
				size_t size = Size();
				iterator newstart = new T[n];
				for (size_t i = 0; i < size; ++i)
				{
					newstart[i] = _start[i];
				}
				delete[] _start;
				_start = newstart;
				_finish = _start + size;
				_endofstorge = _start + n;
			}
		}

		void ReSize(size_t n, const T& value = T())
		{
			if (n > Capacity())
			{
				Reverse(n);
			}
			while (_finish != _start + n)
			{
				*_finish = value;
				++_finish;
			}
		}

		iterator begin() const
		{
			return _start;
		}

		iterator end() const
		{
			return _finish;
		}

		const_iterator cbegin() const
		{
			return _start;
		}

		const_iterator cend() const
		{
			return _finish;
		}

		void PushBack(const T& value)
		{
			insert(_finish, value);
		}

		void PopBack()
		{
			erase(_finish - 1);
		}

		
		iterator insert(iterator pos, const T& value)
		{
			assert(pos >= _start && pos <= _finish);
			if (_finish == _endofstorge)
			{
				size_t posindex = pos - _start;/*避免因扩容导致的迭代器失效*/
				size_t newcapacity = _start == nullptr ? 2 : Capacity() * 2;
				Reverse(newcapacity);
				pos = _start + posindex;
			}
			iterator next = _finish;
			while (next != pos)
			{
				*next = *(next - 1);
				--next;
			}
			*pos = value;
			++_finish;
			return pos;
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start && pos < _finish);
			iterator pCur = pos;
			while (pCur + 1 != _finish)
			{
				*pCur = *(pCur + 1);
				++pCur;
			}
			--_finish;
			return pos;
		}

		void PrintVector()
		{
			for (auto it : *this)
			{
				cout << it << " ";
			}
			cout << endl;
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorge;
	};


	
	void TestVector()
	{
		//Vector<int> v1;
		//v1.PushBack(1);
		//v1.PushBack(2);
		///*v1.PushBack(3);
		//v1.PushBack(4);
		//v1.PushBack(5);*/
		//v1.PrintVector();
		///*Vector<int> v2 = v1;
		//PrintVector(v2);*/
		//cout << v1.Capacity() << endl;
		//printf("%p	%p\n", v1.begin(), v1.end());
		//v1.PushBack(3);
		//printf("%p	%p\n", v1.begin(), v1.end());

		//cout << v1.Capacity() << endl;
		//v1.PrintVector();
		Vector<std::string> v2;
		v2.PushBack("aaa");
		v2.PushBack("bbb");
		v2.PushBack("cccd");
		v2.PopBack();
		v2.PrintVector();


	}
}



#endif //VECTOR_H
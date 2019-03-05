#include <iostream>
#include <vector>
using namespace std;

void print(const vector<int>& v)
{
	for (auto it : v)
	{
		cout << it << " ";
	}
	cout << endl;
}

void vector_test()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);

	vector<int>::iterator pos = find(v1.begin(), v1.end(), 3);
	pos = v1.insert(pos, 4);
	print(v1);
	cout << *pos << endl;
}

void vector_test1()
{
	int a[] = { 1, 2, 3, 4 };
	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));

	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			it = v.erase(it);  //删除后it会指向下一个位置
		}
		else
		{
			++it;
		}
	}
	print(v);
}

int main()
{
	//vector_test();
	vector_test1();
	return 0;
}
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
#include "Goods.h"
#include "priority_queue.h"

int main()
{
	/*PriorityQueue<int> pq;
	pq.Push(1);
	pq.Push(4);
	pq.Push(3);
	pq.Push(5);
	pq.Push(2);*/
	//int arr[] = { 2, 1, 6, 4, 7 };
	////greater
	//PriorityQueue<int, vector<int>, greater<int>> ipq(&arr[0], &arr[5]);

	PriorityQueue<Goods, vector<Goods>, GoodsPriceLess> Goodspq;
	Goodspq.Push(Goods(1, 2, 3, 4));
	Goodspq.Push(Goods(4, 3, 2, 1));


	while (!Goodspq.Empty())
	{
		cout << Goodspq.Top() << " ";
		Goodspq.Pop();
	}
	cout << endl;
	return 0;
}

#if 0
#include <iostream>
#include <memory>
#include <list>
#include <algorithm>

using namespace std;

struct Foo
{
	Foo(int number)
		: number(number)
	{ cout << "ctor(" << number << ")"<< endl; }
	~Foo()
	{ cout << "dtor(" << number << ")"<< endl; }

	int number;
};

void main()
{
	list<shared_ptr<Foo>> originallist;;
	list<weak_ptr<Foo>> list;

	//원본이 존재하지 않는 weak_ptr은 dangle이므로 원본을 유지하는 리스트를 작성.
	for (int i = 0; i < 10; i++)
		originallist.push_back( make_shared<Foo>(i) );

	for (auto& itr : originallist)
		list.push_back( itr );

	weak_ptr<Foo> temp;
	const int someIndex = 6;

	for (auto itr : list)
	{
		//이 루프 내에서만 shaerd_ptr로 사용.
		//방어적 코딩을 할 때는 lock의 결과가 nullptr이 아닌 것을 확인한 후에 사용해야 안전하다.
		auto item (itr.lock());
		cout << item->number << endl;

		if (item->number == someIndex)
			temp = itr;
	}

	//weak_ptr은 operator== 을 구현하지 않는다. 따라서 find를 사용할 수 없음
	//find가 필요할 경우 find_if와 shared_ptr을 비교하는 lambda를 사용해야 한다.
	//D라면 lambda에서도 타입 추론이 되니까 auto 넣으면 끝인데
	//C++은 lambda안에서는 auto 사용 불가능이라 유감.
	auto selector = [&temp](weak_ptr<Foo> item){ return item.lock() == temp.lock();};

	auto itr (std::find_if(list.begin(), list.end(), selector));

	auto foundItem (itr->lock());

	cout << "found item : " << foundItem->number << endl;

	auto t =  (((unsigned long)(1)<<31) | ((unsigned long)(0x876)<<16) | ((unsigned long)(0))) ;
}

#endif
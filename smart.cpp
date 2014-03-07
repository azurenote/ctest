
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

	//������ �������� �ʴ� weak_ptr�� dangle�̹Ƿ� ������ �����ϴ� ����Ʈ�� �ۼ�.
	for (int i = 0; i < 10; i++)
		originallist.push_back( make_shared<Foo>(i) );

	for (auto& itr : originallist)
		list.push_back( itr );

	weak_ptr<Foo> temp;
	const int someIndex = 6;

	for (auto itr : list)
	{
		//�� ���� �������� shaerd_ptr�� ���.
		//����� �ڵ��� �� ���� lock�� ����� nullptr�� �ƴ� ���� Ȯ���� �Ŀ� ����ؾ� �����ϴ�.
		auto item (itr.lock());
		cout << item->number << endl;

		if (item->number == someIndex)
			temp = itr;
	}

	//weak_ptr�� operator== �� �������� �ʴ´�. ���� find�� ����� �� ����
	//find�� �ʿ��� ��� find_if�� shared_ptr�� ���ϴ� lambda�� ����ؾ� �Ѵ�.
	//D��� lambda������ Ÿ�� �߷��� �Ǵϱ� auto ������ ���ε�
	//C++�� lambda�ȿ����� auto ��� �Ұ����̶� ����.
	auto selector = [&temp](weak_ptr<Foo> item){ return item.lock() == temp.lock();};

	auto itr (std::find_if(list.begin(), list.end(), selector));

	auto foundItem (itr->lock());

	cout << "found item : " << foundItem->number << endl;

	auto t =  (((unsigned long)(1)<<31) | ((unsigned long)(0x876)<<16) | ((unsigned long)(0))) ;
}

#endif
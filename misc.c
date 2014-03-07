

#ifdef TEST
#include <chrono>
#include <iostream>
#include <atomic>
#include <thread>

using namespace std;
using namespace std::chrono;
typedef duration<float> fsec;

auto started = steady_clock::now();
atomic<int> counter = 0;

inline int GetNumber()
{
	return ++counter;
}

inline int64_t SigmaN(int64_t n) // to avoid overflow
{
	return n * (n + 1) >> 1;
}

int SerialN(int n)
{
	for (int i = 0; i < n ; ++i)
	{
		if (SigmaN(i) == n)
			return i;
	}

	return 0;
}

int IsPerfectSquare(int n)
{
	if (n < 0)
		return 0;

	int root = (int)(sqrt(n));

	return n == root * root ?
					root : 0;
}

void Work()
{
	while (true)
	{
		int number = GetNumber();

		if (0 > number)
			break; // until overflow

		int root = IsPerfectSquare(number);

		if (0 < root)
		{
			auto last_of_serial = SerialN(number);

			if (0 < last_of_serial)
			{
				//print elapsed time
				printf("%d = %d^2 = sum(1..%d)\n %0.2f sec\n",
					number, root, last_of_serial,
					duration_cast<fsec>(steady_clock::now() - started).count()
					);
			}
		}
	}//while
}


int main (void)
{
	thread t1(Work), t2(Work), t3(Work);

	t1.join();
	t2.join();
	t3.join();
}

#endif
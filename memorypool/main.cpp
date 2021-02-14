#include <cstdlib>
#include "Alloc.h"
#include <iostream>
#include <thread>
#include "CELLtimestamp.hpp"


const int nCount = 1000000;
const int tCount = 4;
const int mCount = nCount / tCount;

char* data[nCount];

void work(int begin,int end)
{
	for (int i = begin; i < end; ++i) {
		data[i] = new char[rand() % 1024 +1];
	}
}
int main()
{
	CELLTimestamp t;
	t.update();
	for (int i = 0; i < tCount; ++i) {
		std::thread t(work, mCount * i, mCount * (i + 1));
		t.detach();
	}
	std::cout << t.getElapsedTimeInMilliSec();

	delete []data;
	return 0;
}
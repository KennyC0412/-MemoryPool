#include <cstdlib>
#include "Alloc.h"
#include <iostream>
#include <thread>
#include "CELLtimestamp.hpp"
#include <memory>
#include "ObjectPool.hpp"

const int nCount = 20;
const int tCount = 4;
const int mCount = nCount / tCount;



class A :public ObjectPoolBase<A,10>{
public:
	A(int n):num(n) {
		std::cout << n << std::endl;
	}
	void fun() {
	}
private:
	int num;
};

A* data[nCount];

void work(int begin, int end)
{
	for (int i = begin; i < end; ++i) {
		data[i] = A::createObject(i);
	}
	for (int i = begin; i < end; ++i) {
		A::destroyObject(data[i]);
	}

}

class B :public ObjectPoolBase<B,10> {
public:
	B(int n,int m) :num(n) {
		std::cout << n*m << std::endl;
	}
	void fun() {
	}
private:
	int num;
};


int main()
{
	CELLTimestamp t;
	t.update();
	for (int i = 0; i < tCount; ++i) {
		std::thread t(work, mCount * i, mCount * (i + 1));
		t.detach();
	}
	std::cout << t.getElapsedTimeInMilliSec();
	getchar();
	/*CELLTimestamp t;
	t.update();
	for (int i = 0; i < 10000000; i++) {
		std::shared_ptr<A> a = std::make_shared<A>(i);
	}
	std::cout << t.getElapsedTimeInMilliSec();
	std::cout << std::endl;
	t.update();
	for (int i = 0; i < 10000000; i++) {
		A* a = new A(i);
		delete a;
	}
	std::cout << t.getElapsedTimeInMilliSec();*/
	
	//std::cout << sizeof(B);
	//B* b = B::createObject(3, 4);
	//B::destroyObject(b);
	return 0;
}
#pragma once
#ifndef _MEMORYPOOL_H_
#define _MEMORYPOOL_H_
#include <cstdlib>


#ifdef _DEBUG
#include <iostream>
	#define xCout std::cout
#else
	#define xCout(...)
#endif

const int MAX_MEMORY_SIZE = 64;

class MemoryAlloc;

//�ڴ��
class MemoryBlock
{
public:
	//�ڴ����
	int nID;
	//���ô���
	int nRef;
	//�����ڴ�飨�أ�
	MemoryAlloc* pAlloc;
	//��һ��λ��
	MemoryBlock* pNext;
	//�Ƿ����ڴ����
	bool inPool;
};

//�ڴ��
class MemoryAlloc
{
public:
	MemoryAlloc() :pBuf(nullptr), pHead(nullptr){ }
	~MemoryAlloc()
	{
		if (pBuf)
			free(pBuf);
	}	
	//��ʼ��
	void initMem();
	//�����ڴ�
	void* allocMem(size_t);
	//�ͷ��ڴ�
	void freeMem(void*);
protected:
	//�ڴ�ص�ַ
	char* pBuf;
	//�ڴ��ͷ��ָ��
	MemoryBlock* pHead;
	//�ڴ浥Ԫ��С
	size_t nSize;
	//�ڴ浥Ԫ����
	size_t nBlockSize;
};

template<size_t nsize,size_t nblockSize>
class MemoryAllocator : public MemoryAlloc
{
public:
	MemoryAllocator() {
		const int size = sizeof(void*);
		nSize = (nsize / size) * size + (nsize % size ? size:0 );
		nBlockSize = nblockSize;
		//initMem();
	}
};

//�ڴ������
class MemoryManage
{
public:
	//����
	static MemoryManage& getInstance();
	//�����ڴ�
	void *allocMem(size_t);
	//�ͷ��ڴ�
	void freeMem(void*);
private:
	//�����췽������Ϊ˽��
	MemoryManage(){
		init(0, 64, &mem64);
	}
	~MemoryManage(){}
	MemoryManage(MemoryManage&) = delete;//ɾ���������캯��
	MemoryManage& operator=(MemoryManage&) = delete;//ɾ�����������
private:
	//�ڴ��ӳ�������ʼ��
	void init(int, int, MemoryAlloc *);
	MemoryAllocator<64, 12> mem64;
	MemoryAlloc* szAlloc[MAX_MEMORY_SIZE + 1];
};
#endif
#pragma once
#include<stdlib.h>
#include<iostream>
#include<string>
using namespace std;

template <typename T>
class MyQueue
{
public:
	MyQueue(int queueCapacity);			//创建队列
	~MyQueue();			//销毁队列
	void ClearQueue();			//清空队列
	bool QueueEmpty() const;				//判空队列；不可修改数据成员用const修饰
	int QueueLength() const;					//队列长度
	bool EnQueue(T element);			//入队
	bool DeQueue(T& element);			//出队
	void QueueTraverse();			//遍历队列
	bool QueueFull();			//队列判满
private:
	T* m_pQueue;			//队列数组指针
	int m_QueueLen;			//队列长度
	int m_QueueCapacity;			//队列容量
	int m_iHead;			//队头索引
	int m_iTail;			//队尾索引
};

template <typename T>
MyQueue<T>::MyQueue(int queueCapacity)
{
	m_QueueCapacity = queueCapacity;
	m_iHead = 0;
	m_iTail = 0;
	m_QueueLen = 0;
	m_pQueue = new T[m_QueueCapacity];
}

template <typename T>
MyQueue<T>::~MyQueue()
{
	delete []m_pQueue;
	m_pQueue = NULL;
}

template <typename T>
void MyQueue<T>::ClearQueue()
{
	m_iHead = 0;
	m_iTail = 0;
	m_QueueLen = 0;
}

template <typename T>
bool MyQueue<T>::QueueEmpty() const
{
	return m_QueueLen == 0 ? true : false;
}

template <typename T>
int MyQueue<T>::QueueLength() const
{
	return m_QueueLen;
}

template <typename T>
bool MyQueue<T>::QueueFull()
{
	if (m_QueueLen == m_QueueCapacity)
	{
		return true;
	}
	return false;
}

template <typename T>
bool MyQueue<T>::EnQueue(T element)
{
	if (!QueueFull())
	{
		m_QueueLen++;
		m_pQueue[m_iTail] = element;
		m_iTail++;
		m_iTail = m_iTail % m_QueueCapacity;
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
bool MyQueue<T>::DeQueue(T &element)
{
	if (QueueEmpty())
	{
		return false;
	}
	else
	{
		element = m_pQueue[m_iHead];
		m_iHead++;
		m_iHead = m_iHead % m_QueueCapacity;
		m_QueueLen--;
		return true;
	}
}

template <typename T>
void MyQueue<T>::QueueTraverse()
{
	for (int i = m_iHead;  i < m_iHead + m_QueueLen; i++)
	{
		cout << m_pQueue[i % m_QueueLen] << endl;
	}
}
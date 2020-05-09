#pragma once
#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;

template <typename T>
class MyStack
{
public:
	MyStack(int size);			//创建并初始化栈
	virtual ~MyStack();			//销毁栈
	bool StackEmpty();			//判空栈
	bool StackFull();			//判满栈
	void ClearStack();			//清空栈
	int StackLength();			//栈中已有元素个数
	bool push(T element);			//入栈
	bool pop(T &element);		//出栈
	void StackTraverse(bool isfromButtom);			//遍历栈
private:
	T *m_pBuffer;			//栈空间指针
	int m_iSize;			//栈空间大小
	int m_iTop;			//栈顶坐标
};

template <typename T>
MyStack<T>::MyStack(int size)
{
	m_iSize = size;
	m_iTop = 0;
	m_pBuffer = new T(m_iSize);
}

template <typename T>
MyStack<T>::~MyStack()
{
	delete []m_pBuffer;
	m_pBuffer = NULL;
}

template <typename T>
bool MyStack<T>::StackEmpty()
{
	if (0 == m_iTop)
	{
		return true;
	}
	return false;
}

template <typename T>
bool MyStack<T>::StackFull()
{
	if (m_iTop == m_iSize)
	{
		return true;
	}
	return false;
}

template <typename T>
void MyStack<T>::ClearStack()
{
	m_iTop = 0;
}

template <typename T>
int MyStack<T>::StackLength()
{
	return m_iTop;
}

template <typename T>
bool MyStack<T>::push(T element)
{
	if (StackFull())
	{
		return false;
	}
	m_pBuffer[m_iTop] = element;
	m_iTop++;
	return true;
}

template <typename T>
bool MyStack<T>::pop(T &element)
{
	if (StackEmpty())
	{
		return false;
	}
	else
	{
		/*--m_iTop;
		element = m_pBuffer[m_iTop];*/
		element = m_pBuffer[--m_iTop];
		return true;
	}
}


template <typename T>
void MyStack<T>::StackTraverse(bool isfromButtom)
{
	if (false == isfromButtom)			//从下往上遍历
	{
		for (int i = 0; i < m_iTop; i++)
		{
			cout << m_pBuffer[i] << ",";
		}
	}
	else             //从上往下遍历
	{
		for (int j = m_iTop - 1; j >= 0; j--)
		{
			cout << m_pBuffer[j] << ",";
		}
	}
}
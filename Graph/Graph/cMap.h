#pragma once
#include<stdlib.h>
#include<string>
#include<iostream>
#include "Node.h"
#include "Edge.h"
#include <vector>
using namespace std;

class cMap
{
public:
	cMap(int Capacity);
	~cMap();
	bool AddNode(Node* pNode);			//加入结点
	void resetNode();			//重置结点
	bool setValueToMatrixForDirectedGraph(int row, int col, int val = 1);			//为有向图设置邻接矩阵
	bool setValueToMatrixForUnDirectedGraph(int row, int col, int val = 1);			//为无向图设置邻接矩阵

	void printMatrix();			//打印邻接矩阵

	void depthFirstTaverse(int nodeIndex);			//深度优先遍历
	void breadthFirstTaverse(int nodeIndex);			//广度优先遍历

	void primTree(int nodeIndex);			//普利姆算法（普利姆生成树）
	void kruskalTree();			//克鲁斯卡尔算法（克鲁斯卡尔生成树）

private:
	bool getValueFromMatrix(int row, int col, int& val);			//从矩阵中获取权值
	void breadthFirstTaverseImpl(vector<int>preVec);			//广度优先遍历实现函数
	int getMinEDge(vector<Edge> edgeVec);			//取最小边
	bool isInSet(vector<int> nodeSet, int target);			//判断点是否在集合内
	void mergeNodeSet(vector<int> &nodeSetA, vector<int> nodeSetB);			//将集合B合并到集合A

private:
	int m_iCapacity;			//图中容纳的顶点数
	int m_iNodeCount;			//图中已经添加了的顶点数
	Node* m_pNodeArray;			//存放顶点数组
	int* m_pMatrix;			//存放邻接数组
	Edge* m_pEdge;			//最小边的指针
};

cMap::cMap(int Capacity)
{
	m_iCapacity = Capacity;
	m_iNodeCount = 0;
	m_pNodeArray = new Node[m_iCapacity];
	m_pMatrix = new int[m_iCapacity * m_iCapacity];
	memset(m_pMatrix, 0, m_iCapacity * m_iCapacity * sizeof(int));
	m_pEdge = new Edge[m_iCapacity - 1];
}
cMap::~cMap()
{
	delete []m_pMatrix;
	delete []m_pNodeArray;
	delete[]m_pEdge;
}

bool cMap::AddNode(Node* pNode)
{
	if (pNode == NULL)
	{
		return false;
	}
	m_pNodeArray[m_iNodeCount].m_cData = pNode->m_cData;
	m_iNodeCount++;
	return true;
}

void cMap::resetNode()
{
	for (int i = 0; i < m_iNodeCount; i++)
	{
		m_pNodeArray[i].m_bIsVisited = false;
	}
}

bool cMap::setValueToMatrixForDirectedGraph(int row, int col, int val)
{
	if (row < 0 || row >= m_iCapacity || col < 0 || col >= m_iCapacity)
	{
		return false;
	}
	m_pMatrix[row * m_iCapacity + col] = val;
	return true;
}

bool cMap::setValueToMatrixForUnDirectedGraph(int row, int col, int val)
{
	if (row < 0 || row >= m_iCapacity || col < 0 || col >= m_iCapacity)
	{
		return false;
	}
	m_pMatrix[row * m_iCapacity + col] = val;
	m_pMatrix[col * m_iCapacity + row] = val;
	return true;
}

void cMap::printMatrix()
{
	for (int r = 0; r < m_iCapacity; r++)
	{
		for (int c = 0; c < m_iCapacity; c++)
		{
			cout << m_pMatrix[r * m_iCapacity + c] << " ";
		}
		cout << endl;
	}
}

bool cMap::getValueFromMatrix(int row, int col, int& val)
{
	if (row < 0 || row >= m_iCapacity || col < 0 || col >= m_iCapacity)
	{
		return false;
	}
	val = m_pMatrix[row * m_iCapacity + col];
	return true;
}

void cMap::depthFirstTaverse(int nodeIndex)
{
	cout << m_pNodeArray[nodeIndex].m_cData << " ";
	m_pNodeArray[nodeIndex].m_bIsVisited = true;
	int value = 0;
	for (int i = 0; i < m_iCapacity; i++)
	{
		getValueFromMatrix(nodeIndex, i, value);
		if (value != 0)
		{
			if (m_pNodeArray[i].m_bIsVisited)
			{
				continue;
			}
			else
			{
				depthFirstTaverse(i);
			}
		}
		else
		{
			continue;
		}
	}
}

void cMap::breadthFirstTaverse(int nodeIndex)
{
	cout << m_pNodeArray[nodeIndex].m_cData << " ";
	m_pNodeArray[nodeIndex].m_bIsVisited = true;
	vector<int> curVec;
	
	curVec.push_back(nodeIndex);
	breadthFirstTaverseImpl(curVec);
}

void cMap::breadthFirstTaverseImpl(vector<int>preVec)
{
	int value = 0;
	vector<int> curVec;
	for (int i = 0; i < (int)preVec.size(); i++)
	{
		for (int j = 0; j < m_iCapacity; j++)
		{
			getValueFromMatrix(preVec[i], j, value);
			if (value != 0)
			{
				if (m_pNodeArray[j].m_bIsVisited)
				{
					continue;
				}
				else
				{
					cout << m_pNodeArray[j].m_cData << " ";
					m_pNodeArray[j].m_bIsVisited = true;
					curVec.push_back(j);
				}
			}
		}
	}
	if (curVec.size() != 0)
	{
		breadthFirstTaverseImpl(curVec);
	}
}

void cMap::primTree(int nodeIndex)
{
	int value = 0;
	int edgeCount = 0;
	vector<int> nodeVec;
	vector<Edge> edgeVec;

	cout << m_pNodeArray[nodeIndex].m_cData << endl;

	nodeVec.push_back(nodeIndex);
	m_pNodeArray[nodeIndex].m_bIsVisited = true;

	while (edgeCount < m_iCapacity-1)
	{
		int temp = nodeVec.back();
		for (int i = 0; i < m_iCapacity; i++)
		{
			getValueFromMatrix(temp, i, value);
			if (value != 0)
			{
				if (m_pNodeArray[i].m_bIsVisited)
				{
					continue;
				}
				else
				{
					Edge edge(temp, i, value);
					edgeVec.push_back(edge);
				}
			}
		}
		//从可选边中找出最小边
		int edgeIndex = getMinEDge(edgeVec);
		if (edgeIndex == -1)
		{
			edgeVec[nodeIndex].m_bSelected = true;
		}
		else
		{
			edgeVec[edgeIndex].m_bSelected = true;
		}
		

		cout << edgeVec[edgeIndex].m_iNodeIndexA << "----" << edgeVec[edgeIndex].m_iNodeIndexB << " ";
		cout << edgeVec[edgeIndex].m_iWeightValue << endl;

		m_pEdge[edgeCount] = edgeVec[edgeIndex];
		edgeCount++;
		int nextNodeIndex = edgeVec[edgeIndex].m_iNodeIndexB;
		nodeVec.push_back(nextNodeIndex);
		m_pNodeArray[nextNodeIndex].m_bIsVisited = true;

		cout << m_pNodeArray[nextNodeIndex].m_cData << endl;

	}
}

int cMap::getMinEDge(vector<Edge> edgeVec)
{
	int minWeight = 0;
	int edgeIndex = 0;
	int i = 0;
	for (; i < edgeVec.size(); i++)
	{
		if (!edgeVec[i].m_bSelected)
		{
			minWeight = edgeVec[i].m_iWeightValue;
			edgeIndex = i;
			break;
		}
	}
	if (0 == minWeight)
	{
		return -1;
	}
	for (; i < edgeVec.size(); i++)
	{
		if (edgeVec[i].m_bSelected)
		{
			continue;
		}
		else
		{
			if (minWeight > edgeVec[i].m_iWeightValue)
			{
				minWeight = edgeVec[i].m_iWeightValue;
				edgeIndex = i;
			}
		}
	}
	return edgeIndex;
}

void cMap::kruskalTree()
{
	int value = 0;
	int edgeCount = 0;

	vector<vector<int>>nodeSets;			//存放结点的数组
	//取出所有边
	vector<Edge> edgeVec;
	for (int i = 0; i < m_iCapacity; i++)
	{
		for (int k = i + 1; k < m_iCapacity; k++)
		{
			getValueFromMatrix(i, k, value);
			if (0 != value)
			{
				Edge edge(i, k, value);
				edgeVec.push_back(edge);
			}
		}
	}
	//从所有边中取出组成最小生成树的边
	//1.找到算法结束条件
	while (edgeCount < m_iCapacity-1)
	{
		//2.从边集合中找到最小边
		int minEdgeIndex = getMinEDge(edgeVec);
		edgeVec[minEdgeIndex].m_bSelected = true;

		//3.找出最小边连接的点
		int nodeAIndex = edgeVec[minEdgeIndex].m_iNodeIndexA;
		int nodeBIndex = edgeVec[minEdgeIndex].m_iNodeIndexB;

		//4.找出点所在的点集合
		bool nodeAIsInSet = false;
		bool nodeBIsInSet = false;

		int nodeAIsInSetLabel = -1;
		int nodeBIsInSetLabel = -1;

		for (int i = 0; i < (int)nodeSets.size(); i++)
		{
			nodeAIsInSet = isInSet(nodeSets[i], nodeAIndex);
			if (nodeAIsInSet)
			{
				nodeAIsInSetLabel = i;
			}
		}
		for (int i = 0; i < (int)nodeSets.size(); i++)
		{
			nodeBIsInSet = isInSet(nodeSets[i], nodeBIndex);
			if (nodeBIsInSet)
			{
				nodeBIsInSetLabel = i;
			}
		}

		//5.根据点所在的集合不同做出不同处理
		if (nodeAIsInSetLabel == -1 && nodeBIsInSetLabel == -1)
		{
			vector<int>vec;
			vec.push_back(nodeAIsInSetLabel);
			vec.push_back(nodeBIsInSetLabel);
			nodeSets.push_back(vec);
		}
		else if (nodeAIsInSetLabel == -1 && nodeBIsInSetLabel != -1)
		{
			nodeSets[nodeBIsInSetLabel].push_back(nodeAIsInSetLabel);
		}
		else if (nodeBIsInSetLabel == -1 && nodeAIsInSetLabel != -1)
		{
			nodeSets[nodeAIsInSetLabel].push_back(nodeBIsInSetLabel);
		}
		else if (nodeAIsInSetLabel != 1 && nodeBIsInSetLabel != -1 && nodeAIsInSetLabel != nodeBIsInSetLabel)
		{
			mergeNodeSet(nodeSets[nodeAIsInSetLabel], nodeSets[nodeBIsInSetLabel]);
			for (int k = nodeBIsInSetLabel; k < (int)nodeSets.size() - 1; k++)
			{
				nodeSets[k] = nodeSets[k + 1];
			}
		}
		else if (nodeAIsInSetLabel != 1 && nodeBIsInSetLabel != -1 && nodeAIsInSetLabel == nodeBIsInSetLabel)
		{
			continue;
		}
		m_pEdge[edgeCount] = edgeVec[minEdgeIndex];
		edgeCount++;

		cout << edgeVec[minEdgeIndex].m_iNodeIndexA << "---" << edgeVec[minEdgeIndex].m_iNodeIndexB << " ";
		cout << edgeVec[minEdgeIndex].m_iWeightValue << endl;

	}
	
}

bool cMap::isInSet(vector<int> nodeSet, int target)
{
	for (int i = 0; i < (int)nodeSet.size(); i++)
	{
		if (nodeSet[i] == target)
		{
			return true;
		}
	}
	return false;
}

void cMap::mergeNodeSet(vector<int>& nodeSetA, vector<int> nodeSetB)
{
	for (int i = 0; i < (int)nodeSetB.size(); i++)
	{
		nodeSetA.push_back(nodeSetB[i]);
	}
}
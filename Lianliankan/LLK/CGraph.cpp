#include "stdafx.h"
#include "CGraph.h"


CGraph::CGraph()
{
	InitGraph();
}


CGraph::~CGraph()
{
}


void CGraph::InitGraph()
{
	m_nVexnum = 0;
	m_nArcnum = 0;
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		//初始化顶点
		m_Vertices[i] = -1;
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			//初始化边
			m_AdjMatrix[i][j] = 0;
		}
	}
}


int CGraph::AddVertex(int info)
{
	if (m_nVexnum >= MAX_VERTEX_NUM)
	{
		return -1;
	}
	//将顶点数据info添加到顶点数组中
	m_Vertices[m_nVexnum] = info;
	m_nVexnum++;
	//返回顶点数组中顶点的个数
	return m_nVexnum;
}

//获取顶点数组中索引为nIndex的顶点的信息
int CGraph::GetVertex(int nIndex)
{
	
	return m_Vertices[nIndex];
}


void CGraph::AddArc(int nV1Index,int nV2Index)
{
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
	//m_nArcnum++;
}


// 获取顶点数组中的顶点数
int CGraph::GetVexnum()
{
	// TODO: 在此处添加实现代码.
	return m_nVexnum;
}


// 将图顶点数组中索引号为nIndex的顶点的值更新为info
void CGraph::UpdateVertex(int nIndex,int info)
{
	m_Vertices[nIndex] = info;
}


// 判断两个点之间是否有边，参数为传入的点在数组中的索引
bool CGraph::GetArc(int nV1Index,int nV2Index)
{
	//鉴于空白处和所有点都有边
	if ((m_AdjMatrix[nV1Index][nV2Index] == true))
		return true;
	else
	    return false;
}


// 将图中顶点和边还原成初始状态
void CGraph::ClearGraph()
{
	//调用initgraph函数直接将图结构还原成初始状态
	InitGraph();
}

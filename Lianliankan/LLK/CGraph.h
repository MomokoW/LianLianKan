#pragma once
#include"global.h"
typedef int Vertices[MAX_VERTEX_NUM];
typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
class CGraph
{
protected:

	
	Vertices m_Vertices;    //顶点数组
	AdjMatrix m_AdjMatrix;  //关系矩阵
	int m_nVexnum;          //顶点数
	int m_nArcnum;          //边数
	void InitGraph();       //初始化图
public:
	CGraph();
	~CGraph();
	//将顶点info添加到顶点数组中
	int AddVertex(int info);
	//获取顶点数组中索引为nIndex的顶点的信息
	int GetVertex(int nIndex);
	//添加关系矩阵中，nV1Index,nV2Index的关系
	void AddArc(int nV1Index, int nV2Index);
	// 获取顶点数组中的顶点数
	int GetVexnum();
	// 将图顶点数组中索引号为nIndex的顶点的值更新为info
	void UpdateVertex(int nIndex, int info);
	// 判断两个点之间是否有边，参数为传入的点在数组中的索引
	bool GetArc(int nV1Index, int nV2Index);
	// 将图中顶点和边还原成初始状态
	void ClearGraph();
};


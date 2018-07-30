#pragma once
#include "global.h"
#include "CGraph.h"
#include "math.h"
class CGameLogic
{
protected:
	Vertex m_avPath[MAX_VERTEX_NUM];    //保存在进行连接判断时所经过的点
	int m_nVexNum;         //路径上的顶点数
	//将索引号为nV的顶点压入m_anPath,并判断压入顶点后，是否形成一个拐点。如果是，则拐点数加一。
	void PushVertex(Vertex v);
	void PopVertex();
	int m_anPath[MAX_VERTEX_NUM];      //保存连通路径的顶点的索引
	int m_nCorner;          //连接路径数组m_anPath中的拐点数。
		
protected:
	// 判断游戏地图中nRow行，nCol列的顶点与它上下左右的顶点是否有边，如果有边则更新图结构
	void UpdateArc(CGraph &g, int nRow, int nCol);
	// 判断索引为nVi的顶点是否保存到联通弄数组m_Path中
	bool IsExsit(int nVi);
	// 判断连接路径数组m_Path中，连续三个顶点是否构成一个顶点
	bool IsCorner();
public:
	void Clear(CGraph &g, Vertex v1, Vertex v2);
	CGameLogic();
	~CGameLogic();
	void InitMap(CGraph &g);
	bool IsLink(CGraph &g, Vertex v1, Vertex v2);
	//保存连通路径中的各个顶点
	int GetVexPath(Vertex avPath[MAX_VERTEX_NUM]);
	// 采用深度优先搜索，判断顶点V0，V1在图g中是否连通，如果连通则返回true
	bool searchPath(CGraph &g, int nV0, int nV1);
	
	// 判断图中所有的顶点是否为空，如果都为空则返回true，否则，返回false
	bool CGameLogic::IsBlank(CGraph &g);
	// 按照提示游戏的规则，查找一对消除的图片
	bool SearchValidPath(CGraph &g);
	// 对图结构中的顶点进行重排，并更新边的关系
	void ResetGraph(CGraph &g);
};

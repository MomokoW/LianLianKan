#pragma once
#include "global.h"
#include "CGraph.h"
#include "CGameLogic.h"
class CGameControl
{
private:
	CGraph m_graph; //初始游戏地图为4行，4列
	 //选中的第一个点
	Vertex m_ptSelFirst;
	//选中的第二个点
	Vertex m_ptSelSec;

public:
	CGameControl();
	~CGameControl();

	void StartGame();
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRpw, int nCol);
	void SetSecPoint(int nRpw, int nCol);
	//调用CGameLogic类中的成员函数，判断选择的两个图片能否连通，如果能连通返回true，并通过参数返回连通路径的路径中顶点个数

	bool Link(Vertex avPath[MAX_VERTEX_NUM],int &nVexnum);
	//根据计时的时间和游戏地图中剩余图片的数量，判断游戏是否结束还是正在进行，如果结束，是胜利还是失败
	int IsWin(int nTime);
	// 调用gamelogic类的函数，对数据成员m_graph中的数据进行重排	bool Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum);
	void ResetGraph();
	// 在游戏地图中查找可以消除的一对图片，并且返回连接路径和路径上的顶点数
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum);
};


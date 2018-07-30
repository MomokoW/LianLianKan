#include "stdafx.h"
#include "CGameControl.h"


CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}


void CGameControl::StartGame()
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_graph);
}

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow*MAX_COL+nCol);
}

void CGameControl::SetFirstPoint(int nRow,int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

bool CGameControl::Link(Vertex avPath[MAX_VERTEX_NUM],int &nVexnum)
{
	//得到所选中图片在数组中的索引
	int nV1Index = m_ptSelFirst.row * MAX_COL + m_ptSelFirst.col;
	int nV2Index = m_ptSelSec.row * MAX_COL + m_ptSelSec.col;
	//m_ptSelSec,m_ptFirstSec是否是同一个位置
	if ((m_ptSelFirst.row == m_ptSelSec.row) && (m_ptSelFirst.col == m_ptSelSec.col))
	{
		return false;
	}
	//m_ptSelSec,m_ptFirstSec是否是同一种图片
	if (m_graph.GetVertex(nV1Index) != m_graph.GetVertex(nV2Index))
	{
		return false;
	}
	
	//判断是否相邻并且连通
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec) == true)
	{
		//消子
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);
		//调用GetVexPath()函数来获取连接路径
		nVexnum = gameLogic.GetVexPath(avPath);
		return true;
	}
	return false;
}


//根据计时的时间和游戏地图中剩余图片的数量，判断游戏是否结束还是正在进行，如果结束，是胜利还是失败
int CGameControl::IsWin(int nTime)
{
	CGameLogic gameLogic;
	//判断游戏时间
	if (nTime <= 0)
	{
		//清除图
		m_graph.ClearGraph();
		return GAME_LOSE;
	}
	//判断图中所有点是否为空
	if (gameLogic.IsBlank(m_graph)==true)
	{
		m_graph.ClearGraph();
		return GAME_SUCCESS;;
	}
	return GAME_PLAY;
}


// 在游戏地图中查找可以消除的一对图片，并且返回连接路径和路径上的顶点数
bool CGameControl::Help(Vertex avPath[MAX_VERTEX_NUM],int &nVexnum)
{
	CGameLogic gameLogic;
	//判断图是否为空
	if (gameLogic.IsBlank(m_graph) == true)
	{
		return false;
	}
	else
	{
		//查找一个有效的提示路径
		if (gameLogic.SearchValidPath(m_graph) == true)
		{
			//返回路径的顶点
			nVexnum=gameLogic.GetVexPath(avPath);
			return true;
		}
		else
			return false;
	}

}


// 调用gamelogic类的函数，对数据成员m_graph中的数据进行重排
void CGameControl::ResetGraph()
{
	CGameLogic gameLogic;
	gameLogic.ResetGraph(m_graph);

}

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
	//�õ���ѡ��ͼƬ�������е�����
	int nV1Index = m_ptSelFirst.row * MAX_COL + m_ptSelFirst.col;
	int nV2Index = m_ptSelSec.row * MAX_COL + m_ptSelSec.col;
	//m_ptSelSec,m_ptFirstSec�Ƿ���ͬһ��λ��
	if ((m_ptSelFirst.row == m_ptSelSec.row) && (m_ptSelFirst.col == m_ptSelSec.col))
	{
		return false;
	}
	//m_ptSelSec,m_ptFirstSec�Ƿ���ͬһ��ͼƬ
	if (m_graph.GetVertex(nV1Index) != m_graph.GetVertex(nV2Index))
	{
		return false;
	}
	
	//�ж��Ƿ����ڲ�����ͨ
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSec) == true)
	{
		//����
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSec);
		//����GetVexPath()��������ȡ����·��
		nVexnum = gameLogic.GetVexPath(avPath);
		return true;
	}
	return false;
}


//���ݼ�ʱ��ʱ�����Ϸ��ͼ��ʣ��ͼƬ���������ж���Ϸ�Ƿ�����������ڽ��У������������ʤ������ʧ��
int CGameControl::IsWin(int nTime)
{
	CGameLogic gameLogic;
	//�ж���Ϸʱ��
	if (nTime <= 0)
	{
		//���ͼ
		m_graph.ClearGraph();
		return GAME_LOSE;
	}
	//�ж�ͼ�����е��Ƿ�Ϊ��
	if (gameLogic.IsBlank(m_graph)==true)
	{
		m_graph.ClearGraph();
		return GAME_SUCCESS;;
	}
	return GAME_PLAY;
}


// ����Ϸ��ͼ�в��ҿ���������һ��ͼƬ�����ҷ�������·����·���ϵĶ�����
bool CGameControl::Help(Vertex avPath[MAX_VERTEX_NUM],int &nVexnum)
{
	CGameLogic gameLogic;
	//�ж�ͼ�Ƿ�Ϊ��
	if (gameLogic.IsBlank(m_graph) == true)
	{
		return false;
	}
	else
	{
		//����һ����Ч����ʾ·��
		if (gameLogic.SearchValidPath(m_graph) == true)
		{
			//����·���Ķ���
			nVexnum=gameLogic.GetVexPath(avPath);
			return true;
		}
		else
			return false;
	}

}


// ����gamelogic��ĺ����������ݳ�Աm_graph�е����ݽ�������
void CGameControl::ResetGraph()
{
	CGameLogic gameLogic;
	gameLogic.ResetGraph(m_graph);

}

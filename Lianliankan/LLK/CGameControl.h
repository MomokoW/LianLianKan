#pragma once
#include "global.h"
#include "CGraph.h"
#include "CGameLogic.h"
class CGameControl
{
private:
	CGraph m_graph; //��ʼ��Ϸ��ͼΪ4�У�4��
	 //ѡ�еĵ�һ����
	Vertex m_ptSelFirst;
	//ѡ�еĵڶ�����
	Vertex m_ptSelSec;

public:
	CGameControl();
	~CGameControl();

	void StartGame();
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRpw, int nCol);
	void SetSecPoint(int nRpw, int nCol);
	//����CGameLogic���еĳ�Ա�������ж�ѡ�������ͼƬ�ܷ���ͨ���������ͨ����true����ͨ������������ͨ·����·���ж������

	bool Link(Vertex avPath[MAX_VERTEX_NUM],int &nVexnum);
	//���ݼ�ʱ��ʱ�����Ϸ��ͼ��ʣ��ͼƬ���������ж���Ϸ�Ƿ�����������ڽ��У������������ʤ������ʧ��
	int IsWin(int nTime);
	// ����gamelogic��ĺ����������ݳ�Աm_graph�е����ݽ�������	bool Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum);
	void ResetGraph();
	// ����Ϸ��ͼ�в��ҿ���������һ��ͼƬ�����ҷ�������·����·���ϵĶ�����
	bool Help(Vertex avPath[MAX_VERTEX_NUM], int &nVexnum);
};


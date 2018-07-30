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
		//��ʼ������
		m_Vertices[i] = -1;
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			//��ʼ����
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
	//����������info��ӵ�����������
	m_Vertices[m_nVexnum] = info;
	m_nVexnum++;
	//���ض��������ж���ĸ���
	return m_nVexnum;
}

//��ȡ��������������ΪnIndex�Ķ������Ϣ
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


// ��ȡ���������еĶ�����
int CGraph::GetVexnum()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	return m_nVexnum;
}


// ��ͼ����������������ΪnIndex�Ķ����ֵ����Ϊinfo
void CGraph::UpdateVertex(int nIndex,int info)
{
	m_Vertices[nIndex] = info;
}


// �ж�������֮���Ƿ��бߣ�����Ϊ����ĵ��������е�����
bool CGraph::GetArc(int nV1Index,int nV2Index)
{
	//���ڿհ״������е㶼�б�
	if ((m_AdjMatrix[nV1Index][nV2Index] == true))
		return true;
	else
	    return false;
}


// ��ͼ�ж���ͱ߻�ԭ�ɳ�ʼ״̬
void CGraph::ClearGraph()
{
	//����initgraph����ֱ�ӽ�ͼ�ṹ��ԭ�ɳ�ʼ״̬
	InitGraph();
}

#pragma once
#include"global.h"
typedef int Vertices[MAX_VERTEX_NUM];
typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
class CGraph
{
protected:

	
	Vertices m_Vertices;    //��������
	AdjMatrix m_AdjMatrix;  //��ϵ����
	int m_nVexnum;          //������
	int m_nArcnum;          //����
	void InitGraph();       //��ʼ��ͼ
public:
	CGraph();
	~CGraph();
	//������info��ӵ�����������
	int AddVertex(int info);
	//��ȡ��������������ΪnIndex�Ķ������Ϣ
	int GetVertex(int nIndex);
	//��ӹ�ϵ�����У�nV1Index,nV2Index�Ĺ�ϵ
	void AddArc(int nV1Index, int nV2Index);
	// ��ȡ���������еĶ�����
	int GetVexnum();
	// ��ͼ����������������ΪnIndex�Ķ����ֵ����Ϊinfo
	void UpdateVertex(int nIndex, int info);
	// �ж�������֮���Ƿ��бߣ�����Ϊ����ĵ��������е�����
	bool GetArc(int nV1Index, int nV2Index);
	// ��ͼ�ж���ͱ߻�ԭ�ɳ�ʼ״̬
	void ClearGraph();
};


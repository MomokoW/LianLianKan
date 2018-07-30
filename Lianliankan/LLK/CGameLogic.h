#pragma once
#include "global.h"
#include "CGraph.h"
#include "math.h"
class CGameLogic
{
protected:
	Vertex m_avPath[MAX_VERTEX_NUM];    //�����ڽ��������ж�ʱ�������ĵ�
	int m_nVexNum;         //·���ϵĶ�����
	//��������ΪnV�Ķ���ѹ��m_anPath,���ж�ѹ�붥����Ƿ��γ�һ���յ㡣����ǣ���յ�����һ��
	void PushVertex(Vertex v);
	void PopVertex();
	int m_anPath[MAX_VERTEX_NUM];      //������ͨ·���Ķ��������
	int m_nCorner;          //����·������m_anPath�еĹյ�����
		
protected:
	// �ж���Ϸ��ͼ��nRow�У�nCol�еĶ��������������ҵĶ����Ƿ��бߣ�����б������ͼ�ṹ
	void UpdateArc(CGraph &g, int nRow, int nCol);
	// �ж�����ΪnVi�Ķ����Ƿ񱣴浽��ͨŪ����m_Path��
	bool IsExsit(int nVi);
	// �ж�����·������m_Path�У��������������Ƿ񹹳�һ������
	bool IsCorner();
public:
	void Clear(CGraph &g, Vertex v1, Vertex v2);
	CGameLogic();
	~CGameLogic();
	void InitMap(CGraph &g);
	bool IsLink(CGraph &g, Vertex v1, Vertex v2);
	//������ͨ·���еĸ�������
	int GetVexPath(Vertex avPath[MAX_VERTEX_NUM]);
	// ������������������ж϶���V0��V1��ͼg���Ƿ���ͨ�������ͨ�򷵻�true
	bool searchPath(CGraph &g, int nV0, int nV1);
	
	// �ж�ͼ�����еĶ����Ƿ�Ϊ�գ������Ϊ���򷵻�true�����򣬷���false
	bool CGameLogic::IsBlank(CGraph &g);
	// ������ʾ��Ϸ�Ĺ��򣬲���һ��������ͼƬ
	bool SearchValidPath(CGraph &g);
	// ��ͼ�ṹ�еĶ���������ţ������±ߵĹ�ϵ
	void ResetGraph(CGraph &g);
};

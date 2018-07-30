#include "stdafx.h"
#include "CGameLogic.h"


CGameLogic::CGameLogic()
{
	m_nVexNum = 0;
	m_nCorner = 0;
}


CGameLogic::~CGameLogic()
{
}


void CGameLogic::InitMap(CGraph &g)
{
	//������ɵ�ͼ
	int anTemp[MAX_VERTEX_NUM];
	//�ȳ�ʼ����ͼ
	//���ٻ�ɫ
	for (int i = 0; i < MAX_PICNUM; i++)
	{
		//�ظ���
		for (int j = 0; j < REPEAT_NUM; j++)
		{
			anTemp[i*REPEAT_NUM + j] = i;
		}
	}
	//��������
	srand((int)time(NULL));

	//������⽻����������
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		//����õ���������
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//����������ֵ
		int nTmp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = nTmp;
	}
	//����Ϸ��ͼ�����е�Ԫ�ر��浽ͼg�Ķ���������
	for (int i = 0; i <MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
		{
			g.AddVertex(anTemp[i*MAX_COL+j]);
		}
	
	//����ͼ��ϵ����
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j <MAX_COL; j++)
		{
			UpdateArc(g, i, j);
		}
	
}

//�ж�ѡ�е��������Ƿ�����,�������ͨ�򷵻�true����������ͨ·��
bool CGameLogic::IsLink(CGraph &g, Vertex v1, Vertex v2)
{
	//�õ���ѡ��ͼƬ�������е�����
	int nV1Index = v1.row * MAX_COL + v1.col;
	int nV2Index = v2.row * MAX_COL+ v2.col;

	//ѹ���һ����
	PushVertex(v1);

	//��Ѱ����֮�����ͨ·��
	if (searchPath(g,nV1Index,nV2Index)==true)
	{
			
			return true;

    }
	//��������򵯳���һ����
	PopVertex();
	return false;
}

//��Vertex v1��v2����Ϸ��ͼ�п�����ͨʱ������Ϸ��ͼ��v1��v2�����ֵ��Ϊ�գ������±�
void CGameLogic::Clear(CGraph &g,Vertex v1,Vertex v2)
{
	//����ͼ�ṹ

	//�õ���ѡ��ͼƬ�������е�����
	int nV1Index = v1.row * MAX_COL + v1.col;
	int nV2Index = v2.row * MAX_COL + v2.col;
	//���¶���
	g.UpdateVertex(nV1Index, BLANK);
	g.UpdateVertex(nV2Index, BLANK);
	//����ͼ��ϵ���飬��v1,v2���������ҵĶ��㶼�б�
	UpdateArc(g, v1.row, v1.col);
	UpdateArc(g, v2.row, v2.col);
}

//��ȡ�õ�·��avPath[MAX_VERTEX_NUM]����ͨ���������ظ����ú�����ͨ������ֵ���ض�����
int CGameLogic::GetVexPath(Vertex avPath[MAX_VERTEX_NUM])
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}
//���һ��·������
void CGameLogic::PushVertex(Vertex v)
{
    //��������Ϣ�Ͷ����������е�������Ϣ��ѹ��ջ
	m_avPath[m_nVexNum] = v;
	int nIndex= v.row * MAX_COL + v.col;
	m_anPath[m_nVexNum] = nIndex;
	m_nVexNum++;
	//�ж��Ƿ��γ��˹յ㣬��������ļ�����δ�γɵȲ����У����йյ�
	if (m_nVexNum >= 3)
	{
		if (IsCorner())
		{
			m_nCorner++;
		}
	}
}


void CGameLogic::PopVertex()
{
	//��m_anPath��ȡ��֮ǰ���ж��Ƿ��γ���һ���յ㣬�γ�����յ�����һ
	if (IsCorner())
	{
		m_nCorner--;
	}
	m_nVexNum--;

}


// �ж���Ϸ��ͼ��nRow�У�nCol�еĶ��������������ҵĶ����Ƿ��бߣ�����б������ͼ�ṹ
void CGameLogic::UpdateArc(CGraph &g,int nRow,int nCol)
{
	//�õ�ѡ�е��λ����Ϣ�������ڶ��������е�λ��
	int nV1Index = nRow *MAX_COL + nCol;
	//����õ��Ѿ������������������Ҷ�����
	if (nCol > 0)    //�������
	{
		int nV2Index = nV1Index - 1;
		if ((g.GetVertex(nV1Index)==BLANK)||(g.GetVertex(nV1Index) == g.GetVertex(nV2Index)))
		{
			g.AddArc(nV1Index, nV2Index);
		}

	}
	if (nCol < MAX_COL-1)      //�ұ�����
	{
		int nV2Index = nV1Index + 1;
		if ((g.GetVertex(nV1Index) == BLANK) || (g.GetVertex(nV1Index) == g.GetVertex(nV2Index)))
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow > 0)      //�ϱ�����
	{
		int nV2Index = nV1Index - MAX_COL;
		if ((g.GetVertex(nV1Index) == BLANK) || (g.GetVertex(nV1Index) == g.GetVertex(nV2Index)))
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow < MAX_ROW-1)       //�±�����
	{
		int nV2Index = nV1Index + MAX_COL;
		if ((g.GetVertex(nV1Index) == BLANK) || (g.GetVertex(nV1Index) == g.GetVertex(nV2Index)))
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
}


// ������������������ж϶���V0��V1��ͼg���Ƿ���ͨ�������ͨ�򷵻�true
bool CGameLogic::searchPath(CGraph &g,int nV0,int nV1)
{
	//��ȡͼ�Ķ�����
	int nVexnum = g.GetVexnum();

	//����ͼ��V0�У���0�е�nVexnum�У�ֵΪtrue�ĵ�
	for (int nVi = 0; nVi < nVexnum; nVi++)
	{
		//�ҵ���v0��ͨ�ĵ�
		if (g.GetArc(nV0,nVi) && !IsExsit(nVi))
		{
			Vertex v;
			v.row = nVi / MAX_COL;
			v.col = nVi % MAX_COL;
			//ѹ�뵱ǰ���㣬��Ϊ·����һ����Ч����
			PushVertex(v);

			//�жϹյ�����û�г���2�������������·��
			if (m_nCorner > 2)
			{
				PopVertex();       //ȡ��ѹ��ĵ㣬��PushVertex(nVi)��Ӧ
				continue;          //����
			}

			//���м䶥�㲻��nViʱ��������Ѱ��������ͨ�ĵ�
			if (nVi != nV1)
			{
				//���м䶥�㲻Ϊ��ʱ����ʾ����·��ͨ
				if (g.GetVertex(nVi) != BLANK)
				{
					PopVertex();       //ȡ��ѹ��ĵ㣬��PushVertex(nVi)��Ӧ
					continue;          //����
				}
				//���nVi��һ���Ѿ������ĵ㣬���ж�(nVi,nV1)�Ƿ���ͨ
				if (searchPath(g, nVi, nV1))
				{
						//searchPath(g,nVi,nV1)��ʾ�Ѿ��ҵ���һ����ͨ·��������true
						return true;
				}
				else //(nVi,nV1)����ͨ�������
				{
					PopVertex();       //ȡ��ѹ��ĵ㣬��PushVertex(nVi)��Ӧ
					continue;          //����
				}
				
			}
			else
			{
				//���nVi==nV1,��ʾ�Ѿ��ҵ���һ����ͨ·��������true
				return true;
			}
		}
	}
	return false;
}


// �ж�����ΪnVi�Ķ����Ƿ��Ѿ�����ͨ����m_Path��,�������򷵻�false
bool CGameLogic::IsExsit(int nVi)
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_anPath[i] == nVi)
			return true;
	}
	return false;
}


// �ж�����·������m_Path�У��������������Ƿ񹹳�һ������
bool CGameLogic::IsCorner()
{
	if (m_nVexNum >= 3)
	{
		//���������������������γ��˵Ȳ����У���û�йյ�
		if (((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2) == m_anPath[m_nVexNum - 2])
			return false;
		else
			return true;
	}
	return false;
}


// �ж�ͼ�����еĶ����Ƿ�Ϊ�գ������Ϊ���򷵻�true�����򣬷���false
bool CGameLogic::IsBlank(CGraph &g)
{
	for (int i = 0; i < g.GetVexnum(); i++)
	{
		if (g.GetVertex(i) != BLANK)
			return false;
	}
	return true;
}


// ������ʾ��Ϸ�Ĺ��򣬲���һ��������ͼƬ
bool CGameLogic::SearchValidPath(CGraph &g)
{
	//�õ�������
	int nVexnum = g.GetVexnum();
	for (int i = 0; i < nVexnum; i++)
	{
		//�õ���һ���ǿն���,��Ϊ����Ѱ����һ��
		if (g.GetVertex(i) == BLANK)
			continue;
		
		//�Ӹõ��ұ߿�ʼ�����õ��ڶ���ͬɫ����
		for (int j = i+1; j < nVexnum; j++)
		{
			//�������ջ��Ϊ·������ʼ����
			Vertex v0;
			v0.row = i / MAX_COL;
			v0.col = i % MAX_COL;
			//ѹ�뵱ǰ���㣬��Ϊ·����һ����Ч����
			PushVertex(v0);
		    //�����i����͵�j����ͬɫ�������ͨ�ж�
			if (g.GetVertex(j) == g.GetVertex(i))
			{
				//�ж��Ƿ���ͨ��������ͨ��·��
				if (searchPath(g, i, j) == true)
				{
					return true;
				}
				else
				{
					//����ͨ��ȡ��ѹ�����㣬������������֮��û����ͨ·��
					PopVertex();
				}
			}
			else
			{
				//����ͼƬ��ͬ��ȡ��֮ǰѹ������
				PopVertex();
			}
		
		}

	}
	return false;
}


// ��ͼ�ṹ�еĶ���������ţ������±ߵĹ�ϵ
void CGameLogic::ResetGraph(CGraph &g)
{
	//��������
	srand((int)time(NULL));
	//���������������,�ظ�100��
	for (int i = 0; i < 100; i++)
	{
		//����õ���������
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//����������ֵ
		int nTmp = g.GetVertex(nIndex1);
		g.UpdateVertex(nIndex1, g.GetVertex(nIndex2));
		g.UpdateVertex(nIndex2, nTmp);
		}	
     //����ͼ��ϵ����
    for (int i = 0; i < MAX_ROW; i++)
	   for (int j = 0; j <MAX_COL; j++)
	   {
	   	   UpdateArc(g, i, j);
	   }
}

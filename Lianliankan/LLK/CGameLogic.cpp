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
	//随机生成地图
	int anTemp[MAX_VERTEX_NUM];
	//先初始化地图
	//多少花色
	for (int i = 0; i < MAX_PICNUM; i++)
	{
		//重复数
		for (int j = 0; j < REPEAT_NUM; j++)
		{
			anTemp[i*REPEAT_NUM + j] = i;
		}
	}
	//设置种子
	srand((int)time(NULL));

	//随机任意交换两个数字
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		//随机得到两个坐标
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//交换两个数值
		int nTmp = anTemp[nIndex1];
		anTemp[nIndex1] = anTemp[nIndex2];
		anTemp[nIndex2] = nTmp;
	}
	//将游戏地图数组中的元素保存到图g的顶点数组中
	for (int i = 0; i <MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
		{
			g.AddVertex(anTemp[i*MAX_COL+j]);
		}
	
	//更新图关系数组
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j <MAX_COL; j++)
		{
			UpdateArc(g, i, j);
		}
	
}

//判断选中的两个点是否相连,如果能连通则返回true，并保存连通路径
bool CGameLogic::IsLink(CGraph &g, Vertex v1, Vertex v2)
{
	//得到所选中图片在数组中的索引
	int nV1Index = v1.row * MAX_COL + v1.col;
	int nV2Index = v2.row * MAX_COL+ v2.col;

	//压入第一个点
	PushVertex(v1);

	//搜寻两点之间的连通路径
	if (searchPath(g,nV1Index,nV2Index)==true)
	{
			
			return true;

    }
	//如果不是则弹出第一个点
	PopVertex();
	return false;
}

//当Vertex v1，v2在游戏地图中可以连通时，将游戏地图中v1，v2顶点的值设为空，并更新边
void CGameLogic::Clear(CGraph &g,Vertex v1,Vertex v2)
{
	//更新图结构

	//得到所选中图片在数组中的索引
	int nV1Index = v1.row * MAX_COL + v1.col;
	int nV2Index = v2.row * MAX_COL + v2.col;
	//更新顶点
	g.UpdateVertex(nV1Index, BLANK);
	g.UpdateVertex(nV2Index, BLANK);
	//更新图关系数组，让v1,v2与上下左右的顶点都有边
	UpdateArc(g, v1.row, v1.col);
	UpdateArc(g, v2.row, v2.col);
}

//获取得到路径avPath[MAX_VERTEX_NUM]，并通过参数返回给调用函数，通过返回值返回顶点数
int CGameLogic::GetVexPath(Vertex avPath[MAX_VERTEX_NUM])
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}
//添加一个路径顶点
void CGameLogic::PushVertex(Vertex v)
{
    //将顶点信息和顶点在数组中的索引信息均压入栈
	m_avPath[m_nVexNum] = v;
	int nIndex= v.row * MAX_COL + v.col;
	m_anPath[m_nVexNum] = nIndex;
	m_nVexNum++;
	//判断是否形成了拐点，如果连续的几个数未形成等差数列，则有拐点
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
	//从m_anPath中取出之前，判断是否形成了一个拐点，形成了则拐点数减一
	if (IsCorner())
	{
		m_nCorner--;
	}
	m_nVexNum--;

}


// 判断游戏地图中nRow行，nCol列的顶点与它上下左右的顶点是否有边，如果有边则更新图结构
void CGameLogic::UpdateArc(CGraph &g,int nRow,int nCol)
{
	//得到选中点的位置信息，即它在顶点数组中的位置
	int nV1Index = nRow *MAX_COL + nCol;
	//如果该点已经被消除则与上下左右都相邻
	if (nCol > 0)    //左边相邻
	{
		int nV2Index = nV1Index - 1;
		if ((g.GetVertex(nV1Index)==BLANK)||(g.GetVertex(nV1Index) == g.GetVertex(nV2Index)))
		{
			g.AddArc(nV1Index, nV2Index);
		}

	}
	if (nCol < MAX_COL-1)      //右边相邻
	{
		int nV2Index = nV1Index + 1;
		if ((g.GetVertex(nV1Index) == BLANK) || (g.GetVertex(nV1Index) == g.GetVertex(nV2Index)))
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow > 0)      //上边相邻
	{
		int nV2Index = nV1Index - MAX_COL;
		if ((g.GetVertex(nV1Index) == BLANK) || (g.GetVertex(nV1Index) == g.GetVertex(nV2Index)))
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
	if (nRow < MAX_ROW-1)       //下边相邻
	{
		int nV2Index = nV1Index + MAX_COL;
		if ((g.GetVertex(nV1Index) == BLANK) || (g.GetVertex(nV1Index) == g.GetVertex(nV2Index)))
		{
			g.AddArc(nV1Index, nV2Index);
		}
	}
}


// 采用深度优先搜索，判断顶点V0，V1在图g中是否连通，如果连通则返回true
bool CGameLogic::searchPath(CGraph &g,int nV0,int nV1)
{
	//获取图的顶点数
	int nVexnum = g.GetVexnum();

	//遍历图中V0行，从0列到nVexnum列，值为true的点
	for (int nVi = 0; nVi < nVexnum; nVi++)
	{
		//找到与v0连通的点
		if (g.GetArc(nV0,nVi) && !IsExsit(nVi))
		{
			Vertex v;
			v.row = nVi / MAX_COL;
			v.col = nVi % MAX_COL;
			//压入当前顶点，设为路径的一个有效顶点
			PushVertex(v);

			//判断拐点数有没有超过2，有则放弃此条路径
			if (m_nCorner > 2)
			{
				PopVertex();       //取出压入的点，与PushVertex(nVi)对应
				continue;          //回溯
			}

			//当中间顶点不是nVi时，继续搜寻相邻且连通的点
			if (nVi != nV1)
			{
				//当中间顶点不为空时，表示该条路不通
				if (g.GetVertex(nVi) != BLANK)
				{
					PopVertex();       //取出压入的点，与PushVertex(nVi)对应
					continue;          //回溯
				}
				//如果nVi是一个已经消除的点，则判断(nVi,nV1)是否连通
				if (searchPath(g, nVi, nV1))
				{
						//searchPath(g,nVi,nV1)表示已经找到了一条连通路径，返回true
						return true;
				}
				else //(nVi,nV1)不连通，则回溯
				{
					PopVertex();       //取出压入的点，与PushVertex(nVi)对应
					continue;          //回溯
				}
				
			}
			else
			{
				//如果nVi==nV1,表示已经找到了一条连通路径，返回true
				return true;
			}
		}
	}
	return false;
}


// 判断索引为nVi的顶点是否已经在连通数组m_Path中,不存在则返回false
bool CGameLogic::IsExsit(int nVi)
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_anPath[i] == nVi)
			return true;
	}
	return false;
}


// 判断连接路径数组m_Path中，连续三个顶点是否构成一个顶点
bool CGameLogic::IsCorner()
{
	if (m_nVexNum >= 3)
	{
		//如果连续三个顶点的索引形成了等差数列，则没有拐点
		if (((m_anPath[m_nVexNum - 1] + m_anPath[m_nVexNum - 3]) / 2) == m_anPath[m_nVexNum - 2])
			return false;
		else
			return true;
	}
	return false;
}


// 判断图中所有的顶点是否为空，如果都为空则返回true，否则，返回false
bool CGameLogic::IsBlank(CGraph &g)
{
	for (int i = 0; i < g.GetVexnum(); i++)
	{
		if (g.GetVertex(i) != BLANK)
			return false;
	}
	return true;
}


// 按照提示游戏的规则，查找一对消除的图片
bool CGameLogic::SearchValidPath(CGraph &g)
{
	//得到顶点数
	int nVexnum = g.GetVexnum();
	for (int i = 0; i < nVexnum; i++)
	{
		//得到第一个非空顶点,不为空则寻找下一个
		if (g.GetVertex(i) == BLANK)
			continue;
		
		//从该点右边开始遍历得到第二个同色顶点
		for (int j = i+1; j < nVexnum; j++)
		{
			//将起点入栈作为路径的起始顶点
			Vertex v0;
			v0.row = i / MAX_COL;
			v0.col = i % MAX_COL;
			//压入当前顶点，设为路径的一个有效顶点
			PushVertex(v0);
		    //如果第i个点和第j个点同色则进行连通判断
			if (g.GetVertex(j) == g.GetVertex(i))
			{
				//判断是否连通并保存连通的路径
				if (searchPath(g, i, j) == true)
				{
					return true;
				}
				else
				{
					//不连通则取出压入的起点，代表这两个点之间没有连通路径
					PopVertex();
				}
			}
			else
			{
				//两个图片不同则取出之前压入的起点
				PopVertex();
			}
		
		}

	}
	return false;
}


// 对图结构中的顶点进行重排，并更新边的关系
void CGameLogic::ResetGraph(CGraph &g)
{
	//设置种子
	srand((int)time(NULL));
	//随机交换两个数字,重复100次
	for (int i = 0; i < 100; i++)
	{
		//随机得到两个坐标
		int nIndex1 = rand() % MAX_VERTEX_NUM;
		int nIndex2 = rand() % MAX_VERTEX_NUM;

		//交换两个数值
		int nTmp = g.GetVertex(nIndex1);
		g.UpdateVertex(nIndex1, g.GetVertex(nIndex2));
		g.UpdateVertex(nIndex2, nTmp);
		}	
     //更新图关系数组
    for (int i = 0; i < MAX_ROW; i++)
	   for (int j = 0; j <MAX_COL; j++)
	   {
	   	   UpdateArc(g, i, j);
	   }
}

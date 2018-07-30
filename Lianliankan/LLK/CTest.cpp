#include "stdafx.h"
#include "CTest.h"
#include <string.h>


CTest::CTest()
{
}


CTest::~CTest()
{
}

/*
int CTest::Output(CGraph &g)
{
	int nVexnum = g.GetVexnum();
	//新建日志文件
	CStdioFile file(_T("log.txt"), CFile::modeCreate | CFile::modeReadWrite);
	LPCUTSTR strTmp;
	//输出顶点信息
	for(int i=0;i<nVexnum;i++)
	{ 
		//strTmp.Format(_T("%d\t", g.GetVertex(i)));
		file.WriteString(strTmp);
		

	return 0;
}
*/

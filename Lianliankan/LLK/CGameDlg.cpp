// CGameDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "CHelpDialog.h"
#include "afxdialogex.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GME_DIALOG, pParent)
{
	//加载系统图标
	m_hIcon = AfxGetApp()->LoadIconW(IDR_MAINFRAME);
	//初始化游戏的起始位置
	m_ptGameTop.x = MAP_LEFT;
	m_ptGameTop.y = MAP_TOP;
	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;
	m_bFirstPoint = true;
	//初始化游戏区域的大小
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;
	//初始化游戏进行的状态
	m_bPlaying = false;
	m_bPause = true;
	m_bScores = 0;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
	DDX_Text(pDX, IDC_TIME, m_text);
	
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGameDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_REARRANGE, &CGameDlg::OnBnClickedBtnRearrange)
	ON_BN_CLICKED(IDC_BTN_TIPS, &CGameDlg::OnBnClickedBtnTips)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CGameDlg::OnBnClickedBtnSetting)
	ON_BN_CLICKED(IDC_BTN_HELP, &CGameDlg::OnBnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_TOOLS, &CGameDlg::OnBnClickedBtnTools)
	ON_BN_CLICKED(IDC_BTN_SCORES, &CGameDlg::OnBnClickedBtnScores)
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()

END_MESSAGE_MAP()


// CGameDlg 消息处理程序


void CGameDlg::InitBackground(void)
{
	// TODO: 在此处添加实现代码.
	//加载位图
	CClientDC dc(this);
	HANDLE bmp = NULL;

	if (model == 1)
	{
		 bmp = ::LoadImage(NULL, _T("theme\\picture\\jiandan.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	else if (model == 2)
	{
		 bmp = ::LoadImage(NULL, _T("theme\\picture\\xiuxian.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	else
	{
		bmp = ::LoadImage(NULL, _T("theme\\picture\\guanqia.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	//创建兼容DC
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(bmp);
	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMap;
	bmpMap.CreateCompatibleBitmap(&dc, 800, 600);

	//将位图选进DC
	m_dcMem.SelectObject(&bmpMap);
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

}
BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InitBackground();
	InitButton();
	InitElement();

	
	return true;
}




void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
	
}
//设置不同窗口的标签
void CGameDlg::InitButton()
{
	CButton *b;
	if (model == 1)
	{
		this->SetWindowTextW((CString)"欢乐连连看—基本模式");
		b = (CButton*)GetDlgItem(IDC_BTN_TOOLS);
		b->ShowWindow(FALSE);
		b = (CButton*)GetDlgItem(IDC_BTN_SCORES);
		b->ShowWindow(FALSE);
	}
	else if (model == 2)
	{
		this->SetWindowTextW((CString)"欢乐连连看—休闲模式");
	}
	else if (model == 3)
	{
		this->SetWindowTextW((CString)"欢乐连连看—关卡模式");
	}
}
void CGameDlg::InitElement()
{
	// 获得当前对话框的视频内存
	CClientDC dc(this);

	//加载BMP图片资源
	HANDLE hBmp = ::LoadImage(NULL, _T("theme\\picture\\diamond.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内容兼容的内存DC
	m_dcElement.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcElement.SelectObject(hBmp);

	//加载BMP图片资源
	HANDLE hMask = ::LoadImage(NULL, _T("theme\\picture\\Background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内容兼容的内存DC
	m_dcMask.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcMask.SelectObject(hMask);

	//加载BMP图片资源
	HANDLE hPause = ::LoadImage(NULL, _T("theme\\picture\\pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内容兼容的内存DC
	m_dcPause.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcPause.SelectObject(hPause);
	//创建于视频内容兼容的位图DC
	CBitmap bmpMap;
	bmpMap.CreateCompatibleBitmap(&dc, 800, 600);
	//将位图保存到缓冲DC中
	m_dcCache.CreateCompatibleDC(&dc);
	m_dcCache.SelectObject(&bmpMap);


}
void CGameDlg::OnBnClickedBtnStart()
{
	// 初始化游戏地图
	m_gameControl.StartGame();

	//更新界面
	UpdateMap();
	//更新窗口
	InvalidateRect(m_rtGameRect,FALSE);

	//游戏状态为正在进行中
	m_bPlaying = true;
	m_bPause = false;
	//将开始按钮设置为禁用状态
	this->GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);

	//显示进度条和时间框
	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_TIME)->ShowWindow(TRUE);
    //设置进度条的范围为（0,300）
	m_GameProgress.SetRange(0, 300);

	//设置进度条的步长为-1
	m_GameProgress.SetStep(-1);

	//设置开始位置为300
	m_GameProgress.SetPos(300);

	//调用SetTimer函数生成一个计时器
	this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
	
	
}
//封装游戏界面语句
void  CGameDlg::UpdateMap()
{
	int nLeft = m_ptGameTop.x;
	int	nTop = m_ptGameTop.y;
	int nWidth = m_sizeElem.cx;
	int nHeight = m_sizeElem.cy;
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i < MAX_ROW; i++)
	{
	
		for (int j = 0; j < MAX_COL; j++)
		{
			int nInfo = m_gameControl.GetElement(i, j);
			//m_dcMem.BitBlt(nLeft + j * nWidth, nTop + i * nHeight, nWidth, nHeight, &m_dcElement, 0, m_anMap[i][j] * nHeight, SRCCOPY);
			m_dcMem.BitBlt(nLeft + j * nWidth, nTop + i * nHeight, nWidth, nHeight, &m_dcMask, 0, nInfo * nHeight, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nWidth, nTop + i * nHeight, nWidth, nHeight, &m_dcElement, 0, nInfo * nHeight, SRCAND);
		}
	}
}





void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	//如果游戏不在进行中，则不响应鼠标事件
	if (m_bPlaying)
	{
		if (point.y < m_ptGameTop.y || point.x < m_ptGameTop.x)
		{
			return CDialogEx::OnLButtonUp(nFlags, point);
		}
		int row = (point.y - m_ptGameTop.y) / m_sizeElem.cy;   //行号
		int col = (point.x - m_ptGameTop.x) / m_sizeElem.cx;    //列号
		if (row >( MAX_ROW-1)|| col >( MAX_COL-1))
		{
			return CDialogEx::OnLButtonUp(nFlags, point);
		}
		if (m_bFirstPoint)
		{   //绘制提示框，选择第一个点
			DrawTipFrame(row, col);

			m_gameControl.SetFirstPoint(row, col);

		}
		else
		{
			//第二个点
			DrawTipFrame(row, col);
			m_gameControl.SetSecPoint(row, col);

			//获得路径
			Vertex avPath[MAX_VERTEX_NUM];
			int nVexnum;
			//判断是否是相同图片
			if (m_gameControl.Link(avPath, nVexnum))
			{
				//画提示线
				DrawTipLine(avPath, nVexnum);

				//更新图片界面
				UpdateMap();

			}
			Sleep(200);
			InvalidateRect(m_rtGameRect, FALSE);

		}
		m_bFirstPoint = !m_bFirstPoint;
	}
	else
	{
		return;
	}

}


void CGameDlg::DrawTipFrame(int nRow,int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	//得到选中矩形的左上角和右下角坐标
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);

}



void CGameDlg::DrawTipLine(Vertex avPath[MAX_VERTEX_NUM],int nVexnum)
{
	//获取DC
	CClientDC dc(this);

	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//将画笔选入DC 
	CPen *pOldPen = dc.SelectObject(&penLine);
	
	//从起点绘制连线到数组中第i个元素...第nVexnum个元素
	for (int i = 0; i < nVexnum-1; i++)
	{
		int j = i + 1;
		dc.MoveTo(m_ptGameTop.x + avPath[i].col*m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i].row*m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.LineTo(m_ptGameTop.x + avPath[j].col*m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[j].row*m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	//将原来的对象选回来
	dc.SelectObject(pOldPen);

}
//游戏暂停按钮
void CGameDlg::OnBnClickedBtnPause()
{
	if (!m_bPlaying)
	{
		return;
	}
	else
	{
		//游戏正在进行则暂停将游戏地图遮盖，并修改暂停按钮文本为继续游戏
		if (m_bPause == false)
		{
			m_dcCache.BitBlt(0, 0, 800, 600, &m_dcMem,0,0, SRCCOPY);
			m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, 640, 400, &m_dcPause, 0, 0, SRCCOPY);
			this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(L"继续游戏");
			
		}
		//游戏已暂停，还原游戏地图，并修改按钮文本为暂停游戏
		else
		{
			m_dcMem.BitBlt(0, 0, 800, 600, &m_dcCache, 0, 0, SRCCOPY);
			this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(L"暂停游戏");	
		}
		//刷新界面
		Invalidate(false);
		m_bPause = !m_bPause;
	}
}


void CGameDlg::OnBnClickedBtnRearrange()
{
	if (m_bPlaying == false)
		return;
	else
	{
		//重排
		m_gameControl.ResetGraph();

		//更新地图
		UpdateMap();

		//重绘界面
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
	}
}


void CGameDlg::OnBnClickedBtnTips()
{
	if (m_bPlaying)
	{
		//获得路径
		Vertex avPath[MAX_VERTEX_NUM];
		int nVexnum;
		//查找连通路径
		if (m_gameControl.Help(avPath, nVexnum) == true)
		{
			//画矩形框和连通路径
			DrawTipFrame(avPath[0].row, avPath[0].col);
			DrawTipFrame(avPath[nVexnum-1].row, avPath[nVexnum-1].col);
			//画提示线
			DrawTipLine(avPath, nVexnum);
			Sleep(200);
			//更新图片界面
			UpdateMap();
			
		}

	}
	else
	{
		return;
	}
}


void CGameDlg::OnBnClickedBtnSetting()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGameDlg::OnBnClickedBtnHelp()
{
	CHelpDialog dlg;
	dlg.SetModel(model);
	dlg.DoModal();
}


void CGameDlg::SetModel(int model)
{
	// TODO: 在此处添加实现代码.
	this->model = model;
}

void CGameDlg::OnBnClickedBtnTools()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGameDlg::OnBnClickedBtnScores()
{
	// TODO: 在此添加控件通知处理程序代码
}



// 更新界面，从生成的游戏地图结构中，取出顶点，根据顶点从游戏元素图片中，取出相对应的元素并显示
void CGameDlg::UpdateWindow()
{
	
}

//进行游戏计时
void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	//判断计时器的编号是否是当前计时器
	if (nIDEvent == PLAY_TIMER_ID&&m_bPlaying&&!m_bPause)
	{
		//游戏时间减一秒
		m_GameProgress.StepIt();
		//创建一个当前时间   
		CTime cTime = CTime::GetCurrentTime();
		CString strTime;
		//字符串格式化时间   
		strTime.Format(L"当前时间：%d年%d月%d日%d时%d分%d秒", cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
		//设置当前窗口标题   
		SetWindowText(strTime);

		//绘制当前秒数
		DrawGameTime();

		//判断胜负
		JudgeWin();
	}
	

	CDialogEx::OnTimer(nIDEvent);
	
}


// 判断胜负
void CGameDlg::JudgeWin()
{
	//游戏胜负判断
	int bGameStatus = m_gameControl.IsWin(m_GameProgress.GetPos());
	//判断是否继续游戏
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		//将游戏标识改为false
		m_bPlaying = false;
		//关闭定时器
		KillTimer(PLAY_TIMER_ID);
		//提示获胜

		if (bGameStatus == GAME_SUCCESS)
		{
			MessageBox(_T("获胜!"), _T("欢乐连连看—基本模式"), MB_ICONINFORMATION);
		}
		else if (bGameStatus == GAME_LOSE)
		{
			MessageBox(_T("很遗憾，时间到了!"));
		}
		//还原开始游戏按钮，使其可以点击
		this->GetDlgItem(IDC_BTN_START)->EnableWindow(true);
	}
}


// 绘制游戏时间
void CGameDlg::DrawGameTime()
{

	//修改计时器字体
	CFont font;
	font.CreatePointFont(200, _T("微软雅黑"));
	GetDlgItem(IDC_TIME)->SetFont(&font);
	int pos= m_GameProgress.GetPos();
	m_text.Format(L"%.2d:%.2d", pos / 60, pos % 60);
	UpdateData(false);
	/*CPaintDC dc(this); 
	//用于绘制的设备上下文
	
	//创建CPaintDC字体背景
	 dc.SetTextColor(RGB(0, 31, 86));
	 dc.SetBkColor(RGB(255, 0, 0));

	//创建字体
	 CFont font;
	 font.CreatePointFont(200, _T("楷体"));
	//将设置的字体选到DC中，并返回原来的字体
	 CFont *oldFont;
	 oldFont = dc.SelectObject(&font);
	 //获取文本内容
	 int pos=m_GameProgress.GetPos();
     
	 CString strWel;
	 strWel.Format(L"%.2d:%.2d", pos / 60, pos % 60);
	
	 //获取文本内容大小
	 CSize size;
	 size = dc.GetTextExtent(strWel, strWel.GetLength());
    
	 //设置文本输出区域
	 CRect rect;
	 GetClientRect(&rect);
	 //this->GetDlgItem(IDC_GAME_TIME)->GetWindowRect(&rect);
	// this->ScreenToClient(&rect);

	 //绘制文本
	 int x = (rect.Width() - size.cx) / 2;
	 int y = (rect.Height() - size.cy) / 2;
	 dc.TextOut(x, y, strWel);
	
	 Invalidate(false);
	 */
}





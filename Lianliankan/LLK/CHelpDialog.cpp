// CHelpDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "CHelpDialog.h"
#include "afxdialogex.h"


// CHelpDialog 对话框

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{
	
}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	
END_MESSAGE_MAP()


// CHelpDialog 消息处理程序


// 根据参数选择是哪个模式的帮助
int CHelpDialog::SetModel(int model)
{
	this->model = model;
	return 0;
}


BOOL CHelpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//加载位图
	CClientDC dc(this);
	HANDLE bmp = NULL;

	if (model == 1)
	{
		bmp = ::LoadImage(NULL, _T("theme\\picture\\basic.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	else if (model == 2)
	{
		bmp = ::LoadImage(NULL, _T("theme\\picture\\relax.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	else
	{
		bmp = ::LoadImage(NULL, _T("theme\\picture\\guanqia.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	//创建兼容DC
	m_dcHelp.CreateCompatibleDC(&dc);
	m_dcHelp.SelectObject(bmp);
	

	
	
	CRect rtClient;
	this->GetWindowRect(&rtClient);

	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMap;
	bmpMap.CreateCompatibleBitmap(&dc,rtClient.Width(), rtClient.Height());
	//将位图选进DC
	m_dcMem.SelectObject(&bmpMap);
	//绘制帮助信息显示区域
	this->GetDlgItem(IDC_STATIC_PICTURE)->GetWindowRect(&m_rtHelp);
	this->ScreenToClient(m_rtHelp);
	
	//绘制帮助信息
	UpdateHelp(0);

	//设置滚动条范围
	CBitmap bmpHelp;
	bmpHelp.Attach(&bmp);
	BITMAP bmpInfo;
	bmpHelp.GetBitmap(&bmpInfo);
	//设置滚动条的范围
	m_Srcollbar =(CScrollBar*) GetDlgItem(IDC_SCROLLBAR);
	m_Srcollbar->SetScrollRange(0,bmpInfo.bmHeight);
	//m_dcMem.BitBlt(0, 0, rtClient.Width(), rtClient.Height(), &m_dcHelp, 0, 0, SRCCOPY);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CHelpDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcMem, 0, 0, SRCCOPY);
}






void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	int pos = m_Srcollbar->GetScrollPos();
	switch (nSBCode)
	{
	case SB_LINEUP:     //点击向上按钮
		pos -= 1;
		break;
	case SB_LINEDOWN:   //点击向下按钮
		pos += 1;
		break;
	case SB_PAGEUP:     //向上翻页
		pos -= 10;
		break;
	case SB_PAGEDOWN:   //向下翻页
		pos += 10;
		break;  
	case SB_TOP:        //顶部
		pos = 0;
		break;
	case SB_BOTTOM:     //底部
		pos = 100;
		break;
	case SB_THUMBPOSITION:  //点击在滑块上
		pos = nPos;
		break;
	default:
		break;

	}
	m_Srcollbar->SetScrollPos(pos);
	UpdateHelp(pos);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CHelpDialog::UpdateHelp(int nPos)
{
	//将重绘区，绘制成白色
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	//绘制当前点的帮助信息
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcHelp, 0, nPos, SRCCOPY);
	//更新界面
	InvalidateRect(m_rtHelp, FALSE);
}




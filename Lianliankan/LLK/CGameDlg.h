#pragma once
#include<cstring>
#include"CGameControl.h"
#include"CGameLogic.h"
#include"global.h"

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();
	CProgressCtrl m_GameProgress;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	void InitBackground(void);
	int model;           //控制游戏模式的变量
	CDC m_dcMem;         //内存DC
	CDC m_dcElement;     //游戏元素的内存DC
	CDC m_dcMask;        //掩码DC
	CDC m_dcBG;          //背景DC

	CDC m_dcCache;       //缓存的内存DC
	CDC m_dcPause;       //暂停图片的内存DC

	CString m_text;          //显示游戏的时间
	HICON m_hIcon;    //对话框图标
	//选中的图片是否是第一次选的，TRUE是，FALSE否
	bool m_bFirstPoint;  
	//游戏区起点，游戏第一张图片的顶点坐标，相对于客户区
	CPoint m_ptGameTop;
	//元素图片大小
	CSize m_sizeElem;
	//游戏区域的大小
	CRect m_rtGameRect;    
	//游戏控制类
	CGameControl m_gameControl;


	// 表示游戏是否正在进行，true表示正在进行，false表示不在进行中
	bool m_bPlaying;
	// 表示游戏是暂停还是在进行中，false表示游戏正在进行
	bool m_bPause;
	//计算游戏的积分
	int m_bScores;
	void InitElement();
	void UpdateMap();


public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnBnClickedBtnRearrange();
	afx_msg void OnBnClickedBtnTips();
	afx_msg void OnBnClickedBtnSetting();
	afx_msg void OnBnClickedBtnHelp();
	void SetModel(int model);

	afx_msg void OnBnClickedBtnTools();
	afx_msg void OnBnClickedBtnScores();
	void InitButton();

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawTipFrame(int nRow,int nCol);
	void DrawTipLine(Vertex avPath[MAX_VERTEX_NUM],int nVexnum);
	// 更新界面，从生成的游戏地图结构中，取出顶点，根据顶点从游戏元素图片中，取出相对应的元素并显示
	void UpdateWindow();

   
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	// 判断胜负
	void JudgeWin();
	// 绘制游戏时间
	void DrawGameTime();



};

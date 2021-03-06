#pragma once


// CHelpDialog 对话框

class CHelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHelpDialog();
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HELP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;   //系统图片
	CDC m_dcMem;     //内存DC
	CDC m_dcHelp;    //帮助DC
	CRect m_rtHelp;  //图片显示区域
	int model;       //用于选择不同的模式显示不同的帮助界面
	
public:
	// 根据参数选择是哪个模式的帮助
	int SetModel(int model);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void UpdateHelp(int nPos);
	
protected:
    CScrollBar *m_Srcollbar;
};

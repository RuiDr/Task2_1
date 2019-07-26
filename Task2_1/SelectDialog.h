#pragma once

// SelectDialog 对话框

class SelectDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SelectDialog)

public:
	SelectDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SelectDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int space;
	int checkbox1;
	int checkbox2;
	afx_msg void OnBnClickedOk();
};

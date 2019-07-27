// SelectDialog.cpp: 实现文件
//
#include "stdafx.h"
#include "Task2_1.h"
#include "SelectDialog.h"
#include "afxdialogex.h"
#include "MainFrm.h"
// SelectDialog 对话框

IMPLEMENT_DYNAMIC(SelectDialog, CDialogEx)

SelectDialog::SelectDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, space(0)
{
}
SelectDialog::~SelectDialog()
{
}
void SelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, space);
}
BEGIN_MESSAGE_MAP(SelectDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &SelectDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &SelectDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &SelectDialog::OnBnClickedButton3)
	ON_BN_CLICKED(IDCANCEL, &SelectDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &SelectDialog::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &SelectDialog::OnEnChangeEdit1)
END_MESSAGE_MAP()

/*BEGIN_MESSAGE_MAP(SelectDialog, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_MESSAGE(WM_MY_MESSAGE, OnMyMessage)
END_MESSAGE_MAP()*/
// SelectDialog 消息处理程序
void SelectDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	checkbox1 = ((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	checkbox2 = ((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck();
	CDialogEx::OnOK();
}
// 实现消息处理函数
void OnMyMessage(WPARAM wParam, LPARAM lParam) 
{  // TODO: 处理用户自定义消息  ... return 0;  

}
void SelectDialog::OnBnClickedButton1()
{
	space = GetDlgItemInt(IDC_EDIT1);
	checkbox1 = ((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	checkbox2 = ((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck();
	CMainFrame* pMF = (CMainFrame*)AfxGetApp()->m_pMainWnd;  //先通过获取当前框架指针
	CView * active = pMF->GetActiveView();//才能获取当前视类指针
	if (active != NULL)  //获取了当前视类指针才能发送消息
		active->SendMessage(WM_MY_MESSAGE, space,checkbox1);   //使用PostMessage发送消息

}


void SelectDialog::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void SelectDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

// 重绘
void SelectDialog::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	draw = -1;
	CMainFrame* pMF = (CMainFrame*)AfxGetApp()->m_pMainWnd;  //先通过获取当前框架指针
	CView * active = pMF->GetActiveView();//才能获取当前视类指针
	if (active != NULL)  //获取了当前视类指针才能发送消息
		active->SendMessage(WM_MY_MESSAGE, draw, 0);   //使用PostMessage发送消息
}


void SelectDialog::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

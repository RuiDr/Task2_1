// SelectDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "Task2_1.h"
#include "SelectDialog.h"
#include "afxdialogex.h"


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
END_MESSAGE_MAP()


// SelectDialog 消息处理程序


void SelectDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	checkbox1 = ((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	checkbox2 = ((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck();
	CDialogEx::OnOK();
}

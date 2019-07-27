
// Task2_1Doc.cpp: CTask21Doc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Task2_1.h"
#endif

#include "Task2_1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTask21Doc

IMPLEMENT_DYNCREATE(CTask21Doc, CDocument)

BEGIN_MESSAGE_MAP(CTask21Doc, CDocument)
END_MESSAGE_MAP()


// CTask21Doc 构造/析构

CTask21Doc::CTask21Doc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

CTask21Doc::~CTask21Doc()
{
}

BOOL CTask21Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	SetTitle(_T("Task2_1"));
	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CTask21Doc 序列化

void CTask21Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CTask21Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CTask21Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CTask21Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CTask21Doc 诊断

#ifdef _DEBUG
void CTask21Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTask21Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTask21Doc 命令

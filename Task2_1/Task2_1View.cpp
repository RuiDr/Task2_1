
// Task2_1View.cpp: CTask21View 类的实现
//

#include "stdafx.h"
#include <atlstr.h>
#include <iostream>
#include<cmath>
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Task2_1.h"
#endif

#include "Task2_1Doc.h"
#include "Task2_1View.h"
#include <string>
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;
vector<CPoint>listPoint;
CPoint cpoint;
CPoint firstpoint;
int sum = 0;
int dis = 0;
// CTask21View


IMPLEMENT_DYNCREATE(CTask21View, CView)

BEGIN_MESSAGE_MAP(CTask21View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_32771, &CTask21View::OnErase)
END_MESSAGE_MAP()

// CTask21View 构造/析构

CTask21View::CTask21View() noexcept
{
	// TODO: 在此处添加构造代码

}

CTask21View::~CTask21View()
{
}

BOOL CTask21View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTask21View 绘图

void CTask21View::OnDraw(CDC* /*pDC*/)
{
	CTask21Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CTask21View 打印

BOOL CTask21View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTask21View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTask21View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CTask21View 诊断

#ifdef _DEBUG
void CTask21View::AssertValid() const
{
	CView::AssertValid();
}

void CTask21View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTask21Doc* CTask21View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTask21Doc)));
	return (CTask21Doc*)m_pDocument;
}
#endif //_DEBUG


// CTask21View 消息处理程序


bool CTask21View::setPixelFormat()
{
	// TODO: 在此处添加实现代码.
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), // 结构的大小  
		1, // 结构的版本  
		PFD_DRAW_TO_WINDOW | // 在窗口(而不是位图)中绘图  
		PFD_SUPPORT_OPENGL | // 支持在窗口中进行OpenGL调用  
		PFD_DOUBLEBUFFER, // 双缓冲模式  
		PFD_TYPE_RGBA, // RGBA颜色模式  
		32, // 需要32位颜色  
		0, 0, 0, 0, 0, 0, // 不用于选择模式  
		0, 0, // 不用于选择模式  
		0, 0, 0, 0, 0, // 不用于选择模式  
		16, // 深度缓冲区的大小  
		0, // 在此不使用  
		0, // 在此不使用  
		0, // 在此不使用  
		0, // 在此不使用  
		0, 0, 0 // 在此不使用  
	};
	// 选择一种与pfd所描述的最匹配的像素格式  
	// 为设备环境设置像素格式  
	int pixelformat;
	pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (0 == pixelformat) return false;
	// 为设备环境设置像素格式  
	return SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd);
	return false;
}


int CTask21View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pDC = new CClientDC(this);
	ASSERT(m_pDC != NULL);
	// 选择像素格式  
	if (!setPixelFormat()) return -1;
	// 创建渲染环境, 并使它成为当前渲染环境  
	m_hRC = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	return 0;
}
void CTask21View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hRC);
	delete m_pDC;
}
void CTask21View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	glClearColor(1, 1, 1, 1);
	// TODO: 在此添加专用代码和/或调用基类
}
void CTask21View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	glViewport(0, 0, cx, cy);
	// 设置投影矩阵(透视投影)  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)cx / (GLfloat)cy, 1.0, 1000.0);
	// 设置模型视图矩阵  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// TODO: 在此处添加消息处理程序代码
}

void CTask21View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	// 暂存的点
	CPoint tempPoint=cpoint;
	cpoint = point;
	CDC*pDC = GetDC();
	pDC->SetPixel(point, RGB(0, 0, 0));
	if (sum != 0)
	{
		pDC->MoveTo(tempPoint.x, tempPoint.y);
		pDC->LineTo(cpoint.x, cpoint.y);
	}
	else
	{
		// 记录第一个点
		firstpoint = point;
	}
	dis = sqrt((firstpoint.x - cpoint.x)*(firstpoint.x - cpoint.x) + (firstpoint.y - cpoint.y)*(firstpoint.y - cpoint.y));
	if (dis < 100)
	{
		pDC->MoveTo(firstpoint.x, firstpoint.y);
		pDC->LineTo(cpoint.x, cpoint.y);
	}
	sum++;
	CView::OnLButtonDown(nFlags, point);
}
void CTask21View::OnErase()
{
	sum = 0;
	Invalidate();
	// TODO: 在此添加命令处理程序代码
}

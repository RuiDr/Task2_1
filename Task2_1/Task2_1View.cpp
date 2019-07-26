
// Task2_1View.cpp: CTask21View 类的实现
//

#include "stdafx.h"
#include <atlstr.h>
#include <iostream>
#include "SelectDialog.h"
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
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <map>
#include <list>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;
// 存放点的信息
vector<CPoint>listPoint;
CPoint cpoint;
CPoint firstpoint;
int sum = 0;
int dis = 0;
// y最大值
int YMAX=0;
// x最大值
int XMAX = 0;
// 间距
int spaceBetween=0;
// 条数
int countLine=0;
void InitConsoleWindow();
void GetNET();
// 更新ET，将特殊点进行特殊处理
void UpdateET();
void ModifyAET();
void ModifyXAET();
void UpdateXET();
void GetNetY();
struct MyPoint
{
	float x;
	float y;
	MyPoint(float x1,float y)
	{
		this->x = x1;
		this->y = y;
	}
};
// 交点
map<int,vector<MyPoint>>IntePoint;
// CTask21View
// 边的数据结构体
typedef struct tagEDGE
{
	int ymax;  //  边的最大y坐标
	float xi;    //  与扫描线交点x坐标
	float dx;   //  斜率的倒数，dx
	tagEDGE(float my, float mx, float mdx) :ymax(my), xi(mx), dx(mdx) {}
	bool operator<(tagEDGE &e);
}EDGE;
bool tagEDGE::operator<(tagEDGE &e)
{
	if (xi != e.xi)
		return xi < e.xi;
	if (dx == 0)	return e.dx > 0;
	if (e.dx == 0)	return dx < 0;
	if (dx < 0 && e.dx>0)	return true;
	if (dx > 0 && e.dx < 0)	return false;
	return dx * ymax < e.dx*e.ymax;
}

// 边的数据结构体
typedef struct tagEDGEX
{
	int xmax;   // 边的最大x坐标
	float yi;  // 与扫描线交点y坐标
	float dy;   //  斜率的倒数，dx
	tagEDGEX(float my, float mx, float mdx) :xmax(my), yi(mx), dy(mdx) {}
	bool operator<(tagEDGEX &e);
}EDGEX;
bool tagEDGEX::operator<(tagEDGEX &e)
{
	if (yi != e.yi)
		return yi < e.yi;
	if (dy == 0)	return e.dy > 0;
	if (e.dy == 0)	return dy < 0;
	if (dy < 0 && e.dy>0)	return true;
	if (dy > 0 && e.dy < 0)	return false;
	return dy * xmax < e.dy*e.xmax;
}
// 边表
map<int, list<EDGE>>ET;
map<int, list<EDGEX>>ETX;
// int 表示序号，Edge表示结构体
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
	ON_COMMAND(ID_32772, &CTask21View::OnFilledWith)
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
	InitConsoleWindow();
	
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
	// 定义一个画笔变量
	CPen penBlack;
	CDC*pDC = GetDC();
	penBlack.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen*poldPen = pDC->SelectObject(&penBlack);
	// 上次的点
	CPoint tempPoint=cpoint;
	// 这次的点
	cpoint = point;
	//pDC->SetPixel(point, RGB(1, 0, 0));
	if (sum != 0)
	{
		// 将当前点加入到点存储器中
		freopen("CONOUT$", "w+t", stdout);// 申请写
		cout <<"point: "<< point.x << " " << point.y << endl;
		freopen("CONIN$", "r+t", stdin);  // 申请读
		listPoint.push_back(point);
		pDC->MoveTo(tempPoint.x, tempPoint.y);
		pDC->LineTo(cpoint.x, cpoint.y);
	}
	else
	{
		freopen("CONOUT$", "w+t", stdout);// 申请写
		cout <<"point: "<< point.x << " " << point.y << endl;
		freopen("CONIN$", "r+t", stdin);  // 申请读
		listPoint.push_back(point);
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
void InitConsoleWindow()
{
	AllocConsole();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle, _O_TEXT);
	FILE * hf = _fdopen(hCrt, "w");
	*stdout = *hf;
}
void CTask21View::OnErase()
{
	int i = 0;
	// 输出
	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);// 申请写
	for (auto it = listPoint.begin();it != listPoint.end();it++)
	{
		cout << it->x << " " << it->y << endl;
	}
	freopen("CONIN$", "r+t", stdin);  // 申请读
	sum = 0;
	map<int, vector<MyPoint>>IntePoint1;
	map<int, list<EDGE>>ET1;
	map<int, list<EDGEX>>ET2;
	vector<CPoint>listPoint1;
	IntePoint=IntePoint1;
	listPoint = listPoint1;
	ET=ET1;
	ETX = ET2;
	YMAX = 0;
	XMAX = 0;
	cout << "ET " << ET.size() << endl;
	cout << "ETX " << ETX.size() << endl;
	cout << "listPoint " << listPoint.size() << endl;
	Invalidate();
	// TODO: 在此添加命令处理程序代码
}
// 初始化新边表结构,画横线
void GetNET()
{
	
	for (int i = 0;i < listPoint.size() - 1;i++)
	{
		// 平行边，这里确定是x,还是y????????
		if (listPoint[i + 1].y == listPoint[i].y)
			continue;
		// 斜率的倒数
		float dx=0;
		double a = listPoint[i + 1].y - listPoint[i].y;
		if (a == 0)
		{
			 dx = 0.0;
		}
		else
		{
			 dx = (listPoint[i + 1].x - listPoint[i].x)*1.0 / (listPoint[i + 1].y - listPoint[i].y);

		}
		// xi低端点的x值，x高端点的x值
		float ymax, xi, ymin;
		if (listPoint[i + 1].y > listPoint[i].y)
		{
			ymax = listPoint[i + 1].y;
			ymin = listPoint[i].y;
			xi = listPoint[i].x;
		}
		else
		{
			ymax = listPoint[i].y;
			ymin = listPoint[i+1].y;
			xi = listPoint[i+1].x;
		}
		EDGE e(ymax, xi, dx);
		ET[ymin].push_back(e);
		if (ymax > YMAX)
		{
			YMAX = ymax;
		}
	}
	// 第一个点与最后一个点所构成的边
	int index = listPoint.size() - 1;
	if (listPoint[0].y != listPoint[index].y)
	{
		float dx = listPoint[index].y - listPoint[0].y == 0 ? 0 : (listPoint[index].x - listPoint[0].x)*1.0 / (listPoint[index].y - listPoint[0].y);
		// xi低端点的x值，x高端点的x值
		float ymax, xi, ymin;
		if (listPoint[index].y > listPoint[0].y)
		{
			ymax = listPoint[index].y;
			ymin = listPoint[0].y;
			xi = listPoint[0].x;
		}
		else
		{
			ymax = listPoint[0].y;
			ymin = listPoint[index].y;
			xi = listPoint[index].x;
		}
		EDGE e(ymax, xi, dx);
		ET[ymin].push_back(e);
	}
}
// 更新ET，将特殊点进行特殊处理
void UpdateET()
{
	for (auto it = ET.begin();it != ET.end();)
	{
		// 只存在一条边
		if (it->second.size() == 1)
		{
			EDGE e = *(it->second.begin());
			e.xi += e.dx;
			// 这里处理矛盾
			int ymin = it->first + 1;
			ET.erase(it++);
			ET[ymin].push_back(e);
		}
		else
		{
			it++;
		}
	}
}
// 获取两个点中，y值最小的值
int getIndex(CPoint c1,CPoint c2)
{
	if (c1.y < c2.y)
	{
		return c1.y;
	}
	else
	{
		return c2.y;
	}
}
// 对AET表排序
void ModifyAET()
{
	// 建立活动边表

	//创建活动边表并填充
	std::list<EDGE>AET;
	int y = 0;
	int count = 0;
	//获取首元素
	y = ET.begin()->first;
	cout << "y is " << y << endl;
	cout << " YMAX IS " << YMAX <<" "<< endl;
	AET.insert(AET.begin(), ET.begin()->second.begin(), ET.begin()->second.end());
	AET.sort();
	do {
		auto node = AET.begin();
		while (node != AET.end())
		{
			// 获取与扫描线交点的值
			float x1 = node->xi;
			// 
			node->xi += node->dx;
			node++;
			if (node != AET.end())
			{
				float x2 = node->xi;
			    node->xi += node->dx;
			    node++;
				if (x1 != x2) 
				{
					vector<MyPoint>listp;
					
					listp.push_back(MyPoint(x1, y));
					listp.push_back(MyPoint(x2, y));
					IntePoint.insert(pair<int, vector<MyPoint>>(count, listp));
					count++;
				}
				cout << "x1: " << x1 << " x2: " << x2 << " y: " << y<<" "<<endl;
			}	
		}
		y++;
		// 逆序迭代器，指向c容器的最后一个元素
		// 如果y大于ymax，表示扫描线大于最大y值
		std::list<EDGE>::reverse_iterator it = AET.rbegin();
		for (; it != AET.rend();) {
			if (y >it->ymax)
				it = std::list<EDGE>::reverse_iterator(AET.erase((++it).base()));
			else it++;
		}
		// 找到扫描线对应的活性表
		auto itt=ET.find(y);
		if (itt != ET.end())
			AET.insert(AET.end(), ET[y].begin(), ET[y].end());
		AET.sort();
		// 如过y大于YMAX,直接退出
	} while ((y<YMAX));
}
void CTask21View::OnFilledWith()
{
	// TODO: 在此添加命令处理程序代码
	// 初始化边表
	/*listPoint.push_back(CPoint(40, 10));
	listPoint.push_back(CPoint(30, 40));
	listPoint.push_back(CPoint(60, 80));
	listPoint.push_back(CPoint(80, 40));*/
	AllocConsole();
	// 间距设置为4
	SelectDialog selectDialog;
	if (selectDialog.DoModal() == IDOK)
	{
		spaceBetween = selectDialog.space;
		if (selectDialog.checkbox1 == 1)
		{
			GetNET();
			UpdateET();
			ModifyAET();
			CDC*pDC = GetDC();
			freopen("CONOUT$", "w+t", stdout);// 申请写
			cout << "大小 " << IntePoint.size() << endl;
			for (auto it = IntePoint.begin();it != IntePoint.end();it++)
			{
				vector<MyPoint>list = it->second;

				//pDC->SetPixel(list[0].x, RGB(255, 0, 0));
				cout << "画线 " << list[0].x << " " << list[0].y << " " << endl;
				//cout << "画线 " << list[1].x << " " << list[1].y << " " << endl;
				freopen("CONIN$", "r+t", stdin);  // 申请读

				int flag = list[0].y;
				if (flag % spaceBetween == 0)
				{
					pDC->MoveTo(list[0].x, list[0].y);
					pDC->LineTo(list[1].x, list[1].y);
				}
			}
		}
		else
		{
			GetNetY();
			// 更新边表

			UpdateXET();
			// 对AET表操作

			ModifyXAET();

			CDC*pDC = GetDC();
			freopen("CONOUT$", "w+t", stdout);// 申请写
			cout << "大小 " << IntePoint.size() << endl;
			for (auto it = IntePoint.begin();it != IntePoint.end();it++)
			{
				vector<MyPoint>list = it->second;

				//pDC->SetPixel(list[0].x, RGB(255, 0, 0));
				cout << "画线 " << list[0].x << " " << list[0].y << " " << endl;
				//cout << "画线 " << list[1].x << " " << list[1].y << " " << endl;
				freopen("CONIN$", "r+t", stdin);  // 申请读

				int flag = list[0].x;
				if (flag % spaceBetween == 0)
				{
					pDC->MoveTo(list[0].x, list[0].y);
					pDC->LineTo(list[1].x, list[1].y);
				}

			}
		}

	}

}
// 进行填充X轴
// 画竖线
void GetNetY()
{
	for (int i = 0;i < listPoint.size() - 1;i++)
	{
		// 平行边，这里确定是x,还是y????????
		if (listPoint[i + 1].x == listPoint[i].x)
			continue;
		// 斜率的倒数
		float dy = 0;
		double a = listPoint[i + 1].y - listPoint[i].y;
		if (a == 0)
		{
			dy = 0.0;
		}
		else
		{
			dy = 1.0/((listPoint[i + 1].x - listPoint[i].x)*1.0 / (listPoint[i + 1].y - listPoint[i].y));

		}
		// xi低端点的x值，x高端点的x值
		float xmax, yi, xmin;
		if (listPoint[i + 1].x> listPoint[i].x)
		{
			xmax = listPoint[i + 1].x;
			xmin = listPoint[i].x;
			yi = listPoint[i].y;
		}
		else
		{
			xmax = listPoint[i].x;
			xmin = listPoint[i + 1].x;
			yi = listPoint[i + 1].y;
		}
		EDGEX e(xmax,yi, dy);
		ETX[xmin].push_back(e);
		if (xmax > XMAX)
		{
			XMAX = xmax;
		}
	}
	// 第一个点与最后一个点所构成的边
	int index = listPoint.size() - 1;
	if (listPoint[0].x!= listPoint[index].x)
	{
		float dy = listPoint[index].y- listPoint[0].y == 0 ? 0 : 1.0/( (listPoint[index].x - listPoint[0].x)*1.0 / (listPoint[index].y - listPoint[0].y));
		// xi低端点的x值，x高端点的x值
		float xmax, yi, xmin;
		if (listPoint[index].x > listPoint[0].x)
		{
			xmax = listPoint[index].x;
			xmin = listPoint[0].x;
			yi = listPoint[0].y;
		}
		else
		{
			xmax = listPoint[0].x;
			xmin = listPoint[index].x;
			yi = listPoint[index].y;
		}
		EDGEX e(xmax, yi, dy);
		ETX[xmin].push_back(e);
	}
}
// 更新ET
void UpdateXET()
{
	for (auto it = ETX.begin();it != ETX.end();)
	{
		// 只存在一条边
		if (it->second.size() == 1)
		{
			EDGEX e = *(it->second.begin());
			e.yi += e.dy;
			// 这里处理矛盾
			int xmin = it->first + 1;
			ETX.erase(it++);
			ETX[xmin].push_back(e);
		}
		else
		{
			it++;
		}
	}
}
// 对AET表排序
void ModifyXAET()
{
	// 建立活动边表
	//创建活动边表并填充
	std::list<EDGEX>AET;
	int x = 0;
	int count = 0;
	//获取首元素
	x = ETX.begin()->first;
	//cout << "x is " << x << endl;
	//cout << " XMAX IS " << XMAX << " " << endl;
	AET.insert(AET.begin(), ETX.begin()->second.begin(), ETX.begin()->second.end());
	AET.sort();
	do {
		auto node = AET.begin();
		while (node != AET.end())
		{
			// 获取与扫描线交点的值
			float y1 = node->yi;
			// 
			node->yi += node->dy;
			node++;
			if (node != AET.end())
			{
				float y2 = node->yi;
				node->yi += node->dy;
				node++;
				if (y1 != y2)
				{
					vector<MyPoint>listp;

					listp.push_back(MyPoint(x, y1));
					listp.push_back(MyPoint(x, y2));
					IntePoint.insert(pair<int, vector<MyPoint>>(count, listp));
					count++;
				}
			}
		}
		x++;
		// 逆序迭代器，指向c容器的最后一个元素
		// 如果y大于ymax，表示扫描线大于最大y值
		std::list<EDGEX>::reverse_iterator it = AET.rbegin();
		for (; it != AET.rend();) {
			if (x > it->xmax)
				it = std::list<EDGEX>::reverse_iterator(AET.erase((++it).base()));
			else it++;
		}
		// 找到扫描线对应的活性表
		auto itt = ETX.find(x);
		if (itt != ETX.end())
			AET.insert(AET.end(), ETX[x].begin(), ETX[x].end());
		AET.sort();
		// 如过y大于YMAX,直接退出
	} while ((x < XMAX));
}